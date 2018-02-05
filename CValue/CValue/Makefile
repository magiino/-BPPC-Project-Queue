## Simple CValue makefile example by: Pety 2017
## $Id: Makefile 1 2017-11-06 09:45:38Z petyovsky $

##CXX = clang++
CXX = g++
CXXFLAGS = -c -O3 -std=c++11 -frtti -Wall -Wextra -pedantic -Wno-keyword-macro
LDFLAGS =
RM = rm -f

.PHONY: all docs openhtmldocs run clean cleandocs
	
all: CValue

CValue: main.o CValue_TWeekDay.o check.o demagle.o
	$(CXX) $(LDFLAGS) -o CValue main.o CValue_TWeekDay.o check.o demagle.o

main.o: main.cpp CValue.h CValue_bool.h CValue_TWeekDay.h ClassInfo.h demagle.h check.h
	$(CXX) $(CXXFLAGS) main.cpp

CValue_TWeekDay.o: CValue_TWeekDay.cpp CValue_TWeekDay.h ClassInfo.h demagle.h check.h
	$(CXX) $(CXXFLAGS) CValue_TWeekDay.cpp

check.o: check.cpp check.h
	$(CXX) $(CXXFLAGS) -Wno-unused-parameter -Wno-missing-field-initializers check.cpp

demagle.o: demagle.cpp demagle.h
	$(CXX) $(CXXFLAGS) demagle.cpp

docs: Doxyfile ClassInfo.h demagle.cpp demagle.h CValue_TWeekDay.cpp CValue_TWeekDay.h CValue_bool.h CValue.h main.cpp Introduction.md Documentation.md
	export LC_CTYPE="en_US.UTF-8"; doxygen Doxyfile

opendocs: docs
	open html/index.html

run: CValue
	./CValue

clean:
	-$(RM) CValue main.o CValue_TWeekDay.o check.o demagle.o

cleandocs:
	-$(RM) -r html latex
