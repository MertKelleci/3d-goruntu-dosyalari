#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#define m 4
#define n 101

struct bilgi
{
    char version[21];
    char alanlar[21];
    long int NSayisi;
    char DType[21];

};

struct Rnksz_Nktlr
{
    float x;
    float y;
    float z;
};

struct Rnkl_Nktlr
{
    float x;
    float y;
    float z;

    int r1;
    int r2;
    int r3;
};

struct flt_tut
{
    float flt;
};

struct int_tut
{
    int nt;
};
struct Rnkl_Bin
{
    float q,w,e;
    int a,b,c;
};
struct Rnksz_Bin
{
    float q,w,e;
};
void bosluk_sil(char bosluk[])
{

    int i,k;

    for(i=0; i<strlen(bosluk); i++)
        if(bosluk[i]==' ')
            for(k=i; k<strlen(bosluk)-1; k++)
                bosluk[k]=bosluk[k+1];

    int len = strlen(bosluk);
    bosluk[len-2] = '\0';

}
void Ister1(char verix_isim[m][n])
{
    FILE *deneme;
    FILE *sonucRnklBin = fopen("OutputRenkliBinary.nkt","ab");
    FILE *sonucRnkszBin = fopen("OutputRenksizBinary.nkt","ab");
    FILE *sonucRnklAscii = fopen("OutputRenkliAscii.nkt","a");
    FILE *sonucRnkszAscii = fopen("OutputRenksizAscii.nkt","a");
    struct dirent *dos;
    char bosluk[101];
    long int stop,bslk_sayisi,i,k,Ncheck;
    int bin_num;
    struct Rnkl_Bin *rnk = (struct Rnkl_Bin*)malloc(sizeof(struct Rnkl_Bin));
    struct Rnksz_Bin *rnksz = (struct Rnksz_Bin*)malloc(sizeof(struct Rnksz_Bin));



    DIR *dr = opendir(".");

    if(dr==NULL)
    {
        printf("Dosya bulunamadi!");
        return(0);
    }

    while((dos = readdir(dr)) != NULL)
    {

        if(strstr(dos->d_name,".nkt")==NULL)
            continue;

        deneme = fopen(dos->d_name,"r");

        fgets(bosluk,100,deneme);

        if(strcmp(bosluk,"# Noktalar dosya format\n") == 0)
        {
            fgets(bosluk,50,deneme);
            fgets(bosluk,50,deneme);


            if(strcmp(bosluk,"ALANLAR x y z r g b\n")==0)
            {
                Ncheck=0;
                fgets(bosluk,50,deneme);
                for(i=0; i<strlen(bosluk); i++)
                    if(bosluk[i]==' ')
                    {
                        stop = i;
                        break;
                    }

                int NSayisi = atoi(bosluk+stop);
                fgets(bosluk,50,deneme);

                bosluk_sil(bosluk);

                if(strstr(bosluk,"ascii")!=NULL)
                {
                    for(i=0; i<NSayisi; i++)
                    {
                        fgets(bosluk,100,deneme);
                        bslk_sayisi=0;

                        for(k=0; bosluk[k]!='\n'; k++)
                        {
                            if(bosluk[k]==' ')
                                bslk_sayisi++;

                        }

                        if(bslk_sayisi!=5)
                        {
                            printf("%s dosyasinin %d. dizininde xyz bilgileri eksiktir!\n",dos->d_name,i+1);
                            fprintf(sonucRnklAscii,"%s dosyasinin %d. dizininde xyz bilgileri eksiktir!\n",dos->d_name,i+1);
                            break;
                        }


                       else if(strstr(bosluk,"0.000000")==NULL || strstr(bosluk,"0")==NULL )
                            Ncheck++;


                    }

                    if(Ncheck==NSayisi)
                        strcpy(verix_isim[0],dos->d_name);

                    else
                    {
                        printf("%s isimli dosyada nokta sayisi gecerli degildir!\n");
                        fprintf(sonucRnklAscii,"%s isimli dosyada nokta sayisi gecerli degildir!\n");
                    }


                }

                else if(strstr(bosluk,"binary")!=NULL)
                {
                    rnk = (struct Rnkl_Bin*)realloc(rnk,NSayisi*sizeof(struct Rnkl_Bin));
                    bin_num=0;


                    for(i=0; i<NSayisi; i++)
                    {
                        fread(&rnk[i].q,sizeof(struct flt_tut),1,deneme);
                        fread(&rnk[i].w,sizeof(struct flt_tut),1,deneme);
                        fread(&rnk[i].e,sizeof(struct flt_tut),1,deneme);
                        fread(&rnk[i].a,sizeof(struct int_tut),1,deneme);
                        fread(&rnk[i].b,sizeof(struct int_tut),1,deneme);
                        fread(&rnk[i].c,sizeof(struct int_tut),1,deneme);


                        if(rnk[i].q == 0 && rnk[i].w == 0 && rnk[i].e == 0 && rnk[i].a == 0 && rnk[i].b == 0 && rnk[i].c == 0)
                        {
                            printf("%s isimli dosyanin rgb bilgileri eksitir!\n");
                            fprintf(sonucRnklBin,"%s isimli dosyanin rgb bilgileri eksitir!\n");
                            break;
                        }

                        else
                            bin_num++;
                    }

                    if(bin_num!=NSayisi)
                    {
                        printf("%s isimli dosyanin nokta sayisi gecersizdir!\n");
                        fprintf(sonucRnklBin,"%s isimli dosyanin nokta sayisi gecersizdir!\n");
                        break;
                    }

                    else
                        strcpy(verix_isim[2],dos->d_name);

                }

            }

            else if(strcmp(bosluk,"ALANLAR x y z\n")==0)
            {

                Ncheck=0;
                fgets(bosluk,50,deneme);
                for(i=0; i<strlen(bosluk); i++)
                    if(bosluk[i]==' ')
                    {
                        stop = i;
                        break;
                    }

                int NSayisi = atoi(bosluk+stop);
                fgets(bosluk,50,deneme);

                bosluk_sil(bosluk);

                if(strstr(bosluk,"ascii")!= NULL)
                {
                    for(i=0; i<NSayisi; i++)
                    {
                        fgets(bosluk,100,deneme);
                        bslk_sayisi=0;

                        for(k=0; bosluk[k]!='\n'; k++)
                        {
                            if(bosluk[k]==' ')
                                bslk_sayisi++;

                        }

                        if(bslk_sayisi!=2)
                        {
                            printf("%s dosyasinin %d. indeksinde xyz verisi eksiktir!\n",dos->d_name,i+1);
                            fprintf(sonucRnkszAscii,"%s dosyasinin %d. indeksinde xyz verisi eksiktir!\n",dos->d_name,i+1);
                            break;
                        }

                        else if(strstr(bosluk,"0.000000")==NULL || strstr(bosluk,"0")==NULL )
                            Ncheck++;
                    }

                    if(Ncheck==NSayisi)
                        strcpy(verix_isim[1],dos->d_name);

                    else
                    {
                        printf("%s isimli dosyada nokta sayisi gecerli degildir!\n");
                        fprintf(sonucRnkszAscii,"%s isimli dosyada nokta sayisi gecerli degildir!\n");
                    }



                }

                else if(strstr(bosluk,"binary")!=NULL)
                {
                    rnksz = (struct Rnksz_Bin*)realloc(rnksz,NSayisi*sizeof(struct Rnksz_Bin));
                    bin_num=0;


                    for(i=0; i<NSayisi; i++)
                    {
                        fread(&rnksz[i].q,sizeof(struct flt_tut),1,deneme);
                        fread(&rnksz[i].w,sizeof(struct flt_tut),1,deneme);
                        fread(&rnksz[i].e,sizeof(struct flt_tut),1,deneme);


                        if(rnksz[i].q == 0 && rnksz[i].w == 0 && rnksz[i].e == 0)
                        {
                            printf("%s isimli dosyanin rgb bilgileri eksitir!\n");
                            fprintf(sonucRnkszBin,"%s isimli dosyanin rgb bilgileri eksitir!\n");
                            break;
                        }

                        else
                            bin_num++;
                    }

                    if(bin_num!=NSayisi)
                    {
                        printf("%s isimli dosyanin nokta sayisi gecersizdir!\n");
                        fprintf(sonucRnkszBin,"%s isimli dosyanin nokta sayisi gecersizdir!\n");
                        break;
                    }

                    else
                        strcpy(verix_isim[3],dos->d_name);
                }

            }


        }

    }

}


void Ister2(struct bilgi veriler,char verix_isim[])
{
    FILE *verix = fopen(verix_isim,"r");
    FILE *sonucRnklBin = fopen("OutputRenkliBinary.nkt","ab");
    FILE *sonucRnkszBin = fopen("OutputRenksizBinary.nkt","ab");
    FILE *sonucRnklAscii = fopen("OutputRenkliAscii.nkt","a");
    FILE *sonucRnkszAscii = fopen("OutputRenksizAscii.nkt","a");

    if(strstr(veriler.alanlar,"xyzrgb")==NULL)
    {
        int i,k;
        float xdis;
        float ydis;
        float zdis;
        float dist_check;


        char atlama[51];
        for(i=0; i<5; i++)
        {
            fgets(atlama,50,verix);
        }

        if(strstr(veriler.DType,"ascii")!=NULL)
        {
            struct Rnksz_Nktlr *p = (struct Rnksz_Nktlr*)malloc(veriler.NSayisi*sizeof(struct Rnksz_Nktlr));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fscanf(verix,"%f",&p[i].x);
                fscanf(verix,"%f",&p[i].y);
                fscanf(verix,"%f",&p[i].z);
            }
            float rdist_uzak,rdist_yakin;
            int i1,k1,i2,k2;

            xdis = pow((p[0].x - p[1].x),2);
            ydis = pow((p[0].y - p[1].y),2);
            zdis = pow((p[0].z - p[1].z),2);
            rdist_uzak = sqrt(xdis+ydis+zdis);
            rdist_yakin = rdist_uzak;

            for(i=0; i<veriler.NSayisi; i++)
                for(k=i+1; k<veriler.NSayisi; k++)
                {
                    xdis = pow((p[k].x - p[i].x),2);
                    ydis = pow((p[k].y - p[i].y),2);
                    zdis = pow((p[k].z - p[i].z),2);
                    dist_check = sqrt(xdis+ydis+zdis);

                    if(dist_check>rdist_uzak)
                    {
                        rdist_uzak = dist_check;

                        i1=i;
                        k1=k;
                    }


                    else if(dist_check<rdist_yakin)
                    {
                        rdist_yakin = dist_check;

                        i2=i;
                        k2=k;

                    }
                }


            printf("\n%s dosyasi\n",verix_isim);
            printf("%f %d %d\n%f %f %f\n%f %f %f\n",rdist_uzak,i1,k1,p[i1].x,p[i1].y,p[i1].z,p[k1].x,p[k1].y,p[k1].z);
            fprintf(sonucRnkszAscii,"%f %d %d\n%f %f %f\n%f %f %f\n",rdist_uzak,i1,k1,p[i1].x,p[i1].y,p[i1].z,p[k1].x,p[k1].y,p[k1].z);

            printf("%f %d %d\n%f %f %f\n%f %f %f\n",rdist_yakin,i2,k2,p[i2].x,p[i2].y,p[i2].z,p[k2].x,p[k2].y,p[k2].z);
            fprintf(sonucRnkszAscii,"%f %d %d\n%f %f %f\n%f %f %f\n",rdist_yakin,i2,k2,p[i2].x,p[i2].y,p[i2].z,p[k2].x,p[k2].y,p[k2].z);
            free(p);
        }

        else if(strstr(veriler.DType,"binary")!=NULL)
        {
            struct Rnksz_Bin *rnksz = (struct Rnksz_Bin*)malloc(veriler.NSayisi*sizeof(struct Rnksz_Bin));

            float rdist_uzak,rdist_yakin;
            int i1,k1,i2,k2;

            for(i=0; i<veriler.NSayisi; i++)
            {
                fread(&rnksz[i].q,sizeof(struct flt_tut),1,verix);
                fread(&rnksz[i].w,sizeof(struct flt_tut),1,verix);
                fread(&rnksz[i].e,sizeof(struct flt_tut),1,verix);

            }

            xdis = pow((rnksz[0].q - rnksz[1].q),2);
            ydis = pow((rnksz[0].w - rnksz[1].w),2);
            zdis = pow((rnksz[0].e - rnksz[1].e),2);
            rdist_uzak = sqrt(xdis+ydis+zdis);
            rdist_yakin = rdist_uzak;


            for(i=0; i<veriler.NSayisi-1; i++)
            {
                for(k=i+1; k<veriler.NSayisi; k++)
                {
                    xdis = pow((rnksz[i].q - rnksz[k].q),2);
                    ydis = pow((rnksz[i].w - rnksz[k].w),2);
                    zdis = pow((rnksz[i].e - rnksz[k].e),2);
                    dist_check = sqrt(xdis+ydis+zdis);

                    if(dist_check>rdist_uzak)
                    {
                        rdist_uzak = dist_check;

                        i1 = i;
                        k1 = k;
                    }

                    else if(dist_check<rdist_yakin)
                    {
                        rdist_yakin = dist_check;

                        i2=i;
                        k2=k;
                    }
                }
            }

            printf("\n%s dosyasi\n",verix_isim);
            printf("%f %d %d\n%f %f %f\n%f %f %f\n",rdist_uzak,i1,k1,rnksz[i1].q,rnksz[i1].w,rnksz[i1].e,rnksz[k1].q,rnksz[k1].w,rnksz[k1].e);
            printf("%f %d %d\n%f %f %f\n%f %f %f\n",rdist_yakin,i2,k2,rnksz[i2].q,rnksz[i2].w,rnksz[i2].e,rnksz[k2].q,rnksz[k2].w,rnksz[k2].e);

            fprintf(sonucRnkszBin,"\n%f %d %d\n",rdist_uzak,i1,k1);
            fwrite(&rnksz[i1].q,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[i1].w,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[i1].e,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[k1].q,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[k1].w,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[k1].e,sizeof(struct flt_tut),1,sonucRnkszBin);

            fprintf(sonucRnkszBin,"\n%f %d %d\n",rdist_yakin,i2,k2);
            fwrite(&rnksz[i2].q,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[i2].w,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[i2].e,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[k2].q,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[k2].w,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&rnksz[k2].e,sizeof(struct flt_tut),1,sonucRnkszBin);

            fclose(sonucRnkszBin);



            free(rnksz);


        }

    }


    else
    {
        int i,k;
        float xdis;
        float ydis;
        float zdis;
        float dist_check;

        char atlama[51];
        for(i=0; i<5; i++)
        {
            fgets(atlama,50,verix);
        }

        if(strstr(veriler.DType,"ascii")!=NULL)
        {

            struct Rnkl_Nktlr *p = (struct Rnkl_Nktlr*)malloc(veriler.NSayisi*sizeof(struct Rnkl_Nktlr));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fscanf(verix,"%f",&p[i].x);
                fscanf(verix,"%f",&p[i].y);
                fscanf(verix,"%f",&p[i].z);
                fscanf(verix,"%d",&p[i].r1);
                fscanf(verix,"%d",&p[i].r2);
                fscanf(verix,"%d",&p[i].r3);
            }


            float rdist_uzak,rdist_yakin;
            int i1,k1,i2,k2;

            xdis = pow((p[0].x - p[1].x),2);
            ydis = pow((p[0].y - p[1].y),2);
            zdis = pow((p[0].z - p[1].z),2);
            rdist_uzak = sqrt(xdis+ydis+zdis);
            rdist_yakin = rdist_uzak;

            for(i=0; i<veriler.NSayisi; i++)
                for(k=i+1; k<veriler.NSayisi; k++)
                {
                    xdis = pow((p[k].x - p[i].x),2);
                    ydis = pow((p[k].y - p[i].y),2);
                    zdis = pow((p[k].z - p[i].z),2);
                    dist_check = sqrt(xdis+ydis+zdis);

                    if(dist_check>rdist_uzak)
                    {
                        rdist_uzak = dist_check;
                        i1=i;
                        k1=k;
                    }

                    else if(dist_check<rdist_yakin)
                    {

                        rdist_yakin = dist_check;
                        i2=i;
                        k2=k;
                    }
                }

            printf("\n%s dosyasi\n",verix_isim);

            printf("%f %d %d\n%f %f %f %d %d %d\n%f %f, %f %d %d %d\n",rdist_uzak,i1,k1,p[i1].x,p[i1].y,p[i1].z,p[i1].r1,p[i1].r2,p[i1].r3,p[k1].x,p[k1].y,p[k1].z,p[k1].r1,p[k1].r2,p[k1].r3);
            fprintf(sonucRnklAscii,"%f %d %d\n%f %f %f %d %d %d\n%f %f %f %d %d %d\n",rdist_uzak,i1,k1,p[i1].x,p[i1].y,p[i1].z,p[i1].r1,p[i1].r2,p[i1].r3,p[k1].x,p[k1].y,p[k1].z,p[k1].r1,p[k1].r2,p[k1].r3);

            printf("%f %d %d\n%f %f, %f %d %d %d\n%f %f %f %d %d %d\n\n",rdist_yakin,i2,k2,p[i2].x,p[i2].y,p[i2].z,p[i2].r1,p[i2].r2,p[i2].r3,p[k2].x,p[k2].y,p[k2].z,p[k2].r1,p[k2].r2,p[k2].r3);
            fprintf(sonucRnklAscii,"%f %d %d\n%f %f %f %d %d %d\n%f %f %f %d %d %d\n\n",rdist_yakin,i2,k2,p[i2].x,p[i2].y,p[i2].z,p[i2].r1,p[i2].r2,p[i2].r3,p[k2].x,p[k2].y,p[k2].z,p[k2].r1,p[k2].r2,p[k2].r3);

            free(p);
        }

        else
        {
            struct Rnkl_Bin *rnkl = (struct Rnkl_Bin*)malloc(veriler.NSayisi*sizeof(struct Rnkl_Bin));


            float rdist_uzak,rdist_yakin;
            int i1,k1,i2,k2;

            for(i=0; i<veriler.NSayisi; i++)
            {
                fread(&rnkl[i].q,sizeof(struct flt_tut),1,verix);
                fread(&rnkl[i].w,sizeof(struct flt_tut),1,verix);
                fread(&rnkl[i].e,sizeof(struct flt_tut),1,verix);

                fread(&rnkl[i].a,sizeof(struct int_tut),1,verix);
                fread(&rnkl[i].b,sizeof(struct int_tut),1,verix);
                fread(&rnkl[i].c,sizeof(struct int_tut),1,verix);

            }


            xdis = pow((rnkl[0].q - rnkl[1].q),2);
            ydis = pow((rnkl[0].w - rnkl[1].w),2);
            zdis = pow((rnkl[0].e - rnkl[1].e),2);
            rdist_uzak = sqrt(xdis+ydis+zdis);
            rdist_yakin = rdist_uzak;


            for(i=0; i<veriler.NSayisi-1; i++)
            {
                for(k=i+1; k<veriler.NSayisi; k++)
                {
                    xdis = pow((rnkl[i].q - rnkl[k].q),2);
                    ydis = pow((rnkl[i].w - rnkl[k].w),2);
                    zdis = pow((rnkl[i].e - rnkl[k].e),2);
                    dist_check = sqrt(xdis+ydis+zdis);

                    if(dist_check>rdist_uzak)
                    {
                        rdist_uzak = dist_check;

                        i1 = i;
                        k1 = k;
                    }

                    else if(dist_check<rdist_yakin)
                    {
                        rdist_yakin = dist_check;

                        i2=i;
                        k2=k;
                    }
                }
            }

            printf("\n%s dosyasi\n",verix_isim);

            printf("%f %d %d\n%f %f %f %d %d %d\n%f %f %f %d %d %d\n",rdist_uzak,i1,k1,rnkl[i1].q,rnkl[i1].w,rnkl[i1].e,rnkl[i1].a,rnkl[i1].b,rnkl[i1].c,rnkl[k1].q,rnkl[k1].w,rnkl[k1].e,rnkl[k1].a,rnkl[k1].b,rnkl[k1].c);
            printf("%f %d %d\n%f %f %f %d %d %d\n%f %f %f %d %d %d\n",rdist_yakin,i2,k2,rnkl[i2].q,rnkl[i2].w,rnkl[i2].e,rnkl[i2].a,rnkl[i2].b,rnkl[i2].c,rnkl[k2].q,rnkl[k2].w,rnkl[k2].e,rnkl[k2].a,rnkl[k2].b,rnkl[k2].c);

            fprintf(sonucRnklBin,"\n%f %d %d\n",rdist_uzak,i1,k1);
            fwrite(&rnkl[i1].q,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[i1].w,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[i1].e,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[i1].a,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[i1].b,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[i1].c,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[k1].q,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[k1].w,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[k1].e,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[k1].a,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[k1].b,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[k1].c,sizeof(struct int_tut),1,sonucRnklBin);

            fprintf(sonucRnklBin,"\n%f %d %d\n",rdist_yakin,i2,k2);
            fwrite(&rnkl[i2].q,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[i2].w,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[i2].e,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[i2].a,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[i2].b,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[i2].c,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[k2].q,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[k2].w,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[k2].e,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&rnkl[k2].a,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[k2].b,sizeof(struct int_tut),1,sonucRnklBin);
            fwrite(&rnkl[k2].c,sizeof(struct int_tut),1,sonucRnklBin);

            fclose(sonucRnklBin);





            free(rnkl);
        }
    }

    fclose(verix);
    fclose(sonucRnklAscii);
    fclose(sonucRnklBin);
    fclose(sonucRnkszAscii);
    fclose(sonucRnkszBin);

}

void Ister3(struct bilgi veriler,char verix_isim[])
{
    FILE *verix = fopen(verix_isim,"r");
    FILE *sonucRnklBin = fopen("OutputRenkliBinary.nkt","ab");
    FILE *sonucRnkszBin = fopen("OutputRenksizBinary.nkt","ab");
    FILE *sonucRnklAscii = fopen("OutputRenkliAscii.nkt","a");
    FILE *sonucRnkszAscii = fopen("OutputRenksizAscii.nkt","a");

    int i,k;
    float xdis;
    float ydis;
    float zdis;
    float dist_check;
    char atlama[51];
    for(i=0; i<5; i++)
    {
        fgets(atlama,50,verix);
    }


    if(strstr(veriler.alanlar,"xyzrgb")==NULL)
    {
        if(strstr(veriler.DType,"ascii")!=NULL)
        {

            struct Rnksz_Nktlr *p = (struct Rnksz_Nktlr*)malloc(veriler.NSayisi*sizeof(struct Rnksz_Nktlr));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fscanf(verix,"%f",&p[i].x);
                fscanf(verix,"%f",&p[i].y);
                fscanf(verix,"%f",&p[i].z);
            }

            float x_yakin = p[0].x;
            float y_yakin = p[0].y;
            float z_yakin = p[0].z;

            float en_uzakx = p[0].x;
            float en_uzaky = p[0].y;
            float en_uzakz = p[0].z;


            for(i=0; i<veriler.NSayisi; i++)
            {
                if(p[i].x>en_uzakx)
                    en_uzakx = p[i].x;

                if(p[i].y>en_uzaky)
                    en_uzaky = p[i].y;

                if(p[i].z>en_uzakz)
                    en_uzakz=p[i].z;

                if(p[i].x<x_yakin)
                    x_yakin = p[i].x;

                if(p[i].y<y_yakin)
                    y_yakin = p[i].y;

                if(p[i].z<z_yakin)
                    z_yakin=p[i].z;


            }
            float dist;

            if((en_uzakx-x_yakin)>(en_uzaky-y_yakin) && (en_uzakx-x_yakin)>(en_uzakz-z_yakin))
                dist = en_uzakx-x_yakin;

            else if((en_uzaky-y_yakin)>(en_uzakx-x_yakin) && (en_uzaky-y_yakin)>(en_uzakz-z_yakin))
                dist = en_uzaky-y_yakin;

             else if((en_uzakz-z_yakin)>(en_uzakx-x_yakin) && (en_uzakz-z_yakin)>(en_uzaky-y_yakin))
                dist = en_uzakz-z_yakin;


            printf("\n%s dosyasi\n",verix_isim);
            printf("%f %f %f\n",x_yakin,y_yakin,z_yakin);
            printf("%f %f %f\n",(x_yakin+dist),y_yakin,z_yakin);
            printf("%f %f %f\n",x_yakin,y_yakin,(z_yakin+dist));
            printf("%f %f %f\n",(x_yakin+dist),y_yakin,(z_yakin+dist));
            printf("%f %f %f\n",x_yakin,(y_yakin+dist),z_yakin);
            printf("%f %f %f\n",(x_yakin+dist),(y_yakin+dist),z_yakin);
            printf("%f %f %f\n",x_yakin,(y_yakin+dist),(z_yakin+dist));
            printf("%f %f %f\n",(x_yakin+dist),(y_yakin+dist),(z_yakin+dist));


            fprintf(sonucRnkszAscii,"%f %f %f\n",x_yakin,y_yakin,z_yakin);
            fprintf(sonucRnkszAscii,"%f %f %f\n",(x_yakin+dist),y_yakin,z_yakin);
            fprintf(sonucRnkszAscii,"%f %f %f\n",x_yakin,y_yakin,(z_yakin+dist));
            fprintf(sonucRnkszAscii,"%f %f %f\n",(x_yakin+dist),y_yakin,(z_yakin+dist));
            fprintf(sonucRnkszAscii,"%f %f %f\n",x_yakin,(y_yakin+dist),z_yakin);
            fprintf(sonucRnkszAscii,"%f %f %f\n",(x_yakin+dist),(y_yakin+dist),z_yakin);
            fprintf(sonucRnkszAscii,"%f %f %f\n",x_yakin,(y_yakin+dist),(z_yakin+dist));
            fprintf(sonucRnkszAscii,"%f %f %f\n",(x_yakin+dist),(y_yakin+dist),(z_yakin+dist));


            free(p);
        }
        else if(strstr(veriler.DType,"binary")!=NULL)
        {
            struct Rnksz_Bin *p = (struct Rnksz_Bin*)malloc(veriler.NSayisi*sizeof(struct Rnksz_Bin));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fread(&p[i].q,sizeof(struct flt_tut),1,verix);
                fread(&p[i].w,sizeof(struct flt_tut),1,verix);
                fread(&p[i].e,sizeof(struct flt_tut),1,verix);
            }

            float x_yakin = p[0].q;
            float y_yakin = p[0].w;
            float z_yakin = p[0].e;

            float en_uzakx = p[0].q;
            float en_uzaky = p[0].w;
            float en_uzakz = p[0].e;

            for(i=0; i<veriler.NSayisi; i++)
            {
                if(p[i].q<x_yakin)
                    x_yakin = p[i].q;

                if(p[i].w<y_yakin)
                    y_yakin = p[i].w;

                if(p[i].e<z_yakin)
                    z_yakin = p[i].e;

                if(p[i].q>en_uzakx)
                    en_uzakx = p[i].q;

                if(p[i].w>en_uzaky)
                    en_uzaky = p[i].w;

                if(p[i].e>en_uzakz)
                    en_uzakz = p[i].e;
            }
            float dist;

             if((en_uzakx-x_yakin)>(en_uzaky-y_yakin) && (en_uzakx-x_yakin)>(en_uzakz-z_yakin))
                dist = en_uzakx-x_yakin;

            else if((en_uzaky-y_yakin)>(en_uzakx-x_yakin) && (en_uzaky-y_yakin)>(en_uzakz-z_yakin))
                dist = en_uzaky-y_yakin;

             else if((en_uzakz-z_yakin)>(en_uzakx-x_yakin) && (en_uzakz-z_yakin)>(en_uzaky-y_yakin))
                dist = en_uzakz-z_yakin;




            float xdist = x_yakin+dist;
            float ydist = y_yakin+dist;
            float zdist = z_yakin+dist;

            printf("\n%s dosyasi\n",verix_isim);

            printf("%f %f %f\n",x_yakin,y_yakin,z_yakin);
            printf("%f %f %f\n",(x_yakin+dist),y_yakin,z_yakin);
            printf("%f %f %f\n",x_yakin,y_yakin,(z_yakin+dist));
            printf("%f %f %f\n",(x_yakin+dist),y_yakin,(z_yakin+dist));
            printf("%f %f %f\n",x_yakin,(y_yakin+dist),z_yakin);
            printf("%f %f %f\n",(x_yakin+dist),(y_yakin+dist),z_yakin);
            printf("%f %f %f\n",x_yakin,(y_yakin+dist),(z_yakin+dist));
            printf("%f %f %f\n",(x_yakin+dist),(y_yakin+dist),(z_yakin+dist));

            fwrite(&x_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&y_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);

            fwrite(&xdist,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&y_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);

            fwrite(&x_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&zdist,sizeof(struct flt_tut),1,sonucRnkszBin);

            fwrite(&xdist,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&y_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&zdist,sizeof(struct flt_tut),1,sonucRnkszBin);

            fwrite(&x_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&ydist,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);

            fwrite(&xdist,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&ydist,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);

            fwrite(&x_yakin,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&ydist,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&zdist,sizeof(struct flt_tut),1,sonucRnkszBin);

            fwrite(&xdist,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&ydist,sizeof(struct flt_tut),1,sonucRnkszBin);
            fwrite(&zdist,sizeof(struct flt_tut),1,sonucRnkszBin);
            fclose(sonucRnkszBin);

            free(p);


        }

    }



    else
    {
        int i,k;

        if(strstr(veriler.DType,"ascii")!=NULL)
        {
            struct Rnkl_Nktlr *p = (struct Rnkl_Nktlr*)malloc(veriler.NSayisi*sizeof(struct Rnkl_Nktlr));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fscanf(verix,"%f",&p[i].x);
                fscanf(verix,"%f",&p[i].y);
                fscanf(verix,"%f",&p[i].z);
                fscanf(verix,"%d",&p[i].r1);
                fscanf(verix,"%d",&p[i].r2);
                fscanf(verix,"%d",&p[i].r3);
            }


            float x_yakin = p[0].x;
            float y_yakin = p[0].y;
            float z_yakin = p[0].z;

            float en_uzakx = p[0].x;
            float en_uzaky = p[0].y;
            float en_uzakz = p[0].z;


            for(i=0; i<veriler.NSayisi; i++)
            {
                if(p[i].x>en_uzakx)
                    en_uzakx = p[i].x;

                if(p[i].y>en_uzaky)
                    en_uzaky = p[i].y;

                if(p[i].z>en_uzakz)
                    en_uzakz=p[i].z;

                if(p[i].x<x_yakin)
                    x_yakin = p[i].x;

                if(p[i].y<y_yakin)
                    y_yakin = p[i].y;

                if(p[i].z<z_yakin)
                    z_yakin=p[i].z;


            }

             float dist;

            if((en_uzakx-x_yakin)>(en_uzaky-y_yakin) && (en_uzakx-x_yakin)>(en_uzakz-z_yakin))
                dist = en_uzakx-x_yakin;

            else if((en_uzaky-y_yakin)>(en_uzakx-x_yakin) && (en_uzaky-y_yakin)>(en_uzakz-z_yakin))
                dist = en_uzaky-y_yakin;

             else if((en_uzakz-z_yakin)>(en_uzakx-x_yakin) && (en_uzakz-z_yakin)>(en_uzaky-y_yakin))
                dist = en_uzakz-z_yakin;


            printf("\n%s dosyasi\n",verix_isim);

            printf("%f %f %f\n",x_yakin,y_yakin,z_yakin);
            printf("%f %f %f\n",(x_yakin+dist),y_yakin,z_yakin);
            printf("%f %f %f\n",x_yakin,y_yakin,(z_yakin+dist));
            printf("%f %f %f\n",(x_yakin+dist),y_yakin,(z_yakin+dist));
            printf("%f %f %f\n",x_yakin,(y_yakin+dist),z_yakin);
            printf("%f %f %f\n",(x_yakin+dist),(y_yakin+dist),z_yakin);
            printf("%f %f %f\n",x_yakin,(y_yakin+dist),(z_yakin+dist));
            printf("%f %f %f\n",(x_yakin+dist),(y_yakin+dist),(z_yakin+dist));


            fprintf(sonucRnklAscii,"%f %f %f\n",x_yakin,y_yakin,z_yakin);
            fprintf(sonucRnklAscii,"%f %f %f\n",(x_yakin+dist),y_yakin,z_yakin);
            fprintf(sonucRnklAscii,"%f %f %f\n",x_yakin,y_yakin,(z_yakin+dist));
            fprintf(sonucRnklAscii,"%f %f %f\n",(x_yakin+dist),y_yakin,(z_yakin+dist));
            fprintf(sonucRnklAscii,"%f %f %f\n",x_yakin,(y_yakin+dist),z_yakin);
            fprintf(sonucRnklAscii,"%f %f %f\n",(x_yakin+dist),(y_yakin+dist),z_yakin);
            fprintf(sonucRnklAscii,"%f %f %f\n",x_yakin,(y_yakin+dist),(z_yakin+dist));
            fprintf(sonucRnklAscii,"%f %f %f\n",(x_yakin+dist),(y_yakin+dist),(z_yakin+dist));


            free(p);
        }

        else if(strstr(veriler.DType,"binary")!=NULL)
        {
            struct Rnkl_Bin *p = (struct Rnkl_Bin*)malloc(veriler.NSayisi*sizeof(struct Rnkl_Bin));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fread(&p[i].q,sizeof(struct flt_tut),1,verix);
                fread(&p[i].w,sizeof(struct flt_tut),1,verix);
                fread(&p[i].e,sizeof(struct flt_tut),1,verix);
                fread(&p[i].a,sizeof(struct int_tut),1,verix);
                fread(&p[i].b,sizeof(struct int_tut),1,verix);
                fread(&p[i].c,sizeof(struct int_tut),1,verix);
            }


            float x_yakin = p[0].q;
            float y_yakin = p[0].w;
            float z_yakin = p[0].e;

            float en_uzakx = p[0].q;
            float en_uzaky = p[0].w;
            float en_uzakz = p[0].e;

            for(i=0; i<veriler.NSayisi; i++)
            {
                if(p[i].q<x_yakin)
                    x_yakin = p[i].q;

                if(p[i].w<y_yakin)
                    y_yakin = p[i].w;

                if(p[i].e<z_yakin)
                    z_yakin = p[i].e;

                if(p[i].q>en_uzakx)
                    en_uzakx = p[i].q;

                if(p[i].w>en_uzaky)
                    en_uzaky = p[i].w;

                if(p[i].e>en_uzakz)
                    en_uzakz = p[i].e;
            }

             float dist;

            if((en_uzakx-x_yakin)>(en_uzaky-y_yakin) && (en_uzakx-x_yakin)>(en_uzakz-z_yakin))
                dist = en_uzakx-x_yakin;

            else if((en_uzaky-y_yakin)>(en_uzakx-x_yakin) && (en_uzaky-y_yakin)>(en_uzakz-z_yakin))
                dist = en_uzaky-y_yakin;

             else if((en_uzakz-z_yakin)>(en_uzakx-x_yakin) && (en_uzakz-z_yakin)>(en_uzaky-y_yakin))
                dist = en_uzakz-z_yakin;




            float xdist = x_yakin+dist;
            float ydist = y_yakin+dist;
            float zdist = z_yakin+dist;

            printf("\n%s dosyasi\n",verix_isim);

            printf("%f %f %f\n",x_yakin,y_yakin,z_yakin);
            printf("%f %f %f\n",(x_yakin+dist),y_yakin,z_yakin);
            printf("%f %f %f\n",x_yakin,y_yakin,(z_yakin+dist));
            printf("%f %f %f\n",(x_yakin+dist),y_yakin,(z_yakin+dist));
            printf("%f %f %f\n",x_yakin,(y_yakin+dist),z_yakin);
            printf("%f %f %f\n",(x_yakin+dist),(y_yakin+dist),z_yakin);
            printf("%f %f %f\n",x_yakin,(y_yakin+dist),(z_yakin+dist));
            printf("%f %f %f\n",(x_yakin+dist),(y_yakin+dist),(z_yakin+dist));

            fwrite(&x_yakin,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&y_yakin,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnklBin);

            fwrite(&xdist,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&y_yakin,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnklBin);

            fwrite(&x_yakin,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&zdist,sizeof(struct flt_tut),1,sonucRnklBin);

            fwrite(&xdist,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&y_yakin,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&zdist,sizeof(struct flt_tut),1,sonucRnklBin);

            fwrite(&x_yakin,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&ydist,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnklBin);

            fwrite(&xdist,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&ydist,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&z_yakin,sizeof(struct flt_tut),1,sonucRnklBin);

            fwrite(&x_yakin,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&ydist,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&zdist,sizeof(struct flt_tut),1,sonucRnklBin);

            fwrite(&xdist,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&ydist,sizeof(struct flt_tut),1,sonucRnklBin);
            fwrite(&zdist,sizeof(struct flt_tut),1,sonucRnklBin);
            fclose(sonucRnklBin);


            free(p);
        }

    }

    fclose(verix);
    fclose(sonucRnklAscii);
    fclose(sonucRnklBin);
    fclose(sonucRnkszAscii);
    fclose(sonucRnkszBin);

}



void Ister4(struct bilgi veriler,char verix_isim[],float kurex,float kurey,float kurez,float kurer)
{
    FILE *veri1 = fopen(verix_isim,"r");
    FILE *sonucRnklBin = fopen("OutputRenkliBinary.nkt","ab");
    FILE *sonucRnkszBin = fopen("OutputRenksizBinary.nkt","ab");
    FILE *sonucRnklAscii = fopen("OutputRenkliAscii.nkt","a");
    FILE *sonucRnkszAscii = fopen("OutputRenksizAscii.nkt","a");

    char bosluk[51];

    if(strstr(veriler.alanlar,"xyzrgb")==NULL)
    {
        int i,k;

        for(i=0; i<5; i++)
        {
            fgets(bosluk,51,veri1);
        }

        if(strstr(veriler.DType,"ascii")!=NULL)
        {
            struct Rnksz_Nktlr *p = (struct Rnksz_Nktlr*)malloc(veriler.NSayisi*sizeof(struct Rnksz_Nktlr));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fscanf(veri1,"%f",&p[i].x);
                fscanf(veri1,"%f",&p[i].y);
                fscanf(veri1,"%f",&p[i].z);
            }


            float *krc;
            float xdis,ydis,zdis,rdis;
            int krc_ns=0;
            krc = (float*)malloc(sizeof(float));

            if(krc==NULL)
            {
                printf("ilk alan ayrilamadi\n");
                exit(1);
            }

            for(i=0; i<veriler.NSayisi; i++)
            {
                xdis = pow((p[i].x-kurex),2);
                ydis = pow((p[i].y-kurey),2);
                zdis = pow((p[i].z-kurez),2);

                rdis = sqrt(xdis+ydis+zdis);

                if(rdis<kurer)
                {
                    krc = (float*)realloc(krc,(i+1)*3*sizeof(float));
                    if(krc==NULL)
                    {
                        printf("sonraki alan ayrilmadi\n");
                        exit(2);
                    }

                    k = krc_ns*3;

                    krc[k] = p[i].x;
                    k++;

                    krc[k] = p[i].y;
                    k++;

                    krc[k] = p[i].z;
                    krc_ns++;
                }
            }

            printf("\n%s dosyasi\n",verix_isim);

            k=0;
            for(i=0; i<krc_ns; i++)
            {
                k=i*3;

                printf("%f\t",krc[k]);
                fprintf(sonucRnkszAscii,"%f\t",krc[k]);

                k++;
                printf("%f\t",krc[k]);
                fprintf(sonucRnkszAscii,"%f\t",krc[k]);

                k++;
                printf("%f\n",krc[k]);
                fprintf(sonucRnkszAscii,"%f\n",krc[k]);
            }

            free(krc);
            free(p);
        }

        else if(strstr(veriler.DType,"binary")!=NULL)
        {
            float xdis,ydis,zdis,rdis;
            int krc_ns=0;
            int sayac;
            int *nktlr = (int*)malloc(sizeof(int));
            struct Rnksz_Bin *p = (struct Rnksz_Bin*)malloc(veriler.NSayisi*sizeof(struct Rnksz_Bin));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fread(&p[i].q,sizeof(struct flt_tut),1,veri1);
                fread(&p[i].w,sizeof(struct flt_tut),1,veri1);
                fread(&p[i].e,sizeof(struct flt_tut),1,veri1);

            }

            for(i=0; i<veriler.NSayisi; i++)
            {
                xdis = pow((p[i].q-kurex),2);
                ydis = pow((p[i].w-kurey),2);
                zdis = pow((p[i].e-kurez),2);

                rdis = sqrt(xdis+ydis+zdis);

                if(rdis<kurer)
                {

                    nktlr[krc_ns]=i;
                    krc_ns++;
                    nktlr =(int*)realloc(nktlr,(krc_ns+1)*sizeof(int));


                }

            }

            printf("\n%s dosyasi\n",verix_isim);


            for(i=0; i<krc_ns; i++)
            {
                sayac = nktlr[i];

                printf("%f %f %f\n",p[sayac].q,p[sayac].w,p[sayac].e);

                fwrite(&p[sayac].q,sizeof(struct flt_tut),1,sonucRnkszBin);
                fwrite(&p[sayac].w,sizeof(struct flt_tut),1,sonucRnkszBin);
                fwrite(&p[sayac].e,sizeof(struct flt_tut),1,sonucRnkszBin);

            }
            fclose(sonucRnkszBin);

            free(p);
            free(nktlr);
        }

    }


    else
    {
        int i,k,sayac;

        for(i=0; i<5; i++)
            fgets(bosluk,51,veri1);

        if(strstr(veriler.DType,"ascii")!=NULL)
        {

            struct Rnkl_Nktlr *p = (struct Rnkl_Nktlr*)malloc(veriler.NSayisi*sizeof(struct Rnkl_Nktlr));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fscanf(veri1,"%f",&p[i].x);
                fscanf(veri1,"%f",&p[i].y);
                fscanf(veri1,"%f",&p[i].z);
                fscanf(veri1,"%d",&p[i].r1);
                fscanf(veri1,"%d",&p[i].r2);
                fscanf(veri1,"%d",&p[i].r3);

            }


            float *krc;
            float xdis,ydis,zdis,rdis;
            int krc_ns=0;
            krc = (float*)malloc(sizeof(float));

            if(krc==NULL)
            {
                printf("ilk alan ayrilamadi\n");
                exit(1);
            }

            for(i=0; i<veriler.NSayisi; i++)
            {
                xdis = pow((p[i].x-kurex),2);
                ydis = pow((p[i].y-kurey),2);
                zdis = pow((p[i].z-kurez),2);

                rdis = sqrt(xdis+ydis+zdis);

                if(rdis<kurer)
                {
                    krc = (float*)realloc(krc,(i+1)*6*sizeof(float));
                    if(krc==NULL)
                    {
                        printf("sonraki alan ayrilmadi\n");
                        exit(2);
                    }

                    k = krc_ns*6;

                    krc[k] = p[i].x;
                    k++;

                    krc[k] = p[i].y;
                    k++;

                    krc[k] = p[i].z;
                    k++;

                    krc[k] = p[i].r1;
                    k++;

                    krc[k] = p[i].r2;
                    k++;

                    krc[k] = p[i].r3;

                    krc_ns++;
                }
            }

            printf("\n%s dosyasi\n",verix_isim);

            k=0;
            for(i=0; i<krc_ns; i++)
            {

                k=i*6;

                printf("%f\t",krc[k]);
                fprintf(sonucRnklAscii,"%f\t",krc[k]);
                k++;

                printf("%f\t",krc[k]);
                fprintf(sonucRnklAscii,"%f\t",krc[k]);
                k++;

                printf("%f\t",krc[k]);
                fprintf(sonucRnklAscii,"%f\t",krc[k]);
                k++;


                printf("%.f\t",krc[k]);
                fprintf(sonucRnklAscii,"%.f\t",krc[k]);
                k++;


                printf("%.f\t",krc[k]);
                fprintf(sonucRnklAscii,"%.f\t",krc[k]);
                k++;


                printf("%.f\n",krc[k]);
                fprintf(sonucRnklAscii,"%.f\n",krc[k]);
                k++;


            }
            free(p);
            free(krc);
        }

        else if(strstr(veriler.DType,"binary")!=NULL)
        {

            struct Rnkl_Bin *p = (struct Rnkl_Bin*)malloc(veriler.NSayisi*sizeof(struct Rnkl_Bin));
            int *nktlr = (int*)malloc(sizeof(int));
            int krc_ns=0;
            float xdis,ydis,zdis,rdis;

            for(i=0; i<veriler.NSayisi; i++)
            {
                fread(&p[i].q,sizeof(struct flt_tut),1,veri1);
                fread(&p[i].w,sizeof(struct flt_tut),1,veri1);
                fread(&p[i].e,sizeof(struct flt_tut),1,veri1),

                fread(&p[i].a,sizeof(struct int_tut),1,veri1);
                fread(&p[i].b,sizeof(struct int_tut),1,veri1);
                fread(&p[i].c,sizeof(struct int_tut),1,veri1);
            }


            for(i=0; i<veriler.NSayisi; i++)
            {
                xdis = pow((p[i].q-kurex),2);
                ydis = pow((p[i].w-kurey),2);
                zdis = pow((p[i].e-kurez),2);
                rdis = sqrt(xdis+ydis+zdis);

                if(kurer>rdis)
                {
                    nktlr[krc_ns] = i;

                    krc_ns++;
                    nktlr = (int*)realloc(nktlr,(krc_ns+1)*sizeof(int));
                }

            }

            printf("\n%s dosyasi\n",verix_isim);

            for(i=0; i<krc_ns; i++)
            {
                sayac = nktlr[i];

                printf("%f %f %f %d %d %d\n",p[sayac].q,p[sayac].w,p[sayac].e,p[sayac].a,p[sayac].b,p[sayac].c);

                fwrite(&p[krc_ns].q,sizeof(struct flt_tut),1,sonucRnklBin);
                fwrite(&p[krc_ns].w,sizeof(struct flt_tut),1,sonucRnklBin);
                fwrite(&p[krc_ns].e,sizeof(struct flt_tut),1,sonucRnklBin);

                fwrite(&p[krc_ns].a,sizeof(struct int_tut),1,sonucRnklBin);
                fwrite(&p[krc_ns].b,sizeof(struct int_tut),1,sonucRnklBin);
                fwrite(&p[krc_ns].c,sizeof(struct int_tut),1,sonucRnklBin);
            }

            fclose(sonucRnklBin);




            free(p);
        }


    }

    fclose(veri1);
    fclose(sonucRnklAscii);
    fclose(sonucRnklBin);
    fclose(sonucRnkszAscii);
    fclose(sonucRnkszBin);

}

void Ister5(struct bilgi veriler,char verix_isim[])
{
    FILE *verix = fopen(verix_isim,"r");
    FILE *sonucRnklBin = fopen("OutputRenkliBinary.nkt","ab");
    FILE *sonucRnkszBin = fopen("OutputRenksizBinary.nkt","ab");
    FILE *sonucRnklAscii = fopen("OutputRenkliAscii.nkt","a");
    FILE *sonucRnkszAscii = fopen("OutputRenksizAscii.nkt","a");

    double ort=0;
    double num=0;
    int i,k;
    float xdis;
    float ydis;
    float zdis;
    double dist_check;

    char atlama[51];
    for(i=0; i<5; i++)
    {
        fgets(atlama,50,verix);
    }

    if(strstr(veriler.alanlar,"xyzrgb")==NULL)
    {
        if(strstr(veriler.DType,"ascii")!=NULL)
        {
            struct Rnksz_Nktlr *p = (struct Rnksz_Nktlr*)malloc(veriler.NSayisi*sizeof(struct Rnksz_Nktlr));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fscanf(verix,"%f",&p[i].x);
                fscanf(verix,"%f",&p[i].y);
                fscanf(verix,"%f",&p[i].z);

            }


            for(i=0; i<veriler.NSayisi; i++)
                for(k=i+1; k<veriler.NSayisi; k++)
                {
                    xdis = pow((p[k].x - p[i].x),2);
                    ydis = pow((p[k].y - p[i].y),2);
                    zdis = pow((p[k].z - p[i].z),2);
                    dist_check = sqrt(xdis+ydis+zdis);

                    ort=ort+dist_check;
                    num ++;
                }

            ort = ort/num;

            printf("\n%s dosyasi\n",verix_isim);

            printf("%f\n",ort);
            fprintf(sonucRnkszAscii,"%f\n",ort);
            free(p);
        }

        else if(strstr(veriler.DType,"binary")!=NULL)
        {
            struct Rnksz_Bin *p = (struct Rnksz_Bin*)malloc(veriler.NSayisi*sizeof(struct Rnksz_Bin));


            for(i=0; i<veriler.NSayisi; i++)
            {
                fread(&p[i].q,sizeof(struct flt_tut),1,verix);
                fread(&p[i].w,sizeof(struct flt_tut),1,verix);
                fread(&p[i].e,sizeof(struct flt_tut),1,verix);
            }

            for(i=0; i<veriler.NSayisi-1; i++)
            {
                for(k=i+1; k<veriler.NSayisi; k++)
                {
                    xdis = pow((p[i].q-p[k].q),2);
                    ydis = pow((p[i].w-p[k].w),2);
                    zdis = pow((p[i].e-p[k].e),2);
                    dist_check = sqrt(xdis+ydis+zdis);
                    num++;

                    ort+=dist_check;

                }
            }
            ort = ort/num;

            printf("\n%s dosyasi\n",verix_isim);

            printf("%f\n",ort);
            fwrite(&ort,sizeof(struct flt_tut),1,sonucRnkszBin);
            fclose(sonucRnkszBin);

            free(p);
        }
    }

    else
    {
        if(strstr(veriler.DType,"ascii")!=NULL)
        {
            struct Rnkl_Nktlr *p = (struct Rnkl_Nktlr*)malloc(veriler.NSayisi*sizeof(struct Rnkl_Nktlr));

            for(i=0; i<veriler.NSayisi; i++)
            {
                fscanf(verix,"%f",&p[i].x);
                fscanf(verix,"%f",&p[i].y);
                fscanf(verix,"%f",&p[i].z);
                fscanf(verix,"%d",&p[i].r1);
                fscanf(verix,"%d",&p[i].r2);
                fscanf(verix,"%d",&p[i].r3);
            }


            for(i=0; i<veriler.NSayisi; i++)
                for(k=i+1; k<veriler.NSayisi; k++)
                {
                    xdis = pow((p[k].x - p[i].x),2);
                    ydis = pow((p[k].y - p[i].y),2);
                    zdis = pow((p[k].z - p[i].z),2);
                    dist_check = sqrt(xdis+ydis+zdis);

                    ort+=dist_check;
                    num++;
                }

            ort = ort/num;

            printf("\n%s dosyasi\n",verix_isim);



            printf("%f\n",ort);
            fprintf(sonucRnklAscii,"%f\n",ort);
            free(p);

        }

        else if(strstr(veriler.DType,"binary")!=NULL)
        {
            struct Rnkl_Bin *p = (struct Rnkl_Bin*)malloc(veriler.NSayisi*sizeof(struct Rnkl_Bin ));
            int *nktlr = (int*)malloc(sizeof(int));
            int nkt_num=0;

            for(i=0; i<veriler.NSayisi; i++)
            {
                fread(&p[i].q,sizeof(struct flt_tut),1,verix);
                fread(&p[i].w,sizeof(struct flt_tut),1,verix);
                fread(&p[i].e,sizeof(struct flt_tut),1,verix);

                fread(&p[i].a,sizeof(struct int_tut),1,verix);
                fread(&p[i].b,sizeof(struct int_tut),1,verix);
                fread(&p[i].c,sizeof(struct int_tut),1,verix);

            }

            for(i=0; i<veriler.NSayisi-1; i++)
            {
                for(k=i+1; k<veriler.NSayisi; k++)
                {
                    xdis = pow((p[i].q-p[k].q),2);
                    ydis = pow((p[i].w-p[k].w),2);
                    zdis = pow((p[i].e-p[k].e),2);
                    dist_check = sqrt(xdis+ydis+zdis);
                    num++;

                    ort+=dist_check;
                }

            }

            ort = ort/num;

            printf("\n%s dosyasi\n",verix_isim);

            printf("%f\n",ort);
            fwrite(&ort,sizeof(struct flt_tut),1,sonucRnklBin);
            fclose(sonucRnklBin);

            free(p);
        }


    }

    fclose(verix);
    fclose(sonucRnklAscii);
    fclose(sonucRnklBin);
    fclose(sonucRnkszAscii);
    fclose(sonucRnkszBin);


}


int main()
{

    char bosluk[51];
    char veri1_isim[51];
    char veri2_isim[51];
    char veri3_isim[51];
    char veri4_isim[51];
    int secim=9;
    char ister1[4][101];
    int bir_check=0;

    do
    {
        FILE *sonucRnklBin = fopen("OutputRenkliBinary.nkt","ab");
        FILE *sonucRnkszBin = fopen("OutputRenksizBinary.nkt","ab");
        FILE *sonucRnklAscii = fopen("OutputRenkliAscii.nkt","a");
        FILE *sonucRnkszAscii = fopen("OutputRenksizAscii.nkt","a");

        printf("\nLutfen seciminizi girin:\n");
        fprintf(sonucRnklAscii,"\nLutfen seciminizi girin:\n");
        fprintf(sonucRnkszAscii,"\nLutfen seciminizi girin:\n");
        fprintf(sonucRnklBin,"\nLutfen seciminizi girin:\n");
        fprintf(sonucRnkszBin,"\nLutfen seciminizi girin:\n");
        printf("Secim1 icin 1'e basin\n");
        printf("Secim2 icin 2'ye basin\n");
        printf("Secim3 icin 3'e basin\n");
        printf("Secim4 icin 4'e basin\n");
        printf("Secim5 icin 5'e basin\n");
        printf("Cikmak icin 0'a basin\n");

        scanf("%d",&secim);

        switch(secim)
        {

        case 0:
            printf("Cikis\n");
            fprintf(sonucRnklAscii,"Cikis\n");
            fprintf(sonucRnkszAscii,"Cikis\n");
            fprintf(sonucRnklBin,"Cikis\n");
            fprintf(sonucRnkszBin,"Cikis\n");
            break;

        case 1:

            printf("Secim1\n");
            fprintf(sonucRnklAscii,"Secim1\n");
            fprintf(sonucRnkszAscii,"Secim1\n");
            fprintf(sonucRnklBin,"Secim1\n");
            fprintf(sonucRnkszBin,"Secim1\n");
            bir_check = 1;

            Ister1(ister1);

            strcpy(veri1_isim,ister1[0]);
            strcpy(veri2_isim,ister1[1]);
            strcpy(veri3_isim,ister1[2]);
            strcpy(veri4_isim,ister1[3]);

            if((strstr(veri1_isim,".")!=NULL) && (strstr(veri2_isim,".")!=NULL)  && (strstr(veri3_isim,".")!=NULL)  && (strstr(veri4_isim,".")!=NULL))
            {
                printf("\nTum dosyalar uyumludur.\n\n");
                fprintf(sonucRnklAscii,"\nTum dosyalar uyumludur.\n\n");
                fprintf(sonucRnkszAscii,"\nTum dosyalar uyumludur.\n\n");
                fprintf(sonucRnklBin,"\nTum dosyalar uyumludur.\n\n");
                fprintf(sonucRnkszBin,"\nTum dosyalar uyumludur.\n\n");
            }


            FILE *veri1 = fopen(veri1_isim,"r");
            FILE *veri2 = fopen(veri2_isim,"r");
            FILE *veri3 = fopen(veri3_isim,"r");
            FILE *veri4 = fopen(veri4_isim,"r");

            struct bilgi tanim1;
            struct bilgi tanim2;
            struct bilgi tanim3;
            struct bilgi tanim4;
            // renksiz ascii = veri2, renkli ascii = veri1, renksiz binary =veri4, renkli binary = veri3;

            int i;

            fseek(veri1,0,SEEK_SET);
            fseek(veri2,0,SEEK_SET);
            fseek(veri3,0,SEEK_SET);
            fseek(veri4,0,SEEK_SET);

            fgets(bosluk,50,veri2);

            fgets(bosluk,50,veri2);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim2.version);


            fgets(bosluk,50,veri2);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim2.alanlar);



            int stop;
            fgets(bosluk,50,veri2);
            for(i=0; i<strlen(bosluk); i++)
                if(bosluk[i]==' ')
                {
                    stop = i;
                    break;
                }


            tanim2.NSayisi = atoi(bosluk+stop);

            fgets(bosluk,50,veri2);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim2.DType);

            ////////////////////////////////////////////
            fgets(bosluk,50,veri1);

            fgets(bosluk,50,veri1);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim1.version);

            fgets(bosluk,50,veri1);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim1.alanlar);


            fgets(bosluk,50,veri1);
            for(i=0; i<strlen(bosluk); i++)
                if(bosluk[i]==' ')
                {
                    stop = i;
                    break;
                }

            tanim1.NSayisi = atoi(bosluk+stop);


            fgets(bosluk,50,veri1);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim1.DType);
            /////////////////////////////////////////

            fgets(bosluk,50,veri3);

            fgets(bosluk,50,veri3);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim3.version);


            fgets(bosluk,50,veri3);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim3.alanlar);


            fgets(bosluk,50,veri3);
            for(i=0; i<strlen(bosluk); i++)
                if(bosluk[i]==' ')
                {
                    stop = i;
                    break;
                }


            tanim3.NSayisi = atoi(bosluk+stop);

            fgets(bosluk,50,veri3);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim3.DType);
            ////////////////////////////////////////////

            fgets(bosluk,50,veri4);

            fgets(bosluk,50,veri4);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim4.version);


            fgets(bosluk,50,veri4);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim4.alanlar);


            fgets(bosluk,50,veri4);
            for(i=0; i<strlen(bosluk); i++)
                if(bosluk[i]==' ')
                {
                    stop = i;
                    break;
                }


            tanim4.NSayisi = atoi(bosluk+stop);

            fgets(bosluk,50,veri4);
            bosluk_sil(bosluk);
            sscanf(bosluk,"%s",tanim4.DType);

            fclose(sonucRnklAscii);
            fclose(sonucRnklBin);
            fclose(sonucRnkszAscii);
            fclose(sonucRnkszBin);




            break;




        case 2:
            if(bir_check != 1)
            {
                printf("1 menusu secilmedigi icin bellekte veri yoktur!\n");
                break;
            }

            printf("Secim2\n");
            fprintf(sonucRnklAscii,"Secim2\n");
            fprintf(sonucRnkszAscii,"Secim2\n");
            fprintf(sonucRnklBin,"Secim2\n");
            fprintf(sonucRnkszBin,"Secim2\n");

            fclose(sonucRnklAscii);
            fclose(sonucRnklBin);
            fclose(sonucRnkszAscii);
            fclose(sonucRnkszBin);


            if(strstr(veri1_isim,".")!=NULL)
                Ister2(tanim1,veri1_isim);

            if(strstr(veri2_isim,".")!=NULL)
                Ister2(tanim2,veri2_isim);

            if(strstr(veri3_isim,".")!=NULL)
                Ister2(tanim3,veri3_isim);

            if(strstr(veri4_isim,".")!=NULL)
                Ister2(tanim4,veri4_isim);

            break;


        case 3:
            if(bir_check != 1)
            {
                printf("1 menusu secilmedigi icin bellekte veri yoktur!\n");
                break;
            }

            printf("Secim3\n");
            fprintf(sonucRnklAscii,"Secim3\n");
            fprintf(sonucRnkszAscii,"Secim3\n");
            fprintf(sonucRnklBin,"Secim3\n");
            fprintf(sonucRnkszBin,"Secim3\n");

            fclose(sonucRnklAscii);
            fclose(sonucRnklBin);
            fclose(sonucRnkszAscii);
            fclose(sonucRnkszBin);

            if(strstr(veri1_isim,".")!=NULL)
                Ister3(tanim1,veri1_isim);

            if(strstr(veri2_isim,".")!=NULL)
                Ister3(tanim2,veri2_isim);

            if(strstr(veri3_isim,".")!=NULL)
                Ister3(tanim3,veri3_isim);

            if(strstr(veri4_isim,".")!=NULL)
                Ister3(tanim4,veri4_isim);


            break;

        case 4:
            if(bir_check != 1)
            {
                printf("1 menusu secilmedigi icin bellekte veri yoktur!\n");
                break;
            }

            float kurex,kurey,kurez,kurer;
            printf("Secim4\n");
            fprintf(sonucRnklAscii,"Secim4\n");
            fprintf(sonucRnkszAscii,"Secim4\n");
            fprintf(sonucRnklBin,"Secim4\n");
            fprintf(sonucRnkszBin,"Secim4\n");

            printf("\nSirasiyla kurenizin x y z ve r bilgilerini girin\n");
            scanf("%f %f %f %f",&kurex,&kurey,&kurez,&kurer);
            fprintf(sonucRnklAscii,"cx=%f cy=%f cz=%f cr=%f\n",kurex,kurey,kurez,kurer);
            fprintf(sonucRnkszAscii,"cx=%f cy=%f cz=%f cr=%f\n",kurex,kurey,kurez,kurer);
            fprintf(sonucRnklBin,"cx=%f cy=%f cz=%f cr=%f\n",kurex,kurey,kurez,kurer);
            fprintf(sonucRnkszBin,"cx=%f cy=%f cz=%f cr=%f\n",kurex,kurey,kurez,kurer);

            fclose(sonucRnklAscii);
            fclose(sonucRnklBin);
            fclose(sonucRnkszAscii);
            fclose(sonucRnkszBin);


            if(strstr(veri1_isim,".")!=NULL)
                Ister4(tanim1,veri1_isim,kurex,kurey,kurez,kurer);

            if(strstr(veri2_isim,".")!=NULL)
                Ister4(tanim2,veri2_isim,kurex,kurey,kurez,kurer);

            if(strstr(veri3_isim,".")!=NULL)
                Ister4(tanim3,veri3_isim,kurex,kurey,kurez,kurer);

            if(strstr(veri4_isim,".")!=NULL)
                Ister4(tanim4,veri4_isim,kurex,kurey,kurez,kurer);


            break;

        case 5:
            if(bir_check != 1)
            {
                printf("1 menusu secilmedigi icin bellekte veri yoktur!\n");
                break;
            }

            printf("Secim5\n");
            fprintf(sonucRnklAscii,"Secim5\n");
            fprintf(sonucRnkszAscii,"Secim5\n");
            fprintf(sonucRnklBin,"Secim5\n");
            fprintf(sonucRnkszBin,"Secim5\n");

            fclose(sonucRnklAscii);
            fclose(sonucRnklBin);
            fclose(sonucRnkszAscii);
            fclose(sonucRnkszBin);


            if(strstr(veri1_isim,".")!=NULL)
                Ister5(tanim1,veri1_isim);

            if(strstr(veri2_isim,".")!=NULL)
                Ister5(tanim2,veri2_isim);

            if(strstr(veri3_isim,".")!=NULL)
                Ister5(tanim3,veri3_isim);

            if(strstr(veri4_isim,".")!=NULL)
                Ister5(tanim4,veri4_isim);


            break;

        default:
            printf("Lutfen gecerli bir islem giriniz:\n");


        }


    }
    while(secim!=0);



    return 0;

}
