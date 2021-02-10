#define STRUCT
#define LEN 10

struct User{
    char user_name[100];
    int total_score;
    int current_score;
};

struct point
{
    int col;
    char row;
};

struct Ship
{
    /// if a ship explodes, must be removed from the list
    struct point top, back;
    int lenght, remain;
    int is_destroyed;
    struct Ship *next;
};

#define WATER 'W'
#define SHIP 'S'
#define EXP 'E'
#define EXPSHIP 'X'
#define EMPTY ' '

struct Map{
    struct Ship* ships_head;
    char view[LEN][LEN];
    char leaked[LEN][LEN];
};

struct GameData{
    struct User users[2];
    struct Map maps[2];
    int used_rocket[2];
    int turn;
    int winner, finished;
};

/////////////////////////////////
/// functions

struct Ship* find_ship(struct Map mp, int col, char row);

void print_user_full(struct User user)
{
    //printf("----------\n");

    printf("%s, total = %d, cur = %d\n", user.user_name, user.total_score, user.current_score);

    //printf("----------\n");
}


void print_user(struct User user)
{
    printf("%s \t %d\n", user.user_name, user.total_score);
}


void view_map(struct Map mp)
{
    int i, j;

    for(j = 0; j < (LEN+1); j++)  printf("        ");   printf("\n");

    printf("        ");
    for(i = 1; i <= LEN; i++)
        printf("   %-02d   ", i);
    printf("\n");

    for(j = 0; j < (LEN+1); j++)  printf("        ");   printf("\n");

    printf("        ");
    for(j = 0; j < 8*(LEN); j++)  printf("-");  printf("\n");


    for(i = 0; i < LEN; i++)
    {
        for(j = 0; j < (LEN+1); j++)  printf("       |");   printf("\n");

        printf("   %c   |", i+'A');

        for(j = 0; j < LEN; j++)
            printf("   %c   |", mp.view[i][j] == WATER ? WATER : SHIP);
        printf("\n");

        for(j = 0; j < (LEN+1); j++)  printf("       |");   printf("\n");

        printf("        ");
        for(j = 0; j < 8*(LEN); j++)  printf("-");    printf("\n");

    }
}


void view_map_leaked(struct Map mp)
{
    int i, j;

    for(j = 0; j < (LEN+1); j++)  printf("        ");   printf("\n");

    printf("        ");
    for(i = 1; i <= LEN; i++)
        printf("   %-02d   ", i);
    printf("\n");

    for(j = 0; j < (LEN+1); j++)  printf("        ");   printf("\n");

    printf("        ");
    for(j = 0; j < 8*(LEN); j++)  printf("-");  printf("\n");


    for(i = 0; i < LEN; i++)
    {
        for(j = 0; j < (LEN+1); j++)  printf("       |");   printf("\n");

        printf("   %c   |", i+'A');

        for(j = 0; j < LEN; j++)
            printf("   %c   |", mp.leaked[i][j]);
        printf("\n");

        for(j = 0; j < (LEN+1); j++)  printf("       |");   printf("\n");

        printf("        ");
        for(j = 0; j < 8*(LEN); j++)  printf("-");    printf("\n");

    }
}


struct point get_point(int col, char row)
{
    struct point ret_point;
    ret_point.row = row;
    ret_point.col = col;
    return ret_point;
}


int get_lenght(struct Ship ship)
{
    int dcol = ship.top.col - ship.back.col;
    int drow = ship.top.row - ship.back.row;
    if(dcol < 0)
        dcol = -dcol;
    if(drow < 0)
        drow = -drow;
    int res = (dcol + 1) * (drow + 1);
    return res;
}


void insert_ship(struct Ship *head, struct point p1, struct point p2)
{
    struct Ship* new_ship = (struct Ship*)malloc(sizeof(struct Ship));

    new_ship->top.col = p1.col;
    new_ship->top.row = p1.row;
    new_ship->back.col = p2.col;
    new_ship->back.row = p2.row;
    new_ship->is_destroyed = 0;
    new_ship->lenght = get_lenght(*new_ship);
    new_ship->remain = new_ship->lenght;

    new_ship->next = head->next;
    head->next = new_ship;
}


void make_ship(struct Map *mp)
{
    mp->ships_head = (struct Ship*)malloc(sizeof(struct Ship));
    mp->ships_head->next = NULL;

    int i, j;
    int checked[LEN][LEN];
    for(i = 0; i < LEN; i++)
        for(j = 0; j < LEN; j++)
            checked[i][j] = 0;

    for(i = 0; i < LEN; i++)
        for(j = 0; j < LEN; j++)
        {
            if(mp->view[i][j] == WATER || checked[i][j] != 0)
                continue;

            int explod = 0;
            struct point p1, p2;
            p1 = get_point(j, i+'a');

            if(i+1 < LEN && mp->view[i+1][j] == SHIP)
            {
                int t = i;
                while(t < LEN && mp->view[t][j] == SHIP)
                {
                    checked[t][j] = 1;
                    if(mp->leaked[t][j] == EXP)
                        explod ++;
                    t++;
                }

                p2 = get_point(j, t-1+'a');
            }
            else if(j+1 < LEN && mp->view[i][j+1] == SHIP)
            {
                int t = j;
                while(t < LEN && mp->view[i][t] == SHIP)
                {
                    checked[i][t] = 1;
                    if(mp->leaked[i][t] == EXP)
                        explod ++;
                    t++;
                }

                p2 = get_point(t-1, i+'a');
            }
            else
            {
                p2 = p1;
                checked[i][j] = 1;
            }

            insert_ship(mp->ships_head, p1, p2);
            mp->ships_head->next->remain -= explod;
        }
}

struct Ship* find_ship(struct Map mp, int col, char row)
{
    struct Ship* tmp_ship = mp.ships_head->next;

    col = col - 1;
    while(tmp_ship != NULL)
    {
        int C1 = tmp_ship->back.col,
            C2 = tmp_ship->top.col;
        char R1 = tmp_ship->back.row,
             R2 = tmp_ship->top.row;

        if(min(C1, C2) <= col && col <= max(C1, C2) &&
                min(R1, R2) <= row && row <= max(R1, R2))
            return tmp_ship;

        tmp_ship = tmp_ship->next;
    }
    return NULL;
}


int destroy(struct Map *mp)
{
    struct Ship* tmp_ship = mp->ships_head->next,
                    *lst_ship = mp->ships_head;

    while(tmp_ship != NULL)
    {
        if(tmp_ship->is_destroyed == 1)
        {
            lst_ship->next = tmp_ship->next;
            free(tmp_ship);
            return 1;
        }

        lst_ship = tmp_ship;
        tmp_ship = tmp_ship->next;
    }
    return 0;
}


void show_stats(struct GameData gamedata)
{
    printf("------------------------------\nGame Stats:\n\n");
    printf("User1 :");
    print_user_full(gamedata.users[0]);

    printf("User2 :");
    print_user_full(gamedata.users[1]);

    printf("Map of User1: \n");
    view_map(gamedata.maps[0]);

    printf("\nMap of User2: \n");
    view_map(gamedata.maps[1]);

    printf("User1 has used %d rockets, User2 has used %d tockers\n", gamedata.used_rocket[0], gamedata.used_rocket[1]);

    printf("It is user%d's turn\n", gamedata.turn+1);
    printf("Winner of the game is %s\n", gamedata.winner == -1 ? "N/A" : gamedata.users[gamedata.winner].user_name);
    printf("The game is %sfinished.\n", gamedata.finished == 1 ? " " : "not ");

    printf("------------------------------");
}
