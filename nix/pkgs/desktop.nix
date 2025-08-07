{
  makeDesktopItem,
  lib,
  ninecraft-extract,
  mcpeVersions,
  ...
}: {
  instance ? null,
  version ? mcpeVersions.a0_6_1,
  gameDir ? "~/.local/share/ninecraft",
  homeDir ? "~/.local/share/ninecraft",
}: let
  meta = import ./meta.nix {inherit lib;};
  desktopName = "Ninecraft ${lib.optionalString (instance != null) "(${instance})"}";
  name = "ninecraft${lib.optionalString (instance != null) "-${instance}"}";
in [
  (
    makeDesktopItem {
      inherit name desktopName;
      genericName = "MCPE Alpha Player";
      comment = meta.longDescription;
      icon = "${version}/res/drawable/iconx.png";
      exec = "ninecraft${
        if (instance == null)
        then " --game \"${gameDir}\" --home \"${homeDir}\""
        else "-${instance}"
      }";
      categories = ["Game" "AdventureGame"];
      keywords = ["mcpe" "android" "mcpi" "pocket" "edition"];
    }
  )

  (makeDesktopItem {
    desktopName = "Change ${desktopName} Version";
    name = "${name}-install";
    icon =
      if (version == null)
      then "application-game"
      else "${version}/res/drawable/iconx.png";
    path = gameDir;
    exec = "${ninecraft-extract} %u";
    categories = ["Game"];
    terminal = true;
    mimeTypes = ["application/vnd.android.package-archive"];
  })
]
