/** \file CValue_TWeekDay.cpp
*  \brief CValue_TWeekDay class source
*  \details File contains implementation of CValue_TWeekDay support functions and global operators also for \c enum TWeekDay
*  \warning Don't modify this file
*  \author Pety 2017
*  $Id: CValue_TStudent.cpp 1215 2017-12-04 18:30:13Z xlevri01 $
*/

#include <cstring>
#include "CValue_TStudent.h"

namespace CValue_TStudent
{
    std::ostream& operator<<(std::ostream& aOStream, const TStudent& aStudent)
    {
        aOStream << aStudent.iVutID;
        return(aOStream);
    } /* operator<<() */

    std::istream& operator>>(std::istream& aIStream, TStudent& aStudent)
    {
        aIStream >> aStudent.iVutID;
        return(aIStream);
    } /* operator>>() */

} /* namespace CValue_TWeekDay */
