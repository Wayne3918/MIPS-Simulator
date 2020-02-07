#include "MIPS.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  string filename = argv[1];
  MIPS a;
  a.read_binary(filename);

  while(true)
  {
    int b = a.load_instr();
    //cout << hex << b << "\n";
    //return 0;
    a.execute_instr(b);
    //a.REG(2);
  }
}
