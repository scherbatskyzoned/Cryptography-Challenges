#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <ctype.h>

#define ENCRYPT 1
#define DECRYPT 0

int isHumanReadable(const char *str, int len) {
    if (len == 0)
        return 0;
    for (int i=0; i < len; i++) {
        if (!isprint(str[i]) && !isspace(str[i]))
            return 0;
    }
    return 1;
}

int main() {
    // ARIA-128-CBC
    unsigned char key[] = "0123456789ABCDEF";
    unsigned char iv[] = "0123456789ABCDEF";
    unsigned char ciphertext_b64[] = "ZZJ+BKJNdpXA2jaX8Zg5ItRola18hi95MG8fA/9RPvg=";
    const EVP_CIPHER *evp_ciphers[] = {
        EVP_aes_128_ecb(),
        EVP_aes_128_cbc(),
        EVP_aes_128_ofb(),
        EVP_aes_128_cfb(),
        EVP_aes_128_cfb1(),
        EVP_aes_128_cfb8(),
        EVP_aes_128_ctr(),
        EVP_aes_128_gcm(),
        EVP_aes_128_ccm(),
        EVP_aes_128_xts(),
        EVP_aes_192_ecb(),
        EVP_aes_192_cbc(),
        EVP_aes_192_ofb(),
        EVP_aes_192_cfb(),
        EVP_aes_192_cfb1(),
        EVP_aes_192_cfb8(),
        EVP_aes_192_ctr(),
        EVP_aes_192_gcm(),
        EVP_aes_192_ccm(),
        EVP_aes_256_ecb(),
        EVP_aes_256_cbc(),
        EVP_aes_256_ofb(),
        EVP_aes_256_cfb(),
        EVP_aes_256_cfb1(),
        EVP_aes_256_cfb8(),
        EVP_aes_256_ctr(),
        EVP_aes_256_gcm(),
        EVP_aes_256_ccm(),
        EVP_aes_256_xts(),
        EVP_aria_128_ecb(),
        EVP_aria_128_cbc(),
        EVP_aria_128_ofb(),
        EVP_aria_128_cfb(),
        EVP_aria_128_ctr(),
        EVP_aria_128_gcm(),
        EVP_aria_128_ccm(),
        EVP_aria_192_ecb(),
        EVP_aria_192_cbc(),
        EVP_aria_192_ofb(),
        EVP_aria_192_cfb(),
        EVP_aria_192_ctr(),
        EVP_aria_192_gcm(),
        EVP_aria_192_ccm(),
        EVP_aria_256_ecb(),
        EVP_aria_256_cbc(),
        EVP_aria_256_ofb(),
        EVP_aria_256_cfb(),
        EVP_aria_256_ctr(),
        EVP_aria_256_gcm(),
        EVP_aria_256_ccm(),
        EVP_camellia_128_ecb(),
        EVP_camellia_128_cbc(),
        EVP_camellia_128_ofb(),
        EVP_camellia_128_cfb(),
        EVP_camellia_128_ctr(),
        EVP_camellia_192_ecb(),
        EVP_camellia_192_cbc(),
        EVP_camellia_192_ofb(),
        EVP_camellia_192_cfb(),
        EVP_camellia_192_ctr(),
        EVP_camellia_256_ecb(),
        EVP_camellia_256_cbc(),
        EVP_camellia_256_ofb(),
        EVP_camellia_256_cfb(),
        EVP_camellia_256_ctr(),
        EVP_des_ecb(),
        EVP_des_cbc(),
        EVP_des_ofb(),
        EVP_des_cfb(),
        EVP_des_cfb1(),
        EVP_des_cfb8(),
        EVP_des_ede_ecb(),
        EVP_des_ede_cbc(),
        EVP_des_ede_ofb(),
        EVP_des_ede_cfb(),
        EVP_des_ede3_ecb(),
        EVP_des_ede3_cbc(),
        EVP_des_ede3_ofb(),
        EVP_des_ede3_cfb(),
        EVP_des_ede3_cfb1(),
        EVP_des_ede3_cfb8(),
        EVP_bf_ecb(),
        EVP_bf_cbc(),
        EVP_bf_ofb(),
        EVP_bf_cfb(),
        EVP_cast5_ecb(),
        EVP_cast5_cbc(),
        EVP_cast5_ofb(),
        EVP_cast5_cfb(),
        EVP_rc2_ecb(),
        EVP_rc2_cbc(),
        EVP_rc2_64_cbc(),
        EVP_rc2_cfb(),
        EVP_rc2_ofb(),
        EVP_rc4(),
        EVP_rc4_40(),
        EVP_seed_ecb(),
        EVP_seed_cbc(),
        EVP_seed_ofb(),
        EVP_seed_cfb(),
        EVP_sm4_ecb(),
        EVP_sm4_cbc(),
        EVP_sm4_ofb(),
        EVP_sm4_cfb(),
        EVP_sm4_ctr(),
        NULL
    };

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    
    system("echo ZZJ+BKJNdpXA2jaX8Zg5ItRola18hi95MG8fA/9RPvg= | base64 -d > ciphertext.bin");
    
    // hex to bytes
    int key_len = strlen(key)/2;
    unsigned char key_bin[key_len];
    for(int i = 0; i < key_len;i++){
        sscanf(&key[2*i],"%2hhx", &key_bin[i]);
    }

    int iv_len = strlen(iv)/2;
    unsigned char iv_bin[iv_len];
    for(int i = 0; i < iv_len;i++){
        sscanf(&iv[2*i],"%2hhx", &iv_bin[i]);
    }

    FILE *fin = fopen("ciphertext.bin","r");
    if (fin == NULL) {
        printf("Error opening file\n");
        abort();
    }
    unsigned char ciphertext_binary[1024];
    int ciphertext_len;

    while (fscanf(fin,"%s",ciphertext_binary) != EOF);
        // printf("%s\n",ciphertext_binary);
    ciphertext_len = strlen(ciphertext_binary);

    fclose(fin);

    int i=0;
    while (evp_ciphers[i] != NULL) {
        unsigned char decrypted[ciphertext_len]; //may be larger than needed due to padding
        int update_len, final_len;
        int decrypted_len=0;
        
        // printf("Trying cipher: %s\n", EVP_CIPHER_name(evp_ciphers[i]));
        
        EVP_CipherInit(ctx,evp_ciphers[i], key, iv, DECRYPT);
        EVP_CipherUpdate(ctx,decrypted,&update_len,ciphertext_binary,ciphertext_len);
    
        decrypted_len+=update_len;

        EVP_CipherFinal_ex(ctx, decrypted+decrypted_len, &final_len);
        decrypted_len+=final_len;
        
        // Print the flag
        // for(int i = 0; i < decrypted_len; i++)
        //     printf("%2x", decrypted[i]);
        // printf("\n");
        if (isHumanReadable(decrypted, decrypted_len)) {
            printf("Trying cipher: %s\n", EVP_CIPHER_name(evp_ciphers[i]));
            for(int i = 0; i < decrypted_len; i++)
                printf("%c", decrypted[i]);
            printf("\n\n");
        }

        i++;
    }

    EVP_CIPHER_CTX_free(ctx);

    return 0;
}
