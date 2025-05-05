{
  pkgs,
  config,
  lib,
  ...
}: let
  cfg = config.programs.ninecraft;
in {
  options.programs.ninecraft = let
    types = lib.types;
  in {
    enable = lib.mkEnableOption "Install Ninecraft";
    version = lib.mkOption {
      type = types.str;
      default = "0.6.0";
    };
    package = lib.mkOption {
      type = types.package;
      default = with import ../pkgs {}; ninecraft;
    };
    apk = lib.mkOption {
      type = types.nullOr (types.package);
    };
    options = lib.mkOption {
      type = types.attrsOf (types.oneOf [types.int types.bool types.str]);
      default = {
        "mp_username" = "Steve";
        "mp_server" = "Steve";
        "mp_server_visible_default" = true;
        "gfx_fancygraphics" = true;
        "gfx_lowquality" = false;
        "ctrl_sensitivity" = 0.5;
        "ctrl_invertmouse" = false;
        "ctrl_islefthanded" = false;
        "ctrl_usetouchscreen" = false;
        "ctrl_usetouchjoypad" = false;
        "feedback_vibration" = false;
        "game_difficulty" = 4;
      };
    };
    mods = lib.mkOption {
      type = types.listOf types.package;
      default = [];
    };
  };
}
