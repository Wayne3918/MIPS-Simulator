#include <string>

class MIPS
{
  private:
    unsigned char ADDR_NULL[4];//0x00000000
    unsigned char *ADDR_INSTR = new unsigned char [0x1000000];//0x10000000
    unsigned char *ADDR_DATA = new unsigned char [0x4000000];//0x20000000
    unsigned char ADDR_GETC[4];//0x30000000
    unsigned char ADDR_PUTC[4];//0x30000004
    int R[32];
    int PC;
    int maxPC;
    int LO, HI;
    bool BDS;// true if we are in the branch delay slot
  public:
    MIPS();
    int load_instr();
    void read_binary(std::string filename);
    void free_mem();
    void terminate();
    void exception(int code);
    void execute_instr(unsigned instruction);
    void R_type(unsigned instr);
    void I_type(unsigned instr);
    void J_type(unsigned instr);
    void ADD(unsigned instr);
    void ADDI(unsigned instr);
    void ADDIU(unsigned instr);
    void ADDU(unsigned instr);
    void AND(unsigned instr);
    void ANDI(unsigned instr);
    void BEQ(unsigned instr);
    void BGEZ(unsigned instr);
    void BGTZ(unsigned instr);
    void BLEZ(unsigned instr);
    void BNE(unsigned instr);
    void DIV(unsigned instr);
    void DIVU(unsigned instr);
    void J(unsigned instr);
    void JAL(unsigned instr);
    void JALR(unsigned instr);
    void JR(unsigned instr);
    void LB(unsigned instr);
    void LBU(unsigned instr);
    void LH(unsigned instr);
    void LHU(unsigned instr);
    void LUI(unsigned instr);
    void LW(unsigned instr);
    void LWL(unsigned instr);
    void LWR(unsigned instr);
    void MFHI(unsigned instr);
    void MFLO(unsigned instr);
    void MTHI(unsigned instr);
    void MTLO(unsigned instr);
    void MULT(unsigned instr);
    void MULTU(unsigned instr);
    void OR(unsigned instr);
    void ORI(unsigned instr);
    void SB(unsigned instr);
    void SH(unsigned instr);
    void SLL(unsigned instr);
    void SLLV(unsigned instr);
    void SLT(unsigned instr);
    void SLTI(unsigned instr);
    void SLTIU(unsigned instr);
    void SLTU(unsigned instr);
    void SRA(unsigned instr);
    void SRAV(unsigned instr);
    void SRL(unsigned instr);
    void SRLV(unsigned instr);
    void SUB(unsigned instr);
    void SUBU(unsigned instr);
    void SW(unsigned instr);
    void XOR(unsigned instr);
    void XORI(unsigned instr);
    void REG(int number);
};
