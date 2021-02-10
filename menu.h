/// functions related to menu

#define MENU
#define BOT_NAME "_bot_"
#define CLS system("cls")

#include <windows.h>
#include "structs.h"
#include "data.h"

struct GameData show_menu();
struct GameData load_game();
struct GameData load_last_game();
struct GameData init_game(int mod);

struct User get_user();
struct User get_bot();
struct Map get_map();

void exit_game();

struct GameData show_menu()
{
    /// displays the initial menu of the game
    /// returns a game status

    printf("WELCOME TO THE GAME OF BATTLESHIPS!\n\n");
    printf("Please select what you want to do:\n\n");

    printf("1) Play with a friend\n");
    printf("2) Play with computer\n");
    printf("3) Load game\n");
    printf("4) Load last game\n");
    printf("5) Settings\n");
    printf("6) ScoreBoard\n");
    printf("7) Exit\n\n>> ");

    int user_input = 0;
    scanf("%d", &user_input);
    system("cls");

    struct GameData ret_game;

    switch(user_input)
    {
        case 1:
            ret_game = init_game(0);
            return ret_game;

        case 2:
            ret_game = init_game(1);
            return ret_game;

        case 3:
            ret_game = load_game();
            return ret_game;

        case 4:
            ret_game = load_last_game();
            return ret_game;

        case 5:
            break;

        case 6:
            break;

        case 7:
            exit_game();
            break;

        default: // invalid input
            printf("\nInvalid input! please try again!");
            Sleep(1000);
            system("cls");
            return show_menu();
    }
}

struct User get_user(int turn)
{
    system("cls");
    printf("Please choose a user for player%d:\n\n", turn);
    printf("1) Choose from available users\n");
    printf("2) New user\n\n>> ");

    int user_input = 0;
    scanf("%d", &user_input);

    struct User ret_user;
    switch(user_input)
    {
        case 1:
            ret_user = get_user_from_file();
            break;

        case 2:
            ret_user = get_new_user();
            break;

        default:
            printf("\nInvalid input! please try again!");
            Sleep(1000);
            system("cls");
            ret_user = get_user(turn);
    }

    return ret_user;
}

struct User get_bot()
{
    struct User bot;

    strcpy(bot.user_name, BOT_NAME);
    bot.total_score = 0;
    bot.current_score = 0;

    return bot;
}


struct Map get_map()
{
    system("cls");
    printf("Please choose your map:\n\n");
    printf("1) Choose from available maps\n");
    printf("2) New map\n\n>> ");

    int user_input = 0;
    scanf("%d", &user_input);

    struct Map ret_map;
    switch(user_input)
    {
        case 1:
            ret_map = get_map_from_file();
            break;

        case 2:
            ret_map = get_new_map();
            break;

        default:
            printf("\nInvalid input! please try again!");
            Sleep(1000);
            system("cls");
            ret_map = get_map();
    }

    return ret_map;
}

struct GameData init_game(int mod)
{
    struct User user1 = get_user(1);
    struct Map map1 = get_map();

    struct User user2;
    struct Map map2;

    if(mod == 0)
    {
        user2 = get_user(2);
        map2 = get_map();
    }
    else
    {
        user2 = get_bot();
        map2 = get_bot_map();
    }

    system("cls");
    printf("<<< %s VS %s >>>\n", user1.user_name, user2.user_name);
    Sleep(2000);

    struct GameData ret_game;

    ret_game.users[0] = user1;
    ret_game.users[1] = user2;

    ret_game.maps[0] = map1;
    ret_game.maps[1] = map2;

    ret_game.winner = -1;
    ret_game.finished = 0;
    ret_game.used_rocket[0] = 0;
    ret_game.used_rocket[1] = 0;

    return ret_game;
}

struct GameData load_game()
{

}

struct GameData load_last_game()
{
    return load_last_game_file();
}

void exit_game()
{
    system("cls");
    printf("Thanks for playing!\n");
    Sleep(2000);
    exit(0);
}
