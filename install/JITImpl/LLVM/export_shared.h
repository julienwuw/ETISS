
#ifndef LLVMJIT_EXPORT_H
#define LLVMJIT_EXPORT_H

#ifdef LLVMJIT_STATIC_DEFINE
#  define LLVMJIT_EXPORT
#  define LLVMJIT_NO_EXPORT
#else
#  ifndef LLVMJIT_EXPORT
#    ifdef LLVMJIT_make_genheader_EXPORTS
        /* We are building this library */
#      define LLVMJIT_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define LLVMJIT_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef LLVMJIT_NO_EXPORT
#    define LLVMJIT_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef LLVMJIT_DEPRECATED
#  define LLVMJIT_DEPRECATED __attribute__ ((__deprecated__))
#  define LLVMJIT_DEPRECATED_EXPORT LLVMJIT_EXPORT __attribute__ ((__deprecated__))
#  define LLVMJIT_DEPRECATED_NO_EXPORT LLVMJIT_NO_EXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define LLVMJIT_NO_DEPRECATED
#endif

#endif
