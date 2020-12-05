#ifndef ANGLESRPY_HH
#define ANGLESRPY_HH

/*!
 * \file
 * \brief Zawiera definicję klasy AnglesRPY
 */

#include <iostream>


/*!
 * \brief Modeluje zestaw kątów typu Roll-Pitch-Yaw
 */
class AnglesRPY {
       /*!
        * \brief Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OZ.
	*
	* Kąt \e yaw reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OZ. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Yaw_deg = 0;

       /*!
        * \brief Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OY.
	*
	* Kąt \e pitch reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OY. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Pitch_deg = 0;

       /*!
        * \brief Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        *        wokół osi \e OX.
	*
	* Kąt \e roll reprezentuje rotację zgodnie z ruchem wskazówek zegara
        * wokół osi \e OX. Wartość kąta wyrażona jest w stopniach.
        */
       double _Ang_Roll_deg = 0;
   public:
      /*!
       * \brief Udostępia wartość kąta \e roll.
       *
       * Udostępia wartość kąta \e roll. Jest ona wyrażona w stopniach.
       */
       double GetAng_Roll_deg() const { return _Ang_Roll_deg; }
      /*!
       * \brief Udostępia wartość kąta \e pitch.
       *
       * Udostępia wartość kąta \e pitch. Jest ona wyrażona w stopniach.
       */
       double GetAng_Pitch_deg() const { return _Ang_Pitch_deg; }
       /*!
       * \brief Udostępia wartość kąta \e yaw.
       *
       * Udostępia wartość kąta \e yaw. Jest ona wyrażona w stopniach.
       */
       double GetAng_Yaw_deg() const { return _Ang_Yaw_deg; }
  
      /*!
       * \brief Zmienia wartość kąta \e roll.
       *
       * Zmienia wartość kąta \e roll.
       * \param[in] Ang_Roll_deg - nowa wartość kąta \e roll wyrażona w stopniach.
       */
       void SetAng_Roll_deg(double Ang_Roll_deg) { _Ang_Roll_deg = Ang_Roll_deg; }
      /*!
       * \brief Zmienia wartość kąta \e pitch.
       *
       * Zmienia wartość kąta \e pitch.
       * \param[in] Ang_Pitch_deg - nowa wartość kąta \e pitch wyrażona w stopniach.
       */
       void SetAng_Pitch_deg(double Ang_Pitch_deg) { _Ang_Pitch_deg = Ang_Pitch_deg; }
      /*!
       * \brief Zmienia wartość kąta \e yaw.
       *
       * Zmienia wartość kąta \e yaw.
       * \param[in] Ang_Yaw_deg - nowa wartość kąta \e yaw wyrażona w stopniach.
       */
       void SetAng_Yaw_deg(double Ang_Yaw_deg) { _Ang_Yaw_deg = Ang_Yaw_deg; }  
};


inline
std::istream & operator >> (std::istream & IStrm, AnglesRPY &rAngles_deg)
{
  double  Angle_Roll_deg, Angle_Pitch_deg, Angle_Yaw_deg;

  IStrm >> Angle_Roll_deg >> Angle_Pitch_deg >> Angle_Yaw_deg;
  if (IStrm.fail()) return IStrm;
  rAngles_deg.SetAng_Roll_deg(Angle_Roll_deg);
  rAngles_deg.SetAng_Pitch_deg(Angle_Pitch_deg);
  rAngles_deg.SetAng_Yaw_deg(Angle_Yaw_deg);
  return IStrm;
}


inline
std::ostream & operator << (std::ostream & OStrm, const AnglesRPY &rAngles_deg)
{
  OStrm << rAngles_deg.GetAng_Roll_deg()
	<< " "
	<< rAngles_deg.GetAng_Pitch_deg()
	<< " "
	<< rAngles_deg.GetAng_Yaw_deg();
  return OStrm;
}



#endif
