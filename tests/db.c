#include <stdio.h>
#include <unistd.h>
#include "libs/database/database.h"

int main()
{

    if(!openConnection()){
        printf("FATAL ERROR: Could not open database!\n");
        return 0;
    }

    
    closeConnection();









    
    return 0;
}