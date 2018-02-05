#ifndef __CVALUE_BOOL_H__
#define __CVALUE_BOOL_H__
/** \file CValue_bool.h
 *  \brief CValue_bool class header
 *  \details File contain CValue_bool::CValue definition.
 *  \warning Don't modify this file
 *  \author Pety 2017
 *  $Id: CValue_bool.h 3 2017-11-06 10:03:34Z petyovsky $
 */

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <typeinfo>
#include "ClassInfo.h"

#include "check.h"

/** \brief Namespace for encapsulating of \c bool variant of CValue class
 *  \details For selecting this variant of CValue class uncomment \c using \c namespace section in the CValue.h
 */
namespace CValue_bool
	{
	/** \brief CValue class (\c bool variant)
	 *  \details Definition of CValue class (\c bool variant). There is defined all common methods and attributes.
	 */
	class CValue 
		{
		ClassInfo<CValue> iInstanceInfo;	///< Instance of the class info for usage statistics
		bool iValue; ///< Encapsulated \c bool value

	public:
	// c'tors
		/** \brief Implicit c'tor
		 *  \details Value attributes is set to \c false. 
		 */
		CValue(): iValue(false)
			{}

		/** \brief Conversion c'tor
		 *  \details Pointer attributes are initialised to the \c this value.
		 *  \param[in]	aValue New encapsulated \c bool Value
		 */
		explicit CValue(const bool aValue): iValue(aValue)
			{}

		/** \brief Copy c'tor
		 *  \details Create new instance by copying only \p iValue parameter. 
		 *  \param[in]	aValue	Original instance for copying
		 */
		CValue(const CValue& aValue): iValue(aValue.Value())
			{}

		/** \brief String conversion c'tor
		 *  \details Create new instance from Value in the string. Pointer attributes are initialised to the \c this value.
		 *  \param[in] aStr Plain C string with value "0" or "1"
		 */
		explicit CValue(const char* aStr): iValue(false)
			{std::istringstream iss(aStr, std::istringstream::in); iss >> std::boolalpha >> iValue;}

	// d'tor
		/** \brief Virtual d'tor
		 */
		virtual ~CValue() noexcept(false)
			{iValue = false;}

	// InstanceInfo getters
		/** \brief ID getter
		 *  \return Unique instance ID
		 */
		size_t ID() const
			{return(iInstanceInfo.ID());}

	// setter/getter
		/** \brief Value setter
		 *  \param[in]	aValue	New Value
		 */
		void SetValue(const bool aValue)
			{iValue = aValue;}

		/** \brief Value getter
		 *  \return Actual \c bool \p Value
		 */
		bool Value() const
			{return(iValue);}

	// operators
		/** \brief Complement operator
		 *  \return CValue instance with complemented attribute Value.
		 */
		CValue operator-() const
			{return(CValue(!iValue));}

		/** \brief Assigment operator
		 *  \return CValue instance with copied attribute Value.
		 */
		CValue& operator=(const CValue& aValue)
			{SetValue(aValue.Value()); return(*this);}

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
			{
			std::ios_base::fmtflags fmtflags = aOStream.setf(std::ios_base::boolalpha); // Save the state of the boolalpha flag & set it
			aOStream << aValue.Value();
			aOStream.flags(fmtflags); 	// restore previous flags
			return aOStream;
			}

		/** \brief Input from the stream operator. (\em deserialization)
		 *  \param[in]	aIStream	Input stream
		 *  \param[out]	aValue	Place for deserialized instantion of CValue
		 *  \return Return rest of \c std::istream
		 */
		friend std::istream& operator>>(std::istream& aIStream, CValue& aValue)
			{
			std::ios_base::fmtflags fmtflags = aIStream.setf(std::ios_base::boolalpha); // Save the state of the boolalpha flag & set it
			aIStream >> aValue.iValue;
			aIStream.flags(fmtflags); 	// restore previous flags
			return aIStream;
			}

#ifdef CVALUE_TEST_API
	// constants for testing CValue functionality

		/** \brief First test value
		 *  \return Return \c bool value (\c false)
		 *  \note Useful for automated testing of CValue functionality
		 */
		static bool TestValue0()
			{return(false);}

		/** \brief First test string value
		 *  \return Return string with \c bool value (\c false)
		 *  \note Useful for automated testing of CValue functionality
		 */
		static const char* TestStringValue0()
			{return("false");}

		/** \brief Second test value
		 *  \return Return \c bool value (\c true)
		 *  \note Useful for automated testing of CValue functionality
		 */
		static bool TestValue1()
			{return(true);}

		/** \brief Second test string value
		 *  \return Return string with \c bool value (\c true)
		 *  \note Useful for automated testing of CValue functionality
		 */
		static const char* TestStringValue1()
			{return("true");}

		/** \brief Random test value
		 *  \return Return random \c bool value
		 *  \note Useful for automated testing of CValue functionality
		 */
		static bool TestValueRandom()
			{return((std::rand() % 2) != 0);}

		/** \brief Random test string value
		 *  \return Return string with random \c bool value
		 *  \note Useful for automated testing of CValue functionality
		 */
		static const char* TestStringValueRandom()
			{return(TestValueRandom() ? TestStringValue1(): TestStringValue0());}

#endif /* CVALUE_TEST_API */

		}; /* class CValue */

	} /* namespace CValue_bool */

#endif /* __CVALUE_BOOL_H__ */
