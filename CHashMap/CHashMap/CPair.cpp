/** \file CPair.cpp
 *  \brief CPair class implementation
 *  \details File contain CPair class (key and value) implementation.
 *	$Id: CPair.cpp 129 2017-11-06 15:57:56Z xmagat01 $
 */

#include <sstream>
#include <stdexcept>
#include "CPair.h"

CPair::TKey CPair::Deserialize(const char *aStr, CValue &aValue)
	{
	std::istringstream iss(aStr, std::istringstream::in);
	char ch = '\0';

	iss >> ch;
	if(!iss.good() || ch != '(')
		throw std::runtime_error("Input stream data integrity error! Missing (");

	iss >> ch;
	if(!iss.good() || ch != '#')
		throw std::runtime_error("Input stream data integrity error! Missing #");
	
	TKey key = 0;
	iss >> key;
	if(!iss.good())
		throw std::runtime_error("Input stream data integrity error! Wrong key");

	iss >> ch;
	if(!iss.good() || ch != ',')
		throw std::runtime_error("Input stream data integrity error! missing ,");

	iss >> aValue;
	if(!iss.good())
		throw std::runtime_error("Input stream data integrity error! Wrong value");

	iss >> ch;
	if(!iss.good() || ch != ')')
		throw std::runtime_error("Input stream data integrity error! Missing )");

	return key;
	}  /* CPair::Deserialize(aStr, aValue) */
