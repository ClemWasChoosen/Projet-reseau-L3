#include <stdint.h>
#include <stdio.h>

uint16_t set_nth_bit(int n, uint16_t m){
    // ou
    m |= (1 << (15-n));

    return m;
}

uint16_t get_nth_bit(int n, uint16_t m){
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



uint16_t encode_G(uint16_t m){
    int data[8]; 
    for(int i=0; i<8; i++){
        data[i] = get_nth_bit(i, m);
        // printf("%d\n", data[i]);
    }
    uint16_t encoded = m;
    printf("%d\n", (data[0] ^ data[1] ^ data[4] ^ data[6] ^ data[7]));
    encoded |= (data[1] ^ data[2] ^ data[3] ^ data[5] ^ data[6])<<7;
    encoded |= (data[2] ^ data[3] ^ data[4] ^ data[6] ^ data[7])<<6;
    encoded |= (data[0] ^ data[1] ^ data[7])<<5;
    encoded |= (data[0] ^ data[2] ^ data[3] ^ data[4] ^ data[5])<<4;
    encoded |= (data[1] ^ data[3] ^ data[4] ^ data[5] ^ data[6])<<3;
    encoded |= (data[2] ^ data[4] ^ data[5] ^ data[6] ^ data[7])<<2;
    encoded |= (data[0] ^ data[1] ^ data[4] ^ data[6] ^ data[7])<<1;
    encoded |= (data[0] ^ data[2] ^ data[3] ^ data[4] ^ data[7]);


    return encoded;
}


uint16_t cnt_bits(uint16_t m){
    int res = 0;
    for(int i=0; i<16; i++){
        res += get_nth_bit(i, m);
    }

    return res;
}


int main(int argc, char** argv){

    print_word(16 ,encode_G(0b0011100100000000));
    // printf("%d\n", cnt_bits(0b0011100100000000));

    return 0;
}



