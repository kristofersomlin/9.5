#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#define CS "\x1b[33;1m"                     // Startar en kod för att färga text.
#define CL "\x1b[33m"
#define CE "\x1b[0m"                        // Avslutar koden.
#if defined POSIX                           // HITTADE DENNA PÅ NÄTET, SÅ DET SKA FUNGERA PÅ LINUX
  #define CLEARSCR system ( "clear" )
#elif defined MSDOS || defined WIN32
  #define CLEARSCR system ( "cls" )
#endif

void pausa() {
    system("pause");
}
void fileDontExist() {
    printf("ERROR\t FILEN EXISTERAR INTE!\n\nVill du skapa filen betyg.txt?\nJa eller Nej?");
    char val[3];
    scanf("%s", val);
    val[0] = tolower(val[0]);
    if(val[0] == 'j') {
        FILE *makefile = fopen("betyg.txt","w");
    }
}
void tabort(char *a) {
    int i = strlen(a)-1;
    if (a[i] == '\n') {
        a[i] = '#';
        a[i+1] = '\0';
    }
}
void leggtill (int vad, int *antalVad, int *menyval2) {
    if (vad == 1) {
        printf("[0] För att avbryta\n\n");
        char temp[100];
        printf("Namn på elev? (Förnamn Efternamn)");
        fflush(stdin);          // Raderar allt som ligger i buffer.
        fgets(temp,100,stdin);  // Hämtar inmatning ifrån tangentbordet och lägger det i temp
        if (temp[0] != 0+'0') { // Ifall man får en 0'a gör ej detta!
            *antalVad+=1;
            char a[100]={'1','#',*antalVad + '0','#'};
            strcat(a, temp);
            FILE *infil = fopen("betyg.txt","a");
            fprintf(infil, "%s", a);
            fclose(infil);
        }
    }
    if (vad == 2) {
        printf(CS"[0] "CE"För att avbryta\n\n");
        char temp[100];
        printf("Namn på kurs?");
        fflush(stdin);
        fgets(temp,100,stdin);
        if (temp[0] != 0+'0') {
            *antalVad+=1;
            char a[100]={'2','#',*antalVad + '0','#'};
            strcat(a, temp);
            FILE *infil = fopen("betyg.txt","a");
            fprintf(infil, "%s", a);
            fclose(infil);
        }
    }
    if (vad == 3) {
        printf(CS"[0] "CE"För att avbryta\n\n");
        char temp[100];
        printf("Namn på prov?");
        fflush(stdin);
        fgets(temp,100,stdin);
        if (temp[0] != 0+'0') {
            *antalVad+=1;
            char a[100]={'3','#',*antalVad + '0','#'};
            strcat(a, temp);
            tabort(a);
            printf("Poäng för godkänt?");
            fflush(stdin);
            fgets(temp,100,stdin);
            strcat(a, temp);
            tabort(a);
            printf("Poäng för väl godkänt?");
            fflush(stdin);
            fgets(temp,100,stdin);
            strcat(a, temp);
            FILE *infil = fopen("betyg.txt","a");
            fprintf(infil, "%s", a);
            fclose(infil);
        }
    }
}
void lista (int vad) {
    FILE *infil = fopen("betyg.txt", "r");
    if (vad == 1) {
        char s[100];
        printf(CS"Lista över elever"CE"\n"CL"--------------------------------"CE"\n\n"CS"ID\tNAMN\n"CE);
        while(fgets(s,100,infil) != NULL) {
            if (s[0]==1+'0') {                  // EFTERSOM DET ÄR EN CHAR SÅ MÅSTE MAN PLUSSA 1 MED '0'.
                    for(int i=2; s[i]!= '\0';i++) {
                            if(s[i]=='#') {
                                printf("\t");
                            } else {
                            printf("%c",s[i]);
                            }
                    }
            }
        }
        pausa();
    }
    else if (vad == 2) {
        char s[100];
        printf(CS"Lista över kurser"CE"\n"CL"--------------------------------"CE"\n\n"CS"ID\tKURSNAMN\n"CE);
        while(fgets(s,100,infil) != NULL) {
            if (s[0]==2+'0') {                  // EFTERSOM DET ÄR EN CHAR SÅ MÅSTE MAN PLUSSA 1 MED '0'.
                    for(int i=2; s[i]!= '\0';i++) {
                            if(s[i]=='#') {
                                printf("\t");
                            } else {
                            printf("%c",s[i]);
                            }
                    }
            }
        }
        pausa();
    }
    else if (vad == 3) {
        char s[100];
        printf(CS"Lista över prov"CE"\n"CL"--------------------------------"CE"\n\n"CS"ID\tNAMN PÅ PROV\tG\tVG\n"CE);
        while(fgets(s,100,infil) != NULL) {
            if (s[0]==3+'0') {                  // EFTERSOM DET ÄR EN CHAR SÅ MÅSTE MAN PLUSSA 1 MED '0'.
                    for(int i=2,j=0; s[i]!= '\0';i++) {
                            if(s[i]=='#') {
                               if(j==1) {printf("\t");}
                                printf("\t");
                                j++;
                            } else {
                            printf("%c",s[i]);
                            }
                    }
            }
        }
        pausa();
    }
    fclose(infil);
}

int main()
{
    system("CHCP 1252");                                          // För att kunna skriva ut åäö
    int antalElever=0,antalKurser=0,antalProv=0;
    FILE *infil = fopen("betyg.txt", "r");
    char s[100];
    int menyval = 1, menyval2 = 1, menyval3 = 1;
    if (infil == NULL) { fileDontExist(); }                       // Kontrollerar om filen betyg.txt finns med hjälp av fileDontExist()
    else {
        while(fgets(s,100,infil) != NULL) {                       // Kontrollerar hur många elever, kurser och prov det finns för att sedan kunna
            if (s[0]==1+'0') {antalElever++;}                     // lägg till nya med ett id som är antal+1
            if (s[0]==2+'0') {antalKurser++;}
            if (s[0]==3+'0') {antalProv++;}
            }
        }
    while(menyval) {
        CLEARSCR;
        printf(CS"[1] "CE"Elever\n"CS"[2] "CE"Kurser\n"CS"[3] "CE"Prov\n"CS"[0] "CE"För att avsluta");
        scanf("%d", &menyval2);
        if(menyval2==0) { menyval=0; }
        while(menyval2){
            if(menyval2==1) {
                CLEARSCR;
                printf(CS"[1]"CE" Visa en lista på elever\n");
                printf(CS"[2]"CE" Lägg till elev\n");
                printf(CS"[0]"CE" För att backa\n");
                scanf("%d", &menyval3);
                if(menyval3==0) { menyval2=0; }
            }
            if(menyval2==2) {
                CLEARSCR;
                printf(CS"[1]"CE" Visa en lista på kurser\n");
                printf(CS"[2]"CE" Lägg till kurs\n");
                printf(CS"[0]"CE" För att backa\n");
                scanf("%d", &menyval3);
                if(menyval3==0) { menyval2=0; }
            }
            if(menyval2==3) {
                CLEARSCR;
                printf(CS"[1]"CE" Visa en lista på prov\n");
                printf(CS"[2]"CE" Lägg till prov\n");
                printf(CS"[0]"CE" För att backa\n");
                scanf("%d", &menyval3);
                if(menyval3==0) { menyval2=0; }
            }
            while(menyval3) {
                if(menyval2==1) {
                    if(menyval3==1){
                        CLEARSCR;
                        lista(1);
                        menyval3=0;
                    }
                    if(menyval3==2){
                        CLEARSCR;
                        leggtill(1, &antalElever, &menyval2);
                        menyval3=0;
                    }
                }
                if(menyval2==2) {
                    if(menyval3==1){
                        CLEARSCR;
                        lista(2);
                        menyval3=0;
                    }
                    if(menyval3==2){
                        CLEARSCR;
                        leggtill(2, &antalKurser, &menyval2);
                        menyval3=0;
                    }
                }
                if(menyval2==3) {
                    if(menyval3==1){
                        CLEARSCR;
                        lista(3);
                        menyval3=0;
                    }
                    if(menyval3==2){
                        CLEARSCR;
                        leggtill(3, &antalProv, &menyval2);
                        menyval3=0;
                    }
                }
            }
        }
    }
    printf("HARE GÖTT! HERRÅ!\n");
    return 0;
}
