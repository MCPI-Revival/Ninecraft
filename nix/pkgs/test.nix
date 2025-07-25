{
  buildNinecraftInstance,
  buildNinecraftMod,
  mcpeVersions,
  writeTextDir,
}:
buildNinecraftInstance {
  name = "test";
  # version = mcpeVersions.a0_7_0;
  options.mp_username = "bobface";
  # homeDir = "home-dir";
  useNixGL = false;
  mods = [
    (buildNinecraftMod {
      name = "hello";
      src =
        writeTextDir "main.cpp"
        ''
          #include <iostream>

          extern "C" {
          void ninecraft_mod_on_load(void* m, int v) {
            printf("Hi, hm m\n");
          }
          }
        '';
    })
  ];
}
