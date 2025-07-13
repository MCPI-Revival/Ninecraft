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
        if [[ ( ! -d "$gameDir/lib"  ) || ( ! -d "$gameDir/res"  ) || ( ! -d "$gameDir/assets"  ) ]]; then
          cp -rf "${version}"/{assets,lib,res} "$gameDir"
          chmod -R u+rw "$gameDir"/{assets,lib,res}
        fi

      ''
    }
    ${
      if (builtins.isAttrs options)
      then ''
        # Options
        if [[ ! -d $homeDir/storage/games/com.mojang/minecraftpe ]]; then
          mkdir -p $homeDir/storage/games/com.mojang/minecraftpe
        fi
        if [[ -L $homeDir/options.txt ]] || [[ ! -e $homeDir/options.txt ]]; then
          cp -sf ${optionsTxt} $homeDir/options.txt
        fi
        if [[ -L $homeDir/storage/games/com.mojang/minecraftpe/options.txt ]] || [[ ! -e $homeDir/storage/games/com.mojang/minecraftpe/options.txt ]]; then
          cp -sf ${optionsTxt} $homeDir/storage/games/com.mojang/minecraftpe/options.txt
        fi

      ''
      else ""
    }
    # Mods
    ${lib.concatMapStrings (mod: "cp -rf ${mod}/* $homeDir") mods}

    "$(dirname $0)/.ninecraft" --game "${
      if (isNull gameDir)
      then version
      else "$gameDir"
    }" --home "$homeDir" "$@"
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

    desktopItems =
      (
        lib.optional (!(isNull gameDir))
        (makeDesktopItem {
          desktopName = "Change Ninecraft Version";
          name = "ninecraft-extract";
          icon = "${version}/res/drawable/iconx.png";
          path = gameDir;
          exec = "${ninecraft-extract} %u";
          categories = ["Game"];
          terminal = true;
          mimeTypes = ["application/vnd.android.package-archive"];
        })
      )
      ++ [
        (
          makeDesktopItem {
            desktopName = "Ninecraft";
            name = "ninecraft";
            genericName = "MCPE Alpha Player";
            comment = "A mcpe 0.1 .0 - 0.10 .5 launcher for linux and windows";
            icon = "${version}/res/drawable/iconx.png";
            exec = "ninecraft ";
            categories = ["Game" "AdventureGame"];
            keywords = ["mcpe" "android" "mcpi" "pocket" "edition"];
          }
        )
        (
          makeDesktopItem {
            desktopName = "Extract APK to current folder";
            name = "ninecraft-install";
            icon = "${version}/res/drawable/iconx.png";
            exec = "${ninecraft-extract} %u";
            categories = ["Game"];
            terminal = true;
            mimeTypes = ["application/vnd.android.package-archive"];
          }
        )
      ];
  })
