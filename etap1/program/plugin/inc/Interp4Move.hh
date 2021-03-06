#ifndef  COMMAND4MOVE_HH
#define  COMMAND4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"
#include <string>
/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicję klasy Interp4Move
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Move: public Interp4Command {
  /*!
   * \brief Nazwa obiektu.
   * Zmienna przechowujaca nazwe obietu
   */
  std::string _Obj_Name;
  /*!
   * \brief Predkosc jaka nalezy nadac obiektowi w [mm/s].
   * Zmienna przechowujaca szybkosc jaka nalezy nadac robotowi mobilnemu w [mm/s]
   */
  double  _Speed_mmS;
  /*!
   * \brief Dlugosc drogi jaka ma przebyc obiekt w [m]
   *Zmienna przechowujaca dlugosc drogi jaka ma przebyc robot mobilny w [m]
   */
  double _Len_m;
 public:
  /*!
   * \brief
   */
  Interp4Move();  
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
