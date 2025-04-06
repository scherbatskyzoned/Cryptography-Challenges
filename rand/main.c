#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char *rand1 = "ed-8a-3b-e8-17-68-38-78-f6-b1-77-3e-73-b3-f7-97-f3-00-47-76-54-ee-8d-51-0a-2f-10-79-17-f8-ea-d8-81-83-6e-0f-0c-b8-49-5a-77-ef-2d-62-b6-5e-e2-10-69-d6-cc-d6-a0-77-a2-0a-d3-f7-9f-a7-9e-a7-c9-08"; 
// char *rand2 = "4c-75-82-ca-02-07-bd-1d-8d-52-f0-6c-7a-d6-b7-87-83-95-06-2f-e0-f7-d4-24-f8-03-68-97-41-4c-85-29-e5-0d-b0-e4-3c-ee-74-dc-18-8a-aa-26-f0-46-94-e8-52-91-4a-43-8f-dd-ea-bb-a8-cf-51-14-79-ec-17-c2";


int main() {
    char *rand1[64] = {"ed", "8a", "3b", "e8", "17", "68", "38", "78", "f6", "b1", "77", "3e", "73", "b3", "f7", "97", "f3", "00", "47", "76", "54", "ee", "8d", "51", "0a", "2f", "10", "79", "17", "f8", "ea", "d8", "81", "83", "6e", "0f", "0c", "b8", "49", "5a", "77", "ef", "2d", "62", "b6", "5e", "e2", "10", "69", "d6", "cc", "d6", "a0", "77", "a2", "0a", "d3", "f7", "9f", "a7", "9e", "a7", "c9", "08"};
    char *rand2[64] = {"4c", "75", "82", "ca", "02", "07", "bd", "1d", "8d", "52", "f0", "6c", "7a", "d6", "b7", "87", "83", "95", "06", "2f", "e0", "f7", "d4", "24", "f8", "03", "68", "97", "41", "4c", "85", "29", "e5", "0d", "b0", "e4", "3c", "ee", "74", "dc", "18", "8a", "aa", "26", "f0", "46", "94", "e8", "52", "91", "4a", "43", "8f", "dd", "ea", "bb", "a8", "cf", "51", "14", "79", "ec", "17", "c2"};
    int hexRand1[64];
    int hexRand2[64];

    for (int i = 0; i < 64; i++) {
        hexRand1[i] = (int) strtol(rand1[i], NULL, 16);
        hexRand2[i] = (int) strtol(rand2[i], NULL, 16);
    }

    int k1[64], k2[64];

    for (int i = 0; i < 64; i++) {
        k1[i] = hexRand1[i] | hexRand2[i];
        k2[i] = hexRand1[i] & hexRand2[i];
    }

    int key[64];

    for (int i = 0; i < 64; i++)
        key[i] = k1[i] ^ k2[i];
    int i;
    printf("CRYPTO25{");
    for (i = 0; i < 64 - 1; i++)
        printf("%02x-", key[i]);
    printf("%02x}", key[i]);
    
}

