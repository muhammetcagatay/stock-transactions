#include "Emir.h"
#include "cJSON.h"
#include "string.h"

//parametre olarak aldigi degiskenleri emir yapisina aktarir
Emir EmirOlustur(char * id,char * sembol,char * islem,double adet)
{
    Emir this;
    this = (Emir)malloc(sizeof(struct EMIR));
    this -> id = id;
    this -> sembol = sembol;
    this -> islem = islem;
    this -> adet = adet;
    return this;
}
