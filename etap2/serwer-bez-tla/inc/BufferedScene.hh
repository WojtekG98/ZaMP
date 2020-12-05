#ifndef BUFFEREDSCENE_HH
#define BUFFEREDSCENE_HH

/*!
 * \file
 * \brief Zawiera definicję klasy BufferedScene
 */

#include "Scene.hh"
#include <mutex>
#include <memory>

/*!
 * \brief Modeleluje buforowaną scenę.
 *
 * Modeleluje buforowaną scenę. Pozwala to wykonywać
 * niezależnie peracje wyświetlania i przebudowywania sceny.
 */
class BufferedScene {
   /*!
   * \brief Scena zawierającej bryły reprezentowane przez
   *        obiekty graficzne.
   */
   Scene               _ScnTab[2];
  /*!
   * \brief Wskaźnik na wyświetlaną bieżącą scenę.
   */
   Scene              *_pCurrScn = nullptr;
  /*!
   * \brief Zabezpiecza selektywny dostęp do aktualnej sceny.
   */
   std::mutex          _Mutex_CurrScn;

  /*!
   * \brief Wskaźnik na scenę przygotowywaną do wyświetlenia.
   */
   Scene              *_pPrepScn = nullptr;
  /*!
   * \brief Zabezpiecza selektywny dostęp do przygotowywanej sceny.
   */
   std::mutex          _Mutex_PrepScn;
  /*!
   * \brief Ślad zmiany
   */
   bool                _Trace0Change = false;

  public:
   /*!
    * \brief Inicjalizuje pola dla aktualnej sceny i przygotowywanej.
    */
    BufferedScene(): _pCurrScn(&_ScnTab[0]), _pPrepScn(&_ScnTab[1]) {}
   /*!
    * \brief Udostępnia informacje o zmianie.
    */
    bool IsChanged() const { return _Trace0Change; }
   /*!
    * \brief Zaznacza zmianę
    */
    void MarkTrace0Change() { _Trace0Change = true; }
   /*!
    * \brief Kasuje ślad zmiany
    */
    void CancelTrace0Change() { _Trace0Change = false; }
   /*!
    * \brief Usuwa obiekty z przygotowywanej sceny
    */
    void ClearPrepScn();
   /*!
    * \brief Zamienia sceny
    */
    void SwapScn();
   /*!
    * \brief Dodaje prostopadłościan
    */
    void AddCube2PrepScn(
		           const Vector3D   &rSize_m,
		           const Vector3D   &rPos_m,
		           const AnglesRPY  &rAngles_deg,
		           const RGB        &rColors
		        );
  /*!
   * \brief Zablokowanie dostępu do bieżącej sceny
   */
   void LockAccessToCurrScn() { _Mutex_CurrScn.lock(); }



  /*!
   * \brief Otwarcie dostępu do bieżącej sceny
   */
   void UnlockAccessToCurrScn() { _Mutex_CurrScn.unlock(); }
  /*!
   * \brief Dostęp do bieżącej sceny.
   */
   const Scene* GetCurrScn() const { return _pCurrScn; }
};

#endif
