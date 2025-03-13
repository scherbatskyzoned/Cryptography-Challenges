#include <stdio.h>
#include <string.h>

#include <openssl/evp.h>


#define ENCRYPT 1
#define DECRYPT 0

int main()
{
    FILE *f_in;
    unsigned char key[] = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
    unsigned char iv[]  = "11111111111111112222222222222222";
    char ciphertext_b64[] = "jyS3NIBqenyCWpDI2jkSu+z93NkDbWkUMitg2Q==";
    
    // system("openssl base64 -d -in file.enc -out file.decode");
    
    if((f_in = fopen("file.decode","r")) == NULL) {
            fprintf(stderr,"Couldn't open the input file, try again\n");
            abort();
    }

    unsigned char key_bin[strlen(key)/2];
    for(int i = 0; i < strlen(key)/2;i++){
        sscanf(&key[2*i],"%2hhx", &key_bin[i]);
    }

    unsigned char iv_bin[strlen(iv)/2];
    for(int i = 0; i < strlen(iv)/2;i++){
        sscanf(&iv[2*i],"%2hhx", &iv_bin[i]);
    }

    unsigned char ciphertext_binary[1024];
    int ciphertext_len;

    while (fscanf(f_in,"%s",ciphertext_binary) != EOF)
        printf("%s\n",ciphertext_binary);
    ciphertext_len = strlen(ciphertext_binary);

    fclose(f_in);


    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_CipherInit(ctx,EVP_chacha20(), key_bin, iv_bin, DECRYPT);
   
    unsigned char decrypted[ciphertext_len]; //may be larger than needed due to padding
    int update_len, final_len;
    int decrypted_len=0;

    EVP_CipherUpdate(ctx,decrypted,&update_len,ciphertext_binary,ciphertext_len);
    decrypted_len+=update_len;
    printf("update size: %d\n",decrypted_len);

    EVP_CipherFinal_ex(ctx,decrypted+decrypted_len,&final_len);
    decrypted_len+=final_len;

    EVP_CIPHER_CTX_free(ctx);

    printf("Plaintext lenght = %d\n",decrypted_len);
    for(int i = 0; i < decrypted_len; i++)
        printf("%02x", decrypted[i]);
    printf("\n");
    
    for(int i = 0; i < decrypted_len; i++)
        printf("%c", decrypted[i]);
    printf("\n");

    return 0;
}




