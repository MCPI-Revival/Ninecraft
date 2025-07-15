{
  copyDesktopItems,
  lib,
  makeNinecraftDesktopItems,
  mcpeVersions,
  ninecraft,
  ninecraft-extract ? ../../tools/extract.sh,
  nixgl,
  stdenvNoCC,
  writeShellScript,
  writeText,
}: {
  name ? "ninecraft",
  homeDir ? "$(mktemp -d)",
  gameDir ? null,
  mods ? [],
  options ? null,
  version ? mcpeVersions.a0_6_1,
  useNixGL ? !stdenvNoCC
.isNixOS,
}: let
  optionsTxtContent = lib.concatStringsSep "\n" (
    lib.mapAttrsToList (
      k: v: let
        val = {
          bool =
            if v
            then "true"
            else "false";
          string = v;
          int = toString v;
          float = toString v;
        };
      in "${k}:${val.${builtins.typeOf v} or (toString v)}"
    ) (
      lib.optionalAttrs (lib.isAttrs options)
      {
        mp_username = "Steve";
        mp_server = "Steve";
        mp_server_visible_default = true;
        gfx_fancygraphics = true;
        gfx_lowquality = false;
        ctrl_sensitivity = 0.5;
        ctrl_invertmouse = false;
        ctrl_islefthanded = false;
        ctrl_usetouchscreen = false;
        ctrl_usetouchjoypad = false;
        feedback_vibration = false;
        game_difficulty = 4;
      }
      // options
    )
  );
  optionsTxt = writeText "options.txt" optionsTxtContent;
  startScript = writeShellScript "start-ninecraft-instance.sh" ''
    homeDir=${homeDir}
    ${
      lib.optionalString (gameDir != null) ''
        gameDir=${gameDir}

        # Version
        if [ ! -d $gameDir ]; then
          mkdir -p $gameDir
        fi
        if [[ ( ! -d "$gameDir/lib"  ) || ( ! -d "$gameDir/res"  ) || ( ! -d "$gameDir/assets"  ) ]]; then
          cp -r "${version}"/{assets,lib,res} "$gameDir"
          chmod -R u+w "$gameDir"/{assets,lib,res}
        fi
      ''
    }
    ${lib.optionalString (builtins.isAttrs options) ''
      # Options
      if [[ ! -d "$homeDir/storage/games/com.mojang/minecraftpe" ]]; then
        mkdir -p $homeDir/{mods,global_overrides,storage/games/com.mojang/minecraftpe}
      fi
      if [[ -L $homeDir/options.txt ]] || [[ ! -e $homeDir/options.txt ]]; then
        cp -sf "${optionsTxt}" $homeDir/options.txt
      fi
      if [[ -L "$homeDir/storage/games/com.mojang/minecraftpe/options.txt" ]] || [[ ! -e "$homeDir/storage/games/com.mojang/minecraftpe/options.txt" ]]; then
        cp -sf "${optionsTxt}" "$homeDir/storage/games/com.mojang/minecraftpe/options.txt"
      fi

    ''}
    # Mods
    ${lib.concatMapStrings (mod: "cp -r ${mod}/* $homeDir") mods}

    ${lib.optionalString useNixGL "\"${nixgl.auto.nixGLDefault}\"/bin/nixGL "}${lib.getExe
      ninecraft}" --game "${
      if (isNull gameDir)
      then version
      else "$gameDir"
    }" --home "$homeDir" "$@"
  '';
in
  stdenvNoCC.mkDerivation {
    name = "ninecraft-${name}";
    src = ninecraft;

    nativeBuildInputs = [copyDesktopItems];
    dontConfigure = true;
    dontBuild = true;
    installPhase = ''
      runHook preInstall
      mkdir -p $out/bin/
      install ${startScript} $out/bin/ninecraft-${name}
      runHook postInstall
    '';

    desktopItems = makeNinecraftDesktopItems {
      instance = name;
    };
  }
