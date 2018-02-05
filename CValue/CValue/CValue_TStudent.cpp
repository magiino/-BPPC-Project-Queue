/** \file CValue_TWeekDay.cpp
*  \brief CValue_TWeekDay class source
*  \details File contains implementation of CValue_TWeekDay support functions and global operators also for \c enum TWeekDay
*  \warning Don't modify this file
*  \author Pety 2017
*  $Id: CValue_TStudent.cpp 2790 2017-12-26 01:47:26Z xmagat01 $
*/

#include <cstring>
#include "CValue_TStudent.h"

namespace CValue_TStudent
{
    std::ostream& operator<<(std::ostream& aOStream, const TStudent& aStudent)
    {
        aOStream << "(" << aStudent.iVutID << ")";
        return(aOStream);
    } /* operator<<() */

    std::istream& operator>>(std::istream& aIStream, TStudent& aStudent)
    {
        char ch = '\0';
        aIStream >> ch;
        if (!aIStream.good() || ch != '(')
            throw std::runtime_error("Input stream data integrity error! Wrong input format");

        aIStream >> aStudent.iVutID;

        aIStream >> ch;
        if (!aIStream.good() || ch != ')')
            throw std::runtime_error("Input stream data integrity error! Wrong input format");

        return(aIStream);
    } /* operator>>() */
} /* namespace CValue_TWeekDay */
