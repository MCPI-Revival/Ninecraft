{
  stdenv,
  pkg-config,
  cmake,
  python312Packages,
  openal,
  glfw,
  zlib,
  lib,
  writeShellApplication,
  curl,
  zenity,
  ninecraft-extract,
  wrapGAppsHook,
  unzip,
  nixgl,
}: let
  ninecraft = stdenv.mkDerivation {
    name = "ninecraft";
    version = "1.2.0_56b9f26";
    src = ../..;
    nativeBuildInputs = [
      pkg-config
      cmake

      wrapGAppsHook
    ];
    patches = [./use-system-dependancies.patch];
    buildInputs = [
      openal
      python312Packages.jinja2
      glfw
      zlib
    ];
    installPhase = ''
      mkdir -p $out/{bin,var/lib/ninecraft}
      cp -r ninecraft/ninecraft $out/bin/ninecraft
      cp -r $src/internal_overrides $out/var/lib/ninecraft
    '';
  };
  entryScript = ninecraft:
    writeShellApplication {
      name = "ninecraft-wrapper";

      runtimeInputs = [curl ninecraft ninecraft-extract zenity unzip nixgl.auto.nixGLDefault];
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
            cp -r ${ninecraft}/var/lib/ninecraft/internal_overrides .
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
            ninecraft-extract mcpe.apk

          fi
          pwd
          ls
          echo "Starting Ninecraft..."
          nixGL ninecraft
      '';
    };
in
  stdenv.mkDerivation {
    name = "ninecraft";
    version = "1.2.0_56b9f26";
    src = ./.;
    buildPhase = ''
      mkdir -p $out/bin
      cp ${entryScript ninecraft}/bin/ninecraft-wrapper $out/bin/ninecraft
      cp ${ninecraft}/bin/ninecraft $out/bin/ninecraft-unwrapped
      cp ${ninecraft-extract}/bin/ninecraft-extract $out/bin
    '';

    meta = with lib; {
      mainProgram = "ninecraft";
      description = "A mcpe 0.1.0-0.10.5 launcher for linux and windows ";
      homepage = "https://github.com/MCPI-Revival/Ninecraft";
      changelog = "https://github.com/MCPI-Revival/Ninecraft/-/blob/${finalAttrs.version}/NEWS?ref_type=tags";
      license = licenses.mit;
      platforms = platforms.unix;
      maintainers = ["MCPI-Revival"];
    };
  }
