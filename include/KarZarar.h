#ifndef KARZARAR_H
#define KARZARAR_H

#include "stdio.h"
#include "stdlib.h"
#include "Hisse.h"
#include "stdbool.h"

//hangi hisseden ne kadar kar veya zarar yaptigi,kar mi zarar mi yaptigi bilgilerini tutan yapi
struct KARZARAR
{

    char* sembol;
    double tutar;
    bool is_it_kar;

};

typedef struct KARZARAR* KarZarar;

//parametre olarak aldigi degiskenleri KarZarar yapisina aktarir
KarZarar Ekle(char* sembol,double,bool);


#endif