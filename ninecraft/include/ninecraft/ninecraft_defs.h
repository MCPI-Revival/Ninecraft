#ifndef NINECRAFT_NINECRAFT_DEFS_H
#define NINECRAFT_NINECRAFT_DEFS_H

#ifdef _WIN32
#define SYSV_WRAPPER_US "_"
#else
#define SYSV_WRAPPER_US ""
#endif

#if defined(__i386__) || defined(_M_IX86)
#if defined(_MSC_VER)

#define SYSV_WRAPPER_1(FUNC) \
    void __declspec(naked) SYSV_WRAPPER_##FUNC() { \
        __asm push [esp+4] \
        __asm call FUNC \
        __asm pop eax \
        __asm retn 4 \
    }

#define SYSV_WRAPPER_2(FUNC) \
    void __declspec(naked) SYSV_WRAPPER_##FUNC() { \
        __asm push [esp+8] \
        __asm push [esp+8] \
        __asm call FUNC \
        __asm pop eax \
        __asm add esp, 4 \
        __asm retn 4 \
    }

#define SYSV_WRAPPER_3(FUNC) \
    void __declspec(naked) SYSV_WRAPPER_##FUNC() { \
        __asm push [esp+12] \
        __asm push [esp+12] \
        __asm push [esp+12] \
        __asm call FUNC \
        __asm pop eax \
        __asm add esp, 8 \
        __asm retn 4 \
    }

#define SYSV_WRAPPER_4(FUNC) \
    void __declspec(naked) SYSV_WRAPPER_##FUNC() { \
        __asm push [esp+16] \
        __asm push [esp+16] \
        __asm push [esp+16] \
        __asm mov eax, dword ptr [esp+16] \
        __asm push eax \
        __asm call FUNC \
        __asm pop eax \
        __asm add esp, 12 \
        __asm retn 4 \
    }

#define SYSV_WRAPPER_5(FUNC) \
    void __declspec(naked) SYSV_WRAPPER_##FUNC() { \
        __asm push [esp+20] \
        __asm push [esp+20] \
        __asm push [esp+20] \
        __asm push [esp+20] \
        __asm push [esp+20] \
        __asm push eax \
        __asm call FUNC \
        __asm pop eax \
        __asm add esp, 16 \
        __asm retn 4 \
    }

#define SYSV_WRAPPER_6(FUNC) \
    void __declspec(naked) SYSV_WRAPPER_##FUNC() { \
        __asm push [esp+24] \
        __asm push [esp+24] \
        __asm push [esp+24] \
        __asm push [esp+24] \
        __asm push [esp+24] \
        __asm push [esp+24] \
        __asm call FUNC \
        __asm pop eax \
        __asm add esp, 20 \
        __asm retn 4 \
    }

#else

#define SYSV_WRAPPER_1(FUNC) \
    __asm__( \
        ".globl " SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC " \n" \
        SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC ": \n" \
        "mov      4(%esp), %eax \n" \
        "push %eax \n" \
        "call " SYSV_WRAPPER_US #FUNC " \n" \
        "pop %eax \n" \
        "ret      $0x4 \n" \
    ); \
    void SYSV_WRAPPER_##FUNC();

#define SYSV_WRAPPER_2(FUNC) \
    __asm__( \
        ".globl " SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC " \n" \
        SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC ": \n" \
        "mov      8(%esp), %eax \n" \
        "push %eax \n" \
        "mov      8(%esp), %eax \n" \
        "push %eax \n" \
        "call " SYSV_WRAPPER_US #FUNC " \n" \
        "pop %eax \n" \
        "add $4, %esp \n" \
        "ret      $0x4 \n" \
    ); \
    void SYSV_WRAPPER_##FUNC();

#define SYSV_WRAPPER_3(FUNC) \
    __asm__( \
        ".globl " SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC " \n" \
        SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC ": \n" \
        "mov      12(%esp), %eax \n" \
        "push %eax \n" \
        "mov      12(%esp), %eax \n" \
        "push %eax \n" \
        "mov      12(%esp), %eax \n" \
        "push %eax \n" \
        "call " SYSV_WRAPPER_US #FUNC " \n" \
        "pop %eax \n" \
        "add $8, %esp \n" \
        "ret      $0x4 \n" \
    ); \
    void SYSV_WRAPPER_##FUNC();

#define SYSV_WRAPPER_4(FUNC) \
    __asm__( \
        ".globl " SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC " \n" \
        SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC ": \n" \
        "mov      16(%esp), %eax \n" \
        "push %eax \n" \
        "mov      16(%esp), %eax \n" \
        "push %eax \n" \
        "mov      16(%esp), %eax \n" \
        "push %eax \n" \
        "mov      16(%esp), %eax \n" \
        "push %eax \n" \
        "call " SYSV_WRAPPER_US #FUNC " \n" \
        "pop %eax \n" \
        "add $12, %esp \n" \
        "ret      $0x4 \n" \
    ); \
    void SYSV_WRAPPER_##FUNC();

#define SYSV_WRAPPER_5(FUNC) \
    __asm__( \
        ".globl " SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC " \n" \
        SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC ": \n" \
        "mov      20(%esp), %eax \n" \
        "push %eax \n" \
        "mov      20(%esp), %eax \n" \
        "push %eax \n" \
        "mov      20(%esp), %eax \n" \
        "push %eax \n" \
        "mov      20(%esp), %eax \n" \
        "push %eax \n" \
        "mov      20(%esp), %eax \n" \
        "push %eax \n" \
        "call " SYSV_WRAPPER_US #FUNC " \n" \
        "pop %eax \n" \
        "add $16, %esp \n" \
        "ret      $0x4 \n" \
    ); \
    void SYSV_WRAPPER_##FUNC();

#define SYSV_WRAPPER_6(FUNC) \
    __asm__( \
        ".globl " SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC " \n" \
        SYSV_WRAPPER_US "SYSV_WRAPPER_" #FUNC ": \n" \
        "mov      24(%esp), %eax \n" \
        "push %eax \n" \
        "mov      24(%esp), %eax \n" \
        "push %eax \n" \
        "mov      24(%esp), %eax \n" \
        "push %eax \n" \
        "mov      24(%esp), %eax \n" \
        "push %eax \n" \
        "mov      24(%esp), %eax \n" \
        "push %eax \n" \
        "mov      24(%esp), %eax \n" \
        "push %eax \n" \
        "call " SYSV_WRAPPER_US #FUNC " \n" \
        "pop %eax \n" \
        "add $20, %esp \n" \
        "ret      $0x4 \n" \
    ); \
    void SYSV_WRAPPER_##FUNC();

#endif

#define SYSV_WRAPPER(FUNC, ARG_CNT) SYSV_WRAPPER_##ARG_CNT(FUNC)

#define GET_SYSV_WRAPPER(FUNC) SYSV_WRAPPER_##FUNC

#define EXTERN_SYSV_WRAPPER(FUNC) extern void SYSV_WRAPPER_##FUNC();
#else
#define SYSV_WRAPPER(FUNC, ARG_CNT)

#define GET_SYSV_WRAPPER(FUNC) FUNC

#define EXTERN_SYSV_WRAPPER(FUNC)
#endif

#endif
