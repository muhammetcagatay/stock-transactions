#ifndef HISSE_H
#define HISSE_H

#include "stdio.h"
#include "stdlib.h"

//hisse yapisina ait degiskenler
struct HISSE
{
    char *id;
    char *sembol;
    char *ad;
    double fiyat;
};

typedef struct HISSE* Hisse;

//parametre olarak aldigi degiskenleri hisse yapisina aktarir
Hisse HisseOlustur(char* id,char *sembol,char* ad,double);



#endif