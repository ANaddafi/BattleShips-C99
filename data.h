/// functions related to files and saves

#define DATA
#include <windows.h>

#ifndef STRUCT
#include "structs.h"
#endif // STRUCT

#define DIST_USER_LIST "./saves/testdata.bin"

//////////////////////////////////////////////////////

struct User get_user_from_file();
struct User get_user_by_order(int ord);
struct Map get_map(struct User user);
struct Map get_bot_map();
void error(char err[1000], int ext);
void print_user_list();


void error(char err[1000], int ext)
{
    printf("%s", err);
    Sleep(1500);
    if(ext)
        exit(0);
    else
        system("cls");
}

void print_user_list()
{
    printf("Saved Users:\n");

    FILE *fusers = fopen(DIST_USER_LIST, "rb");
    if(fusers == NULL)
        error("FILE NOT FOUND!\n", 1);

    int cnt = 1;
    struct User tmp_user;
    while(fread(&tmp_user, sizeof(struct User), 1, fusers))
        printf("%d) ", cnt++), print_user(tmp_user);

    fclose(fusers);
}

struct User get_user_by_order(int ord)
{
    struct User tmp_user;

    if(ord <= 0)
    {
        error("Invalid input, try again!\n", 0);
        return get_user_from_file();
    }

    FILE *fusers = fopen(DIST_USER_LIST, "rb");
    if(fusers == NULL)
        error("FILE NOT FOUND!\n", 1);


    while(ord > 0 && fread(&tmp_user, sizeof(struct User), 1, fusers))
        ord --;

    fclose(fusers);

    if(ord > 0)
    {
        error("Invalid input, try again!\n", 0);
        return get_user_from_file();
    }

    return tmp_user;
}

struct User get_user_from_file()
{
    /// not complete

    struct User ret_user;

    print_user_list();

    printf("\n>> ");
    int user_input = 0;
    scanf("%d", &user_input);

    ret_user = get_user_by_order(user_input);

    return ret_user;
}

struct User get_new_user()
{
    /// not complete

    struct User ret_user;
    return ret_user;
}

struct Map get_map(struct User user)
{
    /// not complete

    struct Map ret_map;
    return ret_map;
}

struct Map get_bot_map()
{
    /// mot complete

    struct Map bot_map;
    return bot_map;
}
