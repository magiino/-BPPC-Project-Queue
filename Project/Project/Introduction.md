\mainpage Úvod a zadání

\n

| Projekt BPPC					| 2017 															| Hodnocení zadání, CValue(max 10b)	| Hodnocení hlavička max(10b)	| Hodnocení projektu max(20b)	|
| ---							| ---															|									|								|								|
| Autor 1:						| \c 186135, __Magáth__ Marek,  \c xmagat01@feec.vutbr.cz   	|			8						|			6,5	 Znacna cast tohoto souboru je opisem jineho projektu. Kontaktujte cviciciho. Pracujte samostatne. Pokud se to bude opakovat, budete mit z celeho projektu nulu!!!				|								|
| Autor 2:						| \c 186125, __Kuna__ Ján, \c xkunaj01@feec.vutbr.cz        	|			8						|			6,5	Znacna cast tohoto souboru je opisem jineho projektu. Kontaktujte cviciciho. Pracujte samostatne. Pokud se to bude opakovat, budete mit z celeho projektu nulu!!!				|								|
| Autor 3:						| \c 173688, __Levrinc__ Adam, \c xlevri01@feec.vutbr.cz		|			8						|			6,5	Znacna cast tohoto souboru je opisem jineho projektu. Kontaktujte cviciciho. Pracujte samostatne. Pokud se to bude opakovat, budete mit z celeho projektu nulu!!!				|								|
| Autor 4:						| \c ID, __Příjmení__ Jméno, \c login/email						|									|								|								|
| Datum zadání:					| 23.10.2017 													|									|								|								|
| Datum finálního odevzdání:	| 13.12.2017 (včetně)											|									|								|								|

\n\n
\bugfix[Zad] sledovat warningy doxygen. //odstranene vsetky warningy doxygen  

## Úvodní poznámky


V následujícím textu je vzor zadání. 
Tučně jsou označeny prvky, které se mohou lišit obsahem, ale které platí obecně pro třídu kontejner. 
Tyto pasáže je nutné nahradit upraveným významem pro konkrétní kontejner (vámi upravené části zůstanou zvýrazněny). 
Čím více tučných položek využijete, tím více vlastností si osvojíte a tím hodnotnější program bude. 
V tomto okamžiku nás nezajímá implementace, (tedy konkrétní realizace - názvy proměnných a jak uvnitř fungují jednotlivé metody), pouze u metod a operátorů vždy slovně popište, 
jak si představujete jejich činnost. Činnost popište tak, aby byla dostatečná = jak byste ji zadali externímu programátorovi, aby jasně věděl jak se má metoda/funkce chovat. 
U metod a operátorů bude tedy uveden: název, popis činnosti, použití, smyslu a významu funkce (anotace/synopsis) - která se později stane součástí komentáře/helpu ve zdrojovém textu (Doxygen).

U každé metody/funkce uveďte monogram jednoho z autorů, který daný kód bude realizovat. Každý student by měl realizovat část každého bodu zadání (pokud to zadání umožňuje).


Uvedené poznámky (Note) v odevzdávaném zadání nebudou, slouží pouze jako doporučení a upřesnění. 
U některých variant zadání kontejneru mohou nastat problémy s tím, že daná vlastnost (metoda) kontejneru nemá \em "nejlogičtější" využití – zkuste si nějaké (byť méně logické) využití vymyslet (z hlediska programátorské praxe je to samozřejmě špatně, protože metody by měly být logické a snadno chápatelné, ale my zde dáme prioritu procvičení, výuce a použití daného typu metod). 
Každý z autorů by měl napsat alespoň jednu metodu příp. operátor daného typu.

Vývoj projektu je možný v libovolném prostředí a kompilátoru C++ ([g++](http://gcc.gnu.org/), [clang++](http://clang.llvm.org/), [XCode](https://developer.apple.com/xcode/download/)), 
ale referenčním překladačem bude [Microsoft Visual Studio Professional 2017](http://www.visualstudio.com/).

\n\n



## Zadání

### Popis datové struktury a výběr datových typů pro realizaci projektu

V rámci projektu se bude tvořit objektová knihovna zajišťující kontejnerové funkce pro prvky nesoucí hodnotu zvoleného typu. 
Vnitřní implementace kontejneru bude realizována jako tzv. [HashMap (HashTable)](https://en.wikipedia.org/wiki/Hash_table) tj. seznam prvků s klíči a hodnotami. 
Tato datová struktura umožňuje časově efektivní vyhledávání, odebíraní a vyhledávání prvků. 
_Snažte se tedy realizovat paměťově i časově úspornou implementaci kontejneru!_
Prvky vkládané do datové struktury \c CHashMap budou instance třídy \c CValue.

Třída \c CValue bude prvkem kontejneru. 
Ve výsledném projektu bude vytvořený kontejner schopen pracovat minimálně se čtyřmi různými implementacemi třídy \c CValue. 
První dvě třídy \c CValue Vám již byly dodány v rámci zadání a realizují zapouzdření typu \c bool a výčtového typu \c TWeekDay a je v rámci řešení projektu zakázána jejich modifikace. Podle těchto příkladů v rámci projektu vytvoříte dvě další třídy \c CValue.

Třídy \c CHashMap a pomocná třída \c CPair budou dodány v rozpracované podobě a v rámci projektu bude nutné je dopracovat (doplnit jejich funkčnost). Struktury \c TItem a \c CPair budou sloužit jako pomocné 
pro realizaci třídy \c CHashMap. Struktura \c TItem bude sloužit jako prvek pro tvorbu vázaného seznamu, jehož datovou složku bude tvořit prvek třídy \c CPair. Tento prvek bude obsahovat klíč a hodnotu. Hodnota bude
reprezentována pomocí třídy \c CValue. Pomocné třídy budou nedílnou součástí projektu ale v dalším budeme zmiňovat pouze \c CValue. 

\attention
Kontejner budete realizovat bez podpory kontejnerových typů knihovny STL nebo jiných knihoven třetích stran. Prvky kontejneru bude realizován pomocí seznamu typu \c CHashMap a jeho prvky budou instance třídy \c CValue.
Kontejner bude realizován tak, aby uvnitř umožňoval práci s HashMap seznamy obecného rozměru. 
Realizace kontejneru jako HashMap seznamu nebude degenerována na realizaci pomocí pouhého lineárního spojového seznamu. 
Kontejner musí správně pracovat pro všechny čtyři vytvořené třídy \c CValue, ale nemusí s nimi pracovat současně v rámci jednoho překladu.\n
_Pozor! Nedodržení těchto podmínek znamená nesplnění základních požadavků zadání a hodnocení takového projektu bude bohužel 0 bodů!!!_


-----------------------------------------------------------------------------------------------------------------


\n
\todo V následujících třech částech ponechejte v seznamu vždy pouze ty položky, které odpovídají Vašemu zadání projektu.

Místo všech názvů <b> \c CContainer</b> uveďte název kontejneru zvoleného v části zadání číslo 3
První Vámi realizovaná třída \c CValue_long bude zapouzdřovat jeden ze základních typů, který si zvolte v části 1:

_Zadání část 1: základní datové typy (mimo bool), (zvolte jednu z možností):_
- Jeden z __celočíselných typů__: \c long
\note - Jeden z __reálných typů__: např.: \c float, \c double, \c long \c double
\note - __Výčtový typ enum__ např.: (měsíce, výčet barev, znak Morseovy abecedy, znamení zvěrokruhu)



Druhá Vámi realizovaná třída \c CValue_TStudent bude zapouzdřovat jeden ze složených datových typů, který si zvolte v části 2:

_Zadání část 2: složené datové typy (struktury, pole) (mimo TWeekDay - Dny v týdnu), (zvolte jednu z možností):_
- __Libovolný další__ :  TStudent (jméno a příjmení, VUT ID) 
\note- __Komplexní číslo__
\note- __Textový řetězec__ (dynamický)
\note- __Bod v prostoru__ (x,y,z)
\note- __Číselný interval__ <min,max>
\note- __Barevná informace__ (RGB složky)
\note- __Pole číselných hodnot__ typu \c double



Třetí Vámi realizovaná třída bude samotný kontejner pracující s prvky třídy \c CValue. Charakter a funkci kontejneru si zvolte v části 3:

_Zadání část 3: typ kontejneru implementován pomocí HashMap seznamu (zvolte jednu z možností):_
- __Fronta__ – jeden vstup, jeden výstup, architektura FIFO. Poradie prvkov na výstupe je zhodné s poradím prvkov na vstupe (všetky prvky majú rovnakú prioritu). Do Fronty vkladame prvky a fronta si uklada kluce prveho vlozeneho prvku a posledneho. Vzdy zacina od 0 a pokracuje pri kazdom vlozenom prvku o +1. Ak vytiahneme posledny prvok z fornty kluce prveho a posledneho prvku sa resetuju na 0. Za pomoci tohto cislovania kluca vieme v akom poradi sme vkladali prvky a vieme ich spravne vyberat.
\bugfix[Zad] Jak se uplatni klič? // podla kluca vieme v akom poradi sme vkladali prvky

\note- __Prioritní fronta__ – jeden vstup, jeden výstup, architektura FIFO. Prvky vstupují do fronty vždy dodatečnou s informací o své prioritě, prvky vystupují z fronty v pořadí určeném prioritou a při stejné prioritě je pořadí prvků na výstupu shodné s pořadím prvků na vstupu.
\note- __Prioritní zásobník__ – jeden vstup, jeden výstup, architektura LIFO. Prvky vstupují do fronty vždy dodatečnou s informací o své prioritě, prvky vystupují z fronty na základě své priority a při výskytu prvku se stejnou prioritou je pořadí prvků na výstupu opačné o proti pořadí prvků na vstupu.
\note- __Množina__ – souhrn (kolekce) prvků, neumožňuje indexaci jednotlivých prvků, prvky stejné hodnoty se nemohou v množině opakovat. Mezi definované operace patří tzv. řezy. (tj. vznik nové množiny obsahující všechny prvky původní množiny, které jsou menší (resp. větší) než zadaná hodnota).
\note- __Multimnožina__ - (totéž co množina, navíc může obsahovat více prvků stejné hodnoty) – tj. hodnoty prvků se mohou opakovat, zajistěte efektivní využití paměti (neduplikujte fyzicky v seznamu prvky stejné hodnoty).
\note- __Asociativní pole__ – pole prvků typu \c CValue umožňující indexaci hodnotou typu \c int. Asociativní pole předpokládá, že indexy jednotlivých vložených prvků nemusí tvořit spojitou řadu (tj. asociativní pole je pole prvků, který nemusí obsahovat všechny indexy v daném rozsahu posloupnosti).
\note- __Mapa__ - představuje seznam hodnot typu \c int a umožňuje indexaci těchto prvků pomocí hodnoty typu \c CValue. Bude obsahovat metody pro vložení a odebrání prvku. Pro jednu konkrétní hodnotu indexu existuje vždy pouze jedna hodnota typu \c int.
\note- __Multimapa__ - (totéž co mapa, navíc může obsahovat pro jeden index typu \c CValue obecně více prvků s různou hodnotou) – tj. pro jednu konkrétní hodnotu indexu může existovat několik hodnot typu \c int.


-----------------------------------------------------------------------------------------------------------------

\n
### Vzorový text zadání:

\todo Místo všech názvů <b> \c CContainer</b> uveďte název kontejneru zvoleného v části zadání číslo 3

\todo Od tohoto místa dále (včetně obrázku) nahraďte tučně zapsané texty vhodnou modifikací pro Vaše zadání (značky pro zvýraznění bold neodstraňujte). Nezvýrazněný text nemažte - jedná se o povinné body zadání!!! 
Dále viz úvodní poznámky.

Navrhněte třídu \c __CFronta__, která bude obsahovat prvky třídy \c CValue a realizovat knihovnu pro práci s vybraným jednoduchým typem (__long__) a složeným datovým typem (__TStudent__), 
který bude zapouzdřen ve třídě \c CValue. 
Třída \c CValue (společně s dalšími pomocnými datovými typy) je připravena pro práci s HashMap seznamem a její využití při tvorbě fronty je povinnou součástí projektu. Celá knihovna bude realizovat činnost __fronty__ podle následujících bodů. 
Pokud je to možné, bude splňovat očekávané chování (podobné jako u jednoduchých typů: \c int, \c float, ...). Navržená třída __CFronta__ umožní že:

1. Třída \c CValue zapouzdřuje dva dodané (\c bool, \c TWeekDay) a dva datové typy: jeden základní: __long__ a druhý složený: __TStudent__. Zložený typ TStudent je štruktúra (definícia struct) a obsahuje nasledujúce prvky: iFirstName, iLastName, iVutID.
Tyto definované třídy budou vytvořeny ve svých jmenných prostorech: __CValue_long, CValue_TStudent__.
\note Zde uveďte za NAZEV_TYPU typy zvolené pro třídy z části zadání č.1 a č.2.
\note Pro oba nové datové typy (z části zadání č.1 a č.2) uveďte, jaký typ budou zapouzdřovat (u výčtového typu definujte i jednotlivé názvy hodnot). Pro datový typ č.2 uveďte název nově definovaného složeného typu s informaci, zda půjde o definici: \c typedef, \c struct, \c union, \c class.

2. Vznik objektu třídy \c __CFronta__:
	- implicitní konstruktor __který nastaví atribúty jednoduchého dátoveho typu defaultné hodnoty, pre zložité dátové typy zavolá implicitný konštruktor zloženého dátoveho typu__ [implementovať bude xkunaj01]
	- (konverzní) konstruktor - bude mat parameter CValue, vytvorí novú instanciu CFronty, pridá do mapy prvý prvok [implementovať bude xkunaj01]
	- kopykonstruktor - vytvára novú instanciu, tým že skopíruje všetky prvky fronty [implementovať bude xlevri01]
	- konstruktor z typu int z typu int (vytvářející seznam o daném počtu prvků CValue) [implementovať bude xlevri01]
	- konstruktor z dvojice hodnot reprezentujících pole prvků CValue a počet prvků - výsledný objekt se vytvoří tak, že bude pridávať prvky od indexu [0] po [size]  [implementovať bude xmagat01]
	- konstruktor na základě C řetězce (char *) __ve kterém budou hodnoty jednotlivých CValue, oddelené čiarkami. Reťazec bude mať napríklad tvar CValue long "626565,6565655,322322" [implementovať bude xmagat01]
\note Celkem tedy – implicitní, kopykonstruktor, konverzní, konverzní z řetězce, s více parametry, ... – (minimální počet 6ks)

3. Počet vzniklých a aktuálních instancí třídy \c __CFronta__ bude možné sledovat za pomoci statických proměnných třídy a bude možné je získat voláním statických metod (třída \c ClassInfo). 
Každá instance třídy \c __CFronta__ bude obsahovat privátní atribut \c iInstanceInfo pomocné třídy \c ClassInfo sloužící k identifikaci instance (odpovídající pořadí vzniku). Identifikační hodnota instance musí být přístupná mimo třídu pomocí vhodné metody - \c ID().

4. Zánik objektu - destruktor __CFronty__ bude implementován s mechanizmem odpočtu aktivních prvků pomocí pomocné třídy \c ClassInfo. Dynamické členské prvky __odalokuje__.
 
5. Budou implementovány operátory __CFronty__ s příslušnými činnostmi:
	- Unárne operátory [implementovať bude xkunaj01]
		- operátor – prefix (-A), slúži na odobranie posledného prvku z fronty \bugfix[Zad] Jak je v hashmape definováno pořadí? Podobne dale - posouvani pořadí ve frontě // vieme s akymi indexami tam vkladame prvky takze vieme ist aj po poradi// .

		- operátor ++ na koniec fronty vloží nový prvok ktorý je kópia prvku pred ním 
		- operátor - - odoberie posledný prvok z fronty 
		- operátor ~  prehodi prvy prvok s posledným
	
	- Logické operátory (slúži pre porovnávanie počtu prvkov dvoch front) [implementovať bude xlevri01]
		- operátor == vracia TRUE ak je rovnaký počet prvkov
		- operátor != vracia TRUE ak nie je rovnaký počet prvkov
		- operátor > vracia TRUE ak je počet prvkov fronty pred operátorom vačší ako počet prvkov fronty za operátorom
		- operátor < vracia TRUE ak je počet prvkov fronty pred operátorom menší ako počet prvkov fronty za operátorom

	- Binárne operátory [implementovať bude xmagat01]
		- operátor = jedná sa o priradenie, nevytvára sa žiadny nový objekt, prvky A sa prepíšu prvkami B (pri A=B) 
		- operátor += prvky z B priradí na koniec A, ostane to v pôvodnom objekte (objekt pred oprerátorom (A)) (pre A+=B)
		- operátor + to isté čo +=, s rozdielom, že vracia nový objekt
		- operátor - prvky z B priradí pred prvky A, vracia nový objekt

		- konverzny - vracia true ak je pocet prkov v mape vacsi ako 0 inak vracia false [implementovať bude xmagat01]
		- nečlensky - prida Cvalue do fronty (CValue + CFronta) [implementovať bude xlevri01]
\note Celkem tedy – unárních (nejméně 3ks), binárních (nejméně 3ks), konverzní, nečlenský, logické (nejméně 3ks) – (celkem minimálně 12ks). U operátorů i metod z následujících bodů uveďte požadované informace (viz úvodní poznámky).
_Zadání bude obsahovat definici zvolené operace (tedy například co se myslí pod termínem odečtení kontejnerů, jak se bude chovat k prvkům fronty, popřípadě ke kontejnerům prázdným)_
\bugfix[Zad] Chybi nečlenský a konverzni. // doplnene


6. Standardní vstup a výstup z instance třídy \c __CFronta__ bude realizován pomocí streamů (realizovaný \c friend funkcí s využitím jejích vlastností) – přetížením operátorů << a >> ve stejném formátu navrženém pro konstruktor z \c char * (tj. __čárkami oddělený seznam hodnot ... ve tvaru ...__).[implementovať bude xmagat01]

7. Budou realizovány privátní a veřejné metody: veřejná metoda \c PocetPrvku pro zjištění prvků ve __fronte__, která nebude mít parametry. Metody pro vložení a vyzvednutí prvku dle funkce __fronty__. 
 
 Public methods:
	- \c Usage(), která vrátí \c double hodnotu [v procentech] reprezentující efektivnost využití paměti při použití lineárního seznamu prvků \c CValue(TItem) v poměru k reprezentaci kontejneru 
pomocí standardního C pole stejného počtu prvků jako je typ zapouzdřený ve třídě \c CValue [implementovať bude xmagat01]
	- EnQueue() - vloží prvok do fronty na koniec [implementovať bude xmagat01]
	- DeQueue() - odstráni prvý prvok fronty [implementovať bude xmagat01]
	- Front() - vráti kópiu/referenciu prvého prvku [implementovať bude xlevri01]
	- Back() - vráti kópiu/referenciu posledného prvku [implementovať bude xlevri01]
	- Length() - vráti počet prvkov vo fronte [implementovať bude xlevri01]
	- isEmpty() - vráti true/false podľa toho či je prázdna [implementovať bude xlevri01]
	- Clear() - vymaže všetky prvky vo fronte [implementovať bude xmagat01]
 
 Private methods:
	- \c Compare - porovná "velikost" dvou kontejnerů, kde velikost je dána počtem prvků, a vrátí hodnotu -1,0 nebo 1 (první je kratší, stejné, první je delší). [implementovať bude xkunaj01]
	- \c CompareDeep - porovná velikost kontejnerů i podle hodnot \c CValue. [implementovať bude xkunaj01] 
Výsledky těchto metod budou ke své činnosti používat logické operátory kontejneru.
\note Pro privátní metody jsou nejvýhodnější funkce typu „uprav“, „přepočítej“, „zkontroluj“. Celkem tedy  – minimálně 2ks privátní a 4ks veřejné.
\note U každé z metod definujte nejen její název, ale uveďte i informaci, co bude jejím úkolem z hlediska funkce __fronty__ (tj. textově popište její funkci popř. smysl).

8. Budou realizovány metody, pro reverzaci (reverzace je __např. otočení pořadí prvků kontejneru__ ): 
	- umožňující volání \c bbb=aaa.Reverzuj(), která mění __frontu__ \c aaa na __reverzovanú frontu__ \c bbb,  [implementovať bude xkunaj01]
	- umožňující volání \c bbb=Reverzuj(aaa), která nechává __frontu__ \c aaa nezměněnú a vrací (temp objekt) __reverzovaný frontu__ \c bbb.  [implementovať bude xkunaj01]

9. Použití dynamických dat ve třídě – __ANO__.
10. Dědění  __NE__ ve třídě ... .
11. Použití výjimek - __ÁNO__.
12. Ve vlastním projektu se předpokládá i implementace metod vytvářených překladačem implicitně.
13. Ve třídě bude pro kontrolu korektní práce s pamětí implementována knihovna [Checker](http://www.uamt.feec.vutbr.cz/~petyovsky/projects/checker/checker.zip).

\todo testy??? 14. Pro každou implementovanou metodu navrhněte alespoň 3 case testy. 

\n\n
### Poznámky k řešení (jsou součástí zadání):

Odvozené třídy \c CValue_NAZEV_TYPU vypracujte v projektu CValue, kde je ve funkci \c main demonstrována činnost \c CValue_bool. Po odladění je použijte ve vlastním projektu testování \c CHashMap a tvorbě __fronty__, 
kde vytvořte v \c main podobný testovací kód (pro třídu fronty) jako je ukázáno v projektu s CValue.
Projekty CValue a CHashMap chápejte jako ukázkové projekty, které demonstrují principy práce s CValue, a s HashMap seznamy a všemi dodanými třídami. Věřím, že pro Vás bude cennou studnicí vědomostí a zároveň vhodným testovacím _pískovištěm_
k pokusům a experimentům. Proto si jeho činnost prostudujte a snažte se ho pochopit do co nejmenších detailů. Pokud Vám tento testovací projekt přestane fungovat, obnovte poslední fungující verzi z repozitáře a zkuste to znovu. ;-)
_Aneb kdo nic nerozbije, ten se nic nenaučí._

Vytvořená implementace __fronty__ bude využívat vlastnosti třídy \c CValue a musí umožňovat bezchybný překlad s libovolnou třídou \c CValue (zapouzdřující některý z jednoduchých datových typů) bez nutnosti zásahu 
do zdrojových textů __fronty__!!!!
Implementace fronty tedy nebude závislá na typu ukládaných hodnot, protože bude využívat pouze definované rozhraní třídy \c CValue (společné pro všechny typy), tak jak je uvedeno v testovacím příkladu. 
__CFronta__ proto implementujte tak, aby přímo nevyužíval (nevolal) Setter ani Getter metody třídy \c CValue, jejichž hlavička je na zapouzdřujícím typu závislá!!! 
Celá hierarchie souboru projektu je patrná na následujícím obrázku. _Nezapomeňte v obrázku upravit názvy tučně označených souborů._
\dotfile project_hierarchy.gv "Obr.1 - Nákres hierarchie souboru v projektu"
\n

Vlastní realizace třídy pro __kontejner__ bude rozdělena na hlavičkový a zdrojový soubor (__CFronta.h__, __CFronta.cpp__). Další zdrojový soubor (main.cpp) bude reprezentovat program demonstrující vlastnosti a použití 
definované třídy __CFronta__. Všechny zdrojové a hlavičkové soubory budou obsahovat úvodní poznámku o svém názvu, řešitelích...). 

Demonstrační program bude realizován jako konzolová aplikace přeložitelná ve Visual C++ (prázdný projekt, přísnost (stupeň) překladu 3 na detekci chybových a varovných hlášení). 
Snažte se, aby demonstrační program byl napsán tak, aby při činnosti nevyžadoval zásahy obsluhy ani vstupní data z jiných speciálních souborů (s výjimkou operátoru pro standardní vstup). 
Demonstrační/testovací programu bude inicializovat proměnné (v něm definovanými daty nezadávanými uživatelem) a na jejich základě bude demonstrovat činnost třídy a dále zobrazovat data na konzolu, 
nebo ukládat výsledky do souboru.
\ref doc "Dokumentaci" výsledného projektu  realizujte pomocí nástroje [Doxygen](http://www.doxygen.org).

K tomuto odevzdávanému zadání nezapomeňte připsat úvod pro hlavičku (tj. jména řešitelů, název projektu, datum zadání ... budou součástí odevzdávaného souboru)

Na následujícím odkazu najdete [Myšlenkovou mapu k projektu](https://my.mindnode.com/s2Bbn2gFS8pHZFGcZJhRj4U7zmxx8ivygkoPCuZz), kterou jsme tvořili během
přednášky věnované projektu. Pro lepší orientaci uvádíme krátkou motivaci k pojmu třída na odkazu:
[Motivace třída](http://www.uamt.feec.vutbr.cz/~richter/vyuka/XPPC/bppc/cviceni/motivace_trida.html).


Pokud Vás trápí nastavení [Unit testů](https://en.wikipedia.org/wiki/Test-driven_development) ve VS2017 zkuste si projít [tento postup](http://www.evernote.com/l/AElAKsn_ps1ONbQRPVcvgmGPXcK76B0P0qs/).
\n\n
Poslední změna: $Date:: 2017-12-29#$

$Id: Introduction.md 2995 2017-12-29 01:59:30Z xmagat01 $
