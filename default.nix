{pkgs ? import <nixpkgs> {}, ...}: let
  path = builtins.path {
    path = ./.;
    name = "ninecraft-source";
  };
  nixgl = import (builtins.fetchTarball "https://github.com/nix-community/nixGL/archive/master.tar.gz");
in rec {
  extract = pkgs.callPackage ./nix/pkgs/extract.nix {};
  ninecraft = pkgs.pkgsi686Linux.callPackage ./nix/pkgs/ninecraft.nix {
    ninecraft-extract = extract;
    nixgl = nixgl.nixgl;
  };
  nixos = {pkgs, ...}: {
    imports = [./nix/nixos];
    programs.ninecraft.package = ninecraft;
  };
  shell = import ./nix/shell.nix {
    inherit (pkgs) mkShell;
    inherit ninecraft;
    ninecraft-extract = extract;
  };
}
