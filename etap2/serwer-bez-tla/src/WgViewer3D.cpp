#include <iostream>
#include "WgViewer3D.hh"
#include "BackgroundImage.hh"

using namespace std;




//====================================================================
//===                  WgViewier3D
//===


/*!
 *
 */
WgViewer3D::WgViewer3D(QWidget *pParent, BufferedScene  *pBScn):
  QGLViewer(pParent),  _pBuffScn(pBScn)
{
  _Timer.setInterval(50);
  connect(&_Timer,SIGNAL(timeout()),this,SLOT(PeriodicSceneUpdate()));
  _Timer.start();
}




void WgViewer3D::PeriodicSceneUpdate()
{
  if (_pBuffScn->IsChanged()) update();
}







void WgViewer3D::init()
{
  // Restore previous viewer state.
  restoreStateFromFile();


  // GLfloat Light1_Position[] = { 1.0, 1.0, 1.0, 0.0 };
  // glLightfv(GL_LIGHT0, GL_POSITION, Light1_Position);

  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
}

void WgViewer3D::draw()
{
  //  GLfloat Light1_Position[] = { 3*SLIDER2RAD(X), 3*SLIDER2RAD(Y), 3*SLIDER2RAD(Z), 0.0 };
  //  glLightfv(GL_LIGHT0, GL_POSITION, Light1_Position);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
   /*-----------------------------------------------------
    *  Tworzenie tła wypełnionego wygenerowaną teksturą
    */
  glDisable(GL_TEXTURE_2D);
  
  glDepthMask(GL_TRUE);

  
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
 
  glScalef( 0.1, 0.1, 0.1 );

  _pBuffScn->LockAccessToCurrScn();
  for (const std::shared_ptr<GraphObject> &PGraphObj : _pBuffScn->GetCurrScn()->GetGraphList()) {
    PGraphObj->DrawGL();
  }
  _pBuffScn->CancelTrace0Change();
  _pBuffScn->UnlockAccessToCurrScn();
 glFlush();
 glDisable(GL_TEXTURE_2D);  
}



QString WgViewer3D::helpString() const
{
  QString text("<h2>V i e w e r 3 D</h2>");
  text += "Use the mouse to move the camera around the object. ";
  text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
  text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
  text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
  text += "Simply press the function key again to restore it. Several keyFrames define a ";
  text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
  text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
  text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
  text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
  text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
  text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
  text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
  text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
  text += "Press <b>Escape</b> to exit the viewer.";
  return text;
}



//===
//===                  WgViewier3D
//====================================================================
