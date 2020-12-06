#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _Speed_mmS(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
 
  cout << GetCmdName() << " " << _Obj_Name  <<  " " << _Speed_mmS  << " " << _Len_m << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccCtrl) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  std::cout << "ExecCmd Move"<< std::endl;
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Obj_Name >> _Speed_mmS >> _Len_m;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
