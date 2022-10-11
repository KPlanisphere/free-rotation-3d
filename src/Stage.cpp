#include "Stage.h"


extern float P1[3];
extern float P2[3];
extern float points[5][3];
extern float Theta;

Operaciones3D Op3D;

Stage::Stage()
{
    //ctor
}

Stage::~Stage()
{
    //dtor
}



/////////////////////////////////////////////////////////////////////////////
//funciones de objetos
/////////////////////////////////////////////////////////////////////////////
float Stage::Norma(float p1[3], float p2[3])
{
      float n=0;
      int i;
      for(i=0;i<3;i++)
        n += pow(p2[i]-p1[i],2);
      return(sqrt(n));
}

void Stage::ImprimeMallaPiramide(int k)
{
     int i,j;
     float U[3],d,norma;
     for(i=0;i<3;i++)
     {
        norma = Norma(points[i],points[i+1]);
        d = norma/(float)k;
        U[0] = (points[i+1][0]-points[i][0])/norma;
        U[1] = (points[i+1][1]-points[i][1])/norma;
        U[2] = (points[i+1][2]-points[i][2])/norma;
        for(j = 1; j < k; j++)
        {
           glBegin(GL_LINES);
             glVertex3f(points[4][0],points[4][1],points[4][2]);
             glVertex3f(points[i][0]+U[0]*d*j,points[i][1]+U[1]*d*j,points[i][2]+U[2]*d*j);
           glEnd();
        }
     }
     norma = Norma(points[i],points[0]);
     d = norma /(float)k;
     U[0] = (points[0][0]-points[i][0])/norma;
     U[1] = (points[0][1]-points[i][1])/norma;
     U[2] = (points[0][2]-points[i][2])/norma;
     for(j = 1; j < k; j++)
        {
           glBegin(GL_LINES);
             glVertex3f(points[4][0],points[4][1],points[4][2]);
             glVertex3f(points[i][0]+U[0]*d*j,points[i][1]+U[1]*d*j,points[i][2]+U[2]*d*j);
           glEnd();
        }

}

void Stage::ImprimePiramide()
{   int i;
    glColor3f(0.8,0.56,1);
    glBegin(GL_LINE_LOOP);
      for(i=0;i<4;i++)
        glVertex3f(points[i][0],points[i][1],points[i][2]);
    glEnd();
    glBegin(GL_LINES);
      for(i=0;i<4;i++){
        glVertex3f(points[4][0],points[4][1],points[4][2]);
        glVertex3f(points[i][0],points[i][1],points[i][2]);
        }
    glEnd();
    ImprimeMallaPiramide(20);
    glColor3f(1,1,1);
 }


//Rotacion paralela
//rota a la piramide theta grados, donde el eje de rotacion se encuentra
//a una distancia distA-distB del eje seleccionado (ejeXYZ)
void Stage::RotacionPiramide(char ejeXYZ, float theta, float distA, float distB)
{
     //se prepara la matriz de operaciones A: T^(-1)R(T)
     Op3D.RotacionParalela(ejeXYZ,theta,distA,distB);
     //se aplica A a cada punto de la piramide
     Op3D.MatObject(Op3D.A,5,points);
}

//Rotacion libre
void Stage::RotacionPiramide(float theta, float p1[3], float p2[3])
{
     //se imprime el eje de rotacion
     glColor3f(1.0,1.0,1.0);
     glBegin(GL_LINES);
       glVertex3f(p1[0],p1[1],p1[2]);
       glVertex3f(p2[0],p2[1],p2[2]);
     glEnd();
    //Se prepara la matriz de operaciones A
    Op3D.RotacionLibre(theta,p1,p2);
    //se aplica A a cada punto de la piramide
    Op3D.MatObject(Op3D.A,5,points);
}


void Stage::ShowStage(){
    RotacionPiramide(Theta,P1,P2);
    ImprimePiramide();



}
