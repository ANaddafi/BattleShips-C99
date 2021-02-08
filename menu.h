/// functions related to menu

#include <windows.h>
#include "structs.h"

struct GameData show_menu();
struct GameData load_game();
struct GameData load_last_game();
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

    switch(user_input)
    {
        case 1:

            break;
        case 2:

            break;
        case 3:
            return load_game();

        case 4:
            return load_last_game();

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

struct GameData load_game()
{

}

struct GameData load_last_game()
{

}

void exit_game()
{
    system("cls");
    printf("Thanks for playing!\n");
    Sleep(2000);
    exit(0);
}
