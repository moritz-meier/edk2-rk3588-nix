{ runCommand }:
{ uboot }:

runCommand "boot-image" { } ''
  mkdir $out

  dd if=${uboot}/idbloader.img of=$out/boot.bin bs=1K seek=32
''
