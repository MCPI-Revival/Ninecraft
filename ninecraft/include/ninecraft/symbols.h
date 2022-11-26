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
    "AConfiguration_delete",
    "AConfiguration_fromAssetManager",
    "AConfiguration_getCountry",
    "AConfiguration_getLanguage",
    "AConfiguration_new",
    "AInputEvent_getDeviceId",
    "AInputEvent_getSource",
    "AInputEvent_getType",
    "AInputQueue_attachLooper",
    "AInputQueue_detachLooper",
    "AInputQueue_finishEvent",
    "AInputQueue_getEvent",
    "AInputQueue_preDispatchEvent",
    "AKeyEvent_getAction",
    "AKeyEvent_getKeyCode",
    "AKeyEvent_getMetaState",
    "AKeyEvent_getRepeatCount",
    "ALooper_addFd",
    "ALooper_pollAll",
    "ALooper_prepare",
    "AMotionEvent_getAction",
    "AMotionEvent_getPointerCount",
    "AMotionEvent_getPointerId",
    "AMotionEvent_getX",
    "AMotionEvent_getY",
    "ANativeActivity_finish",
    "ANativeWindow_setBuffersGeometry",
    0
};

const char *sles_symbols[] = {
    "slCreateEngine",
    "SL_IID_ENGINE",
    "SL_IID_BUFFERQUEUE",
    "SL_IID_VOLUME",
    "SL_IID_PLAY",
    0
};

#endif