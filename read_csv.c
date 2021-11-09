//
//  read_csv.c
//  Systems
//
//  Created by Theodore Fahey on 11/4/21.
//
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

struct pop_entry {
  int year;
  int population;
  char boro[15];
};
void print_struct(struct pop_entry * h){
    int counter = 0;
    while(h->population != 0){
        counter++;
        printf("EntryId: %d, Boro: %s, Year: %d, Population: %d\n",counter, h->boro,h->year,h->population);
        h++;
    }
    counter = 0;
}
void read_csv(){
    int fd = open("./nyc_pop.csv", O_RDONLY, 0);
    struct stat size;
    stat("./nyc_pop.csv", &size);
    long total = size.st_size;
    char temp[total+1];
    char * hold = malloc(total+1);
    read(fd, temp,total);
    hold = strtok(temp,",");
    int i = 0;
    struct pop_entry * list= malloc(total);
    struct pop_entry * holder = list;
    int yea = 0;
    char * man = "Manhattan";
    char * bk = "Brooklyn";
    char * que = "Queens";
    char * bx =  "Bronx";
    char * fake = "Staten Island";
    int c = 0;
    printf("reading nyc_pop.csv\n");
    for (c = 0; c < 4; c++){
        hold = strtok(NULL,",");
    }
    hold = strtok(NULL, "\n");
    hold = strtok(NULL,",");
   // hold = strtok(NULL,",");
    while(hold){
        if (i == 0){

            yea = atoi(hold);
            i++;
            hold = strtok(NULL, ",");
            }
        if (i == 1){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, man, 10);
            i++;
            hold = strtok(NULL, ",");
            list++;
            }
        if (i == 2){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, bk, 9);
            i++;
            hold = strtok(NULL, ",");
            list++;
        }
        if (i == 3){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, que, 7);
            i++;
            hold = strtok(NULL, ",");
            list++;
        }
        if (i == 4){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, bx, 6);
            i++;
            hold = strtok(NULL, "\n");
            list++;
        }
        if (i == 5){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, fake, 15);
            
            i=0;
            hold = strtok(NULL, ",");
            list++;
            
        }
    }
    list = NULL;
    list = holder;
    int wr = open("text.data", O_WRONLY | O_CREAT,0777);
    int counter = 0;
    while (list-> population != 0){
        //printf("boro: %s, year %d, pop: %d", list->boro, list-> year, list->population);
        write(wr,list, sizeof(struct pop_entry));
        counter++;
        list++;
    }
    printf("writing %lu bytes to text.data\n",(sizeof(struct pop_entry) * counter));
    

}
struct pop_entry * read_data(){
    int fd = open("./nyc_pop.csv", O_RDONLY, 0);
    struct stat size;
    stat("./nyc_pop.csv", &size);
    long total = size.st_size;
    char temp[total+1];
    char * hold = malloc(total+1);
    read(fd, temp,total);
    hold = strtok(temp,",");
   // printf("%s\n", temp);
    int i = 0;
    struct pop_entry * list= malloc(total);
    struct pop_entry * holder = list;
    //printf("%p\n",list);
    //printf("%p\n",holder);
    int yea = 0;
    char * man = "Manhattan";
    char * bk = "Brooklyn";
    char * que = "Queens";
    char * bx =  "Bronx";
    char * fake = "Staten Island";
    int c = 0;
    for (c = 0; c < 4; c++){
        hold = strtok(NULL,",");
    }
    hold = strtok(NULL, "\n");
    hold = strtok(NULL,",");
   // hold = strtok(NULL,",");
    while(hold){
        if (i == 0){

            yea = atoi(hold);
            i++;
            hold = strtok(NULL, ",");
            }
        if (i == 1){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, man, 10);
            i++;
            hold = strtok(NULL, ",");
            list++;
            }
        if (i == 2){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, bk, 9);
            i++;
            hold = strtok(NULL, ",");
            list++;
        }
        if (i == 3){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, que, 7);
            i++;
            hold = strtok(NULL, ",");
            list++;
        }
        if (i == 4){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, bx, 6);
            i++;
            hold = strtok(NULL, "\n");
            list++;
        }
        if (i == 5){
            list -> year = yea;
            list->population = atoi(hold);
            strncpy(list->boro, fake, 15);
            
            i=0;
            hold = strtok(NULL, ",");
            list++;
            
        }
    }
    list = NULL;
    list = holder;
    int num = 0;
    while (list-> population != 0){
        num++;
        //printf("entry no: %d boro: %s, year %d, pop: %d\n", num, list->boro, list-> year, list->population);
        list++;
    }
    //print_struct(holder);
    return holder;
}

struct pop_entry * add_data(struct pop_entry * list, char * borough, int yea, int pop){
    struct pop_entry * holder = list;
    while (list->population != 0){
        list++;
    }
    struct pop_entry * new = list;
    strncpy((new->boro),borough,15);
    new -> year = yea;
    new -> population = pop;
    return holder;
    
}
struct pop_entry * update_data(int entryno, char * new_boro, int new_year, int new_pop, struct pop_entry * list){
    struct pop_entry * holder = list;
    int i = 0;
    for (i = 0; i < entryno; i++){
        list++;
    }
    strncpy(list->boro, new_boro, 15);
    list->year = new_year;
    list->population = new_pop;
    //print_struct(holder);
    return holder;
}
int main(){
    char file[100];
    struct pop_entry * list;
    printf("Please List a Command:\n" );
    read(STDIN_FILENO,file,100);
    file[strlen(file)-1] = '\0';
    if (strcmp(file, "-read_csv")== 0){
        read_csv();
    }
    else if (strcmp(file, "-read_data") == 0){
        list = read_data();
        print_struct(list);
    }
    else if (strcmp(file, "-add_data") == 0){
        int year;
        char * boro;
        int pop;
        list = read_data();
        char arg[1000];
        printf("Enter year boro pop: \n");
        read(STDIN_FILENO,arg,1000);
        arg[strlen(arg)-1] = '\0';
        if ((strstr(arg, "staten") != NULL) || (strstr(arg, "Staten")) != NULL){
            year = atoi(strtok(arg," "));
            boro = "Staten Island";
            strtok(NULL, " ");
            strtok(NULL, " ");
            pop = atoi(strtok(NULL, "\0"));
        }
        else{
            year = atoi(strtok(arg," "));
            boro = strtok(NULL," ");
            pop = atoi(strtok(NULL, "\0"));
        }

        list = add_data(list,boro,year,pop);
        print_struct(list);
        
    }
    else if(strcmp(file, "-update_data") == 0){
        char entryno[10];
        char arg[1000];
        int id;
        int year;
        char * boro;
        int pop;
        list = read_data();
        printf("Entry to update: \n");
        read(STDIN_FILENO,entryno,10);
        id = atoi(entryno);
        printf("Enter year boro pop: \n");
        read(STDIN_FILENO,arg,1000);
        arg[strlen(arg)-1] = '\0';
        if ((strstr(arg, "staten") != NULL) || (strstr(arg, "Staten")) != NULL){
            year = atoi(strtok(arg," "));
            boro = "Staten Island";
            strtok(NULL, " ");
            strtok(NULL, " ");
            pop = atoi(strtok(NULL, "\0"));
        }
        else{
            year = atoi(strtok(arg," "));
            boro = strtok(NULL," ");
            pop = atoi(strtok(NULL, "\0"));
        }
        list = update_data(id, boro, year, pop, list);
        print_struct(list);
        
        
    }
//    struct pop_entry * list = read_data();
//    list = add_data(list, "Manhattan",2021,20000000);
//    list = update_data(10, "New Jersey", 2970, 49998, list);
//    print_struct(list);
//    //read_data();
//    return 0;
    
}
