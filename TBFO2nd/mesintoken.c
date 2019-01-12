/* File: mesintoken.h */
/* Definisi Mesin Token: Model Akuisisi Versi I */


#include "mesintoken.h"
#include "mesinkar.h"
#include <stdio.h>
#include "boolean.h"
#include <stdlib.h>
#include <math.h>


boolean EndToken;
Token CToken;
int fraction;
boolean dotExist;

void IgnoreBlank(){
    while ((CC== BLANK) && (CC != MARK)){
        ADV();
    }
}
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTTOKEN(){
    IgnoreBlank();
    START();
    IgnoreBlank();
    if (CC == MARK)
        EndToken = true;
    else{
        EndToken = false;
        SalinToken();
    }
}
/* I.S. : CC sembarang
   F.S. : EndToken = true, dan CC = MARK;
          atau EndToken = false, CToken adalah Token yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir Token */

void ADVTOKEN(){
    ADV();
    IgnoreBlank();
    /*if (CC == MARK){
        EndToken = true;}
    else{*/
        //ADV();
    SalinToken();
    IgnoreBlank();
}

/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CToken adalah Token terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, maka EndToken = true
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinToken(){
    CToken.val = 0;
    fraction = 0;
    dotExist = false;
    //printf("SalinToken CC = %c\n", CC);
		if (CC == '+'){
			CToken.tkn = '+';
			CToken.val = -1;
		}
		else if (CC == '-'){
			CToken.tkn = '-';
			CToken.val = -1;
		}
		else if (CC == '/'){
			CToken.tkn = '/';
			CToken.val = -1;
		}
		else if (CC == '*'){
			CToken.tkn = '*';
			CToken.val = -1;
		}
		else if (CC == '^'){
			CToken.tkn = '^';
			CToken.val = -1;
		}
    else if (CC == '('){
      CToken.tkn = '(';
      CToken.val = -1;
    }
    else if (CC == ')'){
      CToken.tkn = ')';
      CToken.val = -1;
    }
    else if (CC == '\n'){
      CToken.tkn = '\n';
      CToken.val = -1;
    }
    else if (CC=='i'){
      CToken.tkn='i';
      CToken.val=1;
    }
		else if (CC >= '0' && CC <= '9' ){
      CToken.tkn = 'b';
      for(;;){
          if (CC == '.'){
            if (dotExist){
              printf("SYNTAX ERROR!\n");
              exit(1);
              }
            else{
              //CToken.tkn = '.';
              dotExist = true;
              }
          IgnoreBlank();
          ADV();
          IgnoreBlank();
          }
          else{
            //printf("CC = %c\n", CC);
            if (!dotExist){
        			CToken.val = (CToken.val *10) + (CC-'0');
              //printf("1st method : %f\n", CToken.val);
              }
            else    {
                    fraction ++;
                    //printf("2nd Ctoken : %f\n", CToken.val);
                    //printf("2nd : %f\n", (CC-'0')/(10.0*fraction));
                    CToken.val = CToken.val + ((CC-'0')/(pow(10.0,fraction)));
                    //printf("2nd Ctoken : %f\n", CToken.val);
                    }

          //printf("CToken.val = %f\n", CToken.val);
          IgnoreBlank();
          ADV();
          IgnoreBlank();
          //printf("(%c) compared to (BLANK)\n", CC);
          if ( CC== MARK || CC == BLANK || !((CC >= '0' && CC <= '9') || CC == '.')) {
              //printf("BACKCHAR CC = %c\n", CC);
              BACKCHAR();
              break;
              }
          }
      }
  }
  //printf("tkn: %c ; val : %f\n", CToken.tkn, CToken.val);
}
/* Mengakuisisi Token dan menyimpan hasilnya dalam CToken
   I.S. : CC adalah karakter pertama dari Token
   F.S. : CToken berisi Token yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
