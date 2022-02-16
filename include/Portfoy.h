#ifndef PORTFOY_H
#define PORTFOY_H

#include "stdio.h"
#include "stdlib.h"
#include "Hisse.h"

//portfoy yapisina ait degiskenler
struct PORTFOY
{
    char * id;
    char *sembol;
    double maliyet;
    double adet;
};

typedef struct PORTFOY* Portfoy;

//parametre olarak aldigi degiskenleri portfoy yapisina aktarir
Portfoy PortfoyOlustur(char * id,char * sembol,double,double);

#endif