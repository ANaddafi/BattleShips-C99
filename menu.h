/// functions related to menu

void show_menu()
{
    /// displays the initial menu of the game
    /// returns a game status

    printf("WELCOME TO THE GAME OF BATTLESHIPS!\n\n");
    printf("Please select what you want to do:\n\n");

    printf("1) Play with a friend\n");
    printf("2) Play with computer\n");
    printf("3) Load game\n");
    printf("4) Load last game\n");
    printf("5) Settings\n");
    printf("6) ScoreBoard\n");
    printf("7) Exit\n\n>> ");

    int user_input = 0;
    scanf("%d", &user_input);
}
