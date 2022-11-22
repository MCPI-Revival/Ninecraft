#include <hybris/dlfcn.h>
#include <ninecraft/android_string.h>
#include <string.h>
#include <ninecraft/android_alloc.h>

void *android_string$__ucopy_trivial(const void *__first, const void *__last, void *__result) {
  uintptr_t n = (const char*)__last - (const char*)__first;
  return n ? (void*)((char*)memcpy(__result, __first, n) + n) : __result;
}

void android_string$_M_allocate_block(android_string *__this, size_t __n, void *handle) {
    __this->_M_start_of_storage = android_alloc$allocate((uint32_t *)&__n, handle);
    __this->_M_finish = __this->_M_start_of_storage;
    __this->buffers._M_end_of_storage = __this->_M_start_of_storage + __n;
}

void to_str(android_string *str, char *cstr, void *handle) {
    size_t length = strlen(cstr);
    uintptr_t last = cstr + length;
    android_string$_M_allocate_block(str, length + 1, handle);
    str->_M_finish = android_string$__ucopy_trivial(cstr, last, str->_M_start_of_storage);
    *(char *)str->_M_finish = 0;
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
