#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

 struct problem{

    char soorat_moshkel[201];

    char tasmim_1[201];
    int mardom_tasmim_1;
    int darbar_tasmim_1;
    int khazane_tasmim_1;

    char tasmim_2[201] ;

    int mardom_tasmim_2;
    int darbar_tasmim_2;
    int khazane_tasmim_2;

    int emkan ;
    int number_node;
    struct problem* next;

};

 //-----------------------------------
 //***********************************

int del(struct problem* e , struct problem** list){
    struct problem *temp;
    if( e == *list){
        temp = *list;
        temp = temp->next;
        free(*list);
        *list = temp;
    }
    else{
        struct problem* current = *list;

        for( ; current->next != e ;current  = current->next ){

        }

        temp =  current->next->next;

        free(current->next);

        current->next = temp;
    }
    return 0;
}

//----------------------------------
//********************************

struct problem* creat_node(char *name_file  , int number_node){

    struct problem* p;

    p = (struct problem*)malloc(sizeof(struct problem));

    FILE * moshkel;

    moshkel = fopen(name_file , "r");


    if(moshkel == NULL){

        printf("Cannot open file\n");
        return -1;
    }

    char  buff_1[250];
    char  buff_2[250];
    char  buff_3[250];
    char  buff_4[250];

    fgets(buff_1 , 250 , moshkel);
    strcpy(p->soorat_moshkel , buff_1);

    fgets(buff_2 , 250 , moshkel);
    strcpy(p->tasmim_1 , buff_2);

    fscanf(moshkel , "%d" , &(p->mardom_tasmim_1) );

    fscanf(moshkel , "%d" , &(p->darbar_tasmim_1) );

    fscanf(moshkel , "%d" , &(p->khazane_tasmim_1) );


    fgets(buff_4 , 250 , moshkel);


    fgets(buff_3 , 250 ,  moshkel);
    strcpy(p->tasmim_2 , buff_3);

    fscanf(moshkel , "%d" , &(p->mardom_tasmim_2) );


    fscanf(moshkel , "%d" , &(p->darbar_tasmim_2) );

    fscanf(moshkel , "%d" , &(p->khazane_tasmim_2) );

    p->emkan = 3;
    p->number_node = number_node;

    p->next = NULL;
    fclose(moshkel);

    return p;
}

//-------------------------------------
//***************************************


struct problem* creat_list(){

    struct problem* list;
    struct problem* current;


    list = creat_node("C:\\Users\\01RAYANEH\\Desktop\\FoP_FP\\c1.txt" , 1);

    current = list;

    for(int i = 2 ; i < 8 ; i++ ){
        char s[200] = "C:\\Users\\01RAYANEH\\Desktop\\FoP_FP\\c.txt";
        sprintf(s , "C:\\Users\\01RAYANEH\\Desktop\\FoP_FP\\c%d.txt" , i);
        current->next = creat_node(s , i);

        current = current->next;

    }

    current->next = NULL;
    return list;
}

//--------------------------
//****************************



int game(struct problem* list , int* mardom , int *darbar , int *khazane , int * number_of_node){
    int selected_node , tasmim;

    char vaziyat_exit;



    srand(time(NULL));
    struct problem* current;
    current = list;

    printf("People:%d  Court:%d   Treasury:%d\n\n\n" , *mardom , *darbar , *khazane);
    printf("\n\n");

    for(int i = 0 ; i< 21 ; i++){


        if((*darbar <= 0) || (*khazane <= 0) || (*mardom <= 0) || (((*darbar + *mardom + *khazane)  /  3 ) < 10 )){

            printf("LOSE!! :(\n");
            printf("Do you want to save this game ?(y/n) \n");

            scanf(" %c" , &vaziyat_exit);
            if(vaziyat_exit == 'y'){
                struct problem * new_game = creat_list();
                save( new_game, 50 , 50 , 50 , number_of_node);



            }
            else if(vaziyat_exit == 'n'){

            }
            return 1;
        }

        selected_node = rand();

        selected_node = (selected_node % *number_of_node) + 1;

        current = list;
        for(int u = 0 ; u < selected_node - 1 ; u++){
            current = current->next;
        }

        printf("%s\n" , current->soorat_moshkel);
        printf("1) %s\n" , current->tasmim_1);
        printf("2) %s\n" , current->tasmim_2);

        scanf("%d" , &tasmim);

        if(tasmim == 1){
            *mardom += current->mardom_tasmim_1;
            *darbar += current->darbar_tasmim_1;
            *khazane += current->khazane_tasmim_1;
        }

        else if(tasmim == 2){
            *mardom += current->mardom_tasmim_2;
            *darbar += current->darbar_tasmim_2;
            *khazane += current->khazane_tasmim_2;
        }

        else if(tasmim == -1){
            printf("Do you want to save this game ?(y/n)\n");
            scanf(" %c" , &vaziyat_exit);
            if(vaziyat_exit == 'y'){
            save(list , *mardom ,  *darbar , *khazane , number_of_node);
                return 1;
            }
            else if(vaziyat_exit == 'n'){
                return 1;
            }
        }

        if((*mardom > 100) || (*darbar > 100) || (*khazane > 100)){
            if(*mardom > 100){
                *mardom = 100;
            }
            else if(*darbar > 100){
                *darbar = 100;
            }
            else if(*khazane > 100){
                *khazane = 100;
            }
        }

        printf("People:%d  Court:%d   Treasury:%d\n" , *mardom , *darbar , *khazane);

        current->emkan -= 1;

        if(current->emkan == 0){
            del(current , &list);
            *
            number_of_node -= 1;

        }

        if(i == 20){
            list = creat_list();
            *number_of_node = 7;
            i = -1;
        }

        printf("\n\n\n");
    }

return 0;
}

//----------------------------
//*****************************

int save(struct problem * list , int mardom , int darbar , int khazane , int* number_of_node){

    printf("Enter your name to save game: ");

    char name_save_user[50];

    scanf("%s" , name_save_user );

    strcat(name_save_user , ".txt");


    FILE* save_file;
    save_file = fopen(name_save_user   , "w");
    if(save_file == NULL){
        printf("cant save this file");
        return 1;
    }


    struct problem * current;
    current = list;

    fprintf(save_file , "%d\n" , *number_of_node);

    for(int y = 0 ; y < *number_of_node ; y++){
         fprintf(save_file , "%d\n" , current->number_node);
         fprintf(save_file , "%d\n" , current->emkan);
         current = current->next;
    }


    fprintf(save_file , "%d\n" , mardom);
    fprintf(save_file , "%d\n" , darbar);
    fprintf(save_file , "%d\n" , khazane);

}

//---------------------------------------------
//*********************************************

int load(struct problem* list , int * mardom  , int * darbar , int * khazane , int * number_of_node){

    printf("Enter name of saved game: ");
    char name_file_load[200];
    scanf("%s" , name_file_load);

    strcat(name_file_load , ".txt");

    FILE * load_file;
    load_file = fopen( name_file_load , "r");
    if(load_file == NULL){
        printf("cant open the file\n");
        return 1;
    }


    struct problem* current;
    current = list;

    char buffer[500];
    for(int u = 0 ; u < 7 ; u++){
        current->emkan = 0;
        current = current->next;
    }

    current = list;

    fscanf(load_file , "%d" , number_of_node);
    fgets(buffer , 500 , load_file);

    int number ;

    for(int p = 0 ; p < *number_of_node ; p++){
        current = list;
        fscanf(load_file , "%d" , &number);
        fgets(buffer , 500 , load_file);
        for(int r = 0 ; r < number - 1; r++ ){
            current= current->next;
        }

        fscanf(load_file , "%d" , &(current->emkan));

        fgets(buffer , 500 , load_file);
    }


    fscanf(load_file , "%d" , mardom);
    fgets(buffer , 500 , load_file);

    fscanf(load_file , "%d" , darbar);
    fgets(buffer , 500 , load_file);

    fscanf(load_file , "%d" , khazane);
    fgets(buffer , 500 , load_file);
    current = list;
    for(int k = 0 ; k< 7 ; k++){
        if(current->emkan == 0){
            del(current , &list);
        }
        current = current->next;
    }


 return 0 ;
}


int main()
{

    printf("Enter your name: \n");
    char user_name[50];
    scanf("%s" , user_name);
    printf("\nWelcome %s, select one of these options: \n" , user_name);


    printf("1) Start a new game\n");
    printf("2) Resume a game\n");
    printf("3) Exit\n");

    while(1){
        int number_of_node = 7;

        int mardom = 50 , darbar = 50 , khazane = 50;
        struct problem* list;

        int entekhab;
        scanf("%d" , &entekhab);

        if(entekhab == 1){
            printf("Let's go \n\n");
            list = creat_list();
            game(list , &mardom , &darbar , &khazane , &number_of_node);

        }

        else if(entekhab == 2){
            list = creat_list();
            load(list , &mardom , &darbar , &khazane ,&number_of_node);
            printf("Let's go \n\n");
            game(list , &mardom , &darbar , &khazane , &number_of_node);
        }

        else if(entekhab == 3){
            printf("Good bye :)\n");
            return 1;
        }

        printf("\n\n1) Start a new game\n");
        printf("2) Resume a game\n");
        printf("3) Exit\n");
    }

    return 0;
}










