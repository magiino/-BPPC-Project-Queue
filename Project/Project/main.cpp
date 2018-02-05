/** \file main.cpp
 *  \brief Main source
 *  \details Simple CValue example of usage
 *  \author Pety 2017
 *  $Id: main.cpp 3108 2017-12-30 15:22:32Z xmagat01 $
 */

#include <ctime>
#include "CValue.h"
#include "demagle.h"
#include "CFronta.h"
#include "CHashMap.h"

#include "check.h"

using std::endl;
using std::cout;
using std::cin;
using std::cerr;

int main(int argc, char *argv[])
	{
#ifdef NDEBUG
	std::srand(unsigned(std::time(nullptr)));	// Initialize random generator by actual time
#else
	std::srand(unsigned(42));					// Initialize random generator by fixed value useful for debugging
#endif

	cout << "Pocet parametru: " << argc << endl;
	for(int i = 0; i < argc; i++)
		cout << "Parametr #" << i << ": " << argv[i] << endl;
	
	cout << endl << "Nyni existuje " << ClassInfo<CValue>::Living() << " instanci tridy: " << DM(typeid(CValue).name()) << endl;
	cout << "Velikost jedne instance tridy " << DM(typeid(CValue).name()) << " je: " << sizeof(CValue) << " bajtu." << endl;

	/** \bugfix[Zad] Chybi volani metod z main. // opravene [xkunaj01,xmagat01,xlevri01]*/
    try
    {
        cout << "Nyni existuje " << ClassInfo<CValue>::Living() << " instanci tridy: " << DM(typeid(CValue).name()) << endl;
        // Tady bude zdrojovy text pouzivajici vas projekt 

        // Vytvorenie fronty zavolaním implicitného konstruktra
        CFronta fronta0;
        cout << '#' << fronta0.ID() << endl;

        // Vytvorenie troch instancí CValue
        CValue val1(CValue::TestStringValue0());
        cout << '#' << val1.ID() << endl;
        CValue val2(CValue::TestStringValue1());
        cout << '#' << val2.ID() << endl;
        CValue val3(CValue::TestValue0());
        cout << '#' << val3.ID() << endl;
        cout << endl;

        // Testovanie vkladanie do fronty
        cout << "Vkladam do fronty 3x CValue." << endl;
        fronta0.EnQueue(val1);
        fronta0.EnQueue(val2);
        fronta0.EnQueue(val3);

        // Testovanie ratanie prvkov v mape
        cout << "Vo fronte  " << fronta0.ID() << " je " << fronta0.Length() << " CValue" << endl;
        // Testovanie vyberanie z fronty
        cout << "Vyberam prve CValue" << endl;
        CValue tmp = fronta0.DeQueue();
        cout << "Vo fronte je" << fronta0.Length() << "CValue" << endl;
        cout << "Vybral som CValue s hodnotou " << tmp << endl;

        cout << "Vyberam druhe CValue" << endl;
        CValue tmp2 = fronta0.DeQueue();
        cout << "Vo fronte je" << fronta0.Length() << "CValue" << endl;
        cout << "Vybral som CValue s hodnotou " << tmp2 << endl;

        cout << "Vyberam tretie CValue" << endl;
        CValue tmp3 = fronta0.DeQueue();
        cout << "Vo fronte je" << fronta0.Length() << "CValue" << endl;
        cout << "Vybral som CValue s hodnotou " << tmp3 << endl;
        cout << endl;

        // Vytvorenie pola CValue
        CValue vectorCValue[3]{ val1 , val2, val3 };
        cout << "Test parametrizovaneho konstruktora" << endl;
        // Testovanie konstruktora ktorý dostane pole CValue
        CFronta fronta1(vectorCValue, 3);
        cout << "Vo fronte  " << fronta1.ID() << " je " << fronta1.Length() << " CValue" << endl;
        cout << endl;

        // Testovanie konstruktora ktorý dostane string s odelenymi hodnotami ciarkou
        cout << "Test string konstruktora" << endl;
        const char* hodnoty = CValue::TestStringValues();
        CFronta fronta2(hodnoty);
        cout << "Vo fronte  " << fronta2.ID() << " je " << fronta2.Length() << " CValue" << endl;
        cout << endl;

        // Testovanie operatorov //
        // Binárne operátory
        // Operátor +=
        std::stringstream ss1;
        ss1 << fronta0;
        std::stringstream ss2;
        ss2 << fronta1;
        std::stringstream ss3;
       
        cout << " Operator +=; Prvky z fronty 1 pridam na koniec fronty 0" << endl;
        cout << "Vo fronte  " << fronta0.ID() << " je " << fronta0.Length() << " CValue" << endl;
        cout << "A tieto prvky su  " << ss1.str() << endl;
        cout << "Vo fronte  " << fronta1.ID() << " je " << fronta1.Length() << " CValue" << endl;
        cout << "A tieto prvky su  " << ss2.str() << endl;
        fronta0 += fronta1;

        ss3 << fronta0;
        cout << "Po pridani je vo fronte 0  " << ss3.str() << endl;
        cout << "Vo fronte  " << fronta0.ID() << " je " << fronta0.Length() << " CValue" << endl;
        cout << "Vo fronte  " << fronta1.ID() << " je " << fronta1.Length() << " CValue" << endl;
        cout << endl;

        ss1.str("");
        ss2.str("");

        // Operátor +
        cout << "Operator +; fronta2 + fronta1 ; Prvky z fronty 1 pridam na koniec fronty 2 a vratim novy objekt" << endl;
        cout << "Vo fronte  " << fronta2.ID() << " je " << fronta2.Length() << " CValue" << endl;
        ss1 << fronta2;
        cout << "A tieto prvky su  " << ss1.str() << endl;

        cout << "Vo fronte  " << fronta1.ID() << " je " << fronta1.Length() << " CValue" << endl;
        ss2 << fronta1;
        cout << "A tieto prvky su  " << ss2.str() << endl;
        // Zaroven testujem operator = 
        fronta0 = fronta2 + fronta1;
        cout << "Toto je aj test pre operator =" << endl;
        cout << "Po scitani prvkov z fronty 2 a 1 som ich pridal pomocou operatora = do fronty 0"<< endl;
        cout << "Vo fronte  " << fronta0.ID() << " je " << fronta0.Length() << " CValue" << endl;
        cout << endl;

        ss1.str("");
        ss2.str("");

        // Test operator <<
        cout << "Test operatora <<." << endl;
        std::stringstream ss;
        ss << fronta0;
        cout << "Vo fronte " << fronta0.ID() << 
        " po pridani prvkov z fronty 1 a 2 sa nachadzaju tieto prvky ktore sa vypisuju zo streamu "
        << endl << ss.str() << endl;
        cout << endl;

        // Test operator >>
        cout << "Test operatora >>, Zo streamu pridam prvky do fronty " << fronta2.ID() << endl;
        ss1 << fronta2;
        cout << "Vo fronte  " << fronta2.ID() << " je " << fronta2.Length() << " CValue" << endl;
        cout << "A tieto prvky su  " << ss1.str() << endl;
        cout << "Pridavam" << endl;
        ss >> fronta2;
        cout << "Vo fronte  " << fronta2.ID() << " je " << fronta2.Length() << " CValue" << endl;
        ss2 << fronta2;
        cout << "A tieto prvky su  " << ss2.str() << endl;
        cout << endl;

        ss.str("");
        ss1.str("");
        ss2.str("");
        ss3.str("");

        // Operátor -
        cout << "Operator -; A-B, Vratim novy objekt kde budu najprv prvky B a potom prvky A" << endl;
        cout << "Vo fronte  " << fronta0.ID() << " je " << fronta0.Length() << " CValue" << endl;
        ss << fronta0;
        cout << "A tieto prvky su  " << ss.str() << endl;
        cout << "Vo fronte  " << fronta1.ID() << " je " << fronta1.Length() << " CValue" << endl;
        ss1 << fronta1;
        cout << "A tieto prvky su  " << ss1.str() << endl;
        fronta1 = fronta0 - fronta1;
        cout << "Vo fronte  " << fronta1.ID() << " je " << fronta1.Length() << " CValue" << endl;
        ss2 << fronta1;
        cout << "A tieto prvky su  " << ss2.str() << endl;
        cout << endl;

        // Test operator bool()
        cout << "Testovanie operatora bool()." << endl;
        bool test = bool(fronta1);
        cout << "Operator bool som pouzil na frontu "<< fronta1.ID() << " a vysledok je " << test << endl;
        cout << endl;

        // Test Clear()
        cout << "Testovanie metody Clear()." << endl;
        fronta1.Clear();
        test = bool(fronta1);
        cout << "Vo fronte  " << fronta1.ID() << " je " << fronta1.Length() << " CValue" << endl;
        cout << "Operator bool som pouzil na frontu " << fronta1.ID() << " po pouziti Clear() a vysledok je " << test << endl;
        ss3 << fronta1;
        cout << "A tieto prvky su  " << ss3.str() << endl;
        cout << endl;

        ss.str("");
        ss1.str("");
        ss2.str("");
        ss3.str("");

        // Test D`toru()
        cout << "Testovanie destruktoru." << endl;
        fronta1.~CFronta();
        if (!fronta1)
            cout << "Destruktor funguje!" << endl;
        cout << endl;

        // Test Usage()
        cout << "Testovanie metody Usage()." << endl;
        double percent = fronta0.Usage();
        cout << "Efektivnost fronty "<< fronta0.ID() << " oproti polu je " << percent << "%."<< endl;
        cout << endl;

        // Test Front()
        CValue a = fronta0.Front();
        CValue b = fronta0.Back();

		cout << "Hotovo." << endl;
		} /* try */

	catch(std::invalid_argument &e)
		{
		cerr << "std::invalid_argument: " << e.what() << "!!!\n\a" << endl;
		}
	catch(std::length_error &e)
		{
		cerr << "std::length_error: " << e.what() << "!!!\n\a" << endl;
		}
	catch(std::out_of_range &e)
		{
		cerr << "std::out_of_range: " << e.what() << "!!!\n\a" << endl;
		}
	catch(std::range_error &e)
		{
		cerr << "std::range_error: " << e.what() << "!!!\n\a" << endl;
		}
	catch(std::runtime_error &e)
		{
		cerr << "std::runtime_error: " << e.what() << "!!!\n\a" << endl;
		}


	cout << endl << "Nyni existuje " << ClassInfo<CValue>::Living() << " instanci tridy: " << DM(typeid(CValue).name()) << endl;
	cout << "V prubehu programu vzniklo celkem " << ClassInfo<CValue>::Total() << " instanci tridy: " << DM(typeid(CValue).name()) << endl;
	
	cout << endl << "V prubehu programu vzniklo celkem " << ClassInfo<CValue_long::CValue>::Total() << " instanci tridy: " << DM(typeid(CValue_long::CValue).name()) << endl;
	cout << "V prubehu programu vzniklo celkem " << ClassInfo<CValue_TStudent::CValue>::Total() << " instanci tridy: " << DM(typeid(CValue_TStudent::CValue).name()) << endl;

	return(0);
	}
