/*

"Base64, Vigenere, Caesar" encoding/decoding program.

Made by:

Ahmet Galip Sengun
Emirhan Arslantas
Ilhan Furkan Sadikoglu
Kerem Akkoyun

25/10/2019

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 6000

void AsciiToBin_B64en();
void BinToDec_B64en();
void DivideBy6_B64en();
void Result_B64en();
void RemoveEqualsSign_B64de();
void AsciiToBin_B64de();
void BinToResult_B64de();
void CaesarCipherEn(int);
void CaesarCipherDe(int);
void VigenereCipherEn(int);
void VigenereCipherDe(int);


struct s{
		int proc;//işlemi tutar
		int input;//girdi tipini tutar
		int method;//sifreleme yöntemini tutar
		int output;//çıktı tipini tutar
		int tekrar;//şifreleme sayısını tutar
		};

	char base64table[]=	{'A','B','C','D','E','F','G','H','I',
						'J','K','L','M','N','O','P','Q','R',
						'S','T','U','V','W','X','Y','Z','a',
						'b','c','d','e','f','g','h','i','j',
						'k','l','m','n','o','p','q','r','s',
						't','u','v','w','x','y','z','0','1',
						'2','3','4','5','6','7','8','9','+','/'};
char input[6000];//kullanıcıdan alınan veri tüm yöntemlerde aynı dizide tutuluyor
char finalOutput[(MAX*8/6)+2];//işlenmiş veriyi tutar
int pasw_size;//şifre bıyutunu tutar
int paswdecimal_6[MAX*8/6];//6lık taban halini tutar
int uzunluk_6;//uzunluğu  tutar
int bos2[6];//yedek dizi
int tut_6_2[((600000*8/6)+1)];
char dizi[600000]="";
char viegenere_adim_sayisi_tutucu[10][50];
char sifre_tut[50];


//base64<
int b,h;
int flag=0;
int bos[8];
int tut_8[MAX*8];
int tut_6[(MAX*8/6)+2][6];
int des[(MAX*8/6)+2];
//base64>

int adim_sayisi_tutucu[10];//sezar


int main()
{
	FILE *f,*f2;
	struct s Sec;
	printf("Yapilacak islemi seciniz:\n1:Sifrele\n2:Coz\n");
	scanf("%d",&Sec.proc);
	printf("Alma yontemini seciniz:\n1:Submit\n2:Text file\n");
	scanf("%d",&Sec.input);
	printf("Sifreleme algoritmasini seciniz:\n1:Base64\n2:Sezar\n3:Vigenere\n");
	scanf("%d",&Sec.method);
	printf("Cikti yontemini seciniz:\n1:Submit\n2:Text file\n");
	scanf("%d",&Sec.output);
    if (Sec.method==1)
        Sec.tekrar=1;
    else{
        printf("Kac kere tekrarlanacagini giriniz:\n");
        scanf("%d",&Sec.tekrar);
    }
		if(Sec.input==1)//input < terminalden alma
	{
		flag=1;
		printf("\n\nLutfen islem yapilacak karakterleri giriniz (maksimum 6000 karakter girebilirsiniz): ");
		fflush(stdin);
		fgets(input, 6000, stdin);
	}
		if(Sec.input==2)//input < dosyadan alma
	{

	if(Sec.proc == 1){
        f = fopen("text.txt","r");
        if(f==NULL)
        {
            return 0;
        }
	}

	else if(Sec.proc == 2){
        f = fopen("text2.txt","r");
        if(f==NULL)
        {
            return 0;
        }
	}

        char c;// vigenere encoding
        int i=0;
        while((c = fgetc(f)) != EOF)
        {
            input[i]=c;
            i++;
        }
        printf("\nAlinan metin:%s",input);
        fclose(f);
    }

    if(Sec.method==1){//>base64
		if(Sec.proc==1){//encode
            for(int tek=0;tek<Sec.tekrar;tek++){
            AsciiToBin_B64en();
            DivideBy6_B64en();
            BinToDec_B64en();
            Result_B64en();
            strcpy(input,finalOutput);}
						}//encode
		if(Sec.proc==2){//decode
            for(int tek=0;tek<Sec.tekrar;tek++){
            pasw_size = strlen(input);
            RemoveEqualsSign_B64de();
            AsciiToBin_B64de();
            BinToResult_B64de();
            strcpy(input,finalOutput);}
		}//decode

								  }//base64<



    if(Sec.method==2){//>sezar
		if(Sec.proc==1){//encode

            int i;

            printf("\n");

            for(i=0;i<Sec.tekrar;i++)
            {
                printf("%d. Adimdaki oteleme sayisini giriniz: ",i+1);
                scanf("%d",&adim_sayisi_tutucu[i]);
            }

            CaesarCipherEn(Sec.tekrar);

        }//encode
		if(Sec.proc==2){//decode


            printf("\n");

            for(int i=0;i<Sec.tekrar;i++)
            {
                printf("%d. Adimdaki oteleme sayisini giriniz: ",i+1);
                scanf("%d",&adim_sayisi_tutucu[i]);
            }

            CaesarCipherDe(Sec.tekrar);

        }//decode

    }//sezar<


    if(Sec.method==3){//>vigenere
		if(Sec.proc==1){//encode
            int i;

            printf("\n");

            for(i=0;i<Sec.tekrar;i++)
            {
                printf("%d. Adimdaki sifre degistirciyi giriniz(maksimum 50 karakter olabilir): ",i+1);
                fflush(stdin);
                fgets(sifre_tut,50,stdin);
                int k = strlen(sifre_tut);

                for(int j=0;j<k-1;j++)
                {
                    viegenere_adim_sayisi_tutucu[i][j] = sifre_tut[j];
                }
            }

            VigenereCipherEn(Sec.tekrar);

        }//encode
		if(Sec.proc==2){//decode
            printf("\n");

            for(int i=0;i<Sec.tekrar;i++)
            {
                printf("%d. Adimdaki sifre degistirciyi giriniz(maksimum 50 karakter olabilir): ",i+1);
                fflush(stdin);
                fgets(sifre_tut,50,stdin);
                int k = strlen(sifre_tut);

                for(int j=0;j<k-1;j++)
                {
                    viegenere_adim_sayisi_tutucu[i][j] = sifre_tut[j];
                }
            }


            VigenereCipherDe(Sec.tekrar);

        }//decode

    }//vigenere<


	if(Sec.output==1)//output < terminale yazdırma
	{
		printf("\nSonuc: %s",finalOutput);

    }
    if(Sec.output==2)//output < dosyaya yazdırma
	{
		f2 = fopen("text2.txt","w");
        fflush(stdout);
        fprintf(f2, "\n%s", finalOutput);//text2 dosyasına şifreyi yazdırma
        fclose(f2);
    }
	return 0;
}

void AsciiToBin_B64en() {// şifrelenecek metini karakter karakter okur,
	flag=0;              // bu karakterlerin ascii kodlarını 2'lik tabana
	int i,j,k;           // her biri 8 basamaklı olacak şekilde çevirir.

	b=strlen(input);
	if(flag==1)
        b=strlen(input)-1;

	for(i=0;i<b;i++) {
		for(j=0;j<7;j++) {
			bos[j]=0;
		}

        int r = (int)input[i];

        for(k=7;k>=0;k--) {

            bos[k]=r%2;
            r = r/2;
        }

        for(int h=i*8,f=0;h<(i*8)+8;h++,f++){
            tut_8[h] = bos[f];
        }
        tut_8[(i*8)+8] = 2;

	}
}

void DivideBy6_B64en() { // 2'lik tabandaki binary dizisini 6'lı parçalara böler

	h = b*8/6;
	int s=0;

	if(b*8%6!=0)
	{
		h = (b*8/6)+1;
	}

	for(int i=0;i<h;i++)
	{
		for(int j=0;j<6;j++)
		{
			if(tut_8[s]==1||tut_8[s]==0)
			{
				tut_6[i][j]=tut_8[s++];
			}

			else
			{
				tut_6[i][j]= 0;
			}
		}
	}
	if(b*8%6 == 2){
			h = h+2;
			for(int u = h-2;u<h;u++){
				for(int q = 0;q<6;q++)
				{
					tut_6[u][q] = 0;
				}
			}
		}

	if(b*8%6 == 4){
			h = h+1;
			for(int u = h-1;u<h;u++){
				for(int q = 0;q<6;q++)
				{
					tut_6[u][q] = 0;
				}
			}
		}
}

void BinToDec_B64en() // 6'şar basamaklı binary parçalarını 10'luk tabana çevirir
{

	for(int i=0;i<h;i++)
	{
		int toplam=0;
		for(int j=0;j<6;j++)
            toplam += tut_6[i][j]*pow(2,5-j);

		des[i] = toplam;
	}
}

void Result_B64en() // output dizisine şifreli metini atar
{
	if(b*8%6==0)
	{
		for(int i = 0;i<h;i++)
		{
			finalOutput[i] = base64table[des[i]];
		}


	}

	if(b*8%6==2)
	{
		for(int i = 0;i<(b*8/6)+1;i++)
		{
			finalOutput[i] = base64table[des[i]];
		}
		for(int z = h-2;z<h;z++)
		{
			finalOutput[z] = '=';
		}


	}

	if(b*8%6==4)
	{
		for(int i = 0;i<(b*8/6)+1;i++)
		{
			finalOutput[i] = base64table[des[i]];
		}
		for(int z = h-1;z<h;z++)
		{
			finalOutput[z] = '=';
		}



	}

}
//decrypt
void RemoveEqualsSign_B64de() // şifreli metini, sonundaki olası '=' işaretlerini yoksayarak yeni bir diziye atar.
{

	for(int i = 0;i<pasw_size; i++){
		uzunluk_6=i;
		if(input[i] == '='){
		break;}

		for(int j = 0; j<64; j++){
			if(input[i] == base64table[j]){
				paswdecimal_6[i] = j;
				break;
			}
		}
	}
}
void AsciiToBin_B64de(){ // şifreli metini karakter karakter okur,
	int i,j,k;           // bu karakterlerin ascii kodlarını 2'lik tabana,
                         // her biri 6 basamaklı olacak şekilde çevirir.
	int b=uzunluk_6;


	for(i=0;i<b;i++){
		for(j=0;j<6;j++){
			bos2[j]=0;
		}

        int r = (int)paswdecimal_6[i];

        for(k=5;k>=0;k--){
            bos2[k]=r%2;
            r = r/2;
        }

        for(int h=i*6,f=0;h<(i*6)+6;h++,f++){
            tut_6_2[h] = bos2[f];
        }

        tut_6_2[(i*6)+6] = 2;
    }
}
void BinToResult_B64de(){   // ikilik tabandaki diziyi 8'erli parçalar olarak okur
                            // bu parçaları onluk tabana çevirir
    int toplam,a,t=0;       // onluk tabana çevrilmiş sayıların ascii karşılıklarını output dizisine gönderir
    a=uzunluk_6*6;
    int i=0;
    while (i<a){
        toplam=0;
        if (i<(a-(a%8))){
            for(int j=0;j<8;j++){
                if (tut_6_2[i]==1){
                    toplam += pow(2,7-j);
                }
                i++;
            }
        }
        else {
            for(int j=0;j<a%8;j++){
                if (tut_6_2[i]==1){
                    toplam += pow(2,a%8-j);
                }
                i++;
            }
        }
    dizi[i]=(char)toplam;
    finalOutput[t]=dizi[i];
    t++;
    }
}
//base64


//sezar
void CaesarCipherEn(int sayi) // sezar encoding
{
	flag = 0;
	b = strlen(input);
	if(flag == 1)
	{
		b = strlen(input)-1;
	}
    int toplam;
    int ekleme=0;

    for (int i = 0; i < sayi; i++)
    {
        ekleme += adim_sayisi_tutucu[i];
    }


    for(int i = 0; i<b; i++)
    {
		if((int)input[i]<127 && (int)input[i]>31)
        {
            toplam = (int)input[i]-32 + ekleme;
            if(toplam >94)
            {
                toplam = toplam % 95;
            }
            finalOutput[i] = (char)toplam+32;
        }
        else
        {
            finalOutput[i] = input[i];
        }
    }

}
//sezar
void CaesarCipherDe(int sayi)   // sezar decoding
{
	flag = 0;
	b = strlen(input);
	if(flag == 1)
	{
		b = strlen(input)-1;
	}

    int toplam;
    int ekleme=0;

    for (int i = 0; i < sayi; i++)
    {
        ekleme += adim_sayisi_tutucu[i];
    }

    for(int i = 0; i<b; i++)
    {
        if((int)input[i]<127 && (int)input[i]>31)
        {
            toplam = (int)input[i] -32 - ekleme;

            if(toplam <0)
            {
                toplam = toplam % 95;
                if(toplam == 0)
                    toplam = 0;
                else
                    toplam = toplam + 95;
            }
           finalOutput[i] = (char)toplam +32;

        }
        else
        {
            finalOutput[i] = input[i];
        }
    }

}
//sezar

//vigenere
void VigenereCipherEn(int sayi)  // vigenere encoding
{
	flag = 0;
	b = strlen(input);
	if(flag == 1)
	{
		b = strlen(input)-1;
	}

    int toplam;

    for(int j=0;j<sayi;j++)
    {
        int uzunluk = strlen(viegenere_adim_sayisi_tutucu[j]);

        for(int i = 0; i<b; i++)
        {
		    if((int)input[i]<127 && (int)input[i]>31)
            {
                toplam = (int)input[i]-32 + (int)viegenere_adim_sayisi_tutucu[j][i%uzunluk];
                if(toplam >94)
                {
                    toplam = toplam % 95;
                }
                finalOutput[i] = (char)toplam+32;
                input[i] = finalOutput[i];
            }
            else
            {
                finalOutput[i] = input[i];
            }
        }
    }
}

void VigenereCipherDe(int sayi)     // vigenere decoding
{
	flag = 0;
	b = strlen(input);
	if(flag == 1)
	{
		b = strlen(input)-1;
	}
    int toplam;

	for(int j=0;j<sayi;j++)
    {
		int uzunluk = strlen(viegenere_adim_sayisi_tutucu[j]);

		for(int i = 0; i<b; i++)
		{
			if((int)input[i]<127 && (int)input[i]>31)
			{
				toplam = (int)input[i] -32 - (int)viegenere_adim_sayisi_tutucu[j][i%uzunluk];

				if(toplam <0)
				{
					toplam = toplam % 95;
					if(toplam == 0)
					toplam = 0;
					else
					toplam = toplam + 95;
				}
				finalOutput[i] = (char)toplam +32;
				input[i] = finalOutput[i];
			}
			else
			{
				finalOutput[i] = input[i];
			}
		}
	}

}
