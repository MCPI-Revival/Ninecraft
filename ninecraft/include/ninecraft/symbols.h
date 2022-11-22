#ifndef MCPER_SYMBOLS
#define MCPER_SYMBOLS

const char *egl_symbols[] = {
    "eglChooseConfig",
    "eglCreateContext",
    "eglCreateWindowSurface",
    "eglDestroyContext",
    "eglDestroySurface",
    "eglGetConfigAttrib",
    "eglGetCurrentDisplay",
    "eglGetDisplay",
    "eglInitialize",
    "eglMakeCurrent",
    "eglQuerySurface",
    "eglSwapBuffers",
    "eglSwapInterval",
    "eglTerminate",
    0
};

const char *android_symbols[] = {
    "ANativeWindow_setBuffersGeometry",
    "AAssetManager_open",
    "AAsset_getLength",
    "AAsset_getBuffer",
    "AAsset_close",
    "ALooper_pollAll",
    "ANativeActivity_finish",
    "AInputQueue_getEvent",
    "AKeyEvent_getKeyCode",
    "AInputQueue_preDispatchEvent",
    "AInputQueue_finishEvent",
    "AKeyEvent_getAction",
    "AMotionEvent_getAxisValue",
    "AKeyEvent_getRepeatCount",
    "AKeyEvent_getMetaState",
    "AInputEvent_getDeviceId",
    "AInputEvent_getType",
    "AInputEvent_getSource",
    "AMotionEvent_getAction",
    "AMotionEvent_getPointerId",
    "AMotionEvent_getX",
    "AMotionEvent_getRawX",
    "AMotionEvent_getY",
    "AMotionEvent_getRawY",
    "AMotionEvent_getPointerCount",
    "AConfiguration_new",
    "AConfiguration_fromAssetManager",
    "AConfiguration_getLanguage",
    "AConfiguration_getCountry",
    "ALooper_prepare",
    "ALooper_addFd",
    "AInputQueue_detachLooper",
    "AConfiguration_delete",
    "AInputQueue_attachLooper",
    0
};

const char *sles_symbols[] = {
    "slQueryNumSupportedEngineInterfaces",
    "slCreateEngine",
    "slQuerySupportedEngineInterfaces",
    "SL_IID_ENGINE",
    "SL_IID_BUFFERQUEUE",
    "SL_IID_VOLUME",
    "SL_IID_PLAY",
    0
};

#endif