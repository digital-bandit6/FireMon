#include "firewall_ops.h"
struct fw_ops *head = NULL;
int pid = 1;

void load_pid(void) {
    FILE *input_file = fopen(FIREWALL_DATABASE, "r");
    if (input_file == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    int max_id = 0;
    char line[256];

    while (fgets(line, sizeof(line), input_file) != NULL) {
        int id;
        if (sscanf(line, "ID: %d", &id) == 1) {
            if (id > max_id) {
                max_id = id;
            }
        }
    }

    fclose(input_file);

    pid = max_id + 1;
}


void free_memory(void){
    struct fw_ops *temp = head;
    while(temp != NULL){
        struct fw_ops *next = temp -> next;
        free(temp);
        temp = next;
    }
    head = NULL;
}

void staged_devices(void){
    printf("Staged (Unsaved) Firewalls:\n");
    show_staged_devices();
}


struct fw_ops *create_new_device(const char *name,const char *description){
    struct fw_ops *device = (struct fw_ops *)malloc(sizeof(struct fw_ops));
    if(device == NULL){
        printf("Error Allocating memory\n");
        return 0;
    }

    device -> id = pid++;
    strncpy(device -> name,name,sizeof(device -> name) - 1);
    strncpy(device -> description,description,sizeof(device -> description) - 1);
    device -> name[sizeof(device -> name) - 1] = '\0';
    device -> description[sizeof(device -> description) - 1] = '\0';

    device -> next = NULL;

    return device;
}

void add_new_device(struct fw_ops *device){
    if(device == NULL){
        return;
    }
    if(head == NULL){
        head = device;
    }
    else{
        struct fw_ops *temp = head;
        while(temp -> next != NULL){
            temp = temp -> next;
        }
    temp -> next = device;
    }
    
    printf("Firewall Creation Successfull\n");
    
}
int delete_device_by_id(int id){
    if(head == NULL){
        printf("No Firewalls to Delete\n");
        return 0;
    }
    struct fw_ops *temp = head;
    struct fw_ops *prev = NULL;

    if(head -> id == id){
        head = head -> next;
        free(temp);
        return 1;
    }
    while(temp != NULL && temp -> id != id){
        prev = temp;
        temp = temp -> next;
    }
    if(temp == NULL){
        printf("No Firewalls found with matching ID\n");
        return 1;
    }
    prev -> next = temp -> next;
    free(temp);
    printf("Firewall with ID %d deleted\n",id);

}

void delete_device_by_name(const char *name){
    if(head == NULL){
        printf("No Firewalls to Delete\n");
        return;
    }
    struct fw_ops *temp = head;
    struct fw_ops *prev = NULL;

    if(strcmp(head -> name,name) == 0){
        head = head -> next;
        free(temp);
        return;
    }
    while(temp != NULL && strcmp(temp -> name,name) != 0){
        prev = temp;
        temp = temp -> next;
    }
    if(temp == NULL){
        printf("No Firewalls found with matching ID\n");
        return;
    }
    prev -> next = temp -> next;
    free(temp);
    printf("Firewall with Name %s deleted\n",name);
 
}


void show_staged_devices(void){
    if(head == NULL){
        printf("No Firewalls In Database\n");
        return;
    }
    else{
        struct fw_ops *device = head;
        while(device != NULL){
            printf("ID: %d\nFirewall Name: %s\nFirewall Description: %s\n",device -> id, device -> name, device -> description);
            device = device -> next;
        }
    }
}

void show_all_devices(void){
    FILE *input_file = fopen(FIREWALL_DATABASE,"r");
    if (input_file == NULL){
        printf("No Firewalls in  Database\n");
        return;
    }
    else{
        printf("Saved Devices in DB\n-----------\n");
        char buffer[4096];
        while(fgets(buffer,sizeof(buffer),input_file) != NULL){
            printf("%s", buffer);
        }
        printf("\n-----------\nStaged Devices\n");
        show_staged_devices();
    }
}

void find_by_id(int id){
    if(head == NULL){
        printf("No Firewalls in Database\n");
        return;
    }
    else{
        struct fw_ops *temp = head;
        while(temp != NULL){
            if(id == temp -> id){
                printf("ID: %d\nFirewall Name: %s\nFirewall Description: %s\n",temp -> id, temp -> name, temp -> description);
                return;
            }
        temp = temp -> next;
        }
    }
    printf("No Firewalls found with ID %d\n",id);
}

void find_by_name(const char *name){
    if(head == NULL){
        printf("No Firewalls in Database\n");
        return;
    }
    else{
        struct fw_ops *temp = head;
        while(temp != NULL){
            if(strcmp(name,temp -> name) == 0){
                printf("ID: %d\nFirewall Name: %s\nFirewall Description: %s\n",temp -> id, temp -> name, temp -> description);
                return;
            }
            temp = temp -> next;
        }
    }
    
}
