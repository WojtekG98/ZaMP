#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"
#include <string>

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego obrot
 *
 *  Klasa modeluje ...
 */
class Interp4Rotate: public Interp4Command {
  /*!
   * \brief Zmienna przechowujaca nazwe obiektu.
   */
  std::string _Obj_Name;
  /*!
   * \brief Zmienna przechowujaca wartosc szybkosci katowej w [kat/s]
   */
  double  _AngSpeed_degS;
  /*!
   * \brief Zmienna przechowujaca wartosc katu obrotu w [kat]
   */
  double  _deg_deg;
 public:
  /*!
   * \brief
   */
  Interp4Rotate();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd( MobileObj  *pMobObj, int Socket) const;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
