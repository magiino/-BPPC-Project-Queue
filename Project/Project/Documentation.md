\page doc Dokumentace projektu CKontejner

## Základní popis
Tady jednou bude dokumentace Vašeho projektu. ;-)\n
Pro její realizaci pomocí dokumentačního nástroje [Doxygen](http://www.doxygen.org) můžete využít tento [manual](http://www.doxygen.org/manual/index.html).

### Trieda CFronta

Táto trieda slúži ako wraper na triedu CHashMap. K CHashMap sa správame ako k fronte.
A to tak že sa k nej správame ako ku kontajneru kde prvok ktorý prvý vložíme aj prvý vyberáme.
Táto trieda si sama spravuje indexi prvkov. V tejto triede sú uložené indexi prvého uloženého prvku a poslendného.
Vždy ked sa pridá prvok do fronty inkeremntuje sa index, ktorý drží údaj o poslednom prvku vo fronte.
V prípade ak vyberieme posledný prvok si táto fronta vyresetuje indexi o prvom a poslednom prvku na nulu.
Prvky sa do tejto fronty kopírujú!
Táto trieda tak isto obsahuje friend metódy pre výpis na konzoĺu a nečlenský operátor ktorý slúži na pridanie CValue do tejto fronty.
Tieto operátory je potrebné používať so správnym formátom stringu.
Podrobné informácie o každej metóde nájdete v dokumentácii.

Táto trieda obsahuje HashMapu a dve čísla ktoré držia informácie o indexe prvom a poslendom prvku.
HashMapa príjma do seba prvky typu CValue. Celkovo táto trieda obsahuje 6 konštruktorov niekoľko operátorov medzi ktorými sú binárne, unárne, konverzný a operátory pre vípis na konzolu.

### Záver
Pri navrhovaní tejto triedy, sme niekoľko krát boli nútený pozmeniť zadanie, či už z dúvodu zlého pochopenia zadania, alebo sme si uvedomili že tak ako sme to najprv navrhli to nemôže fungovať.
V prípade že sa vstupná hodnota v metódach nemení, bola predaná ako konštanta. Používaním triedy ClassInfo sme mohli sledovať ako sa vytvárajú nové objekty CValue pri vkladaní a vyberaní z fronty.


$Id: Documentation.md 3569 2018-01-02 22:42:23Z xmagat01 $
