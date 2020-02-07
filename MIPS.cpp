#include "MIPS.hpp"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

MIPS::MIPS()
{
  for(int i = 0; i < 32; ++i)
    R[i] = 0;

  PC = 0;
  maxPC = 1;
  LO = 0;
  HI = 0;
  BDS = false;

  for(int i = 0; i < 4; ++i)
  {
    ADDR_NULL[i] = 0;
    ADDR_GETC[i] = 0;
    ADDR_PUTC[i] = 0;
  }

  for(int i = 0; i < 0x1000000; ++i)
    ADDR_INSTR[i] = 0;

  for(int i = 0; i < 0x4000000; ++i)
    ADDR_DATA[i] = 0;

}

int MIPS::load_instr()
{
  R[0] = 0;
  int res = 0;
  unsigned char tmp;
  for(int i = 0; i < 4; ++i)
  {
    if(PC >= maxPC and BDS == false)
      this->exception(-11);
    if(PC >= 0x1000000)// we are outside INSTR memory
      this->exception(-11);
    tmp = ADDR_INSTR[PC];
    res = (res << 8) + tmp;
    ++PC;
  }
  return res;
}

void MIPS::read_binary(string filename)
{
  char temp[1];
  ifstream myFile (filename, ios::in | ios::binary);

  unsigned char byte;
  while(myFile.read(temp, 1) and PC < 0x1000000)
  {
    byte = temp[0];
    ADDR_INSTR[PC] = byte;
    ++PC;
    ++maxPC;
  }
  PC = 0;
  myFile.close();
}

void MIPS::execute_instr(unsigned instruction)
{
  int opcode = (instruction >> 26);
  if(opcode == 0)
    this->R_type(instruction);
  else if(opcode == 2 or opcode == 3)
    this->J_type(instruction);
  else
    this->I_type(instruction);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MIPS::R_type(unsigned instr)
{
  int function = (instr & 0x3F);// extracting ls 6 bits
  if(function == 0x20)
    this->ADD(instr);
  else if(function == 0x21)
    this->ADDU(instr);
  else if(function == 0x24)
    this->AND(instr);
  else if(function == 0x1A)
    this->DIV(instr);
  else if(function == 0x1B)
    this->DIVU(instr);
  else if(function == 0x09)
    this->JALR(instr);
  else if(function == 0x08)
    this->JR(instr);
  else if(function == 0x10)
    this->MFHI(instr);
  else if(function == 0x12)
    this->MFLO(instr);
  else if(function == 0x11)
    this->MTHI(instr);
  else if(function == 0x13)
    this->MTLO(instr);
  else if(function == 0x18)
    this->MULT(instr);
  else if(function == 0x19)
    this->MULTU(instr);
  else if(function == 0x25)
    this->OR(instr);
  else if(function == 0x00)
    this->SLL(instr);
  else if(function == 0x04)
    this->SLLV(instr);
  else if(function == 0x2A)
    this->SLT(instr);
  else if(function == 0x2B)
    this->SLTU(instr);
  else if(function == 0x03)
    this->SRA(instr);
  else if(function == 0x07)
    this->SRAV(instr);
  else if(function == 0x02)
    this->SRL(instr);
  else if(function == 0x06)
    this->SRLV(instr);
  else if(function == 0x22)
    this->SUB(instr);
  else if(function == 0x23)
    this->SUBU(instr);
  else if(function == 0x26)
    this->XOR(instr);
  else
    this->exception(-12);
}

void MIPS::ADD(unsigned instr)
{
  int rt, rs, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);
  int n1, n2, res;
  n1 = R[rs];
  n2 = R[rt];
  res = n1 + n2;
  if((n1 > 0 and n2 > 0 and res <= 0) or (n1 < 0 and n2 < 0 and res >= 0))
    this->exception(-10);// we have an overflow
  R[dest] = res;
}

void MIPS::ADDU(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);
  int n1, n2, res;
  n1 = R[rs];
  n2 = R[rt];
  res = n1 + n2;
  R[dest] = res;
}

void MIPS::AND(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);
  int n1, n2, res;
  n1 = R[rs];
  n2 = R[rt];
  res = (n1 & n2);
  R[dest] = res;
}

void MIPS::DIV(unsigned instr)
{
  int s1, s2;
  const int bit5 = 0x1F;
  if(((instr >> 6) & 0x3FF) != 0)
    this->exception(-12);
  s2 = ((instr >> 16) & bit5);
  s1 = ((instr >> 21) & bit5);
  int n1, n2;
  n1 = R[s1];
  n2 = R[s2];
  if(n2 == 0)
    return;// we can't throw an exception so we just do nothing
  LO = n1 / n2;
  HI = n1 % n2;
}


void MIPS::DIVU(unsigned instr)
{
  int s1, s2;
  const int bit5 = 0x1F;
  if(((instr >> 6) & 0x3FF) != 0)
    this->exception(-12);
  s2 = ((instr >> 16) & bit5);
  s1 = ((instr >> 21) & bit5);
  unsigned int n1, n2;
  n1 = R[s1];
  n2 = R[s2];
  if(n2 == 0)
    return;
  LO = n1 / n2;
  HI = n1 % n2;
}

void MIPS::JALR(unsigned instr)
{
  int s1, s2;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0 or ((instr >> 16) & bit5) != 0)
    this->exception(-12);
  s2 = ((instr >> 11) & bit5);
  s1 = ((instr >> 21) & bit5);
  int index, tmpPC;
  tmpPC = PC + 0x10000000;
  index = R[s1];
  if(BDS == true)
    return;
  BDS = true;
  this->execute_instr(this->load_instr());
  BDS = false;
  if(index % 4 != 0)
    this->exception(-11);// address is not alligned
  if(index == 0)
    this->terminate();
  if(index < 0x10000000 or index >= 0x11000000)// we want to jump outside the memory range and not terminate the simulation
    this->exception(-11);
  R[s2] = tmpPC + 4;// place the return link (second instruction following the branch)
  PC = index - 0x10000000;
}

void MIPS::JR(unsigned instr)
{

  int s1;
  const int bit5 = 0x1F;
  if(((instr >> 6) & 0x7FFF) != 0)
    this->exception(-12);
  s1 = ((instr >> 21) & bit5);
  int index;
  index = R[s1];
  if(BDS == true)
    return;
  BDS = true;
  this->execute_instr(this->load_instr());
  BDS = false;
  //cout << index;
  if(index % 4 != 0)
    this->exception(-11);// address is not alligned
  if(index == 0)
    this->terminate();
  if(index < 0x10000000 or index >= 0x11000000)// we want to jump outside the memory range and not terminate the simulation
    this->exception(-11);
  PC = index - 0x10000000;
}

void MIPS::MFHI(unsigned instr)
{
  int dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0  or ((instr >> 16) & 0x3FF) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  R[dest] = HI;
}

void MIPS::MFLO(unsigned instr)
{
  int dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0  or ((instr >> 16) & 0x3FF) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  R[dest] = LO;
}

void MIPS::MTHI(unsigned instr)
{
  int s1;
  const int bit5 = 0x1F;
  if(((instr >> 6) & 0x7FFF) != 0)
    this->exception(-12);
  s1 = ((instr >> 21) & bit5);
  int n1;
  n1 = R[s1];
  HI = n1;
}

void MIPS::MTLO(unsigned instr)
{
  int s1;
  const int bit5 = 0x1F;
  if(((instr >> 6) & 0x7FFF) != 0)
    this->exception(-12);
  s1 = ((instr >> 21) & bit5);
  int n1;
  n1 = R[s1];
  LO = n1;
}

void MIPS::MULT(unsigned instr)
{
  int s1, s2;
  const int bit5 = 0x1F;
  if(((instr >> 6) & 0x3FF) != 0)
    this->exception(-12);
  s2 = ((instr >> 16) & bit5);
  s1 = ((instr >> 21) & bit5);

  long long n1, n2;
  n1 = R[s1];
  n2 = R[s2];

  long long res;
  res = n1 * n2;
  HI = (res >> 32);
  LO = (res & 0xFFFFFFFF);
}

void MIPS::MULTU(unsigned instr)
{
  int s1, s2;
  const int bit5 = 0x1F;
  if(((instr >> 6) & 0x3FF) != 0)
    this->exception(-12);
  s2 = ((instr >> 16) & bit5);
  s1 = ((instr >> 21) & bit5);

  unsigned long long n1, n2;
  n1 = (unsigned)R[s1];
  n2 = (unsigned)R[s2];

  unsigned long long res;
  res = (unsigned long long)n1 * n2;
  HI = (res >> 32);
  LO = (res & 0xFFFFFFFF);
}

void MIPS::OR(unsigned instr)
{
  int s1, s2, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  s2 = ((instr >> 16) & bit5);
  s1 = ((instr >> 21) & bit5);

  int n1, n2;
  n1 = R[s1];
  n2 = R[s2];
  R[dest] = (n1 | n2);
}

void MIPS::SLL(unsigned instr)
{
  int rt, dest, sa;
  const int bit5 = 0x1F;
  if(((instr >> 21) & bit5) != 0)
    this->exception(-12);
  sa = ((instr >> 6) & bit5);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);

  int n1;
  n1 = R[rt];
  R[dest] = (n1 << sa);
}

void MIPS::SLLV(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  int n1, n2;
  n1 = R[rt];
  n2 = (R[rs] & 0x1F);// we need only 5 lsb
  R[dest] = (n1 << n2);
}

void MIPS::SLT(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  int n1, n2;
  n1 = R[rt];
  n2 = R[rs];
  R[dest] = (n2 < n1);
}

void MIPS::SLTU(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  unsigned int n1, n2;
  n1 = R[rt];
  n2 = R[rs];
  R[dest] = (n2 < n1);
}

void MIPS::SRA(unsigned instr)
{
  int rt, dest, sa;
  const int bit5 = 0x1F;
  if(((instr >> 21) & bit5) != 0)
    this->exception(-12);
  sa = ((instr >> 6) & bit5);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);

  int n1;
  n1 = R[rt];
  int sign = n1 >> 31;
  for(int i = 1; i <= sa; ++i)
    n1 = ((n1 >> 1) | (sign << 31));
  R[dest] = n1;
}

void MIPS::SRAV(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  int n1, n2;
  n1 = R[rt];
  n2  = (R[rs] & 0x1F);// we need only ls 5 bits
  int sign = n1 >> 31;
  for(int i = 1; i <= n2; ++i)
    n1 = ((n1 >> 1) | (sign << 31));
  R[dest] = n1;
}

void MIPS::SRL(unsigned instr)
{
  int rt, dest, sa;
  const int bit5 = 0x1F;
  if(((instr >> 21) & bit5) != 0)
    this->exception(-12);
  sa = ((instr >> 6) & bit5);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);

  unsigned int n1;
  n1 = R[rt];
  R[dest] = (unsigned)(n1 >> sa);
}

void MIPS::SRLV(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  unsigned int n1, n2;
  n1 = R[rt];
  n2  = (R[rs] & 0x1F);// we need only ls 5 bits
  R[dest] = (unsigned)(n1 >> n2);
}

void MIPS::SUB(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  int n1, n2, res;
  n1 = R[rt];
  n2  = R[rs];
  res = n2 - n1;
  if((n1 < 0 and n2 >= 0 and res <= 0) or (n1 > 0 and n2 < 0 and res >= 0))
    this->exception(-10);
  R[dest] = res;
}

void MIPS::SUBU(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  unsigned int n1, n2, res;
  n1 = R[rt];
  n2  = R[rs];
  res = n2 - n1;
  R[dest] = res;
}

void MIPS::XOR(unsigned instr)
{
  int rs, rt, dest;
  const int bit5 = 0x1F;
  if(((instr >> 6) & bit5) != 0)
    this->exception(-12);
  dest = ((instr >> 11) & bit5);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  int n1, n2;
  n1 = R[rt];
  n2 = R[rs];
  R[dest] = (n1 ^ n2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MIPS::I_type(unsigned instr)
{
  int opcode = (instr >> 26);
  if(opcode == 0x08)
    this->ADDI(instr);
  else if(opcode == 0x09)
    this->ADDIU(instr);
  else if(opcode == 0x0C)
    this->ANDI(instr);
  else if(opcode == 0x04)
    this->BEQ(instr);
  else if(opcode == 0x01)// BGEZ, BGEZAL, BLTZ, BLTZAL
    this->BGEZ(instr);
  else if(opcode == 0x07)
    this->BGTZ(instr);
  else if(opcode == 0x06)
    this->BLEZ(instr);
  else if(opcode == 0x05)
    this->BNE(instr);
  else if(opcode == 0x20)
    this->LB(instr);
  else if(opcode == 0x24)
    this->LBU(instr);
  else if(opcode == 0x21)
    this->LH(instr);
  else if(opcode == 0x25)
    this->LHU(instr);
  else if(opcode == 0x0F)
    this->LUI(instr);
  else if(opcode == 0x23)
    this->LW(instr);
  else if(opcode == 0x22)
    this->LWL(instr);
  else if(opcode == 0x26)
    this->LWR(instr);
  else if(opcode == 0x0D)
    this->ORI(instr);
  else if(opcode == 0x28)
    this->SB(instr);
  else if(opcode == 0x29)
    this->SH(instr);
  else if(opcode == 0x0A)
    this->SLTI(instr);
  else if(opcode == 0x0B)
    this->SLTIU(instr);
  else if(opcode == 0x2B)
    this->SW(instr);
  else if(opcode == 0x0E)
    this->XORI(instr);
  else
    this->exception(-12);
}

void MIPS::ADDI(unsigned instr)
{
  int rs, imm, rt;
  const int bit5 = 0x1F;
  imm = (instr & 0xFFFF);
  int sign = ((imm >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    imm = (imm | (sign << i));// sign extension for the immediate

  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);
  int n1, res;
  n1 = R[rs];
  res = n1 + imm;
  if((n1 > 0 and imm > 0 and res <= 0) or (n1 < 0 and imm < 0 and res >= 0))
    this->exception(-10);
  R[rt] = res;
}

void MIPS::ADDIU(unsigned instr)
{
  int rs, imm, rt;
  const int bit5 = 0x1F;
  imm = (instr & 0xFFFF);
  int sign = ((imm >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    imm = (imm | (sign << i));// sign extension for the immediate

  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);
  int n1, res;
  n1 = R[rs];
  res = n1 + imm;
  R[rt] = res;
}

void MIPS::ANDI(unsigned instr)
{
  int rs, imm, rt;
  const int bit5 = 0x1F;
  imm = (instr & 0xFFFF);

  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);
  int n1, res;
  n1 = R[rs];
  res = (n1 & imm);
  R[rt] = res;
}

void MIPS::BEQ(unsigned instr)
{
  int rt, rs, imm;
  const int bit5 = 0x1F;
  imm = (instr & 0xFFFF);
  int sign = ((imm >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    imm = (imm | (sign << i));// sign extension for the offset

  imm = (imm << 2);// the offset should be shifted left by 2 bits
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);
  int n1, n2;
  n1 = R[rt];
  n2 = R[rs];
  if(BDS == true)
    return;
  if(n1 == n2)// we should take the branch
  {
    int newPC = PC + imm;
    if(newPC < 0 or newPC >= 0x1000000)// branch tries to go outside the memory range that can be executed
      this->exception(-11);
    BDS = true;
    this->execute_instr(this->load_instr());
    PC = newPC;
    BDS = false;
  }
}

void MIPS::BGEZ(unsigned instr)
{
  int s1, s2, imm;
  const int bit5 = 0x1F;
  imm = (instr & 0xFFFF);
  int sign = ((imm >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    imm = (imm | (sign << i));// sign extension for the offset

  imm = (imm << 2);// the offset should be shifted left by 2 bits
  s2 = ((instr >> 16) & bit5);
  s1 = ((instr >> 21) & bit5);
  int n1;
  n1 = R[s1];

  if(s2 != 0 and s2 != 0b10000 and s2 != 0b00001 and s2 != 0b10001)
    this->exception(-12);
  if(BDS == true)
    return;
  if(s2 == 0 or s2 == 0b10000)//we have BLTZ
  {
    if(n1 < 0)
    {
      int newPC = PC + imm;
      if(newPC < 0 or newPC >= 0x1000000)// branch tries to go outside the memory range that can be executed
        this->exception(-11);
      BDS = true;
      this->execute_instr(this->load_instr());
      BDS = false;
      if(s2 == 0b10000)// we have BLTZAL instruction (NOT SURE IF R[31] =... IS DONE EVEN IF BRANCH IS NOT TAKEN)
        R[31] = newPC - imm + 4 + 0x10000000;// the return address is the address of the second instr following the branch
      PC = newPC;
    }
    return;
  }

  else if(n1 >= 0 and (s2 == 0b00001 or s2 == 0b10001))
  {
    int newPC = PC + imm;
    if(newPC < 0 or newPC >= 0x1000000)// branch tries to go outside the memory range that can be executed
      this->exception(-11);
    BDS = true;
    this->execute_instr(this->load_instr());
    BDS = false;
    if(s2 == 0b10001)// we have BGEZAL instruction (NOT SURE IF R[31] =... IS DONE EVEN IF BRANCH IS NOT TAKEN)
      R[31] = newPC - imm + 4 + 0x10000000;// the return address is the address of the second instr following the branch
    PC = newPC;
  }
}

void MIPS::BGTZ(unsigned instr)
{
  int rs, imm;
  const int bit5 = 0x1F;
  if(((instr >> 16) & bit5) != 0)
    this->exception(-12);

  imm = (instr & 0xFFFF);
  int sign = ((imm >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    imm = (imm | (sign << i));// sign extension for the offset

  imm = (imm << 2);// the offset should be shifted left by 2 bits
  rs = ((instr >> 21) & bit5);
  int n1;
  n1 = R[rs];
  if(BDS == true)
    return;
  if(n1 > 0)
  {
    int newPC = PC + imm;
    if(newPC < 0 or newPC >= 0x1000000)// branch tries to go outside the memory range that can be executed
      this->exception(-11);
    BDS = true;
    this->execute_instr(this->load_instr());
    BDS = false;
    PC = newPC;
  }
}

void MIPS::BLEZ(unsigned instr)
{
  int rs, imm;
  const int bit5 = 0x1F;
  if(((instr >> 16) & bit5) != 0)
    this->exception(-12);

  imm = (instr & 0xFFFF);
  int sign = ((imm >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    imm = (imm | (sign << i));// sign extension for the offset

  imm = (imm << 2);// the offset should be shifted left by 2 bits
  rs = ((instr >> 21) & bit5);
  int n1;
  n1 = R[rs];
  if(BDS == true)
    return;
  if(n1 <= 0)
  {
    int newPC = PC + imm;
    if(newPC < 0 or newPC >= 0x1000000)// branch tries to go outside the memory range that can be executed
      this->exception(-11);
    BDS = true;
    this->execute_instr(this->load_instr());
    BDS = false;
    PC = newPC;
  }
}

void MIPS::BNE(unsigned instr)
{
  int s1, s2, imm;
  const int bit5 = 0x1F;
  imm = (instr & 0xFFFF);
  int sign = ((imm >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    imm = (imm | (sign << i));// sign extension for the offset

  imm = (imm << 2);// the offset should be shifted left by 2 bits
  s1 = ((instr >> 16) & bit5);
  s2 = ((instr >> 21) & bit5);
  int n1, n2;
  n1 = R[s1];
  n2 = R[s2];
  if(BDS == true)
    return;
  if(n1 != n2)// we should take the branch
  {
    int newPC = PC + imm;
    if(newPC < 0 or newPC >= 0x1000000)// branch tries to go outside the memory range that can be executed
      this->exception(-11);
    BDS = true;
    this->execute_instr(this->load_instr());
    BDS = false;
    PC = newPC;
  }
}

void MIPS::LB(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);
  int n1;
  n1 = R[base];
  int mem_location = n1 + offset;
  if(mem_location >= 0x20000000 and mem_location < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    R[rt] = ADDR_DATA[mem_location];
    sign = ((R[rt] >> 7) & 1);
    for(int i = 8; i < 32; ++i)
      R[rt] = (R[rt] | (sign << i));
  }
  else if(mem_location >= 0x0 and mem_location < 0x4)// ADDR_NULL
  {
    exception(-11);
  }
  else if(mem_location >= 0x10000000 and mem_location < 0x11000000)// ADDR_INSTR
  {
    mem_location -= 0x10000000;
    R[rt] = ADDR_INSTR[mem_location];
    sign = ((R[rt] >> 7) & 1);
    for(int i = 8; i < 32; ++i)
      R[rt] = (R[rt] | (sign << i));
  }
  else if(mem_location >= 0x30000000 and mem_location < 0x30000004)// ADDR_GETC
  {
    mem_location -= 0x30000000;
    int character = getchar();
    R[rt] = ((character >> (8 * (3 - mem_location))) & 0xFF);
    sign = ((R[rt] >> 7) & 1);
    for(int i = 8; i < 32; ++i)
      R[rt] = (R[rt] | (sign << i));
  }
  else
    this->exception(-11);
}

void MIPS::LBU(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);
  int n1;
  n1 = R[base];
  int mem_location = n1 + offset;
  if(mem_location >= 0x20000000 and mem_location < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    R[rt] = ADDR_DATA[mem_location];
  }
  else if(mem_location >= 0x0 and mem_location < 0x4)// ADDR_NULL
  {
    exception(-11);
  }
  else if(mem_location >= 0x10000000 and mem_location < 0x11000000)// ADDR_INSTR
  {
    mem_location -= 0x10000000;
    R[rt] = ADDR_INSTR[mem_location];
  }
  else if(mem_location >= 0x30000000 and mem_location < 0x30000004)// ADDR_GETC
  {
    mem_location -= 0x30000000;
    int character = getchar();
    R[rt] = ((character >> (8 * (3 - mem_location))) & 0xFF);
  }
  else
    this->exception(-11);
}

void MIPS::LH(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);
  int n1;
  n1 = R[base];
  int mem_location = n1 + offset;
  if(mem_location % 2 != 0)
    this->exception(-11);
  if(mem_location >= 0x20000000 and mem_location + 1 < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    R[rt] = ADDR_DATA[mem_location];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_DATA[mem_location + 1];
    sign = ((R[rt] >> 15) & 1);
    for(int i = 16; i < 32; ++i)
      R[rt] = (R[rt] | (sign << i));
  }
  else if(mem_location >= 0x0 and mem_location + 1 < 0x4)// ADDR_NULL
  {
    exception(-11);
  }
  else if(mem_location >= 0x10000000 and mem_location + 1 < 0x11000000)// ADDR_INSTR
  {
    mem_location -= 0x10000000;
    R[rt] = ADDR_INSTR[mem_location];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_INSTR[mem_location + 1];
    sign = ((R[rt] >> 15) & 1);
    for(int i = 16; i < 32; ++i)
      R[rt] = (R[rt] | (sign << i));
  }
  else if(mem_location >= 0x30000000 and mem_location + 1 < 0x30000004)// ADDR_GETC
  {
    mem_location -= 0x30000000;
    int character = getchar();
    R[rt] = ((character >> (8 * (3 - mem_location))) & 0xFF);
    R[rt] = (R[rt] << 8);
    R[rt] += ((character >> (8 * (2 - mem_location))) & 0xFF);
    sign = ((R[rt] >> 15) & 1);
    for(int i = 16; i < 32; ++i)
      R[rt] = (R[rt] | (sign << i));
  }
  else
    this->exception(-11);
}

void MIPS::LHU(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);
  int n1;
  n1 = R[base];
  int mem_location = n1 + offset;
  if(mem_location % 2 != 0)
    this->exception(-11);
  if(mem_location >= 0x20000000 and mem_location + 1 < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    R[rt] = ADDR_DATA[mem_location];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_DATA[mem_location + 1];
  }
  else if(mem_location >= 0x0 and mem_location + 1 < 0x4)// ADDR_NULL
  {
    exception(-11);
  }
  else if(mem_location >= 0x10000000 and mem_location + 1 < 0x11000000)// ADDR_INSTR
  {
    mem_location -= 0x10000000;
    R[rt] = ADDR_INSTR[mem_location];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_INSTR[mem_location + 1];
  }
  else if(mem_location >= 0x30000000 and mem_location + 1 < 0x30000004)// ADDR_GETC
  {
    mem_location -= 0x30000000;
    int character = getchar();
    R[rt] = ((character >> (8 * (3 - mem_location))) & 0xFF);
    R[rt] = (R[rt] << 8);
    R[rt] += ((character >> (8 * (2 - mem_location))) & 0xFF);
  }
  else
    this->exception(-11);
}

void MIPS::LUI(unsigned instr)
{
  int rt, imm;
  const int bit5 = 0x1F;
  if(((instr >> 21) & bit5))
    this->exception(-12);
  imm = (instr & 0xFFFF);

  rt = ((instr >> 16) & bit5);
  R[rt] = (imm << 16);
}

void MIPS::LW(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);
  int n1;
  n1 = R[base];
  int mem_location = n1 + offset;
  if(mem_location % 4 != 0)
    this->exception(-11);
  if(mem_location >= 0x20000000 and mem_location + 3 < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    R[rt] = ADDR_DATA[mem_location];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_DATA[mem_location + 1];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_DATA[mem_location + 2];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_DATA[mem_location + 3];
  }
  else if(mem_location >= 0x0 and mem_location + 3 < 0x4)// ADDR_NULL
  {
    exception(-11);
  }
  else if(mem_location >= 0x10000000 and mem_location + 3 < 0x11000000)// ADDR_INSTR
  {
    mem_location -= 0x10000000;
    R[rt] = ADDR_INSTR[mem_location];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_INSTR[mem_location + 1];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_INSTR[mem_location + 2];
    R[rt] = (R[rt] << 8);
    R[rt] += ADDR_INSTR[mem_location + 3];
  }
  else if(mem_location >= 0x30000000 and mem_location + 3 < 0x30000004)// ADDR_GETC
  {
    mem_location -= 0x30000000;
    R[rt] = getchar();
  }
  else
    this->exception(-11);
}

void MIPS::LWL(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);
  int n1;
  n1 = R[base];
  int mem_location = n1 + offset;

  if(mem_location >= 0x20000000 and mem_location + 3 < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    int tmp = (ADDR_DATA[mem_location] << 24);
    int counter = 0;
    for(int i = 1; (mem_location + i) % 4 != 0; ++i)// we go until we reach the next alligned word
    {
      tmp += (ADDR_DATA[mem_location + i] << ((3 - i) * 8));
      counter = i;
    }
    R[rt] = (R[rt] << ((counter + 1) * 8));
    R[rt] = (R[rt] >> ((counter + 1) * 8));// we cut off most significant bits that will be loaded from the memory
    R[rt] += tmp;// now we load those bits
    //cout << hex << R[rt];
  }
  else if(mem_location >= 0x0 and mem_location + 3 < 0x4)// ADDR_NULL
  {
    exception(-11);
  }
  else if(mem_location >= 0x10000000 and mem_location + 3 < 0x11000000)// ADDR_INSTR
  {
    mem_location -= 0x10000000;
    int tmp = (ADDR_INSTR[mem_location] << 24);
    int counter = 0;
    for(int i = 1; (mem_location + i) % 4 != 0; ++i)// we go until we reach the next alligned word
    {
      tmp += (ADDR_INSTR[mem_location + i] << ((3 - i) * 8));
      counter = i;
    }
    R[rt] = (R[rt] << ((counter + 1) * 8));
    R[rt] = (R[rt] >> ((counter + 1) * 8));// we cut off most significant bits that will be loaded from the memory
    R[rt] += tmp;// now we load those bits
  }
  else if(mem_location >= 0x30000000 and mem_location + 3 < 0x30000004)// ADDR_GETC
  {
    int character = getchar();
    R[rt] = character;
  }
  else
    this->exception(-11);
}

void MIPS::LWR(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);
  int n1;
  n1 = R[base];
  int mem_location = n1 + offset;
  if(mem_location >= 0x20000000 and mem_location + 3 < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    int tmp = ADDR_DATA[mem_location + 3];
    int counter = 0;
    for(int i = 1; (mem_location + 3 - i) % 4 != 3; ++i)// we go until we reach the next alligned word
    {
      tmp += (ADDR_DATA[mem_location + 3 - i] << (i * 8));
      counter = i;
    }
    R[rt] = (R[rt] >> ((counter + 1) * 8));
    R[rt] = (R[rt] << ((counter + 1) * 8));// we cut off least significant bits that will be loaded from the memory
    R[rt] += tmp;// now we load those bits
    //cout << hex << R[rt] << "\n";
  }
  else if(mem_location >= 0x0 and mem_location + 3 < 0x4)// ADDR_NULL
  {
    exception(-11);
  }
  else if(mem_location >= 0x10000000 and mem_location + 3 < 0x11000000)// ADDR_INSTR
  {
    mem_location -= 0x10000000;
    int tmp = (ADDR_INSTR[mem_location] << 24);
    int counter = 0;
    for(int i = 1; (mem_location + 3 - i) % 4 != 3; ++i)// we go until we reach the next alligned word
    {
      tmp += (ADDR_INSTR[mem_location + i] << ((3 - i) * 8));
      counter = i;
    }
    R[rt] = (R[rt] << ((counter + 1) * 8));
    R[rt] = (R[rt] >> ((counter + 1) * 8));// we cut off most significant bits that will be loaded from the memory
    R[rt] += tmp;// now we load those bits
  }
  else if(mem_location >= 0x30000000 and mem_location + 3 < 0x30000004)// ADDR_GETC
  {
    int character = getchar();
    R[rt] = character;
  }
  else
    this->exception(-11);
}

void MIPS::ORI(unsigned instr)
{
  int s1, dest, imm;
  const int bit5 = 0x1F;

  imm = (instr & 0xFFFF);
  dest = ((instr >> 16) & bit5);
  s1 = ((instr >> 21) & bit5);

  int n1;
  n1 = R[s1];
  R[dest] = (n1 | imm);
}

void MIPS::SB(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);

  int  n1;
  n1 = R[base];

  int mem_location = offset + n1;
  if(mem_location >= 0x20000000 and mem_location < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    unsigned char byte;
    int tmp = (R[rt] & 0xFF);
    byte = tmp;
    ADDR_DATA[mem_location] = byte;
  }
  else if(mem_location >= 0x30000004 and mem_location <= 0x30000008)// ADDR_PUTC
  {
    if(mem_location == 0x30000004)
      putchar((R[rt] & 0xFF));
    else
      putchar(0);
  }
  else
    this->exception(-11);
}

void MIPS::SH(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);

  int  n1;
  n1 = R[base];

  int mem_location = offset + n1;
  if(mem_location % 2 != 0)
    this->exception(-11);
  if(mem_location >= 0x20000000 and mem_location + 1 < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    unsigned char byte;
    int tmp = ((R[rt] >> 8)  & 0xFF);
    byte = tmp;
    ADDR_DATA[mem_location] = byte;
    tmp = (R[rt] & 0xFF);
    byte = tmp;
    ADDR_DATA[mem_location + 1] = byte;
  }
  else if(mem_location >= 0x30000004 and mem_location + 1 <= 0x30000008)// ADDR_PUTC
  {
    if(mem_location == 0x30000004)
      putchar((R[rt] & 0xFF));
    else
      putchar(0);
  }
  else
    this->exception(-11);
}

void MIPS::SLTI(unsigned instr)
{
  int imm, rt, rs;
  const int bit5 = 0x1F;

  imm = (instr & 0xFFFF);
  int sign = ((imm >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    imm = (imm | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  int n1;
  n1 = R[rs];
  R[rt] = (n1 < imm);
}

void MIPS::SLTIU(unsigned instr)
{
  unsigned int imm;
  int rt, rs;
  const int bit5 = 0x1F;

  imm = (instr & 0xFFFF);
  int sign = ((imm >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    imm = (imm | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  unsigned int n1;
  n1 = R[rs];
  R[rt] = (n1 < imm);
}

void MIPS::SW(unsigned instr)
{
  int offset, rt, base;
  const int bit5 = 0x1F;

  offset = (instr & 0xFFFF);
  int sign = ((offset >> 15) & 1);

  for(int i = 16; i < 32; ++i)
    offset = (offset | (sign << i));// sign extension for the offset

  rt = ((instr >> 16) & bit5);
  base = ((instr >> 21) & bit5);

  int  n1;
  n1 = R[base];

  int mem_location = offset + n1;
  if(mem_location % 4 != 0)
    this->exception(-11);
  if(mem_location >= 0x20000000 and mem_location + 3 < 0x24000000)// we are in the read-write area
  {
    mem_location -= 0x20000000;
    unsigned char byte;
    int tmp = ((R[rt] >> 24)  & 0xFF);
    byte = tmp;
    ADDR_DATA[mem_location] = byte;
    tmp = ((R[rt] >> 16) & 0xFF);
    byte = tmp;
    ADDR_DATA[mem_location + 1] = byte;
    tmp = ((R[rt] >> 8) & 0xFF);
    byte = tmp;
    ADDR_DATA[mem_location + 2] = byte;
    tmp = (R[rt] & 0xFF);
    byte = tmp;
    ADDR_DATA[mem_location + 3] = byte;
  }
  else if(mem_location == 0x30000004)
    putchar(R[rt]);
  else
    this->exception(-11);
}

void MIPS::XORI(unsigned instr)
{
  int imm, rt, rs;
  const int bit5 = 0x1F;

  imm = (instr & 0xFFFF);
  rt = ((instr >> 16) & bit5);
  rs = ((instr >> 21) & bit5);

  int n1;
  n1 = R[rs];
  R[rt] = (n1 ^ imm);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MIPS::J_type(unsigned instr)
{
  int opcode = (instr >> 26);
  if(opcode == 0x02)
    this->J(instr);
  else if(opcode == 0x03)
    this->JAL(instr);
  else
    this->exception(-12);
}

void MIPS::J(unsigned instr)
{
  if(BDS == true)
    return;
  int index = instr & 0x3FFFFFF;
  index = (index << 2);
  int tmpPC = PC + 0x10000000;
  BDS = true;
  this->execute_instr(this->load_instr());
  BDS = false;
  index += (tmpPC & 0xF0000000);
  if(index == 0)
    this->terminate();
  if(index < 0x10000000 or index >= 0x11000000)// we want to jump outside the memory range and not terminate the simulation
    this->exception(-11);
  PC = index - 0x10000000;
}

void MIPS::JAL(unsigned instr)
{
  if(BDS == true)
    return;
  int index = instr & 0x3FFFFFF;
  index = (index << 2);
  int tmpPC = PC + 0x10000000;
  BDS = true;
  this->execute_instr(this->load_instr());
  BDS = false;
  index += (tmpPC & 0xF0000000);
  if(index == 0)
    this->terminate();
  if(index < 0x10000000 or index >= 0x11000000)// we want to jump outside the memory range and not terminate the simulation
    this->exception(-11);
  R[31] = tmpPC + 4;// place the return link (second instruction following the branch)
  PC = index - 0x10000000;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MIPS::terminate()
{
  this->free_mem();
  exit((R[2] & 0xFF));
}

void MIPS::exception(int code)
{
  this->free_mem();
  exit(code);
}

void MIPS::free_mem()
{
  delete [] ADDR_INSTR;
  delete [] ADDR_DATA;
}

//DEBUG SECTION//////////////////////////////////////////////////////////////////

void MIPS::REG(int number)
{
  cout << R[number] << "\n";
}
