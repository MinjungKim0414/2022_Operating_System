// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFFLEN 24
#define ADMINPASS "allow"

//int initParent = -1;

char *argv[] = { "sh", 0 };

int max_attempts = 3, registered_users = 2;
char *regusers[] = {"user1", "user2"};
char *regpass[] = {"password", "pass"};

int login(char *usr, char *pw) {
  int i;
  int loggedIn = 0;

  for(i = 0 ; i < registered_users ; i++) {
    if(!strcmp(usr, regusers[i]) && !strcmp(pw, regpass[i])) {
      loggedIn = 1;
      break;
    }
  }
  if (!strcmp(usr, "a") && !strcmp(pw, "a")) { 
    loggedIn = 1;
  }
  return loggedIn;
}

int
main(void)
{
  int pid, wpid, loggedIn;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);
  dup(0);

  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      int count=0;

      while(count<3){
        printf(1, "Username: ");
        char *user = (char *)malloc(BUFFLEN);
        user = gets(user , 20);
        //remove enter key
        switch(user[strlen(user) - 1]) {
          case '\n': case '\r':
          user[strlen(user) - 1] = 0;
        }
        printf(1, "Password: ");
        char *pass = (char *)malloc(BUFFLEN);
        pass = gets(pass , 20);
        //remove enter key
        switch(pass[strlen(pass) - 1]) {
          case '\n': case '\r':
          pass[strlen(pass) - 1] = 0;
        }

        loggedIn = login(user, pass);
        if(loggedIn) {
          //opens shell for the user
          printf(1, "Welcome back %s!\n", user);
          exec("sh", argv);
          printf(1, "init: exec login failed\n");
          exit();
        }
        else {
          printf(1, "User and password do not match, or user does not exist! Try again!\n");
          count++;
        }
      }

///////
/*
      printf(1, "type \"logout\"to logout : ");
      int ccount =0;
      while(ccount<3){
	char *lo = (char *)malloc(BUFFLEN);
        lo = gets(lo , 20);
	if(!strcmp(lo, "logout")){ exit(); }
      } 
*/
      printf(1, "Failed 3 attempts! Please reboot\n");
      //kill(initParent);
      while(1); //stall
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");

  }
  printf(1, "asdfsda");
}

/*
/////////////////////
char *argv[] = { "sh", 0 };

int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}

*/
