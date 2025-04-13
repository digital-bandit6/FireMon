#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "../config/common.h"
#include "../config/structs.h"
void check_file_existance(void);
void save_staged_devices(void);
void delete_device_from_file_by_id(int id);
void delete_device_from_file_by_name(const char *name);


#endif