#ifndef NINECRAFT_PATCH_PATCH_ADDRESS_H
#define NINECRAFT_PATCH_PATCH_ADDRESS_H

#include <stdlib.h>

typedef enum {
    PATCH_ADDRESS_PROT_NA,
    PATCH_ADDRESS_PROT_R,
    PATCH_ADDRESS_PROT_W,
    PATCH_ADDRESS_PROT_RW,
    PATCH_ADDRESS_PROT_X,
    PATCH_ADDRESS_PROT_XR,
    PATCH_ADDRESS_PROT_XW,
    PATCH_ADDRESS_PROT_XRW
} patch_address_prot_t;

void patch_address(void *address, void *data, size_t size, patch_address_prot_t prot);

#endif