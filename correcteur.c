#include <stdint.h>
#include <stdio.h>




uint16_t set_nth_bit(int n, uint16_t m){
    // ou
    m |= (1 << (15-n));

    return m;
}

uint16_t get_nth_bit(int n, uint16_t m){    //pour n=0 n->15 : de gauche à droite
    // et
    return (m >> (15-n)) & 1;
}

uint16_t chg_nth_bit(int n, uint16_t m){
    // xor
    m ^= (1 << (15-n));
    
    return m;
}

void print_word(int k, uint16_t m){
    for(int i=0; i<k; i++){
        printf("%d", get_nth_bit(i, m));
    }
    printf("\n");
}

void print_byte(int k, uint8_t m){
    for(int i=0; i<k; i++){
        printf("%d", (m >> (7-i) & 1));
    }
    printf("\n");
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




uint16_t cnt_bits(uint16_t m){
    int res = 0;
    for(int i=0; i<16; i++){
        res += get_nth_bit(i, m);
    }

    return res;
}


uint16_t dist_code_G(){

    int G [8][16] ={{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0},
                {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1},
                {0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
                {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0},
                {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0},
                {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1},
                {0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1}
                };

    int k = 8;
    int n = 16;
    uint16_t distance = n; //init a val maximale

    for (int i = 0; i < k-1; i++) {
        for (int j = i + 1; j < k; j++) {
            uint16_t diff = 0;
            for (int l = 0; l < n; l++) {
                if (G[i][l] != G[j][l]) {
                    diff++;
                }
            }
            if (diff < distance) {
                distance = diff;
            }
        }
    }

    if(distance == 4){
        return 1;
    }else{
        return 0;
    }
}



uint8_t mod_poly(uint16_t m) {
    uint16_t polynomial = 0b110111001; // P(X) = X^8 + X^7 + X^5 + X^4 + X^3 + 1
    uint16_t reste = m;

    for (int i = 15; i >= 8; i--) {
        if (get_nth_bit((15-i), reste)) {
            reste ^= (polynomial << (i-8));
            // print_word(16, reste);
        }
    }
    
    return (uint8_t)(reste);
}


uint16_t encode_poly(uint16_t m){
    return m |= mod_poly(m);
}

uint8_t decode_poly(uint16_t m){
    uint8_t test = (uint8_t)(m >> 8);
    return test;
}


uint8_t syndromes[8] = {0b01110110,0b00111011,0b11000001,0b10111100,0b01011110,0b00101111,0b11001011,0b10111001};


uint8_t correct(uint16_t m) {
    uint8_t syndrome = mod_poly(m); // Calcul du syndrome
    uint8_t correction = 0;
    int i = 0;
    while (i < 8 && correction == 0) {
        if(syndrome == syndromes[i]){
            correction = chg_nth_bit(i, m) >> 8;

        }
        i++;
    }
    
    return correction;
}


unsigned char correct2errors(uint16_t m){

    return '\0';
}



int main(/*int argc, char** argv*/){

    // uint16_t m = encode_poly(0b0000101100000000);
    // print_word(16, m);
    // print_byte(8, mod_poly(m ^ 0b1000000000000000));

    // print_byte(8, mod_poly(0b1000000000000000));
    // print_byte(8, mod_poly(0b0010000000000000));
    // print_byte(8, mod_poly(0b1010000000000000));




    return 0;
}



