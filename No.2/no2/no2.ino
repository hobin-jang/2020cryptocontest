#pragma GCC optimize ("-O3") 
#define ROUND_NUM 128

typedef unsigned char u8;

typedef unsigned short u16;

u8 key_table1[256]={
  0x00,0x22,0x44,0x66,0x88,0xaa,0xcc,0xee,0x11,0x33,0x55,0x77,0x99,0xbb,0xdd,0xff,0x22,0x44,0x66,0x88,0xaa,0xcc,0xee,0x10,
  0x33,0x55,0x77,0x99,0xbb,0xdd,0xff,0x21,0x44,0x66,0x88,0xaa,0xcc,0xee,0x10,0x32,0x55,0x77,0x99,0xbb,0xdd,0xff,0x21,0x43,
  0x66,0x88,0xaa,0xcc,0xee,0x10,0x32,0x54,0x77,0x99,0xbb,0xdd,0xff,0x21,0x43,0x65,0x88,0xaa,0xcc,0xee,0x10,0x32,0x54,0x76,
  0x99,0xbb,0xdd,0xff,0x21,0x43,0x65,0x87,0xaa,0xcc,0xee,0x10,0x32,0x54,0x76,0x98,0xbb,0xdd,0xff,0x21,0x43,0x65,0x87,0xa9,
  0xcc,0xee,0x10,0x32,0x54,0x76,0x98,0xba,0xdd,0xff,0x21,0x43,0x65,0x87,0xa9,0xcb,0xee,0x10,0x32,0x54,0x76,0x98,0xba,0xdc,
  0xff,0x21,0x43,0x65,0x87,0xa9,0xcb,0xed,0x11,0x33,0x55,0x77,0x99,0xbb,0xdd,0xff,0x22,0x44,0x66,0x88,0xaa,0xcc,0xee,0x10,
  0x33,0x55,0x77,0x99,0xbb,0xdd,0xff,0x21,0x44,0x66,0x88,0xaa,0xcc,0xee,0x10,0x32,0x55,0x77,0x99,0xbb,0xdd,0xff,0x21,0x43,
  0x66,0x88,0xaa,0xcc,0xee,0x10,0x32,0x54,0x77,0x99,0xbb,0xdd,0xff,0x21,0x43,0x65,0x88,0xaa,0xcc,0xee,0x10,0x32,0x54,0x76,
  0x99,0xbb,0xdd,0xff,0x21,0x43,0x65,0x87,0xaa,0xcc,0xee,0x10,0x32,0x54,0x76,0x98,0xbb,0xdd,0xff,0x21,0x43,0x65,0x87,0xa9,
  0xcc,0xee,0x10,0x32,0x54,0x76,0x98,0xba,0xdd,0xff,0x21,0x43,0x65,0x87,0xa9,0xcb,0xee,0x10,0x32,0x54,0x76,0x98,0xba,0xdc,
  0xff,0x21,0x43,0x65,0x87,0xa9,0xcb,0xed,0x10,0x32,0x54,0x76,0x98,0xba,0xdc,0xfe}; // key_table1[u8 x] = ROL8( u8 x, 1)+ROL8( u8 x , 5)

u8 key_table2[256]{
  0x00,0x88,0x11,0x99,0x22,0xaa,0x33,0xbb,0x44,0xcc,0x55,0xdd,0x66,0xee,0x77,0xff,0x88,0x10,0x99,0x21,0xaa,0x32,0xbb,0x43,
  0xcc,0x54,0xdd,0x65,0xee,0x76,0xff,0x87,0x11,0x99,0x22,0xaa,0x33,0xbb,0x44,0xcc,0x55,0xdd,0x66,0xee,0x77,0xff,0x88,0x10,
  0x99,0x21,0xaa,0x32,0xbb,0x43,0xcc,0x54,0xdd,0x65,0xee,0x76,0xff,0x87,0x10,0x98,0x22,0xaa,0x33,0xbb,0x44,0xcc,0x55,0xdd,
  0x66,0xee,0x77,0xff,0x88,0x10,0x99,0x21,0xaa,0x32,0xbb,0x43,0xcc,0x54,0xdd,0x65,0xee,0x76,0xff,0x87,0x10,0x98,0x21,0xa9,
  0x33,0xbb,0x44,0xcc,0x55,0xdd,0x66,0xee,0x77,0xff,0x88,0x10,0x99,0x21,0xaa,0x32,0xbb,0x43,0xcc,0x54,0xdd,0x65,0xee,0x76,
  0xff,0x87,0x10,0x98,0x21,0xa9,0x32,0xba,0x44,0xcc,0x55,0xdd,0x66,0xee,0x77,0xff,0x88,0x10,0x99,0x21,0xaa,0x32,0xbb,0x43,
  0xcc,0x54,0xdd,0x65,0xee,0x76,0xff,0x87,0x10,0x98,0x21,0xa9,0x32,0xba,0x43,0xcb,0x55,0xdd,0x66,0xee,0x77,0xff,0x88,0x10,
  0x99,0x21,0xaa,0x32,0xbb,0x43,0xcc,0x54,0xdd,0x65,0xee,0x76,0xff,0x87,0x10,0x98,0x21,0xa9,0x32,0xba,0x43,0xcb,0x54,0xdc,
  0x66,0xee,0x77,0xff,0x88,0x10,0x99,0x21,0xaa,0x32,0xbb,0x43,0xcc,0x54,0xdd,0x65,0xee,0x76,0xff,0x87,0x10,0x98,0x21,0xa9,
  0x32,0xba,0x43,0xcb,0x54,0xdc,0x65,0xed,0x77,0xff,0x88,0x10,0x99,0x21,0xaa,0x32,0xbb,0x43,0xcc,0x54,0xdd,0x65,0xee,0x76,
  0xff,0x87,0x10,0x98,0x21,0xa9,0x32,0xba,0x43,0xcb,0x54,0xdc,0x65,0xed,0x76,0xfe}; // key_table2[u8 x] = ROL8( u8 x, 3)+ROL8( u8 x , 7)

u16 swap_arr(u8* arr) {                  // swap_arr : 입력 인자 arr의 arr[0], arr[1]을 swap하여 16비트 결과를 출력
  u8 arr2[2] = { 0,0 };
  arr2[0] = arr[1];
  arr2[1] = arr[0];
  return *(u16*)arr2;
} 

void key_gen(u8 *rnd, u8 *key){
  u16 *key_p;     
  key_p=(u16*) key;                      // key_in 대신 입력 인자 key 사용
  
  int i,j;                               
  for(i=0;i<3;i++){                      // for문 : 기존의 16개의 라운드를 for문의 한 라운드로 사용
    j=i*32;
    
    key[0]=key_table1[key[0]];           // ROL8(key[0],1)+ROL8(key[0],5)와 같은 결과
    key[1]=key_table2[key[1]];           // ROL8(key[1],3)+ROL8(key[1],7)와 같은 결과
    rnd[j+0]=key[0]+key[1];              // tmp 대신 입력 인자 rnd 활용
    rnd[j+1]=key[0]^key[1];
    key[0]=rnd[j+0];
    key[1]=rnd[j+1];

    *key_p=(*key_p<<1)|(*key_p>>15);     // ROL16(*key_p,1)을 풀어쓴 결과
    *key_p=*key_p+swap_arr(key)+0x3579;  // ROL16(*key_p,9)는 ROL16(*key_p,1) 계산 후 key[0], key[1]을 swap한 것과 같음. ROL16(con,(i%16)) 미리 계산
    rnd[j+2]=key[0]+key[1];
    rnd[j+3]=key[0]^key[1];
    key[0]=rnd[j+2];
    key[1]=rnd[j+3];
  
    key[0]=key_table1[key[0]];
    key[1]=key_table2[key[1]];
    rnd[j+4]=key[0]+key[1];
    rnd[j+5]=key[0]^key[1];
    key[0]=rnd[j+4];
    key[1]=rnd[j+5];

    *key_p=(*key_p<<1)|(*key_p>>15);
    *key_p=*key_p+swap_arr(key)+0xD5E4;
    rnd[j+6]=key[0]+key[1];
    rnd[j+7]=key[0]^key[1];
    key[0]=rnd[j+6];
    key[1]=rnd[j+7];
  
    key[0]=key_table1[key[0]];
    key[1]=key_table2[key[1]];
    rnd[j+8]=key[0]+key[1];
    rnd[j+9]=key[0]^key[1];
    key[0]=rnd[j+8];
    key[1]=rnd[j+9];

    *key_p=(*key_p<<1)|(*key_p>>15);
    *key_p=*key_p+swap_arr(key)+0x5793;
    rnd[j+10]=key[0]+key[1];
    rnd[j+11]=key[0]^key[1];
    key[0]=rnd[j+10];
    key[1]=rnd[j+11];
  
    key[0]=key_table1[key[0]];
    key[1]=key_table2[key[1]];
    rnd[j+12]=key[0]+key[1];
    rnd[j+13]=key[0]^key[1];
    key[0]=rnd[j+12];
    key[1]=rnd[j+13];

    *key_p=(*key_p<<1)|(*key_p>>15);
    *key_p=*key_p+swap_arr(key)+0x5E4D;
    rnd[j+14]=key[0]+key[1];
    rnd[j+15]=key[0]^key[1];
    key[0]=rnd[j+14];
    key[1]=rnd[j+15];
  
    key[0]=key_table1[key[0]];
    key[1]=key_table2[key[1]];
    rnd[j+16]=key[0]+key[1];
    rnd[j+17]=key[0]^key[1];
    key[0]=rnd[j+16];
    key[1]=rnd[j+17];
    
    *key_p=(*key_p<<1)|(*key_p>>15);
    *key_p=*key_p+swap_arr(key)+0x7935;
    rnd[j+18]=key[0]+key[1];
    rnd[j+19]=key[0]^key[1];
    key[0]=rnd[j+18];
    key[1]=rnd[j+19];
  
    key[0]=key_table1[key[0]];
    key[1]=key_table2[key[1]];
    rnd[j+20]=key[0]+key[1];
    rnd[j+21]=key[0]^key[1];
    key[0]=rnd[j+20];
    key[1]=rnd[j+21];
    
    *key_p=(*key_p<<1)|(*key_p>>15);
    *key_p=*key_p+swap_arr(key)+0xE4D5;
    rnd[j+22]=key[0]+key[1];
    rnd[j+23]=key[0]^key[1];
    key[0]=rnd[j+22];
    key[1]=rnd[j+23];
    
    key[0]=key_table1[key[0]];
    key[1]=key_table2[key[1]];
    rnd[j+24]=key[0]+key[1];
    rnd[j+25]=key[0]^key[1];
    key[0]=rnd[j+24];
    key[1]=rnd[j+25];
    
    *key_p=(*key_p<<1)|(*key_p>>15);
    *key_p=*key_p+swap_arr(key)+0x9357;
    rnd[j+26]=key[0]+key[1];
    rnd[j+27]=key[0]^key[1];
    key[0]=rnd[j+26];
    key[1]=rnd[j+27];
  
    key[0]=key_table1[key[0]];
    key[1]=key_table2[key[1]];
    rnd[j+28]=key[0]+key[1];
    rnd[j+29]=key[0]^key[1];
    key[0]=rnd[j+28];
    key[1]=rnd[j+29];
    
    *key_p=(*key_p<<1)|(*key_p>>15);
    *key_p=*key_p+swap_arr(key)+0x4D5E;
    rnd[j+30]=key[0]+key[1];
    rnd[j+31]=key[0]^key[1];
    key[0]=rnd[j+30];
    key[1]=rnd[j+31];
  }
  for(int s=0;s<8;s++)            // rnd가 반복됨을 이용. (rnd[64]~rnd[95])의 값을 (rnd[96]~rnd[127]),...,(rnd[224]~rnd[255])에 복사하였다.
  {
    int t=4*s;
    u32 rnd_copy=*((u32*)(rnd+64+t));
    *((u32*)(rnd+96+t))=rnd_copy;
    *((u32*)(rnd+128+t))=rnd_copy;
    *((u32*)(rnd+160+t))=rnd_copy;
    *((u32*)(rnd+192+t))=rnd_copy;
    *((u32*)(rnd+224+t))=rnd_copy;
  }
}
void enc(u8 *text, u8 *rnd){
  u16 *text_p;
  text_p=(u16*) text;                      // text_in 대신 text 사용
  
  int i,j;
  for(i=0;i<8;i++){                        // for문 : 기존의 라운드 16개를 for문의 한 라운드로 사용
    j=i*32;
    *text_p=(*text_p<<4)|(*text_p>>12);    // ROL16(*text_p,4)를 풀어쓴 결과
    text[0]=(text[0]+rnd[j+0])^rnd[j+3];   // ROL16(*text_p,8)을 계산하지 않고, rnd와의 연산 순서를 변경하여 같은 결과 나오게끔 연산 순서 조정
    text[1]=(text[1]^rnd[j+1])+rnd[j+2];
    
    *text_p=(*text_p<<4)|(*text_p>>12);
    text[0]=(text[0]^rnd[j+5])+rnd[j+6];
    text[1]=(text[1]+rnd[j+4])^rnd[j+7];
    
    *text_p=(*text_p<<4)|(*text_p>>12);
    text[0]=(text[0]+rnd[j+8])^rnd[j+11];
    text[1]=(text[1]^rnd[j+9])+rnd[j+10];
    
    *text_p=(*text_p<<4)|(*text_p>>12);
    text[0]=(text[0]^rnd[j+13])+rnd[j+14];
    text[1]=(text[1]+rnd[j+12])^rnd[j+15];
    
    *text_p=(*text_p<<4)|(*text_p>>12);
    text[0]=(text[0]+rnd[j+16])^rnd[j+19];
    text[1]=(text[1]^rnd[j+17])+rnd[j+18];
    
    *text_p=(*text_p<<4)|(*text_p>>12);
    text[0]=(text[0]^rnd[j+21])+rnd[j+22];
    text[1]=(text[1]+rnd[j+20])^rnd[j+23];
    
    *text_p=(*text_p<<4)|(*text_p>>12);
    text[0]=(text[0]+rnd[j+24])^rnd[j+27];
    text[1]=(text[1]^rnd[j+25])+rnd[j+26];
    
    *text_p=(*text_p<<4)|(*text_p>>12);
    text[0]=(text[0]^rnd[j+29])+rnd[j+30];
    text[1]=(text[1]+rnd[j+28])^rnd[j+31];
  }
}
    
 u8 TEST_VECTOR(u8 *in, u8 *answer){
  return (in[0] == answer[0] && in[1] == answer[1]);
 }

void setup(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  u8 key[3][2] = { {0x12, 0x34}, {0x9A, 0xBD}, {0x11, 0x22} };
  u8 rnd[ROUND_NUM * 2] = {0, };
  u8 text[3][2] = { {0x56, 0x78}, {0xDE, 0xF0}, {0x33, 0x44} };
  u8 out_text[3][2] = { {0x50, 0x3F}, {0x88, 0x28}, {0x7F, 0x33} };


  Serial.println("-----------------");
  Serial.println(" TEST_VECTOR ");
  Serial.println(" ----------------");

  for(int i=0; i<3; i++) {
    key_gen(rnd, key[i]);
    enc(text[i], rnd);

    if(TEST_VECTOR(text[i], out_text[i])){
      Serial.println(">> CORRECT");
    }else{
      Serial.println("WRONG");
    }
  }
  Serial.println("-----------------");
  Serial.println(" BENCHMARK ");
  Serial.println("-----------------");

  u8 key_bench[2] = { 0x12, 0x34 };
  u8 text_bench[2] = { 0x56, 0x78};

  u32 time1;
  u32 time2;
  time1 = millis();
  for(int i=0; i<4096; i++){
    key_gen(rnd, key_bench);
    enc(text_bench,rnd);

    if(text_bench[0]>0x80){
      digitalWrite(LED_BUILTIN, HIGH);
    }else{
      digitalWrite(LED_BUILTIN, LOW);
    }
  }


  time2 = millis();
  Serial.print(">>");
  Serial.println((time2-time1));
  Serial.println("————————");
}
    
void loop() {
  // put your main code here, to run repeatedly:

}
