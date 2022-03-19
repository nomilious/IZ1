#ifndef HEADER_TOOLS
#include "header.h"
#define HEADER_TOOLS

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