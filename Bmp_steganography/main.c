/*Samet Elmalı
Bu kodun yazlması esnasında chatgpt https://chat.openai.com/ den yardım
alımıştır*/

#include "lab4bmp.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Image *imread(char *fname)
{
    Image *im;
    FILE *f = fopen(fname, "rb");
    if (f == NULL)
    {
        perror("the file not found!");
        return NULL;
    }

    /*dosyadan değişkenleri alma*/
    uint32_t offset2, hsize, width2, height2;
    uint16_t nplanes2, nbits2;
    fseek(f, 10, SEEK_CUR);
    fread(&offset2, 4, 1, f);
    fread(&hsize, 4, 1, f);
    fread(&width2, 4, 1, f);
    fread(&height2, 4, 1, f);
    fread(&nplanes2, 2, 1, f);
    fread(&nbits2, 2, 1, f);

    im = (Image *)malloc(height2 * width2 * sizeof(Pixel));
    /*im yapısı içerisindeki elemanları dosyadan alınan değişkenlerle doldurma
     * doldurma*/

    im->offset = offset2;
    im->headersize = hsize;
    im->width = width2;
    im->height = height2;
    im->nplanes = nplanes2;
    im->nbits = nbits2;
    rewind(f);
    fseek(f, offset2, SEEK_CUR);

    /*bmp dosyasından pixelleri okuma*/
    /*bmp dosyadaki pixel formatından dolayı sol altan okuma yapılır*/
    for (int i = (im->height) - 1; i >= 0; i--)
    {

        for (int j = 0; j < im->width; j++)
        {

            fread(&(im->pixels[i * im->width + j]), 4, 1, f);
        }
    }
    fclose(f);
    return im;
}

int imclose(Image *im)
{
    free(im);
    return 0;
}

int hideinpixel(Pixel *p, unsigned char c)
{
    /*c nin en anlımlı 2 bitini b değerinin en anlmasız kısmına saklama*/
    p->b = (p->b & 0xFC) | ((c >> 6) & 0x03);

    /*c nın 3 ve 4 . anlamlı bitlerini g(yeşil) en anlamsız kısmına saklama*/
    p->g = (p->g & 0xFC) | ((c >> 4) & 0x03);

    /*c nın 5 ve 6 . anlamlı bitlerini r(kırmızı) en anlamsız kısmına saklama*/
    p->r = (p->r & 0xFC) | ((c >> 2) & 0x03);

    /*c nın 7 ve 8 . anlamlı bitlerini a(alfa) en anlamsız kısmına saklama*/
    p->a = (p->a & 0xFC) | (c & 0x03);

    return 0;
}

/*hideinpixel fonksiyonunu kullanarak msg stringini foroğrafa gizler*/
int hidemsg(Image *im, unsigned char *msg)
{
    int maxlength = strlen((char *)msg);
    int max_length = im->height * im->width;
    for (int i = 0; i < max_length && i < maxlength; i++)
    {
        hideinpixel(&(im->pixels[i]), msg[i]);
    }

    return 0;
}

/* |= operatörü her bit için OR işlemi yapar*/
char readcharinpixel(Pixel *p)
{
    /*sırasıyla b g r a değerlerinin en anlamsız 2 biti alıp sırayla c ye
    yerleştirme*/
    /*hideinpixel fonksiyonun tam tersi işlemleri yapar*/
    char c = 0;
    c |= (p->b & 0x03) << 6;

    c |= (p->g & 0x03) << 4;

    c |= (p->r & 0x03) << 2;

    c |= (p->a & 0x03);
    return c;
}

/*gizlemiş metni karakter karakter okuyup msg stringine yazdırma*/
int readmsg(Image *im, unsigned char msg[], int maxlength)
{
    char c = '\n';
    int i = 0;
    for (; i < im->width * im->height && i < maxlength; i++)
    {
        c = readcharinpixel(&(im->pixels[i]));
        msg[i] = c;
    }
    return i;
}

int main(void)
{
    /* unsigned char msg[] = "hello";
     printf("msg new :%s", msg);
     char fname[] = "cute-animals32bit.bmp";
     Image *im = imread(fname);
     if (im == NULL)
     {
         printf("Failed to open image file.\n");
         return 1;
     }

     int msglength = strlen((char *)msg); // Mesaj uzunluğunu hesapla
     printf("hello uzunluk:%d\n", msglength);
     hidemsg(im, msg);
     readmsg(im, msg, msglength); // Mesajın tamamını oku
     printf("%s", msg);
     imclose(im);*/
    return 0;
}
