#include "read.h"

#include "init.h"
#include "tools.h"

Post* create_post(FILE* f) {
    char* title = NULL;
    char* text = NULL;
    char ch;
    struct tm* date = NULL;
    Post* post;
    Comm_container com_container;

    // title
    printf("Введите названеи: ");
    title = insert_text(f, 1);
    if (!title)
        return NULL;
    title = format(title);
    if (!title)
        return NULL;

    // date of creation
    date = insert_date(f);
    if (!date) {
        free(title);
        return NULL;
    }
    // content
    printf("Введите текcт: ");
    text = insert_text(f, 0);
    if (!text) {
        free(title);
        free(date);
        return NULL;
    }
    text = format(text);
    com_container = init(4);
    if (!text || com_container.capacity == 0) {
        free(title);
        free(date);
        return NULL;
    }

    // Comments+rate+their date
    while (1) {
        printf("Введите комментарий(\\n для выхода): ");
        fscanf(f, "%c", &ch);
        if (ch == '\n')
            break;
        ungetc(ch, f);
        if (com_container.len >= com_container.capacity - 1) {  // realloc for next comments
            if (realloc_comm(&com_container) == -1) {
                free(title);
                free(date);
                free(text);
                free_comm(&com_container);
                return NULL;
            }
        }
        insert_comm(&(com_container.comms[com_container.len]), date, f);
        com_container.len++;
    }
    // Create the post

    post = init_post(title, com_container, date, text);
    if (!post) {
        free(title);
        free(date);
        free(text);
        free_comm(&com_container);
        return NULL;
    }
    return post;
}

struct tm* insert_date(FILE* f) {
    struct tm* date = (struct tm*) calloc(1, sizeof(struct tm));
    int d = -1, m = -1, y = -1;
    if (!date) {
        printf("error calloc in insert_date()\n");
        return NULL;
    }
    do {
        printf("Введите дату(Формат DD:MM:(YYY)Y: ");
        if (fscanf(f, "%d%*c%d%*c%d%*c", &d, &m, &y) != 3)  // if inputting error happend
            clear_buff(f);
        y = (y < 100) ? (y + 2000) : y;  // если вводить год двумя цифрами
    } while (!is_valid_date(d, m, y));
    date->tm_mday = d;
    date->tm_mon = (--m);
    date->tm_year = y;
    date->tm_yday = date->tm_wday = date->tm_sec = date->tm_min = date->tm_isdst = date->tm_hour = 0;
    return date;
}

Comm* insert_comm(Comm* cur_comm, struct tm* date, FILE* f) {
    int n = 100;

    cur_comm->text = insert_text(f, 1);
    cur_comm->text = format(cur_comm->text);
    while (cur_comm->date == NULL) {
        cur_comm->date = insert_date(f);
        if (!is_valid_comm_date(date, cur_comm->date)) {
            printf("Введите ПРАВИЛЬНУЮ дату комментария. ");
            free(cur_comm->date);
            cur_comm->date = NULL;
        }
    }
    cur_comm->rate = -1;
    while (cur_comm->rate == -1) {
        printf("Введите оценку(от 0 до 5): ");
        fscanf(f, "%d%*c", &n);
        if (n <= 5 && n >= 0)
            cur_comm->rate = n;
        else  // input error happend
            clear_buff(f);
    }
    return cur_comm;
}

char* insert_text(FILE* f, bool No_additionalLF) {
    int capacity = STD_TXT_L;
    char* text = NULL;
    char ch;
    int read = 0;

    text = (char*) calloc(capacity, sizeof(char));
    if (!text) {
        printf("error calloc in insert_text()\n");
        return NULL;
    }
    do {
        fscanf(f, "%1c", &ch);
        while (ch == '\n')  // не допускается ввод пустого названия/комментария...
            fscanf(f, "%1c", &ch);
        ungetc(ch, f);
        fgets(&text[read], STD_TXT_L, f);
        read = strlen(text);
        if (strchr(text, '\n') && No_additionalLF) {
            break;
        } else {  // выделяем буфер такой же длины на чтение
            capacity = read + STD_TXT_L;
            char* a = realloc(text, sizeof(char) * capacity);
            if (!a) {
                printf("error realloc in insert_text()\n");
                free(text);
                return NULL;
            }
            text = a;
        }
        fscanf(f, "%1c", &ch);
        if (ch == '\n')  // проверяет на выход из режима ввода
            break;
        else
            ungetc(ch, f);
    } while (ch != EOF);
    return text;
}
