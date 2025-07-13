{
  symlinkJoin,
  unzip,
  makeWrapper,
  writeScriptBin,
  ...
}: let
  name = "ninecraft-extract";
  script = writeScript name (builtins.readFile ../../tools/extract.sh);
in
  symlinkJoin {
    inherit name;
    paths = [unzip script];
    buildInputs = [makeWrapper];
    postFixup = ''
      wrapProgram $out/bin/${name} --prefix PATH : $out/bin
    '';
  }
