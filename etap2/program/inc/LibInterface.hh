#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include <string>
#include "Interp4Command.hh"
#include <sstream>
#include <dlfcn.h>
/*!
 * \file
 * \brief Definicja klasy LibInterface
 *
 * Plik zawiera definicję klasy LibInterface
 */
     
/*!
 * \brief Modeluje interfejs do biblioteki
 */
class LibInterface{
  /*!
   * \brief Nazwa polecenia (std::string).
   */
  std::string _CmdName;
  /*!
   * \brief Wskaznik obslugujacy biblioteke.
   */
  void *_LibHandler;
  /*!
   * \brief Wskaznik na funkcje CreateCmd z wtyczki.
   */
  Interp4Command *(*_pCreateCmd)(void);
 public:
  /*!
   * \brief Zwraca nazwe polecenia (std::string).
   */
 std::string GetCmdName(){return _CmdName;}
  /*!
   * \brief Zwraca wskaznik na utworzone polecenie.
   */
  Interp4Command *CreateCmd() { return _pCreateCmd();}
  
  /*!
   * \brief Konstruktor klasy
   * \param LibName - (\b we.) nazwa pliku z wtyczką.
   */
  explicit LibInterface(const std::string LibName){
    void *FunHandler;
    _LibHandler = dlopen(LibName.c_str(), RTLD_LAZY);
    
    if(!_LibHandler){
      std::cerr << "Library not found: " << LibName << std::endl;
      throw 1;
    }
    FunHandler = dlsym(_LibHandler, "CreateCmd");
    if(!FunHandler){
      std::cerr << "Create Cmd function not found" << std::endl;
      dlclose(_LibHandler);
      throw 2;
    }
    _pCreateCmd = * reinterpret_cast<Interp4Command* (**)(void)>(&FunHandler);
    _CmdName = _pCreateCmd()->GetCmdName();
  }
};
#endif
