/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   odev8.c
 * Author:  Anıl GÜRSES
 *
 * Created on 28 Aralık 2017 Perşembe, 12:11
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 256

typedef struct musterinfo{
    int musteri_No;
    char musteri_isim[max];
    char musteri_soyadi[max];
    int toplam_tutar;
    int dogum_yili;
} MusteriInfo;

void menu();
void musteriEkle(FILE *dosya1, MusteriInfo musteri);
void musteriSil(FILE *dosya1, FILE *temp, MusteriInfo musteri, MusteriInfo musteri2);
void musteriyiGuncelle(FILE *dosya1, MusteriInfo musteri, MusteriInfo musteri2);
void musteriAra(FILE *dosya1, MusteriInfo musteri2);


int main() {

    int secim;
    FILE *dosya, *dosyakopya;
    MusteriInfo temp, temp2;
    dosya = fopen("musteriler.csv", "a+");
    dosyakopya = fopen("musterilerkopya.csv", "w+");
    
    printf("\t------------------------------------\n\tMusteri kayit programina hosgeldiniz.\n\t------------------------------------\n");
    menu();
    scanf("%d", &secim);
    
    while(secim != 5){
        switch (secim){
            case 1:
                 musteriEkle(dosya,temp);
                 printf("Isleminiz basariyla gerceklestirildi.Yeni islem seciniz\n");
                 menu();
                 scanf("%d", &secim);
                 break;
            case 2:
                musteriSil(dosya, dosyakopya, temp, temp2);
                printf("Isleminiz basariyla gerceklestirildi.Yeni islem seciniz\n");
                menu();
                scanf("%d", &secim);
                break;
            case 3:
                musteriyiGuncelle(dosya, temp, temp2);
                printf("Isleminiz basariyla gerceklestirildi.Yeni islem seciniz\n");
                menu();
                scanf("%d", &secim);
                break;
            case 4:
                musteriAra(dosya, temp);
                printf("Isleminiz basariyla gerceklestirildi.Yeni islem seciniz\n");
                menu();
                scanf("%d", &secim);
                break;
            default:
                printf("Lutfen gecerli bir secim yapiniz\n");
                menu();
                scanf("%d", &secim);
                break;
        }
    }
    fclose(dosya);
    fclose(dosyakopya);
    remove("musterilerkopya.csv");
    return 0;
}

void menu(){
    printf("\t\t--Menu--\n1-Yeni Musteri Ekle\n2-Musteri sil\n3-Musteriyi guncelle\n4-Musteri ara\n5-Kaydet\n");
    printf("Seciminiz");
}

void musteriEkle(FILE *dosya1, MusteriInfo musteri){
    printf("Musteri No:");
    scanf("%d", &musteri.musteri_No);
    printf("Musteri Adi:");
    scanf("%s", musteri.musteri_isim);
    printf("Musteri Soyadi:");
    scanf("%s", musteri.musteri_soyadi);
    printf("Alisveris Tutari:");
    scanf("%d", &musteri.toplam_tutar);
    printf("Dogum Yili:");
    scanf("%d", &musteri.dogum_yili);
    fprintf(dosya1, "\n%d;%s;%s;%d;%d;", musteri.musteri_No, musteri.musteri_isim, musteri.musteri_soyadi, musteri.toplam_tutar, musteri.dogum_yili);
    
    fclose(dosya1);
    
    dosya1 = fopen("musteriler.csv", "a+");
}

void musteriSil(FILE *dosya1, FILE *temp, MusteriInfo musteri, MusteriInfo musteri2){
    printf("Silmek istediginiz musterinin bilgilerini giriniz:\n");
    printf("Isim:");scanf("%s", musteri.musteri_isim);
    printf("Soyad:");scanf("%s", musteri.musteri_soyadi);
    printf("Dogum Yili:");scanf("%d", &musteri.dogum_yili);
    printf("Isleminiz gerceklesiyor...\n");
    
    while(!feof(dosya1)){
        fscanf(dosya1, "%d;%s;%s;%d;%d;", &musteri2.musteri_No, musteri2.musteri_isim, musteri2.musteri_soyadi, &musteri2.toplam_tutar, &musteri2.dogum_yili);
        if(feof(dosya1))
            continue;
        if((musteri.dogum_yili == musteri2.dogum_yili) && (musteri.musteri_isim == musteri2.musteri_isim) && (musteri.musteri_soyadi == musteri2.musteri_soyadi))
            continue;
        fprintf(temp, "\n%d;%s;%s;%d;%d;", musteri2.musteri_No, musteri2.musteri_isim, musteri2.musteri_soyadi, musteri2.toplam_tutar, musteri2.dogum_yili);
    }
    fclose(dosya1);
    fclose(temp);
    
    remove("musteriler.csv");
    rename("musterilerkopya.csv", "musteriler.csv");
    
    dosya1 = fopen("musteriler.csv", "a+");
    temp = fopen("musterilerkopya.csv", "w+");
}

void musteriyiGuncelle(FILE *dosya1, MusteriInfo musteri,MusteriInfo musteri2){
    printf("Guncellemek istediginiz musterinin bilgilerini giriniz:\n");
    printf("Isim:");scanf("%s", musteri.musteri_isim);
    printf("Soyad:");scanf("%s", musteri.musteri_soyadi);
    printf("Isleminiz gerceklesiyor...\n");
    
    while(!feof(dosya1)){
        fscanf(dosya1, "%d;%s;%s;%d;%d;", &musteri2.musteri_No, musteri2.musteri_isim, musteri2.musteri_soyadi, &musteri2.toplam_tutar, &musteri2.dogum_yili);
        if(feof(dosya1))
            continue;
        if((musteri.musteri_isim != musteri2.musteri_isim) && (musteri.musteri_soyadi != musteri2.musteri_soyadi))
            continue;
        fprintf(dosya1, "%d;%s;%s;%d;%d;", musteri2.musteri_No, musteri2.musteri_isim, musteri2.musteri_soyadi, musteri2.toplam_tutar, musteri2.dogum_yili);
    }
    
    fclose(dosya1);
    dosya1 = fopen("musteriler.csv", "a+");
}

void musteriAra(FILE *dosya1, MusteriInfo musteri2){
    char arama[10];
    printf("Aramak istediginiz musteriye ait herhangi bir kelime giriniz:\n");
    printf("Kelime:");scanf("%s", arama);
    printf("Isleminiz gerceklesiyor...\n");
    while(!feof(dosya1)){
        fscanf(dosya1, "%d;%s;%s;%d;%d;", &musteri2.musteri_No, musteri2.musteri_isim, musteri2.musteri_soyadi, &musteri2.toplam_tutar, &musteri2.dogum_yili);
        if(feof(dosya1))
            continue;
        if((strstr(musteri2.musteri_isim, arama) == NULL) || (strstr(musteri2.musteri_soyadi, arama) == NULL))
            continue;
        printf("Bulunan kullanıcı:\n");
        printf("%d %s %s %d %d\n", musteri2.musteri_No, musteri2.musteri_isim, musteri2.musteri_soyadi, musteri2.toplam_tutar, musteri2.dogum_yili);
    }
}