#ifdef DWIN3DLIB_EXPORTS
#define DWIN3DLIB_API __declspec(dllexport)
#else
#define DWIN3DLIB_API __declspec(dllimport)
#endif
