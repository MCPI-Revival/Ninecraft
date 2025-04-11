#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/android/android_alloc.h>
#include <ninecraft/android/android_string.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ancmp/android_dlfcn.h>

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
    __this->stlp.buffers._M_end_of_storage = (void *)((char *)__this->stlp._M_start_of_storage + __n);
}

void android_string_deallocate_block(android_string_t *__this) {
    if (__this->stlp._M_start_of_storage && __this->stlp._M_start_of_storage != __this->stlp.buffers._M_static_buf) {
        android_alloc_deallocate(__this->stlp._M_start_of_storage, (size_t)__this->stlp.buffers._M_end_of_storage - (size_t)__this->stlp._M_start_of_storage); 
    }
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

void android_string_cstrl(android_string_t *__this, char *__s, size_t length) {
    if (android_alloc_node_alloc != NULL) {
        void *last = __s + length;
        android_string_allocate_block(__this, length + 1);
        __this->stlp._M_finish = android_string_ucopy_trivial(__s, last, __this->stlp._M_start_of_storage);
        *(char *)__this->stlp._M_finish = 0;
    } else { // just a small hack to allow gnu strings
        char *str = (char *)malloc(0x0d + length);
        *(int *)str = length;
        *(int *)(str + 4) = length;
        *(int *)(str + 8) = 0;
        str[0x0c + length] = 0;
        memcpy(str + 0x0c, __s, length);
        __this->gnu.data = str + 0x0c;
    }
}

void android_string_destroy(android_string_t *__this) {
    if (android_alloc_node_alloc != NULL) {
        android_string_deallocate_block(__this);
    } else {
        free(__this->gnu.data - 0x0c);
    }
}

uintptr_t android_string_rest(android_string_t *__this) {
    if ((uintptr_t)__this->stlp._M_start_of_storage == (uintptr_t)__this->stlp._M_start_of_storage) {
        return ((uintptr_t)__this->stlp._M_start_of_storage + sizeof(__this->stlp.buffers)) - (uintptr_t)__this->stlp._M_finish;
    }
    return (uintptr_t)__this->stlp.buffers._M_end_of_storage - (uintptr_t)__this->stlp._M_finish;
}

void android_string_erase(android_string_t *__this, void *__first, void *__last) {
    memmove(__first, __last, ((size_t)__this->stlp._M_finish - (size_t)__last) + 1);
    __this->stlp._M_finish = (void *)((uintptr_t)__this->stlp._M_finish - ((uintptr_t)__last - (uintptr_t)__first));
}

size_t android_string_next_size(android_string_t *__this, size_t __n) {
    size_t str_size = (size_t)__this->stlp._M_finish - (size_t)__this->stlp._M_start_of_storage;
    size_t ret = 0;
    if (__n > 0xfffffffe - str_size) {
        puts("Invalid size");
        abort();
    }
    if (str_size < __n) {
        ret = (str_size + 1) + __n;
    } else {
        ret = (str_size * 2) + 1;
    }
    if (ret <= 0xfffffffe && ret >= str_size) {
        return ret;
    }
    return 0xfffffffe;
}

void android_string_reset(android_string_t *__this, void *__new_start, void *__new_finish, void *__new_end) {
    __this->stlp._M_finish = __new_finish;
    __this->stlp.buffers._M_end_of_storage = __new_end;
    __this->stlp._M_start_of_storage = __new_start;
}

void android_string_construct_null(void *addr) {
    *(char *)addr = '\0';
}

void android_string_append(android_string_t *__this, char *__first, char *__last) {
    if (__first != __last) {
        size_t __n = (size_t)__last - (size_t)__first;
        if (__n >= android_string_rest(__this)) {
            size_t __len = android_string_next_size(__this, __n);
            void *__new_start = android_alloc_allocate(&__len);
            void *__new_finish = android_string_ucopy_trivial(__this->stlp._M_start_of_storage, __this->stlp._M_finish, __new_start);
            __new_finish = android_string_ucopy_trivial(__first, __last, __new_finish);
            android_string_construct_null(__new_finish);
            android_string_deallocate_block(__this);
            android_string_reset(__this, __new_start, __new_finish, (void *)((uintptr_t)__new_start + __len));
        } else {
            char * __f1 = __first;
            ++__f1;
            android_string_ucopy_trivial((void *)__f1, __last, (void *)((uintptr_t)__this->stlp._M_finish + 1));
            android_string_construct_null((void *)((uintptr_t)__this->stlp._M_finish + __n));
            ((char *)__this->stlp._M_finish)[0] = __first[0];
            *(uintptr_t *)(&__this->stlp._M_finish) += __n;
        }
    }
}

void android_string_assign(android_string_t *__this, char *__f, char *__l) {
    size_t __n = (size_t)__l - (size_t)__f;
    size_t str_size = (size_t)__this->stlp._M_finish - (size_t)__this->stlp._M_start_of_storage;
    if (__n <= str_size) {
        if (__n) {
            memmove(__this->stlp._M_start_of_storage, __f, __n);
        }
        android_string_erase(__this, (void *)((uintptr_t)__this->stlp._M_start_of_storage + __n), __this->stlp._M_finish);
    } else {
        if (str_size) {
            memmove(__this->stlp._M_start_of_storage, __f, str_size);
        }
        android_string_append(__this, __f + str_size, __l);
    }
}

void android_string_equ(android_string_t *__this, char *__s) {
    if (android_alloc_node_alloc) {
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