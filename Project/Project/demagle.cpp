#if defined(__GNUC__) && !defined(_MSC_VER)
// Name demagler for Unix/Linux GCC ABI RTTI interface by: Pety 2017
// !!! Don't modify this file !!!
// $Id: demagle.cpp 564 2017-11-27 09:31:23Z petyovsky $

#include <cxxabi.h>
#include <cstdlib>
#include "demagle.h"

std::string cxxabidemagle(const char *aMagledName)
	{
    // http://www.ib.cnea.gov.ar/~oop/biblio/libstdc++/namespaceabi.html

	int status;
	char *realname;
	std::string str(aMagledName);
	realname = abi::__cxa_demangle(aMagledName, 0, 0, &status);
	if(!status) str = realname;
	std::free(realname);
	return(str);
	}
#endif /* defined(__GNUC__) && !defined(_MSC_VER) */
