#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/err.h>
#include <string.h>

#define MAXBUF 1024

void handle_errors(){
    ERR_print_errors_fp(stderr);
    abort();
}


int main(int argc, char **argv){
       
       unsigned char key[] = "keykeykeykeykeykey";
      
        if(argc != 3){
            fprintf(stderr,"Invalid parameters. Usage: %s filename1 filename2\n",argv[0]);
            exit(1);
        }


        FILE *f_in1, *f_in2;
        if((f_in1 = fopen(argv[1],"r")) == NULL) {
                fprintf(stderr,"Couldn't open the input file, try again\n");
                exit(1);
        }
        if ((f_in2 = fopen(argv[2],"r")) == NULL) {
                fprintf(stderr,"Couldn't open the input file, try again\n");
                exit(1);
        }


        /* Load the human readable error strings for libcrypto */
        ERR_load_crypto_strings();
        /* Load all digest and cipher algorithms */
        OpenSSL_add_all_algorithms();

       //EVP_MD_CTX *EVP_MD_CTX_new(void);
       //pedantic mode? Check if md == NULL
		HMAC_CTX  *hmac_ctx = HMAC_CTX_new();

        //int EVP_DigestInit(EVP_MD_CTX *ctx, const EVP_MD *type);
        // int EVP_DigestInit_ex(EVP_MD_CTX *ctx, const EVP_MD *type, ENGINE *impl);
        // Returns 1 for success and 0 for failure.
        if(!HMAC_Init_ex(hmac_ctx, key, strlen(key), EVP_sha256(), NULL))
            handle_errors();

        int n1;
        unsigned char buffer1[MAXBUF];
        while((n1 = fread(buffer1,1,MAXBUF,f_in1)) > 0){
        // Returns 1 for success and 0 for failure.
            if(!HMAC_Update(hmac_ctx, buffer1, n1))
                handle_errors();
        }
        int n2;
        unsigned char buffer2[MAXBUF];
        while((n2 = fread(buffer2,1,MAXBUF,f_in2)) > 0){
        // Returns 1 for success and 0 for failure.
            if(!HMAC_Update(hmac_ctx, buffer2, n2))
                handle_errors();
        }


        unsigned char hmac_value[HMAC_size(hmac_ctx)];
        int hmac_len;

        //int EVP_DigestFinal_ex(EVP_MD_CTX *ctx, unsigned char *md, unsigned int *s);
        if(!HMAC_Final(hmac_ctx, hmac_value, &hmac_len))
            handle_errors();

        // void EVP_MD_CTX_free(EVP_MD_CTX *ctx);
		HMAC_CTX_free(hmac_ctx);

        printf("The HMAC is: ");
        for(int i = 0; i < hmac_len; i++)
			     printf("%02x", hmac_value[i]);
        printf("\n");


        // completely free all the cipher data
        CRYPTO_cleanup_all_ex_data();
        /* Remove error strings */
        ERR_free_strings();


	return 0;

}
