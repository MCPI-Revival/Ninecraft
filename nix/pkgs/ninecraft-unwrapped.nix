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
  glad,
  ancmp,
  stb,
  ...
}:
stdenv.mkDerivation {
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
  ];

  patches = [./use-system-dependancies.patch];
  buildInputs = [
    openal
    python312Packages.jinja2
    glfw
    zlib
  ];
  installPhase = ''
     mkdir -p $out/bin
    cp -r ninecraft/ninecraft $out/bin/ninecraft
  '';
  postFixup = ''
    wrapProgram $out/bin/ninecraft --set PATH ${lib.makeBinPath [
      zenity
    ]}
  '';
}
