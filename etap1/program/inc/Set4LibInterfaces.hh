#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include "LibInterface.hh"
#include <string>
#include <map>
#include <memory>

/*!
 * \file
 * \brief Deklaracja instacji szablonu std::map<string,std::shared_ptr<LibInterface>>
 */
   
typedef std::map<std::string,std::shared_ptr<LibInterface>> Set0LibInterfaces;

/*!
 * \brief Instacja szablonu  std::map<string,std::shared_ptr<LibInterface>>
 */

class Set4LibInterfaces{
   /*!
    * \brief Zbior interfejsow do wtyczek.
    */
    Set0LibInterfaces _Set0LibInterfaces;
  public:
    /*!
     * \brief Zwraca uchwyt do zbioru wtyczek.
     */
    const Set0LibInterfaces & GetLibInterfaces() const { return _Set0LibInterfaces; }
    /*!
     * \brief Dodaje wtyczke pLibInterface do zbioru.
     */
    void Add(std::shared_ptr<LibInterface> &pLibInterface){
      _Set0LibInterfaces.insert(std::pair<std::string,std::shared_ptr<LibInterface>>(pLibInterface->GetCmdName(),pLibInterface));
     }
    /*!
     * \brief Znajduje wtyczke o nazwie sName w zbiorze i zwraca wskaznik dzielony na ta wtyczke do zmiennej LibInterface.
     */
    bool Find(const char* sName, std::shared_ptr<LibInterface> &LibInterface){
      
      Set0LibInterfaces::const_iterator Iter = _Set0LibInterfaces.find(sName);
      if (Iter == _Set0LibInterfaces.end()) 
        return false;
      LibInterface = Iter->second;
      return true;
     }
};

#endif
