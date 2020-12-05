#ifndef GRAPHOBJECT_HH
#define GRAPHOBJECT_HH


#include <string>
#include "Vector3D.hh"
#include "AnglesRPY.hh"
#include "RGB.hh"


/*!
 * \file
 * \brief Zawiera definicję klasy GraphObject
 *
 * Plik zawiera definicję klasy GraphObject.
 * Definicja to może być rozszerzona i zmienione mogą
 * być nazwy pól. Obowiązkowe są jedynie nazwy metod.
 */




   /*!
    * Nazwy pól klasy są jedynie propozycją i mogą być zmienione
    * Nazwy metod są obowiązujące.
    */
    class GraphObject {
      /*!
       * \brief Kąty \e Roll-Pitch-Yaw określające orientację obiektu.
       */
       AnglesRPY  _AngRPY_deg;
       /*!
        * \brief Współrzędne aktualnej pozycji obiektu.
	*
	* Współrzędne aktualnej pozycji obiektu. Przyjmuje się,
	* że współrzędne wyrażone są w metrach.
        */
       Vector3D  _Position_m;
      /*!
       * \brief Kolor we współrzędnych RGB.
       */
       RGB     _ColorRGB;
       // /*!
       //  * \brief Nazwa obiektu, która go indentyfikuje.
       //  *
       //  * Nazwa obiektu, która go indentyfikuje. Z tego względu musi
       //  * musi to być nazwa unikalna wśród wszystkich obiektów na scenie.
       //  */
       // std::string  _Name;

     public:
      /*!
       * \brief Inicjalizuje wartościami współrzędnych pozycji i kątów orientacji.
       *
       *  Inicjalizuje wartościami współrzędnych pozycji i kątów orientacji.
       *  \param[in] rPos_m - współrzędne pozycji środka obiektu. Przyjmuje się,
       *                     że wartości współrzędnych wyrażone są w metrach.
       *  \param[in] rAngles_deg - kąty orientacji obiektu w reprezentacji
       *                      \e Roll-Pitch-Yaw. Przyjmuje się, że wartości kątów
       *                      wyrażone są w stopniach.
       *  \param[in]  rColor  - kolor we współrzędnych RGB.
       */
      GraphObject(const Vector3D &rPos_m, const AnglesRPY &rAngles_deg, const RGB   &rColor):
	_AngRPY_deg(rAngles_deg),  _Position_m(rPos_m), _ColorRGB(rColor) {}
      
      /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
       */
       double GetAng_Roll_deg() const { return _AngRPY_deg.GetAng_Roll_deg(); }
      /*!
       * \brief Udostępia wartość kąta \e pitch.
       *
       * Udostępia wartość kąta \e pitch. Jest ona wyrażona w stopniach.
       */
       double GetAng_Pitch_deg() const { return _AngRPY_deg.GetAng_Pitch_deg(); }
       /*!
       * \brief Udostępia wartość kąta \e yaw.
       *
       * Udostępia wartość kąta \e yaw. Jest ona wyrażona w stopniach.
       */
       double GetAng_Yaw_deg() const { return _AngRPY_deg.GetAng_Yaw_deg(); }

      /*!
       * \brief Zmienia wartość kąta \e roll.
       *
       * Zmienia wartość kąta \e roll.
       * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
       */
       void SetAng_Roll_deg(double Ang_Roll_deg)
                              { _AngRPY_deg.SetAng_Roll_deg(Ang_Roll_deg); }
      /*!
       * \brief Zmienia wartość kąta \e pitch.
       *
       * Zmienia wartość kąta \e pitch.
       * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
       */
       void SetAng_Pitch_deg(double Ang_Pitch_deg)
                              { _AngRPY_deg.SetAng_Pitch_deg(Ang_Pitch_deg); }
      /*!
       * \brief Zmienia wartość kąta \e yaw.
       *
       * Zmienia wartość kąta \e yaw.
       * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
       */
      void SetAng_Yaw_deg(double Ang_Yaw_deg)
                              { _AngRPY_deg.SetAng_Yaw_deg(Ang_Yaw_deg); }

      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie tylko do odczytu.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie tylko do odczytu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
       const Vector3D & GetPositoin_m() const { return _Position_m; }
      /*!
       * \brief Udostępnia współrzędne położenia obiektu w trybie modyfikacji.
       *
       * Udostępnia współrzędne punktu, który definiuje położenia obiektu
       * w trybie modyfikacji.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       */
       Vector3D & UsePosition_m() { return _Position_m; }
      /*!
       * \brief Zmienia współrzędne położenia obiektu.
       *
       * Zmienia współrzędne punktu, który definiuje położenia obiektu.
       * Domyślnie przyjmuje się, że jest to geometryczny środek bryły.
       * \param[in] rPos_m - współrzędne nowgo położenia. Przyjmuje się,
       *                     że są one wyrażone w metrach.
       */
       void SetPosition_m(const Vector3D &rPos_m) { _Position_m = rPos_m; }
      /*!
       * \brief Udostępnia składowe koloru w konwencji RGB
       */
      const RGB& GetColorRGB() const { return _ColorRGB; }
      /*!
       * \brief Generuje kod, który pozwala rysować obiekt w OpenGL.
       */
       virtual void DrawGL() const = 0;
      // /*!
      //  * \brief Zmienia nazwę obiektu.
      //  *
      //  *  Zmienia nazwę obiektu.
      //  *  \param[in] sName - nowa nazwa obiektu.
      //  */
      //  void SetName(const char* sName) { _Name = sName; }
      //  /*!
      //   * \brief Udostępnia nazwę obiektu.
      // 	*
      // 	* Udostępnia nazwę obiektu w trybie tylko do odczytu.
      //   */
      //  const std::string & GetName() const { return _Name; }
    };


#endif
