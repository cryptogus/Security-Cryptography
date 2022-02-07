/*LEA의 라운드 키 찾기(chipwsper 파형이므로 8bits 단위로 짜서 해밍웨이트 값을 구해야함)*/

/*----------------------------------------------------------------------------------*/
/*  분석 시작 바이트 (1~4사이의 수)	라운드키 값을 구할것임							*/
/*  분석 끝 바이트	(1~4사이의 수)													*/
/*----------------------------------------------------------------------------------*/
#define start_byte						1
#define last_byte						1 //한 라운드 당 라운드키가 24바이트
/*----------------------------------------------------------------------------------*/
/*  파형 경로																		*/
/*  평문 경로																		*/
/*----------------------------------------------------------------------------------*/

#define trace_path		"C:\\Users\\hyen\\chipwhisperer\\projects\\tmp\\default_data\\traces\\LEA_CPA(24라운드 파형)\\LEA_10000tr_4820p.trace"
#define plain_path		"C:\\Users\\hyen\\chipwhisperer\\projects\\tmp\\default_data\\traces\\LEA_CPA(24라운드 파형)\\LEA_10000tr_4820p_plain.txt"
#define cipher_path		"C:\\Users\\hyen\\chipwhisperer\\projects\\tmp\\default_data\\traces\\LEA_CPA(24라운드 파형)\\LEA_10000tr_4820p_cipher.txt"

//#define trace_path	"C:\\Users\\hyen\\Documents\\카카오톡 받은 파일\\trace1.trace"
//#define plain_path	"C:\\Users\\hyen\\Documents\\카카오톡 받은 파일\\plain.txt"
//#define cipher_path "C:\\Users\\hyen\\Documents\\카카오톡 받은 파일\\cipher.txt"
/*----------------------------------------------------------------------------------*/
/*  분석할 파형 수																	*/
/*----------------------------------------------------------------------------------*/
#define _TRACE_NUM_					10000
/*----------------------------------------------------------------------------------*/
/*  분석 시작 포인트																*/
/*  분석 끝 포인트																	*/
/*----------------------------------------------------------------------------------*/
#define _START_POINT_				1
#define _END_POINT_					4820
/*----------------------------------------------------------------------------------*/
/*  평문 바이트 수																	*/
/*----------------------------------------------------------------------------------*/
#define Block_Size					16
/*----------------------------------------------------------------------------------*/
/*  추측할 키 수																	*/
/*----------------------------------------------------------------------------------*/
#define Guess_key					0x100
/*----------------------------------------------------------------------------------*/
/*  공격위치(평문대입) 																*/
/*  Xor ---> target = 0																*/
/*  modulo addtion ---> target = 1													*/
/*  modulo subtract ---> target = 2(암호문 사용)									*/
/*----------------------------------------------------------------------------------*/
#define target					2

unsigned int HW(unsigned long long x);

typedef struct TRACE_HEADER {

	unsigned char strID[20];//처음 20byte 정보 날리기
	unsigned int trace_no; // 파형갯수
	unsigned int point_no; //포인트 수
	unsigned char strEND[4]; //4byte 띄고 시작
}trace_HEADER;

void LEA_CPA();

typedef unsigned char byte;
typedef unsigned int word;




