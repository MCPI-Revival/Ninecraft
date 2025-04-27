{
  mkShell,
  ninecraft,
  ninecraft-extract,
  ninecraft-nixgl,
}:
pkgs.mkShell {
  packages = [
    ninecraft
    ninecraft-extract
    ninecraft-nixgl
  ];
}
