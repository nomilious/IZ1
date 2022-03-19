#include "header.h"
#include "init.h"
#include "read.h"
#include "tools.h"
int main() {
    int capacity = 4;
    int len = 0;
    int choice;
    Post** posts = (Post**) calloc(capacity, sizeof(Post*));
    if (!posts) {
        printf("error calloc in main()\n");
        return 1;
    }

    do {
        printf("=======================================================\n");
        printf("\tВаш выбор?\n");
        printf("\t1 - ввести новуую запись \n");
        printf("\t2 - вывессти все записи (%d записей)\n", len);
        printf("\t3 - вывессти самые популярные записи(по коом+оценке) \n");
        printf("\t4 - выход \n");
        printf("=======================================================\n");
        fscanf(stdin, "%d%*c", &choice);

        switch (choice) {
            case (1):
                if (len >= capacity - 1) {
                    capacity *= 2;
                    Post** aa = (Post**) realloc(posts, sizeof(Post*) * capacity);
                    if (!aa) {
                        printf("unable to realloc space for post\n");
                        free_blog(&posts, len);
                        return 0;
                    }
                    posts = aa;
                }
                posts[len] = create_post(stdin);
                if (!posts[len]) {
                    free_blog(&posts, len);
                    return 0;
                }
                len++;
                break;
            case (2):
                print_all(posts, len);
                break;
            case (3):
                if (len > 0 && !find_most_commented(posts, len)) {
                    free_blog(&posts, len);
                    return 0;
                }
                break;
            case (4):
                break;
            default:
                clear_buff(stdin);
        }
    } while (choice != 4);

    free_blog(&posts, len);
    return 0;
}
