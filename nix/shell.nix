{
  mkShell,
  ninecraft,
  ninecraft-extract,
  ...
}:
mkShell {
  packages = [
    ninecraft
    ninecraft-extract
  ];
}
