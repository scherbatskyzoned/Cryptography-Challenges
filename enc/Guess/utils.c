#include <openssl/evp.h>
#include <openssl/obj_mac.h>
#include <openssl/objects.h>

#include <stdio.h>


void list_ciphers() {
    int nid;
    EVP_CIPHER *cipher;

    for (nid = 0; nid < OBJ_nid_count(); nid++) {
        if ((cipher = EVP_get_cipherbynid(nid)) != NULL) {
            printf("%s\n", OBJ_nid2sn(nid));
        }
    }
}