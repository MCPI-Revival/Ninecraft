{writeShellScriptBin,curl,ninecraft,ninecraft-extract}:
writeShellScriptBin "ninecraft-demo" ''
   export NINECRAFT_DATA=''${XDG_DATA_HOME:-$HOME/.local/share}/ninecraft
    if [[ ! -d "$NINECRAFT_DATA" ]]; then
    echo "Setting up data folder at: $NINECRAFT_DATA"
      mkdir -p "$NINECRAFT_DATA"
    fi

    cd $NINECRAFT_DATA
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
    ${ninecraft}/bin/ninecraft --game $NINECRAFT_DATA --home $NINECRAFT_DATA
    ''