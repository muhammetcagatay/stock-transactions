#include "Hisse.h"

//parametre olarak aldigi degiskenleri hisse yapisina aktarir
Hisse HisseOlustur(char* id,char* sembol,char* ad,double fiyat){
    Hisse this;
    this=(Hisse)malloc(sizeof(struct HISSE));
    this->id=id;
    this->sembol=sembol;
    this->ad=ad;
    this->fiyat=fiyat;
    return this;
}