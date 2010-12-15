#ifndef _LIBTVDB_DLLDEFINES_H_
#define _LIBTVDB_DLLDEFINES_H_

/* Cmake will define libtvdb_EXPORTS on Windows when it
configures to build a shared library. If you are going to use
another build system on windows or create the visual studio
projects by hand you need to define libtvdb_EXPORTS when
building a DLL on windows.
*/
// We are using the Visual Studio Compiler and building Shared libraries

#ifdef LIBTVDB_STATIC
   #define TVDB_API
#else
   #if defined (_WIN32) 
     #if defined(libtvdb_EXPORTS)
       #define  TVDB_API __declspec(dllexport)
     #else
       #define  TVDB_API __declspec(dllimport)
     #endif /* libtvdb_EXPORTS */
   #else /* defined (_WIN32) */
    #define TVDB_API
   #endif
#endif

#endif /* _libtvdb_DLLDEFINES_H_ */