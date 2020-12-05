#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <fstream>

using namespace std;


/*!
 * Zawiera przykład definicji interpretacji zapisu poleceń z wykorzystaniem
 * kolekcji std::map<> przechowujących funkcje ich obsługi.
 */



bool CzytajDlaMove(istream &Strm)
{
  double Param1, Param2, Param3;

  Strm >> Param1 >> Param2 >> Param3;
  if (Strm.fail()) return false;
  cout << " Move Parametr: " << Param1 << " " << Param2 << " " << Param3 << endl;
  return true;
}



bool CzytajDlaRotate(istream &Strm)
{
  double Param1, Param2;

  Strm >> Param1 >> Param2;
  if (Strm.fail()) return false;
  cout << " Rotate Parametr: " << Param1 << " " << Param2 << endl;
  return true;
}




bool ExecCmd_Move()
{
  cout << " ExecCmd Move" << endl;
  return true;
}



bool ExecCmd_Rotate()
{
  cout << " ExecCmd Rotate" << endl;
  return true;
}


typedef bool (Type4ReadFun)(istream &rIStrm);
typedef bool (Type4ExecFun)();


class LibInterface {
   string         _CmdName;
  public:
   Type4ReadFun   *_pReadParams;
   Type4ExecFun   *_pExecCmd;


   LibInterface(const char* sCmdName, Type4ReadFun  *pReadParams,  Type4ExecFun *pExecCmd):
          _CmdName(sCmdName), _pReadParams(pReadParams), _pExecCmd(pExecCmd) {}

   const string& GetCmdName() const { return _CmdName; }
};






typedef map<string,shared_ptr<LibInterface>>   Set0LibInterfs;


class Plugins {
   Set0LibInterfs   _Set0Libs;
 public:
    void Add(shared_ptr<LibInterface> &PLibInterf)
        { _Set0Libs
	   .insert(pair<string,shared_ptr<LibInterface>>(PLibInterf->GetCmdName(),PLibInterf));
	}
    bool Find(const string &rName, shared_ptr<LibInterface> &PLibInterf)
     {
        Set0LibInterfs::const_iterator Iter = _Set0Libs.find(rName);
	if (Iter == _Set0Libs.end()) return false;
	PLibInterf = Iter->second;
	return true;
     }    
};




bool WykonajProgram(Plugins  &rSet0Cmds, const char* sNazwaProgramu)
{
 ifstream StrmWej(sNazwaProgramu);

  if (!StrmWej.is_open()) {
    cerr << "Blad otwarcia" << endl;
    return false;
  }

  string  SlowoKluczowe;
  shared_ptr<LibInterface>  PLib_xxx;
  
  StrmWej >> SlowoKluczowe;
  while (!StrmWej.fail()) {
    if (!rSet0Cmds.Find(SlowoKluczowe,PLib_xxx)) {
       cout << "Nieznane polecenie" << endl;
       return false;
    }
    if (!PLib_xxx->_pReadParams(StrmWej)) {
       cout << "Czytanie nie powiodlo sie" << endl;
       return false;
    }
    PLib_xxx->_pExecCmd();
    StrmWej >> SlowoKluczowe;
  }  
}







int main()
{
  shared_ptr<LibInterface>  PLib_Move = make_shared<LibInterface>("Move",CzytajDlaMove,ExecCmd_Move);
  shared_ptr<LibInterface>  PLib_Rotate = make_shared<LibInterface>("Rotate",CzytajDlaRotate,ExecCmd_Rotate);
  Plugins   Set0Cmds;

  Set0Cmds.Add(PLib_Move);
  Set0Cmds.Add(PLib_Rotate);
  
  cout << endl;
  WykonajProgram(Set0Cmds,"polecenia.cmd");
  cout << endl;  
}
