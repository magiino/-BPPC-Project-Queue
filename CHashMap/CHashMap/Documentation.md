\page doc Dokumentace projektu CHashMap

## Teoretický popis: Termín datový kontejner a datová struktura HashMap
Termín kontejner představuje v oblasti návrhu datových struktur a algoritmů takový datový typ, 
který umožňuje za běhu programu sdružovat více prvků (stejného nebo i různého typu) do jedné 
složené datové struktury. Výhody spojené s používáním kontejneru lze najít například v jednoduchém 
předání všech prvků takového kontejneru do funkce pomocí jediného parametru (typu kontejner), 
nebo pro předání více hodnot z funkce, kde návratovou hodnotou je opět jediná hodnota (typu kontejner).
Hlavní výhodou je ovšem možnost provedení operace nad všemi prvky kontejneru pomocí zápisu jediného 
volání služby, kterou zajistí přímo daný kontejner v rámci svého API. Mezi takové služby může patřit 
dealokace paměti všech prvků v kontejneru, vytisknutí všech prvků v kontejneru a další operace spojené 
se správou prvků v kontejneru.


Datový kontejner bude ve Vašem projektu realizován pomocí datové sktruktury 
[Hash table](https://en.wikipedia.org/wiki/Hash_table) (neuspořádané pole prvků (tj. seznam prvků s klíčem/indexem a hodnotou).
Tato datová struktura vychází svými základy z 
[lineárního jednosměrně vázaného seznamu](https://en.wikipedia.org/wiki/Linked_list), 
ale rozšiřuje jej o možnost časově efektivního průchodu seznamem při hledání konkrétního prvku.
Modifikací datové struktury hašovací tabulky je HashMapa resp.
[HashMultiMapa] (https://en.wikipedia.org/wiki/Multimap) umožňujicí vícenásobné vložení prvků se stejným klíčem
případně i se stejným klíčem a hodnotou.


HashMapa se tedy skládá z pole jednosměrně vázaných seznamů (v projektu proměnná \ref CHashMap::iBucketTable "iBucketTable"). 
Základním prvkem jednosměrně vázaného seznamu je struktura \ref CHashMap::TItem "TItem", 
která obsahuje ukazatel na další prvek v seznamu a datový člen. 
Datovým členem je třída CPair, která obsahuje klíč a vlastní hodnotu. Vlastní hodnota je reprezentována 
prvkem třídy \ref CValue_bool::CValue "CValue".

Pro činnost HashMap je důležitá HashFunction (tzv. hašovací funkce), ve třídě CHashMap je to 
metoda \ref CHashMap::CalculateHash "CalculateHash()"), která na základě hodnoty klíče určí index lineárního seznamu v 
poli \ref CHashMap::iBucketTable "iBucketTable", do kterého daný pár klíč/hodnota patří. 

Počet prvků tabulky \ref CHashMap::iBucketTableSize "iBucketTableSize" se vhodně zvolí na základě dané úlohy. 
Tomuto počtu musí odpovídat výsledky hašovací funkce, která by měla rozdělovat prvky do tabulky statisticky rovnoměrně
a to pro celý předpokládaný rozsah hodnot klíčů.

Hašovací tabulka  je reprezentovaná polem prvků typu \ref CHashMap::TBucket "TBucket", který pro manipulaci se 
seznamy obsahuje ukazatele na první \ref CHashMap::TBucket::iHead "iHead" 
a poslední \ref CHashMap::TBucket::iTail "iTail" položku lineárního seznamu. 
Pokud pro danou položku (hash kód) nebyl vložen žádný prvek, odkazují oba ukazatele na hodnotu \c nullptr.

Využití principu hašování má tu výhodu, že pro hodnoty klíčů, které mohou nabývat širokého rozsahu a mít nerovnoměrný výskyt, 
provede hašovací funkce přepočet klíče na index (\c idx) o daleko menším rozsáhu (vznikne tzv. otisk či miniatura hodnoty původního klíče). 

Vytvoření hašovací tabulky (tj. tabulky miniatur) obsahující počátky jednotlivých lineárně vázaných seznamů je dosaženo 
"relativně" paměťově úsporného kontejneru, ale také výpočetně efektivního přístupu k nalezení položky s daným klíčem 
(ve srovnání s jediným lineárním seznamem všech prvků).


\dotfile CPair.gv "Obr. 1 - Instance třídy \c CPair představující pár s datovými složkami klíč a hodnota"
\n

\dotfile CHashMapPrimitive.gv "Obr. 2 - Příklad elementárního seznamu uloženého ve struktuře \c TBucket se třemi prvky \c TItem"
\n

\dotfile CHashMap.gv "Obr. 3 - Princip uložení šesti prvků \c CPair {0,'A'}, {1,'B'}, {1,'C'}, {3,'D'}, {5,'E'}, {11,'F'} v multimapě \c CHashmap"
\n


\n


## Popis implementace
V tomto školním C++ projektu je HashMapa realizována za pomocí pole lineárních seznamů. Pro svou činnost definuje a využívá další pomocné datové typy.
Pro pole lineárních seznamů používá datový typ \ref CHashMap::TBucket "TBucket", který obsahuje ukazatele na první a poslední prvek lineárního seznamu. Lineární seznam je tvořen za
pomoci prvků datového typu \ref CHashMap::TItem "TItem", který obsahuje datový prvek a ukazatel na další položku v lineárním seznamu. 
Datový prvek je realizován pomocí typu CPair, který obsahuje dvojici klíč a vlastní hodnotu. Hodnota je realizována jedním z 
připravených typů \ref CValue_bool::CValue "CValue".

Pro práci s prvky HashMap seznamu je vytvořen iterátor (\ref CHashMap::CForwardIterator "CForwardIterator"), který realizuje dopředné procházení seznamu. 
Dále jsou pro práci s prvky HashMap předdefinovány konstanty, které umožňují řešit různý přístup k duplicitním prvkům při 
hledání (CHashMap::TAt), a nebo určit implicitní způsob řazení prvků (CHashMap::TInsert).

__Celý projekt kontejneru budete realizovat bez podpory standardních kontejnerových typů knihovny STL nebo jiných knihoven třetích stran!__


### Třída CHashMap
Třída  CHashMap je základní třídou, která realizuje mechanizmus uchování prvků a určuje způsob jakým se s nimi pracuje.
Princip uložení prvků je mechanizmus HashMap, kdy na základě klíče datové položky je 
určena pozice dvojice klíč/hodnota v HashMap. Za pomoci hašovací funkce CHashMap::CalculateHash je
pomocí klíče v tabulce určen lineární seznam, do kterého daná položka (vkládaná, vybíraná, hledaná ...)
patří. 
Základním prvkem třídy CHashMap je pole struktur \ref CHashMap::TBucket "TBucket", které odkazuje na jednotlivé lineární seznamy obsahující datové prvky. 
Tato třída realizuje kompletní funkčnost pro manipulaci s prvky (včetně práce s prvky lineárního seznamu).

Pro určení způsobu řazení prvků, které v seznamu existují vícenásobně (tj. ošetření dvojic se 
stejnými hodnotami klíč nebo i hodnota) jsou vytvořeny konstanty pomocí výčtového typu \ref CHashMap::TInsert "TInsert".
Promyslete si využití těchto hodnot pro realizaci Vašeho kontejneru. Je možné určit,
že se duplicita nezařadí, nebo že se zařadí před či za prvky se stejnými hodnotami.


### Třída CHashMap::CForwardIterator
Pro manipulaci s prvky kontejnerů jsou často používány iterátory. Iterátor slouží
k postupnému procházení kontejneru po jednotlivých prvcích. V projektu je 
vytvořen iterátor, který se váže na daný objekt CHashMap a umožňuje nastavení
své pozice na začátek nebo za konec prvků mapy. Umožňuje též procházení prvků
po jednom dopředu - prochází se prvky CHashMap a to tak, že se postupně prochází
jednotlivé lineární seznamy pole \ref CHashMap::iBucketTable "iBucketTable" mapy. 
Při nalezení posledního prvku v daném lineárního seznamu se začne procházet další
položka (další lineární seznam) z pole \ref CHashMap::iBucketTable "iBucketTable". 
Aktuální prvek, na který iterátor ukazuje je možné získat a pracovat s ním pomocí 
předdefinovaného \ref CHashMap::CForwardIterator::operator* " operátoru *" 
a \ref CHashMap::CForwardIterator::operator-> "operatoru ->".
Instance iterátoru vždy ověřuje, zda pomocí indexace přistupujeme k existujícímu prvku mapy 
a v případě neplatného indexu generuje výjimku \c std::out_of_range.
Dále je třeba vzít v úvahu skutečnost, že iterátor je asociován se zvolenou mapou pouze jednosměrně, 
tj. pokud z mapy odebereme prvek, iterátor nemá možnost se aktualizovat. 
Mapa neobsahuje seznam iterátorů, které vytvořila a nemůže tedy provést 
automatickou aktualizaci (změnu hodnoty) všech vytvořených iterátorů.


### Struktura CHashMap::TItem
Pomocná struktura, která slouží jako prvek lineárního seznamu. Obsahuje datový prvek 
třídy CPair se jménem \ref CHashMap::TItem::iPair "iPair" a ukazatel na další prvek seznamu \ref CHashMap::TItem::iNext "iNext". 
Je-li posledním prvkem, obsahuje ukazatel hodnotu \c nullptr. Vytvořený lineární seznam je v HashMap uchováván pomocí
odkazu v poli pomocných struktur \ref CHashMap::TBucket "TBucket".


### Struktura CHashMap::TBucket
Pomocná struktura, která ve třídě CHashMap slouží k uchování odkazů na jednotlivé
lineární seznamy. Každý prvek třídy \ref CHashMap::TBucket "TBucket" uchovává odkaz na první \ref CHashMap::TBucket::iHead "iHead" 
a poslední \ref CHashMap::TBucket::iTail "iTail" prvek téhož seznamu.
Neobsahuje-li žádný člen, jsou obě složky třídy nastaveny na \c nullptr.


### Třída CPair
Představuje kontejnerovou datovou strukturu, kterou využívá struktura \ref CHashMap::TItem "TItem" pro
uchování dat. Vlastní data se skládají z dvojice klíče \ref CPair::iKey "iKey" a hodnoty \ref CPair::iValue "iValue".


### Třída CValue
Třída \ref CValue_bool::CValue "CValue" obsahuje prvek (nebo prvky) mající hodnotu vkládanou do kontejneru. 
Úlohou třídy \ref CValue_bool::CValue "CValue" je zapouzdřit vlastní hodnotu - datovou složku \ref CValue_bool::CValue::iValue "iValue",
která představuje užitečná/pracovní data, která bude každý prvek seznamu obsahovat. 
Pro tuto třídu je třeba vhodně upravit (případně doplnit) metody určené pro konstrukci a 
likvidaci prvku tak, aby bylo možné nový prvek efektivně konstruovat a využívat.
Třída \ref CValue_bool::CValue "CValue" je navíc správcem své vlastní hodnoty \ref CValue_bool::CValue::iValue "iValue" a proto definuje 
základní metody pro zjištění, nastavení této hodnoty a zároveň zajišťuje pro 
nadřazené vyšší části programu metody pro porovnání dvou prvků \ref CValue_bool::CValue "CValue" dle 
této hodnoty,
čímž izoluje nadřazené části od nutnosti znát konkrétní datový typ 
složky \ref CValue_bool::CValue::iValue "iValue".
Využití této třídy v rámci CHashMap i výsledného kontejneru musí být ovšem takové,
aby CHashMap i výsledný kontejner pracovali s jakoukoli třídou \ref CValue_bool::CValue "CValue" jednotně, 
bez úprav kódu mapy nebo kontejneru.


### Třída ClassInfo
Třída ClassInfo implementuje mechanismus automatického počítání vzniklých objektů 
a mechanismus jednoznačné identifikace ClassInfo<>::ID "ID" instancí za běhu programu. 
Tento mechanismus se Vám bude hodit při ladění programu. 
Všechny Vaše třídy by měly obsahovat datovou složku \p iInstanceInfo třídy ClassInfo, 
čímž zajistíte Vašim třídám tyto ladicí vlastnosti. 
Samotná třída ClassInfo je definována jako šablona umožňující, 
vznik různých variant této třídy - (generické programování resp. metaprogramování).

Mezi ladicí metody třídy ClassInfo patří:
\li ClassInfo<T>::Total() - počítadlo vzniklých instancí třídy T
\li ClassInfo<T>::Living() - počítadlo v daném okamžiku existujících instancí třídy T
\li ClassInfo<T>::ID() resp. \ref CValue_bool::CValue::ID "CValue::ID()" - unikátní číselné označení dané instance


\attention Projděte si všechny uvedené kontrolní i ladicí mechanismy, snažte se pochopit jejich smysl a využití při trasování programu. Získané vědomosti se Vám budou rozhodně hodit, například když se nějaká část Vašeho programu začne chovat "nepřátelsky". 


\note 
Hodně štěstí při realizaci Vašeho projektu. Nebojte se, ono to půjde. Hlavně _nepropadejte panice!_ ;-)

Richter & Petyovský.

$Id: Documentation.md 2 2017-11-06 10:01:25Z petyovsky $
