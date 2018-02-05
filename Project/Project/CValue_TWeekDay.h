#ifndef __CVALUE_TWEEKDAY_H__
#define __CVALUE_TWEEKDAY_H__
/** \file CValue_TWeekDay.h
 *  \brief CValue_TWeekDay class header
 *  \details File contain CValue_TWeekDay::CValue definition.
 *  \warning Don't modify this file
 *  \author Pety 2017
 *  $Id: CValue_TWeekDay.h 3108 2017-12-30 15:22:32Z xmagat01 $
 */

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <typeinfo>
#include "ClassInfo.h"

#include "check.h"

/** \brief Namespace for encapsulating of \c TWeekDay variant of CValue class
 *  \details For selecting this variant of CValue class uncomment \c using \c namespace section in the CValue.h
 */
namespace CValue_TWeekDay
	{
	/** \brief Basic definition of enumeration type for representing day of week.
	 */
	enum TWeekDay
		{EMonday = 0, ETuesday, EWednesday, EThursday, EFriday, ESaturday, ESunday};

	/** \brief Constant defining numbers of day in the week
	 */
	enum { KTWeekDaysCount = 7 };

// Definition of support functions a global operators for type enum TWeekDay

	/** \brief Conversion and range checking function. Convert \c unsigned value to the TWeekDay
	 *  \param[in]	aDayNum		Number of day
	 *  \return Return TWeekDay value
	 *  \attention Method generate \c std::range_error exception if argument \a aDayNum is out of numbers of the day
	 */
	TWeekDay CheckRangeWithException(const unsigned aDayNum);

	/** \brief Conversion Day number to the Day name
	 *  \param[in]	aWeekDay	Day enumeration
	 *  \return Return Day name
	 */
	const char* TWeekStringName(TWeekDay aWeekDay);

	/** \brief Output to the stream operator. (\em serialization)
	 *  \param[in]	aOStream	Output stream
	 *  \param[in]	aWeekDay	Serialized instantion of TWeekDay
	 *  \return Return \c std::ostream with serialized aWeekDay
	 */
	std::ostream& operator<<(std::ostream& aOStream, const TWeekDay& aWeekDay);

	/** \brief Input from the stream operator. (\em deserialization)
	 *  \param[in]	aIStream	Input stream
	 *  \param[out]	aWeekDay	Place for deserialized instantion of TWeekDay
	 *  \return Return rest of \c std::istream
	 *  \attention Method generate \c std::range_error exception if stream doesn't contains correct name of the day
	 *  \attention Method generate \c std::runtime_error exception if stream isn't in good state
	 */
	std::istream& operator>>(std::istream& aIStream, TWeekDay& aWeekDay);

	
	/** \brief CValue class (\c TWeekDay variant)
	 *  \details Definition of CValue class (\c TWeekDay variant). There is defined all common methods and attributes.
	 */
	class CValue
		{
		ClassInfo<CValue> iInstanceInfo;	///< Instance of the class info for usage statistics
		enum TWeekDay iValue;	///< Encapsulated \c enum TWeekDay value

	public:
	// c'tors
		/** \brief Implicit c'tor
		 *  \details Value attributes is set to \c EMonday.
		 */
		CValue(): iValue(CheckRangeWithException(EMonday))
			{}

		/** \brief Conversion c'tor
		 *  \details Pointer attributes are initialised to the \c this value.
		 *  \param[in]	aValue New TWeekDay value
		 *  \attention Method generate \c std::range_error exception if parameters \p aValue is out of the \c enum TWeekDay range.
		 */
		explicit CValue(const enum TWeekDay aValue): iValue(CheckRangeWithException(aValue))
			{}

		/** \brief Copy c'tor
		 *  \details Create new instance by copying only \p iValue parameter.
		 *  \param[in]	aValue	Original instance for copying
		 */
		CValue(const CValue& aValue): iValue(aValue.Value()) 
			{}

		/** \brief String conversion c'tor
		 *  \details Create new instance from Value in the string. Pointer attributes are initialised to the \c this value.
		 *  \param[in] aStr Plain C string with string value convertable to the TWeekDay value
		 */
		explicit CValue(const char* aStr): iValue(EMonday)
			{std::istringstream iss(aStr, std::istringstream::in); iss >> iValue;}

	// d'tor
		/** \brief Virtual d'tor
		 */
		virtual ~CValue()
			{iValue = EMonday;}

	// InstanceInfo getters
		/** \brief ID getter
		 *  \return Unique instance ID
		 */
		size_t ID() const
			{return(iInstanceInfo.ID());}

	// setter/getter
		/** \brief Value setter
		 *  \param[in]	aValue	New Value
		 *  \attention Method generate \c std::range_error exception if parameters \p aValue is out of the \c enum TWeekDay range.
		 */
		void SetValue(const TWeekDay aValue)
			{iValue = CheckRangeWithException(unsigned(aValue));}

		/** \brief Value getter
		 *  \return Actual \c bool \p Value
		 */
		TWeekDay Value() const
			{return(iValue);}

	// operators
		/** \brief Complement operator
		 *  \return CValue instance with complemented attribute Value.
		 */
		CValue operator-() const
			{unsigned tmp = unsigned(ESunday) - unsigned(Value());  return(CValue(TWeekDay(tmp)));}

		/** \brief Assigment operator
		 *  \return CValue instance with copied attribute Value.
		 */
		CValue& operator=(const CValue& aValue)
			{SetValue(aValue.Value());return(*this);}

		/** \brief Comparing by Value operator
		 *  \return Return \c bool result of comparation
		 */
		bool operator==(const CValue& aValue) const
			{return(iValue == aValue.Value());}

		/** \brief Comparing by Value operator
		 *  \return Return \c bool result of comparation
		 */
		bool operator!=(const CValue& aValue) const
			{return(iValue != aValue.Value());}

		/** \brief Comparing by Value operator
		 *  \return Return \c bool result of comparation
		 */
		bool operator<(const CValue& aValue) const
			{return(iValue < aValue.Value());}

		/** \brief Comparing by Value operator
		 *  \return Return \c bool result of comparation
		 */
		bool operator>(const CValue& aValue) const
			{return(iValue > aValue.Value());}

		/** \brief Output to the stream operator. (\em serialization)
		 *  \param[in]	aOStream	Output stream
		 *  \param[in]	aValue	Serialized instantion of CValue
		 *  \return Return \c std::ostream with serialized Value
		 */
		friend std::ostream& operator<<(std::ostream& aOStream, const CValue& aValue)
			{aOStream << aValue.Value(); return(aOStream);}

		/** \brief Input from the stream operator. (\em deserialization)
		 *  \param[in]	aIStream	Input stream
		 *  \param[out]	aValue	Place for deserialized instantion of CValue
		 *  \return Return rest of \c std::istream
		 */
		friend std::istream& operator>>(std::istream& aIStream, CValue& aValue)
			{aIStream >> aValue.iValue; return(aIStream);}

#ifdef CVALUE_TEST_API
	// constants for testing CValue functionality

		/** \brief First test value
		 *  \return Return TWeekDay value (EMonday)
		 *  \note Useful for automated testing of CValue functionality
		 */
		static TWeekDay TestValue0()
			{return(EMonday);}

		/** \brief First test string value
		 *  \return Return string with TWeekDay value (EMonday)
		 *  \note Useful for automated testing of CValue functionality
		 */
		static const char* TestStringValue0()
			{return("(Monday)");}

		/** \brief Second test value
		 *  \return Return TWeekDay value (ETuesday)
		 *  \note Useful for automated testing of CValue functionality
		 */
		static TWeekDay TestValue1()
			{return(ETuesday);}

		/** \brief Second test string value
		 *  \return Return string with TWeekDay value (ETuesday)
		 *  \note Useful for automated testing of CValue functionality
		 */
		static const char* TestStringValue1()
			{return("(Tuesday)");}

		/** \brief Random test value
		 *  \return Return random TWeekDay value
		 *  \note Useful for automated testing of CValue functionality
		 */
		static TWeekDay TestValueRandom()
			{return(CheckRangeWithException(std::rand() % KTWeekDaysCount));}

		/** \brief Random test string value
		 *  \return Return string with random TWeekDay value
		 *  \note Useful for automated testing of CValue functionality
		 */
		static const char* TestStringValueRandom()
			{return(TWeekStringName(TestValueRandom()));}

        /** \brief Test string values
        *  \return Return string with \c TWeekDay values
        *  \note Useful for automated testing of CValue functionality
        */
        static const char* TestStringValues()
        {
            return("[(Monday),(Tuesday),(Wednesday)]");
        }

#endif /* CValue_TEST_VALUES */

		}; /* class CValue */

	} /* namespace CValue_TWeekDay */

#endif /* __CVALUE_TWEEKDAY_H__ */
