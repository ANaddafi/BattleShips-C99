/// functions related to files and saves

#define DATA
#include <windows.h>
#include "map.h"

#ifndef STRUCT
#include "structs.h"
#endif // STRUCT

#define DIST_USER_LIST "./saves/testdata.bin"
#define DIST_MAP_LIST "./maps/map_list.txt"
#define DIST_LAST_GAME_SAVE "./saves/lastgame.bin"

//////////////////////////////////////////////////////

struct User get_user_from_file();
struct User get_user_by_order(int ord);
struct User get_new_user();

struct Map get_map_by_order(int ord);
struct Map get_map_from_file();
struct Map get_new_map();
struct Map get_bot_map();

struct GameData load_last_game_file();

void log(char err[1000], int ext);
void print_user_list();
void print_map_list();

/// error -> log
void log(char err[1000], int ext)
{
    printf("%s", err);
    Sleep(1500);
    if(ext)
        exit(0);
    else
        system("cls");
}


struct GameData load_game_file(char game_name[100])
{
    char tmp_name[100];
    strcpy(tmp_name, "./saves/");
    strcat(tmp_name, game_name);

    struct GameData ret_game;
}


struct GameData load_last_game()
{
    FILE *fgame = fopen(DIST_LAST_GAME_SAVE, "rb");
    if(fgame == NULL)
        log("FILE NOT FOUND!\n", 1);

    struct GameData gamedata;
    if(fread(&gamedata, sizeof(struct GameData), 1, fgame) < 1)
        log("Something went wrong!\n", 1);

    fclose(fgame);

    make_ship(&(gamedata.maps[0]));
    make_ship(&(gamedata.maps[1]));

    return gamedata;
}


void save_game_file(struct GameData *gamedata)
{
    FILE *fgame = fopen(DIST_LAST_GAME_SAVE, "wb");
    if(fgame == NULL)
        log("FILE NOT FOUND!\n", 1);

    if(fwrite(gamedata, sizeof(struct GameData), 1, fgame) < 1)
        log("Something went wrong!\n", 1);

    fclose(fgame);
}


void print_user_list()
{
    printf("Saved Users:\n");

    FILE *fusers = fopen(DIST_USER_LIST, "rb");
    if(fusers == NULL)
        fclose(fusers), log("FILE NOT FOUND!\n", 1);

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
        log("Invalid input, try again!\n", 0);
        return get_user_from_file();
    }

    FILE *fusers = fopen(DIST_USER_LIST, "rb");
    if(fusers == NULL)
        fclose(fusers), log("FILE NOT FOUND!\n", 1);


    while(ord > 0 && fread(&tmp_user, sizeof(struct User), 1, fusers))
        ord --;

    fclose(fusers);

    if(ord > 0)
    {
        log("Invalid input, try again!\n", 0);
        return get_user_from_file();
    }

    return tmp_user;
}


struct User get_user_from_file()
{
    system("cls");

    struct User ret_user;

    print_user_list();

    printf("\n>> ");
    int user_input = 0;
    scanf("%d", &user_input);

    ret_user = get_user_by_order(user_input);

    return ret_user;
}


void add_new_user(struct User new_user)
{
    FILE *fusers = fopen(DIST_USER_LIST, "ab");
    if(fusers == NULL)
        log("FILE NOT FOUND!\n", 1);

    if(fwrite(&new_user, sizeof(struct User), 1, fusers) < 1)
        log("Something went wrong!\n", 1);

    fclose(fusers);
}


struct User get_new_user()
{
    system("cls");

    struct User new_user;
    printf("Enter your username:\n");

    char user_input[100];
    scanf("%s", user_input);

    strcpy(new_user.user_name, user_input);
    new_user.total_score = 0;
    new_user.current_score = 0;

    add_new_user(new_user);

    system("cls");
    printf("Welcome, %s!", user_input);
    log("\n", 0);

    return new_user;
}


struct Map get_map_by_order(int ord)
{
    if(ord <= 0)
    {
        log("Invalid input, try again!\n", 0);
        return get_map_from_file();
    }

    FILE *fmaps = fopen(DIST_MAP_LIST, "r");
    if(fmaps == NULL)
        fclose(fmaps), log("FILE NOT FOUND!\n", 1);

    int cnt;
    fscanf(fmaps, "%d", &cnt);
    if(ord > cnt)
    {
        fclose(fmaps);
        log("Invalid input, try again!\n", 0);
        return get_map_from_file();
    }

    char map_name[100];
    while(ord >= 1)
        fscanf(fmaps, "%s", map_name), ord --;

    fclose(fmaps);

    return get_map_from_map_file(map_name);
}


void print_map_list()
{
    printf("Choose one of these maps:\n");

    FILE *fmaps = fopen(DIST_MAP_LIST, "r");
    if(fmaps == NULL)
        fclose(fmaps), log("FILE NOT FOUND!\n", 1);

    int cnt=0, i;
    fscanf(fmaps, "%d", &cnt);

    for(i = 0; i < cnt; i++)
    {
        char map_name[100];
        fscanf(fmaps, "%s", map_name);
        printf("%d) %s\n", i+1, map_name);
    }

    fclose(fmaps);
}


struct Map get_map_from_file()
{
    system("cls");

    struct Map ret_map;

    system("cls");
    print_map_list();

    int user_input;
    printf("\n>> ");
    scanf("%d", &user_input);

    ret_map = get_map_by_order(user_input);

    //printf("\n:TEST:\n");
    view_map(ret_map);
    //printf(":TEST:\n");
    //Sleep(3000);

    return ret_map;
}


struct Map get_new_map()
{

}


struct Map get_bot_map()
{
    /// not complete

    struct Map bot_map;
    return bot_map;
}
