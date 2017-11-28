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
    int *lettreDuMot= NULL; //tableau ou chaque case correspond à une lettre du mot
    long coupsRestants = TENTATIVE;
    long i=0;
    long tailleMot=0;

    printf("Jeu du Pendu | Version 0.1\n");
    printf("Wesh Alors, wesh alors !");
    printf("\nQuel est le mot petit singe? ");

    if (!piocherMot(secretWord))
        exit(0);

    tailleMot = strlen(secretWord);

    lettreDuMot = malloc(tailleMot * sizeof(int)); // On alloue dynamiquement le tableau lettreTrouvee (dont on ne connaissait pas la taille au départ)
    if (lettreDuMot == NULL)
        exit(0);
    for (i = 0 ; i < tailleMot ; i++)
        lettreDuMot[i] = 0;

    while (coupsRestants != 0 && !gagne(lettreDuMot, tailleMot))
    {
        printf("\n\nIl te reste %d essai%s :\n\n ", coupsRestants, coupsRestants<2 ? "": "s");

        // On affiche le mot secret en masquant les lettres non trouvées
        for (i = 0 ; i < tailleMot ; i++)
        {
            if (lettreDuMot[i])
                printf("%c", secretWord[i]);
            else
                printf("_ "); // Sinon, on affiche une étoile pour les lettres non trouvées

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

    free(lettreDuMot); // On libère la mémoire allouée manuellement (par malloc)
    return 0;
}


int rechercheLettre(char lettre, char motSecret[], int lettreTrouvee[])
{
    int i = 0;
    int bonneLettre = 0;
    // On parcourt motSecret pour vérifier si la lettre proposée y est
    for (i = 0 ; motSecret[i] != '\0' ; i++)
    {
        if (lettre == motSecret[i]) // Si la lettre y est
        {
            bonneLettre = 1; // On mémorise que c'était une bonne lettre
            lettreTrouvee[i] = 1; // On met à 1 la case du tableau de booléens correspondant à la lettre actuelle
        }
    }
    return bonneLettre;
}

char litLeCar()
{
    char caractere = 0;
    caractere = getchar();//on lit le premier caractère
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
