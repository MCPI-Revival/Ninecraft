{
  pkgs ?
    import <nixpkgs> {
      config = {
        allowUnfree = true;
        android_sdk.accept_license = true;
      };
    },
  lib ? import ./lib.nix {inherit pkgs;},
  ninecraftPkgs ? import ./pkgs {inherit pkgs;},
}:
ninecraftPkgs
// {
  inherit (lib) nixgl;
  home = import ./home;
  nixos = import ./nixos;
}
