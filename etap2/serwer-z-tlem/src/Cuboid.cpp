#include "Cuboid.hh"
#include <iostream>
#include <QGLViewer/qglviewer.h>

using namespace std;


inline
unsigned short int MakeBrighter(unsigned short int Lum)
{
  #define SHIFT  20
  
  if (Lum > (255-SHIFT)) return 255;
  return Lum+SHIFT;
}

void Cuboid::DrawGL() const
{
  const Vector3D   &rMid_m = GetPositoin_m();
  const RGB        &rColor = GetColorRGB();
  Vector3D         Size_m = GetSize_m();  
  Size_m /= 2;

#define Vx(Idx,Sign) (Sign Size_m[(Idx)])
#define COORDS3(Vec)  Vec[0],Vec[1],Vec[2]
  
  glPushMatrix();

  glTranslatef(COORDS3(rMid_m));
  glRotatef(GetAng_Roll_deg() , 1.0, 0.0, 0.0 );
  glRotatef(GetAng_Pitch_deg() , 0.0, 1.0, 0.0 );
  glRotatef(GetAng_Yaw_deg() , 0.0, 0.0, 1.0 );  

  glBegin(GL_QUADS);
   glColor3ub(rColor.GetColor_Red(),rColor.GetColor_Green(),rColor.GetColor_Blue());
   glNormal3f(-1,0,0);
   glVertex3f( Vx(0,-), Vx(1,-),  Vx(2,-));  // Boczna x=-1
   glVertex3f( Vx(0,-), Vx(1,+),  Vx(2,-));
   glVertex3f( Vx(0,-), Vx(1,+),  Vx(2,+));
   glVertex3f( Vx(0,-), Vx(1,-),  Vx(2,+));

   
   glNormal3f(0,-1,0);
   glVertex3f( Vx(0,-), Vx(1,-),  Vx(2,-));  // Boczna y=-1
   glVertex3f( Vx(0,+), Vx(1,-),  Vx(2,-));
   glVertex3f( Vx(0,+), Vx(1,-),  Vx(2,+));
   glVertex3f( Vx(0,-), Vx(1,-),  Vx(2,+));

   glNormal3f(0,1,0);
   glVertex3f( Vx(0,-), Vx(1,+),  Vx(2,-));  // Boczna y=+1
   glVertex3f( Vx(0,+), Vx(1,+),  Vx(2,-));
   glVertex3f( Vx(0,+), Vx(1,+),  Vx(2,+));
   glVertex3f( Vx(0,-), Vx(1,+),  Vx(2,+));   


   glNormal3f(0,0,-1);
   glVertex3f( Vx(0,-), Vx(1,-),  Vx(2,-));  // Boczna z=-1
   glVertex3f( Vx(0,+), Vx(1,-),  Vx(2,-));
   glVertex3f( Vx(0,+), Vx(1,+),  Vx(2,-));
   glVertex3f( Vx(0,-), Vx(1,+),  Vx(2,-));

   glNormal3f(0,0,1);
   glVertex3f( Vx(0,-), Vx(1,-),  Vx(2,+));  // Boczna z=+1
   glVertex3f( Vx(0,+), Vx(1,-),  Vx(2,+));
   glVertex3f( Vx(0,+), Vx(1,+),  Vx(2,+));
   glVertex3f( Vx(0,-), Vx(1,+),  Vx(2,+));   

   glColor3ub(MakeBrighter(rColor.GetColor_Red()),
	      MakeBrighter(rColor.GetColor_Green()),
	      MakeBrighter(rColor.GetColor_Blue()));   
   glNormal3f(1,0,0);
   glVertex3f( Vx(0,+), Vx(1,-),  Vx(2,-));  // Boczna x=+1
   glVertex3f( Vx(0,+), Vx(1,+),  Vx(2,-));
   glVertex3f( Vx(0,+), Vx(1,+),  Vx(2,+));
   glVertex3f( Vx(0,+), Vx(1,-),  Vx(2,+));

   glEnd();
   glPopMatrix();
}
