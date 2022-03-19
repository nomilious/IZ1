#ifndef HEADER_READ
#include "header.h"
#define HEADER_READ

Post* create_post(FILE*);
char* insert_text(FILE*, bool);
struct tm* insert_date(FILE*);
Comm* insert_comm(Comm*, struct tm*, FILE*);
#endif