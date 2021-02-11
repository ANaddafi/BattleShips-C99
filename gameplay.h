/// functions about running the game


#include <time.h> //time(0)
#ifndef STRUCT
#include "structs.h"
#endif // STRUCT

#ifndef DATA
#include "data.h"
#endif // DATA

void exit_with_save(struct GameData *game);
void save_game(struct GameData *game);
void play_turn(struct GameData* game, int mod);

//int min(int a, int b){return a > b ? b : a;}
//int max(int a, int b){return a > b ? a : b;}

void show_water(struct Map *mp, struct Ship* ship)
{
    /// showing water around the ship
    /// And showing the ship is destroyed
    int C1 = ship->back.col,
        C2 = ship->top.col;
    int R1 = ship->back.row - 'a',
         R2 = ship->top.row - 'a';

    int i, j;
    for(i = min(R1, R2); i <= max(R1, R2); i++)
        for(j = min(C1, C2); j <= max(C1, C2); j++)
        {
            int tc, tr;
            for(tc = -1; tc <= 1; tc++)
                for(tr = -1; tr <= 1; tr++)
                {
                    if(tc == 0 && tr == 0)
                        continue;
                    int new_C = j + tc;
                    int new_R = i + tr;
                    if(new_C >= 0 && new_C < LEN && new_R >= 0 && new_R < LEN)
                        mp->leaked[new_R][new_C] = WATER;
                }
        }

    for(i = min(R1, R2); i <= max(R1, R2); i++)
        for(j = min(C1, C2); j <= max(C1, C2); j++)
            mp->leaked[i][j] = EXPSHIP;
}

void prefix(int turn, struct User cur_user)
{
    system("cls");
    if(strcmp(cur_user.user_name, BOT_NAME)==0)
    {
        printf("Player%d: %s\t", turn+1, "Computer");
        printf("Game Score: %d\n", cur_user.current_score);
    }
    else
    {
        printf("Player%d: %s\t", turn+1, cur_user.user_name);
        printf("Game Score: %d\tTotal Score: %d\n", cur_user.current_score, cur_user.total_score);
    }
}

void attack(int col, char row, int turn, struct GameData *game)
{
    char target = game->maps[1-turn].view[row-'a'][col-1];

    if(game->maps[1-turn].leaked[row-'a'][col-1] != EMPTY)
    {
        log("       You cannot shoot this cell! Select another one!\n", 0);
        play_turn(game, 0);
        return;
    }
    else if(target == WATER)
    {
        game->maps[1-turn].leaked[row-'a'][col-1] = WATER;
        return;
    }
    else if(target == SHIP)
    {
        game->maps[1-turn].leaked[row-'a'][col-1] = EXP;

        struct Ship *target_ship = find_ship(game->maps[1-turn], col, row);
        if(target_ship == NULL)
            log("ERROR IN FINDING SHIP!\n", 1);

        target_ship->remain --;

        if(target_ship->remain == 0) // fully exploded
        {
            log("       Hooray! You destroyed a ship!", 0);

            show_water(&(game->maps[1-turn]), target_ship);

            target_ship->is_destroyed = 1;
            if(destroy( &( game->maps[1-turn] ) ) == 0)
                log("ERROR IN REMOVING SHIP!'n", 1);

            game->users[turn].current_score += 25/target_ship->lenght;
        }

        game->users[turn].current_score ++;

        if(game->maps[1-turn].ships_head->next == NULL) // use is_lost, and check if all of ships are destroyed!
        {
            /// game over! YOU WON!

            game->finished = 1;
            game->winner = turn;
        }
        else{
            prefix(turn, game->users[turn]);
            view_map_leaked(game->maps[1-turn]);
            log("\n       YAY! You got one more move!\n", 0);
            play_turn(game, 1);
        }

        return;
    }
    else
    {
        log("Nothing to do!!", 0);
    }
}

void play_bot_turn(int turn, struct GameData* game, int mod) // mod=1 -> bonus move!
{
    printf("\n       << COMPUTER IS MAKING A MOVE! >>\n");
    Sleep(1000);
    CLS;

    int i, j,  empty_cells = 0;
    for(i = 0; i < LEN; i++)
        for(j = 0; j < LEN; j++)
            if(game->maps[1-turn].leaked[i][j] == EMPTY)
                empty_cells ++;

    int bot_move = rand()%empty_cells +1;

    int bot_col = 0;
    char bot_row = 'a';

    for(i = 0; i < LEN&& bot_move > 0; i++)
        for(j = 0; j < LEN && bot_move > 0; j++)
            if(game->maps[1-turn].leaked[i][j] == EMPTY)
            {
                bot_move --;
                if(bot_move == 0)
                    bot_col = j+1, bot_row = i+'a';
            }

    /*static int  last_col = -1;
    static char last_row = 'a'-1;
    printf("~~ bot_move  = %c %d ~~", bot_move);
    printf("~~ last_move = %c %d ~~\n", last_move);
    Sleep(1500);
    last_move = bot_move;*/

    CLS;
    prefix(turn, game->users[turn]);
    view_map_leaked(game->maps[1-turn]);
    printf("\n       << Computer shot %c %d! >>\n", bot_row -'a'+'A', bot_col);
    Sleep(1500);


    attack(bot_col, bot_row, turn, game);

    if(mod == 1)
            return;

    prefix(turn, game->users[turn]);
    view_map_leaked(game->maps[1-turn]);
    //printf("\n<< Computer shot %c %d! >>\n", bot_row -'a'+'A', bot_col);

    Sleep(2500);

}

void play_turn(struct GameData* game, int mod) // mod=1 -> bonus move!
{
    int turn = game->turn;
    struct User cur_user = game->users[turn];

    prefix(turn, cur_user);
    view_map_leaked(game->maps[1-turn]);

    if(strcmp(cur_user.user_name, BOT_NAME) == 0)
    {
        play_bot_turn(turn, game, mod);
        return;
    }

    printf("\n       Enter Your Move: \t");
    printf("(S for Save, X for Exit, Coordinates for shoot (row col))\n       >> ");

    char row;
    int col;

    fflush(stdin);
    scanf("%c", &row);

    if('A' <= row && row <= 'Z')
        row = row - 'A' + 'a';

    if(row == 's'){
        save_game(game);
        play_turn(game, 0);
    }
    else if(row == 'x')
        exit_with_save(game);
    else if(row < 'a' || row > 'j')
    {
        printf("       <%c> is Invalid input!", row);
        Sleep(1500);
        fflush(stdin);

        play_turn(game, 0);
    }
    else
    {
        scanf("%d", &col);
        attack(col, row, turn, game);

        if(mod == 1)
            return;

        prefix(turn, cur_user);
        view_map_leaked(game->maps[1-turn]);
        Sleep(1500);
    }

}

void play_game(struct GameData game)
{
    if(strcmp(game.users[1].user_name, BOT_NAME) == 0)
        srand(time(0));

    while(! game.finished)
    {
        play_turn(&game, 0);
        game.turn = 1-game.turn;
    }


    if(game.finished)
    {
        CLS;
        printf("--%s WON--\n", game.users[game.winner].user_name);
        Sleep(3000);

        struct User *user_list = get_user_list();
        int cnt = user_list[0].total_score, i;
        for(i = 1; i < cnt; i++){
            if(strcmp(user_list[i].user_name, game.users[game.winner].user_name) == 0) // is winner suer
               user_list[i].total_score += game.users[game.winner].current_score;

            else if(strcmp(user_list[i].user_name, game.users[1-game.winner].user_name) == 0) // is loser user
                user_list[i].total_score += game.users[1-game.winner].current_score / 2;
        }

        replace_user_list(user_list);

        printf("\nPress any key to exit...");
        getch();
        exit_game();
    }
    else
    {
        system("cls");
        log("Error!\n", 1);
    }
}

void save_game(struct GameData *game)
{
    char save_name[100];
    printf("       Enter a name for you save file: ");
    scanf("%s", save_name);

    save_game_file(game, save_name);
    log("\n       --SAVED--\n", 0);
}

void save_last_game(struct GameData *game)
{
    save_game_file(game, LASTGAME);
}

void exit_with_save(struct GameData *game)
{
    save_last_game(game);
    exit_game();
}
