{stdenv,
pkg-config,
cmake,
xorg,
python312,
python312Packages,
openal,
glfw,
zlib
}:
stdenv.mkDerivation {
  name = "ninecraft";
  version = "1.2.0_56b9f26";
  src = ../..;
  nativeBuildInputs = [
    pkg-config
    cmake
  ];
  patches = [./use-system-dependancies.patch];
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
  cp -r ninecraft/ninecraft $out/bin
  cp -r $src/internal_overrides $out/var/lib/ninecraft
  '';
}