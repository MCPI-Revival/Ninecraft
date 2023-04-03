#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/android/android_string.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

android_string_deallocate_block_t android_string_deallocate_block = NULL;
android_string_assign_t android_string_assign = NULL;

void android_string_setup_hooks(void *handle) {
    android_string_deallocate_block = (android_string_deallocate_block_t)internal_dlsym(handle, "_ZNSt4priv12_String_baseIcSaIcEE19_M_deallocate_blockEv");
    android_string_assign = (android_string_assign_t)internal_dlsym(handle, "_ZNSs9_M_assignEPKcS0_");
}

void *android_string_ucopy_trivial(const void *__first, const void *__last, void *__result) {
  size_t n = (const char *)__last - (const char *)__first;
  return n ? (void *)((char *)memcpy(__result, __first, n) + n) : __result;
}

void android_string_move_src(android_string_t *__this, android_string_t *__ps) {
    if ((const char *)__ps->stlp._M_start_of_storage == (const char *)__ps) {
        __this->stlp.buffers = __ps->stlp.buffers;
        __this->stlp._M_finish = (void *)((const char *)__this->stlp.buffers._M_static_buf + ((const char *)__ps->stlp._M_finish - (const char *)__ps->stlp._M_start_of_storage));
        __this->stlp._M_start_of_storage = __this->stlp.buffers._M_static_buf;
    } else {
        __this->stlp._M_start_of_storage = __ps->stlp._M_start_of_storage;
        __this->stlp._M_finish = __ps->stlp._M_finish;
        __this->stlp.buffers._M_end_of_storage = __ps->stlp.buffers._M_end_of_storage;
        __ps->stlp._M_start_of_storage = 0;
    }
}

void android_string_allocate_block(android_string_t *__this, size_t __n) {
    __this->stlp._M_start_of_storage = android_alloc_allocate(&__n);
    __this->stlp._M_finish = __this->stlp._M_start_of_storage;
    __this->stlp.buffers._M_end_of_storage = __this->stlp._M_start_of_storage + __n;
}

char *android_string_to_str(android_string_t *__this) {
    if (android_alloc_node_alloc == NULL) { // just a small hack to allow gnu strings
        return __this->gnu.data;
    } else {
        return (char *)__this->stlp._M_start_of_storage;
    }
}

size_t android_string_tsize() {
    if (android_alloc_node_alloc == NULL) { // just a small hack to allow gnu strings
        return sizeof(android_string_gnu_t);
    } else {
        return sizeof(android_string_stlp_t);
    }
}

void android_string_cstr(android_string_t *__this, char *__s) {
    if (android_alloc_node_alloc != NULL) {
        size_t length = strlen(__s);
        void *last = __s + length;
        android_string_allocate_block(__this, length + 1);
        __this->stlp._M_finish = android_string_ucopy_trivial(__s, last, __this->stlp._M_start_of_storage);
        *(char *)__this->stlp._M_finish = 0;
    } else { // just a small hack to allow gnu strings
        size_t length = strlen(__s);
        char *str = (char *)malloc(0x0d + length);
        *(int *)str = length;
        *(int *)(str + 4) = length;
        *(int *)(str + 8) = 0;
        str[0x0c + length] = 0;
        memcpy(str + 0x0c, __s, length);
        __this->gnu.data = str + 0x0c;
    }
}

void android_string_equ(android_string_t *__this, char *__s) {
    if (android_string_assign) {
        android_string_assign(__this, __s, __s + strlen(__s));
    } else {
        if (__this->gnu.data == NULL) {
            android_string_cstr(__this, __s);
        } else {
            char *str = __this->gnu.data - 0x0c;
            size_t length = strlen(__s);
            if (*(int *)(str + 4) >= length) {
                *(int *)str = length;
                str[0x0c + length] = 0;
                memcpy(str + 0x0c, __s, length);
            } else {
                if (*(int *)(str + 4) != 0) {
                    free(str);
                }
                android_string_cstr(__this, __s);
            }
        }
    }
}