#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
typedef struct
{
    char Isim[50];
    int Yas;
    float Maas;
} personelBilgi;

void menuHazirla()
{

    printf("\n*************************************************************\n");
    printf("*                 ----------MENU-----------                 * \n");
    printf("*   1-Kayit Ekle:                                           * \n");
    printf("*   2-Listele:                                              * \n");
    printf("*   3-Duzenle:                                              * \n");
    printf("*   4-Sil:                                                  * \n");
    printf("*   5-Cikis:                                                * \n");
    printf("*                                                           * \n");
    printf("************************************************************* \n");
}

void KayitEkle()
{

    personelBilgi yeniKayit;
    FILE *pd;
    char cevap;
    if((pd=fopen("per.dat","a+"))==NULL)
    {
        printf("Hata!");
        exit(1);
    }
    printf("\n Isim: ");
    scanf("%s", yeniKayit.Isim);
    printf("\n Yas: ");
    scanf("%d", &yeniKayit.Yas);
    printf("\n Maas: ");
    scanf("%f", &yeniKayit.Maas);
    printf("\nYeni kayit icin y yoksa n <y/n>: ");
    scanf(" %c",&cevap);
    if((fwrite(&yeniKayit,sizeof(yeniKayit),1,pd)) !=1)
    {
        printf("Hata!");
        exit(1);
    }
    fclose(pd);
    if(cevap == 'Y' || cevap == 'y')
    {
        KayitEkle();

    }


}


void Listele()
{
    FILE *pd;
    personelBilgi aktifKayit;
    if((pd=fopen("per.dat","r"))==NULL)
    {
        return -1;

    }
    while(!feof(pd))
    {
        if((fread(&aktifKayit,sizeof(aktifKayit),1,pd)) !=1)
        {
            return -1;
        }
        if(strcmp(aktifKayit.Isim,"000") && strcmp(aktifKayit.Isim,""))
        {
            printf("\n Isim:%s\t",aktifKayit.Isim);
            printf(" Yas: %d\t\t",aktifKayit.Yas);
            printf(" Maas:%f\t\t",aktifKayit.Maas);
        }

    }

    fclose(pd);
}
void Duzenle()
{
    personelBilgi kayit;
    FILE *pd;
    char isim[50];
    int bulunan=0;
    char devam;
    int i=0;
    printf("\n Duzenlemek Istediginiz Kisinin Ismini Giriniz:");
    scanf("%s",isim);

    pd=fopen("per.dat","r+");


    while(fread(&kayit,sizeof(kayit),1,pd) == 1)
    {
        if(!strcmp(isim,kayit.Isim))
        {
            bulunan+=1;
            break;
        }
        i++;
    }

    if(bulunan == 0)
    {
        printf("\n Hic kayit bulunamadi!Tekrar arama yapmak ister misiniz?(Y/N):");
        scanf(" %c",&devam);
        if(devam == 'Y' || devam == 'y')
            Duzenle();
        else
        {
            printf("\n Arama Sonlandirildi!\n");
            exit(1);
        }
    }
    else
    {
        printf(" Yeni Isim:");
        scanf("%s",kayit.Isim);
        printf("\n Yeni Yas:");
        scanf("%d",&kayit.Yas);
        printf("\n Yeni Maas:");
        scanf("%f",&kayit.Maas);

        fseek(pd,sizeof(personelBilgi)*i,SEEK_SET);
        fwrite(&kayit,sizeof(personelBilgi),1,pd);
    }

    fclose(pd);

    printf("\n Kayit Guncellendi.\n");

}

void Sil()
{
    char isim[50];
    personelBilgi kayit1;
    FILE *pd;
    if((pd=fopen("per.dat","r+"))==NULL)
    {
        return -1;
    }

    printf("\n Silinecek kayidin ismini giriniz: ");
    scanf("%s",isim);
    int i=0;
    while(fread(&kayit1,sizeof(kayit1),1,pd) ==1)
    {
        if(!strcmp(isim,kayit1.Isim))
        {
            strcpy(kayit1.Isim,"000");
            fseek(pd,sizeof(personelBilgi)*i,SEEK_SET);
            fwrite(&kayit1,sizeof(personelBilgi),1,pd);
            break;
        }
        i++;
    }
    fclose(pd);


}

int main()
{
    int secim;
    system("color 02");

    do
    {
        menuHazirla();
        printf("\n Secimin:");
        scanf("%d",&secim);
        switch (secim)
        {
        case 1:
            KayitEkle();
            break;
        case 2:
            Listele();
            break;
        case 3:
            Duzenle();
            break;
        case 4:
            Sil();
            break;
        case 5:
            printf("\n Cikis yaptiniz.. \n");
            return 0;
            break;
        default:
            printf(" ");
            break;
        }
    }
    while(secim!=5);
    return 0 ;


}
