#include <stdio.h>
#include <stdlib.h> //malloc() ve free() kodlar� ile bellek i�lemleri
#include <string.h> //strcpy gibi string �zelliklerine eri�im
#include <locale.h> //setlocale kodu ile t�rk�e karakterlere izin

//1
//D���m tan�mlamas� , i�inde "ki�i,sonraki,�ehir" de�i�kenlerini tutuyor.
struct dugum{                
	char *kisi;
	struct dugum *sonraki;
	char *sehir;
};

struct dugum *ilk=NULL;            //D���m�n ilk i null dur
struct dugum *son=NULL;            //D���m�n son u null dur

//2
/*Onaybekle() metodu �o�u i�lemde i�lem sonras�nda menu ekran�na ba�lanmak i�in
 kullan�c�n�n bir tu�a basmas�n� bekler.*/
int onayBekle(){      
 	printf("��lemlerinize devam etmek i�in bir tu�a bas�n�z.\n");
	getchar();
	getchar();
	
	return 1;
}

//3
/*EkraniTemizle() metodu ,parametre olarak tam say� tipinde onayDurumunu tutar,
onayDurumu 1 ise onaybekle metodu �al��t�r�l�r ve baz� durumlar ger�ekle�tirilir,
bu metod ekran� temizlemek i�in kullan�l�r �o�u i�lem bitiminde kullan�l�r.*/
void ekraniTemizle(int onayDurumu){
	if(onayDurumu==1){
		onayBekle();
	}
	system("cls");
}

//4
/*U�u�Ekle metodu,u�u�Sayisi parametresiyle kullan�l�r u�u� say�s�n� g�ncellemek i�in,
kuyru�a ki�i ve ki�inin gidece�i �ehri ekler
*/
int ucusEkle(int *ucusSayisi){    
char yolcu[50];
char sehir[20];
ekraniTemizle(0);
printf("\n\tSe�iminiz *>>>> 1 ");
printf("\n\n:-: Yolcu ismi: ");
			scanf("%s", yolcu);
			yolcu[0]=toupper(yolcu[0]);
		
			printf(":-: %s yolcusu hangi �ehire gitmek istiyor? : ",yolcu);
			scanf("%s", sehir);
			sehir[0]=toupper(sehir[0]);
			
struct dugum *yeniDugum=malloc(sizeof(struct dugum));     //Yeni d���m i�in bellekte malloc ile yer a�ar
yeniDugum->kisi = malloc(strlen(yolcu));
yeniDugum->sehir= malloc(strlen(sehir));
strcpy(yeniDugum->kisi , yolcu);
strcpy(yeniDugum->sehir , sehir);
yeniDugum->sonraki=NULL;


if(ilk==NULL && son==NULL){  //E�er u�u� listesi bo� ve ilk bileti alan ki�iyse

    ilk = yeniDugum;
    son = yeniDugum;
    ilk->sehir = malloc(strlen(sehir));
    strcpy(ilk->sehir, sehir);
}else{
	son->sonraki = yeniDugum;
	son = yeniDugum;
    son->sehir = malloc(strlen(sehir));
    strcpy(son->sehir, sehir);
}	
printf("\n*************************************\n");
printf("\n\t*>Yeni u�u� eklendi: \n");
printf("\n:-: Yolcu ismi: %s ",yolcu); 
printf("\n:-: Rota: �stanbul --> %s \n",sehir);
printf("\n*************************************\n\n");
(*ucusSayisi)++;
      return  *ucusSayisi;
}

//5
/*Ucu�Listesi() metodu, dolayliKullanim parametresi ile kullan�l�r,
u�u� listesini yani yolcular ve gidecekleri �ehirleri ekrana yazd�r�r.*/
void ucusListesi(int dolayliKullanim){
	
	if(dolayliKullanim==0){
       ekraniTemizle(0);
	   printf("\n\tSe�iminiz *>>>> 2 ");
	}
	
	struct dugum *gecici=ilk;
	int donguyeGirildi=0;
	int sayac=1;
	if(donguyeGirildi==0 && gecici==NULL){
		printf("\n**********************************************************\n");
		printf("\n >BO� YOLCU L�STES�< !! L�STELENME GER�EKLE�T�R�LEMED� !!\n");
	    printf("\n**********************************************************\n\n");
	}
	else{
		   printf("\n\n*****************  U�U� L�STES�  *****************\n\n");	
		   
	while(gecici!=NULL){
		donguyeGirildi=1;
		printf("\t %d> %s --> %s\n",sayac, gecici->kisi, gecici->sehir);
		
		gecici = gecici->sonraki;
		sayac++;
	}	
	printf("\n*************************************\n\n");
	}
	
}

//6
/*Ucu�Sil() metodu ,ucu�Say�s� parametresi ile gelir ve bu say�y� g�nceller,
g�revi u�u�tan yolcuyu ve gidece�i �ehri silmektir.*/
int ucusSil(int *ucusSayisi) {
	ekraniTemizle(0);
	printf("\n\tSe�iminiz *>>>> 6 ");
	int sayac=1;
    if (ilk == NULL) {           //Herhangi bir u�u� yoksa liste bo�sa
    	printf("\n*************************************\n");
        printf("\n\t*> YOLCU L�STES� BO�TUR\n");
        printf("\n*************************************\n\n");
    } else {                  //Liste bo� de�ilse
        int silinecekUcus=0;
        printf("\n\t*> Silmek istedi�iniz u�u� hangisidir? ");
        ucusListesi(1);
        scanf("%d",&silinecekUcus);
        
		while(silinecekUcus<=0){
		printf("\n*************************************\n");	
        printf("\n\t*> !! SE��M� YANLI� YAPTINIZ !!\n");
        printf("YEN� SE��M: ");
	    scanf("%d",&silinecekUcus);
	    printf("\n*************************************\n");
	    system("cls");
		}

        struct dugum *onceki = NULL;
        struct dugum *simdiki = ilk;

        while (simdiki != NULL &&  sayac < silinecekUcus) {
            onceki = simdiki;
            simdiki = simdiki->sonraki;
             sayac++;
        }

        if (simdiki == NULL ) {
            printf("\n*************************************\n");
			printf("\nU�u� bulunmamaktad�r.\n");
            printf("\n*************************************\n\n");
		} else {
            if (onceki == NULL) {          // �lk eleman� sileceksek
                ilk = simdiki->sonraki;
             }    
             else if(son == simdiki) {     // Son eleman� siliceksek
				son = onceki;
				son->sonraki=NULL;
            } 
            else {
                onceki->sonraki = simdiki->sonraki;
            }

            printf("\n*************************************\n");
            printf("\n%d . yolcu olan %s ki�isi u�u� listesinden ��kar�ld�.\n",sayac, simdiki->kisi);
            printf("\n*************************************\n\n");
			free(simdiki->kisi);
            free(simdiki->sehir);
            free(simdiki);
        
             (*ucusSayisi)--;
             if(ilk==NULL){
             	son=NULL;
			 }
        }      
    }
    
   return  *ucusSayisi;
}

//7
/*Ucu�Say�s�G�ster() metodu , ucusSay�s� parametresi ile gelir,
aktif u�u� say�s�n� g�stermek i�in kullan�l�r.*/
void ucusSayisiGoster(int ucusSayisi){
	ekraniTemizle(0);
	printf("\n\tSe�iminiz *>>>> 5 ");
	printf("\n*************************************\n");
	printf("\n \t *>Aktif u�u� say�s�: %d \n",ucusSayisi);
    printf("\n*************************************\n\n");
}

//8
/*YolcuListesi() metodu , dolayl�Kullan�m paramteresi ile gelir,
sadece yolcu isimlerini ekrana yazd�rmak istendi�inde kullan�l�r.*/
void yolcuListesi(int dolayliKullanim){                     
	ekraniTemizle(0);
	if(dolayliKullanim==0){
		printf("\n\tSe�iminiz *>>>> 3 ");
	}
	
	struct dugum *gecici=ilk;
	
	int sayac=1;
	if(gecici!=NULL){
		printf("\n\n*****************  U�AKTAK� YOLCU L�STES�  *****************\n\n");
	while(gecici!=NULL){
		
		printf("\t %d> %s\n",sayac, gecici->kisi);
		gecici = gecici->sonraki;
		sayac++;
	}	
	printf("\n*************************************\n\n");		
	
	}
	else{
		printf("\n**********************************************************\n");
		printf("\n >BO� YOLCU L�STES�< !! L�STELENME GER�EKLE�T�R�LEMED� !!\n");
	    printf("\n**********************************************************\n\n"); 
	}	
}

//9
/*�ehirListesi() metodu , gidilecek �ehirler listelenmek istedi�inde kullan�l�r.*/
void sehirListesi(){                               
	ekraniTemizle(0);
	printf("\n\tSe�iminiz *>>>> 4 ");
	struct dugum *gecici=ilk;
	
	int sayac=1;
	if(gecici!=NULL){

		printf("\n\n*****************  G�D�LECEK �EH�RLER�N L�STES�  *****************\n\n");
	while(gecici!=NULL){
		printf("\t %d> �stanbul --> %s\n",sayac, gecici->sehir);
		gecici = gecici->sonraki;
		sayac++;
	}
	printf("\n*************************************\n\n");
	}
	else{
		
		printf("\n************************************************************\n");
		printf("\n\n >BO� �ehir L�STES�< !! L�STELENME GER�EKLE�T�R�LEMED� !!\n");
	    printf("\n************************************************************\n\n");
			
	}	
	
}

//10
/*Menu() metodu , havaliman� men�s�n� ekrana yazd�r�r.*/
void menu(){
	printf("\n\n*****************  HAVAL�MANI MEN�S�NE HO�GELDINIZ  *****************\n\n");
	printf("\t-> U�u� eklemek i�in '1' 'e bas�n�z.\n");
	printf("\t-> U�u�lar� listelemek i�in '2' 'ye bas�n�z.\n");
	printf("\t-> T�m yolcu isimlerini listelemek i�in '3' 'e bas�n�z.\n");
    printf("\t-> Gidilecek t�m �ehirleri listelemek i�in '4' 'e bas�n�z.\n");
	printf("\t-> �u andaki toplam u�u� say�s�n� g�rmek i�in '5' 'ye bas�n�z.\n");
	printf("\t-> U�u� silmek i�in '6' 'ya bas�n�z.\n");
	printf("\t-> ��k�� yapmak i�in '7' 'ye bas�n�z.\n");
	printf("\n\n*****************  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  *****************\n\n");
}


//MA�N
/*Main fonksiyonu kodun �al��t�r�ld��� fonksiyondur t�m i�lemler burda ger�ekle�ir.
��inde setlocale kodu ile t�rk�e karakterlere izin vermi� oluyoruz.*/
int main(){
    setlocale(LC_ALL, "Turkish");            //T�rk�e karakterlere izin vermi� oluyoruz.
    char secim;            //
    int durum=1;
    int ucusSayisi=0;
    
do{
	menu();
	
    printf("\n\tSe�iminiz *>>>>  ");	
	scanf(" %c",&secim);
	char sehir[30]="";
	
	
	switch(secim){
		
        case '1':  //U�u� eklemeyi ger�ekle�tirir.			
			ucusEkle(&ucusSayisi);
			ekraniTemizle(1);
			break;
		  
		case '2':         //U�u�lar� listelemeyi ger�ekle�tiri .
			ucusListesi(0);
			ekraniTemizle(1);
			break;
			
		case '3':         //U�u�taki yolcu listesini g�sterir .
			yolcuListesi(0);
			ekraniTemizle(1);
			break;
			
			case '4':         //Gidilecek �ehirlerin listesini g�sterir .
			sehirListesi(0);
			ekraniTemizle(1);
			break;
					
		case '5':              //Ka� tane u�u� oldu�unu g�sterir.
			ucusSayisiGoster(ucusSayisi);
			ekraniTemizle(1);
			break;
		
	 	case '6':      //U�u�u silmeyi ger�ekle�tirir.
	    	ucusSil(&ucusSayisi);
			ekraniTemizle(1);
			break;
			  	
		case '7':      //Program� sonland�r�r.
            ekraniTemizle(0);
			sleep(1);
            printf("\n\n\n\n\n\t\t***********************/********************/*************************\n");
			sleep(1,5);
			printf("\n\t\t.../.../../.../.../../  Program kapat�l�yor  .../.../../.../.../../\n");
			sleep(1,8);
			printf("\n\t\t***********************/********************/************************\n\n");
			durum=0;
			break;				

	    default:      //Ge�ersiz se�im yap�ld��� i�in do�ru se�im yapmaya zorluyor.
            ekraniTemizle(0);
	    	printf("!!!L�tfen Ge�erli Bir se�im Yap�n�z!!!\n");
	        break; 
	}
}while(durum==1);
	
	return 0;
}
