# compilation shell
with (import <nixpkgs> {}).pkgsi686Linux;
  mkShell {
    packages = [
      gnumake
      pkg-config
      cmake
      libgcc
      python312Packages.jinja2
      zlib
      SDL2

      # packaging
      dpkg
    ];
  }
