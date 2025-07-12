{
  lib,
  ninecraft,
  stdenvNoCC,
  writeShellScript,
  writeText,
  defaultVersion,
  internal_overrides,
}: {
  name ? "ninecraft",
  homeDir ? "$(mktemp -d)",
  gameDir ? "$out/share/ninecraft",
  mods ? [],
  options ? null,
  package ? ninecraft,
  version ? defaultVersion,
  internal_overrides ? internal_overrides,
}: let
  optionsTxt = writeText "options.txt" (with builtins; let
    opt =
      {
        "mp_username" = "Steve";
        "mp_server" = "Steve";
        "mp_server_visible_default" = true;
        "gfx_fancygraphics" = true;
        "gfx_lowquality" = false;
        "ctrl_sensitivity" = .5;
        "ctrl_invertmouse" = false;
        "ctrl_islefthanded" = false;
        "ctrl_usetouchscreen" = false;
        "ctrl_usetouchjoypad" = false;
        "feedback_vibration" = false;
        "game_difficulty" = 4;
      }
      // options;
  in
    concatStringsSep "\n" (map (
        k: let
          v = opt.${k};
          stringFromType = {
            bool =
              if v
              then "true"
              else "false";
            string = v;
          };
        in "${k}:${stringFromType.${typeOf v} or (toString v)}"
      ) (attrNames (
        if (isAttrs options)
        then opt
        else {}
      ))));
  startScript = writeShellScript "start-ninecraft-instance.sh" ''
    out=$(dirname $0)/..
    NINECRAFT_HOME=${homeDir}
    if [[ ! -d $NINECRAFT_HOME ]]; then
      mkdir -p $NINECRAFT_HOME
    fi
    ${
      if (builtins.isAttrs options)
      then ''
        if [[ ! -f $NINECRAFT_HOME/options.txt ]]; then
          ln -s ${optionsTxt} $NINECRAFT_HOME/options.txt
        fi

        if [[ ! -d $NINECRAFT_HOME/storage/games/com.mojang/minecraftpe ]]; then
          mkdir -p $NINECRAFT_HOME/storage/games/com.mojang/minecraftpe
        fi
        if [[ ! -f $NINECRAFT_HOME/storage/games/com.mojang/minecraftpe/options.txt ]]; then
          ln -s ${optionsTxt} $NINECRAFT_HOME/storage/games/com.mojang/minecraftpe/options.txt
        fi
      ''
      else ""
    }

    # INSTALL MODS
    if [[ ! -d $NINECRAFT_HOME/mods ]]; then
      mkdir -p $NINECRAFT_HOME/mods
    fi
    ${lib.concatMapStrings
      (mod: ''
        if [[ ! -f $(basename ${mod}/mods/*.so) ]]; then
          cp -f ${mod}/mods/*.so $NINECRAFT_HOME/mods
        fi
      '')
      mods}

    "$(dirname $0)/.ninecraft" --game ${gameDir} --home "$NINECRAFT_HOME" "$@"
  '';
in
  package.overrideAttrs (old: {
    pname = name;
    postFixup =
      (old.postFixup or "")
      + ''
        mv $out/bin/ninecraft $out/bin/.ninecraft
        ln -s ${startScript} $out/bin/${name}
        if [ ! -d ${gameDir} ]; then
          mkdir ${gameDir}
        fi
        if [ ! -d ${gameDir}/internal_overrides ]; then
          ln -s internal_overrides ${gameDir}/internal_overrides
        fi
        if [ ! -d ${gameDir}/assets ]; then
          ln -s ${version}/assets ${gameDir}/assets
        fi
        if [ ! -d ${gameDir}/lib ]; then
          ln -s ${version}/lib ${gameDir}/lib
        fi
      '';
  })
