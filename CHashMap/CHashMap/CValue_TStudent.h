#ifndef __CVALUE_TSTUDENT_H__
#define __CVALUE_TSTUDENT_H__
/** \file CValue_TStudent.h
*  \brief CValue_TStudent class header
*  \details File contain CValue_TStudent::CValue definition.
*  $Id: CValue_TStudent.h 1215 2017-12-04 18:30:13Z xlevri01 $
*/

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <typeinfo>
#include "ClassInfo.h"

#include "check.h"

/** \brief Namespace for encapsulating of \c TStudent variant of CValue class
*  \details For selecting this variant of CValue class uncomment \c using \c namespace section in the CValue.h
*/
namespace CValue_TStudent
{
    /** \brief Basic definition of struct type for representing day of week.
    */
    struct TStudent {
        char* iFirstName;
        char* iLastName;
        int iVutID;

        TStudent(char* aFisrtName, char* aLastName, int aVutID) {
            iFirstName = aFisrtName;
            iLastName = aLastName;
            iVutID = aVutID;
        }

        bool operator == (const TStudent& aStudent) {
            return (iVutID == aStudent.iVutID);
        }

        bool operator !=(const TStudent& aStudent) {
            return (iVutID != aStudent.iVutID);
        }

        bool operator <(const TStudent& aStudent) {
            return (iVutID < aStudent.iVutID);
        }

        bool operator >(const TStudent& aStudent) {
            return (iVutID > aStudent.iVutID);
        }
    };


    /** \brief Output to the stream operator. (\em serialization)
    *  \param[in]	aOStream	Output stream
    *  \param[in]	aStudent	Serialized instantion of TStudent
    *  \return Return \c std::ostream with serialized aStudent
    */
    std::ostream& operator<<(std::ostream& aOStream, const TStudent& aStudent);

    /** \brief Input from the stream operator. (\em deserialization)
    *  \param[in]	aIStream	Input stream
    *  \param[out]	aStudent	Place for deserialized instantion of TStudent
    *  \return Return rest of \c std::istream
    *  \attention Method generate \c std::range_error exception if stream doesn't contains correct name of the day
    *  \attention Method generate \c std::runtime_error exception if stream isn't in good state
    */
    std::istream& operator>>(std::istream& aIStream, TStudent& aStudent);


    /** \brief CValue class (\c TStudent variant)
    *  \details Definition of CValue class (\c TStudent variant). There is defined all common methods and attributes.
    */
    class CValue
    {
        ClassInfo<CValue> iInstanceInfo;	///< Instance of the class info for usage statistics
        TStudent iValue;	///< Encapsulated \c struct TStudent value

    public:
        // c'tors
        /** \brief Implicit c'tor
        */
        CValue() : iValue(TStudent(" "," ",0))
        {}

        /** \brief Conversion c'tor
        *  \details Pointer attributes are initialised to the \c this value.
        *  \param[in]	aValue New TStudent value
        */
        explicit CValue(const TStudent aValue): iValue(aValue)
        {}

        /** \brief Copy c'tor
        *  \details Create new instance by copying only \p iValue parameter.
        *  \param[in]	aValue	Original instance for copying
        */
        CValue(const CValue& aValue) : iValue(aValue.Value())
        {}

        /** \brief String conversion c'tor
        *  \details Create new instance from Value in the string. Pointer attributes are initialised to the \c this value.
        *  \param[in] aStr Plain C string with string value convertable to the TStudent VutID value.
        */
        explicit CValue(const char* aStr): iValue(TStudent(" ", " ", 0))
        {
            std::istringstream iss(aStr, std::istringstream::in);
            iss >> iValue.iVutID;
        }

        // d'tor
        /** \brief Virtual d'tor
        */
        virtual ~CValue()
        {
            iValue = TStudent("","",-1);
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
        void SetValue(const TStudent aValue)
        {
            iValue = aValue;
        }

        /** \brief Value getter
        *  \return Actual \c bool \p Value
        */
        TStudent Value() const
        {
            return(iValue);
        }

        // operators
        /** \brief Complement operator
        *  \return CValue instance with complemented attribute Value.
        */
        CValue operator-() const
        {
            int tmp = ~iValue.iVutID;

            return(CValue(TStudent("","", tmp)));
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
            return(iValue.iVutID == aValue.Value().iVutID);
        }

        /** \brief Comparing by Value operator
        *  \return Return \c bool result of comparation
        */
        bool operator!=(const CValue& aValue) const
        {
            return(iValue.iVutID != aValue.Value().iVutID);
        }

        /** \brief Comparing by Value operator
        *  \return Return \c bool result of comparation
        */
        bool operator<(const CValue& aValue) const
        {
            return(iValue.iVutID < aValue.Value().iVutID);
        }

        /** \brief Comparing by Value operator
        *  \return Return \c bool result of comparation
        */
        bool operator>(const CValue& aValue) const
        {
            return(iValue.iVutID > aValue.Value().iVutID);
        }

        /** \brief Output to the stream operator. (\em serialization)
        *  \param[in]	aOStream	Output stream
        *  \param[in]	aValue	Serialized instantion of CValue
        *  \return Return \c std::ostream with serialized Value
        */
        friend std::ostream& operator<<(std::ostream& aOStream, const CValue& aValue)
        {
            aOStream << aValue.Value().iVutID << ' ';
            return(aOStream);
        }

        /** \brief Input from the stream operator. (\em deserialization)
        *  \param[in]	aIStream	Input stream
        *  \param[out]	aValue	Place for deserialized instantion of CValue
        *  \return Return rest of \c std::istream
        */
        friend std::istream& operator>>(std::istream& aIStream, CValue& aValue)
        {
            aIStream >> aValue.iValue.iVutID;
            return(aIStream);
        }

#ifdef CVALUE_TEST_API
        // constants for testing CValue functionality

        /** \brief First test value
        *  \return Return TWeekDay value (Student0)
        *  \note Useful for automated testing of CValue functionality
        */
        static TStudent TestValue0()
        {
            return(TStudent("Student0", "", 0));
        }

        /** \brief First test string value
        *  \return Return string - "0"
        *  \note Useful for automated testing of CValue functionality
        */
        static const char* TestStringValue0()
        {
            return("0");
        }

        /** \brief Second test value
        *  \return Return TStudent value (Student1)
        *  \note Useful for automated testing of CValue functionality
        */
        static TStudent TestValue1()
        {
            return(TStudent("Student1", "", 1));
        }

        /** \brief Second test string value
        *  \return Return string - "1"
        *  \note Useful for automated testing of CValue functionality
        */
        static const char* TestStringValue1()
        {
            return("1");
        }

        /** \brief Random test value
        *  \return Return random TStudent value
        *  \note Useful for automated testing of CValue functionality
        */
        static TStudent TestValueRandom()
        {
            return(TStudent("Random","",std::rand() % 10000));
        }

        /** \brief Random test string value
        *  \return Return string with random TStudent value
        *  \note Useful for automated testing of CValue functionality
        */
        static const char* TestStringValueRandom()
        {
            int random = std::rand() % 10000;
            if (random < 5000) {
                return(TestValue0().iFirstName);
            }
            else {
                return(TestValue1().iFirstName);
            }
            
        }

#endif /* CValue_TEST_VALUES */

    }; /* class CValue */

} /* namespace CValue_TStudent */

#endif /* __CVALUE_TSTUDENT_H__ */
