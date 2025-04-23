{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
  let 
  system = "x86_64-linux";
  pkgs = import nixpkgs {inherit system;};
  in 
  {
    packages.${system}.default = pkgs.pkgsi686Linux.callPackage ./nix/pkgs/ninecraft.nix {};
  };
}
