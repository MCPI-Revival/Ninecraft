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
  lib
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

   meta = with lib; {
    mainProgram = "ninecraft";
    description = "A mcpe 0.1.0-0.10.5 launcher for linux and windows ";
    homepage = "https://github.com/MCPI-Revival/Ninecraft";
    changelog = "https://github.com/MCPI-Revival/Ninecraft/-/blob/${finalAttrs.version}/NEWS?ref_type=tags";
    license = licenses.mit;
    platforms = platforms.unix;
    maintainers = "MCPI-Revival";
  };
}
