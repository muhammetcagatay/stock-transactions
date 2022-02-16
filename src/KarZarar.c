#include "KarZarar.h"
#include "Hisse.h"
#include "stdbool.h"

//parametre olarak aldigi degiskenleri KarZarar yapisina aktarir
KarZarar Ekle(char* sembol,double tutar,bool is_it_kar){
    KarZarar this;
    this=(KarZarar)malloc(sizeof(struct KARZARAR));
    this->sembol=sembol;
    this->tutar=tutar;
    this->is_it_kar=is_it_kar;

    return this;
}