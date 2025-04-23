{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
  }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
  in {
    packages.${system} = rec {
      ninecraft = pkgs.pkgsi686Linux.callPackage ./nix/pkgs/ninecraft.nix {};
      default = ninecraft;
      extract = pkgs.callPackage ./nix/pkgs/extract.nix {};
      patch = pkgs.callPackage ./nix/pkgs/patch.nix {};

    };
  };
}
