{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=release-24.11";

    treefmt-nix.url = "github:numtide/treefmt-nix";
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs =
    {
      self,
      nixpkgs,
      treefmt-nix,
      ...
    }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
        overlays = [ self.overlays.default ];
      };

      treefmtEval = treefmt-nix.lib.evalModule pkgs ./treefmt.nix;

    in
    {
      packages.${system} = {

      };

      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          binwalk
          dtc
          rkdeveloptool
          git-subrepo
        ];
      };

      # for `nix fmt`
      formatter.${system} = treefmtEval.config.build.wrapper;

      # for `nix flake check`
      checks.${system}.formatting = treefmtEval.config.build.check self;

      overlays.default = import ./overlay.nix;
    };
}
