#ifndef __CVALUE_H__
#define __CVALUE_H__
/** \file CValue.h
 *  \brief General header for CValue
 *  \details Header file for switching CValue variant.
 *  \author Pety 2017
 *  $Id: CValue.h 3565 2018-01-02 22:25:21Z xmagat01 $
 */

 
#define CVALUE_TEST_API			///< If defined CValue have special APIs for testing

#include "CValue_bool.h"
#include "CValue_long.h"
//#include "CValue_char.h"
//#include "CValue_int.h"
//#include "CValue_float.h"
//#include "CValue_longdouble.h"
#include "CValue_TWeekDay.h"
#include "CValue_TStudent.h"
//#include "CValue_template.h"


using namespace CValue_bool;
//using namespace CValue_long;
//using namespace CValue_char;
//using namespace CValue_int;
//using namespace CValue_float;
//using namespace CValue_longdouble;

//using namespace CValue_TWeekDay;
//using namespace CValue_TStudent;
//#define SUPPLEMENT_TESTS_TWEEKDAY

//typedef CValue_template::CValue<float> CValue;



#endif /* __CVALUE_H__ */
