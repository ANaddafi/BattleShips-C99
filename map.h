/// function for creating map

#define MAP
#ifndef STRUCT
#include "structs.h"
#endif // STRUCT

void log(char err[1000], int ext);

struct Map get_map_from_map_file(char map_name[100])
{
    struct Map ret_map;

    char tmp_name[100];
    strcpy(tmp_name, "./maps/");
    strcat(tmp_name, map_name);

    //printf("In map.h, trying to open <%s> : \n", tmp_name);

    FILE *fin = fopen(tmp_name, "rb");
    if(fin == NULL)
        log("ERROR in read in map.h\n", 1);


    fread(&ret_map, sizeof(struct Map), 1, fin);

    ret_map.ships_head = (struct Ship*)malloc(sizeof(struct Ship));
    ret_map.ships_head->next = NULL;

    make_ship(&ret_map);

    fclose(fin);

    return ret_map;
}


void view_map_from_map_file()
{

}
