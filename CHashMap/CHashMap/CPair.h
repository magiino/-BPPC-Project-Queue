#ifndef __CPAIR_H__
#define __CPAIR_H__
/** \file CPair.h
 *  \brief CPair class header
 *  \details File contain CPair class (key and value) definition.
 *  \warning Don't modify this file
 *  \author Pety 2017
 *  \version $Revision: 1763 $
 *	$Id: CPair.h 1763 2017-12-11 15:25:59Z xkunaj01 $
 */

#include <iostream>
#include "CValue.h"
#include "ClassInfo.h"
#include "check.h"

/** \brief CPair class (key and value)
 *  \details Definition of CPair class (key and value). There is defined all common methods and member variables.
 */
class CPair
	{
	public:
		using TKey = int;

	private:
		const TKey iKey;	///< Key const member variable (must be const because it disable implicit generation of assigment operators)
		CValue iValue;		///< Value member variable
		ClassInfo<CPair> iInstanceInfo;		///< Instance of the class info for usage statistics
	
		/** \brief Deserialization helper for string conversion c'tor
		 *  \details Deserialization static helper method for string conversion c'tor needed for initialization of const \p iKey value
		 *  \param[in] aStr Plain C string with values in the format convertable to the CPair
		 *  \param[in,out] aValue Store to the \a aValue value parsed from C string
		 *  \return New key parsed from C string
		 *  \attention Method generate \c std::invalid_argument exception if \a aStr is not in the proper format.
		 */
		static TKey Deserialize(const char *aStr, CValue &aValue);

		/** \brief Private explicit conversion c'tor help to correct functionality of string conversion c'tor
		 *  \param[in] aStr Plain C string with values in the format convertable to the CPair
		 *  \param[in] aTmpValue Implicitly preconstructed instance of CValue
		 */
		explicit CPair(const char *aStr, CValue aTmpValue): iKey(Deserialize(aStr, aTmpValue)), iValue(aTmpValue)
			{}

	public:
		/** \brief Conversion c'tor
		 *  \details Initialize member variables iKey, iValue
		 *  \param[in] aKey New key value
		 *  \param[in] aValue New value
		 */
		CPair(TKey aKey, const CValue& aValue): iKey(aKey), iValue(aValue)
			{}

		/** \brief String conversion c'tor
		 *  \details Create new instance from key and value in the string.
		 *  \param[in] aStr Plain C string with values in the format convertable to the CPair
		 *  \attention Method generate \c std::invalid_argument exception if \a aStr is not in the proper format.
		 */
		CPair(const char *aStr): CPair(aStr, CValue())
			{}

		/** \brief Key getter
		 *  \return Actual \p iKey
		 */
		TKey Key() const
			{ return iKey; }

		/** \brief Key getter
		 *  \return Actual \p iValue
		 */
		CValue Value() const
			{ return iValue; }

		/** \brief Value setter
		 *  \param[in] aValue New Value
		 */
		void SetValue(const CValue& aValue)
			{ iValue = aValue; }

		/** \brief Output to the stream operator. (\em serialization)
		 *  \param[in] aOstr Output stream
		 *  \param[in] aPair Instantion of CPair for serialization
		 *  \return Return \c std::ostream with serialized CPair values
		 */
		friend std::ostream& operator<<(std::ostream& aOstr, const CPair& aPair)
			{ return aOstr << "(#" << aPair.iKey << ',' << aPair.iValue << ')'; }
	
		/** \brief InstanceInfo ID getter
		 *  \return Unique instance ID
		 */
		size_t ID() const
			{ return(iInstanceInfo.ID()); }

	}; /* class CPair */

#endif /* __CPAIR_H__ */
