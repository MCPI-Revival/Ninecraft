{
  config,
  lib,
  pkgs,
  ...
}: let
  cfg = config.programs.ninecraft;
in {
  options.programs.ninecraft = let
    types = lib.types;
  in {
    enable = lib.mkEnableOption "Install Ninecraft";
    openFirewall = lib.mkEnableOption "Open Ninecraft ports";
    package = lib.mkOption {
      type = types.package;
      default = with import ../pkgs {}; ninecraft;
    };
  };

  config = lib.mkIf cfg.enable {
    environment.systemPackages = with pkgs; [
      (symlinkJoin
        {
          name = "ninecraft-game";
          paths = [
            (makeDesktopItem {
              desktopName = "Ninecraft";
              name = "ninecraft";
              icon = "applications-games";
              exec = "ninecraft";
            })
            cfg.package
          ];
        })
    ];

    networking.firewall = lib.mkIf cfg.openFirewall {
      enable = lib.mkDefault true;
      #allowedTCPPorts = [19132];
      allowedUDPPorts = [19132];
    };
  };
}
