simulator: MIPS.o main.o
	g++ MIPS.o main.o -o bin/mips_simulator

MIPS.o: MIPS.cpp MIPS.hpp
	g++ -c MIPS.cpp

main.o: main.cpp
	g++ -c main.cpp

testbench: testbench2.cpp
	g++ testbench2.cpp -o testbench

run:
	./bin/mips_simulator sub2.exe
#./prog.exe if Windows/Cygwin
