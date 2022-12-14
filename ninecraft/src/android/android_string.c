#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/android/android_string.h>
#include <string.h>

android_string_clone_t android_string_clone = NULL;
android_string_deallocate_block_t android_string_deallocate_block = NULL;
android_string_assign_t android_string_assign = NULL;

void android_string_setup_hooks(void *handle) {
    android_string_clone = (android_string_clone_t)internal_dlsym(handle, "_ZNSsC2ERKSs");
    android_string_deallocate_block = (android_string_deallocate_block_t)internal_dlsym(handle, "_ZNSt4priv12_String_baseIcSaIcEE19_M_deallocate_blockEv");
    android_string_assign = (android_string_assign_t)internal_dlsym(handle, "_ZNSs9_M_assignEPKcS0_");
}

void *android_string_ucopy_trivial(const void *__first, const void *__last, void *__result) {
  size_t n = (const char *)__last - (const char *)__first;
  return n ? (void *)((char *)memcpy(__result, __first, n) + n) : __result;
}

void android_string_move_src(android_string_t *__this, android_string_t *__ps) {
    if ((const char *)__ps->_M_start_of_storage == (const char *)__ps) {
        __this->buffers = __ps->buffers;
        __this->_M_finish = (void *)((const char *)__this->buffers._M_static_buf + ((const char *)__ps->_M_finish - (const char *)__ps->_M_start_of_storage));
        __this->_M_start_of_storage = __this->buffers._M_static_buf;
    } else {
        __this->_M_start_of_storage = __ps->_M_start_of_storage;
        __this->_M_finish = __ps->_M_finish;
        __this->buffers._M_end_of_storage = __ps->buffers._M_end_of_storage;
        __ps->_M_start_of_storage = 0;
    }
}

void android_string_allocate_block(android_string_t *__this, size_t __n) {
    __this->_M_start_of_storage = android_alloc_allocate(&__n);
    __this->_M_finish = __this->_M_start_of_storage;
    __this->buffers._M_end_of_storage = __this->_M_start_of_storage + __n;
}

void android_string_cstr(android_string_t *__this, char *__s) {
    size_t length = strlen(__s);
    void *last = __s + length;
    android_string_allocate_block(__this, length + 1);
    __this->_M_finish = android_string_ucopy_trivial(__s, last, __this->_M_start_of_storage);
    *(char *)__this->_M_finish = 0;
}

void android_string_equ(android_string_t *__this, char *__s) {
    android_string_assign(__this, __s, __s + strlen(__s));
}