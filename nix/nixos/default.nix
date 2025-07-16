{
  config,
  lib,
  pkgs,
  ...
}: let
  cfg = config.programs.ninecraft;
  ninecraftpkgs = import ../pkgs {};
in {
  options.programs.ninecraft = let
    types = lib.types;
  in {
    enable = lib.mkEnableOption "Install Ninecraft";
    openFirewall = lib.mkEnableOption "Open Ninecraft ports";
    package = lib.mkOption {
      type = types.package;
      default = with ninecraftpkgs; ninecraft;
    };
  };

  config = lib.mkIf cfg.enable {
    nixpkgs.overlays = [
      (new: old: import ../. {pkgs = new;})
    ];
    environment.systemPackages = with pkgs; [
      cfg.package
    ];

    networking.firewall = lib.mkIf cfg.openFirewall {
      enable = lib.mkDefault true;
      #allowedTCPPorts = [19132];
      allowedUDPPorts = [19132];
    };
  };
}
