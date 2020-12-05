#ifndef SCENE_HH
#define SCENE_HH

#include <memory>
#include <list>
#include "GraphObject.hh"

/*!
 * \file 
 * \brief Definicja klasy Scene 
 */

/*!
 * \brief Lista obiektów graficznych
 */
typedef std::list<std::shared_ptr<GraphObject>>  GraphList;

/*!
 * \brief Modeluje scenę, na której umieszczony jest zbiór obiektów
 *        graficznych.
 */
class Scene {
    /*!
     * \brief Lista obiektów graficznych, które mają być wizualizowane
     *        na scenie.
     */
     GraphList   _GraphObjs;
   public:
    /*!
     * \brief Usuwa wszystkie obiekty z listy.
     */
     void Clear() { _GraphObjs.clear(); }
    /*!
     * \brief Dodaje prostopadłościan na koniec listy obiektów graficznych.
     */
     void AddCuboid(
		     const Vector3D   &rSize_m,
		     const Vector3D   &rPos_m,
		     const AnglesRPY  &rAngles_deg,
		     const RGB        &rColors
		   );
    /*!
     * \brief Umożliwia dostęp do listy obiektów graficznych.
     *
     * Umożliwia dostęp do listy obiektów graficznych. Jest on realizowany
     * w trybie \e tylko \e do \e odczytu.
     */
     const GraphList & GetGraphList() const { return _GraphObjs; }
};



#endif
