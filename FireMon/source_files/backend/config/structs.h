#ifndef STRUCTS_H
#define STRUCTS_H

struct fw_ops{
    int id;
    char name[250];
    char description[250];

    struct fw_ops *next;
    
};
extern struct fw_ops *head;


#endif