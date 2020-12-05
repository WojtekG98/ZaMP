#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <string>
#include <memory>
#include "Scene.hh"
#include "Set4LibInterfaces.hh"

using namespace std;

/*!
 * \brief Klasa pomocnicza modelująca spis wtyczek oraz obiektow wczytywanych z XML.
 */
class Configuration {
public:
 /*!
  * \brief Wskaznik pomocniczy (do usuniecia).
  */
  shared_ptr<string> napis;
 /*!
  * \brief Wskaźnik na zbior interfejsow do wtyczek.
  */
  shared_ptr<Set4LibInterfaces> LibManager;
 /*!
  * \brief Wskaźnik na Scene.
  */
  shared_ptr<Scene> Scn;
//NALEZY DODAC KONSTRUKTOR
};


#endif
