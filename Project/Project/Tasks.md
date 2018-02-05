\page Tasks Požadavky na dokončení projektu CKontejner
\n
1.	U všech tří projektů (CValue, CHashMap, Project) vyřešit poznámky z minulé
	opravy. Projít stránku Bug a doxygen prikazy bug přepsat na bugfix. Za
	poznámku z opravy připsat, kdo opravil a jak opravil (tj. jak se poznámka
	vyřešila - u jednoduchých poznámek nebo obecných upozornění stačí jméno, kdo
	upravil na bugfix). Výsledný projekt tedy bude obsahovat funkční CValue,
	CHashMap a Project (shrnutý v Project, ale zpětně funkční).\n
\n
2.	Zadání a realizaci projektu kontrolovat proti původní dodané šabloně zadání
	a doplnit chybějící metody a prvky. (= konstruktory a destruktor. Možnost
	zjistit ID a počty prvků třídy. Operátory včetně nečlenského a konverzního.
	Streamy. Privátní a veřejné metody. Dvojici metod "typu Reverzuj".)
	Nejčastější chyby (zatím popsané pro datový typ loňský CXItem) najdete na -
	[http://www.uamt.feec.vutbr.cz/~richter/vyuka/XPPC/bppc/cviceni/chyby_hlavicka.html](http://www.uamt.feec.vutbr.cz/%7Erichter/vyuka/XPPC/bppc/cviceni/chyby_hlavicka.html)\n
\n
3.	Projekt musí jít přeložit bez chyb a bez významných varování (warnings). Bude
	obsahovat knihovnu Check.\n
\n
4.	Realizujte kontejner pro jeden svůj datový typ CValue, který musí projít
	testy prvního projektu CValue s originálním main. (tj. změna na CValue pro
	bool by neměla způsobit problémy v kontejneru).\n
\n
5.	V hlavičkovém souboru v definici třídy budou pouze prototypy metod a funkcí.
	Celé metody s těly budou buď ve zdrojovém souboru nebo inline za definicí
	třídy.\n
\n
6.	Napište main ve stejném stylu jako u projektu CValue a CHashMap s voláním
	všech vytvořených metod kontejneru. Část kódu demonstrující vstup z
	klávesnice dejte do komentáře "//".\n
\n
7.	Kde to u parametrů nebo návratových hodnot je možné, bude použita reference.
	U parametrů které se nemění včetně \c this bude \c const.\n
\n
8.	Vytvořte testy. Pro každou metodu bude test obsahovat alespoň tři testy (=
	testový \c assert. Alespoň jeden bude "významný" tj. nebudou např.  všechny
	jeho proměnné vytvořené implicitními kontejnery).\n
\n
9.	U čtyř testů proveďte i test paměti. U ostatních může být pouze test na
	funkčnost.\n
\n
10.	Vytvoření dokumentace pomocí doxygen proběhne bez varování (warnings) (zkuste na
	příkazovém řádku příkaz \c "doxygen 2>err.txt" , který uloží do souboru
	err.txt chybová hlášení a na obrazovce ponechá pouze informační texty).\n
\n
11.	V dokumentaci bude ponecháno zadání z doby opravování - nemazat. K němu
	dopište změny na základě poznámek (bug) a změny, ke kterým jste se rozhodli
	během realizace.\n
\n
12.	V dokumentaci popište, co je váš kontejner, definujte jeho chování vůči
	klíči a hodnotě (= popište koncepci třídy). Popište vlastnosti a chování
	metod charakteristických pro daný kontejner.\n
\n
13.	Napište dokumentaci pro členy třídy. U metod popište jejich činnost, funkci
	argumentů a návratové hodnoty. Dokumentace musí souhlasit s aktuální verzí
	zdrojových textů.\n
\n
14.	Napište hodnocení/závěr, ve kterém popište nedostatky vašeho řešení (Co jste
	případně nestihli. Proč jste byli nuceni změnit zadáni, hlavičku (oproti
	odevzdané verzi). Jaký k tomu byl důvod.).\n
\n
15.	**Všichni členové teamu budou mít srovnatelný a dostatečný počet komitů do
	svn.**
\n
\n
$Id: Tasks.md 1763 2017-12-11 15:25:59Z xkunaj01 $
