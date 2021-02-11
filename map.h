/// function for creating map

#define MAP
#ifndef STRUCT
#include "structs.h"
#endif // STRUCT

void log(char err[1000], int ext);


int minn(int a, int b)
{
    return a > b ? b : a;
}

int maxx(int a, int b)
{
    return a > b ? a : b;
}

struct Map get_map_from_map_file(char map_name[100])
{
    struct Map ret_map;

    char tmp_name[100];
    strcpy(tmp_name, "./maps/");
    strcat(tmp_name, map_name);

    FILE *fin = fopen(tmp_name, "rb");
    if(fin == NULL)
        log("ERROR in read in map.h\n", 1);


    fread(&ret_map, sizeof(struct Map), 1, fin);

    //ret_map.ships_head = (struct Ship*)malloc(sizeof(struct Ship));
    //ret_map.ships_head->next = NULL;

    make_ship(&ret_map);

    fclose(fin);

    return ret_map;
}

void do_save(struct Map mp)
{
    char name[100];
    printf("       Enter name of your map: ");
    scanf("%s", name);

    /*char tmp_name[100];
    strcpy(tmp_name, "./maps/");
    strcat(tmp_name, name);
    strcat(tmp_name, ".bin");*/

    save_map(mp, name);

    /*FILE *fout = fopen(tmp_name, "wb");
    if(fout == NULL){
        printf("Couldn't Save!\n");
        return;
    }

    fwrite(&mp, sizeof(struct Map), 1, fout);

    fclose(fout);*/
}

struct point ask_point()
{
    int col;
    char row;

    printf("       >> ");
    fflush(stdin);
    scanf("%c %d", &row, &col);

    if('A' <= row && row <= 'Z')
        row = row -'A' + 'a';
    if(row > 'j' || row < 'a' || col > LEN || col < 1)
    {
        printf("       Invalid!\n");
        return ask_point();
    }
    return get_point(col-1, row);
}

struct Map map_maker()
{
    struct Map res_map;
    int i, j;
    for(i = 0; i < LEN; i++)
        for(j = 0; j < LEN; j++)
            res_map.leaked[i][j] = EMPTY,
            res_map.view[i][j] = WATER;


    int cnt[LEN] = {0};
    cnt[5] = 1;
    cnt[3] = 2;
    cnt[2] = 3;
    cnt[1] = 4;

    int k;
    for(k = LEN-1; k > 0; k--)
        while(cnt[k])
        {
            CLS;
            view_map(res_map);
            printf("       Enter Coordinates for the ship (size = %d)", k);
            printf("\n       row col\n");

            struct point pt1 = ask_point();
            struct point pt2 = ask_point();

            if(get_lenght_point(pt1, pt2) != k)
            {
                printf("       Size Should Be %d! Try Again!\n", k);
                Sleep(2000);
                continue;
            }

            for(i = minn(pt1.col, pt2.col); i <= maxx(pt1.col, pt2.col); i++)
                for(j = minn(pt1.row, pt2.row)-'a'; j <= maxx(pt1.row, pt2.row)-'a'; j++)
                    res_map.view[j][i] = SHIP;
            cnt[k]--;
        }


    CLS;
    view_map(res_map);
    printf("       Done!\n");
    Sleep(2000);

    char user_input = 'A';
    while(user_input!='Y' && user_input!='N')
    {
        printf("       Do you want to save it? (Y/N) ");

        fflush(stdin);
        scanf("%c", &user_input);
        if('a' <= user_input && user_input <= 'z')
            user_input = user_input - 'a' + 'A';
        if(user_input != 'Y' && user_input != 'N')
        {
            printf("       !\n");
            continue;
        }
        if(user_input == 'Y')
            do_save(res_map);
        else
            break;
    }

    return res_map;
}
