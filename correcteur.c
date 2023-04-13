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


// int G[8][16]=(
//     1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
//     0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1,
//     0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
//     0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0,
//     0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0,
//     0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1,
//     0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1,
//     0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1
// );


uint16_t encode_G(uint16_t m){
    int data[8]; 
    for(int i=0; i<8; i++){
        data[i] = get_nth_bit(i, m);
    }
    uint16_t encoded = m;
    for(int j=8; j<16; j++){
        encoded |= (/*data1 XOR data2 XOR data3 XOR data4*/);
    }

}


int main(int argc, char** argv){



    return 0;
}



