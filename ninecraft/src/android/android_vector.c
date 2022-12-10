#include <ninecraft/android/android_vector.h>
#include <ninecraft/dlfcn_stub.h>
#include <ninecraft/android/android_alloc.h>
#include <string.h>

size_t android_vector_compute_next_size(android_vector_t *__this, size_t __n, size_t __entry_size) {
    size_t __size = (__this->_M_finish - __this->_M_start) / __entry_size;
    if (__n > (0xFFFFFFFC / __entry_size) - __size) {
        puts("Invalid vector length");
        abort();
    }
    size_t __len = __size + MAX(__n, __size) + 1;
    if (__len < __size) {
        __len = 0xFFFFFFFC / __entry_size;
    }
    return __len;
}

uintptr_t android_vector_uninitialized_fill(uintptr_t __first, size_t __n, uintptr_t __x, size_t __entry_size) {
    while (__n > 0) {
        memcpy((void *)__first, (void *)__x, __entry_size);
        --__n;
        __first += __entry_size;
    }
    return __first;
}

uintptr_t android_vector_uninitialized_move(uintptr_t __first, uintptr_t __last, uintptr_t __result, size_t __entry_size) {
    uint32_t __cur = (uint32_t)__result;
    uint32_t diff = (uint32_t)(((uint32_t)__last - (uint32_t)__first) / __entry_size);
    for (uint32_t __n = diff; __n > 0; --__n) {
        memcpy((void *)__cur, (void *)__first, __entry_size);
        __first += __entry_size;
        __cur += __entry_size;
    }
    return __cur;
}

void android_vector_insert_overflow_aux(android_vector_t *__this, void *__pos, void *__x, void *reserved, size_t __fill_len, bool __atend, size_t __entry_size) {
    size_t __len = android_vector_compute_next_size(__this, __fill_len, __entry_size);
    size_t __size = __len * __entry_size;
    uintptr_t __new_start = (uintptr_t)android_alloc_allocate((uint32_t *)&__size);
    uintptr_t __new_finish = android_vector_uninitialized_move(__this->_M_start, (uintptr_t)__pos, __new_start, __entry_size);
    if (__fill_len == 1) {
        memcpy((void *)__new_finish, __x, __entry_size);
        __new_finish += __entry_size;
    } else {
        __new_finish = android_vector_uninitialized_fill(__new_finish, __fill_len, (uintptr_t)__x, __entry_size);
    }
    if (!__atend) {
        __new_finish = android_vector_uninitialized_move((uintptr_t)__pos, __this->_M_finish, __new_finish, __entry_size);
    }
    if (__this->_M_start) {
        android_alloc_deallocate((void *)__this->_M_start, (__this->_M_end_of_storage - __this->_M_start) & 0xFFFFFFF8);
    }
    __this->_M_start = __new_start;
    __this->_M_finish = __new_finish;
    __this->_M_end_of_storage = __new_start + __len * __entry_size;
}

void android_vector_push_back(android_vector_t *this_vector, void *item, size_t __entry_size) {
    if (this_vector->_M_finish == this_vector->_M_end_of_storage) {
        android_vector_insert_overflow_aux(this_vector, (void *)this_vector->_M_finish, item, 0, 1, 1, __entry_size);
    } else {
        if (this_vector->_M_finish) {
            memcpy((void *)this_vector->_M_finish, item, __entry_size);
        }
        this_vector->_M_finish += __entry_size;
    }
}