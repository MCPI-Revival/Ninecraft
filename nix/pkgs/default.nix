{
  lib ? import ../lib.nix {inherit pkgs;},
  pkgs ? (import <nixpkgs> {
    config = {
      allowUnfree = true;
      android_sdk.accept_license = true;
    };
    overlays = [
      (new: old: let
        isIntel86 = new.system == "x86_64-linux";
      in {
        inherit (lib) nixgl;
      })
    ];
  }),
  glad ? (pkgs.fetchFromGitHub rec {
    name = "glad";
    owner = "Dav1dde";
    repo = name;
    rev = "56e406e90a802e963bb18d9c94cf6589e5a6b0a9";
    hash = lib.getHash name;
  }),
  ancmp ? (pkgs.fetchFromGitHub rec {
    name = "ancmp";
    owner = "MFDGaming";
    repo = name;
    rev = "main";
    hash = lib.getHash name;
  }),
  stb ? (pkgs.fetchFromGitHub rec {
    name = "stb";
    owner = "nothings";
    repo = name;
    rev = "5736b15f7ea0ffb08dd38af21067c314d6a3aae9";
    hash = lib.getHash name;
  }),
  ninecraft-mod-toolchain-build-scripts ? (pkgs.fetchFromGitHub rec {
    name = "ninecraft-mod-toolchain-build-scripts";
    owner = "MCPI-Revival";
    repo = name;
    rev = "main";
    hash = lib.getHash name;
  }),
  flakeRoot ? ../..,
  ninecraft-extract ? ../../tools/extract.sh,
}: rec {
  fetchApk = pkgs.callPackage ./fetchApk.nix {};
  mcpeVersions =
    pkgs.callPackage ./versions.nix {inherit fetchApk;};

  makeNinecraftDesktopItems = pkgs.callPackage ./desktop.nix {
    inherit ninecraft-extract mcpeVersions;
  };
  ninecraft = pkgs.pkgsi686Linux.callPackage ./ninecraft.nix {
    inherit glad stb ancmp ninecraft-extract makeNinecraftDesktopItems mcpeVersions;
  };

  buildNinecraftInstance = pkgs.callPackage ./buildNinecraftInstance.nix {
    inherit ninecraft ninecraft-extract mcpeVersions makeNinecraftDesktopItems;
    inherit (lib) nixgl;
  };
  buildNinecraftMod = pkgs.callPackage ./buildNinecraftMod.nix {inherit ninecraft-mod-toolchain-build-scripts;};
  buildNinecraftModNDK = pkgs.callPackage ./buildNinecraftMod.nix {
    inherit ninecraft-mod-toolchain-build-scripts;
    defaultUseNDK = true;
  };

  ninecraft-nixgl = buildNinecraftInstance {
    version = mcpeVersions.a0_6_1;
    useNixGL = true;
  };
  # test = pkgs.callPackage ./test.nix {
  #   inherit
  #     buildNinecraftInstance
  #     mcpeVersions
  #     buildNinecraftMod
  #     ;
  # };
}
