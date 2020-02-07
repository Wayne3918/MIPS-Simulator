#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int bit8 = 0xFF;
const int bit5 = 0x1F;
const int bit16 = 0xFFFF;
const int bit26 = 0x3FFFFFF;

int ADD()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (1 << 5);
  return out;
}

int ADDI()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1000 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int ADDIU()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1001 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int ADDU()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b100001);
  return out;
}

int AND()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b100100);
  return out;
}

int ANDI()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1100 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int BEQ()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b100 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int BGEZ()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> imm;
  rt = 1;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int BGEZAL()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> imm;
  rt = 0b10001;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int BGTZ()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> imm;
  rt = 0;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b111 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int BLEZ()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> imm;
  rt = 0;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b110 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int BLTZ()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> imm;
  rt = 0;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int BLTZAL()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> imm;
  rt = 0b10000;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int BNE()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b101 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int DIV()
{
  int out = 0;
  int rs, rt;
  cin >> rs >> rt;
  rs &= bit5;
  rt &= bit5;
  out = (rs << 21) + (rt << 16) + (0b11010);
  return out;
}

int DIVU()
{
  int out = 0;
  int rs, rt;
  cin >> rs >> rt;
  rs &= bit5;
  rt &= bit5;
  out = (rs << 21) + (rt << 16) + (0b11011);
  return out;
}

int J()
{
  int out = 0;
  int index;
  cin >> index;
  index &= bit26;
  out = (0b10 << 26) + index;
  return out;
}

int JAL()
{
  int out = 0;
  int index;
  cin >> index;
  index &= bit26;
  out = (0b11 << 26) + index;
  return out;
}

int JALR()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rd;
  rt = 0;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rd << 11) + (0b1001);
  return out;
}

int JR()
{
  int out = 0;
  int rs;
  cin >> rs;
  rs &= bit5;
  out = (rs << 21) + (0b1000);
  return out;
}

int LB()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b100000 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int LBU()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b100100 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int LH()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b100001 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int LHU()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b100101 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int LUI()
{
  int out = 0;
  int rt, imm;
  cin >> rt >> imm;
  rt &= bit5;
  imm &= bit16;
  out = (0b1111 << 26) + (rt << 16) + imm;
  return out;
}

int LW()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b100011 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int LWL()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b100010 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int LWR()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b100110 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int MFHI()
{
  int out = 0;
  int rd;
  cin >> rd;
  rd &= bit5;
  out = (rd << 11) + (0b10000);
  return out;
}

int MFLO()
{
  int out = 0;
  int rd;
  cin >> rd;
  rd &= bit5;
  out = (rd << 11) + (0b10010);
  return out;
}

int MTHI()
{
  int out = 0;
  int rs;
  cin >> rs;
  rs &= bit5;
  out = (rs << 21) + (0b10001);
  return out;
}

int MTLO()
{
  int out = 0;
  int rs;
  cin >> rs;
  rs &= bit5;
  out = (rs << 21) + (0b10011);
  return out;
}

int MULT()
{
  int out = 0;
  int rs, rt;
  cin >> rs >> rt;
  rs &= bit5;
  rt &= bit5;
  out = (rs << 21) + (rt << 16) + (0b11000);
  return out;
}

int MULTU()
{
  int out = 0;
  int rs, rt;
  cin >> rs >> rt;
  rs &= bit5;
  rt &= bit5;
  out = (rs << 21) + (rt << 16) + (0b11001);
  return out;
}

int OR()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b100101);
  return out;
}

int ORI()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1101 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int SB()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b101000 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int SH()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b101001 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int SLL()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 16) + (rt << 11) + (rd << 6);
  return out;
}

int SLLV()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b100);
  return out;
}

int SLT()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b101010);
  return out;
}

int SLTI()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1010 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int SLTIU()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1011 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int SLTU()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b101011);
  return out;
}

int SRA()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 16) + (rt << 11) + (rd << 6) + (0b11);
  return out;
}

int SRAV()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b111);
  return out;
}

int SRL()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 16) + (rt << 11) + (rd << 6) + (0b10);
  return out;
}

int SRLV()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b110);
  return out;
}

int SUB()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b100010);
  return out;
}

int SUBU()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b100011);
  return out;
}

int SW()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b101011 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

int XOR()
{
  int out = 0;
  int rs, rt, rd;
  cin >> rs >> rt >> rd;
  rs &= bit5;
  rt &= bit5;
  rd &= bit5;
  out = (rs << 21) + (rt << 16) + (rd << 11) + (0b100110);
  return out;
}

int XORI()
{
  int out = 0;
  int rs, rt, imm;
  cin >> rs >> rt >> imm;
  rs &= bit5;
  rt &= bit5;
  imm &= bit16;
  out = (0b1110 << 26) + (rs << 21) + (rt << 16) + imm;
  return out;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  string filename;
  cin >> filename;
  fstream myFile (filename + ".exe", ios::out | ios::binary);
  int number;
  while(true)
  {
    string command;
    cin >> command;
    if(command == "end")
      break;
    else if(command == "add")
    {
      int out = ADD();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "addi")
    {
      int out = ADDI();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "addiu")
    {
      int out = ADDIU();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "addu")
    {
      int out = ADDU();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "and")
    {
      int out = AND();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "andi")
    {
      int out = ANDI();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "beq")
    {
      int out = BEQ();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "bgez")
    {
      int out = BGEZ();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "bgezal")
    {
      int out = BGEZAL();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "bgtz")
    {
      int out = BGTZ();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "blez")
    {
      int out = BLEZ();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "bltz")
    {
      int out = BLTZ();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "bltzal")
    {
      int out = BLTZAL();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "bne")
    {
      int out = BNE();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "div")
    {
      int out = DIV();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "divu")
    {
      int out = DIVU();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "j")
    {
      int out = J();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "jalr")
    {
      int out = JALR();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "jal")
    {
      int out = JAL();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "jr")
    {
      int out = JR();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "lb")
    {
      int out = LB();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "lbu")
    {
      int out = LBU();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "lh")
    {
      int out = LH();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "lhu")
    {
      int out = LHU();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "lui")
    {
      int out = LUI();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "lw")
    {
      int out = LW();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "lwl")
    {
      int out = LWL();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "lwr")
    {
      int out = LWR();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "mfhi")
    {
      int out = MFHI();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "mflo")
    {
      int out = MFLO();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "mthi")
    {
      int out = MTHI();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "mtlo")
    {
      int out = MTLO();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "mult")
    {
      int out = MULT();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "multu")
    {
      int out = MULTU();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "or")
    {
      int out = OR();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "ori")
    {
      int out = ORI();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "sb")
    {
      int out = SB();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "sh")
    {
      int out = SH();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "sll")
    {
      int out = SLL();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "sllv")
    {
      int out = SLLV();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "slt")
    {
      int out = SLT();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "slti")
    {
      int out = SLTI();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "sltiu")
    {
      int out = SLTIU();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "sltu")
    {
      int out = SLTU();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "sra")
    {
      int out = SRA();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "srav")
    {
      int out = SRAV();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "srl")
    {
      int out = SRL();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "srlv")
    {
      int out = SRLV();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "sub")
    {
      int out = SUB();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "subu")
    {
      int out = SUBU();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "sw")
    {
      int out = SW();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "xor")
    {
      int out = XOR();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else if(command == "xori")
    {
      int out = XORI();
      for(int i = 3; i >= 0; --i)
        myFile << (char)((out >> (i * 8) & bit8));
    }
    else
      cout << "Try again!\n";
  }
  myFile.close();
}
