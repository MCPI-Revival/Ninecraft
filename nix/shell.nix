{
  mkShell,
  ninecraft,
  ninecraft-extract,
  ninecraft-nixgl,
}:
mkShell {
  packages = [
    ninecraft
    ninecraft-extract
    ninecraft-nixgl
  ];
}
