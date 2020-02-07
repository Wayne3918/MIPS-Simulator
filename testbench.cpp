#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <string> tests;
vector <string> specs;
vector <string> usernames;
vector <int> answer;
vector <string> testID;
string sim;
//Apparently testbench had to be slightly modified to work on Linux and this is a Linux version of it.
// To make it work on Windows just remove "./" and change "/" in addresses of the tests to "\\"


string GetStdoutFromCommand(string cmd)
{
  string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");
  stream = popen(cmd.c_str(), "r");
  if (stream)
  {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}

void run_test_getputc(string id, string spec, string filename, string username, int ans, string data_file, string output)
{
  string command = "./" + sim + " " + filename + " < " + data_file;
  int code = system(command.c_str()) / 256;
  string progout = GetStdoutFromCommand(command);
  cout << id << ", " << spec;
  if(code == ans and progout == output)
    cout << "Pass, ";
  else
    cout << "Fail, ";
  cout << username << "\n";
}

void run_test_putc(string id, string spec, string filename, string username, int ans, string output)
{
  string command = "./" + sim + " " + filename;
  int code = system(command.c_str()) / 256;
  string progout = GetStdoutFromCommand(command);
  cout << id << ", " << spec;
  if(code == ans and progout == output)
    cout << "Pass, ";
  else
    cout << "Fail, ";
  cout << username << "\n";
}

void run_test_getc(string id, string spec, string filename, string username, int ans, string data_file)
{
  string command = "./" + sim + " " + filename + " < " + data_file;
  int code = system(command.c_str()) / 256;
  cout << id << ", " << spec;
  if(code == ans)
    cout << "Pass, ";
  else
    cout << "Fail, ";
  cout << username << "\n";
}

void add_test(string id, string spec, string filename, string username, int ans)// testID, type of instr tested, location of the test, username, correct return code
{
  testID.push_back(id);
  tests.push_back(filename);
  specs.push_back(spec);
  usernames.push_back(username);
  answer.push_back(ans);
}

void run_test(int number)
{
  string command = "./" + sim + " " + tests[number];
  int code = system(command.c_str()) / 256;
  cout << testID[number] << ", " << specs[number];
  if(code == answer[number])
    cout << "Pass, ";
  else
    cout << "Fail, ";
  cout << usernames[number] << "\n";
}

int main(int argc, char** argv)
{
  sim = argv[1];
  add_test("test_jr", "JR, ", "tests/test_jr.exe", "jjm4618", 0);// if jr 0 works
  add_test("test1", "ADDI, ", "tests/test1.exe", "jjm4618", 7);// reg2 = 7
  add_test("test2", "ADDI, ", "tests/test2.exe", "jjm4618", 255);// reg2 = -1
  add_test("test3", "ADD, ", "tests/test3.exe", "jjm4618", 0);// reg2 = sum of all registers
  add_test("test4", "BNE, ", "tests/test4.exe", "jjm4618", 6);// reg1 = 5; bne reg1, reg2, -1; reg2 += 1;
  add_test("test5", "BEQ, ", "tests/test5.exe", "jjm4618", 6);// reg1 = 7; reg2 = 8; reg2 -= 1; beq reg1, reg2, -2; reg0 += 0;
  run_test_getc("test6", "LW_getchar, ", "tests/test6.exe", "jjm4618", 97, "data/test6.txt");
  add_test("test7", "LUI, ", "tests/test7.exe", "cw3918", 0);// reg2 = 0x10000000
  add_test("test8", "ADDU, ", "tests/test8.exe", "cw3918", 3);// reg2 = reg1 + reg0, reg1 = 2, reg0 = 1
  add_test("test9", "ADD(exception), ", "tests/test9.exe", "cw3918", -10);// reg2 = reg1 + reg0, reg1 = 0x50000000, reg0 = 0x50000000
  add_test("test10", "MFHI/MTHI, ", "tests/test10.exe", "cw3918", 5);// reg1 = 5 -> Hi -> reg2
  add_test("test11", "MFLO/MTLO, ", "tests/test11.exe", "cw3918", 5);// reg1 = 5 -> lo -> reg2
  add_test("test12", "DIV, ", "tests/test12.exe", "cw3918", 4);// reg0 = 20, reg1 = 5, reg2 = 20 / 5 = 4
  add_test("test13", "DIVU, ", "tests/test13.exe", "cw3918", 2);// reg0 = 0xa0000000, reg1 = 0x50000000, reg2 = reg0 / reg1
  add_test("test14", "SRA, ", "tests/test14.exe", "cw3918", 255);// reg0 = 0xc0000000, reg2 = sra reg0 >> 30
  add_test("test15", "SRL, ", "tests/test15.exe", "cw3918", 3);// reg0 = 0xc0000000, reg2 = srl reg0 >> 30
  add_test("test16", "SLL, ", "tests/test16.exe", "cw3918", 6);// reg0 = 3, reg2 = sll reg0 << 1
  add_test("test17", "SLLV, ", "tests/test17.exe", "cw3918", 48);// reg0 = 3, reg1 = 4 reg2 = reg0 << reg1
  //SRLV AND SRAV ARE SKIPPED SINCE THEY HAVE SIMILAR STRUCTURE TO SLLV
  add_test("test18", "MULT, ", "tests/test18.exe", "cw3918", 55);// reg0 = 5, reg1 = reg0 + 6, reg2 = reg0 * reg1
  add_test("test19", "MULTU, ", "tests/test19.exe", "cw3918", 4);// reg0 = 0x80020000 reg1 = 0x80020000 reg2 = reg0 * reg1
  add_test("test20", "SUBU, ", "tests/test20.exe", "cw3918", 254);// reg0 = 5, reg1 = 2, reg2 = reg1 - reg0
  add_test("test21", "SUB(exception), ", "tests/test21.exe", "cw3918", -10);// reg0 = 0x60000000, reg1 = 0xa0000000, reg2 = reg0 - reg1

  for(int i = 0; i < tests.size(); ++ i)
    run_test(i);
}
