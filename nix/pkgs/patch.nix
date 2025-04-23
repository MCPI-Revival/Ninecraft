{
  writeShellApplication,
  patchelf
}:
writeShellApplication {
  name = "ninecraft-patch";

  runtimeInputs = [  patchelf ];
  text = builtins.readFile ../../tools/patch.sh;
}