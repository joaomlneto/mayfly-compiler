// $Id: ix86.h,v 1.24 2013/02/10 19:18:24 david Exp $ -*- c++ -*-
#ifndef __CDK8_GENERATOR_IX86_H__
#define __CDK8_GENERATOR_IX86_H__

#include <cdk/generators/Postfix.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cctype>

namespace cdk {

  namespace generator {

    /**
     * Class ix86: generator for nasm targets
     * @see Postfix
     */
    class ix86: public Postfix {

      inline void debug(std::string s) {
        if (_debug) {
          os() << "; " << s << std::endl;
        }
      }

      template <typename Type>
      inline void debug(std::string s, Type value) {
        if (_debug) {
          os() << "; " << s << " " << value << std::endl;
        }
      }

      //----------------------------------------------------------------------

    public:
      inline ix86(std::ostream &o = std::cout, bool debug = false) :
          Postfix(o, debug) {
        // Ensure that double literals are generated
        // in accordance with NASM rules.
        os() << std::setiosflags(std::ios::showpoint);
      }

      //----------------------------------------------------------------------

    private:
      template<typename T> void __cmd1(std::string mnemonic, T arg) {
        os() << "\t" << mnemonic << "\t" << arg << std::endl;
      }
      template<typename T1, typename T2> void __cmd2(std::string mnemonic, T1 arg1, T2 arg2) {
        os() << "\t" << mnemonic << "\t" << arg1 << ", " << arg2 << std::endl;
      }
      template<typename T> std::string _byte(T what) {
        std::ostringstream oss;
        oss << "byte " << what;
        return oss.str();
      }
      template<typename T> std::string _word(T what) {
        std::ostringstream oss;
        oss << "word " << what;
        return oss.str();
      }
      template<typename T> std::string _dword(T what) {
        std::ostringstream oss;
        oss << "dword " << what;
        return oss.str();
      }
      template<typename T> std::string _qword(T what) {
        std::ostringstream oss;
        oss << "qword " << what;
        return oss.str();
      }
      template<typename T> std::string _lbladdr(T what) {
        std::ostringstream oss;
        oss << "$" << what;
        return oss.str();
      }
      template<typename T> std::string _deref(T what) {
        std::ostringstream oss;
        oss << "[" << what << "]";
        return oss.str();
      }
      template<typename T> std::string _offset(T what, int offset) {
        std::ostringstream oss;
        if (offset < 0)
          oss << what << "-" << -offset;
        else if (offset > 0)
          oss << what << "+" << offset;
        else
          oss << what;
        return oss.str();
      }
      template<typename T> std::string _deref(T what, int offset) {
        return _deref(_offset(what, offset));
      }
      void _pop(std::string what) {
        __cmd1("pop", what);
      }
      void _push(std::string what) {
        __cmd1("push", what);
      }
      void _mov(std::string a, std::string b) {
        __cmd2("mov", a, b);
      }

      //!
      //! Arithmetic operations
      //!
      template<typename T> void _add(std::string a, T b) {
        __cmd2("add", a, b);
      }
      template<typename T> void _sub(std::string a, T b) {
        __cmd2("sub", a, b);
      }
      void _neg(std::string a) {
        __cmd1("neg", a);
      }
      void _imul(std::string a, std::string b) {
        __cmd2("imul", a, b);
      }

      /* Comparison */
      void _cmp(std::string a, std::string b) {
        __cmd2("cmp", a, b);
      }

      /* Logical operations */
      void _xor(std::string a, std::string b) {
        __cmd2("xor", a, b);
      }
      void _and(std::string a, std::string b) {
        __cmd2("and", a, b);
      }
      void _or(std::string a, std::string b) {
        __cmd2("or", a, b);
      }
      void _not(std::string a) {
        __cmd1("not", a);
      }

      /* Rotation and shift operations */
      void _rol(std::string a, std::string b) {
        __cmd2("rol", a, b);
      }
      void _ror(std::string a, std::string b) {
        __cmd2("ror", a, b);
      }
      void _sal(std::string a, std::string b) {
        __cmd2("sal", a, b);
      }
      void _sar(std::string a, std::string b) {
        __cmd2("sar", a, b);
      }
      void _shr(std::string a, std::string b) {
        __cmd2("shr", a, b);
      }

      /* Calls, jumps, etc. */
      void _call(std::string what) {
        __cmd1("call", what);
      }
      void _jmp(std::string what) {
        __cmd1("jmp", what);
      }

      /* Segments */
      void _segment(std::string what) {
        os() << "segment\t" << what << "\n";
      }

      /* Floating point */
      void _fild(std::string what) {
        __cmd1("fild", what);
      }
      void _fistp(std::string what) {
        __cmd1("fistp", what);
      }
      void _fld(std::string what) {
        __cmd1("fld", what);
      }
      void _fstp(std::string what) {
        __cmd1("fstp", what);
      }

      //----------------------------------------------------------------------

      // Implementation of the postfix interface

    public:
      void NOP() {
        debug("NOP");
        os() << "\tnop\n";
      }
      void INT(int value) {
        debug("INT", value);
        _push(_dword(value));
      }
      void ADD() {
        debug("ADD");
        _pop("eax");
        _add(_dword(_deref("esp")), "eax");
      }
      void SUB() {
        debug("SUB");
        _pop("eax");
        _sub(_dword(_deref("esp")), "eax");
      }
      void MUL() {
        debug("MUL");
        _pop("eax");
        _imul(_dword("eax"), _deref("esp"));
        _mov(_deref("esp"), "eax");
      }
      void DIV() {
        debug("DIV");
        _pop("ecx");
        _pop("eax");
        os() << "\tcdq\n" << "\tidiv\tecx\n";
        _push("eax");
      }
      void MOD() {
        debug("MOD");
        _pop("ecx");
        _pop("eax");
        os() << "\tcdq\n" << "\tidiv\tecx\n";
        _push("edx");
      }
      void NEG() {
        debug("NEG");
        _neg(_dword(_deref("esp")));
      }
      void INCR(int value) {
        debug("INCR", value);
        DUP();
        _pop("eax");
        _add(_dword(_deref("eax")), value);
      }
      void DECR(int value) {
        debug("DECR", value);
        DUP();
        _pop("eax");
        _sub(_dword(_deref("eax")), value);
      }
      void GT() {
        debug("GT");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        os() << "\tsetg\tcl\n";
        _mov(_deref("esp"), "ecx");
      }
      void GE() {
        debug("GE");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        os() << "\tsetge\tcl\n";
        _mov(_deref("esp"), "ecx");
      }
      void LT() {
        debug("LT");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        os() << "\tsetl\tcl\n";
        _mov(_deref("esp"), "ecx");
      }
      void LE() {
        debug("LE");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        os() << "\tsetle\tcl\n";
        _mov(_deref("esp"), "ecx");
      }
      void EQ() {
        debug("EQ");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        os() << "\tsete\tcl\n";
        _mov(_deref("esp"), "ecx");
      }
      void NE() {
        debug("NE");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        os() << "\tsetne\tcl\n";
        _mov(_deref("esp"), "ecx");
      }
      void AND() {
        debug("AND");
        _pop("eax");
        _and(_dword(_deref("esp")), "eax");
      }
      void OR() {
        debug("OR");
        _pop("eax");
        _or(_dword(_deref("esp")), "eax");
      }
      void XOR() {
        debug("XOR");
        _pop("eax");
        _xor(_dword(_deref("esp")), "eax");
      }
      void NOT() {
        debug("NOT");
        _not(_dword(_deref("esp")));
      }
      void ROTL() {
        debug("ROTL");
        _pop("ecx");
        _rol(_dword(_deref("esp")), "cl");
      }
      void ROTR() {
        debug("ROTR");
        _pop("ecx");
        _ror(_dword(_deref("esp")), "cl");
      }
      void SHTL() {
        debug("SHTL");
        _pop("ecx");
        _sal(_dword(_deref("esp")), "cl");
      }
      void SHTRU() {
        debug("SHTRU");
        _pop("ecx");
        _shr(_dword(_deref("esp")), "cl");
      }
      void SHTRS() {
        debug("SHTRS");
        _pop("ecx");
        _sar(_dword(_deref("esp")), "cl");
      }
      void LOCAL(int offset) {
        debug("LOCAL", offset);
        os() << "\tlea\teax, [ebp+" << offset << "]\n";
        _push("eax");
      }
      void ADDR(std::string label) {
        debug("ADDR", label);
        _push(_dword(_lbladdr(label)));
      }
      void LOCV(int offset) {
        debug("LOCV", offset);
        _push(_dword(_deref("ebp", offset)));
      }
      void ADDRV(std::string label) {
        debug("ADDRV", label);
        _push(_dword(_deref(_lbladdr(label))));
      }
      void LOCA(int offset) {
        debug("LOCA", offset);
        _pop("eax");
        _mov(_deref("ebp", offset), "eax");
      }
      void ADDRA(std::string label) {
        debug("ADDRA", label);
        _pop("eax");
        _mov(_deref(_lbladdr(label)), "eax");
      }
      void LOAD() {
        debug("LOAD");
        _pop("eax");
        _push(_dword(_deref("eax")));
      }
      void STORE() {
        debug("STORE");
        _pop("ecx");
        _pop("eax");
        _mov(_deref("ecx"), "eax");
      }
      void DLOAD() {
        debug("DLOAD");
        _pop("eax");
        _push(_dword(_deref("eax", 4)));
        _push(_dword(_deref("eax")));
      }
      void DSTORE() {
        debug("DSTORE");
        _pop("ecx");
        _pop("eax");
        _mov(_deref("ecx"), "eax");
        _pop("eax");
        _mov(_deref("ecx", 4), "eax");
      }
      void LDCHR() {
        debug("LDCHR");
        _pop("ecx");
        __cmd2("movsx", "eax", _byte(_deref("ecx")));
        _push("eax");
      }
      void STCHR() {
        debug("STCHR");
        _pop("ecx");
        _pop("eax");
        _mov(_deref("ecx"), "al");
      }
      void LD16() {
        debug("LD16");
        _pop("ecx");
        __cmd2("movsx", "eax", _word(_deref("ecx")));
        _push("eax");
      }
      void ST16() {
        debug("ST16");
        _pop("ecx");
        _pop("eax");
        _mov(_deref("ecx"), "ax");
      }
      void ENTER(size_t bytes) {
        debug("ENTER", bytes);
        _push("ebp");
        _mov("ebp", "esp");
        _sub("esp", bytes);
      }
      void START() {
        debug("START");
        _push("ebp");
        _mov("ebp", "esp");
      }
      void ALLOC() {
        debug("ALLOC");
        _pop("eax");
        _sub("esp", "eax");
      }
      void LEAVE() {
        debug("LEAVE");
        os() << "\tleave\n";
      }
      void TRASH(int bytes) {
        debug("TRASH", bytes);
        _add("esp", bytes);
      }
      void CALL(std::string label) {
        debug("CALL", label);
        _call(label);
      }
      void RET() {
        debug("RET");
        os() << "\tret\n";
      }
      void RETN(int bytes) {
        debug("RETN", bytes);
        os() << "\tret\t" << bytes << "\n";
      }
      void BRANCH() {
        debug("BRANCH");
        _pop("eax");
        _call("eax");
      }
      void LEAP() {
        debug("LEAP");
        _pop("eax");
        _jmp("eax");
      }
      void JMP(std::string label) {
        debug("JMP", label);
        _jmp(_dword(label));
      }
      void JZ(std::string label) {
        debug("JZ", label);
        _pop("eax");
        _cmp("eax", _byte(0));
        os() << "\tje\tnear " << label << "\n";
      }
      void JNZ(std::string label) {
        debug("JNZ", label);
        _pop("eax");
        _cmp("eax", _byte(0));
        os() << "\tjne\tnear " << label << "\n";
      }
      void DUP() {
        debug("DUP");
        _push(_dword(_deref("esp")));
      }
      void DDUP() {
        debug("DDUP");
        //DAVID: hack
        SP();
        DLOAD();
      }
      void SWAP() {
        debug("SWAP");
        _pop("eax");
        _pop("ecx");
        _push("eax");
        _mov("eax", "ecx");
        _push("eax");
      }
      void SP() {
        debug("SP");
        _push("esp");
      }
      void PUSH() {
        debug("PUSH");
        _push("eax");
      }
      void POP() {
        debug("POP");
        _pop("eax");
      }
      void DPUSH() {
        debug("DPUSH");
        _sub("esp", _byte(8));
        _fstp(_qword(_deref("esp")));
      }
      void DPOP() {
        debug("DPOP");
        _fld(_qword(_deref("esp")));
        _add("esp", _byte(8));
      }
      void I2D() {
        debug("I2D");
        _fild(_dword(_deref("esp")));
        _sub("esp", _byte(4));
        _fstp(_qword(_deref("esp")));
      }
      void F2D() {
        debug("F2D");
        _fld(_dword(_deref("esp")));
        _sub("esp", _byte(4));
        _fstp(_qword(_deref("esp")));
      }
      void D2I() {
        debug("D2I");
        _fld(_qword(_deref("esp")));
        _add("esp", _byte(4));
        _fistp(_dword(_deref("esp")));
      }
      void D2F() {
        debug("D2F");
        _fld(_qword(_deref("esp")));
        _add("esp", _byte(4));
        _fstp(_dword(_deref("esp")));
      }
      void DADD() {
        debug("DADD");
        _fld(_qword(_deref("esp")));
        _add("esp", _byte(8));
        _fld(_qword(_deref("esp")));
        __cmd1("faddp", "st1");
        _fstp(_qword(_deref("esp")));
      }
      void DSUB() {
        debug("DSUB");
        _fld(_qword(_deref("esp")));
        _add("esp", _byte(8));
        _fld(_qword(_deref("esp")));
        __cmd1("fsubrp", "st1");
        _fstp(_qword(_deref("esp")));
      }
      void DMUL() {
        debug("DMUL");
        _fld(_qword(_deref("esp")));
        _add("esp", _byte(8));
        _fld(_qword(_deref("esp")));
        __cmd1("fmulp", "st1");
        _fstp(_qword(_deref("esp")));
      }
      void DDIV() {
        debug("DDIV");
        _fld(_qword(_deref("esp")));
        _add("esp", _byte(8));
        _fld(_qword(_deref("esp")));
        __cmd1("fdivrp", "st1");
        _fstp(_qword(_deref("esp")));
      }
      void DCMP() {
        debug("DCMP");
        _fld(_qword(_deref("esp")));
        _fld(_qword(_deref("esp", 8)));
        _add("esp", _byte(12));
        __cmd1("fsubrp", "st1");
        os() << "\tfxtract\n";
        __cmd1("ffree", "st1");
        _fistp(_dword(_deref("esp")));
      }
      void DNEG() {
        debug("DNEG");
        _fld(_qword(_deref("esp")));
        os() << "\tfchs\n";
        _fstp(_qword(_deref("esp")));
      }
      void NIL() {
        debug("NIL");
      }
      void TEXT() {
        debug("TEXT");
        _segment(".text");
      }
      void RODATA() {
        debug("RODATA");
        _segment(".rodata");
      }
      void DATA() {
        debug("DATA");
        _segment(".data");
      }
      void BSS() {
        debug("BSS");
        _segment(".bss");
      }
      void ALIGN() {
        debug("ALIGN");
        os() << "align\t4\n";
      }
      void EXTERN(std::string label) {
        debug("EXTERN", label);
        os() << "extern\t" << label << "\n";
      }
      void COMMON(int value) {
        debug("COMMON", value);
        os() << "common\t" << value << "\n";
      }
      void GLOBAL(const char *label, std::string type) {
        GLOBAL(std::string(label), type);
      }
      void GLOBAL(std::string label, std::string type) {
        debug("GLOBAL", label + ", " + type);
        os() << "global\t" << label << type << "\n";
      }
      void LABEL(std::string label) {
        debug("LABEL", label);
        os() << label << ":\n";
      }
      void CONST(int value) {
        debug("CONST", value);
        __cmd1("dd", value);
      }
      void STR(std::string value) {
        debug("STR", "(value omitted -- see below)");
        os() << "\tdb\t";
        for (size_t ix = 0; ix < value.length();) {
          if (isalnum(value[ix])) {
            os() << '"';
            while (isalnum(value[ix]))
              os() << value[ix++];
            os() << '"';
          } else {
            os() << (int)(unsigned char)value[ix++];
          }
          os() << ", ";
        }
        os() << "0" << std::endl;
      }
      void CHAR(char value) {
        debug("CHAR", (int)value);
        os() << "\tdb\t" << (int)value << "\n";
      }
      void ID(std::string label) {
        debug("ID", label);
        __cmd1("dd", label);
      }
      void BYTE(int value) {
        debug("BYTE", value);
        __cmd1("resb", value);
      }
      void FLOAT(float value) {
        debug("FLOAT", value);
        __cmd1("dd", value);
      }
      void DOUBLE(double value) {
        debug("DOUBLE", value);
        __cmd1("dq", value);
      }
      void ULDCHR() {
        debug("ULDCHR");
        __cmd2("movsx", "eax", _byte(_deref("ecx")));
      }
      void ULD16() {
        debug("ULD16");
        __cmd2("movsx", "eax", _word(_deref("ecx")));
      }
      void UDIV() {
        debug("UDIV");
        _pop("ecx");
        _pop("eax");
        _xor("edx", "edx");
        __cmd1("idiv", "ecx");
        _push("eax");
      }
      void UMOD() {
        debug("UMOD");
        _pop("ecx");
        _pop("eax");
        _xor("edx", "edx");
        __cmd1("idiv", "ecx");
        _push("edx");
      }
      void UGT() {
        debug("UGT");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        __cmd1("seta", "cl");
        _mov(_deref("esp"), "ecx");
      }
      void UGE() {
        debug("UGE");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        __cmd1("setae", "cl");
        _mov(_deref("esp"), "ecx");
      }
      void ULT() {
        debug("ULT");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        __cmd1("setb", "cl");
        _mov(_deref("esp"), "ecx");
      }
      void ULE() {
        debug("ULE");
        _pop("eax");
        _xor("ecx", "ecx");
        _cmp(_deref("esp"), "eax");
        __cmd1("setbe", "cl");
        _mov(_deref("esp"), "ecx");
      }
      void JEQ(std::string label) {
        debug("JEQ", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tje near " << label << "\n";
      }
      void JNE(std::string label) {
        debug("JNE", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tjne near " << label << "\n";
      }
      void JGT(std::string label) {
        debug("JGT", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tjg near " << label << "\n";
      }
      void JGE(std::string label) {
        debug("JGE", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tjge near " << label << "\n";
      }
      void JLT(std::string label) {
        debug("JLT", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tjl near " << label << "\n";
      }
      void JLE(std::string label) {
        debug("JLE", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tjle near " << label << "\n";
      }
      void JUGT(std::string label) {
        debug("JUGT", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tja near " << label << "\n";
      }
      void JUGE(std::string label) {
        debug("JUGE", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tjae near " << label << "\n";
      }
      void JULT(std::string label) {
        debug("JULT", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tjbe near " << label << "\n";
      }
      void JULE(std::string label) {
        debug("JULE", label);
        _pop("eax");
        _pop("ecx");
        _cmp("eax", "ecx");
        os() << "\tjb near " << label << "\n";
      }

    };

  }      // namespace generator
} // namespace cdk

#endif

// $Log: ix86.h,v $
// Revision 1.24  2013/02/10 19:18:24  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.23  2013/02/09 19:00:35  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.22  2013/02/03 15:47:34  david
// *** empty log message ***
//
// Revision 1.21  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.20  2012/03/06 15:07:46  david
// Added subtype to ExpressionType. This allows for more expressiveness in
// type description.
//
// Revision 1.19  2012/02/18 19:39:00  david
// This is the first commit in CDK7. Evaluators and code generators are now aware
// of the debug command line options.
//
