#include <hybris/hook.h>
#include <ninecraft/android_string.hpp>

void to_str(void *str, char *cstr, void *handle) {
    #ifdef __i386__
    void *p = hybris_dlsym(handle, "_ZN11BlankButtonD0Ev")+0x80;
    asm volatile(
        "mov %0, %%eax;"
        "mov %1, %%edx;"
        "call %2;"
        :
        : "r"(str), "r"(cstr), "r"(p)
        : "%eax", "%edx"
    );
    #else
    #ifdef __arm__
    void *p = hybris_dlsym(handle, "_ZN6ButtonD0Ev")+0x12;
    /*asm volatile(
        "mov r0, %0;"
        "mov r1, %1;"
        "blx %2;"
        :
        : "r"(str), "r"(cstr), "r"(p)
        : "r0", "r1"
    );*/
    ((void (*)(void *, const char *))p)(str, cstr);
    #endif
    #endif
}
