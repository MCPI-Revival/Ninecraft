{
  ancmp,
  bash,
  cmake,
  copyDesktopItems,
  glad,
  lib,
  makeNinecraftDesktopItems,
  pkg-config,
  python312Packages,
  SDL2,
  stb,
  stdenv,
  unzip,
  wrapGAppsHook,
  zenity,
  zlib,
  mcpeVersions,
  ninecraft-extract ? ../../tools/extract.sh,
}:
stdenv.mkDerivation rec {
  pname = "ninecraft";
  version = "1.2.0";
  # dontUnpack = true;
  src = ../..;
  nativeBuildInputs = [
    cmake
    pkg-config
    wrapGAppsHook
    copyDesktopItems
  ];
  buildInputs = [
    python312Packages.jinja2
    zlib
    SDL2
  ];
  patches = [./use-system-dependancies.patch];
  dontWrapGApps = true;
  prePhases = "submoduleFetchPhase";
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

  installPhase = ''
    runHook preInstall
    mkdir -p $out/bin
    install ninecraft/ninecraft $out/bin/${pname}
    runHook postInstall
  '';

  postFixup = ''
    wrapProgram "$out/bin/${pname}" --set PATH ${lib.makeBinPath [zenity]}
    makeWrapper ${ninecraft-extract} "$out/bin/${pname}-extract" --set PATH ${lib.makeBinPath [bash unzip]}
  '';

  desktopItems = makeNinecraftDesktopItems {
    version = mcpeVersions.a0_6_1;
  };

  meta = import ./meta.nix {inherit lib;};
}
