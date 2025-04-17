#include <ninecraft/android/android_string.h>
#include <ninecraft/android/android_alloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ancmp/android_dlfcn.h>
#include <ancmp/android_atomic.h>

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

void android_string_gnu_copy(char *__dst, char *__src, size_t __n) {
    if (__n == 1) {
        __dst[0] = __src[0];
    } else {
        memcpy(__dst, __src, __n);
    }
}

void android_string_gnu_move(char *__dst, char *__src, size_t __n) {
    if (__n == 1) {
        __dst[0] = __src[0];
    } else {
        memmove(__dst, __src, __n);
    }
}

#define ANDROID_STRING_GNU_MAX_SIZE ((((((size_t)-1) - sizeof(android_string_gnu_data_t)) / 1) - 1) >> 2)

android_string_gnu_data_t *android_string_gnu_create_data(size_t __capacity, size_t __old_capacity) {
    if (__capacity > ANDROID_STRING_GNU_MAX_SIZE) {
        puts("invalid capacity");
        abort();
    }
    size_t __pagesize = 4096;
    size_t __malloc_header_size = 4 * sizeof(void *);
    if (__capacity > __old_capacity && __capacity < 2 * __old_capacity) {
        __capacity = 2 * __old_capacity;
    }
    size_t __size = (__capacity + 1) * sizeof(char) + sizeof(android_string_gnu_data_t);
    size_t __adj_size = __size + __malloc_header_size;
    if (__adj_size > __pagesize && __capacity > __old_capacity) {
        size_t __extra = __pagesize - __adj_size % __pagesize;
        __capacity += __extra / sizeof(char);
        if (__capacity > ANDROID_STRING_GNU_MAX_SIZE) {
            __capacity = ANDROID_STRING_GNU_MAX_SIZE;
        }
        __size = (__capacity + 1) * sizeof(char) + sizeof(android_string_gnu_data_t);
    }
    android_string_gnu_data_t *__p = (android_string_gnu_data_t *)malloc(__size);
    __p->capacity = __capacity;
    android_atomic_swap(0, &__p->refcount);
    return __p;
}

void android_string_gnu_dispose_data(android_string_gnu_data_t *__this) {
    if (!(!android_atomic_cmpxchg(0, 0, &__this->refcount) && __this->length == 0 && __this->capacity == 0)) {
        if (android_atomic_dec(&__this->refcount) <= 0) {
            free(__this);
        }
    }
}

android_string_gnu_data_t *android_string_gnu_clone_data(android_string_gnu_data_t *__this, size_t __res) {
    size_t __requested_cap = __this->length + __res;
    char *__data = (char *)((char *)__this + sizeof(android_string_gnu_data_t));
    android_string_gnu_data_t *__r = android_string_gnu_create_data(__requested_cap, __this->capacity);
    char *__r_data = (char *)((char *)__r + sizeof(android_string_gnu_data_t));
    if (__this->length) {
        android_string_gnu_copy(__r_data, __data, __this->length);
    }
    __r->length = __this->length;
    android_atomic_swap(0, &__r->refcount);
    __r_data[__this->length] = '\0';
    return __r;
}

void android_string_gnu_mutate(android_string_t *__this, size_t __pos, size_t __len1, size_t __len2) {
    android_string_gnu_data_t *str = (android_string_gnu_data_t *)(__this->gnu.data - sizeof(android_string_gnu_data_t));
    size_t __old_size = str->length;
    size_t __new_size = __old_size + __len2 - __len1;
    size_t __how_much = __old_size - __pos - __len1;
    if (__new_size > str->capacity || android_atomic_or(0, &str->refcount) > 0) {
        android_string_gnu_data_t *__r = android_string_gnu_create_data(__new_size, str->capacity);
        char *__r_data = (char *)((char *)__r + sizeof(android_string_gnu_data_t));
        if (__pos) {
            android_string_gnu_copy(__r_data, __this->gnu.data, __pos);
        }
        if (__how_much) {
            android_string_gnu_copy(__r_data + __pos + __len2, __this->gnu.data + __pos + __len1, __how_much);
        }
        android_string_gnu_dispose_data(str);
        __this->gnu.data = __r_data;
        str = __r;
	} else if (__how_much && __len1 != __len2) {
        android_string_gnu_move(__this->gnu.data + __pos + __len2, __this->gnu.data + __pos + __len1, __how_much);
	}
    str->length = __new_size;
    android_atomic_swap(0, &str->refcount);
    __this->gnu.data[__new_size] = '\0';
}

void android_string_gnu_replace(android_string_t *__this, size_t __pos1, size_t __n1, char *__s, size_t __n2) {
    android_string_gnu_mutate(__this, __pos1, __n1, __n2);
    if (__n2) {
        android_string_gnu_copy(&__this->gnu.data[__pos1], __s, __n2);
    }
}

void android_string_gnu_reserve(android_string_t *__this, size_t __res) {
    android_string_gnu_data_t *str = (android_string_gnu_data_t *)(__this->gnu.data - sizeof(android_string_gnu_data_t));
    if (__res != str->capacity || android_atomic_or(0, &str->refcount) > 0) {
        if (__res < str->length) {
            __res = str->length;
        }
        android_string_gnu_data_t *__tmp = android_string_gnu_clone_data(str, __res - str->length);
        android_string_gnu_dispose_data(str);
        __this->gnu.data = (char *)((char *)__tmp + sizeof(android_string_gnu_data_t));
    }
}

void android_string_gnu_assign(android_string_t *__this, char *__s) {
    android_string_gnu_data_t *str = (android_string_gnu_data_t *)(__this->gnu.data - sizeof(android_string_gnu_data_t));
    size_t length = strlen(__s);
    if (length > ANDROID_STRING_GNU_MAX_SIZE) {
        puts("invalid length");
        abort();
    }
    if ((uintptr_t)__s < (uintptr_t)__this->gnu.data || (uintptr_t)__s > ((uintptr_t)__this->gnu.data + (uintptr_t)str->length) || android_atomic_or(0, &str->refcount) > 0) {
        android_string_gnu_replace(__this, 0, str->length, __s, length);
    } else {
        size_t __pos = (size_t)(__s - __this->gnu.data);
        if (length <= __pos) {
            android_string_gnu_copy(__this->gnu.data, __s, length);
        } else if (__s != __this->gnu.data) {
            android_string_gnu_move(__this->gnu.data, __s, length);
        }
        str->length = length;
        android_atomic_swap(0, &str->refcount);
        __this->gnu.data[length] = '\0';
    }
}

void android_string_gnu_append(android_string_t *__this, char *__s, size_t __n) {
    if (__n) {
        android_string_gnu_data_t *str = (android_string_gnu_data_t *)(__this->gnu.data - sizeof(android_string_gnu_data_t));
        if (__n > ANDROID_STRING_GNU_MAX_SIZE) {
            puts("invalid length");
            abort();
        }
        size_t __len = __n + str->length;
        if (__len > str->capacity || android_atomic_or(0, &str->refcount) > 0) {
            if ((uintptr_t)__s < (uintptr_t)__this->gnu.data || (uintptr_t)__s > ((uintptr_t)__this->gnu.data + (uintptr_t)str->length)) {
                android_string_gnu_reserve(__this, __len);
            } else {
                size_t __off = (size_t)(__s - __this->gnu.data);
                android_string_gnu_reserve(__this, __len);
                __s = &__this->gnu.data[__off];
            }
        }
        android_string_gnu_copy(&__this->gnu.data[str->length], __s, __n);
        str->length = __len;
        android_atomic_swap(0, &str->refcount);
        __this->gnu.data[__len] = '\0';
    }
}

size_t android_string_tsize() {
    if (android_alloc_node_alloc == NULL) {
        return sizeof(android_string_gnu_t);
    } else {
        return sizeof(android_string_stlp_t);
    }
}

void android_string_equ(android_string_t *__this, char *__s) {
    if (android_string_tsize() == sizeof(android_string_stlp_t)) {
        android_string_assign(__this, __s, __s + strlen(__s));
    } else {
        android_string_gnu_assign(__this, __s);
    }
}

void android_string_add(android_string_t *__this, char *__s) {
    if (android_string_tsize() == sizeof(android_string_stlp_t)) {
        android_string_append(__this, __s, __s + strlen(__s));
    } else {
        android_string_gnu_append(__this, __s, strlen(__s));
    }
}

char *android_string_to_str(android_string_t *__this) {
    if (android_string_tsize() == sizeof(android_string_stlp_t)) {
        return (char *)__this->stlp._M_start_of_storage;
    } else {
        return __this->gnu.data;
    }
}

void android_string_cstrl(android_string_t *__this, char *__s, size_t length) {
    if (android_string_tsize() == sizeof(android_string_stlp_t)) {
        void *last = __s + length;
        android_string_allocate_block(__this, length + 1);
        __this->stlp._M_finish = android_string_ucopy_trivial(__s, last, __this->stlp._M_start_of_storage);
        *(char *)__this->stlp._M_finish = 0;
    } else {
        android_string_gnu_data_t *str = (android_string_gnu_data_t *)malloc(sizeof(android_string_gnu_data_t) + 1 + length);
        str->length = length;
        str->capacity = length;
        str->refcount = 0;
        char *data = (char *)(str+1);
        data[length] = '\0';
        memcpy(data, __s, length);
        __this->gnu.data = data;
    }
}

void android_string_cstr(android_string_t *__this, char *__s) {
    android_string_cstrl(__this, __s, strlen(__s));
}

void android_string_destroy(android_string_t *__this) {
    if (android_string_tsize() == sizeof(android_string_stlp_t)) {
        android_string_deallocate_block(__this);
    } else {
        android_string_gnu_dispose_data((android_string_gnu_data_t *)(__this->gnu.data - sizeof(android_string_gnu_data_t)));
    }
}