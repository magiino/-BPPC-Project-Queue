## Simple CHashMap makefile example by: Pety 2017
## $Id: Makefile 136 2017-11-06 17:38:46Z petyovsky $

##CXX = clang++
CXX = g++
CXXFLAGS = -c -O3 -std=c++11 -frtti -Wall -Wextra -pedantic -Wno-keyword-macro
LDFLAGS =
RM = rm -f

.PHONY: all docs openhtmldocs run clean cleandocs

all: CHashMap

CHashMap: main.o CHashMap.o CPair.o CValue_TWeekDay.o check.o demagle.o
	$(CXX) $(LDFLAGS) -o CHashMap main.o CHashMap.o CPair.o CValue_TWeekDay.o check.o demagle.o

main.o: main.cpp CHashMap.h CPair.h CValue.h CValue_bool.h CValue_TWeekDay.h ClassInfo.h demagle.h check.h
	$(CXX) $(CXXFLAGS) main.cpp

CHashMap.o: CHashMap.cpp CHashMap.h CPair.h CValue.h CValue_bool.h CValue_TWeekDay.h ClassInfo.h demagle.h check.h
	$(CXX) $(CXXFLAGS) CHashMap.cpp

CPair.o: CPair.cpp CPair.h CValue.h CValue_bool.h CValue_TWeekDay.h ClassInfo.h demagle.h check.h
	$(CXX) $(CXXFLAGS) CPair.cpp

CValue_TWeekDay.o: CValue_TWeekDay.cpp CValue_TWeekDay.h ClassInfo.h demagle.h check.h
	$(CXX) $(CXXFLAGS) CValue_TWeekDay.cpp

check.o: check.cpp check.h
	$(CXX) $(CXXFLAGS) -Wno-unused-parameter -Wno-missing-field-initializers check.cpp

demagle.o: demagle.cpp demagle.h
	$(CXX) $(CXXFLAGS) demagle.cpp

docs: Doxyfile Introduction.md Documentation.md CPair.gv CHashMapPrimitive.gv CHashMap.gv main.cpp CHashMap.h CHashMap.cpp CPair.h CPair.cpp CValue.h CValue_bool.h CValue_TWeekDay.h CValue_TWeekDay.cpp demagle.h demagle.cpp ClassInfo.h
	export LC_CTYPE="en_US.UTF-8"; doxygen Doxyfile

opendocs: docs
	open html/index.html

run: CHashMap
	./CHashMap

clean:
	-$(RM) CHashMap main.o CHashMap.o CPair.o CValue_TWeekDay.o check.o demagle.o

cleandocs:
	-$(RM) -r html latex
