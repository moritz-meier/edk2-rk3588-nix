{
  fetchgit,
  pkgsCross,
  python3,
  acpica-tools,
  llvmPackages,
  dtc,
  edk2-base-tools,
}:
{
  plat,
  edk2-src ? fetchgit {
    url = "https://github.com/edk2-porting/edk2-rk3588.git";
    hash = "sha256-3awEMdFMGYsH18/wjQDkpMoZgWc4sfnm4ttgUof4fl4=";
    fetchSubmodules = true;
  },
}:
pkgsCross.aarch64-multiplatform.stdenv.mkDerivation rec {
  name = "edk2";

  src = edk2-src;

  nativeBuildInputs = [
    python3
    acpica-tools
    llvmPackages.libcxxClang
    dtc
  ];

  buildInputs = [ ];

  hardeningDisable = [
    "format"
  ];

  GCC5_AARCH64_PREFIX = pkgsCross.aarch64-multiplatform.stdenv.cc.targetPrefix;

  unpackPhase = ''
    cp -r -- ${src} ./source
    chmod -R a+rwX ./source
  '';

  patchPhase = ''
    patchShebangs ./source
  '';

  configurePhase = ''
    cd ./source
    mkdir -p Conf

    export EDK_TOOLS_PATH=${edk2-base-tools { }}
    export PACKAGES_PATH="$PWD/edk2:$PWD/edk2-platforms:$PWD/edk2-rockchip:$PWD/devicetree:$PWD/edk2-non-osi:$PWD"

    config=$(grep -rl 'PLATFORM_NAME=${plat}' ./configs/)
    dsc=$(grep '^DSC_FILE=' $config | cut -d = -f 2 -)
    export PLATFORM=$PWD/$dsc

    source edk2/edksetup.sh BaseTools
  '';

  buildPhase = ''
    build -a AARCH64 -b RELEASE -t GCC5 -p $PLATFORM -n $NIX_BUILD_CORES
  '';

  installPhase = ''
    mkdir $out
    cp -r ./Build/${plat}/RELEASE_GCC5/* $out/
  '';

  dontFixup = true;
}
