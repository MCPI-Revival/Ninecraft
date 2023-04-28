#ifndef NINECRAFT_NINECRAFT_DEFS_H
#define NINECRAFT_NINECRAFT_DEFS_H

#ifdef __arm__
#define NINECRAFT_FLOAT_FUNC __attribute__((pcs("aapcs")))
#else
#define NINECRAFT_FLOAT_FUNC
#endif

#ifdef __arm__
#define NINECRAFT_CSR_FUNCDEF(return_type, name, ...) void name(return_type *__ret, __VA_ARGS__)
#define NINECRAFT_CSR_RETURN(x) *(typeof(x) *)__ret = x;
#define NINECRAFT_CSR_FUNCCALL(return_variable, name, ...) name(&return_variable, __VA_ARGS__)

#else
#define NINECRAFT_CSR_FUNCDEF(return_type, name, ...) return_type name(__VA_ARGS__)
#define NINECRAFT_CSR_RETURN(x) return x
#define NINECRAFT_CSR_FUNCCALL(return_variable, name, ...) return_variable = name(__VA_ARGS__)
#endif

#endif
