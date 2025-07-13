{
  lib,
  ninecraft,
  stdenvNoCC,
  writeShellScript,
  writeText,
  writeScript,
  defaultVersion,
  ninecraft-desktop-entry,
  makeDesktopItem,
}: {
  name ? "ninecraft",
  homeDir ? "$(mktemp -d)",
  gameDir ? null,
  mods ? [],
  options ? null,
  package ? ninecraft,
  version ? defaultVersion,
  global_overrides ? [],
}: let
  ninecraft-extract = ../../tools/extract.sh;
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
    homeDir=${homeDir}
    ${
      if (isNull gameDir)
      then ""
      else ''
        gameDir=${gameDir}

        # Version
        if [ ! -d $gameDir ]; then
          mkdir -p $gameDir
        fi
        cp -sru ${version}/{assets,lib} $gameDir
      ''
    }
    ${
      if (builtins.isAttrs options)
      then ''
        # Options
        if [[ ! -d $homeDir/storage/games/com.mojang/minecraftpe ]]; then
          mkdir -p $homeDir/storage/games/com.mojang/minecraftpe
        fi
        cp -su ${optionsTxt} $homeDir/options.txt
        cp -su ${optionsTxt} $homeDir/storage/games/com.mojang/minecraftpe/options.txt
      ''
      else ""
    }
    # Mods
    ${lib.concatMapStrings (mod: "cp -rf ${mod}/* $homeDir") mods}

    "$(dirname $0)/.ninecraft" --game "${lib.defaultTo "$gameDir" version}" --home "$homeDir" "$@"
  '';
in
  package.overrideAttrs (old: {
    pname = name;
    postFixup =
      (old.postFixup or "")
      + ''
        mv $out/bin/ninecraft $out/bin/.ninecraft
        ln -s ${startScript} $out/bin/${name}
      '';

    desktopItems = [
      (
        ninecraft-desktop-entry {
          icon = "${version}/res/drawable/iconx.png";
        }
      )
      (
        makeDesktopItem {
          desktopName = "Change Ninecraft Version";
          name = "ninecraft-install";
          icon = "${version}/res/drawable/iconx.png";
          path = gameDir;
          exec = "${ninecraft-extract} %u";
          categories = ["Game"];
          terminal = true;
          mimeTypes = ["application/vnd.android.package-archive"];
        }
      )
    ];
  })
