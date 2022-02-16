#include "Emir.h"
#include "Hisse.h"
#include "Portfoy.h"
#include "Banka.h"
#include "cJSON.h"
#include "string.h"
#include <windows.h>

//okudugu json dosyasini string'e cevirir
char* JsonToString(char*path);

//verilen stringin satir sayisini hesaplar
int LineCounter(char * content);

int main(){
    SetConsoleOutputCP(65001);

    //json dosyalarinin yollari tanimlanir
    char* emirler_path="doc/json_files/emirler.json";
    char* hisseler_path="doc/json_files/hisseler.json";
    char* portfoy_path="doc/json_files/portfoy.json";

    //cJJSON kutuphanesini kullanmak icin obje olusturulur
    cJSON *cjson_test;

    //stringin neye gore parcalanacagi tanimlanmistir
    char delim[] = "\n";

    //while dongulerinde kullanilmak uzere tanimlanan degiskenler
    int counter=0;
    int index=0;

    //emirler.json dosyasinin okunma,satir sayisi ve parcalama islemleri
    char* content_emirler=JsonToString(emirler_path);
    int lines_emirler=LineCounter(content_emirler);
    char *ptr_emirler = strtok(content_emirler, delim);

    //emirler'in tutulacagi dizi
    Emir emirler[lines_emirler-1];

    //while dongusunde tek tek emir objesi olusturup diziye atamak icin olusturulan obje
    Emir emir_single;
   
    while (ptr_emirler != NULL)
	{  
        //ilk ve son satirlarin alinmamasi icin kontrol islemi
        if(counter!=0 && counter!=lines_emirler){ 
            //json parcalama islemi           
            cjson_test=cJSON_Parse(ptr_emirler);

            //okunan degerlerin objeye aktarilmasi
            emir_single=EmirOlustur(
            cJSON_GetObjectItem(cjson_test, "_id")->valuestring,
            cJSON_GetObjectItem(cjson_test, "Sembol")->valuestring,
            cJSON_GetObjectItem(cjson_test, "Islem")->valuestring,
            cJSON_GetObjectItem(cjson_test, "Adet")->valuedouble
            );

            //olusturulan objenin diziye eklenmesi         
            emirler[index]=emir_single;
            
            index++;
        }
		ptr_emirler = strtok(NULL, delim);
        counter++;
	}

    //hisseler.json dosyasinin okunma,satir sayisi ve parcalama islemleri
    char* content_hisseler=JsonToString(hisseler_path);
    int lines_hisseler=LineCounter(content_hisseler);
    char *ptr_hisseler = strtok(content_hisseler, delim);

    //hisselerin tutulacagi dizi
    Hisse hisseler[lines_hisseler-1];
    Hisse hisse_single;

    counter=0;
    index=0;

    while (ptr_hisseler != NULL)
	{   
        //ilk ve son satirlarin alinmamasi icin kontrol islemi
        if(counter!=0 && counter!=lines_hisseler){ 
            //json parcalama islemi           
            cjson_test=cJSON_Parse(ptr_hisseler);
            
            //olusturulan objeye okunan degerlerin atanmasi islemi
            hisse_single=HisseOlustur(
            cJSON_GetObjectItem(cjson_test, "_id")->valuestring,
            cJSON_GetObjectItem(cjson_test, "Sembol")->valuestring,
            cJSON_GetObjectItem(cjson_test, "Ad")->valuestring,
            cJSON_GetObjectItem(cjson_test, "Fiyat")->valuedouble);

            //olusturulan objenin diziye eklenmesi
            hisseler[index]=hisse_single;

            index++;
        }
		ptr_hisseler = strtok(NULL, delim);
        counter++;
	}
    
    //portfoy.json dosyasinin okunma,satir sayisi ve parcalama islemleri
    char* content_portfoy=JsonToString(portfoy_path);
    int lines_portfoy=LineCounter(content_portfoy);
    char *ptr_portfoy = strtok(content_portfoy, delim);

    //portfoylerin tutulacagi dizi ve obje
    Portfoy portfoy[lines_portfoy-1];
    Portfoy portfoy_single;

    counter=0;
    index=0;

    while (ptr_portfoy != NULL)
	{           
        //dosyanin ilk ve son satirinin kontrolu
        if(counter!=0 && counter!=lines_portfoy){
            
            //json parcalama islemi
            cjson_test=cJSON_Parse(ptr_portfoy);

            //jsondan okunan degerlerin objeye aktarilma islemi
            portfoy_single=PortfoyOlustur(
                cJSON_GetObjectItem(cjson_test, "_id")->valuestring,
                cJSON_GetObjectItem(cjson_test, "Sembol")->valuestring,
                cJSON_GetObjectItem(cjson_test, "Maliyet")->valuedouble,
                cJSON_GetObjectItem(cjson_test, "Adet")->valuedouble
            );
            
            //objenin diziye eklenme islemi
            portfoy[index]=portfoy_single;
            
            index++;
        }
		ptr_portfoy = strtok(NULL, delim);
        counter++;
	}
    
    //tum emirlerin,hisselerin ve portfoyun tutulup islemlerin yapilacagi banka objesinin olusturulmasi
    Banka banka1=Aktar(emirler,hisseler,portfoy,lines_emirler-1,lines_hisseler-1,lines_portfoy-1);

    //emirlerin uygulayacak fonksiyon
    EmirlerUygula(banka1);

    //gerekli bilgileri ekrana yazdiran fonksiyon
    Yazdir(banka1);
    
    return 0;
}

//okudugu json dosyasini string'e cevirir
char* JsonToString(char*path){

    FILE *f;//Input file

    long len;//File length
    
    char *content;//document content
    
    f=fopen(path,"rb");

    fseek(f,0,SEEK_END);
    
    len=ftell(f);
    
    fseek(f,0,SEEK_SET);
    
    content=(char*)malloc(len+1);

    fread(content,1,len,f);

    fclose(f);

    return content;

}

//verilen stringin satir sayisini hesaplar
int LineCounter(char * content){

    int lines=0;

    //her \n gordugunde lines degiskenini arttirak satir sayisini hesaplar
    for(int i=0;content[i]!='\0'; i++){
        if(content[i]=='\n'){
            lines++;
        }
    }

    return lines;
}