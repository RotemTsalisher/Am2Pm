#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* a program to change a string the represents time in an 12 hr clock to 24 hr clock
* input string will include 'AM' or 'PM' at the end of the string
* output string will present the time in 24 hr clock
* note: 24:00:00 is represented as 00:00:00
* 
* solution is based on changin the hr section only (and droping the AM/PM statement):
* AM time will be returned as is (except for 12 AM)
* PM time will be returned with the logic of adding 12 to the hr field and then mod(24)
* case 1 (PM): 00->07 add 0x0102
* case 2 (PM): 08->09 add 0x01F8
* case 3 (PM): 10->11 add 0x0102 (same as case 1)
* case 4 (AM): 12 -> change to 0x3030 */



#define AM 0x414d
#define PM 0x504d

typedef short char16;

void add12(void);
void add0x1F8(void);
void change24to00(void);
char* timeConversion(char* s);

char* returnString;
char16 hrReg;

void main()
{
    char* result = timeConversion("09:05:45PM");
    printf("Input string: 09:05:45PM\n");
    printf("Outpur string: %s\n", result);
}

char* timeConversion(char* s) {

    returnString = (char*)malloc(sizeof(char) * 9);
    int i;
    char16 AmOrPm;

    hrReg = 0x0000;
    AmOrPm = 0x0000;
    returnString[0] = 0x00;
    returnString[1] = 0x00;

    hrReg |= s[0];
    hrReg = hrReg << 8;
    hrReg |= s[1];
    AmOrPm |= s[8];
    AmOrPm = AmOrPm << 8;
    AmOrPm |= s[9];

    for (i = 2;i < 8;i++)
    {
        returnString[i] = s[i];
    }

    switch (AmOrPm)
    {
    case PM:
        if ((hrReg < 0x3038) ||
            ((hrReg > 0x3039) && (hrReg < 0x3132)))
        {
            add12();
        }
        else if ((hrReg > 0x3037) && (hrReg < 0x3130))
        {
            add0x1F8();
        }
        break;

    case AM:
        if (hrReg == 0x3132)
        {
            change24to00();
        }
        break;

    default:
        break;
    }

    returnString[1] |= hrReg;
    returnString[0] |= (hrReg >> 8);

    returnString[8] = '\0';
    return returnString;
}
void add12(void) {
    char16 tmp = 0x0102;
    hrReg += tmp;
}
void add0x1F8(void) {
    char16 tmp = 0x01F8;
    hrReg += tmp;
}
void change24to00(void) {
    char16 tmp = 0x3030;
    hrReg = tmp;
}
