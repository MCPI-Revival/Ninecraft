{
  buildNinecraftInstance,
  buildNinecraftModNDK,
  versions,
  writeTextDir,
}:
buildNinecraftInstance {
  name = "test";
  version = versions.PE-a0_8_0_x86;
  options.mp_username = "bobface";
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
