#ifndef __CVALUE_UNIT_TESTS_H__
#define __CVALUE_UNIT_TESTS_H__
/** \file CValueUnitTests.h
 *  \brief Unit tests parameters and headers include for class CValue
 *  \details Simple functionality header and parameters for unit tests of class CValue
 *  \warning Don't modify this file (except of KCValue_allocate initialization)
 *  \author Pety
 *  $Id: CValueUnitTests.h 563 2017-11-27 09:30:07Z petyovsky $
 */

#include <iostream>
#include <sstream>
#include "CppUnitTest.h"

#define CVALUE_TEST_API
#include "CValue.h"
#include "check.h"

const bool KCValue_allocate = false;		// set for CValue variant that don't allocate dynamic memory for instance data
//const bool KCValue_allocate = true;		// set for CValue variant that allocate dynamic memory for instance data

#endif /* __CVALUE_UNIT_TESTS_H__ */
