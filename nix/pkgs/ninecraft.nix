{
  stdenv,
  pkg-config,
  cmake,
  xorg,
  python312,
  python312Packages,
  openal,
  glfw,
  zlib,
  lib,
  writeScript,
  curl,
  ninecraft-extract,
}: let
  ninecraft-unpatched = stdenv.mkDerivation {
    name = "ninecraft-unpatched";
    version = "1.2.0_56b9f26";
    src = ../..;
    nativeBuildInputs = [
      pkg-config
      cmake
    ];
    buildInputs = [
      xorg.libX11
      xorg.libXrandr
      xorg.libXinerama
      xorg.libXcursor
      xorg.libXi
      python312
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
  ninecraft = ninecraft-unpatched.overrideAttrs {
    patches = [./use-system-dependancies.patch];
  };
  entryScript = ninecraft:
    writeScript "ninecraft" ''
      export NINECRAFT_DATA=''${XDG_DATA_HOME:-$HOME/.local/share}/ninecraft
      if [[ ! -d "$NINECRAFT_DATA" ]]; then
      echo "Setting up data folder at: $NINECRAFT_DATA"
        mkdir -p "$NINECRAFT_DATA"
      fi

      cd $NINECRAFT_DATA

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
        ${curl}/bin/curl -L --output mcpe.apk "$URL"

        echo "Extracting APK..."
        ${ninecraft-extract}/bin/ninecraft-extract mcpe.apk

      fi
      pwd
      ls
      echo "Starting Ninecraft..."
      ${ninecraft}/bin/ninecraft
    '';
in
  stdenv.mkDerivation {
    name = "ninecraft";
    version = "1.2.0_56b9f26";
    phases = ["buildPhase"];
    buildPhase = ''
      mkdir -p $out/bin
      cp ${entryScript ninecraft} $out/bin/ninecraft
      cp ${ninecraft}/bin/ninecraft $out/bin/ninecraft-unwrapped
      cp ${ninecraft-unpatched}/bin/ninecraft $out/bin/ninecraft-unpatched
      cp ${entryScript ninecraft} $out/bin/ninecraft-wrapped-unpatched
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
