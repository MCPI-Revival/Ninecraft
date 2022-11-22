#include <ninecraft/android_vector.hpp>
#include <hybris/dlfcn.h>
#include <ninecraft/android_alloc.hpp>
#include <string.h>

uint32_t android_vector$_M_compute_next_size(android_vector *__this, size_t __n) {
    size_t __size = STLPORT_SIZE_TYPE(__this->_M_finish - __this->_M_start);
    if (__n > STLPORT_MAX_SIZE - __size) {
        puts("Invalid vector length");
        abort();
    }
    size_t __len = __size + MAX(__n, __size) + 1;
    if (__len < __size) {
        __len = STLPORT_MAX_SIZE;
    }
    return __len;
}

void *__ucopy_trivial(const void *__first, const void *__last, void *__result) {
    ptrdiff_t n = (const char *)__last - (const char *)__first;
    //dums: this version can use memcpy (__copy_trivial can't)
    return n ? (void *)((char *)memcpy(__result, __first, n) + n) : __result;
}

void android_vector$_M_insert_overflow_aux(android_vector *__this, void *__pos, void *__x, void *reserved, size_t __fill_len, bool __atend, void *handle) {
    puts("got called!");
    uintptr_t v13; // __node_alloc
    uintptr_t v14; // r8
    int v15; // r11
    void *v17; // r11
    int v19; // r9
    uintptr_t v20; // r9
    int v21; // r11

    uintptr_t __new_finish;
    size_t __len = android_vector$_M_compute_next_size(__this, __fill_len);
    if (__len > 0xAAAAAAA) {
        puts("out of memory\n");
        abort();
    }
    uintptr_t __new_start = __len;
    printf("size: %u\n", __len);
    if (__len) {
        size_t __size = __len * 24;
        __new_start = (uintptr_t)android_alloc$allocate((uint32_t *)&__size, handle);
        puts("allocated!");
    }
    v13 = __this->_M_start;
    v14 = __new_start;
    v15 = STLPORT_SIZE_TYPE((int)__pos - (int)__this->_M_start);
    for (int i = STLPORT_SIZE_TYPE((int)__pos - (int)__this->_M_start); i > 0; --i ) {
        if (v14) {
            *(char **)(v14 + 20) = *(char **)(v13 + 5);
            android_string$_M_move_src((android_string *)v14, (android_string *)v13);
        }
        v13 = (uintptr_t)((char *)v13 + 24);
        v14 += 6;
    }
    v17 = (android_string *)(__new_start + 24 * (v15 & ~(v15 >> 31)));
    if (__fill_len == 1) {
        if (v17) {
            android_string$string((android_string *)v17, (android_string *)__x, handle);
        }
        __new_finish = (uintptr_t)v17 + 24;
    } else {
        __new_finish = (uintptr_t)v17 + 24 * __fill_len;
        v19 = STLPORT_SIZE_TYPE(24 * __fill_len);
        while (v19 > 0) {
            if (v17) {
                android_string$string((android_string *)v17, (android_string *)__x, handle);
            }
            --v19;
            v17 = (android_string *)((char *)v17 + 24);
        }
    }
    if (!__atend) {
        v20 = __new_finish;
        v21 = STLPORT_SIZE_TYPE((int)__this->_M_finish - (int)__pos);
        for (int i = STLPORT_SIZE_TYPE((int)__this->_M_finish - (int)__pos); i > 0; --i) {
            if (v20) {
                *(char **)(v20 + 20) = *(char **)(__pos + 20);
                android_string$_M_move_src((android_string *)v20, (android_string *)__pos);
            }
            *(int *)__pos += 6;
            v20 += 6;
        }
        *(int *)__new_finish += 24 * (v21 & ~(v21 >> 31));
    }
    printf("MSTART: %u\n", __this->_M_start);
    printf("NEW MSTART: %u\n", __new_start);
    printf("MSTART size: %u\n", (__this->_M_end_of_storage - __this->_M_start) & 0xFFFFFFF8);
    if (__this->_M_start) {
        android_alloc$deallocate((void *)__this->_M_start, (__this->_M_end_of_storage - __this->_M_start) & 0xFFFFFFF8, handle);
        puts("deallocate!");
    }
    __this->_M_start = __new_start;
    __this->_M_finish = __new_finish;
    __this->_M_end_of_storage = __new_start + 24 * __len;
}

void android_vector$_M_insert_overflow_aux_2(android_vector *__this, void *__pos, void *__x, void *reserved, size_t __fill_len, bool __atend, void *handle) {
    android_string v12;
    if ((unsigned int)__x < __this->_M_start || (unsigned int)__x >= __this->_M_finish) {
        android_vector$_M_insert_overflow_aux(
            __this,
            (int *)__pos,
            __x,
            0,
            __fill_len,
            __atend,
            handle
        );
    } else {
        android_string$string((android_string *)&v12, (android_string *)__x, handle);
        android_vector$_M_insert_overflow_aux(
            __this,
            __pos,
            &v12,
            0,
            __fill_len,
            __atend,
            handle
        );
        android_string$_M_deallocate_block((android_string *)&v12, handle);
    }
}

void android_vector$push_back(android_vector *this_vector, android_string *item, void *handle) {
    if (this_vector->_M_finish == this_vector->_M_end_of_storage) {
        puts("ok1");
        android_vector$_M_insert_overflow_aux_2(this_vector, (void *)this_vector->_M_finish, item, 0, 1, 1, handle);
    } else {
        puts("ok2");
        if (this_vector->_M_finish) {
            android_string$string((android_string *)this_vector->_M_finish, item, handle);
        }
        this_vector->_M_finish += 24;
    }
}