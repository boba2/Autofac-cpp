#ifdef NO_DI_API
#  define DI_API
#else
#  ifdef DI_EXPORTS
#    define DI_API __declspec(dllexport)
#  else
#    define DI_API __declspec(dllimport)
#  endif
#endif
