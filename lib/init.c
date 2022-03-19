#include "init.h"

Post* init_post(char* Title, Comm_container comments, struct tm* Date, char* Content) {
    Post* p = (Post*) calloc(1, sizeof(Post));
    if (!p || !Title || !Date || !comments.capacity || !Content) {
        printf("error calloc in init_post()");
        return NULL;
    }
    p->title = Title;
    p->cr_date = Date;
    p->ccomm = comments;
    p->content = Content;
    return p;
}

void free_post(Post** p) {
    free((*p)->title);
    free((*p)->cr_date);
    free_comm(&(*p)->ccomm);
    free((*p)->content);
    free((*p));
}

void free_comm(Comm_container* com) {
    Comm* c = com->comms;
    for (size_t i = 0; i < com->len; ++i) {
        free(c[i].date);
        free(c[i].text);
    }

    free(c);
}

void free_blog(Post*** post, int capacity) {
    if (capacity <= 0)
        return;
    for (size_t i = 0; i < capacity; i++)
        free_post(&(*post)[i]);
    free(*post);
}

Comm_container init(int capacity) {
    Comm_container c;
    c.len = 0;
    c.capacity = capacity;
    c.comms = (Comm*) calloc(c.capacity, sizeof(Comm));
    if (!c.comms) {
        printf("error calloc in init()\n");
        c.capacity = 0;
        return c;
    }
    return c;
}

int realloc_comm(Comm_container* c) {
    c->capacity *= 2;
    Comm* a = (Comm*) realloc(c->comms, sizeof(Comm) * c->capacity);
    if (!a) {
        printf("unable to realloc space for comm in realloc_comm()\n");
        return -1;
    }
    c->comms = a;
    for (size_t i = c->len; i < c->capacity; i++) {
        c->comms[i].date = NULL;
        c->comms[i].text = NULL;
    }
    return 0;
}
