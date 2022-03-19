#include <gtest/gtest.h>
extern "C" {
#include "header.h"
#include "init.h"
#include "read.h"
#include "tools.h"
}
TEST(insert_date, Test_date) {
    //                      1                           2
    char* str = (char*) "1.1.11\n29.2.2021\n30git.2.2020\n35.4.2021\n11/2/11\n";
    FILE* stdin_t = fmemopen(str, strlen(str), "r");
    struct tm* date1 = insert_date(stdin_t);
    struct tm* date2 = insert_date(stdin_t);

    EXPECT_EQ(0, commented_in_1month(date1, date2));
    fclose(stdin_t);
    free(date1);
    free(date2);
}
TEST(find_most_commented, Test_cout_funcs_and_rate_and_reallocation) {
    char* str1 = (char*) "\nTitle\n1.1.11\nMY LONG LONG TEXTMY\n LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXTMY LONG LONG TEXT\n\nVery interesting post\n1/1/11\n4\nI'd like another post from U\n2,1,11\n5\nOMG\n13.4.2021\n5\n...\n11/2/11\n1\nVery interesting post\n1/1/11\n4\nI'd like another post from U\n2,a,11\n2.1.11\n5\nOMG\n13.4.2021\n5\n...\n11/2/11\n1\nVery interesting post\n1/1/11\n4\nI'd like another post from U\n2,1,11\n5\nOMG\n13.4.2021\n5\n...\n11/2/11\n1\nVery interesting post\n1/1/11\n4\nI'd like another post from U\n2,1,11\n5\nOMG\n13.4.2021\n5\n...\n11/2/11\n1\nVery interesting post\n1/1/11\n4\nI'd like another post from U\n2,1,11\n5\nOMG\n13.4.2021\n5\n...\n11/2/11\n1\nVery interesting post\n1/1/11\n4\nI'd like another post from U\n2,1,11\n5\nOMG\n13.4.2021\n5\n...\n11/2/11\n1\nVery interesting post\n1/1/11\n4\nI'd like another post from U\n2,1,11\n5\nOMG\n13.4.2021\n5\n...\n11/2/11\n1\n\n";
    char* str = (char*) "Title2\n11.2.11\nMY LONG TEXT\n\nAwful post\n12/2/11\n0\nI wouldn't like another post from U\n6,3,11\n-1\n0\nOMG\n13.4.2021\n1\nAwful post\n12/2/11\n0\nAwful post\n12/2/11\n0\nAwful post\n12/2/11\n0\nAwful post\n12/2/11\n0\nAwful post\n12/2/11\n0\nAwful post\n12/2/11\n0\nAwful post\n12/2/11\n0\n\n";
    FILE *stdin_t, *stdin_t1;
    Post** post = (Post**) calloc(2, sizeof(Post));

    stdin_t = fmemopen(str, strlen(str), "r");
    stdin_t1 = fmemopen(str1, strlen(str1), "r");

    post[0] = create_post(stdin_t);
    post[1] = create_post(stdin_t1);
    EXPECT_EQ(1, find_most_commented(post, 2));
    EXPECT_EQ(0, print_all(post, 2));

    fclose(stdin_t);
    fclose(stdin_t1);
    free_blog(&post, 2);
}