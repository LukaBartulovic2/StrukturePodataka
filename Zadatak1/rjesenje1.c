#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[30];
    char lName[30];
    double bodovi;
} student;


int main() {

    FILE *fp = fopen("studenti.txt", "r");
    if (fp == NULL) {
        printf("gerska");
        return -1;
    }

    int brStudenata = 0;
    char a;

    while((a = fgetc(fp)) != EOF) {
        if (a == '\n') {
            brStudenata++;
        }
    }

    if (brStudenata == 0) {
        printf("greska");
        fclose(fp);
        return -2;
    }

    rewind(fp);

   student *pStudenti = (student *)malloc(brStudenata * sizeof(student));
   if (pStudenti == NULL) {
        printf("greska");
        fclose(fp);
        return -3;
   }

   double max_br_bodova = 0.0;

   for (int i = 0; i < brStudenata; i++) {
        fscanf(fp, "%s %s %lf", pStudenti[i].name, pStudenti[i].lName, &pStudenti[i].bodovi);
        if (pStudenti[i].bodovi > max_br_bodova) {
            max_br_bodova = pStudenti[i].bodovi;
        }
   }
    
    fclose(fp);

    for (int i = 0; i < brStudenata; i++) {
        double relativni_br_bodova = pStudenti[i].bodovi / max_br_bodova * 100.0;
        printf("%s %s %.2f %.2f%%\n", 
            pStudenti[i].name, 
            pStudenti[i].lName, 
            pStudenti[i].bodovi, 
       relativni_br_bodova);
        }

    free(pStudenti);
    
    return 0;

}

