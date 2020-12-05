#include "Scene.hh"
#include "Cuboid.hh"



/*!
 * Dodaje prostopadłościan na koniec listy obiektów graficznych.
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
void Scene::AddCuboid(
		    const Vector3D  &rSize_m,
		    const Vector3D  &rPos_m,
		    const AnglesRPY &rAngles_deg,
		    const RGB       &rColors
		  )
{
  _GraphObjs.push_back(std::make_shared<Cuboid>(rSize_m,rPos_m,rAngles_deg,rColors));
}
