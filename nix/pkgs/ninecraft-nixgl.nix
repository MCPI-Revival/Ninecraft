{
  ninecraft,
  nixgl,
  lib,
  symlinkJoin,
  makeWrapper,
  writeScriptBin,
}: let
  name = "ninecraft-nixgl";
  script = writeScriptBin name ''
    nixGL ninecraft "$@"
  '';
in
  symlinkJoin {
    inherit name;
    paths = [script ninecraft nixgl.auto.nixGLDefault];
    buildInputs = [makeWrapper];
    postBuild = "wrapProgram $out/bin/${name} --prefix PATH : $out/bin";
  }
