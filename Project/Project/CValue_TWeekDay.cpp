/** \file CValue_TWeekDay.cpp
 *  \brief CValue_TWeekDay class source
 *  \details File contains implementation of CValue_TWeekDay support functions and global operators also for \c enum TWeekDay
 *  \warning Don't modify this file
 *  \author Pety 2017
 *  $Id: CValue_TWeekDay.cpp 564 2017-11-27 09:31:23Z petyovsky $
 */

#include <cstring>
#include "CValue_TWeekDay.h"

namespace CValue_TWeekDay
	{
	// Definition of the TWeekDay support constants
	enum { KTWeekDaysNameMaxLength = 11 }; ///< Max length of day name
	static const char* const KTWeekDaysName[KTWeekDaysCount] =
		{ "(Monday)", "(Tuesday)", "(Wednesday)", "(Thursday)", "(Friday)", "(Saturday)", "(Sunday)" }; ///< Day name definition

	TWeekDay CheckRangeWithException(const unsigned aDayNum)
		{
		if(aDayNum > unsigned(ESunday))
			{
			std::ostringstream oss; oss << "Value: " << aDayNum << " is out of range for type enum TWeekDay!";
			throw std::range_error(oss.str());
			}
		return(TWeekDay(aDayNum));
		} /* CheckingRangeWithException() */

	const char* TWeekStringName(TWeekDay aWeekDay)
		{return(KTWeekDaysName[unsigned(aWeekDay)]);}

	std::ostream& operator<<(std::ostream& aOStream, const TWeekDay& aWeekDay)
		{
		aOStream << KTWeekDaysName[unsigned(aWeekDay)];
		return(aOStream);
		} /* operator<<() */

	std::istream& operator>>(std::istream& aIStream, TWeekDay& aWeekDay)
		{
		char ch[KTWeekDaysNameMaxLength + 1] = {0,};
		unsigned i = 1, daynum = 0;
		do
			{
			aIStream >> ch[0];
			if(!aIStream.good())
				throw std::runtime_error("Input stream data integrity error!");
			}
		while(ch[0] != '(');
		do
			{
			aIStream >> ch[i];
			if(!aIStream.good())
				throw std::runtime_error("Input stream data integrity error!");
			}
		while((ch[i++] != ')') && (i < KTWeekDaysNameMaxLength));
		ch[i] = '\0';

		for(; (daynum < KTWeekDaysCount) && (std::strncmp(ch, KTWeekDaysName[daynum], KTWeekDaysNameMaxLength)); daynum++);
		aWeekDay = CheckRangeWithException(daynum);
		return(aIStream);
		} /* operator>>() */

	} /* namespace CValue_TWeekDay */
