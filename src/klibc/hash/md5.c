#include <hash/md5.h>
#include <malloc.h>


#define DIGEST_A 0x67452301
#define DIGEST_B 0xEFCDAB89
#define DIGEST_C 0x98BADCFE
#define DIGEST_D 0X10325476

#define LEFT(x, shift)  (( (x) >> 32 - (shift) )|( (x) << (shift) ))
#define REVS(x)	        ((((x) & 0x000000ff) <<24) | ((x) >>24) | (((x) & 0x00ff0000) >>8) | (((x) & 0x0000ff00) <<8))		   

#define TransF(crx, a, b, c, d, k, s, i) \
	b + LEFT((a + ((b&c) | (~(b)&d)) + crx->X[k] + _md5_pad_[i-1]), s)

#define TransG(crx, a, b, c, d, k, s, i) \
	b + LEFT((a + ((b&d) | (c & ~d) ) + crx->X[k] + _md5_pad_[i-1]), s)

#define TransH(crx, a, b, c, d, k, s, i) \
	b + LEFT((a + (b^c^d) + crx->X[k] + _md5_pad_[i-1]), s)

#define TransI(crx, a, b, c, d, k, s, i) \
	b + LEFT((a + (c^(b|~d))+ crx->X[k] + _md5_pad_[i-1]), s)


static uint32_t _md5_pad_[] =  
{	0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
	0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
    0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
    0x6b901122,0xfd987193,0xa679438e,0x49b40821,
	0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
    0xd62f105d,0x2441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
	0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
    0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
    0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
    0x289b7ec6,0xeaa127fa,0xd4ef3085,0x4881d05,
	0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
    0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
    0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
    0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
	0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};

struct md5_buffer
{
	uint32_t pad;		//no of padding bits for 448 mod 512 
	uint8_t  *bMsg;		//buffer to hold bits
	uint64_t sizeMsg;		//64 bit size pad
	uint32_t sizeMsgBuff;	//buffer size in multiple of bytes
	uint32_t X[16];
	uint32_t digest[4]; // a,b,c,d

}__attribute__((packed));


struct md5_buffer* md5_create_buffer(const char* data,size_t lenght)
{
	struct md5_buffer* crx = malloc(sizeof(struct md5_buffer));
	crx->digest[0] = DIGEST_A;
	crx->digest[1] = DIGEST_B;
	crx->digest[2] = DIGEST_C;
	crx->digest[3] = DIGEST_D;

	int temp=(448-((lenght*8)%512)); //temporary

	crx->pad = (uint32_t )((temp+512)%512);		//getting no of bits to  be pad
	if (crx->pad==0) crx->pad=512;

	crx->sizeMsgBuff= (uint32_t) ((lenght) + (crx->pad/8)+8);
	crx->sizeMsg=(uint64_t)lenght * 8;
	crx->bMsg= (uint8_t*)calloc(1, sizeof(uint8_t) * crx->sizeMsgBuff);

	////copying string to buffer 
	for (int i =0; i< lenght; i++)
		crx->bMsg[i] = data[i];

	crx->bMsg[lenght] |= 0x80;		///making first bit of padding 1,

	//wrting the size value
	for (int i =8; i >0;i--)
		crx->bMsg[crx->sizeMsgBuff - i] = (uint8_t) ( crx->sizeMsg >> ((8-i) * 8) & 0x00000000000000ff);
	
	return crx;
}
void md5_copyblock(struct md5_buffer* crx, uint32_t block) // msg
{
	block = block << 6;
	for (uint32_t j = 0; j < 61; j +=4 )
	{
		crx->X[j>>2] =	(((uint32_t) crx->bMsg[block+(j+3)]) << 24 ) |
						(((uint32_t) crx->bMsg[block+(j+2)]) << 16 ) |
						(((uint32_t) crx->bMsg[block+(j+1)]) << 8 ) |
						(((uint32_t) crx->bMsg[block+(j)]) ) ;
	}
	
}
void md5_transform(struct md5_buffer* crx)
{
	uint32_t AA = crx->digest[0], BB = crx->digest[1], 
			 CC = crx->digest[2] ,DD = crx->digest[3];
	
	uint32_t A = crx->digest[0], B = crx->digest[1], 
			 C = crx->digest[2] ,D = crx->digest[3];

	A = TransF(crx, A,B,C,D,0,7,1); D = TransF(crx, D,A,B,C,1,12,2); C = TransF(crx, C,D,A,B,2,17,3); B = TransF(crx, B,C,D,A,3,22,4);
	A = TransF(crx, A,B,C,D,4,7,5); D = TransF(crx, D,A,B,C,5,12,6); C = TransF(crx, C,D,A,B,6,17,7); B = TransF(crx, B,C,D,A,7,22,8);
	A = TransF(crx, A,B,C,D,8,7,9); D = TransF(crx, D,A,B,C,9,12,10); C = TransF(crx, C,D,A,B,10,17,11); B = TransF(crx, B,C,D,A,11,22,12);
	A = TransF(crx, A,B,C,D,12,7,13); D = TransF(crx, D,A,B,C,13,12,14); C = TransF(crx, C,D,A,B,14,17,15); B = TransF(crx, B,C,D,A,15,22,16);


	A = TransG(crx, A,B,C,D,1,5,17);D = TransG(crx, D,A,B,C,6,9,18);C = TransG(crx, C,D,A,B,11,14,19);B = TransG(crx, B,C,D,A,0,20,20);
	A = TransG(crx, A,B,C,D,5,5,21);D = TransG(crx, D,A,B,C,10,9,22);C = TransG(crx, C,D,A,B,15,14,23);B = TransG(crx, B,C,D,A,4,20,24);
	A = TransG(crx, A,B,C,D,9,5,25);D = TransG(crx, D,A,B,C,14,9,26);C = TransG(crx, C,D,A,B,3,14,27);B = TransG(crx, B,C,D,A,8,20,28);
	A = TransG(crx, A,B,C,D,13,5,29);D = TransG(crx, D,A,B,C,2,9,30);C = TransG(crx, C,D,A,B,7,14,31);B = TransG(crx, B,C,D,A,12,20,32);

	A = TransH(crx, A,B,C,D,5,4,33);D = TransH(crx, D,A,B,C,8,11,34);C = TransH(crx, C,D,A,B,11,16,35);B = TransH(crx, B,C,D,A,14,23,36);
	A = TransH(crx, A,B,C,D,1,4,37);D = TransH(crx, D,A,B,C,4,11,38);C = TransH(crx, C,D,A,B,7,16,39);B = TransH(crx, B,C,D,A,10,23,40);
	A = TransH(crx, A,B,C,D,13,4,41);D = TransH(crx, D,A,B,C,0,11,42);C = TransH(crx, C,D,A,B,3,16,43);B = TransH(crx, B,C,D,A,6,23,44);
	A = TransH(crx, A,B,C,D,9,4,45);D = TransH(crx, D,A,B,C,12,11,46);C = TransH(crx, C,D,A,B,15,16,47);B = TransH(crx, B,C,D,A,2,23,48);

	A = TransI(crx, A,B,C,D,0,6,49);D = TransI(crx, D,A,B,C,7,10,50);C = TransI(crx, C,D,A,B,14,15,51);B = TransI(crx, B,C,D,A,5,21,52);
	A = TransI(crx, A,B,C,D,12,6,53);D = TransI(crx, D,A,B,C,3,10,54);C = TransI(crx, C,D,A,B,10,15,55);B = TransI(crx, B,C,D,A,1,21,56);
	A = TransI(crx, A,B,C,D,8,6,57);D = TransI(crx, D,A,B,C,15,10,58);C = TransI(crx, C,D,A,B,6,15,59);B = TransI(crx, B,C,D,A,13,21,60);
	A = TransI(crx, A,B,C,D,4,6,61);D = TransI(crx, D,A,B,C,11,10,62);C = TransI(crx, C,D,A,B,2,15,63);B = TransI(crx, B,C,D,A,9,21,64);

	crx->digest[0] = A+AA;
	crx->digest[1] = B+BB;
	crx->digest[2] = C+CC;
	crx->digest[3] = D+DD;
}
struct md5_buffer* md5_do(struct md5_buffer* crx)
{
	uint32_t N;
	if(crx == 0)
		return 0;

	N = (uint32_t)( crx->sizeMsgBuff * 8 ) / 32;

	for (uint32_t i=0; i < N/16; i++)
	{
		md5_copyblock(crx, i);
		md5_transform(crx);
	}

	return crx;
}
void  md5_hash(struct md5_buffer* crx, char* ret)
{

	char st[260];
	sprintf(st, "%x%x%x%x",
				REVS(crx->digest[0]),
				REVS(crx->digest[1]),
				REVS(crx->digest[2]),
				REVS(crx->digest[3]));

	memcpy(ret, st, 260);
	free( st );
}
void   md5(const char* text, char* hash)
{
	struct md5_buffer* crx = md5_create_buffer(text, strlen(text));
	crx = md5_do(crx);

	md5_hash(crx, hash);
}