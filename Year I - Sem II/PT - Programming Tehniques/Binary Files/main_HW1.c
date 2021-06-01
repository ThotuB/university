# include <stdio.h>
# include <unistd.h>

/* how many seconds */
# define DURATION 60
/* thes ampling rate */
# define RATE 8000//8000
/* sample size : 8 bits */
# define SIZE 8
/* 1 = mono */
# define CHANNELS 1

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <x86intrin.h>

#define LCS _lrotl // left circular shift
#define RCS _lrotr // right circular shift
#define u64 unsigned long long
#define i64 long long
#define R(x,y,k) (x=RCS(x,8), x+=y, x^=k, y=LCS(y,3), y^=x)
#define INV_R(x,y,k) (y^=x, y=RCS(y,3), x^=k, x-=y, x=LCS(x,8))
#define O 0x2020202020202020;

unsigned char buffer[DURATION*RATE*SIZE*CHANNELS/8] ;

void PasswordHash128Key(u64 k[], char *password){
  k[0] = 0x0f0e0d0c0b0a0908;
  k[1] = 0x0706050403020100;
  u64 len = strlen(password);
  u64 i;

  for (i = 0 ; i < len/2 ; i++){
    k[0] = k[0] ^ (k[0] * ((u64)(password[i]) + (u64)(password[len-i-1])) );
  }
  for ( ; password[i] != '\0' ; i++){
  k[1] = k[1] ^ (k[1] * ((u64)(password[i]) + (u64)(password[len-i-1])) );
  }
}

void Speck128Encrypt(u64 pt[], u64 ct[], u64 k[]){
  ct[0] = pt[0];
  ct[1] = pt[1];

  for (u64 i = 0 ; i < 32 ; i++){
    R(ct[1], ct[0], k[i]);
  }
}

void Speck128Decrypt(u64 pt[], u64 ct[], u64 k[]){
  pt[0] = ct[0];
  pt[1] = ct[1];

  for (i64 i = 31 ; i >= 0 ; i--){
    INV_R(pt[1], pt[0], k[i]);
  }
}

static void speck_keyexpand(u64 k[]){
  u64 tmp[32], *p;
  memcpy(tmp, k, sizeof(tmp));

  for (u64 i = 0 ; i < (31) ; ){
    p = tmp + (1 + (i%(2 - 1)));
    R(*p, tmp[0], i);
    ++i;
    k[i] = tmp[0];
  }
}

char* GetPassword(){
  char* password = (char*)malloc(sizeof(char));
  u64 i = 0;
  for ( scanf("%c", &password[i]) ; isalnum(password[i]) ; scanf("%c", &password[i])){
    i++;
    password = (char*)realloc(password, (i+1)*sizeof(char));
  }
  password[i] = '\0';

  return password;
}

u64 GetBytes(unsigned nrBytes, unsigned char arr[]){
  u64 bytes = 0x0;
  for (unsigned i = 0 ; i < nrBytes ; i++){
    bytes <<= 8;
    bytes += arr[nrBytes-i-1];
  }

  //printf("%llx", bytes);

  return bytes;
}

void EncryptFile(FILE* file_in){
  fread(buffer, sizeof(buffer), 1, file_in);

  printf("Encrypt Password: ");
  char* password = GetPassword();
  u64 key[32];

  u64 data128b[] = {0x0, 0x0};
  u64 data128b_encrypt[] = {0x0, 0x0};

  // Password Hash to 128 bit Key
  PasswordHash128Key(key, password);

  // Speck128 Exapnd Key
  speck_keyexpand(key);
  printf("Key 128 bit: %llx %llx\n", key[0], key[1]);

  //Speck128Encrypt(pt, ct, k);
  FILE* encrypt_out = fopen("sound_encrypt", "wb");

  for (unsigned i = 0 ; i < sizeof(buffer) ; i += 16){
    data128b[0] = GetBytes(8, buffer + i);
    data128b[1] = GetBytes(8, buffer + i + 8);

    Speck128Encrypt(data128b, data128b_encrypt, key);
    //printf("%016llx %016llx -> %016llx %016llx\n", data128b[0], data128b[1], data128b_encrypt[0], data128b_encrypt[1]);

    fwrite(data128b_encrypt, sizeof(u64), 2, encrypt_out);
  }


  fclose(encrypt_out);
  fclose(file_in);

  printf("FILE ENCRYPTED\n\n");
}

void DecryptFile(FILE* encrypt_in){
  fread(buffer, sizeof(buffer), 1, encrypt_in);

  printf("Decrypt Password: ");
  char* password = GetPassword();
  u64 key[32];

  u64 data128b_encrypt[] = {0x0, 0x0};
  u64 data128b_decrypt[] = {0x0, 0x0};

  // Password Hash to 128 bit Key
  PasswordHash128Key(key, password);

  // Speck128 Exapnd Key
  speck_keyexpand(key);
  printf("Key 128 bit: %llx %llx\n", key[0], key[1]);

  //Speck128Encrypt(pt, ct, k);
  FILE* decrypt_out = fopen("sound_decrypt", "wb");

  for (unsigned i = 0 ; i < sizeof(buffer) ; i += 16){
    data128b_encrypt[0] = GetBytes(8, buffer + i);
    data128b_encrypt[1] = GetBytes(8, buffer + i + 8);

    Speck128Decrypt(data128b_decrypt, data128b_encrypt, key);
    //printf("%016llx %016llx -> %016llx %016llx\n", data128b_encrypt[0], data128b_encrypt[1], data128b_decrypt[0], data128b_decrypt[1]);

    fwrite(data128b_decrypt, sizeof(u64), 2, decrypt_out);
  }

  fclose(decrypt_out);
  fclose(encrypt_in);

  printf("FILE DECRYPTED\n\n");
}

int main(int argc ,char* argv[]){
  FILE* soundcard ;
  int n, filenum ;


  if ( argc == 2) {
  	soundcard = fopen( argv[1], "r+b" ) ;
  }
  else {
  	soundcard = fopen( "/dev/dsp", "r+b" ) ;
  }

  if ( soundcard == NULL) {
    perror( "Cannot talk to soundcard : X.. " ) ;
    return 0;
  }

  if ( argc == 1) {
    printf( "Recording for %d seconds ( mic ): \n" , DURATION ) ;
  }


  EncryptFile(soundcard);

  FILE* soundcard_encrypted = fopen("sound_encrypt", "rb");
  if ( !soundcard_encrypted ){
    perror("Encrypted soundcard failed to open!");
    return 0;
  }

  DecryptFile(soundcard_encrypted);

  fclose( soundcard ) ;
  fclose( soundcard_encrypted ) ;

  return 1 ;
}
