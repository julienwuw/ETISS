
#ifndef ETISS_EXPORT_H
#define ETISS_EXPORT_H

#ifdef ETISS_STATIC_DEFINE
#  define ETISS_EXPORT
#  define ETISS_NOEXPORT
#else
#  ifndef ETISS_EXPORT
#    ifdef ETISS_EXPORTS
        /* We are building this library */
#      define ETISS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define ETISS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef ETISS_NOEXPORT
#    define ETISS_NOEXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef ETISS_DEPRECATED
#  define ETISS_DEPRECATED __attribute__ ((__deprecated__))
#  define ETISS_DEPRECATED_EXPORT ETISS_EXPORT __attribute__ ((__deprecated__))
#  define ETISS_DEPRECATED_NO_EXPORT ETISS_NOEXPORT __attribute__ ((__deprecated__))
#endif

#define DEFINE_NO_DEPRECATED 1
#if DEFINE_NO_DEPRECATED
# define ETISS_NODEPRECATED
#endif

#endif
