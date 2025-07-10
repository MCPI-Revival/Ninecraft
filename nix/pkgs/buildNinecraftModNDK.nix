{
  stdenv,
  writeText,
  androidenv,
  ...
}: {
  pname ? null,
  version ? null,
  name ? "${pname}-${version}",
  src,
  mainC ? "main.c",
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
  applicationMk = writeText "Application.mk" ''
    APP_PLATFORM := android-21
    APP_ABI := x86
  '';
in
  stdenv.mkDerivation {
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
      mkdir -p $out/mods
      cp -r libs/*/*.so $out/mods
      runHook postInstall
    '';
  }
