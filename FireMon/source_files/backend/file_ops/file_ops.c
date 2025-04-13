#include "file_ops.h"
#include "../firewall_ops/firewall_ops.h"
#include "../menu/menu.h"


void check_file_existance(void){

    FILE *input_file = fopen(FIREWALL_DATABASE,"r");
    if(input_file == NULL){
        input_file = fopen(FIREWALL_DATABASE,"w");
        fclose(input_file);
        menu();
    }
    else{
        load_pid();
        menu();
    }
}

void save_staged_devices(void){
    FILE *input_file = fopen(FIREWALL_DATABASE, "a");
    if (input_file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    struct fw_ops *current = head;

    while (current != NULL) {
        fprintf(input_file, "ID: %d\nFirewall Name: %s\nFirewall Description: %s\n", current->id, current->name, current->description);
        current = current->next;
    }

    fclose(input_file);
    printf("Devices saved to %s\n", FIREWALL_DATABASE);
    free_memory();
}

void delete_device_from_file_by_id(int id){
    FILE *input_file = fopen(FIREWALL_DATABASE,"r");
    FILE *temp = fopen("temp","w");
    if(!input_file || !temp){
        printf("Error handling files\n");
        exit(EXIT_FAILURE);
    }
    int current_id;
    char buffer[4096];
    char name[1024];
    char description[1024];

    while(fgets(buffer,sizeof(buffer),input_file)){
        if (sscanf(buffer, "ID: %d", &current_id) == 1){
            fgets(name,sizeof(name),input_file);
            fgets(description,sizeof(description),input_file);

            if(current_id != id){
                fprintf(temp,"ID: %d\n",current_id);
                fputs(name,temp);
                fputs(description,temp);

            }
        }
    }
    fclose(input_file);
    fclose(temp);
    remove(FIREWALL_DATABASE);
    rename("temp",FIREWALL_DATABASE);
}

void delete_device_from_file_by_name(const char *name_to_delete) {
    FILE *input_file = fopen(FIREWALL_DATABASE, "r");
    FILE *temp = fopen("temp", "w");

    if (!input_file || !temp) {
        printf("Error handling files\n");
        exit(EXIT_FAILURE);
    }

    char id_line[1024], name_line[1024], description_line[1024];
    char current_name[1024];

    while (fgets(id_line, sizeof(id_line), input_file)) {
        if (fgets(name_line, sizeof(name_line), input_file) &&
            fgets(description_line, sizeof(description_line), input_file)) {

            // Extract the firewall name from the line (e.g., "Firewall Name: CiscoASA")
            if (sscanf(name_line, "Firewall Name: %[^\n]", current_name) == 1) {
                if (strcmp(current_name, name_to_delete) != 0) {
                    fputs(id_line, temp);
                    fputs(name_line, temp);
                    fputs(description_line, temp);
                }
            }
        }
    }

    fclose(input_file);
    fclose(temp);

    remove(FIREWALL_DATABASE);
    rename("temp", FIREWALL_DATABASE);
}

