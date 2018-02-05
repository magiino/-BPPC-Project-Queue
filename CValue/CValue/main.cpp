/** \file main.cpp
 *  \brief Main source
 *  \details Simple CValue example of usage
 *  \author Pety 2017
 *  $Id: main.cpp 1215 2017-12-04 18:30:13Z xlevri01 $
 */

#include <ctime>
#include "CValue.h"
#include "demagle.h"

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

	try
		{
	// Test c'tor implicitni
		CValue_long::CValue temp_instance1;
		CValue_TStudent::CValue temp_instance2;

		CValue a;
		cout << "Objekt 'a' je " << a.ID() << "-tou instanci tridy: " << DM(typeid(CValue).name()) << endl;
		cout << "Nyni existuje " << ClassInfo<CValue>::Living() << " instanci tridy: " << DM(typeid(CValue).name()) << endl;
		cout << "V prubehu programu zatim vzniklo celkem " << ClassInfo<CValue>::Total() << " instanci tridy: " << DM(typeid(CValue).name()) << endl;

	// Test c'tor konverzni
		CValue b(CValue::TestValue0());
		CValue c(CValue::TestValue1());

	// Test c'tor copy
		CValue d = a;
		CValue e(a);

	// Test c'tor konverzni s nahodnymi parametry
		CValue f(CValue::TestValueRandom());

	// Test c'tor z retezce
		const char *str(CValue::TestStringValue1());
		cout << "C'tor instance CValue z C retezce: \"" << str << "\"." << endl;
		CValue g(CValue::TestStringValue0());
		CValue h(str);
		cout << " V instanci je hodnota: " << h << endl;

	// Test CValue::operator<<
		cout << "CValue::operator<<" << endl;
		cout << ' ' << a << ',' << b << ',' << c << ','<< d << ',' << e << ',' << f << ',' << g << ',' << h << endl;

	// Test CValue::operator>>
		cout << "CValue::operator>>" << endl;
		cout << " Test vlozeni " << DM(typeid(CValue).name()) << " nahodne hodnoty\n";
		const char* teststring = CValue::TestStringValueRandom();
		cout << " Vkladam hodnotu: '" << teststring << '\'' << endl;
		std::istringstream test_cin(teststring, std::istringstream::in);
		test_cin >> d;
		cout << " V instanci je hodnota: " << d << endl;

	// Test setter CValue::SetValue
		cout << "CValue::SetValue" << endl;
		b.SetValue(CValue::TestValue0());

	// Test getter CValue::Value
		cout << "CValue::Value" << endl;
		cout << " Value=" << a.Value() << endl;

	// Test CValue::operator-
		cout << "CValue::operator-" << endl;
		cout << ' ' << c << ',';
		cout << -c << ',';
		cout << c << endl;

	// Test CValue::operator=
		c = a;

	// Test CValue::operator==
		cout << "CValue::operator==" << endl;
		cout << " Hodnota v objektu 'a' je ";
		if(a == d)
			cout << "stejna jako hodnota";
		else
			cout << "ruzna od hodnoty";
		cout << " v objektu 'd'" << endl;

	// Test CValue::operator!=
		cout << "CValue::operator!=" << endl;
		cout << " Hodnota v objektu 'a' je ";
		if(a != d)
			cout << "ruzna od hodnoty";
		else
			cout << "stejna jako hodnota";
		cout << " v objektu 'd'" << endl;

	// Test CValue::operator>
		cout << "CValue::operator>" << endl;
		cout << " Hodnota v objektu 'a' ";
		if(a > d)
			cout << "je";
		else
			cout << "neni";
		cout << " vetsi nez hodnota v objektu 'd'" << endl;

	// Test CValue::operator<
		cout << "CValue::operator<" << endl;
		cout << " Hodnota v objektu 'a' ";
		if(a < d)
			cout << "je";
		else
			cout << "neni";
		cout << " mensi nez hodnota v objektu 'd'" << endl;

		cout << "Nyni existuje " << ClassInfo<CValue>::Living() << " instanci tridy: " << DM(typeid(CValue).name()) << endl;

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

// Doplnkove testy
#ifdef SUPPLEMENT_TESTS_TWEEKDAY
	try 
		{
		unsigned x = 0;
		CValue a;
		cout << "CValue::operator<<" << endl;
		cout << " Zadej schvalne (kvuli testovani) cislo vetsi nez (0-6) jako hodnotu dne: ";
		cin >> x;
		a.SetValue(TWeekDay(x));
		cout << " Zadal jsi hodnotu: " << a << endl;

		cout << " Zadej schvalne spatne jmeno dne napr.: (Wonday) ";
		cin >> a;
		cout << " Zadal jsi hodnotu: " << a << endl;
		}
	catch(std::range_error &e)
		{
		cerr << "std::range_error: " << e.what() << "!!!\n\a" << endl;
		}
	catch(std::runtime_error &e)
		{
		cerr << "std::runtime_error: " << e.what() << "!!!\n\a" << endl;
		}
#endif

	cout << endl << "Nyni existuje " << ClassInfo<CValue>::Living() << " instanci tridy: " << DM(typeid(CValue).name()) << endl;
	cout << "V prubehu programu vzniklo celkem " << ClassInfo<CValue>::Total() << " instanci tridy: " << DM(typeid(CValue).name()) << endl;
	
	cout << endl << "V prubehu programu vzniklo celkem " << ClassInfo<CValue_long::CValue>::Total() << " instanci tridy: " << DM(typeid(CValue_long::CValue).name()) << endl;
	cout << "V prubehu programu vzniklo celkem " << ClassInfo<CValue_TStudent::CValue>::Total() << " instanci tridy: " << DM(typeid(CValue_TStudent::CValue).name()) << endl;

	return(0);
	}
