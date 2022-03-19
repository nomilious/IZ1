#ifndef HEADER_INIT
#include "header.h"
#define HEADER_INIT

Post* init_post(char*, Comm_container, struct tm*, char*);
void free_post(Post**);
void free_blog(Post***, int);
Comm_container init(int);
void free_comm(Comm_container*);
#endif