#include "types.h"
#include "defs.h"

struct info {
	char username;
	char userpw;
};

int
addUser(char *username, char *password)
{
/*
	int fd;
        struct info t;
                
        fd = open("userInfo", O_CREATE | O_RDWR);
        if(fd >= 0){
                printf(1, "create file succeed. \n");
        } else {
                printf(1, "create file failed. \n");
        }
        
        int size = sizeof(t);
        if(write(fd, &t, size) != size){
                printf(1, "errorrrrr \n");
                exit();
        }
        printf(1, "write successssss \n");
        close(fd);
*/
        cprintf("user name : %s, pw : %s \n", username, password); 
        return 0;
}

/*
int 
deleteUser(char *username){
        printf(1, "delete \n");
        return 0;
}
*/

int
sys_addUser(void)
{
        char *username, *password;
        //cprintf("sys_addUser \n");

        if(argstr(0, &username)<0)
                return -1;
        if(argstr(0, &password)<0)
                return -1;

        return addUser(username, password);
}

/*
int
sys_deleteUser(void)
{
        char *username;

        if(argstr(0, &username)<0)
                return -1;

        return deleteUser(username);
}
*/
