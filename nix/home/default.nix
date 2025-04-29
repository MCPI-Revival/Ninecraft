{
  pkgs,
  config,
  lib,
  ...
}: let
  cfg = config.programs.ninecraft;
  fetchapk = pkgs.callPackage ../pkgs/fetchapk.nix {};
  versions = pkgs.callPackage ../pkgs/versions.nix {inherit fetchapk;};
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
      default = versions."PE-a${builtins.replaceStrings ["." "_"] ["_" "_"] cfg.version}_x86";
    };
    options = lib.mkOption {
      type = types.attrsOf (types.oneOf [types.int types.bool types.str]);
    };
    mods = lib.mkOption {
      type = types.listOf types.package;
      default = [];
    };
  };

  config = lib.mkIf cfg.enable {
    home.packages = with pkgs; [
      (symlinkJoin
        {
          name = "ninecraft-game";
          paths = [
            (makeDesktopItem {
              desktopName = "Ninecraft";
              name = "ninecraft";
              icon = "applications-games";
              exec = "ninecraft";
              path = "$XDG_DATA_HOME/ninecraft";
            })
            cfg.package
          ];
        })
    ];

    programs.ninecraft.options."mp_username" = lib.mkDefault "Steve";
    programs.ninecraft.options."mp_server" = lib.mkDefault "Steve";
    programs.ninecraft.options."mp_server_visible_default" = lib.mkDefault true;
    programs.ninecraft.options."gfx_fancygraphics" = lib.mkDefault true;
    programs.ninecraft.options."gfx_lowquality" = lib.mkDefault false;
    programs.ninecraft.options."ctrl_sensitivity" = lib.mkDefault0 .5;
    programs.ninecraft.options."ctrl_invertmouse" = lib.mkDefault false;
    programs.ninecraft.options."ctrl_islefthanded" = lib.mkDefault false;
    programs.ninecraft.options."ctrl_usetouchscreen" = lib.mkDefault false;
    programs.ninecraft.options."ctrl_usetouchjoypad" = lib.mkDefault false;
    programs.ninecraft.options."feedback_vibration" = lib.mkDefault false;
    programs.ninecraft.options."game_difficulty" = lib.mkDefault 4;

    xdg.dataFile = {
      "ninecraft-options" = let
        createContents = with builtins;
          options:
            concatStringsSep "\n" (map (
              k: let
                v = options.${k};
                stringFromType = {
                  bool =
                    if v
                    then "true"
                    else "false";
                  int = toString v;
                  string = v;
                };
              in "${k}:${stringFromType.${typeOf v}}"
            ) (attrNames options));
      in {
        enable = true;
        force = true;
        text = createContents cfg.options;
        target = "ninecraft/options.txt";
      };

      "assets" = {
        target = "ninecraft/assets";
        recursive = true;
        force = true;
        source = cfg.apk + "/assets";
      };
      "lib" = {
        target = "ninecraft/lib";
        recursive = true;
        force = true;
        source = cfg.apk + "/lib";
      };
      "res" = {
        target = "ninecraft/res";
        recursive = true;
        force = true;
        source = cfg.apk + "/res";
      };
      "internal_overrides" = {
        target = "ninecraft/internal_overrides";
        recursive = true;
        force = true;
        source = ../../internal_overrides;
      };
    };
  };
}
