// Included modules ----------------------------------------------
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <math.h>
    #include "mesintoken.h"
    #include "mesinkar.h"
    #include <complex.h>

// Aesthetics Functions ----------------------------------------------
    #define MAX_LEN 128
    void print_image(char* filename);
    void print_image(char* filename)
    {
        FILE *fptr = NULL;
     
        if((fptr = fopen(filename,"r")) == NULL)
          {
              fprintf(stderr,"error opening %s\n",filename);
          }
        else
          {
              char read_string[MAX_LEN];
           
              while(fgets(read_string,sizeof(read_string),fptr) != NULL)
                  printf("%s",read_string);
          }
    }

// Functions & Procedures Declaration -------------------------------------------------------------------
    double complex result=0+0*I;

    double complex PlusMinusFunction(void);
    double complex MultDivFunction(void);
    double complex PowerFunction(void);
    double complex NegativeFunction(void);
    double complex NumParenthesesFunction(void);

    double complex MakeCMPLX(double a, double b){
      return (a + b * I);
    }

    void error()
        {
          if (isinf((double)result) || isnan((double)result)) 
            print_image("error2.txt");
          else
            print_image("error1.txt");
          exit(1);
        }

    void compare( char targetchar)
        { if (CToken.tkn==targetchar){
            //printf(" targetchar : %c \n",targetchar);
            ADVTOKEN();

          }
          else{
            //printf("ERROR AT compareING\n");
            error();
          }
        }
    double complex PlusMinusFunction(void)
    { 
        double complex temp = MultDivFunction();
        while (CToken.tkn=='+' || CToken.tkn =='-')
        { 
            if(CToken.tkn =='+')
            {
                compare('+');
                if(CToken.tkn != 'b' && CToken.tkn != '(' && CToken.tkn != ')' )
                  error();
                else
                  temp += MultDivFunction();
            }
            else
            {
                compare('-');
                if(CToken.tkn != 'b' && CToken.tkn != '(' && CToken.tkn != ')' )
                  error();
                else
                  temp -= MultDivFunction();
            }
        }
    //printf("temp at PlusMinusFunction : %f\n", temp);
        return temp;
    }

    double complex MultDivFunction(void)
    {
        double complex temp = PowerFunction();
        while (CToken.tkn =='*' || CToken.tkn =='/')
        {
            if(CToken.tkn =='*')
            {
                compare('*');
                if(CToken.tkn != 'b' && CToken.tkn != '(' && CToken.tkn != ')' )
                  error();
                else
                  temp *= PowerFunction();
            }
            else
            {
                compare('/');
                if(CToken.tkn != 'b' && CToken.tkn != '(' && CToken.tkn != ')' )
                  error();
                else
                  temp *= 1/PowerFunction();
            }

        }
        //printf("temp at MultDivFunction :%f\n", temp);
        return temp;
    }



    double complex PowerFunction(void)
    {
        double complex temp = NegativeFunction();
        while (CToken.tkn =='^')
        {
            compare('^');
            if(CToken.tkn != 'b' && CToken.tkn != '(' && CToken.tkn != ')' )
                error();
            else
            // printf ("The result progress is...  =  %.2f%+.2fi\n",creal(temp), cimag(temp));
                temp = cpow(temp,PowerFunction());
            // printf ("The result progress2 is...=  %.2f%+.2fi\n",creal(temp), cimag(temp));
        }
        //printf("temp at PowerFunction : %f\n", temp);
        return temp;
    }

    double complex NegativeFunction(void)
    { 
        double complex temp;
        if(CToken.tkn == '-'){

        compare('-');
        temp=(-1)*NumParenthesesFunction();
        if (creal(temp)==0){
          temp = MakeCMPLX(0,cimag(temp));
        }
        if (cimag(temp)==0){
          temp = MakeCMPLX(creal(temp),0);
        }
        //printf("temp at NegativeFunction : %f\n", temp);
        return temp;
        }
        temp=NumParenthesesFunction();
        //printf("temp at NegativeFunction : %f\n", temp);
        return temp;
    }

    double complex NumParenthesesFunction(void)
    { 
        double complex temp;
        if (CToken.tkn =='(')
            {
            //printf("MASUK!\n");
            compare('(');
            temp = PlusMinusFunction();
            compare(')');
            //CToken.tkn = CC;
            //printf("SELESAI!\n");
            }
        else if(CToken.tkn == 'i')
            {
            temp = MakeCMPLX(0,CToken.val);
            compare('i');
            }
        else if (CToken.tkn == 'b')
            {
            //printf("Proceed if2 : %c\n", CToken.tkn);
            temp = MakeCMPLX(CToken.val,0);
            ADVTOKEN();
            }
        else
            {
            //printf("ERROR AT NumParenthesesFunction : %c\n", CToken.tkn);
            error();
            }

        if (CToken.tkn == 'i')
            {
            compare('i');
            return MakeCMPLX(0,temp);
            }
        else
            {
            //printf("temp at NumParenthesesFunction : %f\n", temp);
            return temp;
            }
    }


//MAIN PROGRAM ----------------------------------------------------------------------------------------
    int main()
    {
        //INTERFACE LOAD : 
            print_image("mainmenu.txt");

        // Main Group :
        STARTTOKEN();
        result = PlusMinusFunction();
        //printf("CToken.tkn = %c\n",CToken.tkn);
        if ((CToken.tkn =='\n') && !isinf((double)result) && !isnan((double)result))  
            {
                print_image("result.txt");
                printf("<Result>    :   ");
                if (cimag(result)==0)
                    {
                      printf("%.2f\n",creal(result));
                    }
                else if (creal(result)==0)
                    {
                      if (cimag(result)==1)
                          {
                            printf("i\n");
                          }
                      else
                          {
                            printf("%.2fi\n",cimag(result));
                          }
                    }
                else
                {
                  if (cimag(result)==1)
                      {
                        printf("%.2f+i\n",creal(result));
                      }
                  else
                      {
                        printf("%.2f%+.2fi\n",creal(result), cimag(result));
                      }
                }
                print_image("result.txt");
                printf("\n");
            }
        else
            {
            //printf("ERROR AT MAIN\n");
            error();
            }
        return 0;
    }


