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

uint32_t android_vector$__uninitialized_fill(uintptr_t __first, size_t __n, uintptr_t __x, void *handle) {
    size_t size = STLPORT_SIZE_TYPE(__n * 24);
    while (size > 0) {
        android_string$string((android_string *)__first, (android_string *)__x, handle);
        --size;
        __first += 24;
    }
    return __first;
}

uintptr_t android_vector$__uninitialized_move(uintptr_t __first, uintptr_t __last, uintptr_t __result) {
    uint32_t __cur = (uint32_t)__result;
    uint32_t diff = (uint32_t)STLPORT_SIZE_TYPE((uint32_t)__last - (uint32_t)__first);
    for (uint32_t __n = diff; __n > 0; --__n) {
        android_string$_M_move_src((android_string *)__cur, (android_string *)__first);
        __first += 24;
        __cur += 24;
    }
    return __cur;
}

void android_vector$_M_insert_overflow_aux(android_vector *__this, void *__pos, void *__x, void *reserved, size_t __fill_len, bool __atend, void *handle) {
    size_t __len = android_vector$_M_compute_next_size(__this, __fill_len);
    size_t __size = __len * 24;
    uintptr_t __new_start = (uintptr_t)android_alloc$allocate((uint32_t *)&__size, handle);
    uintptr_t __new_finish = android_vector$__uninitialized_move(__this->_M_start, (uintptr_t)__pos, __new_start);
    if (__fill_len == 1) {
        android_string$string((android_string *)__new_finish, (android_string *)__x, handle);
        __new_finish += 24;
    } else {
        __new_finish = android_vector$__uninitialized_fill(__new_finish, __fill_len, (uintptr_t)__x, handle);
    }
    if (!__atend) {
        __new_finish = android_vector$__uninitialized_move((uintptr_t)__pos, __this->_M_finish, __new_finish);
    }
    if (__this->_M_start) {
        android_alloc$deallocate((void *)__this->_M_start, (__this->_M_end_of_storage - __this->_M_start) & 0xFFFFFFF8, handle);
    }
    __this->_M_start = __new_start;
    __this->_M_finish = __new_finish;
    __this->_M_end_of_storage = __new_start + 24 * __len;
}

void android_vector$push_back(android_vector *this_vector, android_string *item, void *handle) {
    if (this_vector->_M_finish == this_vector->_M_end_of_storage) {
        android_vector$_M_insert_overflow_aux(this_vector, (void *)this_vector->_M_finish, item, 0, 1, 1, handle);
    } else {
        if (this_vector->_M_finish) {
            android_string$string((android_string *)this_vector->_M_finish, item, handle);
        }
        this_vector->_M_finish += 24;
    }
}