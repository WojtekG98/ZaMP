#include <iostream>
#include "gtsDebug.hh"
#include "CommandInterpreter.hh"
#include "RGB.hh"

using namespace std;


/*!
 * Wykonuje polecenie, które jest jako pierwsze w kolejce.
 * Polecenie pobierane jest w wewnętrznej kolejki poleceń,
 * które reprezentowane jest przez pole 
 * \link CommandInterpreter::_CmdBuff _CmdBuff\endlink.
 */
bool CommandInterpreter::ExecCmd(BufferedScene &rBScn)
{
  std::string  CmdLine;

  if (!_CmdBuff.Pop(CmdLine)) return false;
  InterpCmd(CmdLine,rBScn);
  return true;
}


/*!
 * Rozpoznaje polecenie i je wykonuje.
 * \param[in] rCmdLine - treść rozpoznawanego polecenia.
 * \retval true - jeżeli z kolejki zostało pobrane jakieś polecenie,
 * \retval false - w przeciwnym przypadku.
 */
bool CommandInterpreter::InterpCmd(const std::string &rCmdLine, BufferedScene  &rBScn)
{
  istringstream IStrm(rCmdLine);
  string     Keyword;
  Vector3D   Sizes_m, Pos_m;
  AnglesRPY  Angles_deg;
  RGB        Colors;
  
  IStrm >> Keyword;
  if (Keyword == "Clear") { rBScn.ClearPrepScn();  return true; }
  if (Keyword == "Display") { rBScn.SwapScn(); return true; }
  if (Keyword == "Cube") {
    IStrm >> Sizes_m >> Pos_m >> Angles_deg >> Colors;
    if (IStrm.fail()) {
      CWarning_1(":(  Bledy w linii polecenia \"Cube\":\n     " << rCmdLine );
      return false;
    }
    rBScn.AddCube2PrepScn(Sizes_m,Pos_m,Angles_deg,Colors);
    //    cout << "  Cube: " << Sizes_m << "  " << Pos_m << "  "
    //	 << Angle_deg << "  " << Colors << endl;
    return true;
  }
  if (Keyword == "Close") {
    CancelContinueListening();
    return true;
  }
  CWarning_1(":(  Nieznane polecenie: " << Keyword << endl <<\
	     ":(  w linii: " << rCmdLine );
  return false;
}


/*!
 * Dodaje nowe polecenie do kolejki, które ma wykonać serwer.
 * \param[in] sCmdLine - tekst polecenia, które ma wykonać serwer.
 */
void CommandInterpreter::AddCmd(const char* sCmdLine)
{
  //  DOut1( "Polecenie: " << sCmdLine );
  _CmdBuff.Push(sCmdLine);
}
