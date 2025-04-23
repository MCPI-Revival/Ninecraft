{
  description = "A mcpe 0.1.0-0.10.5 launcher for linux and windows ";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils
  }: let
    system = "x86_64-linux";
    mkPkgs = system:
      import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      };
  in 
   flake-utils.lib.eachDefaultSystem (system: let
      pkgs = mkPkgs system;
    in {
    packages = rec {
      ninecraft = pkgs.pkgsi686Linux.callPackage ./nix/pkgs/ninecraft.nix {};
      default = ninecraft;
      extract = pkgs.callPackage ./nix/pkgs/extract.nix {};
      patch = pkgs.callPackage ./nix/pkgs/patch.nix {};

    };
  });
}
