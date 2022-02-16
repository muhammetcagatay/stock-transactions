#ifndef BANKA_H
#define BANKA_H

#include "stdio.h"
#include "stdlib.h"
#include "Emir.h"
#include "Hisse.h"
#include "Portfoy.h"
#include "stdbool.h"
#include "KarZarar.h"

//banka yapisina ait degiskenler
struct BANKA
{
    Emir *emirler;
    Hisse  *hisseler;
    Portfoy *portfoy;
    KarZarar * karzarar;
    int len_emirler;
    int len_hisseler;
    int len_portfoy;
    int len_karzarar;
};

typedef struct BANKA* Banka;

//banka yapisina parametre olarak aldigi dizileri ve degiskenleri atamak icin yazilan fonksiyon
Banka Aktar(Emir emirler[],Hisse hisseler[],Portfoy portfoy[],int,int,int);

void EmirlerUygula(const Banka);//emirler.json dosyasindaki bilgileri portfoye uygulayan fonksiyon
void HisseAl(const Banka,int,int); // parametre olarak hissenin indexini ve emirin indexini alacak ve portfoye ekleyecek.
void HisseEkle(const Banka,int,int,int);//hisse alirken portfoyde o hisseden varsa onun üzerine ekleme yapar
void HisseSat(const Banka,int,int,int); // parametre olarak satilacak hissenin portfoydeki,emirler ve hisseler de ki indexini alacak ve kar zarar kismina ekleyip portfoyden dusecek.
bool IslemKontrol(const Banka,int);//parametre olarak emir'in indexini alir ve alim islemi ise true satim islemi ise false dondurur
bool PortfoyKontrol(const Banka,int) ;//parametre olarak emirin indexini alir ve portfoyde o hisse varsa true yoksa false dondurur
int HisseBul(const Banka,int);//parametre olarak emirin indexini alır ve emrin uygulanacağı hissenin indexini döndürür.
int PortfoyBul(const Banka,int);//parametre olarak emirin indexini alır ve emrin uygulanacağı portfoyun indexini dondurur
void Yazdir(const Banka); //gerekli bilgileri ekrana yazdirir

#endif