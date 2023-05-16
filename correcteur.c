#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



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

uint8_t decode_poly(uint16_t m) {
    uint8_t syndrome = mod_poly(m);

    if (syndrome == 0) {
        return 1;
    } else {
        return 0;
    }
}



uint8_t syndromes[8] = {0b01110110,0b00111011,0b11000001,0b10111100,0b01011110,0b00101111,0b11001011,0b10111001};


uint8_t correct(uint16_t m) {
    uint8_t syndrome = mod_poly(m);
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


// unsigned char correct2errors(uint16_t m){
//     uint16_t temp = m;
//     uint8_t syndrome = mod_poly(m);
//     uint8_t correction = 0;
//     int i = 0;
//     int j = 1;

//     while (i < 7 && correction == 0){
//         while (j < 8 && correction == 0){
//             if(syndrome == (syndromes[i]^syndromes[j])){
//                 temp = chg_nth_bit(i, m);
//                 correction = chg_nth_bit(j, temp) >> 8;
//             }
//             j++;
//         }
//         i++;
//     }


//     return correction;
// }


unsigned char correct2errors(uint16_t m) {
    uint16_t temp = m;
    uint8_t syndrome = mod_poly(m);
    uint8_t correction = 0;

    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (syndrome == (syndromes[i] ^ syndromes[j])) {
                temp = chg_nth_bit(i, temp);
                temp = chg_nth_bit(j, temp);
                correction = temp >> 8;
                return (char) correction; // Return the corrected data immediately
            }
        }
    }

    // If no correction is found, fallback to the existing correct function
    correction = correct(m);
    return (char) correction;
}




int main(){

    uint16_t m = encode_poly(0b0000101100000000);
    // printf("%d\n", decode_poly(m));
    // print_word(16, m);
    // print_byte(8, mod_poly(m ^ 0b1000000000000000));

    // print_byte(8, mod_poly(0b1000000000000000));
    // print_byte(8, mod_poly(0b0010000000000000));
    // print_byte(8, mod_poly(0b1010000000000000));

    // uint16_t test = m ^ 0b1001000000000000;
    // print_word(16, test);
    // print_byte(8, correct2errors(test));




    FILE* file = fopen("corrupted_file_RL", "rb");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }


    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);



    uint16_t* encoded_data = (uint16_t*)malloc(file_size);
    if (encoded_data == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    fread(encoded_data, sizeof(uint16_t), file_size / sizeof(uint16_t), file);
    fclose(file);

    printf("Decoding the corrupted file:\n");

    // Decode and print the corrected data
    for (int i = 0; i < file_size / sizeof(uint16_t); i++) {
        uint16_t block = encoded_data[i];
        unsigned char corrected_data = correct2errors(block);
        printf("%c", corrected_data);
    }

    printf("\n");

    free(encoded_data);


    return 0;
}



