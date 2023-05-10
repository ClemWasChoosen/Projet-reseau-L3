#include <stdio.h>
#include <stdint.h>

/**
 * Fonction utile pour afficher un nombre binaire sous la forme de short
 * (Fonction récupéré de Stack Overflow)
 */
void afficherBinaire(short num, int retLigne) {
    int i;
	printf("0b");
    for (i = 15; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
	if (retLigne) {
		printf("\n");
	}
}

/**
 * Cette fonction commence par calculer l'emplacement du bit à changer 
 * (avec short x = .. et (x << (15 - n))) ensuite on réalise l'opération 
 * OR avec le code m passé en paramètre
 */
uint16_t set_nth_bit(int n, uint16_t m) {
	short x = 0b0000000000000001; 
    return (m | (x << (15 - n)));
}

/**
 * Pour réaliser ceci, on vient faire un décalage vers le droite de 15 - n, 
 * ce qui permet de mettre le bit que l'on veut à sur le bit de poid faible 
 * (tout à droite). Ensuite avec '& 1', on vient récuperer uniquement le bit 
 * voulu en mettant à 0 les autres bits.
 */
uint16_t get_nth_bit(int n, uint16_t m) {
    return (m >> (15 - n)) & 1;
}

/**
 * Pour changer le bit voulu, on va simplement faire un décalage vers la gauche
 * pour avoir x avec le bit à l'emplacement où l'on veut à 1 les autres bits à 0.
 * Ensuite on fait une opération arithmétique OU exclusif pour retourner 
 * le message m avec uniquement le bit à l'emplacement n changé en 1 ou 0.
 */
uint16_t chg_nth_bit(int n, uint16_t m) {
	short x = 0b0000000000000001;
    return m ^ (x << (15 - n));
}

/**
 * Cette fonction est inspirées de la fonction afficherBinaire() développé plus 
 * haut sauf qu'on affiche uniquement jusqu'à la valeur k.
 */
void print_word(int k, uint16_t m) {
    printf("0b");
    for (int i = 15; i >= 16 - k; i--) {
        printf("%d", get_nth_bit(i, m));
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
	/* Cette partie sert a tester les premières fonctions du projet */
	uint16_t m = 0b0000000000000001;
	printf("Affichage du message de base : ");
	afficherBinaire(m, 1);
	printf("Retour de la fonction set_nth_bit : ");
	afficherBinaire(m = set_nth_bit(3, m), 1);

	printf("Retour de la fonction get_nth_bit: ");
	printf("%d\n", get_nth_bit(15, m));

	printf("Retour de la fonction chg_nth_bit: ");
	afficherBinaire(chg_nth_bit(3, m), 1);
	/* ################### */

	return 0;
}
