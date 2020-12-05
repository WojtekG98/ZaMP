#ifndef GRAPHICSWINDOW_HH
#define GRAPHICSWINDOW_HH

// #ifdef __GNUG__
// # pragma interface
// # pragma implementation
// #endif


#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include "BufferedScene.hh"


/*!
 * \file
 * \brief Zawiera definicje klasę MainWindow4Server
 */



// /*!
//  * \brief Serwer odbierający od klienta informacje o stanie sceny
//  *
//  *  Klasa modeluje serwer, który odbiera od aplikacji klienckiej
//  *  informacje o aktualnym rozmieszczeniu obiektów graficznych.
//  *  Interpretuje te informacje i tworzy odpowiednie struktry
//  *  danych reprezentujących wspomniane obiekty graficzne.
//  */
// class Serwer {

//  public:
// };



/*!
 * \brief Główne okno aplikacji
 */
class MainWindow4Server: public QMainWindow { //------------------------------
   Q_OBJECT
  public:
   MainWindow4Server(BufferedScene *pBuffScn, QWidget *pParent = nullptr);
							    
  public slots:
   void ShowMessage(const QString &);
}; //------------------------------------------------------------------

#endif
