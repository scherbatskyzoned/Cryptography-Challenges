#include <stdio.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/err.h>

#define ENCRYPT 1
#define DECRYPT 0


void handleErrors(){
    ERR_print_errors_fp(stderr);
    abort();
}

int main()
{
    

    unsigned char key[] = "0123456789ABCDEF"; // ASCII, 16 bytes
    unsigned char iv[]  = "1111111111111111"; // ASCII 

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    // Initialization
    EVP_CipherInit(ctx,EVP_aes_128_cbc(), key, iv, ENCRYPT);

    // Disable padding
    if (1 != EVP_CIPHER_CTX_set_padding(ctx, 0)) {
        handleErrors();
    }

    unsigned char plaintext[] = "This is the plaintext to encrypt."; //len 33
    unsigned char ciphertext[48]; // First multiple of 16 bytes greater than len(plaintext)

    int update_len, final_len;
    int ciphertext_len=0;

    EVP_CipherUpdate(ctx,ciphertext,&update_len,plaintext,strlen(plaintext));
    ciphertext_len+=update_len;
    printf("update size: %d\n",ciphertext_len);

    EVP_CipherFinal_ex(ctx,ciphertext+ciphertext_len,&final_len);
    ciphertext_len+=final_len;

    EVP_CIPHER_CTX_free(ctx);

    printf("Ciphertext lenght = %d\n", ciphertext_len);
    for(int i = 0; i < ciphertext_len; i++)
        printf("%02x", ciphertext[i]);
    printf("\n");

    return 0;
}

