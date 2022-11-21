#include <hybris/dlfcn.h>
#include <ninecraft/android_string.hpp>

void to_str(android_string *str, char *cstr, void *handle) {
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

void android_string$string(android_string *__this, android_string *str, void *handle) {
    ((void (*)(void *, void *))hybris_dlsym(handle, "_ZNSsC2ERKSs"))(__this, str);
}

void android_string$_M_deallocate_block(android_string *__this, void *handle) {
    ((void (*)(android_string *))hybris_dlsym(handle, "_ZNSt4priv12_String_baseIcSaIcEE19_M_deallocate_blockEv"))(__this);
}

void android_string$_M_move_src(android_string *__this, android_string *src) {
    if ((uintptr_t)src->_M_start_of_storage == (uintptr_t)src) {
        __this->buffers = src->buffers;
        __this->_M_finish = (void *)((uintptr_t)__this->buffers._M_static_buf + ((uintptr_t)src->_M_finish - (uintptr_t)src->_M_start_of_storage));
        __this->_M_start_of_storage = __this->buffers._M_static_buf;
    } else {
        __this->_M_start_of_storage = src->_M_start_of_storage;
        __this->_M_finish = src->_M_finish;
        __this->buffers._M_end_of_storage = src->buffers._M_end_of_storage;
        src->_M_start_of_storage = 0;
    }
}
