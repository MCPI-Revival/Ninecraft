{
  commits ? import ../commits.nix,
  flakeLock ? builtins.fromJSON (builtins.readFile ../../flake.lock),
  getHash ? name: flakeLock.nodes.${name}.locked.narHash,
  getRev ? name: flakeLock.nodes.${name}.locked.rev,
  nixgl ? (pkgs.fetchFromGitHub {
    owner = "nix-community";
    repo = "nixGL";
    rev = getRev "nixgl";
    hash = getHash "nixgl";
  }),
  pkgs ? (import <nixpkgs> {
    config.allowUnfree = true;
    overlays = [
      (new: old: let
        isIntel86 = new.system == "x86_64-linux";
      in {
        nixgl = import nixgl {
          pkgs = new;
          enable32bits = isIntel86;
          enableIntelX86Extensions = isIntel86;
        };
      })
    ];
  }),
  internal_overrides ? ../../internal_overrides,
  glad ? (pkgs.fetchFromGitHub rec {
    name = "glad";
    owner = "Dav1dde";
    repo = name;
    rev = getRev name;
    hash =
      getHash name;
  }),
  ancmp ? (pkgs.fetchFromGitHub rec {
    name = "ancmp";
    owner = "MFDGaming";
    repo = name;
    rev = getRev name;
    hash =
      getHash name;
  }),
  stb ? (pkgs.fetchFromGitHub rec {
    name = "stb";
    owner = "nothings";
    repo = name;
    rev = getRev name;
    hash = getHash name;
  }),
}: rec {
  extract = pkgs.callPackage ./extract.nix {};
  ninecraft = pkgs.pkgsi686Linux.callPackage ./ninecraft.nix {
    ninecraft-extract = extract;
    inherit internal_overrides;
    inherit glad ancmp stb;
  };
  ninecraft-nixgl = pkgs.callPackage ./ninecraft-nixgl.nix {
    inherit ninecraft;
  };
}
