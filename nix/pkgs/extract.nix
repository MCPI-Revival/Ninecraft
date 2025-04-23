{
  writeScriptBin,...
}:
writeScriptBin "ninecraft-extract" 
(builtins.readFile ../../tools/extract.sh)