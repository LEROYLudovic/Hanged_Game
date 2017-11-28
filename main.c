#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include <string.h>
#include "dico.h"

#define TENTATIVE 10
#define TRUE 1
#define FALSE 0

int main(int argc, char* argv[])
{
    char secretWord[100] = {0};
    char lettre = 0;
    int *lettreDuMot= NULL; //tableau ou chaque case correspond � une lettre du mot
    long coupsRestants = TENTATIVE;
    long i=0;
    long tailleMot=0;

    printf("Jeu du Pendu | Version 0.1\n");
    printf("Wesh Alors, wesh alors !");
    printf("\nQuel est le mot petit singe? ");

    if (!piocherMot(secretWord))
        exit(0);

    tailleMot = strlen(secretWord);

    lettreDuMot = malloc(tailleMot * sizeof(int)); // On alloue dynamiquement le tableau lettreTrouvee (dont on ne connaissait pas la taille au d�part)
    if (lettreDuMot == NULL)
        exit(0);
    for (i = 0 ; i < tailleMot ; i++)
        lettreDuMot[i] = 0;

    while (coupsRestants != 0 && !gagne(lettreDuMot, tailleMot))
    {
        printf("\n\nIl te reste %d essai%s :\n\n ", coupsRestants, coupsRestants<2 ? "": "s");

        // On affiche le mot secret en masquant les lettres non trouv�es
        for (i = 0 ; i < tailleMot ; i++)
        {
            if (lettreDuMot[i])
                printf("%c", secretWord[i]);
            else
                printf("_ "); // Sinon, on affiche une �toile pour les lettres non trouv�es

        }
        printf("\n\nSaisis une lettre : ");
        lettre = litLeCar();
        printf("\n\n\n ");
        if(!rechercheLettre(lettre,secretWord,lettreDuMot))
        {
            coupsRestants--;
        }
    }
    if (gagne(lettreDuMot, tailleMot))
        printf("\n\nGagne ! Le mot secret etait bien : %s, gros chien va\n\n", secretWord);
    else
        printf("\n\nPerdu fdp ! Le mot secret etait : %s\n\n", secretWord);

    free(lettreDuMot); // On lib�re la m�moire allou�e manuellement (par malloc)
    return 0;
}


int rechercheLettre(char lettre, char motSecret[], int lettreTrouvee[])
{
    int i = 0;
    int bonneLettre = 0;
    // On parcourt motSecret pour v�rifier si la lettre propos�e y est
    for (i = 0 ; motSecret[i] != '\0' ; i++)
    {
        if (lettre == motSecret[i]) // Si la lettre y est
        {
            bonneLettre = 1; // On m�morise que c'�tait une bonne lettre
            lettreTrouvee[i] = 1; // On met � 1 la case du tableau de bool�ens correspondant � la lettre actuelle
        }
    }
    return bonneLettre;
}

char litLeCar()
{
    char caractere = 0;
    caractere = getchar();//on lit le premier caract�re
    caractere = toupper(caractere);//on met en maj
    while (getchar() != '\n');//on lit les autres caracteres pour effacer
    return caractere;
}

int gagne(int lettreTrouvee[], long tailleMot)
{
    int i = 0;
    int joueurGagne = 1;
    for (i = 0 ; i < 6 ; i++)
    {
        if (lettreTrouvee[i] == 0)
            joueurGagne = 0;
    }
    return joueurGagne;
}
