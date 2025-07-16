{
  buildNinecraftInstance,
  buildNinecraftModNDK,
  mcpeVersions,
  writeTextDir,
}:
buildNinecraftInstance {
  name = "test";
  version = mcpeVersions.a0_7_0;
  options.mp_username = "bobface";
  homeDir = "home-dir";
  useNixGL = true;
  mods = [
    (buildNinecraftModNDK {
      name = "hello";
      src =
        writeTextDir "main.c"
        ''
          #include <stdio.h>
          void ninecraft_mod_on_load(void* m, int v) {
            printf("Hi, hmm\n");
          }
        '';
    })
  ];
}
