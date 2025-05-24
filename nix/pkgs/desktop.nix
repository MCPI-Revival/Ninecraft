{
  makeDesktopItem,
  icon ? "applications-games",
  ...
}:
makeDesktopItem {
  desktopName = "Ninecraft";
  name = "ninecraft";
  inherit icon;
  exec = "ninecraft";
  categories = [
    "Game"
  ];
}
