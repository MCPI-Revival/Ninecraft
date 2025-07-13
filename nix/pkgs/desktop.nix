{
  makeDesktopItem,
  icon ? "applications-games",
  homeDir ? "~/.local/share/ninecraft",
  gameDir ? "~/.local/share/ninecraft",
  ...
}:
makeDesktopItem {
  desktopName = "Ninecraft";
  name = "ninecraft";
  GenericName = "MCPE Alpha Player";
  Comment = "A mcpe 0.1 .0 - 0.10 .5 launcher for linux and windows"
  inherit icon;
  exec = "ninecraft --home \"${homeDir}\" --game \"${gameDir}\"";
  categories = ["Game" "AdventureGame"];
  Keywords = ["mcpe""android""mcpi""pocket""edition"];
}
