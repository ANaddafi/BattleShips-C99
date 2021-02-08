struct User{
    char user_name[100];
    int total_score;
    int current_score;
};


struct Map{

};

struct GameData{
    struct User user[2];
    struct Map map[2];
};
