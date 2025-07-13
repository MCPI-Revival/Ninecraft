{
  commits ? import ../commits.nix,
  flakeLock ? builtins.fromJSON (builtins.readFile ../../flake.lock),
  getHash ? name: flakeLock.nodes.${name}.locked.narHash,
  nixgl ? (pkgs.fetchFromGitHub {
    owner = "nix-community";
    repo = "nixGL";
    rev = "main";
    hash = getHash "nixgl";
  }),
  pkgs ? (import <nixpkgs> {
    config = {
      allowUnfree = true;
      android_sdk.accept_license = true;
    };
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
  glad ? (pkgs.fetchFromGitHub {
    owner = "Dav1dde";
    repo = "glad";
    rev = "56e406e90a802e963bb18d9c94cf6589e5a6b0a9";
    hash = getHash "glad";
  }),
  ancmp ? (pkgs.fetchFromGitHub {
    owner = "MFDGaming";
    repo = "ancmp";
    rev = "main";
    hash = getHash "ancmp";
  }),
  stb ? (pkgs.fetchFromGitHub {
    owner = "nothings";
    repo = "stb";
    rev = "5736b15f7ea0ffb08dd38af21067c314d6a3aae9";
    hash = getHash "stb";
  }),
  ninecraft-desktop-entry ? (pkgs.callPackage ./desktop.nix {}),
}: rec {
  fetchApk = pkgs.callPackage ./fetchApk.nix {};
  versions = pkgs.callPackage ./versions.nix {inherit fetchApk;};
  buildNinecraftInstance = pkgs.pkgsi686Linux.callPackage ./buildNinecraftInstance.nix {
    inherit internal_overrides glad stb ninecraft-desktop-entry ancmp;
    defaultVersion = versions.a0_6_1;
  };
  buildNinecraftModNDK = pkgs.callPackage ./buildNinecraftModNDK.nix {};
  ninecraft = pkgs.callPackage ./ninecraftNew.nix {inherit buildNinecraftInstance versions buildNinecraftModNDK;};
  ninecraft-nixgl = pkgs.callPackage ./ninecraft-nixgl.nix {
    inherit ninecraft;
  };
  test = pkgs.callPackage ./test.nix {inherit buildNinecraftInstance versions buildNinecraftModNDK;};
}
