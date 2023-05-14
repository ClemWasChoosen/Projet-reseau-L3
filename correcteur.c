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


uint8_t dist_code_G(){

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
    int8_t distance = n; //init a val maximale

    for (int i = 0; i < k-1; i++) {
        for (int j = i + 1; j < k; j++) {
            int8_t diff = 0;
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


int main(int argc, char** argv){

    // print_word(16 ,encode_G(0b0011100100000000));
    // printf("%d\n", cnt_bits(0b0011100100000000));



    
    printf("%d\n", dist_code_G());

    return 0;
}



