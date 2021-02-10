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
    int lenght;
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
    int winner;
    int finished;
};

/////////////////////////////////
/// functions

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

    printf(" ");
    for(i = 1; i <= LEN; i++)
        printf(" %d", i);
    printf("\n");

    for(i = 0; i < LEN; i++){
        printf("%c ", i+'a');

        for(j = 0; j < LEN; j++)
            //printf("%c ", mp.view[i][j]);
            printf("%c ", mp.view[i][j] == 'W' ? '.' : '#');
        printf("\n");
    }
}

void view_map_leaked(struct Map mp)
{
    int i, j;

    printf(" ");
    for(i = 1; i <= LEN; i++)
        printf(" %d", i);
    printf("\n");

    for(i = 0; i < LEN; i++){
        printf("%c ", i+'a');

        for(j = 0; j < LEN; j++)
            printf("%c ", mp.leaked[i][j]);
            //printf("%c ", mp.leaked[i][j] == 'W' ? '.' : '#');
        printf("\n");
    }
}

struct point get_point(int col, char row)
{
    struct point ret_point;
    ret_point.row = row;
    ret_point.col = col;
    return ret_point;
};

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

    printf("Winner of the game is %s\n", gamedata.winner == -1 ? "N/A" : gamedata.users[gamedata.winner].user_name);
    printf("The game is %sfinished.\n", gamedata.finished == 1 ? " " : "not ");

    printf("------------------------------");
}
