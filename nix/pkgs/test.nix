{
  buildNinecraftInstance,
  buildNinecraftModNDK,
  versions,
  writeTextDir,
}:
buildNinecraftInstance {
  version = versions.a0_8_0;
  options.mp_username = "bobface";
  homeDir = "home-dir";
  gameDir = "game-dir";
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
