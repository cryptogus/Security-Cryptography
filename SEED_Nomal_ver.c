#include <stdio.h>
#include <stdint.h>

typedef unsigned char byte;
typedef uint32_t word;

byte SBox1[256] = {
    169, 133, 214, 211, 84, 29, 172, 37,
        93, 67, 24, 30, 81, 252, 202, 99,
        40, 68, 32, 157, 224, 226, 200, 23,
        165, 143, 3, 123, 187, 19, 210, 238,
        112, 140, 63, 168, 50, 221, 246, 116,
        236, 149, 11, 87, 92, 91, 189, 1,
        36, 28, 115, 152, 16, 204, 242, 217,
        44, 231, 114, 131, 155, 209, 134, 201,
        96, 80, 163, 235, 13, 182, 158, 79,
        183, 90, 198, 120, 166, 18, 175, 213,
        97, 195, 180, 65, 82, 125, 141, 8,
        31, 153, 0, 25, 4, 83, 247, 225,
        253, 118, 47, 39, 176, 139, 14, 171,
        162, 110, 147, 77, 105, 124, 9, 10,
        191, 239, 243, 197, 135, 20, 254, 100,
        222, 46, 75, 26, 6, 33, 107, 102,
        2, 245, 146, 138, 12, 179, 126, 208,
        122, 71, 150, 229, 38, 128, 173, 223,
        161, 48, 55, 174, 54, 21, 34, 56,
        244, 167, 69, 76, 129, 233, 132, 151,
        53, 203, 206, 60, 113, 17, 199, 137,
        117, 251, 218, 248, 148, 89, 130, 196,
        255, 73, 57, 103, 192, 207, 215, 184,
        15, 142, 66, 35, 145, 108, 219, 164,
        52, 241, 72, 194, 111, 61, 45, 64,
        190, 62, 188, 193, 170, 186, 78, 85,
        59, 220, 104, 127, 156, 216, 74, 86,
        119, 160, 237, 70, 181, 43, 101, 250,
        227, 185, 177, 159, 94, 249, 230, 178,
        49, 234, 109, 95, 228, 240, 205, 136,
        22, 58, 88, 212, 98, 41, 7, 51,
        232, 27, 5, 121, 144, 106, 42, 154 };

byte SBox2[256] = {
    56, 232, 45, 166, 207, 222, 179, 184,
        175, 96, 85, 199, 68, 111, 107, 91,
        195, 98, 51, 181, 41, 160, 226, 167,
        211, 145, 17, 6, 28, 188, 54, 75,
        239, 136, 108, 168, 23, 196, 22, 244,
        194, 69, 225, 214, 63, 61, 142, 152,
        40, 78, 246, 62, 165, 249, 13, 223,
        216, 43, 102, 122, 39, 47, 241, 114,
        66, 212, 65, 192, 115, 103, 172, 139,
        247, 173, 128, 31, 202, 44, 170, 52,
        210, 11, 238, 233, 93, 148, 24, 248,
        87, 174, 8, 197, 19, 205, 134, 185,
        255, 125, 193, 49, 245, 138, 106, 177,
        209, 32, 215, 2, 34, 4, 104, 113,
        7, 219, 157, 153, 97, 190, 230, 89,
        221, 81, 144, 220, 154, 163, 171, 208,
        129, 15, 71, 26, 227, 236, 141, 191,
        150, 123, 92, 162, 161, 99, 35, 77,
        200, 158, 156, 58, 12, 46, 186, 110,
        159, 90, 242, 146, 243, 73, 120, 204,
        21, 251, 112, 117, 127, 53, 16, 3,
        100, 109, 198, 116, 213, 180, 234, 9,
        118, 25, 254, 64, 18, 224, 189, 5,
        250, 1, 240, 42, 94, 169, 86, 67,
        133, 20, 137, 155, 176, 229, 72, 121,
        151, 252, 30, 130, 33, 140, 27, 95,
        119, 84, 178, 29, 37, 79, 0, 70,
        237, 88, 82, 235, 126, 218, 201, 253,
        48, 149, 101, 60, 182, 228, 187, 124,
        14, 80, 57, 38, 50, 132, 105, 147,
        55, 231, 36, 164, 203, 83, 10, 135,
        217, 76, 131, 143, 206, 59, 74, 183 };
word round_constant[16] = {
             0x9e3779b9,
             0x3c6ef373,
             0x78dde6e6,
             0xf1bbcdcc,
             0xe3779b99,
             0xc6ef3733,
             0x8dde6e67,
             0x1bbcdccf,
             0x3779b99e,
             0x6ef3733c,
             0xdde6e678,
             0xbbcdccf1,
             0x779b99e3,
             0xef3733c6,
             0xde6e678d,
             0xbcdccf1b };

word G_fun(word x) {
    
    word y[4] = { 0, };
    word z[4] = { 0, };
    word m[4] = { 0xfc, 0xf3, 0xcf, 0x3f };

   
    y[0] = SBox1[((x) & 0xff)];
    y[1] = SBox2[((x) >> 8) & 0xff];
    y[2] = SBox1[((x) >> 16) & 0xff];
    y[3] = SBox2[((x) >> 24) & 0xff];

    z[3] = (y[0] & m[3]) ^ (y[1] & m[0]) ^ (y[2] & m[1]) ^ (y[3] & m[2]); // 0x3f 0xfc 0xf3 0xcf
    z[2] = (y[0] & m[2]) ^ (y[1] & m[3]) ^ (y[2] & m[0]) ^ (y[3] & m[1]); // 0xcf 0x3f 0xfc 0xf3
    z[1] = (y[0] & m[1]) ^ (y[1] & m[2]) ^ (y[2] & m[3]) ^ (y[3] & m[0]); // 0xf3 0xcf 0x3f 0xfc 
    z[0] = (y[0] & m[0]) ^ (y[1] & m[1]) ^ (y[2] & m[2]) ^ (y[3] & m[3]); // 0xfc 0xf3 0xcf 0x3f

    return (z[0] | (z[1] << 8) | (z[2] << 16) | (z[3] << 24));
}

void Key_gen(word Key[], word RoundKey[][2]) {

    word A, B;
    
    for (int i = 0; i < 16; i++) {

        A = Key[0] + Key[2] - round_constant[i];
        B = Key[1] - Key[3] + round_constant[i];

        A = G_fun(A);
        B = G_fun(B);
        
        RoundKey[i][0] = A;
        RoundKey[i][1] = B;

        if (i % 2 == 0) {
            A = Key[0];
            Key[0] = (Key[0] >> 8) | (Key[1] << 24);
            Key[1] = (Key[1] >> 8) | (A << 24);
             
        }
        else {
            A = Key[2];
            Key[2] = (Key[2] << 8) | (Key[3] >> 24);
            Key[3] = (Key[3] << 8) | (A >> 24);
            
        }
    }
}

void F_fun(word C, word D, word K0, word K1, word *E, word *F) {
    
    word First = 0;
    word Second = 0;

    First = (C ^ K0) ^ (D ^ K1);
    First = G_fun(First);
    Second = First;
    First = (First + (C ^ K0)) & 0xffffffff;
    First = G_fun(First);
    Second = (Second + First) & 0xffffffff;
    Second = G_fun(Second);
    *F = Second;
    *E = (First + Second) & 0xffffffff;
    
}

void SEED_Enc(word* Plaintext, word* Key, word* Ciphertext) {
    
    word RK[16][2] = { 0, };
    word state[4] = { 0, };
    Key_gen(Key, RK);
   /* for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%08x ", RK[i][j]);
        }
        printf("\n");
    }*/
    //1Round ~ 15Round
    state[0] = Plaintext[0];
    state[1] = Plaintext[1];
    state[2] = Plaintext[2];
    state[3] = Plaintext[3];
    word A = 0, B = 0, C = 0, D = 0;
    for (int i = 0; i < 15; i++) {
        C = state[2];
        D = state[3];
        
        F_fun(state[2], state[3], RK[i][0], RK[i][1], &A, &B);
        state[2] = A ^ state[0];
        state[3] = B ^ state[1];
        state[0] = C;
        state[1] = D;
        
       /* 
        for (int j = 0; j < 4; j++) {
            printf("%08x ", state[j]);
        }
        printf("\n");*/
    }
    Ciphertext[2] = state[2];
    Ciphertext[3] = state[3];
    F_fun(state[2], state[3], RK[15][0], RK[15][1], &A, &B);
    Ciphertext[0] = A ^ state[0];
    Ciphertext[1] = B ^ state[1];

    

}
void SEED_Dec(word* Plaintext, word* Key, word* Ciphertext) {

    word RK[16][2] = { 0, };
    word state[4] = { 0, };
    Key_gen(Key, RK);
    /* for (int i = 0; i < 16; i++) {
         for (int j = 0; j < 2; j++) {
             printf("%08x ", RK[i][j]);
         }
         printf("\n");
     }*/
     //1Round ~ 15Round
    state[0] = Plaintext[0];
    state[1] = Plaintext[1];
    state[2] = Plaintext[2];
    state[3] = Plaintext[3];
    word A = 0, B = 0, C = 0, D = 0;
    for (int i = 0; i < 15; i++) {
        C = state[2];
        D = state[3];

        F_fun(state[2], state[3], RK[15 -i][0], RK[15 - i][1], &A, &B);
        state[2] = A ^ state[0];
        state[3] = B ^ state[1];
        state[0] = C;
        state[1] = D;

        /*
         for (int j = 0; j < 4; j++) {
             printf("%08x ", state[j]);
         }
         printf("\n");*/
    }
    Ciphertext[2] = state[2];
    Ciphertext[3] = state[3];
    F_fun(state[2], state[3], RK[0][0], RK[0][1], &A, &B);
    Ciphertext[0] = A ^ state[0];
    Ciphertext[1] = B ^ state[1];



}
byte inv_SBox1[256] = { 0, };
byte inv_SBox2[256] = { 0, };
//G의 역함수
word invG_fun(word x) {
    byte X[4] = { 0, };
    byte X1[4] = { 0, };
    byte A = 0;
    byte B = 0;
    byte C = 0;
    byte D = 0;

    for (int k = 0; k < 256; k++) {
        inv_SBox1[SBox1[k]] = k;
        inv_SBox2[SBox2[k]] = k;
    }
    
    X1[0] = x & 0xff;
    X1[1] = (x >> 8) & 0xff;
    X1[2] = (x >> 16) & 0xff;
    X1[3] = (x >> 24) & 0xff;

    A = X1[1] ^ X1[2] ^ X1[3];
    X[0] = A & 0x03;
    X[1] = A & 0x0c;
    X[2] = A & 0x30;
    X[3] = A & 0xc0;

    B = X1[0] ^ X1[2] ^ X1[3];
    X[0] ^= B & 0x0c;
    X[1] ^= B & 0x30;
    X[2] ^= B & 0xc0;
    X[3] ^= B & 0x03;

    C = X1[0] ^ X1[1] ^ X1[3];
    X[0] ^= C & 0x30;
    X[1] ^= C & 0xc0;
    X[2] ^= C & 0x03;
    X[3] ^= C & 0x0c;

    D = X1[0] ^ X1[1] ^ X1[2];
    X[0] ^= D & 0xc0;
    X[1] ^= D & 0x03;
    X[2] ^= D & 0x0c;
    X[3] ^= D & 0x30;

    X[0] = inv_SBox1[X[0]];
    X[1] = inv_SBox2[X[1]];
    X[2] = inv_SBox1[X[2]];
    X[3] = inv_SBox2[X[3]];

    return ((X[3] << 24) | (X[2] << 16) | (X[1] << 8) | X[0]);

}
int main() {
    /***********************test vector*********************/
    word Key[4] = { 0, };
    //word Plaintext[4] = { 0x00010203, 0x04050607, 0x08090A0B, 0x0C0D0E0F };
    //word Ciphertext[4] = { 0, };
    //Little Endian
    //03 02,01 00 07 06 05 04 0B 0A 09 08 0F 0E 0D 0C
    //byte Plaintext[16] = { 0x03, 0x02, 0x01, 0x00, 0x07, 0x06, 0x05, 0x04, 0x0B, 0x0A, 0x09, 0x08, 0x0F ,0x0E, 0x0D, 0x0C };
   
    
    byte Ciphertext[16] = { 0, };
    //e0 c6 ba 5e 68 16 4e 05 cc f1 af 19 db 6c 34 6d
    //SEED_Enc(Plaintext, Key, Ciphertext);
    //SEED_Dec(Ciphertext, Key, Plaintext);
    word A = 0;
    word B = 0;
    word C = 0;
   /*G의 역함수 테스트*/
    B = G_fun(A);
    printf("%08x ", B);
    C = invG_fun(B);
    printf("%08x ", C);
    for(int i = 0; i< 16; i++)
        printf("%02x ", Ciphertext[i]);
}
