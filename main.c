#include <stdio.h>
#include "menu.h"

#ifndef STRUCT
#include "structs.h"
#endif // STRUCT

int main()
{
    struct GameData game;
    game = show_menu();

    show_stats(game);



    return 0;
}
