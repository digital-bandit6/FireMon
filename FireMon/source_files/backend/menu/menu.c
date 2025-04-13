#include "menu.h"
#include "../firewall_ops/firewall_ops.h"
#include "../file_ops/file_ops.h"

void prompt(void){
    printf("~> ");
}
void menu(void){

    int selection,id;
    char name[250];
    char description[250];

    do{
        printf("Enter Selection\n1.view all devices includeing staged\n2.view staged devices\n3.find device by id\n4.find device by name\n5.add new device\n6.delete device by id\n7.delete device by name\n8.save staged devices\n9.delete device by id from file\n10. Delete device from file by name\n11.exit\n");
        prompt();

        scanf("%d", &selection);
        getchar();

        switch(selection){
            case 1:
                show_all_devices();
                break;
            case 2:
                show_staged_devices();
                break;
            case 3:
                printf("Enter ID of device to find: ");
                scanf("%d",&id);
                getchar();
                
                find_by_id(id);
                break;
            case 4:

                printf("Enter Name of device to find: ");
                fgets(name,sizeof(name),stdin);
                name[strcspn(name,"\n")] = '\0';

                find_by_name(name);
                break;

            case 5:
                printf("Enter Name of New Device: ");
                fgets(name,sizeof(name),stdin);
                name[strcspn(name,"\n")] = '\0';

                printf("Enter Description Of Firewall: ");
                fgets(description,sizeof(description),stdin);
                description[strcspn(description,"\n")] ='\0';

                struct fw_ops *new_fw = create_new_device(name,description);
                add_new_device(new_fw);
                break;
            case 6:
                printf("Enter Device ID to delete: ");
                scanf("%d",&id);
                getchar();

                delete_device_by_id(id);
                break;
            
            case 7:
                printf("Enter Name of device to Delete: ");
                fgets(name,sizeof(name),stdin);
                name[strcspn(name,"\n")] ='\0';

                delete_device_by_name(name);
                break;
            case 8:
                save_staged_devices();
                break;
            case 9:
                printf("Enter ID of Device to Delete: ");
                scanf("%d", &id);
                getchar();
                
                delete_device_from_file_by_id(id);
                break;
            case 10:
                printf("Enter Device Name to Delete: ");
                fgets(name,sizeof(name),stdin);
                name[strcspn(name,"\n")] = '\0';

                delete_device_from_file_by_name(name);
                break;
            case 11:
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
            default:
                printf("invalid entry\n");
                break;
        }
    }while(selection != 11);

    
}