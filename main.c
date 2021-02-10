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

    show_stats(game);

    play_game(game);

    return 0;
}
