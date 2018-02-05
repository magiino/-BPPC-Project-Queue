#ifndef __DEMAGLE_H__
#define __DEMAGLE_H__
// Name demagler for Unix/Linux GCC ABI RTTI interface by: Pety 2017
// !!! Don't modify this file !!!
// $Id: demagle.h 602 2017-11-27 14:17:49Z xlevri01 $

#if !defined(__GNUC__) || defined(_MSC_VER)
 #define DM(a) (a)
#else
 #include <string>
 #define DM(a) cxxabidemagle(a)
 std::string cxxabidemagle(const char *aMagledName);
#endif /* __GNUC__ */

#endif /* __DEMAGLE_H__ */
