{pkgs ? import <nixpkgs> {}}: let
  isIntel86 = pkgs.stdenv.hostPlatform.isx86;
  flakeLock = builtins.fromJSON (builtins.readFile ../flake.lock);
  getHash = name: flakeLock.nodes.${name}.locked.narHash;
  nixgl = pkgs.fetchFromGitHub {
    owner = "nix-community";
    repo = "nixGL";
    rev = "main";
    hash = getHash "nixgl";
  };
in {
  inherit getHash;
  nixgl = import nixgl {
    pkgs = pkgs;
    enable32bits = isIntel86;
    enableIntelX86Extensions = isIntel86;
  };
}
