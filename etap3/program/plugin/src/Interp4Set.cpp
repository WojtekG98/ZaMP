#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _DesPosition_m()
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << _Obj_Name << " " << _DesPosition_m[0] << " " << _DesPosition_m[1] << " " << _DesPosition_m[2] << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccCtrl) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  
  pAccCtrl->LockAccess();
  pMobObj->SetPosition_m(_DesPosition_m);
  pAccCtrl->UnlockAccess();
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Obj_Name >> _DesPosition_m[0] >> _DesPosition_m[1] >> _DesPosition_m[2];
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  wspX wspY  KatOZ[deg]" << endl;
}
