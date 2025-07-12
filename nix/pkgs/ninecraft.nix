{
  stdenv,
  pkg-config,
  cmake,
  python312Packages,
  zlib,
  lib,
  writeShellApplication,
  writeScript,
  curl,
  zenity,
  wrapGAppsHook,
  internal_overrides,
  glad,
  ancmp,
  stb,
  tree,
  makeWrapper,
  ninecraft-desktop-entry,
  symlinkJoin,
  SDL2,
  copyDesktopItems,
  bash,
  unzip,
  ...
}: let
  ninecraft-extract = ../../tools/extract.sh;
  ninecraft = stdenv.mkDerivation {
    pname = "ninecraft";
    version = "1.2.0";
    src = ../..;
    prePhases = ["submoduleFetchPhase"];
    submoduleFetchPhase = ''
         export glad=$PWD/deps_src/glad
         export ancmp=$PWD/deps_src/ancmp
         export stb=$PWD/deps_src/stb
      mkdir -p deps_src
      cp --no-preserve=mode,ownership -r ${glad} $glad
      cp --no-preserve=mode,ownership -r ${ancmp} $ancmp
      cp --no-preserve=mode,ownership -r ${stb} $stb

         	 ls -al deps_src
    '';
    nativeBuildInputs = [
      pkg-config
      cmake

      wrapGAppsHook
      copyDesktopItems
    ];

    patches = [./use-system-dependancies.patch];
    buildInputs = [
      python312Packages.jinja2
      zlib
      SDL2
    ];
    installPhase = ''
      runHook preInstall
      mkdir -p $out/{bin,share/ninecraft}
      cp ninecraft/ninecraft $out/bin/ninecraft
      ln -s ${internal_overrides} $out/share/ninecraft/internal_overrides
      runHook postInstall

    '';
    postFixup = ''
      wrapProgram $out/bin/ninecraft --set PATH ${lib.makeBinPath [
        zenity
      ]}
      makeWrapper ${ninecraft-extract} $out/bin/ninecraft-extract --set PATH ${lib.makeBinPath [
        bash
        unzip
      ]}
    '';

    dontWrapGApps = true;
    desktopItems = [ninecraft-desktop-entry];
  };
  ninecraft-script = writeShellApplication {
    name = "ninecraft";

    runtimeInputs = [curl ninecraft];
    text = ''
      set +u
        export NINECRAFT_DATA=''${XDG_DATA_HOME:-$HOME/.local/share}/ninecraft
        if [[ ! -d "$NINECRAFT_DATA" ]]; then
        echo "Setting up data folder at: $NINECRAFT_DATA"
          mkdir -p "$NINECRAFT_DATA"
        fi

        cd "$NINECRAFT_DATA"

        if [[ ! -d "internal_overrides" ]]; then
          echo "copying internal_overrides..."
          cp -r ${internal_overrides} .
        fi

        export VERSION=$1
        export ARCH=$2

        if [[ -z "$VERSION" ]]; then
          if [[ ! -d "lib" ]]; then
            VERSION=0.5.0
          fi
        fi

        if [[ -n "$VERSION" ]]; then
          if [[ -e "mcpe.apk" ]]; then
            rm mcpe.apk
          fi
          rm -rf assets res lib
          export URL="https://archive.org/download/MCPEAlpha/PE-a''${VERSION}-''${ARCH:-x86}.apk"
          echo "Downloading Minecraft PE $VERSION from $URL..."
          curl -L --output mcpe.apk "$URL"

          echo "Extracting APK..."
          ${ninecraft-extract} mcpe.apk
          cp res/drawable/iconx.png  "''${XDG_DATA_HOME:-$HOME/.local/share}/icons/ninecraft.png"

        fi
        pwd
        ls
        echo "Starting Ninecraft..."
        ninecraft
    '';
  };
in
  ninecraft
