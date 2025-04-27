{pkgs ? import <nixpkgs> {}, ...}: let
  path = builtins.path {
    path = ./.;
    name = "ninecraft-source";
  };
in rec {
  extract = pkgs.callPackage ./nix/pkgs/extract.nix {};
  ninecraft = pkgs.pkgsi686Linux.callPackage ./nix/pkgs/ninecraft.nix {
    ninecraft-extract = extract;
  };
  nixos = {pkgs, ...}: {
    imports = [./nix/modules/nixos.nix];
    programs.ninecraft.package = ninecraft;
  };
}
