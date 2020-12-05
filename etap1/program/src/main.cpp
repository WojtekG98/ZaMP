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

#define LINE_SIZE 500

using namespace std;

bool ExecPreprocesor( const char * NazwaPliku, istringstream &IStrm4Cmds )
{
	string Cmd4Preproc = "cpp -P ";
        char Line[LINE_SIZE];
        ostringstream OTmpStrm;
        Cmd4Preproc += NazwaPliku;
        FILE* pProc = popen(Cmd4Preproc.c_str(), "r");
        if (!pProc) return false;
        while (fgets(Line,LINE_SIZE,pProc)) {
                OTmpStrm << Line;
        }
        IStrm4Cmds.str(OTmpStrm.str());
        return pclose(pProc) == 0;
}

bool ExecProgram(istream &rIStrm, Set4LibInterfaces _Plugins)
{
  string KeyWord;
  shared_ptr<LibInterface> Wtyczka;  
  Interp4Command *wInterf;
  rIStrm >> KeyWord;
  
  
  if (!_Plugins.Find(KeyWord.c_str(),Wtyczka))
    return false;
  wInterf = Wtyczka->CreateCmd();
  if (!wInterf->ReadParams(rIStrm)) return false;
  cout << "---Parametry---" << endl;
  wInterf->PrintCmd();
  return true;
}

int main(int argc, char** argv)
{
  // Sprawdzamy, czy jest wystarczajaca ilosc argumentow
  if ( argc < 2) {
  	std::cerr << "!!! Za malo arguemntow\n";
	return 1;
  }
  cout << endl << "Nazwa pliku: " << argv[1] << endl;

  istringstream IStrm;
  if (!ExecPreprocesor(argv[1], IStrm)) {
        return 2;
  }
  cout << IStrm.str() <<endl;
  
  Set4LibInterfaces Plugins;
  Scene Scena;
  shared_ptr<Cuboid> Kostka = make_shared<Cuboid>();
  shared_ptr<LibInterface> Interface4Move = make_shared<LibInterface>("libInterp4Move.so"),
                           Interface4Set = make_shared<LibInterface>("libInterp4Set.so"),
                           Interface4Rotate = make_shared<LibInterface>("libInterp4Rotate.so"),
                           Interface4Pause = make_shared<LibInterface>("libInterp4Pause.so");
  Plugins.Add(Interface4Move);
  Plugins.Add(Interface4Set);
  Plugins.Add(Interface4Rotate);
  Plugins.Add(Interface4Pause);
  
  while(ExecProgram(IStrm, Plugins));
  return 0;
 }
