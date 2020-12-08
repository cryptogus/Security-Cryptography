#include <stdio.h>																		  /**************************주의*****************************/
#include <string.h>																		  //암호화연산들은  무조건 padding을 했다는 가정하에 코드를 짬.
#include <stdlib.h>																		  //
#include <time.h>																		  //
																						  //
int Byte;

//CTR모드는 따로 key, IV test vector가 있다 , vector참고 사이트https://www.cnblogs.com/shangdawei/p/4589924.html

unsigned char key[16] = { 0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c };
unsigned char IV[16] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f };

/////////////////////////////////ECB모드 test vetor////////////////////////////////////////////////////////////
unsigned char ECB_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char ECB_CipherText[16] = { 0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97 };

/////////////////////////////CBC모드 test vector////////////////////////////////
unsigned char CBC_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char CBC_CipherText[16] = { 0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d };

///////////////////////////////CFB TEST VECTOR////////////////////////////////////////
unsigned char CFB_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char CFB_CipherText[16] = { 0x3b,0x3f,0xd9,0x2e,0xb7,0x2d,0xad,0x20,0x33,0x34,0x49,0xf8,0xe8,0x3c,0xfb,0x4a };

///////////////////////////////OFB test vector/////////////////////////////////////////////////////
unsigned char OFB_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char OFB_CipherText[16] = { 0x3b,0x3f,0xd9,0x2e,0xb7,0x2d,0xad,0x20,0x33,0x34,0x49,0xf8,0xe8,0x3c,0xfb,0x4a };


///////////////////////////////////CTR모드의 TEST Vector//////////////////////////////////////////////////////////////
unsigned char key_ctr[16] = { 0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c };		 
unsigned char IV_ctr[16] = { 0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff };
unsigned char CTR_plainText[16] = { 0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a };
unsigned char CTR_CipherText[16] = { 0x87,0x4d,0x61,0x91,0xb6,0x20,0xe3,0x26,0x1b,0xef,0x68,0x64,0x99,0x0d,0xb6,0xce };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************패딩 규격*************************/
unsigned char* PKCS_7(unsigned char* text) {


	//////추가할 바이트 수/////////////
	unsigned char pad;
	pad = 16 - (Byte % 16);

	///////////////////////////////////
	unsigned char* test1 = malloc(pad + Byte);

	memcpy(test1, text, Byte);

	for (int i = Byte; i < Byte + pad; i++) {
		test1[i] = pad;
	}
	printf("패딩 : ");
	for (int i = 0; i < Byte + pad; i++) {
		printf("%x ", test1[i]);
	}
	printf("\n");
	return test1;
}

unsigned char* IEC(unsigned char* text) {

	unsigned char pad;
	pad = 16 - (Byte % 16);

	unsigned char* test1 = malloc(pad + Byte);

	memcpy(test1, text, Byte);
	test1[Byte] = 0x80;
	for (int i = Byte + 1; i < Byte + pad; i++) {
		test1[i] = 0x00;
	}
	printf("패딩 : ");
	for (int i = 0; i < Byte + pad; i++) {
		printf("%x ", test1[i]);
	}

	printf("\n");
	return test1;

}

unsigned char* ANSI(unsigned char* text) {

	unsigned char pad;
	pad = 16 - (Byte % 16);

	unsigned char* test1 = malloc(pad + Byte);
	memcpy(test1, text, Byte);

	for (int i = Byte; i < Byte + pad; i++) {
		test1[i] = 0x00;
	}

	test1[Byte + pad - 1] = pad;

	printf("패딩 : ");
	for (int i = 0; i < Byte + pad; i++) {
		printf("%x ", test1[i]);
	}
	return test1;

}

unsigned char* ISO(unsigned char* text) {

	unsigned char pad;

	//////추가할 바이트 수/////////////

	pad = 16 - (Byte % 16);
	unsigned char* test1 = malloc(pad + Byte);

	///////////////////////////////////
	memcpy(test1, text, Byte);


	for (int i = Byte; i < Byte + pad; i++) {
		srand(time(NULL) * i); //랜덤값을 다르게 해주기 위해
		test1[i] = rand() % 256;
	}
	test1[Byte + pad - 1] = pad;
	printf("패딩 : ");
	for (int i = 0; i < Byte + pad; i++) {
		printf("%x ", test1[i]);
	}
	return test1;
}
void Del(unsigned char* text) { //PKCS_7, ANSI, ISO, IEC 규격 패딩 제거


	//////제거할 바이트 수/////////////
	unsigned char del;
	del = text[15]; // 암호문 decrypt이후 가장 끝자리 패딩된 바이트 크기

	////////////////////////////////////////


	////IEC padding 제거시 사용할 구문 - 이 패딩은 가장 끝이 0이기때문에 0이 아닌 패딩들은 사용되지 않음
	for (int a = 0; ; a++) {																	   //
		if (text[15 - a] == 0)																   //
			del++;																				   //
		else																					   //
			break;																				   //
		if (text[15 - a] == 0x80) {															   //
			del++;																				   //
			break;																				   //
		}																						   //
	}																						   //
	////////////////////////////////////////////////////////////////////////////////////////////////

	unsigned char* test1 = malloc(15 - del);

	memcpy(test1, text, Byte - del);


	for (int i = 0; i < Byte - del; i++) {
		printf("%x ", test1[i]);

	}
}



void ECB(unsigned char* text);
void CBC_en(unsigned char* text);
void CBC_de(unsigned char* text);
void OFB(unsigned char* text);
void CFB(unsigned char* text);
void CTR(unsigned char* text);
void AES_En(unsigned char cipherText[16], unsigned char plainText[16], unsigned char key[16]);
void AES_De(unsigned char cipherText[16], unsigned char plainText[16], unsigned char key[16]);

int main() {
	printf("입력할 TEXT의 BYTE크기 입력(test vector는 16 byte) : ");
	scanf_s("%hd", &Byte);
																														 
	/*unsigned char* plaintext = (char*)malloc(sizeof(char) * Byte);														 
	printf("평문은 16진수로 입력 : ");																					 
	for (int i = 0; i < Byte; i++) {																					 
																														 
		scanf_s("%hhx", &plaintext[i]);																					 
	}
	printf("IV값 입력 : ");
	for (int i = 0; i < Byte; i++) {															    
																									
		scanf_s("%hhx", &IV[i]);																    
	}*/																						        
																									
	

	/*같은 운용모드의 암복호화를 같이 돌리지 말것*/ 
	// 암호화는 padding이 되었다는 했다는 가정하에 16byte입력시 1블럭이 더 나옴
	
	ECB(ECB_plainText);									 //-- 암호화 테스트
	printf("\n비교할 Text Vector값 : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ",ECB_CipherText[i]);
	}
	/*
	ECB(ECB_CipherText);										//--복호화 테스트
	printf("\nText Vector값 : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", ECB_plainText[i]);
	}*/
	
	/*CBC_en(CBC_plainText);
	printf("\nText Vector값 : ");									 //-- 암호화 테스트
	for (int i = 0; i < 16; i++) {
		printf("%x ", CBC_CipherText[i]);
	}*/
	
	/*
	CBC_de(CBC_CipherText);													//--복호화 테스트
	printf("\nText Vector값 : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CBC_plainText[i]);
	}*/
	
	/*
	CFB(CFB_plainText);														  // -- 암호화 테스트
	printf("\nText Vector값 : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CFB_CipherText[i]);
	}*/

	/*
	CFB(CFB_CipherText);														//  --복호화 테스트
	printf("\nText Vector값 : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CFB_plainText[i]);
	}*/
	/*
	OFB(OFB_plainText);
	printf("\nText Vector값 : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", OFB_CipherText[i]);
	}*/
	
	/*
	OFB(OFB_CipherText);
	printf("\nText Vector값 : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", OFB_plainText[i]);
	}*/
	
	/*CTR(CTR_plainText); 
	printf("\nCTR cipher Vector값 : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CTR_CipherText[i]);
	}
	/*
	CTR(CTR_CipherText);
	printf("\nCTR decrypt Vector값 : ");
	for (int i = 0; i < 16; i++) {
		printf("%x ", CTR_plainText[i]);
	}*/

}

void ECB(unsigned char* text) { //ECB운용모드 암호화
	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	int choose;
	printf("ECB encrypt - 1, decrypt - 2 을 입력 : ");
	scanf_s("%d", &choose);

	if (choose == 1) {

		//Byte / 16 + 1 은 패딩 고려한 블럭 수
		printf("ECB 암호문 : ");
		for (int i = 0; i < Byte / 16 + 1; i++) {
			for (int k = 0; k < 16; k++)
				plain[k] = text[k + 16 * i];

			AES_En(cipher, plain, key);
			for (int j = 0; j < 16; j++) {

				printf("%x ", cipher[j]);
			}
		}
		
	}
	else if (choose == 2) {

		printf("ECB 복호문 : ");
		//암호문은 16byte 단위로 들어와서 Byte / 16 을 블럭수로 둠
		for (int i = 0; i < Byte / 16; i++) {
			for (int j = 0; j < 16; j++) {
				cipher[j] = text[j + 16 * i];
			}
			AES_De(plain, cipher, key);
			if (i == (Byte / 16 - 1) && Byte > 16) { //&& Byte > 16 조건은 test vector에는 패딩이 안되어 있어서 넣음 원래는 빼야함
				Del(plain); //  padding 제거함수
				break;
			}
			for (int j = 0; j < 16; j++) {

				printf("%x ",plain[j]);
			}
		}
	}
	
}


void CBC_en(unsigned char* text) {

	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	printf("CBC 암호문 : ");
	for (int i = 0; i < Byte / 16 + 1; i++) {

		for(int k = 0; k < 16; k++)
			plain[k] = text[k + 16 * i];
		for (int k = 0; k < 16; k++)
			plain[k] ^= IV[k];
		AES_En(cipher, plain, key);

		for (int j = 0; j < 16; j++) {

			printf("%x ", cipher[j]);
			IV[j] = cipher[j];
		}

		
	}
}

void CBC_de(unsigned char* text) {

	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	printf("CBC 복호문 : ");
	for (int i = 0; i < Byte / 16; i++) {
		for (int j = 0; j < 16; j++) {
			cipher[j] = text[j + 16 * i];
		}
		AES_De(plain, cipher, key);
		for (int j = 0; j < 16; j++) {
			plain[j] = plain[j] ^ IV[j];
		}
		//i == (Byte / 16 - 1)은 암호문의 마지막 블럭
		if (i == (Byte / 16 - 1) && Byte > 16) {//&&  Byte > 16 조건은 test vector에는 패딩이 안되어 있어서 넣음 원래는 빼야함
			Del(plain); // padding 제거
			break;
		}
		for (int j = 0; j < 16; j++) {

			printf("%x ", plain[j]);
			IV[j] = cipher[j];
		}
	}
}

void OFB(unsigned char* text) {

	int choose;
	printf("OFB encrypt - 1, decrypt - 2 을 입력 : ");;
	scanf_s("%d", &choose);
	unsigned char text2[16] = { 0, };

	for (int i = 0; i < Byte / 16 + 1; i++) {
		
		
		AES_En(IV, IV, key);

		for (int j = 0; j < 16; j++) 
			text2[j] = text[j + 16 * i] ^ IV[j];

		if (i == Byte / 16 -1 && choose == 2 && Byte > 16) {//&&  Byte > 16 조건은 test vector에는 패딩이 안되어 있어서 넣음 원래는 빼야함
			Del(text2); // padding 제거
			break;
		}
		for (int j = 0; j < 16; j++) {
			printf("%x ", text2[j]);
		}
		
	}
}
void CFB(unsigned char* text) {
	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	int choose;
	printf("encrypt - 1, decrypt - 2 을 입력 : ");
	scanf_s("%d", &choose);
	if (choose == 1) {
		printf("CFB 암호문 : ");
		for (int i = 0; i < Byte / 16 + 1; i++) {
			for (int k = 0; k < 16; k++)
				plain[k] = text[k + 16 * i];

			AES_En(IV, IV, key);

			for (int j = 0; j < 16; j++) {
				cipher[j] = plain[j] ^ IV[j];
				printf("%x ", cipher[j]);
				IV[j] = cipher[j];
			}
		}
	}
	else if(choose == 2){
		printf("CFB 복호문 : ");
		for (int i = 0; i < Byte / 16; i++) {
			for (int k = 0; k < 16; k++)
				cipher[k] = text[k + 16 * i];

			AES_En(IV, IV, key);

			for (int j = 0; j < 16; j++) {
				plain[j] = cipher[j] ^ IV[j];

				if (i == Byte / 16 - 1 && Byte > 16) {//&&  Byte > 16조건은 test vector에는 패딩이 안되어 있어서 넣음 원래는 빼야함
					Del(plain); // padding 제거
					break;
				}
				printf("%x ", plain[j]);
				IV[j] = cipher[j];
			}
		}
	}

	
}

void CTR(unsigned char* text) {
	
	unsigned char cipher[16] = { 0, };
	unsigned char plain[16] = { 0, };
	unsigned int sum = 0;
	int choose;
	printf("encrypt -  0, decrypt - 1 을 입력 : ");
	scanf_s("%d", &choose);
	for (int i = 0; i < Byte / 16 + 1; i++) {
		
		AES_En(IV_ctr, IV_ctr, key_ctr);
		
		for (int j = 0; j < 16; j++) {
			plain[j] = text[j + 16 * i];
			cipher[j] = plain[j] ^ IV_ctr[j];
			if (i == Byte / 16 && choose && Byte > 16) {//&& Byte > 16 조건은 test vector에는 패딩이 안되어 있어서 넣음 원래는 빼야함
				Del(cipher); // padding 제거
				break;
			}
			printf("%x ", cipher[j]);
			
		}
		if (choose && Byte == 16)				   //1블럭 복호화시 패딩이 안 되어있는 test vector때문에 써놓은 조건문(실제론 지워야함)
			break;

		for (int k = 0; k < 15; k++) { // CTR정수로 변형 -- sum변수에 저장
			sum += IV_ctr[k];
			sum *= 2;
		}
		sum += IV_ctr[15]+1;// ---- CTR + 1
		sum %= (2048 * 2 * 2 * 2 * 2 * 2);
		for (int k = 15; k >= 0; k--) { // CTR값을 비트로 바꿈
			IV_ctr[k] = sum & 0x01;
			sum = sum >> 1;
		}
	}
}
