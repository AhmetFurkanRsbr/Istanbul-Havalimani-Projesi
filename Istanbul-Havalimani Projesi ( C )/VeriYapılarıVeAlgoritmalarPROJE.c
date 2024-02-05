#include <stdio.h>
#include <stdlib.h> //malloc() ve free() kodlarý ile bellek iþlemleri
#include <string.h> //strcpy gibi string özelliklerine eriþim
#include <locale.h> //setlocale kodu ile türkçe karakterlere izin

//1
//Düðüm tanýmlamasý , içinde "kiþi,sonraki,þehir" deðiþkenlerini tutuyor.
struct dugum{                
	char *kisi;
	struct dugum *sonraki;
	char *sehir;
};

struct dugum *ilk=NULL;            //Düðümün ilk i null dur
struct dugum *son=NULL;            //Düðümün son u null dur

//2
/*Onaybekle() metodu çoðu iþlemde iþlem sonrasýnda menu ekranýna baðlanmak için
 kullanýcýnýn bir tuþa basmasýný bekler.*/
int onayBekle(){      
 	printf("Ýþlemlerinize devam etmek için bir tuþa basýnýz.\n");
	getchar();
	getchar();
	
	return 1;
}

//3
/*EkraniTemizle() metodu ,parametre olarak tam sayý tipinde onayDurumunu tutar,
onayDurumu 1 ise onaybekle metodu çalýþtýrýlýr ve bazý durumlar gerçekleþtirilir,
bu metod ekraný temizlemek için kullanýlýr çoðu iþlem bitiminde kullanýlýr.*/
void ekraniTemizle(int onayDurumu){
	if(onayDurumu==1){
		onayBekle();
	}
	system("cls");
}

//4
/*UçuþEkle metodu,uçuþSayisi parametresiyle kullanýlýr uçuþ sayýsýný güncellemek için,
kuyruða kiþi ve kiþinin gideceði þehri ekler
*/
int ucusEkle(int *ucusSayisi){    
char yolcu[50];
char sehir[20];
ekraniTemizle(0);
printf("\n\tSeçiminiz *>>>> 1 ");
printf("\n\n:-: Yolcu ismi: ");
			scanf("%s", yolcu);
			yolcu[0]=toupper(yolcu[0]);
		
			printf(":-: %s yolcusu hangi þehire gitmek istiyor? : ",yolcu);
			scanf("%s", sehir);
			sehir[0]=toupper(sehir[0]);
			
struct dugum *yeniDugum=malloc(sizeof(struct dugum));     //Yeni düðüm için bellekte malloc ile yer açar
yeniDugum->kisi = malloc(strlen(yolcu));
yeniDugum->sehir= malloc(strlen(sehir));
strcpy(yeniDugum->kisi , yolcu);
strcpy(yeniDugum->sehir , sehir);
yeniDugum->sonraki=NULL;


if(ilk==NULL && son==NULL){  //Eðer uçuþ listesi boþ ve ilk bileti alan kiþiyse

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
printf("\n\t*>Yeni uçuþ eklendi: \n");
printf("\n:-: Yolcu ismi: %s ",yolcu); 
printf("\n:-: Rota: Ýstanbul --> %s \n",sehir);
printf("\n*************************************\n\n");
(*ucusSayisi)++;
      return  *ucusSayisi;
}

//5
/*UcuþListesi() metodu, dolayliKullanim parametresi ile kullanýlýr,
uçuþ listesini yani yolcular ve gidecekleri þehirleri ekrana yazdýrýr.*/
void ucusListesi(int dolayliKullanim){
	
	if(dolayliKullanim==0){
       ekraniTemizle(0);
	   printf("\n\tSeçiminiz *>>>> 2 ");
	}
	
	struct dugum *gecici=ilk;
	int donguyeGirildi=0;
	int sayac=1;
	if(donguyeGirildi==0 && gecici==NULL){
		printf("\n**********************************************************\n");
		printf("\n >BOÞ YOLCU LÝSTESÝ< !! LÝSTELENME GERÇEKLEÞTÝRÝLEMEDÝ !!\n");
	    printf("\n**********************************************************\n\n");
	}
	else{
		   printf("\n\n*****************  UÇUÞ LÝSTESÝ  *****************\n\n");	
		   
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
/*UcuþSil() metodu ,ucuþSayýsý parametresi ile gelir ve bu sayýyý günceller,
görevi uçuþtan yolcuyu ve gideceði þehri silmektir.*/
int ucusSil(int *ucusSayisi) {
	ekraniTemizle(0);
	printf("\n\tSeçiminiz *>>>> 6 ");
	int sayac=1;
    if (ilk == NULL) {           //Herhangi bir uçuþ yoksa liste boþsa
    	printf("\n*************************************\n");
        printf("\n\t*> YOLCU LÝSTESÝ BOÞTUR\n");
        printf("\n*************************************\n\n");
    } else {                  //Liste boþ deðilse
        int silinecekUcus=0;
        printf("\n\t*> Silmek istediðiniz uçuþ hangisidir? ");
        ucusListesi(1);
        scanf("%d",&silinecekUcus);
        
		while(silinecekUcus<=0){
		printf("\n*************************************\n");	
        printf("\n\t*> !! SEÇÝMÝ YANLIÞ YAPTINIZ !!\n");
        printf("YENÝ SEÇÝM: ");
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
			printf("\nUçuþ bulunmamaktadýr.\n");
            printf("\n*************************************\n\n");
		} else {
            if (onceki == NULL) {          // Ýlk elemaný sileceksek
                ilk = simdiki->sonraki;
             }    
             else if(son == simdiki) {     // Son elemaný siliceksek
				son = onceki;
				son->sonraki=NULL;
            } 
            else {
                onceki->sonraki = simdiki->sonraki;
            }

            printf("\n*************************************\n");
            printf("\n%d . yolcu olan %s kiþisi uçuþ listesinden çýkarýldý.\n",sayac, simdiki->kisi);
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
/*UcuþSayýsýGöster() metodu , ucusSayýsý parametresi ile gelir,
aktif uçuþ sayýsýný göstermek için kullanýlýr.*/
void ucusSayisiGoster(int ucusSayisi){
	ekraniTemizle(0);
	printf("\n\tSeçiminiz *>>>> 5 ");
	printf("\n*************************************\n");
	printf("\n \t *>Aktif uçuþ sayýsý: %d \n",ucusSayisi);
    printf("\n*************************************\n\n");
}

//8
/*YolcuListesi() metodu , dolaylýKullaným paramteresi ile gelir,
sadece yolcu isimlerini ekrana yazdýrmak istendiðinde kullanýlýr.*/
void yolcuListesi(int dolayliKullanim){                     
	ekraniTemizle(0);
	if(dolayliKullanim==0){
		printf("\n\tSeçiminiz *>>>> 3 ");
	}
	
	struct dugum *gecici=ilk;
	
	int sayac=1;
	if(gecici!=NULL){
		printf("\n\n*****************  UÇAKTAKÝ YOLCU LÝSTESÝ  *****************\n\n");
	while(gecici!=NULL){
		
		printf("\t %d> %s\n",sayac, gecici->kisi);
		gecici = gecici->sonraki;
		sayac++;
	}	
	printf("\n*************************************\n\n");		
	
	}
	else{
		printf("\n**********************************************************\n");
		printf("\n >BOÞ YOLCU LÝSTESÝ< !! LÝSTELENME GERÇEKLEÞTÝRÝLEMEDÝ !!\n");
	    printf("\n**********************************************************\n\n"); 
	}	
}

//9
/*ÞehirListesi() metodu , gidilecek þehirler listelenmek istediðinde kullanýlýr.*/
void sehirListesi(){                               
	ekraniTemizle(0);
	printf("\n\tSeçiminiz *>>>> 4 ");
	struct dugum *gecici=ilk;
	
	int sayac=1;
	if(gecici!=NULL){

		printf("\n\n*****************  GÝDÝLECEK ÞEHÝRLERÝN LÝSTESÝ  *****************\n\n");
	while(gecici!=NULL){
		printf("\t %d> Ýstanbul --> %s\n",sayac, gecici->sehir);
		gecici = gecici->sonraki;
		sayac++;
	}
	printf("\n*************************************\n\n");
	}
	else{
		
		printf("\n************************************************************\n");
		printf("\n\n >BOÞ Þehir LÝSTESÝ< !! LÝSTELENME GERÇEKLEÞTÝRÝLEMEDÝ !!\n");
	    printf("\n************************************************************\n\n");
			
	}	
	
}

//10
/*Menu() metodu , havalimaný menüsünü ekrana yazdýrýr.*/
void menu(){
	printf("\n\n*****************  HAVALÝMANI MENÜSÜNE HOÞGELDINIZ  *****************\n\n");
	printf("\t-> Uçuþ eklemek için '1' 'e basýnýz.\n");
	printf("\t-> Uçuþlarý listelemek için '2' 'ye basýnýz.\n");
	printf("\t-> Tüm yolcu isimlerini listelemek için '3' 'e basýnýz.\n");
    printf("\t-> Gidilecek tüm þehirleri listelemek için '4' 'e basýnýz.\n");
	printf("\t-> Þu andaki toplam uçuþ sayýsýný görmek için '5' 'ye basýnýz.\n");
	printf("\t-> Uçuþ silmek için '6' 'ya basýnýz.\n");
	printf("\t-> Çýkýþ yapmak için '7' 'ye basýnýz.\n");
	printf("\n\n*****************  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  *****************\n\n");
}


//MAÝN
/*Main fonksiyonu kodun çalýþtýrýldýðý fonksiyondur tüm iþlemler burda gerçekleþir.
Ýçinde setlocale kodu ile türkçe karakterlere izin vermiþ oluyoruz.*/
int main(){
    setlocale(LC_ALL, "Turkish");            //Türkçe karakterlere izin vermiþ oluyoruz.
    char secim;            //
    int durum=1;
    int ucusSayisi=0;
    
do{
	menu();
	
    printf("\n\tSeçiminiz *>>>>  ");	
	scanf(" %c",&secim);
	char sehir[30]="";
	
	
	switch(secim){
		
        case '1':  //Uçuþ eklemeyi gerçekleþtirir.			
			ucusEkle(&ucusSayisi);
			ekraniTemizle(1);
			break;
		  
		case '2':         //Uçuþlarý listelemeyi gerçekleþtiri .
			ucusListesi(0);
			ekraniTemizle(1);
			break;
			
		case '3':         //Uçuþtaki yolcu listesini gösterir .
			yolcuListesi(0);
			ekraniTemizle(1);
			break;
			
			case '4':         //Gidilecek þehirlerin listesini gösterir .
			sehirListesi(0);
			ekraniTemizle(1);
			break;
					
		case '5':              //Kaç tane uçuþ olduðunu gösterir.
			ucusSayisiGoster(ucusSayisi);
			ekraniTemizle(1);
			break;
		
	 	case '6':      //Uçuþu silmeyi gerçekleþtirir.
	    	ucusSil(&ucusSayisi);
			ekraniTemizle(1);
			break;
			  	
		case '7':      //Programý sonlandýrýr.
            ekraniTemizle(0);
			sleep(1);
            printf("\n\n\n\n\n\t\t***********************/********************/*************************\n");
			sleep(1,5);
			printf("\n\t\t.../.../../.../.../../  Program kapatýlýyor  .../.../../.../.../../\n");
			sleep(1,8);
			printf("\n\t\t***********************/********************/************************\n\n");
			durum=0;
			break;				

	    default:      //Geçersiz seçim yapýldýðý için doðru seçim yapmaya zorluyor.
            ekraniTemizle(0);
	    	printf("!!!Lütfen Geçerli Bir seçim Yapýnýz!!!\n");
	        break; 
	}
}while(durum==1);
	
	return 0;
}
