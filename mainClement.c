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

uint16_t cnt_bits(uint16_t m){
    int res = 0;
    for(int i=0; i<16; i++){
        res += get_nth_bit(i, m);
    }

    return res;
}

uint16_t encode_G(uint16_t m){
    uint16_t data[8];
    uint16_t result = m >> 8;
    for (int i=0; i<8; i++){
        data[i] = get_nth_bit(i, m);
    }
    
    result = result << 1;
    result |= data[2]^data[3]^data[6]^data[7];
    result = result << 1;
    result |= data[0]^data[2]^data[4]^data[6];
    result = result << 1;
    result |= data[0]^data[1]^data[3]^data[5]^data[7];
    result = result << 1;
    result |= data[0]^data[1]^data[3]^data[4]^data[7];
    result = result << 1;
    result |= data[1]^data[3]^data[4]^data[5]^data[6]^data[7];
    result = result << 1;
    result |= data[0]^data[3]^data[4]^data[5];
    result = result << 1;
    result |= data[0]^data[1]^data[4]^data[5]^data[6];
    result = result << 1;
    result |= data[1]^data[2]^data[5]^data[6]^data[7];
    return result;
}

/**
 * Cette fonction permet de savoir si la distance du code de Hamming représentée
 * par G est égale à 4 ou non. Pour ce faire, on a pris toutes les combinaisons
 * du code de G. Ensuite, on vérifie tous les mots distincts et si il y 
 * Suite à écrire
 */ 
uint8_t dist_code_G() {
    // Tableau contenant les 16 mots du code G sous forme de variables Ob16bits
    uint16_t words[16] = {0b0000000000000000, 0b0000000011111111, 0b0000111100001111, 0b0011001100110011,
                          0b0101010101010101, 0b1010101010101010, 0b1100110011001100, 0b1111000011110000,
                          0b0000000000111111, 0b0000111100000000, 0b0000000011110000, 0b0000000000001111,
                          0b0011000000110011, 0b0000110011000000, 0b0000001100001100, 0b0000000000000011};
    
    // Double boucle pour parcourir chaque combinaison de deux mots distincts
    for (int i = 0; i < 15; i++) {
        for (int j = i+1; j < 16; j++) {
            // Calcul de la distance de Hamming entre les deux mots
            uint8_t dist = cnt_bits(words[i] ^ words[j]);
            // Si la distance est inférieure à 4, le code G n'a pas une distance de Hamming de 4
            if (dist < 4) {
                return 0;
            }
        }
    }
    
    // Si toutes les combinaisons ont une distance de Hamming de 4, le code G a une distance de Hamming de 4
    return 1;
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


	printf("Somme des bits à 1 sur le mot 0b0011100100000000:");
	printf("%d\n", cnt_bits(0b0011100100000000));

	printf("Retour de la fonction encode_G: ");
	print_word(16 ,encode_G(0b0011100100000000));
	// printf("%d\n", cnt_bits(0b0011100100000000));


	return 0;
}
