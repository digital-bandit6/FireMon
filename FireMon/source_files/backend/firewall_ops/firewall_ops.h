#ifndef FIREWALL_OPS_H
#define FIREWALL_OPS_H

#include "../config/common.h"
#include "../config/structs.h"


void staged_devices(void);

struct fw_ops *create_new_device(const char *name,const char *description);
void add_new_device(struct fw_ops *device);

int delete_device_by_id(int id);
void delete_device_by_name(const char *name);

void find_by_id(int id);

void find_by_name(const char *name);

void show_staged_devices(void);
void show_all_devices(void);

void load_pid(void);

void free_memory(void);
#endif