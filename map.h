/// function for creating map

#define MAP
#ifndef STRUCT
#include "structs.h"
#endif // STRUCT

void log(char err[1000], int ext);

void insert(struct Ship *head, struct Ship ship)
{
    struct Ship* new_ship = (struct Ship*)malloc(sizeof(struct Ship));

    new_ship->top.col   = ship.top.col;
    new_ship->top.row   = ship.top.row;
    new_ship->back.col  = ship.back.col;
    new_ship->back.row  = ship.back.row;
    new_ship->lenght    = ship.lenght;
    new_ship->is_destroyed  = ship.is_destroyed;

    new_ship->next = head->next;
    head->next = new_ship;
}

struct Map get_map_from_map_file(char map_name[100])
{
    struct Map ret_map;

    char tmp_name[100];
    strcpy(tmp_name, "./maps/");
    strcat(tmp_name, map_name);

    //printf("In map.h, trying to open <%s> : \n", tmp_name);

    FILE *fin = fopen(tmp_name, "rb");
    if(fin == NULL)
        log("ERROR in map.h\n", 1);


    fread(&ret_map, sizeof(struct Map), 1, fin);

    ret_map.ships_head = (struct Ship*)malloc(sizeof(struct Ship));
    ret_map.ships_head->next = NULL;

    struct Ship new_ship;
    while(fread(&new_ship, sizeof(struct Ship), 1, fin) >= 1)
        insert(ret_map.ships_head, new_ship);

    fclose(fin);

    return ret_map;
}


void view_map_from_map_file()
{

}
