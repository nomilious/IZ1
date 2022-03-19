#include "tools.h"

bool is_valid_date(int day, int month, int year) {
    bool isValidDate = true;
    bool isLeap = (year % 4 == 0);

    if (day < 1 || day > 31 || month < 1 || month > 12)
        isValidDate = false;
    if (month == 2 && day > 29 && isLeap)
        isValidDate = false;
    if (month == 2 && day > 28 && !isLeap)
        isValidDate = false;
    if (month == 4 || month == 6 || month == 9 || month == 11)
        if (day > 30)
            isValidDate = false;

    return isValidDate;
}

bool is_valid_comm_date(struct tm* d1, struct tm* d2) {
    return (difftime(mktime(d2), mktime(d1)) >= 0);
}

char* format(char* old) {
    char* new = (char*) calloc(strlen(old), sizeof(char));
    int j = 0;

    if (!new) {
        printf("error calloc in format()\n");
        free(old);
        return NULL;
    }
    for (size_t i = 0; old[i] != '\0'; i++)
        if (old[i] != '\n' && old[i] != '\t' && !(j == 0 && old[i] == ' '))
            new[j++] = old[i];
    new[j] = '\0';
    free(old);
    return new;
}

void clear_buff(FILE* f) {
    char ch;
    do {
        fscanf(f, "%c", &ch);
    } while (ch != '\n');
}

bool commented_in_1month(struct tm* dt1, struct tm* dt2) {
    if (dt1->tm_mon == dt2->tm_mon)
        return true;
    else if (dt1->tm_mon + 1 == dt2->tm_mon && dt1->tm_mday >= dt2->tm_mday)
        return true;
    return false;
}

int largest(int arr[], int n) {
    int max = arr[0];
    for (size_t i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int find_ind(int arr[], int n, int value) {
    for (size_t i = 0; i < n; i++)
        if (arr[i] == value)
            return i;
    return -1;
}

int print_all(Post** a, int len) {
    for (size_t i = 0; i < len; i++) {
        printf("=======================================================\n");
        printf("\t\tPost №%zu\n", i + 1);
        printf("Title: %s\n", a[i]->title);
        printf("Date:%d/%d/%d\n", a[i]->cr_date->tm_mday,
               (a[i]->cr_date->tm_mon + 1), a[i]->cr_date->tm_year);
        printf("Text:%s\n", a[i]->content);
        printf("ALL COMMENTS:\n");
        for (size_t j = 0; j < a[i]->ccomm.len; j++) {
            Comm comm = a[i]->ccomm.comms[j];
            printf("%100s", comm.text);
            printf("\t%d", comm.rate);
            printf("\t%d/%d/%d\n", comm.date->tm_mday, (comm.date->tm_mon + 1),
                   comm.date->tm_year);
        }
        printf("=======================================================\n");
    }
    return 0;
}

int find_most_commented(Post** posts, int len) {  // returs 0 on error
    int* good_post_n = (int*) calloc(len, sizeof(int));
    int m, n;
    int k = 0;
    if (!good_post_n) {
        printf("unable to calloc space in find_most_commented()\n");
        return 0;
    }

    for (size_t i = 0; i < len; ++i)
        for (size_t j = 0; j < posts[i]->ccomm.len; ++j) {
            if (commented_in_1month(posts[i]->cr_date, posts[i]->ccomm.comms[j].date))
                good_post_n[i] += 1;  // заполняем четными чилслами
        }
    m = largest(good_post_n, len);
    while ((n = find_ind(good_post_n, len, m)) > -1 && m > 0) {
        k++;
        printf("Title %s\n", posts[n]->title);
        printf("Comments/Rates:\t%d\n", m);
        good_post_n[n] = -1;
    }
    free(good_post_n);
    return (k > 0) ? k : -1;
}
