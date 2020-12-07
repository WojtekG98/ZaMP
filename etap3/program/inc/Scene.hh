#ifndef SCENE_HH
#define SCENE_HH

#include "MobileObj.hh"
#include "AccessControl.hh"
#include <string>
#include <memory>
#include <map>

using namespace std;

/*!
 * \brief Deklaracja instacji szablonu std::map<string,std::shared_ptr<MobileObj>>
 */

typedef map<string,shared_ptr<MobileObj>> Set0MobileObjs; // Set of Mobile Objets   
/*!
 * \brief Klasa modelujaca Scene, czyli zbior obiektow mobilnych
 */
class Scene: public AccessControl {
   /*!
    * \brief Zbior obiektow mobilnych.
    */
    Set0MobileObjs   _Set0MobObjs;
  public:
    /*!
     * \brief Zwraca uchwyt do zbioru obiektow.
     */
    const Set0MobileObjs & GetMobObjs() const { return _Set0MobObjs; }
    /*!
     * \brief Dodaje obiekt PMobObj do zbioru.
     * \param PMobObj - uchwyt do obiektu który zostanie dodany do zbioru 
     */
    void Add(shared_ptr<MobileObj> &PMobObj)
      { _Set0MobObjs.insert(pair<string,shared_ptr<MobileObj>>(PMobObj->GetName(),PMobObj)); }
    /*!
     * \brief Znajduje obiekt o nazwie sName w zbiorze i zwraca wskaznik dzielony na ten obiekt do zmiennej PMobObj.
     * \param sName - (\b we.) nazwa szukanego obiektu 
     * \param PMobObj - (\b we.) uchwyt do obiektu do którego zostanie przypisany znaleziony obiekt 
     * \retval true - jeśli obiekt zostal znaleziony,
     * \retval false - w przeciwnym przypadku.
     */
    bool Find(const char* sName, shared_ptr<MobileObj> &PMobObj){
      Set0MobileObjs::const_iterator Iter = _Set0MobObjs.find(sName);
      if (Iter == _Set0MobObjs.end()) return false;
      PMobObj = Iter->second;
      return true;
    }
};    
#endif

