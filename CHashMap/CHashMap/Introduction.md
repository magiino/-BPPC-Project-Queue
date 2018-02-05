\mainpage Úvod a zadání

\n

| Projekt BPPC  CHash Map Example	| 2017																|
| ---								| ---																|
| Název projektu:					| CHashMap															|
| Autor 1:							| \c 186135, __Magáth__ Marek,  \c xmagat01@feec.vutbr.cz			|
| Autor 2:							| \c 186125, __Kuna__ Ján, \c xkunaj01@feec.vutbr.cz				|
| Autor 3:							| \c 173688, __Levrinc__ Adam, \c xlevri01@feec.vutbr.cz   			|
| Autor 4:							| \c ID, __Příjmení__ Jméno, \c login/email							|
| Datum zadání:						| 23.10.2017 														|
| Datum finálního odevzdání:		| 13.12.2017 (včetně)												|

\n\n

## Úvodní poznámky
Cílem tohoto testovacího projektu je pomoci Vám navrhnout a odzkoušet  třídu \c CHashMap a pomocné třídy nutné pro její správnou činnost (\c CHashMap::TItem, \c CPair). 
Projekt již obsahuje plně funkční varianty \c CValue_bool::CValue a \c CValue_TWeekDay::CValue. Dále obsahuje strukturu pro uzel vázaného seznamu \c CHashMap::TItem, která je 
základní součástí množiny prvků připadající každému indexu ve třídě \c CHashMap.  Třídy \c CHashMap a \c CPair jsou připravené, až na funkčnost vybraných metod, 
jejichž kód je nutné dopsat. Třída \c CPair slouží jako datový člen uzlu vázaného seznamu \c CHashMap::TItem a obsahuje dvojici hodnot: klíč a hodnota. Třída \c CHashMap 
slouží pro vlastní manipulaci s hodnotami (vkládání, výběr, třídění, ...)
Vaším úkolem je naprogramovat (a pomocí kódu ve funkci main ověřit) chybějící kód metod tříd \c CPair a \c CHashMap. Kód musí fungovat pro všechny varianty 
třídy CValue dle zvoleného zadání.

Vývoj projektu je možný v libovolném prostředí a kompilátoru C++ ([g++](http://gcc.gnu.org/), [clang++](http://clang.llvm.org/)), 
ale referenčním překladačem bude [Microsoft Visual Studio Professional 2017](http://www.visualstudio.com/).

\attention Tento projekt (tj. adresář CHashMap) je určen pouze pro testování a slouží pro kontrolu funkčnosti doplněného kódu tříd \c CPair, \c CHashMap 
a nových typů \c CValue. Hodnocení funkčnosti tříd \c CPair a \c CHashMap proto proběhne v tomto projektu. 
Hodnocení zadání, komentářů a zdrojů datového kontejneru, ale proběhne na základě dat v adresáři \b Project 
(tj. "modrá" varianta dokumentace vygenerovaná pomocí Doxygen).

\n
## Doporučený postup
1.	Pročtěte si tuto dokumentaci (\ref doc) a dodané zdrojové texty. Význam symbolů a barevného značení u zobrazovaných grafů popisuje tato [legenda](graph_legend.html).
2.	Proveďte trasování dodané funkce main.
3.	Promyslete strukturu celého programu a význam tříd CPair, CHashMap, CHashMap::TItem a CValue.
4.	Navrhněte a implementujte chybějící kód tak, aby byl výsledný kód funkční pro všechny varianty tříd \c CValue.
5.	Ověřte správnou funkci nového kódu na \b nemodifikovaném těle funkce \c main.
6.	Doplňte dokumentaci Doxygen pro nově vytvořené metody (preferovaným jazykem C++ zdrojových textů je angličtina, případně čeština bez diakritiky).
7.	Jakmile Vámi navržené varianty tříd budou fungovat správně a ohodnotí Vám je vyučující (společně s průběžným hodnocením hlavičkových souborů projektu), 
        zkopírujte a začleňte si jejich zdrojové texty do Vašeho projektu: \b Project (CKontejner).

\n
## Poznámky k řešení:
\todo
Do tohoto textu nezapomeňte doplnit hlavičku (tj. jména řešitelů, varianty tříd \c CValue, datum zadání).

\note Na následujícím odkazu najdete [Myšlenkovou mapu k projektu](https://my.mindnode.com/s2Bbn2gFS8pHZFGcZJhRj4U7zmxx8ivygkoPCuZz),
kterou jsme tvořili během přednášky věnované projektu
a také [Mind mapu třídy CHashMap](https://my.mindnode.com/hGXwS1Fwu9UbP7HD9E5GjsE8hyzBgtz2hPg2zWJQ).
Pro lepší orientaci uvádíme i krátkou motivaci k pojmu třída na odkazu:
[Motivace třída](http://www.uamt.feec.vutbr.cz/~richter/vyuka/1314_ppc/bppc/cviceni/motivace_trida.html).
\n

$Id: Introduction.md 190 2017-11-07 12:56:21Z xlevri01 $
