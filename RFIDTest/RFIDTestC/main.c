
#include <stdio.h>
#include "ct_api.h"

int main(int argc, char *argv[])
{
    char ret;
    unsigned short ctn;
    unsigned short pn;
    unsigned short sad;
    unsigned short dad;
    
    // REQUEST ICC
    unsigned char command[] = { 0xFF, 0xCA, 0x00, 0x00, 0x00 };
//    unsigned char command[] = { 0xFF, 0x00, 0x48, 0x00, 0x00 };//%c
    
    unsigned short lenc = sizeof(command);
    
    unsigned char response[300];
    unsigned short lenr = sizeof(response);
    
    ctn = 1;
    pn = 1;
    
    // Initialize card terminal
    ret = CT_init(ctn, pn);
    if (ret != OK)
    {
        printf("Error: CT_init failed with error %d\n", ret);
        return 1;
    }
    
    sad = 2; // Source = Host
    dad = 0; // Destination = Card Terminal
    
    // Send command
    ret = CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);
    if (ret != OK)
        printf("Error: CT_data failed with error %d\n", ret);
    else
    {
        // Display response
        printf("Response: ");
        for (int i = 0; i < lenr; i++)
            printf("%02X", response[i]);
        printf("\n");
    }
    
    // Close card terminal
    ret = CT_close(ctn);
    if (ret != OK)
        printf("Error: CT_close failed with error %d\n", ret);
    
    return 0;
}