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
  //cout << code << "\n";
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
  add_test("add1", "ADD, ", "tests/add1.exe", "jjm4618", 1);
  add_test("add2", "ADD, ", "tests/add2.exe", "jjm4618", 24);
  add_test("add3", "ADD, ", "tests/add3.exe", "jjm4618", -10 + 256);
  add_test("add4", "ADD, ", "tests/add4.exe", "jjm4618", -10 + 256);
  add_test("addi1", "ADDI, ", "tests/addi1.exe", "jjm4618", 255);
  add_test("addi2", "ADDI, ", "tests/addi2.exe", "jjm4618", 16);
  add_test("addi3", "ADDI, ", "tests/addi3.exe", "jjm4618", -10 + 256);
  add_test("addi4", "ADDI, ", "tests/addi4.exe", "jjm4618", -10 + 256);
  add_test("addiu1", "ADDIU, ", "tests/addiu1.exe", "jjm4618", 8);
  add_test("addiu2", "ADDIU, ", "tests/addiu2.exe", "jjm4618", 0);
  add_test("addu1", "ADDU, ", "tests/addu1.exe", "jjm4618", 27);
  add_test("addu2", "ADDU, ", "tests/addu2.exe", "jjm4618", 255);
  add_test("and1", "AND, ", "tests/and1.exe", "jjm4618", 0);
  add_test("and2", "AND, ", "tests/and2.exe", "jjm4618", 2);
  add_test("andi1", "ANDI, ", "tests/andi1.exe", "jjm4618", 97);
  add_test("andi2", "ANDI, ", "tests/andi2.exe", "jjm4618", 0);
  add_test("beq1", "BEQ, ", "tests/beq1.exe", "jjm4618", 1);
  add_test("beq2", "BEQ, ", "tests/beq2.exe", "jjm4618", 9);
  add_test("bgez1", "BGEZ, ", "tests/bgez1.exe", "jjm4618", 19);
  add_test("bgez2", "BGEZ, ", "tests/bgez2.exe", "jjm4618", 0);
  add_test("bgez3", "BGEZ, ", "tests/bgez3.exe", "jjm4618", 19);
  add_test("bgezal1", "BGEZAL, ", "tests/bgezal1.exe", "jjm4618", 19);
  add_test("bgezal2", "BGEZAL, ", "tests/bgezal2.exe", "jjm4618", 0);
  add_test("bgezal3", "BGEZAL, ", "tests/bgezal3.exe", "jjm4618", 19);
  add_test("bgtz1", "BGTZ, ", "tests/bgtz1.exe", "jjm4618", 19);
  add_test("bgtz2", "BGTZ, ", "tests/bgtz2.exe", "jjm4618", 0);
  add_test("bgtz3", "BGTZ, ", "tests/bgtz3.exe", "jjm4618", 0);
  add_test("blez1", "BLEZ, ", "tests/blez1.exe", "jjm4618", 0);
  add_test("blez2", "BLEZ, ", "tests/blez2.exe", "jjm4618", 19);
  add_test("blez3", "BLEZ, ", "tests/blez3.exe", "jjm4618", 19);
  add_test("bltz1", "BLTZ, ", "tests/bltz1.exe", "jjm4618", 0);
  add_test("bltz2", "BLTZ, ", "tests/bltz2.exe", "jjm4618", 19);
  add_test("bltz3", "BLTZ, ", "tests/bltz3.exe", "jjm4618", 0);
  add_test("bltzal1", "BLTZAL, ", "tests/bltzal1.exe", "jjm4618", 0);
  add_test("bltzal2", "BLTZAL, ", "tests/bltzal2.exe", "jjm4618", 19);
  add_test("bltzal3", "BLTZAL, ", "tests/bltzal3.exe", "jjm4618", 0);
  add_test("bne1", "BNE, ", "tests/bne1.exe", "jjm4618", 7);
  add_test("bne2", "BNE, ", "tests/bne2.exe", "jjm4618", 7);
  add_test("div1", "DIV, ", "tests/div1.exe", "jjm4618", 0);
  add_test("div2", "DIV, ", "tests/div2.exe", "jjm4618", 2);
  add_test("div3", "DIV, ", "tests/div3.exe", "jjm4618", -2 + 256);
  add_test("div4", "DIV, ", "tests/div4.exe", "jjm4618", 0);
  add_test("div5", "DIV, ", "tests/div5.exe", "jjm4618", 2);
  add_test("div6", "DIV, ", "tests/div6.exe", "jjm4618", 0);
  add_test("div7", "DIV, ", "tests/div7.exe", "jjm4618", 2);
  add_test("div8", "DIV, ", "tests/div8.exe", "jjm4618", 1);
  add_test("divu1", "DIVU, ", "tests/divu1.exe", "jjm4618", 0);
  add_test("divu2", "DIVU, ", "tests/divu2.exe", "jjm4618", 7);
  add_test("j1", "J, ", "tests/j1.exe", "jjm4618", 14);
  add_test("j2", "J, ", "tests/j2.exe", "jjm4618", 8);
  add_test("jal1", "JAL, ", "tests/jal1.exe", "jjm4618", 21);
  add_test("jal2", "JAL, ", "tests/jal2.exe", "jjm4618", 15);
  add_test("jalr1", "JALR, ", "tests/jalr1.exe", "jjm4618", 2);
  add_test("sb1", "SB, ", "tests/sb1.exe", "jjm4618", 0);
  add_test("lb1", "LB, ", "tests/lb1.exe", "jjm4618", 7);
  add_test("sb2", "SB, ", "tests/sb2.exe", "jjm4618", 0);
  add_test("lb2", "LB, ", "tests/lb2.exe", "jjm4618", 7);
  add_test("sb3", "SB, ", "tests/sb3.exe", "jjm4618", 0);
  add_test("lb3", "LB, ", "tests/lb3.exe", "jjm4618", 7);
  add_test("sb4", "SB, ", "tests/sb4.exe", "jjm4618", 0);
  add_test("lb4", "LB, ", "tests/lb4.exe", "jjm4618", 7);
  add_test("sb5", "SB, ", "tests/sb5.exe", "jjm4618", 0);
  add_test("lb5", "LB, ", "tests/lb5.exe", "jjm4618", -1 + 256);
  add_test("lbu1", "LBU, ", "tests/lbu1.exe", "jjm4618", 0);
  add_test("lbu2", "LBU, ", "tests/lbu2.exe", "jjm4618", -1 + 256);
  add_test("sh1", "SH, ", "tests/sh1.exe", "jjm4618", 0);
  add_test("lh1", "LH, ", "tests/lh1.exe", "jjm4618", -1 + 256);
  add_test("lhu1", "LHU, ", "tests/lhu1.exe", "jjm4618", 0);
  add_test("lhu2", "LHU, ", "tests/lhu2.exe", "jjm4618", -1 + 256);
  add_test("lui1", "LUI, ", "tests/lui1.exe", "jjm4618", 0);
  add_test("lui2", "LUI, ", "tests/lui2.exe", "jjm4618", 12);
  run_test_getc("lw1", "LW, ", "tests/lw1.exe", "jjm4618", 97, "tests/data.txt");
  run_test_putc("sw1", "SW, ", "tests/sw1.exe", "jjm4618", 0, "a");
  run_test_getputc("lw2", "LW, ", "tests/lw2.exe", "jjm4618", 98, "tests/data2.txt", "a");
  add_test("lwl1", "LWL, ", "tests/lwl1.exe", "jjm4618", 7);
  add_test("lwr1", "LWR, ", "tests/lwr1.exe", "jjm4618", 7);
  add_test("mult1", "MULT, ", "tests/mult1.exe", "jjm4618", 1);
  add_test("mult2", "MULT, ", "tests/mult2.exe", "jjm4618", 0);
  add_test("mult3", "MULT, ", "tests/mult3.exe", "jjm4618", 1);
  add_test("multu1", "MULTU, ", "tests/multu1.exe", "jjm4618", 254);
  add_test("multu2", "MULTU, ", "tests/multu2.exe", "jjm4618", 1);
  add_test("or1", "OR, ", "tests/or1.exe", "jjm4618", 255);
  add_test("ori1", "ORI, ", "tests/ori1.exe", "jjm4618", 255);
  add_test("ori2", "ORI, ", "tests/ori2.exe", "jjm4618", 0);
  add_test("sll1", "SLL, ", "tests/sll1.exe", "jjm4618", 2);
  add_test("sll2", "SLL, ", "tests/sll2.exe", "jjm4618", 254);
  add_test("sllv1", "SLLV, ", "tests/sllv1.exe", "jjm4618", 1);
  add_test("slt1", "SLT, ", "tests/slt1.exe", "jjm4618", 1);
  add_test("slt2", "SLT, ", "tests/slt2.exe", "jjm4618", 0);
  add_test("slt3", "SLT, ", "tests/slt3.exe", "jjm4618", 0);
  add_test("slti1", "SLTI, ", "tests/slti1.exe", "jjm4618", 1);
  add_test("sltiu1", "SLTIU, ", "tests/sltiu1.exe", "jjm4618", 0);
  add_test("sltu1", "SLTU, ", "tests/sltu1.exe", "jjm4618", 1);
  add_test("sltu2", "SLTU, ", "tests/sltu2.exe", "jjm4618", 0);
  add_test("sltu3", "SLTU, ", "tests/sltu3.exe", "jjm4618", 0);
  add_test("sra", "SRA, ", "tests/sra.exe", "jjm4618", 1);
  add_test("sra1", "SRA, ", "tests/sra1.exe", "jjm4618", 255);
  add_test("sra2", "SRA, ", "tests/sra2.exe", "jjm4618", 255);
  add_test("srav1", "SRAV, ", "tests/srav1.exe", "jjm4618", 255);
  add_test("srav2", "SRAV, ", "tests/srav2.exe", "jjm4618", 0);
  add_test("sub1", "SUB, ", "tests/sub1.exe", "jjm4618", 0);
  add_test("sub2", "SUB, ", "tests/sub2.exe", "jjm4618", 246);
  add_test("sub3", "SUB, ", "tests/sub3.exe", "jjm4618", 1);
  add_test("xor1", "XOR, ", "tests/xor1.exe", "jjm4618", 5);
  add_test("xori1", "XORI, ", "tests/xori1.exe", "jjm4618", 0);
  add_test("xori2", "XORI, ", "tests/xori2.exe", "jjm4618", 255);
  add_test("test7", "LUI, ", "tests/test7.exe", "cw3918", 0);//ref: testcode/test7.txt
  add_test("test8", "ADDU, ", "tests/test8.exe", "cw3918", 3);//ref: testcode/test8.txt
  add_test("test9", "ADD(exception), ", "tests/test9.exe", "cw3918", -10 + 256);//ref: testcode/test9.txt
  add_test("test10", "MFHI/MTHI, ", "tests/test10.exe", "cw3918", 5);//ref: testcode/test10.txt
  add_test("test11", "MFLO/MTLO, ", "tests/test11.exe", "cw3918", 5);//ref: testcode/test11.txt
  add_test("test12", "DIV, ", "tests/test12.exe", "cw3918", 4);//ref: testcode/test12.txt
  add_test("test13", "DIVU, ", "tests/test13.exe", "cw3918", 2);//ref: testcode/test13.txt
  add_test("test14", "SRA, ", "tests/test14.exe", "cw3918", 255);//ref: testcode/test14.txt
  add_test("test15", "SRL, ", "tests/test15.exe", "cw3918", 3);//ref: testcode/test15.txt
  add_test("test16", "SLL, ", "tests/test16.exe", "cw3918", 6);//ref: testcode/test16.txt
  add_test("test17", "SLLV, ", "tests/test17.exe", "cw3918", 48);//ref: testcode/test17.txt
  add_test("test18", "MULT, ", "tests/test18.exe", "cw3918", 55);//ref: testcode/test18.txt
  add_test("test19", "MULTU, ", "tests/test19.exe", "cw3918", 4);//ref: testcode/test19.txt
  add_test("test20", "SUBU, ", "tests/test20.exe", "cw3918", 254);//ref: testcode/test20.txt
  add_test("test21", "SUB(exception), ", "tests/test21.exe", "cw3918", -10 + 256);//ref: testcode/test21.txt
  add_test("test22", "OR, ", "tests/test22.exe", "cw3918", 31);//ref: testcode/test22.txt
  add_test("test23", "AND, ", "tests/test23.exe", "cw3918", 16);//ref: testcode/test23.txt
  add_test("test24", "ORI, ", "tests/test24.exe", "cw3918", 55);//ref: testcode/test24.txt
  add_test("test25", "ANDI, ", "tests/test25.exe", "cw3918", 18);//ref: testcode/test25.txt
  add_test("test26", "XOR, ", "tests/test26.exe", "cw3918", 15);//ref: testcode/test26.txt
  add_test("test27", "XORI, ", "tests/test27.exe", "cw3918",37);//ref: testcode/test27.txt
  add_test("test28", "BGEZ, ", "tests/test28.exe", "cw3918",6);//ref: testcode/test28.txt
  add_test("test29", "BGTZ, ", "tests/test29.exe", "cw3918",5);//ref: testcode/test29.txt
  add_test("test30", "BLEZ, ", "tests/test30.exe", "cw3918",6);//ref: testcode/test30.txt
  add_test("test31", "BLTZ, ", "tests/test31.exe", "cw3918",5);//ref: testcode/test31.txt
  add_test("test32", "BLTZAL, ", "tests/test32.exe", "cw3918",12);//ref: testcode/test32.txt
  add_test("test33", "BGEZAL, ", "tests/test33.exe", "cw3918",12);//ref: testcode/test33.txt
  add_test("test34", "J, ", "tests/test34.exe", "cw3918",3);//ref: testcode/test34.txt
  add_test("test35", "JR, ", "tests/test35.exe", "cw3918",3);//ref: testcode/test35.txt
  add_test("test36", "JALR, ", "tests/test36.exe", "cw3918",16);//ref: testcode/test36.txt
  add_test("test37", "JAL, ", "tests/test37.exe", "cw3918",8);//ref: testcode/test37.txt
  add_test("test38", "LB/SB(0x20000000), ", "tests/test38.exe", "cw3918",8);//ref: testcode/test38.txt
  add_test("test39", "LH/SH(0x20000000), ", "tests/test39.exe", "cw3918",8);//ref: testcode/test39.txt
  add_test("test40", "LW/SW(0x20000000), ", "tests/test40.exe", "cw3918",4);//ref: testcode/test40.txt
  for(int i = 0; i < tests.size(); ++ i)
    run_test(i);
}
