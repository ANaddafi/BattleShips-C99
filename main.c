#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "gameplay.h"

#ifndef STRUCT
#include "structs.h"
#endif // STRUCT

int main()
{
    struct GameData game;
    game = show_menu();

    play_game(game);

    return 0;
}
