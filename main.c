#include <stdio.h>
#include "menu.h"
#include "gameplay.h"

#ifndef STRUCT
#include "structs.h"
#endif // STRUCT

int main()
{
    struct GameData game;
    game = show_menu();
    /// if user list is empty, it will be bad! stop user from seeing the list or just put a return key!

    //show_stats(game);

    play_game(game);

    return 0;
}
