{
  pkgs,
  config,
  lib,
  ...
}: let
  cfg = config.programs.ninecraft;
  types = lib.types;
  ncPkgs = import ../pkgs {inherit pkgs;};
  mkOptDef = default: lib.mkOption {inherit default;};
  mkOptType = type: lib.mkOption {inherit type;};
  mkOptNamed = options:
    lib.mkOption {
      default = {};
      type = with types; attrsOf (submodule [{inherit options;}]);
    };
in {
  options.programs.ninecraft = {
    enable = lib.mkEnableOption "Install Ninecraft";
    package = lib.mkOption {
      type = types.package;
      default = pkgs.ninecraft;
    };
    instances = mkOptNamed {
      version = lib.mkOption {
        type = types.str;
        default = "0.6.1";
      };

      options = lib.mkOption {
        default = null;
        type =
          types.nullOr (types.attrsOf (types.oneOf [types.int types.bool types.str]));
      };
      apk = lib.mkOption {
        type = types.nullOr (types.package);
        default = ncPkgs.mcpeVersions.a0_6_1;
      };
      mods = lib.mkOption {
        type = types.listOf types.package;
        default = [];
      };
    };
  };

  config = lib.mkIf cfg.enable {
    # nixpkgs.overlays = [
    #   (final: prev: import ../pkgs {pkgs = prev;})
    # ];
    home.packages = builtins.map (
      name: let
        inCfg = cfg.instances.${name};
        version = inCfg.apk or ncPkgs.mcpeVersions."a${lib.replaceStrings ["."] ["_"] cfg.version}";
      in
        ncPkgs.buildNinecraftInstance (inCfg
          // {
            inherit name version;
            homeDir = "~/.local/share/ninecraft/instances/${name}";
          })
    ) (builtins.attrNames cfg.instances);
  };
}
