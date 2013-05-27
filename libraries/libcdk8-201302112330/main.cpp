// $Id: main.cpp,v 1.23 2013/02/10 19:18:24 david Exp $ -*- c++ -*-
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cdk/Compiler.h>
#include <cdk/CompilerFactory.h>

void usage(const char *progname) {
  std::cerr << "Usage: " << std::endl << "\t" << progname
      << " [-O] [-tree] [-trace LEVEL] [-target output-format] [-o outfile] infile" << std::endl
      << " -h " << std::endl
      << "\t(if an option is specified multiple times, only the last one is considered)"
      << std::endl;
  exit(1);
}

//---------------------------------------------------------------------------

void processCmdLineOptions(int argc, char **argv, cdk::Compiler *compiler) {

#ifdef YYDEBUG
  extern int yydebug;
  yydebug = getenv("YYDEBUG") ? 1 : 0;
#endif

  compiler->extension("asm"); // default output extension/target: ASM

  std::string ifile = "", ofile = "";
  for (int ax = 1; ax < argc; ax++) {
    std::string option = argv[ax];
    if (option == "-h") usage(argv[0]);
    else if (option == "-O")
      compiler->optimize(true);
    else if (option == "-g")
      compiler->debug(true);
    else if (option == "-tree")
      compiler->extension("xml");
    else if (option == "-target") {
      compiler->extension(argv[++ax]);
    } else if (option == "-o") {
      ofile = argv[++ax];
      size_t dot = ofile.find_last_of('.');
      if (dot != std::string::npos) {
        compiler->extension(ofile.substr(dot + 1));
      }
      compiler->ofile(ofile.c_str());
      std::ostream *ofs = new std::ofstream(compiler->ofile().c_str());
      compiler->ostream(ofs);
    } else {
      if (ifile == "") {
        ifile = argv[ax];
        compiler->ifile(ifile);
        std::istream *ifs = new std::ifstream(compiler->ifile().c_str());
        compiler->istream(ifs);
      } else
        usage(argv[0]);
    }
  }

  //if (ifile == "") usage(argv[0]);
  if (ofile == "" && ifile != "") {
    size_t dot = ifile.find_last_of('.');
    ofile = ifile.substr(0, dot) + "." + compiler->extension();
    compiler->ofile(ofile);
    std::ostream *ofs = new std::ofstream(compiler->ofile().c_str());
    compiler->ostream(ofs);
  }

}

//---------------------------------------------------------------------------

int main(int argc, char *argv[]) {
  /* ====[ COMPILER INITIALIZATION ]==== */

  std::string language = argv[0];

  // if the compiler is called dir1/dir2/compact-XML, for instance,
  // extract "compact-XML"
  size_t ipos = language.find_last_of("/");
  if (ipos == std::string::npos)
    ipos = -1;
  language = language.substr(ipos + 1);

  // if the compiler is called compact-XML, for instance, extract "compact"
  size_t fpos = language.find_first_of("-.");
  language = language.substr(0, fpos);

  cdk::CompilerFactory *fact = cdk::CompilerFactory::getImplementation(language);
  if (!fact) {
    std::cerr << "FATAL: No implementation available for language '" << language << "'. Exiting..."
        << std::endl;
    exit(1);
  }

  cdk::Compiler *compiler = fact->createCompiler(language.c_str());

  /* ====[ COMMAND LINE ARGUMENTS ]==== */
  processCmdLineOptions(argc, argv, compiler);

  /* ====[ SYNTACTIC ANALYSIS ]==== */

  if (compiler->parse() != 0 || compiler->errors() > 0) {
    std::cerr << "** Syntax errors in " << compiler->ifile() << std::endl;
    return 1;
  }

  /* ====[ SEMANTIC ANALYSIS ]==== */

  if (!compiler->evaluate()) {
    std::cerr << "** Semantic errors in " << compiler->ifile() << std::endl;
    return 1;
  }

  return 0;
}

// $Log: main.cpp,v $
// Revision 1.23  2013/02/10 19:18:24  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.22  2013/02/09 19:00:34  david
// First CDK8 commit. Major code simplification.
// Starting C++11 implementation.
//
// Revision 1.21  2013/02/03 15:47:34  david
// *** empty log message ***
//
// Revision 1.20  2012/04/10 19:01:05  david
// Removed initialization-dependent static members in factories.
// Handling of ProgramNodes is now better encapsulated by visitors (not done
// by evaluators, as before). Major cleanup (comments).
//
// Revision 1.19  2012/02/18 19:38:59  david
// This is the first commit in CDK7. Evaluators and code generators are now aware
// of the debug command line options.
//
