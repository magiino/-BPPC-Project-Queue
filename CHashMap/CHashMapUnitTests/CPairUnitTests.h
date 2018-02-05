#ifndef __CPAIR_UNIT_TESTS_H__
#define __CPAIR_UNIT_TESTS_H__
/** \file CPairUnitTests.h
 *  \brief Unit tests parameters and headers include for class CPair
 *  \details Simple functionality header and parameters for unit tests of class CPair
 *  \warning Don't modify this file 
 *  \author Richter
 *  $Id: CPairUnitTests.h 1763 2017-12-11 15:25:59Z xkunaj01 $
*/

#include <iostream>
#include <sstream>
#include "CppUnitTest.h"
#include "../CHashMap/CPair.h"
#include "../CHashMap/check.h"

const bool KCValue_allocate = false;		// set for CValue variant that don't allocate dynamic memory for instance data
//const bool KCValue_allocate = true;		// set for CValue variant that allocate dynamic memory for instance data

#endif /* __CPAIR_UNIT_TESTS_H__ */