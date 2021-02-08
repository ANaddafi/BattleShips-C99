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
