#ifndef EMIR_H
#define  EMIR_H

#include "stdio.h"
#include "stdlib.h"

//emir yapisina ait degiskenler
struct EMIR
{
    char * id;
    char * sembol;
    char * islem;
    double adet;
    
};

typedef struct EMIR * Emir;

//parametre olarak aldigi degiskenleri emir yapisina aktarir
Emir EmirOlustur(char * id,char * sembol,char * islem,double);





#endif
