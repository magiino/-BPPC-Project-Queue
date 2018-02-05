#ifndef __CVALUE_LONG_H__
#define __CVALUE_LONG_H__
/** \file CValue_long.h
*  \brief CValue_long class header
*  \details File contain CValue_long::CValue definition.
*  \warning Don't modify this file
*  \author Marek Mag�th 2017
*/

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <typeinfo>
#include <limits>
#include "ClassInfo.h"

#include "check.h"

/** \brief Namespace for encapsulating of \c long variant of CValue class
*  \details For selecting this variant of CValue class uncomment \c using \c namespace section in the CValue.h
*/
namespace CValue_long
{
    /** \brief CValue class (\c long variant)
    *  \details Definition of CValue class (\c long variant). There is defined all common methods and attributes.
    */
    class CValue
    {
        ClassInfo<CValue> iInstanceInfo;	///< Instance of the class info for usage statistics
        long iValue; ///< Encapsulated \c long value

    public:
        // c'tors
        /** \brief Implicit c'tor
        *  \details Value attributes is set to \c minimal value of long.
        */
        CValue() : iValue(std::numeric_limits<long>::min())
        {}

        /** \brief Conversion c'tor
        *  \details Pointer attributes are initialised to the \c this value.
        *  \param[in]	aValue New encapsulated \c long Value
        */
        explicit CValue(const long aValue) : iValue(aValue)
        {}

        /** \brief Copy c'tor
        *  \details Create new instance by copying only \p iValue parameter.
        *  \param[in]	aValue	Original instance for copying
        */
        CValue(const CValue& aValue) : iValue(aValue.Value())
        {}

        /** \brief String conversion c'tor
        *  \details Create new instance from Value in the string. Pointer attributes are initialised to the \c this value.
        *  \param[in] aStr Plain C string with long value.
        */
        explicit CValue(const char* aStr): iValue(0)
        {
            // toto je kontrola ci prislo samotne cislo v stringu alebo cislo v stringu ktore je v zatvorkach (-216454564) .. tieto zatvorky musime odfiltrovat
            char ch;
            std::istringstream iss(aStr, std::istringstream::in);
            ch = iss.peek();
            if (ch == '(') {
                iss >> *this;
            }
            else {
                char* pEnd;
                iValue = strtol(aStr, &pEnd, 10);
            }

        }

        // d'tor
        /** \brief Virtual d'tor
        */
        virtual ~CValue() noexcept(false)
        {
            iValue = 0;
        }

        // InstanceInfo getters
        /** \brief ID getter
        *  \return Unique instance ID
        */
        size_t ID() const
        {
            return(iInstanceInfo.ID());
        }

        // setter/getter
        /** \brief Value setter
        *  \param[in]	aValue	New Value
        */
        void SetValue(const long aValue)
        {
            iValue = aValue;
        }

        /** \brief Value getter
        *  \return Actual \c long \p Value
        */
        long Value() const
        {
            return(iValue);
        }

        // operators
        /** \brief Complement operator
        *  \return CValue instance with complemented attribute Value.
        */
        CValue operator-() const
        {
            return(CValue(~this->iValue));
        }

        /** \brief Assigment operator
        *  \return CValue instance with copied attribute Value.
        */
        CValue& operator=(const CValue& aValue)
        {
            SetValue(aValue.Value());
            return(*this);
        }

        /** \brief Comparing by Value operator
        *  \return Return \c bool result of comparation
        */
        bool operator==(const CValue& aValue) const
        {
            return(iValue == aValue.Value());
        }

        /** \brief Comparing by Value operator
        *  \return Return \c bool result of comparation
        */
        bool operator!=(const CValue& aValue) const
        {
            return(iValue != aValue.Value());
        }

        /** \brief Comparing by Value operator
        *  \return Return \c bool result of comparation
        */
        bool operator<(const CValue& aValue) const
        {
            return(iValue < aValue.Value());
        }

        /** \brief Comparing by Value operator
        *  \return Return \c bool result of comparation
        */
        bool operator>(const CValue& aValue) const
        {
            return(iValue > aValue.Value());
        }

        /** \brief Output to the stream operator. (\em serialization)
        *  \param[in]	aOStream	Output stream
        *  \param[in]	aValue	Serialized instantion of CValue
        *  \return Return \c std::ostream with serialized Value
        */
        friend std::ostream& operator<<(std::ostream& aOStream, const CValue& aValue)
        {
            aOStream << "(" << aValue.Value() << ")";
            return aOStream;
        }

        /** \brief Input from the stream operator. (\em deserialization)
        *  \param[in]	aIStream	Input stream
        *  \param[out]	aValue	Place for deserialized instantion of CValue
        *  \return Return rest of \c std::istream
        */
        friend std::istream& operator>>(std::istream& aIStream, CValue& aValue)
        {
            char ch = '\0';
            aIStream >> ch;
            if (!aIStream.good() || ch != '(')
                throw std::runtime_error("Input stream data integrity error! Missing (");

            aIStream >> aValue.iValue;

            aIStream >> ch;
            if (!aIStream.good() || ch != ')')
                throw std::runtime_error("Input stream data integrity error! Missing )");

            return aIStream;
        }

#ifdef CVALUE_TEST_API
        // constants for testing CValue functionality

        /** \brief First test value
        *  \return Return \c long value (\c max long)
        *  \note Useful for automated testing of CValue functionality
        */
        static long TestValue0()
        {
            return(std::numeric_limits<long>::min());
        }

        /** \brief First test string value
        *  \return Return string with \c long value (\c Min value)
        *  \note Useful for automated testing of CValue functionality
        */
        static const char* TestStringValue0()
        {
            return("(-2147483648)");
        }

        /** \brief Second test value
        *  \return Return \c long value (\c Min long)
        *  \note Useful for automated testing of CValue functionality
        */
        static long TestValue1()
        {
            return(std::numeric_limits<long>::max());
        }

        /** \brief Second test string value
        *  \return Return string with \c long value (\c 2147483647)
        *  \note Useful for automated testing of CValue functionality
        */
        static const char* TestStringValue1()
        {
            return("(2147483647)");
        }

        /** \brief Random test value
        *  \return Return random \c long value of RAND_MAX = 32767
        *  \note Useful for automated testing of CValue functionality
        */
        static long TestValueRandom()
        {   //  32767 is RAND_MAX constant
            return(std::rand() % 32767);
        }

        /** \brief Random test string value
        *  \return Return string with random \c long value
        *  \note Useful for automated testing of CValue functionality
        */
        static const char* TestStringValueRandom()
        {
            return((TestValueRandom() < TestValue0()) ? TestStringValue0() : TestStringValue1());
        }

#endif /* CVALUE_TEST_API */

    }; /* class CValue */

} /* namespace CValue_long */

#endif /* __CVALUE_LONG_H__ */
