PRG=gnu.exe
GCC=g++
GCCFLAGS=-O2 -Wall -Wextra -std=c++11 -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -Wsign-promo  -Wctor-dtor-privacy -Wnon-virtual-dtor -Wreorder

MSC=cl
MSCFLAGS=/EHa /W4 /Za /Zc:forScope /nologo /D_CRT_SECURE_NO_DEPRECATE /D"_SECURE_SCL 0" /O2i /GL

VALGRIND_OPTIONS=-q --leak-check=full
DIFFLAGS=--strip-trailing-cr -y --suppress-common-lines

OBJECTS0=knapsack_brute_force_minchange.cpp definitions.cpp
DRIVER0=driver.cpp

OSTYPE := $(shell uname)
ifeq (,$(findstring CYGWIN,$(OSTYPE)))
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

gcc0:
	$(GCC) -o $(PRG) $(CYGWIN) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS)
msc0:
	$(MSC) /Fe$@.exe           $(DRIVER0) $(OBJECTS0) $(MSCFLAGS)
0 1 3 4:
	@echo "running test$@"
	@echo "should run in less than 200 ms"
	./$(PRG) $@ >studentout$@
	diff out$@ studentout$@ $(DIFFLAGS) > difference$@
2 5:
	@echo "running test$@"
	@echo "should run in less than 1800 ms"
	./$(PRG) $@ >studentout$@
	diff out$@ studentout$@ $(DIFFLAGS) > difference$@
mem0 mem4:
	@echo "running memory test $@"
clean:
	rm -f *gcno *gcda *gcov *.exe *.o *.obj *.tds
