#ifndef HEADER_NAME

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define STD_RATE_L 8  // L = Length
#define STD_TAG_L 16
#define STD_TITLE_L 32
#define HEADER_NAME
#define STD_TXT_L 128

typedef struct
{
    char* text;
    int rate;
    struct tm* date;
} Comm;
typedef struct
{
    Comm* comms;
    int capacity;
    int len;
} Comm_container;
typedef struct
{
    char* title;
    struct tm* cr_date;
    char* content;
    Comm_container ccomm;
} Post;
// tools.c
#endif
