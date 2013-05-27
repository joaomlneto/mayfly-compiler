// $Id: DebugOnly.h,v 1.15 2013/02/11 20:56:51 david Exp $ -*- c++ -*-
#ifndef __CDK8_GENERATOR_DEBUGONLY_H__
#define __CDK8_GENERATOR_DEBUGONLY_H__

#include <cdk/generators/Postfix.h>

namespace cdk {

  namespace generator {

    /**
     * Class DebugOnly: generate PF assembly (debug only).
     * @see Postfix
     */
    class DebugOnly: public Postfix {

    public:
      inline DebugOnly(std::ostream &o = std::cout, bool debug = false) :
          Postfix(o, debug) {
      }

    public:
      void NOP() {
        os() << "NOP\n";
      }
      void INT(int value) {
        os() << "INT " << value << "\n";
      }
      void ADD() {
        os() << "ADD\n";
      }
      void SUB() {
        os() << "SUB\n";
      }
      void MUL() {
        os() << "MUL\n";
      }
      void DIV() {
        os() << "DIV\n";
      }
      void MOD() {
        os() << "MOD\n";
      }
      void NEG() {
        os() << "NEG\n";
      }
      void INCR(int value) {
        os() << "INCR " << value << "\n";
      }
      void DECR(int value) {
        os() << "DECR " << value << "\n";
      }
      void GT() {
        os() << "GT\n";
      }
      void GE() {
        os() << "GE\n";
      }
      void LT() {
        os() << "LT\n";
      }
      void LE() {
        os() << "LE\n";
      }
      void EQ() {
        os() << "EQ\n";
      }
      void NE() {
        os() << "NE\n";
      }
      void AND() {
        os() << "AND\n";
      }
      void OR() {
        os() << "OR\n";
      }
      void XOR() {
        os() << "XOR\n";
      }
      void NOT() {
        os() << "NOT\n";
      }
      void ROTL() {
        os() << "ROTL\n";
      }
      void ROTR() {
        os() << "ROTR\n";
      }
      void SHTL() {
        os() << "SHTL\n";
      }
      void SHTRU() {
        os() << "SHTRU\n";
      }
      void SHTRS() {
        os() << "SHTRS\n";
      }
      void LOCAL(int offset) {
        os() << "LOCAL " << offset << "\n";
      }
      void ADDR(std::string label) {
        os() << "ADDR\n" << label << "\n";
      }
      void LOCV(int offset) {
        os() << "LOCV " << offset << "\n";
      }
      void ADDRV(std::string label) {
        os() << "ADDRV " << label << "\n";
      }
      void LOCA(int offset) {
        os() << "LOCA " << offset << "\n";
      }
      void ADDRA(std::string label) {
        os() << "ADDRA " << label << "\n";
      }
      void LOAD() {
        os() << "LOAD\n";
      }
      void STORE() {
        os() << "STORE\n";
      }
      void LDCHR() {
        os() << "LDCHR\n";
      }
      void STCHR() {
        os() << "STCHR\n";
      }
      void LD16() {
        os() << "LD16\n";
      }
      void ST16() {
        os() << "ST16\n";
      }
      void ENTER(size_t bytes) {
        os() << "ENTER " << bytes << "\n";
      }
      void START() {
        os() << "START\n";
      }
      void ALLOC() {
        os() << "ALLOC\n";
      }
      void LEAVE() {
        os() << "LEAVE\n";
      }
      void TRASH(int bytes) {
        os() << "TRASH " << bytes << "\n";
      }
      void CALL(std::string label) {
        os() << "CALL" << label << "\n";
      }
      void RET() {
        os() << "RET\n";
      }
      void RETN(int bytes) {
        os() << "RETN " << bytes << "\n";
      }
      void BRANCH() {
        os() << "BRANCH\n";
      }
      void LEAP() {
        os() << "LEAP\n";
      }
      void JMP(std::string label) {
        os() << "JMP " << label << "\n";
      }
      void JZ(std::string label) {
        os() << "JZ " << label << "\n";
      }
      void JNZ(std::string label) {
        os() << "JNZ " << label << "\n";
      }
      void DUP() {
        os() << "DUP\n";
      }
      void DDUP() {
        os() << "DDUP\n";
      }
      void SWAP() {
        os() << "SWAP\n";
      }
      void SP() {
        os() << "SP\n";
      }
      void PUSH() {
        os() << "PUSH\n";
      }
      void POP() {
        os() << "POP\n";
      }
      void I2D() {
        os() << "I2D\n";
      }
      void F2D() {
        os() << "F2D\n";
      }
      void D2I() {
        os() << "D2I\n";
      }
      void D2F() {
        os() << "D2F\n";
      }
      void DADD() {
        os() << "DADD\n";
      }
      void DSUB() {
        os() << "DSUB\n";
      }
      void DMUL() {
        os() << "DMUL\n";
      }
      void DDIV() {
        os() << "DDIV\n";
      }
      void DCMP() {
        os() << "DCMP\n";
      }
      void DNEG() {
        os() << "DNEG\n";
      }
      void DLOAD() {
        os() << "DLOAD\n";
      }
      void DSTORE() {
        os() << "DSTORE\n";
      }
      void DPUSH() {
        os() << "DPUSH\n";
      }
      void DPOP() {
        os() << "DPOP\n";
      }
      void NIL() {
        os() << "NIL\n";
      }
      void TEXT() {
        os() << "TEXT\n";
      }
      void RODATA() {
        os() << "RODATA\n";
      }
      void DATA() {
        os() << "DATA\n";
      }
      void BSS() {
        os() << "BSS\n";
      }
      void ALIGN() {
        os() << "ALIGN\n";
      }
      void EXTERN(std::string label) {
        os() << "EXTERN " << label << "\n";
      }
      void COMMON(int value) {
        os() << "COMMON " << value << "\n";
      }
      void GLOBAL(const char *label, std::string type) {
        GLOBAL(std::string(label), type);
      }
      void GLOBAL(std::string label, std::string type) {
        os() << "GLOBAL " << label << " " << type << "\n";
      }
      void LABEL(std::string label) {
        os() << "LABEL " << label << "\n";
      }
      void CONST(int value) {
        os() << "CONST " << value << "\n";
      }
      void STR(std::string value) {
        os() << "STR " << value << "\n";
      }
      void CHAR(char value) {
        os() << "CHAR " << value << "\n";
      }
      void ID(std::string label) {
        os() << "ID " << label << "\n";
      }
      void BYTE(int value) {
        os() << "BYTE " << value << "\n";
      }
      void FLOAT(float value) {
        os() << "FLOAT " << value << "\n";
      }
      void DOUBLE(double value) {
        os() << "DOUBLE " << value << "\n";
      }
      void ULDCHR() {
        os() << "ULDCHR\n";
      }
      void ULD16() {
        os() << "ULD16\n";
      }
      void UDIV() {
        os() << "UDIV\n";
      }
      void UMOD() {
        os() << "UMOD\n";
      }
      void UGT() {
        os() << "UGT\n";
      }
      void UGE() {
        os() << "UGE\n";
      }
      void ULT() {
        os() << "ULT\n";
      }
      void ULE() {
        os() << "ULE\n";
      }
      void JEQ(std::string label) {
        os() << "JEQ " << label << "\n";
      }
      void JNE(std::string label) {
        os() << "JNE " << label << "\n";
      }
      void JGT(std::string label) {
        os() << "JGT " << label << "\n";
      }
      void JGE(std::string label) {
        os() << "JGE " << label << "\n";
      }
      void JLT(std::string label) {
        os() << "JLT " << label << "\n";
      }
      void JLE(std::string label) {
        os() << "JLE " << label << "\n";
      }
      void JUGT(std::string label) {
        os() << "JUGT " << label << "\n";
      }
      void JUGE(std::string label) {
        os() << "JUGE " << label << "\n";
      }
      void JULT(std::string label) {
        os() << "JULT " << label << "\n";
      }
      void JULE(std::string label) {
        os() << "JULE " << label << "\n";
      }

    };

  } // namespace generator
} // namespace cdk

#endif

// $Log: DebugOnly.h,v $
// Revision 1.15  2013/02/11 20:56:51  david
// *** empty log message ***
//
// Revision 1.14  2013/02/10 19:18:24  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.13  2013/02/09 19:00:35  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.12  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.11  2012/03/06 15:07:46  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
// Revision 1.10  2012/02/18 19:38:59  david
// This is the first commit in CDK7. Evaluators and code generators are now aware
// of the debug command line options.
//
