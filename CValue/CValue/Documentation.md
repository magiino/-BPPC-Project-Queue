\page doc Dokumentace projektu CValue

## Teoretický popis: Termín datový kontejner

Termín kontejner představuje v oblasti návrhu datových struktur a algoritmů takový datový typ, který umožňuje za běhu programu sdružovat více prvků (stejného nebo i různého typu) 
do jedné společné složené datové struktury. Výhody spojené s používáním kontejneru lze najít například v jednoduchém předání všech prvků takového kontejneru do funkce pomocí 
jediného argumentu (typu kontejner), nebo pro předání více hodnot z funkce, kde návratovou hodnotou je opět jediná hodnota (typu kontejner). Hlavní výhodou je ovšem možnost 
provedení operace nad všemi prvky kontejneru pomocí zápisu jediného volání služby, kterou zajistí přímo daný kontejner v rámci svého API. Mezi takové služby může patřit 
dealokace paměti všech prvků v kontejneru, vytisknutí všech prvků v kontejneru a další operace spojené se správou prvků v kontejneru. 
Prvky vkládané do Vašeho budoucího datového kontejneru budou právě instance třídy \c CValue. Ale i na samotnou třídu \c CValue lze pohlížet jako na primitivní kontejner mající
jedinou hodnotu.


### Třída CValue
Třída \c CValue obsahuje prvek (nebo prvky) mající hodnotu kterou jako třída zapouzdřuje (\c bool, \c TWeekDay, __long__, __TStudent__) _Nahraďte tučně označenou část zadanými typy!_ 

Úlohou třídy \c CValue je v definici mít složku \p iValue, jenž představuje užitečná data, která bude každý prvek seznamu obsahovat. 
Dále je třeba vhodně upravit (případně doplnit) metody určené pro konstrukci a likvidaci prvku tak, aby bylo možné nový prvek efektivně konstruovat a využívat.
Třída \c CValue je navíc správcem své vlastní hodnoty \p iValue a proto definuje základní metody pro zjištění, nastavení této hodnoty a zároveň zajišťuje pro nadřazené vyšší části programu metody pro porovnání dvou prvků \c CValue dle této hodnoty,
čímž izoluje nadřazené části od nutnosti znát konkrétní datový typ složky \p iValue.


### Jmenné prostory CValue_xxxx (CValue_bool::CValue, CValue_TWeekDay::CValue)
Návrh programu i Vaše zadání požaduje nezávislost na vnitřní implementaci třídy \c CValue (konkrétním datovém typu složky \p iValue). Návrh navíc umožňuje, aby uživatel mohl 
odkomentováním řádku přepínat mezi vnitřními implementacemi \c CValue. Tento mechanismus je zajištěn pomocí definice každé z variant \c CValue ve vlastním jmenném prostoru
\c CValue_NAZEV_TYPU. Díky této skutečnosti může existovat v programu několik stejně pojmenovaných tříd \c CValue, neboť názvy existují ve svém vlastním oboru 
viditelnosti (jmenném prostoru).

Volba dané varianty \c CValue je potom prováděna v souboru CValue.h, odkomentovaním toho řádku, který exportuje daný jmenný prostor do globálního prostoru jmen.
\code{.cpp}
using namespace CValue_bool;
//using namespace CValue_TWeekDay;
//using namespace CValue_char;
//using namespace CValue_int;
//using namespace CValue_float;
//using namespace CValue_long_double;
\endcode


\n
## Realizace dalších variant tříd CValue
V současnosti projekt obsahuje tyto varianty tříd \c CValue, z nichž je každá definována ve svém jmenném prostoru:
\li CValue_bool::CValue
\li CValue_TWeekDay::CValue

__Tyto dvě třídy jsou pevně zadány a je zakázáno modifikovat jejich zdrojové texty!__ Pro každou další variantu \c CValue nadefinujte nový jmenný prostor \c CValue_NAZEV_TYPU 
a v něm implementujte novou variantu třídy \c CValue.
\note Mechanismus by samozřejmě bylo možné realizovat i zcela automaticky (překladač sám dle potřeby programátora vygeneruje novou variantu třídy \c CValue pomocí 
definované šablony, případně bude umožnovat dynamickou identifikaci typu a tím umožní mít při běhu programu v jednom seznamu různé varianty prvků \c CValue.
Obě tyto techniky ovšem svým rozsahem vybočují nad rámec výuky v tomto kurzu a proto jsme se rozhodli se jim v tomto projektu vyhnout.


\n
## Testovací hlavní program
Hlavní program v souboru main.cpp představuje základní sadu testů, které ověřují správnou funkci libovolné varianty třídy \c CValue. Seznamte se s obsahem hlavního 
programu a trasujte si jednotlivá volání.

### Testovací hodnoty
Každá z implementací třídy \c CValue navíc obsahuje šest základních metod vracející hodnotu datového typu, který je vhodný pro vložení do složky \p iValue. Projděte si 
uvedené mechanismy a snažte se pochopit jejich vliv na nezávislost kódu hlavního programu.

Jedná se o tyto metody:
\li \c TestValue0() (např. CValue_bool::CValue::TestValue0())
\li \c TestStringValue0() (např. CValue_bool::CValue::TestStringValue0)
\li \c TestValue1() (např. CValue_bool::CValue::TestValue1)
\li \c TestStringValue1() (např. CValue_bool::CValue::TestStringValue1)
\li \c TestValueRandom() (např. CValue_bool::CValue::TestValueRandom)
\li \c TestStringRandom() (např. CValue_bool::CValue::TestStringValueRandom)

### Další kontrolní vlastnosti prvku
Třída CValue obsahuje několik kontrolních a ladicích mechanismů, které budete jistě chtít využívat.

\li Členskou proměnnou \p iInstance typu \c ClassInfo obsahující počítadlo vzniklých instancí (viz dále).
\li Pokud budete v metodách třídy CValue dynamicky alokovat pamět nezapomeňte na kontroly dealokace paměti pomocí knihovny check.
\li Pokud je prováděn překlad v _Debug režimu_ je při každém spuštění zajištěna identická inicializace generátoru náhodných čísel. Tím při každém krokování programu bude 
generován pro stejná vstupní data identický seznam (výsledný kontejner bude obsahovat prvky se stejnými hodnotami pro každé spuštění). Až si budete jisti, že program je funkční, zkuste přepnout překlad do _Release režimu_ a ověřit správnou funkci celého 
kontejneru při různých počátečních podmínkách generátoru náhodných čísel.

### Třída ClassInfo
Třída ClassInfo implementuje mechanismus automatického počítání vzniklých objektů a mechanismus jednoznačné identifikace ClassInfo<>::ID "ID" instancí za běhu programu. 
Tento mechanismus se Vám bude hodit při ladění programu. Všechny Vaše třídy by měly obsahovat datovou složku \ref CValue_bool::CValue::iInstanceInfo "iInstanceInfo" třídy ClassInfo, čímž 
zajistíte Vašim třídám tyto ladicí vlastnosti. Samotná třída ClassInfo je definována jako šablona umožňující, vznik různých variant této třídy - (generické programování 
resp. metaprogramování).

Mezi ladicí metody třídy ClassInfo patří:
\li ClassInfo<T>::Total()  - počítadlo vzniklých instancí třídy T
\li ClassInfo<T>::Living() - počítadlo v daném okamžiku existujících instancí třídy T
\li ClassInfo<T>::ID() resp. \ref CValue_bool::CValue::ID "CValue::ID()" - unikátní číselné označení dané instance


\attention Projděte si všechny uvedené kontrolní i ladicí mechanismy, snažte se pochopit jejich smysl a využití při trasování programu. Získané vědomosti se Vám budou rozhodně 
hodit, například když se nějaká část Vašeho programu začne chovat "podezřele" či přímo "nepřátelsky". 


\note 
Hodně štěstí při realizaci Vašeho projektu. Nebojte se, ono to půjde. Hlavně _nepropadejte panice!_ ;-)

Pety.

$Id: Documentation.md 2248 2017-12-19 23:22:50Z xmagat01 $
