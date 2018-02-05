#ifndef __CFRONTA_H__
#define __CFRONTA_H__
/** \file CFronta.h
 *  \brief CFronta class header
 *  \details File contain CContainer class container definition.
 *  \authors
 *  \version $Revision: 3358 $
 *  $Id: CFronta.h 3358 2018-01-02 00:36:48Z xmagat01 $
 */

#include "CHashMap.h"
#include "CPair.h"
#include "ClassInfo.h"
#include "check.h"
#include <string>

/** \bugfix[Zad] Znacna cast tohoto souboru je opisem jineho projektu. Pracujte samostatne. Pokud se to bude opakovat, budete mit z celeho projektu nulu!!! // [xmagat01,xlevri01,xkunaj01]*/

 /** \bugfix[Zad] Chybi metody podle zadani - napriklad static, ... // metody doplnene [xmagat01,xlevri01,xkunaj01] */

/** \brief CHashMap class definition
*   \details Definition of CFronta class. There is defined all common methods and member variables.
*/
class CFronta
{
private:
    ClassInfo<CFronta> iInstanceInfo;         ///< Instance of the class info for usage statistics.
    int iFront;                               ///< Index of element which is at front of HashMap (first added).
    int iBack;                                ///< Index of element which is at the end of HashMap (last added).
	CHashMap iMap;                            ///< CHasmap where are stored CValues.

    // Private methods
    /** \brief This method compare two instances of CFronta by number of CValue.
	*   \param[in]   aFronta Fronta for comparing.
	*   \return Return -1 if this have less CValue then aFronta, 1 if this have more CValue then aFronta and 0 if equal.
    *   \author xkunaj01
	*/
	int Compare(const CFronta &aFronta) const;
	/** \bugfix[Zad] Funkcionalita metod compare je dana zadanim.//opravene [xkunaj01]  */

	/** \brief This method compare two instances of CFronta by sum of all CValues.
	*   \param[in]   aFronta Fronta for comparing.
	*   \return Return -1 if sum of this CValue values is less then sum of CValue values, 1 if sum of this CValue values is more then sum of CValue values, 0 if equal.
    *   \author xkunaj01
	*/
	int DeepCompare(const CFronta &aFronta) const;


public:
    // c'tors
	/** \brief Implicit c'tor
	*   \details Value attributes are set to \c default values of data type.
    *   \author xkunaj01
	*/
	CFronta() : iFront(0), iBack(0), iMap(CHashMap()) {}

	/** \brief Conversion c'tor
	*  \details Creates new instance of CFronta and set \c aValue as first element.
	*  \param[in]   aValue First element of Queue.
    *  \author xkunaj01
	*/
    CFronta(const CValue& aValue);

    /** \brief Copy c'tor
    *   \details Create new instance of CFronta by copying all \p elemnts of aFronta.
    *   \param[in]	aFronta	Original instance for copying.
    *   \author xlevri01
    */
    CFronta(const CFronta& aFronta) : iFront(aFronta.iFront), iBack(aFronta.iBack), iMap(aFronta.iMap) {}

    /** \brief Set BucketTableSize C'tor
    *   \details Create new instance of CFronta with empty CValues.
    *   \param[in] aNumberOfElements This parameter define number of new empty elements in CFronta.
    *   \author xlevri01
    */
    CFronta(const int &aNumberOfElements);

    /** \brief CValues array C'tor
    *   \details Create new instance of CFronta, and will fill it with CValues from input. First CValue will be at index 0 and last on index size.
    *   \param[in] aValues Array of CValues.
    *   \param[in] aLength Length of input array, which holds CValues.
    *   \author xmagat01
    */
    CFronta(CValue *aValues, const int &aLength);

    /** \brief String C'tor
    *   \details Create new instance of CFront, and from input string will create new CValues and push it to HashMap.
    *   \param[in] aStr CValues values in string. etc. CValue long "[(95662125),(25554455),(335847441)]"
    *   \author xmagat01
    */
    CFronta(const char* aStr);

	// d'tor
	/** \brief d'tor
	*	\details Will free all alocated memory in HashMap, and destroys HashMap and set default data types to default values.
    *   \author xmagat01
	*/
    ~CFronta() noexcept(false) {
        iMap.Clear();
        iFront = -1;
        iBack = -1;
    }

    // InstanceInfo getters
    /** \brief ID getter.
    *   \return Unique instance ID.
    *   \author xkunaj01
    */
    size_t ID() const {
        return(iInstanceInfo.ID());
    }

    // Stream operators
    /** \brief Output to the stream operator. (\em serialization)
    *   \param[in]	aOStream	Output stream
    *   \param[in]	aFronta	Serialized instantion of CFronta
    *   \return Return \c std::ostream with serialized Value
    *   \author xmagat01
    */
    friend std::ostream& operator<<(std::ostream& aOStream, const CFronta& aFronta);

    /** \brief Input from the stream operator. (\em deserialization)
    *  \param[in]	aIStream	Input stream
    *  \param[out]	aFronta	Place for deserialized instantion of CFronta
    *  \return Return rest of \c std::istream
    *   \author xmagat01
    */
    friend std::istream& operator>>(std::istream& aIStream, CFronta& aFronta);

    //operators

    //Unárne operátory
    /** \brief Prefix - operator (-A)
    *   \details Reverts order of elements.
    *   \return New CFronta instance with reverted order of elements.
    *   \author xkunaj01
    */
    CFronta operator-() const;
	/** \bugfix[Zad] Promyslet navrat pomoci reference u operator- (i dalsich). //  unarny operator - vytvory novu frontu s poprehadzovanymi prvkami [xkunaj01,xmagat01]*/

    /** \brief Prefix ++ operator (++A)
    *   \details Copy last element and paste it to last position of CFronta.
    *   \return CFronta instance with doubled last element.
    *   \author xkunaj01
    */
    CFronta& operator++();
	/** \bugfix[Zad] Kdyz je definovan jeden operator ++ (prefex nebo postfix) musi byt definovan i druhy.// prekladac nic nekrici tak je to ok (konzultovane s cviciacim) [xkunaj01,xmagat01,xlevri01] */

    /** \brief Prefix -- operator (--A)
    *   \details Delete last element of CFronta.
    *   \return CFronta instance without last element.
    *   \author xkunaj01
    */
    CFronta& operator--();

    /** \brief Prefix ~ operator (~A)
    *   \details Flip first element with last one.
    *   \return CFronta instance with fliped last and fisrt element.
    *   \author xkunaj01
    */
    CFronta operator~() const;
	/** \bugfix[Zad] Jak vymìní první a posledni element, kdyz razeni je podle klice? // tento operator vrati novu Frontu s vymenenym prvym prvkom za posledny. [xkunaj01]*/

    //Logické operátory
    /** \brief Comparing two CFronty by number of elements.
    *   \return Return \c bool result of comparation.
    *   \author xlevri01
    */
    bool operator==(const CFronta& aFronta) const;

    /** \brief Comparing two CFronty by number of elements.
    *   \return Return \c bool result of comparation.
    *   \author xlevri01
    */
    bool operator!=(const CFronta& aFronta) const;

    /** \brief Comparing two CFronty by number of elements.
    *   \return Return \c bool result of comparation.
    *   \author xlevri01
    */
    bool operator<(const CFronta& aFronta) const;

    /** \brief Comparing two CFronty by number of elements.
    *   \return Return \c bool result of comparation.
    *   \author xlevri01
    */
    bool operator>(const CFronta& aFronta) const;

    //Binárne operátory
    /** \brief Plus-equal operator
    *   \details A+=B, takes elements from B and add it to back of CFronta A.
    *   \return Return CFronta \c instance with new ellements added to back.
    *   \author xmagat01
    */
    CFronta& operator+=(const CFronta& aFronta);

    /** \brief Plus operator 
    *   \details A+B ; A`=Aelements+Belements.
    *   \return New CFronta instance with elements from A and B attribute Value.
    *   \author xmagat01
    */
    CFronta operator+(const CFronta& aFronta) const;

    /** \brief Minus operator
    *   \details A-B ; A`= Belements + Aelements.
    *   \return New CFronta instance with elements from A and B attribute Value.
    *   \author xmagat01
    */
    CFronta operator-(const CFronta& aFronta) const;
	/** \bugfix[Zad] Proc je minus definovano stejne jako plus? // Neni definovane rovnako, rozdiel je na aku stranu sa pridavaju prvky [xmagat01]*/

    /** \brief Assignment operator. 
    *   \details A = B , this operator delete all elements of A and copy new elements from B.
    *   \return Return CFronta \c instance with new (Copyied) CValues.
    *   \author xmagat01
    */
    CFronta& operator=(const CFronta& aFronta);

    /** \brief CFronta conversion operator
    *   \return Operator returns \c true when fronta is not empty returns \c false
    *   \author xmagat01
    */
    operator bool() const {
        return bool(Length() > 0);
    }

    // Neèlenský operátor 
    /** \brief CFronta nonmember operator
    *   \details This operator add CValue to CFronta.
    *   \return Return new CFronta with added CValue.
    *   \author xlevri01
    */
	friend CFronta operator+(const CValue aValue, const CFronta aFronta);
	
	/** \bugfix[Zad] Dorobeny neclensky a konverzni operator. [xlevri01, xmagat01] */

    // Public methods for CFronta which are used for manipulating with Nodes.
    /** \brief Push new CValue to end of CFronta.
	*	\param[in] aValue
    *   \author xmagat01
    */
    void EnQueue(const CValue &aValue);

    /** \brief Take out first CValue from CFronta and remove it from CFronta.
    *   \return CValue object if pick up run correctly, empty CValue if Fronta is empty
    *   \author xmagat01
    */
    CValue DeQueue();

	/** \brief Take out first CValue from CFronta but do not remove it from CFronta. (not copy!)
	*   \return CValue if pick up run correctly, empty CValue if CFronta is empty.
    *   \author xlevri01
	*/
    CValue Front() const;

	/** \brief Take out last CValue from CFronta but do not remove it from CFronta. (not copy!)
	*   \return CValue if pick up run correctly, empty CValue if CFronta is empty.
    *   \author xlevri01
	*/
    CValue Back() const ;
	/** \bugfix[Zad] pracujete z hodnotou nebo je dùležitý i klíè? // pracujeme len s hodnotou na kluci nezalezi [xkunaj01]*/

    /** \brief  Information about CFronta length.
    *   \return Length of CFronta.
    *   \author xlevri01
    */
    size_t Length() const {
        return(iMap.Count());
    }

	/** \brief  Checking if CFronta is empty.
	*   \return True if CFronta is empty, false otherwise.
    *   \author xlevri01
	*/
    bool IsEmpty() const {
        return Length() == 0;
    }

    /** \brief  Deletes all elements in CFronta.
    *   \return True if CFronta is cleared successfully, false if CFronta is empty.
    *   \author xmagat01
    */
    bool Clear() {
        if (Length() == 0)
            return false;

        iMap.Clear();
        iFront = 0;
        iBack = 0;

        return true;
    }

	/** \brief  Usage memory using CFronta vs array.
	*   \return Return double value(%) which represent usage efectivity of memory. 
    *   \author xmagat01
	*/
    double Usage() const;

    /** \brief  Reverse order of elements in object.
    *   \author xkunaj01
    */
    void Reverz();

	/** \bugfix[Zad] metoda reverz uz nieje void, funkcia reverz opravena [xlevri01]. */
    /** \brief  Reverse order of elements.
    *   \return Return new CFronta with reversed order of elements.
    *   \author xkunaj01
    */
    friend CFronta Reverz(CFronta &aFronta);
}; /* CFronta */

#endif /* __CFronta_H__ */
