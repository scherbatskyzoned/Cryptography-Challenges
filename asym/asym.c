#include <stdio.h>
#include <openssl/bn.h>
#include <string.h>
#include <ctype.h>
int main() {
    unsigned char value1_hex[] = "009eee82dc2cd4a00c4f5a7b8663b0c1ed0677fcebde1a235df4c3ff876a7dadc607faa835f6ae0503573e223676d50d574f99f958ad637ae745a6aafa023423b69d34157b1141b6b1cab91acd2955bd42f504abdf454a9d4eca4e01f9f8745967eeb6a9fb96b7c09400178a530eb6d831c968e66438d3633a04d7886bf0e1ad607f41bd857bd904e1975b1f9b05ceac2cc4553fb48b894d0a509a094e5e8f5b5f5569725f049b3a8a09b47f8db2ca520e5ebff4b0eec9badc934f6dd31f821ad9fc2ca73f18230dd744c728546784ee739265f01ce81e6d4d9565b4c84fb80462582bee3264a0a7dc99250e505376bc30db715e93d69f1f881c765d82c8593951";
    // 256 + 1 = key len + 1
    unsigned char value2_hex[] = "00d2c601326b4c4b855f527bb78ed68ae4c8767e6bc9249a3ecacd2fc9b875d4f97111e1cfbe62d32c5ff9fd9bfaed62f3df44c757fbee9bb232cb5449296c692e301d8c1ffab18ee44966c1fb927c82ca60c940a40ab2db50ecf6ff98a71623388d06d27ca9858ac22b4dd4e6f189e5b04254a05f3cddc764330511fbee8b2607";
    // 128 + 1 = N 
    BIGNUM *N = BN_new(), *p = BN_new(), *q = BN_new();
    
    // one is N the other is p 
    BN_hex2bn(&N, value1_hex);
    BN_hex2bn(&p, value2_hex);
    


    BN_div(q, NULL, N, p, BN_CTX_new());
    // printf("a / b = ");
    // BN_print_fp(stdout, N);
    // printf("\n");

    // printf("a mod b = ");
    // BN_print_fp(stdout, p);
    // puts("");
    
    char *q_hex = BN_bn2hex(q);

    for (int i = 0; i < strlen(q_hex); i++) {
        q_hex[i] = tolower(q_hex[i]);
    }
    printf("CRYPTO25{00");
    for (int i = 0; i < strlen(q_hex); i++) {
        if (i % 2 == 0)
            printf(":");
        printf("%c", q_hex[i]);
    }
    printf("}\n");
    BN_free(N);
    BN_free(p);

}



