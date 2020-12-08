#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <cstdio>
#include "Interp4Command.hh"
#include "Set4LibInterfaces.hh"
#include "Scene.hh"
#include "MobileObj.hh"
#include "Cuboid.hh"
#include "xmlinterp.hh"
#include "ProgramInterpreter.hh"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>




using namespace std;
using namespace xercesc;

int main(int argc, char** argv)
{
  // Sprawdzamy, czy jest wystarczajaca ilosc argumentow
  istringstream IStrm;
  ProgramInterpreter Inter;
  if ( argc < 2) {
  	std::cerr << "!!! Za malo arguemntow\n";
	return 1;
  }
  cout << endl << "Nazwa pliku: " << argv[1] << endl;


  if(!Inter.Read_XML_Config("./config/config.xml")) return 2;
  if(!Inter.SendSceneState2Server()) return 4;

  if(!Inter.ExecProgram(argv[1])) return 3;
  if(!Inter.SendSceneState2Server()) return 5;
 }

