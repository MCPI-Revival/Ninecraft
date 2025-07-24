{
  stdenv,
  writeText,
  androidenv,
  ninecraft-toolchain-build-scripts,
  defaultUseNDK?false,
  fetchurl,
  libmpc,gmp ,mpfr ,isl ,texinfo ,zlib ,bison ,flex ,python3 ,perl ,help2man,
  ...
}: {
  pname ? null,
  version ? null,
  useNDK? defaultUseNDK,
  name ? "${pname}-${version}",
  src,
  mainC ? "main.c",
  precompiled ? false,
  compiledX86 ? null,
  compiledArm ? null,
  globalOverrides ? "",
  ...
}: let
  effectiveName =
    if name != null
    then name
    else if pname != null && version != null
    then "${pname}-${version}"
    else throw "Either 'name' must be provided, or both 'pname' and 'version'.";
  androidToolchain = androidenv.composeAndroidPackages {
    includeNDK = true;
    platformVersions = ["21"];
  };
  androidMk = writeText "Android.mk" ''
        LOCAL_PATH := $(call my-dir)
    include $(CLEAR_VARS)
    LOCAL_MODULE := ${effectiveName}
    LOCAL_SRC_FILES := ${mainC}
    include $(BUILD_SHARED_LIBRARY)
  '';
  abi =
    if stdenv.hostPlatform.isx86
    then "x86"
    else "armeabi-v7a";
  applicationMk = writeText "Application.mk" ''
    APP_PLATFORM := android-21
    APP_ABI := ${abi}
  '';
  ninecraftModToolchain = stdenv.mkDerivation rec {
    name = "ninecraft-mod-toolchain";

    dontConfigure = true;
    dontPatch = true;

     buildInputs = [libmpc gmp mpfr isl texinfo zlib bison flex python3 perl help2man];
    hardeningDisable = [ "format" ];
    sourceRoot = ".";

  CHOSEN_GCC_VERSION="13.3.0";
  CHOSEN_BINUTILS_VERSION="2.40";

    srcs = [
        ninecraft-toolchain-build-scripts
      (fetchurl {
        url = "https://ftp.gnu.org/gnu/binutils/binutils-${CHOSEN_BINUTILS_VERSION}.tar.xz";
        hash = "sha256-D4pMJy1/F/Np3tEKSsoouOMEgo6VUm2kgrDMxN/J2OE=";
      })
      (fetchurl {
        url = "https://ftp.gnu.org/gnu/gcc/gcc-${CHOSEN_GCC_VERSION}/gcc-${CHOSEN_GCC_VERSION}.tar.gz";
        hash = "sha256-OisQyrhuMjWP2shxVG1X4nAOm9tYde8z//W2ASZbnjI=";
      })
    ];

    postUnpack = ''
      cp ninecraft-mod-toolchain-build-scripts/*.sh .
      cp -r */sysroot .
    '';

    buildPhase = ''
      echo $PWD
      ls -lah .
      ./build-all.sh
      cp -r  toolchain* $out sysroot bin
    '';
  };
  preCompiledLib = let
    c = {
      inherit compiledArm compiledX86;
    };
  in
    if stdenv.hostPlatform.isx86
    then (c.compiledX86 or src)
    else (c.compiledArm or src);
  compileNDK = stdenv.mkDerivation {
    name = effectiveName;
    inherit src;
    buildInputs = with androidToolchain; [androidsdk ndk-bundle];
    buildPhase = ''
      runHook preBuild
      mkdir jni
      cp -r $src/* jni
      cp ${androidMk} jni/Android.mk
      cp ${applicationMk} jni/Application.mk
      ndk-build
      runHook postBuild
    '';
    installPhase = ''
      runHook preInstall
      mkdir -p $out/{mods,global_overrides}
      cp -r libs/*/*.so $out/mods
      if [[ -d "${globalOverrides}" ]]; then
        cp -r ${globalOverrides} $out/global_overrides
      fi
      runHook postInstall
    '';
  };
  compileToochain = stdenv.mkDerivation {
    # TODO: Compile mod using ninecraft toolchain
  };
  getLib = stdenv.mkDerivation {
    name = effectiveName;
    inherit src;
    installPhase = ''
      runHook preInstall
      mkdir -p $out/mods

      if [[ -f "${preCompiledLib}" ]]; then
        cp -r "${preCompiledLib}" $out/mods
      fi
      if [[ -d "${preCompiledLib}" ]]; then
        cp -r "${preCompiledLib}/*/*.so" $out/mods
      fi
      runHook postInstall
    '';
  };
in
  if precompiled
  then getLib
  else if useNDK then compileNDK else compileToochain
