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
  inherit icon;
  exec = "ninecraft --home \"${homeDir}\" --game \"${gameDir}\"";
  categories = ["Game" "AdventureGame"];
}
