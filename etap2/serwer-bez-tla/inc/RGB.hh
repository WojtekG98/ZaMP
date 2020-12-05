#ifndef RGB_HH
#define RGB_HH

/*!
 * \file
 * \brief Zawiera definicję klasy RGB
 *
 */




#include <iostream>


/*!
 * \brief Modeluje zestaw współrzędnych koloru w notacji RGB
 */
class RGB {
       /*!
        * \brief Kolor niebiecki
	*
	* Dopuszczalna wartość pola musi być z zakresu [0,255].
        */
       unsigned short int _Color_Blue = 0;

       /*!
        * \brief Kolor zielone
	*
	* Dopuszczalna wartość pola musi być z zakresu [0,255].
        */
       unsigned short int _Color_Green = 0;

       /*!
        * \brief Kolor czerwony
	*
	* Dopuszczalna wartość pola musi być z zakresu [0,255].
        */
       unsigned short int _Color_Red = 0;
   public:
      /*!
       * \brief Udostępia wartość koloru czerwonego.
       */
       unsigned short int GetColor_Red() const { return _Color_Red; }
      /*!
       * \brief Udostępia wartość koloru zielonego.
       */
       unsigned short int GetColor_Green() const { return _Color_Green; }
       /*!
       * \brief Udostępia wartość koloru niebieskiego.
       */
       unsigned short int GetColor_Blue() const { return _Color_Blue; }
  
      /*!
       * \brief Zmienia wartość koloru czerwonego.
       *
       * Zmienia wartość koloru czerwonego.
       * \param[in] Color_Red - nowa wartość koloru czerwonego.
       */
       void SetColor_Red(unsigned short int Color_Red) { _Color_Red = Color_Red; }
      /*!
       * \brief Zmienia wartość koloru zielonego.
       *
       * Zmienia wartość koloru zielonego.
       * \param[in] Color_Green - nowa wartość koloru zielonego.
       */
       void SetColor_Green(unsigned short int Color_Green) { _Color_Green = Color_Green; }
      /*!
       * \brief Zmienia wartość koloru niebieskiego.
       *
       * Zmienia wartość koloru niebieskiego.
       * \param[in] Color_Green - nowa wartość koloru niebieskiego.
       */
       void SetColor_Blue(unsigned short int Color_Blue) { _Color_Blue = Color_Blue; }  
};


inline
std::istream & operator >> (std::istream & IStrm, RGB &rColors)
{
  unsigned short int  Color_Red, Color_Green, Color_Blue;

  IStrm >> Color_Red >> Color_Green >> Color_Blue;
  if (IStrm.fail()) return IStrm;
  rColors.SetColor_Red(Color_Red);
  rColors.SetColor_Green(Color_Green);
  rColors.SetColor_Blue(Color_Blue);
  return IStrm;
}


inline
std::ostream & operator << (std::ostream & OStrm, const RGB &rColors)
{
  OStrm << rColors.GetColor_Red() << " " << rColors.GetColor_Green() << " " << rColors.GetColor_Blue();
  return OStrm;
}

#endif
