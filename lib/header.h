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
// init.c
Post* init_post(char*, Comm_container, struct tm*, char*);
void free_post(Post**);
void free_blog(Post***, int);
Comm_container init(int);
void free_comm(Comm_container*);
// read.c
Post* create_post(FILE*);
char* insert_text(FILE*, bool);
struct tm* insert_date(FILE*);
Comm* insert_comm(Comm*, struct tm*, FILE*);
// tools.c
char* format(char*);
bool is_valid_date(int, int, int);
void clear_buff(FILE*);
int find_ind(int[], int, int);
int largest(int[], int);
int realloc_comm(Comm_container*);
bool commented_in_1month(struct tm*, struct tm*);
bool is_valid_comm_date(struct tm*, struct tm*);
int print_all(Post**, int);
int find_most_commented(Post**, int);
#endif
