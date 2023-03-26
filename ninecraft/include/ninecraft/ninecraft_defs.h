#ifndef NINECRAFT_NINECRAFT_DEFS_H
#define NINECRAFT_NINECRAFT_DEFS_H

#ifdef __thumb2__
#define NINECRAFT_FLOAT_FUNC __attribute__((pcs("aapcs")))
#else
#define NINECRAFT_FLOAT_FUNC
#endif

#endif