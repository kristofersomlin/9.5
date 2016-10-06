#include <stdio.h>
#include <stdlib.h>

int forstaOrdet(const char *from, char *to) {  // PLOCKAR UR FÖRSTA ORDET UT A OCH GER TILL B
    int i=0;
    for (;!isspace(from[i]);i++){
        to[i]=from[i];
    }
    to[i]='\0';
    return 0;
}
int sistaOrdet(const char *from, char *to, int l) { // PLOCKAR UR SISTA ORDET UR A OCH GER TILL C
    int i=l-2,j=0;
    for (;!isspace(from[i]);i--,j++){
        to[j]=from[i];
    }
    to[j]='\0';
    return 0;
}
int baklanges(char *to, char *from, int l) {   // EFTERSOM C ÄR SKRIVET BAKLÄNGES SÅ BYTER VI PLATS PÅ DESSA
    int j=l-1;
    int i=0;
    to[l]='\0';
    for (;from[i] != '\0';i++,j--) {
        to[j]=from[i];
    }
    to[i]='\0';
    return 0;
}
int main()
{
    char a[100];
    char b[20];
    char c[20];
    printf("Skriv in en rad \n");
    fgets (a, 99, stdin);
    int l=strlen(a);
    printf("Längd på sträng: %d\n", strlen(a)-2);
    forstaOrdet(a,b);
    printf("Forsta ordet: %s\n", b);
    sistaOrdet(a,c,l);
    l=strlen(c);
    baklanges(b,c,l);
    printf("Sista ordet: %s\n", b);
    printf("Texten du skrev in:%s\n", a);
    return 0;
}
