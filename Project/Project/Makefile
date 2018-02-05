## Simple Project makefile example by: Pety 2017
## $Id: Makefile 1763 2017-12-11 15:25:59Z xkunaj01 $

##CXX = clang++
CXX = g++
CXXFLAGS = -c -O3 -std=c++11 -frtti -Wall -Wextra -pedantic -Wno-keyword-macro
LDFLAGS =
RM = rm -f

.PHONY: all docs openhtmldocs run clean cleandocs

all: Project

Project: main.o CContainer.o CHashMap.o CPair.o CValue_TWeekDay.o check.o demagle.o
	$(CXX) $(LDFLAGS) -o CHashMap main.o CContainer.o CHashMap.o CPair.o CValue_TWeekDay.o check.o demagle.o

main.o: main.cpp CHashMap.h CPair.h CValue.h CValue_bool.h CValue_TWeekDay.h ClassInfo.h demagle.h check.h
	$(CXX) $(CXXFLAGS) main.cpp

CContainer.o: CContainer.cpp CContainer.h CHashMap.h CPair.h CValue.h CValue_bool.h CValue_TWeekDay.h ClassInfo.h demagle.h check.h
	$(CXX) $(CXXFLAGS) CContainer.cpp

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

docs: Doxyfile Introduction.md Documentation.md main.cpp CHashMap.h CHashMap.cpp CPair.h CPair.cpp CValue.h CValue_bool.h CValue_TWeekDay.h CValue_TWeekDay.cpp demagle.h demagle.cpp ClassInfo.h
	export LC_CTYPE="en_US.UTF-8"; doxygen Doxyfile

opendocs: docs
	open html/index.html

run: CHashMap
	./CHashMap

clean:
	-$(RM) CHashMap main.o CContainer.o CHashMap.o CPair.o CValue_TWeekDay.o check.o demagle.o

cleandocs:
	-$(RM) -r html latex
