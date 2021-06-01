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
  for (i64 i = 31 ; i >= 0 ; i--){
    INV_R(ct[1], ct[0], k[i]);
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

  printf("%s\n", password);

  return password;
}

void EncryptFile(FILE* file_in){
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
  FILE* encrypt_out = fopen("file_encrypt.txt", "wb");

  while ( fread(data128b, sizeof(u64), 2, file_in) == 2 ){
  	//printf("%llx %llx ->", data128b[0], data128b[1]);

  	Speck128Encrypt(data128b, data128b_encrypt, key);
  	//printf(" %llx %llx\n", data128b_encrypt[0], data128b_encrypt[1]);

  	fwrite(data128b_encrypt, sizeof(u64), 2, encrypt_out);
  	data128b[0] = O; data128b[1] = O;
  }
  Speck128Encrypt(data128b, data128b_encrypt, key);
  fwrite(data128b_encrypt, sizeof(u64), 2, encrypt_out);


  fclose(encrypt_out);
  fclose(file_in);

  printf("FILE ENCRYPTED\n\n");
}

void DecryptFile(FILE* encrypt_in){
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
  FILE* decrypt_out = fopen("file_decrypt.txt", "wb");

  while ( fread(data128b_encrypt, sizeof(u64), 2, encrypt_in) == 2 ){
  	//printf("%llx %llx ->", data128b_encrypt[0], data128b_encrypt[1]);

  	data128b_decrypt[0] = data128b_encrypt[0];
  	data128b_decrypt[1] = data128b_encrypt[1];
  	Speck128Decrypt(data128b_encrypt, data128b_decrypt, key);
  	//printf(" %llx %llx\n", data128b_decrypt[0], data128b_decrypt[1]);

  	fwrite(data128b_decrypt, sizeof(u64), 2, decrypt_out);
  }

  fclose(decrypt_out);
  fclose(encrypt_in);

  printf("FILE DECRYPTED\n\n");
}

int main(int argc, char** argv){
  // ENCRYPTION
  if ( argc != 2 ){
    fprintf(stderr, "Wrong number of arguments!\n");
    exit(EXIT_FAILURE);
  }
  FILE* file_in = fopen(argv[1], "rb");

  if ( file_in == NULL ){
    fprintf(stderr, "File open error!\n");
    exit(EXIT_FAILURE);
  }

  EncryptFile(file_in);

  // DECRYPTION
  FILE* encrypt_in = fopen("file_encrypt.txt", "rb");

  if ( encrypt_in == NULL ){
    fprintf(stderr, "File open error!\n");
    exit(EXIT_FAILURE);
  }

  DecryptFile(encrypt_in);

  return 0;
}
