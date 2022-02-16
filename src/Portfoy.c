#include "Portfoy.h"
#include "Hisse.h"

//parametre olarak aldigi degiskenleri portfoy yapisina aktarir
Portfoy PortfoyOlustur(char* id,char* sembol,double maliyet,double adet){
    Portfoy this;
    this=(Portfoy)malloc(sizeof(struct PORTFOY));
    this->id=id;
    this->sembol=sembol;
    this->maliyet=maliyet;
    this->adet=adet;
    return this;
}