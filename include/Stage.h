#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>



#ifndef STAGE_H
#define STAGE_H


class Stage
{
    public:
        Stage();
        ~Stage();
        float Norma(float [], float []);
        void ImprimeMallaPiramide(int);
        void ImprimePiramide();
        void RotacionPiramide(char , float, float, float);
        void RotacionPiramide(float , float , float);
        void ShowStage();


    private:
};

#endif // STAGE_H
