#include "Emir.h"
#include "Hisse.h"
#include "Portfoy.h"
#include "Banka.h"
#include "string.h"

//banka yapisina parametre olarak aldigi dizileri ve degiskenleri atamak icin yazilan fonksiyon
Banka Aktar(Emir emirler[],Hisse hisseler[],Portfoy portfoy[],int len_emirler,int len_hisseler,int len_portfoy)
{
    Banka this;

    this = (Banka)malloc(sizeof(struct BANKA));
    
    this -> emirler = malloc(sizeof(Emir)*len_emirler);
    
    this -> hisseler = malloc(sizeof(Hisse)*len_hisseler);
    
    this -> portfoy = malloc(sizeof(Portfoy)*len_portfoy);

    //dizilerin uzunlugunu tutan degiskenler
    this->len_emirler=len_emirler;

    this->len_hisseler=len_hisseler;

    this->len_portfoy=len_portfoy;

    this->len_karzarar=0;

    this->karzarar=malloc(sizeof(KarZarar)*this->len_karzarar);

    //for donguleri icin olusturulmus degiskenler
    int i;
    int j;
    int k;
    
    //disardan aldigi emirler,hisseler ve portfoyu for dongusuyle teker teker diziye ekler
    for(i=0;i<len_emirler;i++){
        
        this->emirler[i]=emirler[i];  
        
    }
    
    for(j=0;j<len_hisseler;j++){
    
        this->hisseler[j]=hisseler[j];
    }
    
    for(k=0;k<len_portfoy;k++){
    
        this->portfoy[k]=portfoy[k];
    }
    
    return this;
}

//emirler.json dosyasindaki bilgileri portfoye uygulayan fonksiyon
void EmirlerUygula(const Banka this){

    //alim veya satim islemini tutacak degisken
    bool is_it_buy;

    //hissenin ve portfoyun indexini tutacak degiskenler
    int hisse_index;
    int portfoy_index;
    
    //tum emirleri dolasan dongu
    for(int emir_index=0;emir_index<this->len_emirler;emir_index++){

        //alim veya satim islemini belirleyen yer
        is_it_buy=IslemKontrol(this,emir_index);

        //hisse alma islemleri 
        if(is_it_buy){

            //portfoyde o hisseden varsa uzerine ekleme yapar
            if(PortfoyKontrol(this,emir_index)){
                
                //emirin sembolune gore hissenin ve portfoyun dizideki indexini bulup hisseyi portfoyde bulunan hissenin uzerine ekler
                hisse_index=HisseBul(this,emir_index);
                portfoy_index=PortfoyBul(this,emir_index);
                HisseEkle(this,hisse_index,portfoy_index,emir_index);
                
            }

            //portfoyde o hisseden yoksa yeni olusturur
            else{
                
                //emirin sembolune gore hissenin indexini bulup portfoye ekler
                hisse_index=HisseBul(this,emir_index);
                HisseAl(this,hisse_index,emir_index);  
                
            }
                    
        }

        //hisse satma islemleri
        else{

            //satilacak hissenin portfoyde bulunuyorsa islemi gerceklestirir
            if(PortfoyKontrol(this,emir_index)){

                //emirin sembolune gore hisse ve portfoyun indexini bulup o hisseyi satip kar zarar durumunu KarZarar dizisine ekler
                hisse_index=HisseBul(this,emir_index);
                portfoy_index=PortfoyBul(this,emir_index);
                HisseSat(this,hisse_index,portfoy_index,emir_index);

            }     
        }   
    }
}

// parametre olarak hissenin indexini ve emirin indexini alacak ve portfoye ekleyecek.
void HisseAl(const Banka this,int hisse_index,int emir_index){

    /*
    ----------------FONKSIYONUN CALISMA MANTIGI------------------------
    -oncelikle eklenecek hissenin bilgilerini emir ve hisse yapisindan alir
    -daha sonrasinda aldigi bu bilgiler ile yeni bir portfoy yapisi olusturur
    -mevcut portfoy dizisini eski_portfoy degiskenine yedekler
    -portfoy dizisinin uzunlugunu bir arttir
    -banka yapisindaki portfoy dizisini bos olarak yeniden tanimlar
    -for dongusu ile portfoyun hepsini gezer ve dongunun sonuna gelene kadar yedeklenen dizideki elemanlari ekler
    -for dongusunun sonuna gelince ise yeni eklenecek hisseyi ekler
    */

    char* id=this->emirler[emir_index]->id;
    char* sembol=this->emirler[emir_index]->sembol;
    double maliyet=this->hisseler[hisse_index]->fiyat;
    double adet=this->emirler[emir_index]->adet;

    Portfoy yeni_hisse=PortfoyOlustur(id,sembol,maliyet,adet);

    Portfoy* eski_portfoy=this->portfoy;

    this->len_portfoy+=1;

    this -> portfoy = malloc(sizeof(Portfoy)*this->len_portfoy);

    for(int k=0;k<this->len_portfoy;k++){
    
        if(k==this->len_portfoy-1){

            this->portfoy[k]=yeni_hisse;
        }

        else{
            this->portfoy[k]=eski_portfoy[k];
        }
    }
}

//hisse alirken portfoyde o hisseden varsa onun üzerine ekleme yapar
void HisseEkle(const Banka this,int hisse_index,int portfoy_index,int emir_index){

    //hisse adeti eklemede ve maliyetin yeniden hesaplanmasi icin kullanilacak degiskenler
    double eski_adet=this->portfoy[portfoy_index]->adet;
    double eklenecek_adet=this->emirler[emir_index]->adet;
    double eski_maliyet=this->portfoy[portfoy_index]->maliyet;
    double guncel_fiyat=this->hisseler[hisse_index]->fiyat;
    
    //hissenin maliyeti yeniden hesaplandı
    this->portfoy[portfoy_index]->maliyet=((eski_adet*eski_maliyet)+(eklenecek_adet*guncel_fiyat))/(eski_adet+eklenecek_adet);

    //hisse adeti eklendi
    this->portfoy[portfoy_index]->adet+=eklenecek_adet;

}

// parametre olarak satilacak hissenin portfoydeki,emirler ve hisseler de ki indexini alacak ve kar zarar kismina ekleyip portfoyden dusecek fonksiyon.
void HisseSat(const Banka this,int hisse_index,int portfoy_index,int emir_index){
    KarZarar karzarar;
    char* sembol=this->emirler[emir_index]->sembol;
    double tutar;
    bool is_it_kar=NULL;

    double satilacak_adet=this->emirler[emir_index]->adet;
    double mevcut_adet=this->portfoy[portfoy_index]->adet;
    double fiyat=this->hisseler[hisse_index]->fiyat;
    double maliyet=this->portfoy[portfoy_index]->maliyet;

    //satilacak adet mevcut adetten fazla ise portfoyde bulunun kadari satilir ve o hisse portfoyden cikarilir
    if(satilacak_adet>=mevcut_adet){
        //kar
        if(fiyat>maliyet){

            is_it_kar=true;

            tutar=(fiyat-maliyet)*satilacak_adet;

        }
        //kar zarar yok
        else if(fiyat==maliyet){

            tutar=0;
        }
        //zarar
        else{

            is_it_kar=false;

            tutar=(maliyet-fiyat)*satilacak_adet;

        }

        //satilan hissenin portfoyden kaldirilmasi islemi
        //silinecek hisseden sonraki yapilarin dizide bir one alinarak islem yapildi
        for(int i=portfoy_index;i<this->len_portfoy-1;i++){

            this->portfoy[i]=this->portfoy[i+1];

        }

        //portfoy dizisinin uzunlugu bir azaltilir
        this->len_portfoy-=1;

    }

    //satilacak adet mevcut adetten az ise belirtilen adet kadar portfoyden dusulur
    else{

        if(fiyat>maliyet){

            is_it_kar=true;

            tutar=(fiyat-maliyet)*satilacak_adet;
            
        }
        //kar zarar yok
        else if(fiyat==maliyet){

            tutar=0;

        }
        //zarar
        else{

            is_it_kar=false;

            tutar=(maliyet-tutar)*satilacak_adet;

        }

        this->portfoy[portfoy_index]->adet-=satilacak_adet;

    }
    
    //satilan hissenin karzarar dizisine eklenmesi
    KarZarar* karzarar_multi=this->karzarar;

    karzarar=Ekle(sembol,tutar,is_it_kar);

    this->len_karzarar+=1;

    this->karzarar=malloc(sizeof(KarZarar)*this->len_karzarar);

    for(int a=0;a<this->len_karzarar;a++){

        if(a==this->len_karzarar-1){
            this->karzarar[a]=karzarar;
        }
        else{
            this->karzarar[a]=karzarar_multi[a];
        }
    }
}

//parametre olarak emir'in indexini alir ve alim islemi ise true satim islemi ise false dondurur
bool IslemKontrol(const Banka this,int emir_index){

    //emir yapisindaki islem degeri ALIS'a esitse true degilse false dondurur
    char* islem=this->emirler[emir_index]->islem;
    
    if(strcmp(islem,"ALIS") == 0){
        
        return true;
    }

    else{
        
        return false;
    }

}

//parametre olarak emirin indexini alir ve portfoyde o hisse varsa true yoksa false dondurur
bool PortfoyKontrol(const Banka this,int emir_index){

    /*
    for dongusu ile tum portfoyu gezer ve parametre olarak verilen hisse varsa check degiskenini true yapar
    */
    bool check=false;

    for(int i=0;i<this->len_portfoy;i++){

        if(strcmp(this->emirler[emir_index]->sembol,this->portfoy[i]->sembol)==0){
            
            check= true;

            break;
        }
     
    } 
    return check;
}

//parametre olarak emirin indexini alır ve emrin uygulanacağı hissenin indexini döndürür.
int HisseBul(const Banka this,int emir_index){

    /*
    parametre olarak gonderilen hissenin sembolunu
    hisseler dizisindeki tum sembollerle karsilastirir ve hangisi ile 
    eslesirse onun indexini dondurur
    */

    int hisse_index=0;

    for(int i=0;i<this->len_hisseler;i++){

        if(strcmp(this->emirler[emir_index]->sembol,this->hisseler[i]->sembol)==0){

            hisse_index=i;

            break;
        }

    }
    
    return hisse_index;
}

//parametre olarak emirin indexini alır ve emrin uygulanacağı portfoyun indexini dondurur
int PortfoyBul(const Banka this,int emir_index){
    
    /*
    parametre olarak gonderilen hissenin sembolunu
    portfoy dizisindeki tum sembollerle karsilastirir ve hangisi ile 
    eslesirse onun indexini dondurur
    */
    int portfoy_index;

    for(int i=0;i<this->len_portfoy;i++){

        if(strcmp(this->portfoy[i]->sembol,this->emirler[emir_index]->sembol)==0){

            portfoy_index=i;

            break;
        }
    }

    return portfoy_index;
}

//gerekli bilgileri ekrana yazdiran fonksiyon
void Yazdir(const Banka this){

    double total=0;
    char* karZarar;

    printf("\nSatışlar Kar/Zarar:\n");

    for(int i=0;i<this->len_karzarar;i++){

        if(this->karzarar[i]->tutar==0){

            karZarar="Kar veya zarar yok";

        }

        else if(this->karzarar[i]->is_it_kar==false){

            karZarar="Zarar";

        }

        else{

            karZarar="Kar";

        }

        printf("%s : %.2f  %s\n",this->karzarar[i]->sembol,this->karzarar[i]->tutar,karZarar);
        
        if(this->karzarar[i]->is_it_kar){

            total+=this->karzarar[i]->tutar;

        }

        else{

            total-=this->karzarar[i]->tutar;

        }
    
    }

    printf("Toplam Kar/Zarar: %s %.2f TL\n\n",total>=0 ? "+":"-",total);

    printf("Güncel Portföy:\n");

    for(int j=0;j<this->len_portfoy;j++){

        printf("Hisse: %s\nAdet: %.1f\nMaliyet : %.2f TL\n",this->portfoy[j]->sembol,this->portfoy[j]->adet,this->portfoy[j]->maliyet);

        printf("------------------------------\n");

    }

}