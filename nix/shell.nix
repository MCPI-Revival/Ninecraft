# compilation shell
with import <nixpkgs> {};
  mkShell {
    nativeBuildInputs = [
      pkg-config
      cmake
    ];
    buildInputs = [
      python312Packages.jinja2
      zlib
      SDL2
    ];
    packages = [
      make
    ];
  }
