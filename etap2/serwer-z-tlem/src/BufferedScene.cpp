#include "BufferedScene.hh"
#include <mutex>
#include <iostream>

using namespace std;


void BufferedScene::ClearPrepScn()
{
  std::lock_guard<std::mutex> oGuard(_Mutex_PrepScn);
  _pPrepScn->Clear();
}



void BufferedScene::SwapScn()
{
  std::lock_guard<std::mutex> oGuard_PrepScn(_Mutex_PrepScn);
  std::lock_guard<std::mutex> oGuard_CurrScn(_Mutex_CurrScn);
  swap(_pCurrScn,_pPrepScn);
  MarkTrace0Change();
}


/*!
 * Do przygotowywanej sceny
 * dodaje prostopadłościan na koniec listy obiektów graficznych.
 * \param[in]  rSize_m - rozmiary boków prostopadłościanu wzdłuż
 *                       poszczególnych osi. Zakłada się, że rozmiary
 *                       podawane są w metrach.
 * \param[in]  rPos_m  - współrzędne pozycji środka prostopadłościanu
 *                       na scenie. Zakłada się, że rozmiary
 *                       podawane są w metrach. 
 * \param[in]  rAngles_deg - kąty orientacji obiektu podane jako kąty
 *                       Roll-Pitch-Yaw. Wartości kątów wyrażone są
 *                       w stopniach.
 * \param[in]  rColors  - kolor we współrzędnych RGB
 */
void BufferedScene::AddCube2PrepScn(
		           const Vector3D   &rSize_m,
		           const Vector3D   &rPos_m,
		           const AnglesRPY  &rAngles_deg,
		           const RGB        &rColors
		        )
{
  _pPrepScn->AddCuboid(rSize_m,rPos_m,rAngles_deg,rColors);
}
