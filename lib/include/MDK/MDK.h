#ifndef MDK_H
#define MDK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h> // for unit8_t

using namespace std;

public:
    class MDK_MAIN {
        void macros() {
            #define MDK_MAIN_REGION void main()
            #define MDK_PRIVATE_REGION private:
            #define MDK_REZERVED_REGION #pragma region
            #define MDK_PRESERVE_VOID void prev()
            #define MDK_FUNC void func()
            #define MDK_PROGRAMMABLE_BINARY { void mkbin() {
                srand((unsigned int)time(NULL));
                unit8_t random_byte = (unit8_t)rand();
                printf("Bin: 0x%02X\n", random_byte);

                printf("IO: ");
                for (int i = 7; i >= 0; i--) {
                    printf("%d", (random_byte >> i) & 1);
                }
                printf("\n")
                return 0;
            }
            } }
    }

#endif // MDK_H