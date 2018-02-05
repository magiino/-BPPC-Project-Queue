/** \file CContainer.cpp
 *  \brief CContainer class implementation
 *  \details File contain CContainer class container implementation.
 *  \authors 
 *  $Id: CFronta.cpp 3108 2017-12-30 15:22:32Z xmagat01 $
*/

#include "CFronta.h"

// C`tors //
CFronta::CFronta(const CValue &aValue): iFront(0), iBack(0), iMap(CHashMap()) {
    EnQueue(aValue);
}

CFronta::CFronta(const int &aNumberOfElements): iFront(0), iBack(0), iMap(CHashMap()) {
    if (aNumberOfElements < 0) 
        throw std::runtime_error("Wrong number of elements from input!");

    for (int i = 0; i < aNumberOfElements; ++i) {
        EnQueue(CValue());
    }
}

CFronta::CFronta(CValue *aValues, const int &aLength): iFront(0), iBack(0), iMap(CHashMap()) {
    if (aLength > 0) {
        for (int i = 0; i < aLength; ++i) {
            EnQueue(aValues[i]);
        }
    } else throw std::runtime_error("Wrong length of input array!");
}

CFronta::CFronta(const char* aStr): iFront(0), iBack(0), iMap(CHashMap()) {
    std::stringstream ss(aStr);
    char ch = '\0';

    ss >> ch;
    if (!ss.good() || ch != '[')
        throw std::runtime_error("Input stream data integrity error! Wrong CValue");

    while (ss.good())
    {
        CValue tmp;
        ss >> tmp;
        EnQueue(tmp);
        ss >> ch;

        if (!ss.good() || ch != ',') {
            if (ch == ']')
                break;
            throw std::runtime_error("Input stream data integrity error! Wrong Format");
        }
    }
}

///////////////
//   Metody  //
///////////////
// Public metody pre pracu s frontou //
void CFronta::EnQueue(const CValue &aValue){
    if (Length() == 0) {
        iMap.Insert(CPair(iFront, aValue));
    }
    else {
        iMap.Insert(CPair(++iBack, aValue));
    }
}

CValue CFronta::DeQueue() {
    if (!*this)
        return CValue();

    CHashMap::CForwardIterator tmpIterator = iMap.At(iFront);
	CValue vysl = tmpIterator->Value();

    iMap.Erase(tmpIterator);
    // ak vyberiem posledny prvok resetujem si indexi
    if (iFront == iBack){
        iFront = 0;
        iBack = 0;
    } else iFront++;
 
    return vysl;
}

CValue CFronta::Front() const {
    if (Length() == 0)
        return CValue();

    CHashMap::CForwardIterator tmpIterator = iMap.At(iFront);
    CValue vysl = tmpIterator->Value();

    return vysl;
}

CValue CFronta::Back() const {
    if (Length() == 0)
        return CValue();

    CHashMap::CForwardIterator tmpIterator = iMap.At(iBack);
    CValue vysl = tmpIterator->Value();

    return vysl;
}

double CFronta::Usage() const{
    if (Length() == 0)
        return 0;
    int mapSize = (int)(sizeof(CHashMap) + 2 * sizeof(void*) * 256 + Length()* (sizeof(void*) + sizeof(CPair)));
    int arraySize = (int)(sizeof(CPair)*Length());

    return (double)(mapSize / arraySize * 100);
}

void CFronta::Reverz() {
    CFronta tmp(*this);
    Clear();

    CHashMap::CForwardIterator iterator;
    for (int i = tmp.iBack; i >= tmp.iFront; --i) {
        iterator = tmp.iMap.At(i);
        EnQueue(iterator->Value());
    }
}

CFronta Reverz(CFronta &aFronta) {
    CHashMap::CForwardIterator iterator;
    CFronta tmp;
    for (int i = aFronta.iBack; i >= aFronta.iFront; --i) {
        iterator = aFronta.iMap.At(i);
        tmp.EnQueue(iterator->Value());
    }
    return tmp;
}

// Private metody //
int CFronta::Compare(const CFronta &aFronta) const{
    int compare;

    if (*this < aFronta)
        compare = -1;
    else if (*this > aFronta)
        compare = 1;
    else
        compare = 0;

    return compare;
}

int CFronta::DeepCompare(const CFronta &aFronta) const {
    CHashMap::CForwardIterator thisIterator = iMap.At(iFront);
    CHashMap::CForwardIterator aFrontaIterator = aFronta.iMap.At(aFronta.iFront);
    int sumThis = 0, sumAfronta = 0;

    for (int i = 0; i < Length(); ++i) {
        CValue tmpThis = thisIterator->Value();
        CValue tmpAfronta = aFrontaIterator->Value();

        if (tmpThis > tmpAfronta)
            ++sumThis;
        else if (tmpThis < tmpAfronta)
            ++sumAfronta;

        ++thisIterator;
        ++aFrontaIterator;
    }

    int compare;

    if (sumThis < sumAfronta)
        compare = -1;
    else if (sumThis > sumAfronta)
        compare = 1;
    else
        compare = 0;
    return compare;
}

///////////////
// Operatory //
///////////////
// Unárne operátory //
CFronta CFronta::operator-() const {
    CHashMap::CForwardIterator iterator;
    CFronta tmp;
    for (int i = iBack; i >= iFront; --i) {
        iterator = iMap.At(i);
        tmp.EnQueue(iterator->Value());
    }
    return tmp;
}

CFronta& CFronta::operator++() {
    CHashMap::CForwardIterator iterator = iMap.At(iBack);
    EnQueue(iterator->Value());
    ;
    return(*this);
}

CFronta& CFronta::operator--() {
    CHashMap::CForwardIterator iterator = iMap.At(iBack);
    iMap.Erase(iterator);
    --iBack;
    return(*this);
}

CFronta CFronta::operator~() const {
    CFronta tmp;
    // Posledny prvok dam na zaciatok
    CHashMap::CForwardIterator iterator = iMap.At(iBack);
    tmp.EnQueue(iterator->Value());

    //prekopirujem od 2 do predposledneho prvku
    for (int i = iFront+1; i < iBack; ++i) {
        iterator = iMap.At(i);
        tmp.EnQueue(iterator->Value());
    }

    // nakopirujem prvy na koniec
    iterator = iMap.At(iFront);
    tmp.EnQueue(iterator->Value());

    return tmp;
}

// Logicke operatory //
bool CFronta::operator==(const CFronta& aFronta) const {
    return (Length()==aFronta.Length());
}
bool CFronta::operator!=(const CFronta& aFronta) const {
    return (Length() != aFronta.Length());
}
bool CFronta::operator<(const CFronta& aFronta) const {
    return (Length() < aFronta.Length());
}
bool CFronta::operator>(const CFronta& aFronta) const {
    return (Length() > aFronta.Length());
}

// Binárne operátory //
CFronta& CFronta::operator+=(const CFronta& aFronta) {
    if (aFronta.Length() == 0)
        return (*this);

    for (int i = aFronta.iFront; i < aFronta.iBack+1; ++i) {
       CPair tmp = aFronta.iMap[i];
       EnQueue(tmp.Value());
    }
    return(*this);
}

CFronta CFronta::operator+(const CFronta& aFronta) const {
    if (aFronta.Length() == 0)
        return (CFronta(*this));
    CFronta tmp(*this);

    for (int i = aFronta.iFront; i < aFronta.iBack + 1; ++i) {
        CPair pair = aFronta.iMap[i];
        tmp.EnQueue(pair.Value());
    }
    return(tmp);
}

CFronta CFronta::operator-(const CFronta& aFronta) const {
    if (aFronta.Length() == 0)
        return (CFronta(*this));

    CFronta tmp(aFronta);

    for (int i = iFront; i < iBack + 1; ++i) {
        CPair pair = iMap[i];
        tmp.EnQueue(pair.Value());
    }
    return(tmp);
}

CFronta& CFronta::operator=(const CFronta& aFronta) {
    Clear();
    if (aFronta.Length() == 0)
        return (*this);

    for (int i = aFronta.iFront; i < aFronta.iBack + 1; ++i) {
        CPair pair = aFronta.iMap[i];
        EnQueue(pair.Value());
    }

    return (*this);
}

// Neclensky operator //
CFronta operator+(const CValue aValue, const CFronta aFronta) {
    CFronta vysl(aFronta);
    vysl.EnQueue(aValue);

    return vysl;
}

// Stream operatory //
std::ostream& operator<<(std::ostream& aOStream, const CFronta& aFronta) {
    if (aFronta.Length() == 0) {
        aOStream << "<<Fronta " << aFronta.ID() << " je prazdna.>>";
    }
    else {
        aOStream << "(";

        for (int i = aFronta.iFront; i < aFronta.iBack + 1; ++i) {
            CPair pair = aFronta.iMap[i];

            aOStream << "[" << pair.Key() << "]" << pair.Value();
            // pridavam ciarku len ak mame dalsi item
            if (i != aFronta.iBack) {
                aOStream << ",";
            }
        }
        aOStream << ")";
    }
    return(aOStream);
}

std::istream& operator>>(std::istream& aIStream, CFronta& aFronta) {
    char ch = '\0';
    int key;

    aIStream >> ch;
    if (!aIStream.good() || ch != '(') {
        //Ak je fronta prazdna ulozim do streamu spravu vo formate << >> a tu to kontorlujem
        if (ch == '<')
            return(aIStream);
        throw std::runtime_error("Input stream data integrity error! Wrong input format");
    }

    while (aIStream.good())
    {
        aIStream >> ch;
        if (!aIStream.good() || ch != '[')
            throw std::runtime_error("Input stream data integrity error! Wrong input format");

        aIStream >> key;

        aIStream >> ch;
        if (!aIStream.good() || ch != ']')
            throw std::runtime_error("Input stream data integrity error! Wrong input format");

        CValue tmp;
        aIStream >> tmp;
        aFronta.EnQueue(tmp);
        aIStream >> ch;

        if (ch == ')')
            break;
        else {
            if (!aIStream.good() || ch != ',')
                throw std::runtime_error("Input stream data integrity error! Wrong Format");
        }
    }

    return(aIStream);
}