#define STRUCT

struct User{
    char user_name[100];
    int total_score;
    int current_score;
};

struct Map{

};

struct GameData{
    struct User users[2];
    struct Map maps[2];
    int used_rocket[2];
    int winner;
    int finished;
};


void print_user_full(struct User user)
{
    printf("----------\n");

    printf("%s, total = %d, cur = %d\n", user.user_name, user.total_score, user.current_score);

    printf("----------\n");
}

void print_user(struct User user)
{
    printf("%s \t %d\n", user.user_name, user.total_score);
}
