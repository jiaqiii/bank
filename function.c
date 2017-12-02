#include<openssl/sha.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"record.h"


/*******************************************************************************
* FUNCTION NAME: addRecord
* 
* DESCRIPTION: add new account into the list
*
* PARAMETERS: struct record** start  :  the address of the pointer to the start of the list
*             int accountno : new account number the user entered  
*             char name[] : name for the account the user input
*             char type[] : currency type
*             int value : account balance
*
* RETURN VALUE: 0 : added successfully
*               1 : username taken
******************************************************************************/
int addRecord(struct record** start, char name[], char pw[], char type[], float value)
{
    char salt[5];
    int i = 0;
    time_t t;
    int rvalue = 0;
    int check = 0;
    struct record* temp;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    temp = (struct record*)malloc(sizeof(struct record));
    srand((unsigned) time(&t));
    for(;i<5; i++)
    {
        salt[i] = (rand() %50)+1;
    }
    strcat(pw, salt);
    SHA256((const unsigned char*)pw, strlen(pw), hash);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        temp->hash[i] = hash[i];
    //strcpy((char*)temp->hash, (char*)hash);
    strcpy(temp->salt, salt);
    strcpy(temp->name , name);
    strcpy(temp->type , type);
    temp->value = value;
    temp->next = NULL;
    if(*start == NULL)
    {
        *start = temp;
    }else
    {
        struct record *temp2;
        struct record *before;
        temp2 = *start;
        while(temp2 != NULL && check !=1 )
        {
            if(strcmp(temp2->name, name) == 0)
            {
                check = 1;
            }
            else
            {
                before = temp2;
                temp2 = temp2->next;
            }
        }
        if(check == 0)
        {
            before->next = temp;
        }
        else
        {
             rvalue = 1;
             printf("User name is already taken, please select a different user name.\n");
        }
    }

    if(debug == 1)
    {
        printf(" function addRecord is called, with parameters struct double pointer: &start, account name:%s, currency type:%s, value:%f\n " , name, type, value);
    }

    return rvalue;

}


/*******************************************************************************
* FUNCTION NAME: printRecord
* 
* DESCRIPTION: print information of the selected account
*
* PARAMETERS: struct record* start  :  the pointer to the start of the list
*             int accountno : account number the user entered  
*
* RETURN VALUE: 0
******************************************************************************/
int printRecord(struct record* start, char name[])
{
    int check = 0;
    struct record* temp;
    temp = start;
    while(temp != NULL)
    {
       if(strcmp((temp->name), name) == 0)
       {
           printf(" \n account name: %s \n currency type: %s \n balance: %f", temp->name, temp->type, temp->value);
           check = 1;
           temp = temp->next;
       }
       else
       {
           temp = temp->next;
       }
    }
    if(check == 0)
    {
        printf("\naccount not found\n");
    }
  
    
    if(debug == 1)
    { 
        printf("function printRecord is called, with parameters struct pointer: start, account name: %s\n", name);
    }

        return 0;

}


/*******************************************************************************
* FUNCTION NAME: modifyRecordValue
* 
* DESCRIPTION: modify selected account
*
* PARAMETERS: struct record* start  :  the pointer to the start of the list
*             int accountno : account number the user entered  
*             int value : new balance
*
* RETURN VALUE: 0
******************************************************************************/
int modifyRecordValue(struct record* start, char name[], float value)
{
    int check;
    struct record* temp;
    temp = start;
    check = 0;
    while(temp != NULL)
    {
        if(strcmp(temp->name, name) == 0)
        {
             temp -> value = value;
             check = 1;
             printf("new balace: %f", temp->value);
             temp = temp->next;
        }
        else
        {
            temp = temp->next;
        }
    }
    if(check == 0)
    {
        printf("\naccount not found\n");
    }

    if(debug == 1)
    {
        printf("function modifyRecord is called, with parameters struct pointer: start, account name: %s,  value: %f\n", name, value);
    }
        return 0;

}

/*******************************************************************************
* FUNCTION NAME: modifyRecordType
* 
* DESCRIPTION: modify selected account
*
* PARAMETERS: struct record* start  :  the pointer to the start of the list
*             int accountno : account number the user entered  
*             char type[] : new currency type
*
* RETURN VALUE: 0
******************************************************************************/
int modifyRecordType(struct record* start, char name[], char type[], float(*table)[3])
{
    int check;
    int from;
    int to;
    struct record* temp;
    temp = start;
    check = 0;
    while(temp != NULL && check != 1)
    {
        if(strcmp(temp->name, name) == 0)
        {
             if(strcmp(type, "rmb")==0 || strcmp(type,"dollar") ==0 || strcmp(type,"euro") ==0)
             {
                 if(strcmp(temp -> type, "rmb")== 0)
                 {
                      from = 0;
                 }
                 else if(strcmp(temp ->type, "dollar") == 0)
                 {
                      from = 1;
                 }
                 else
                 {
                      from = 2;
                 }

                 strcpy(temp->type, type);
                 if(strcmp(temp -> type, "rmb")== 0)
                 {
                      to = 0;
                 }
                 else if(strcmp(temp ->type, "dollar") == 0)
                 {
                      to = 1;
                 }
                 else
                 {
                      to = 2;
                 }
                 temp->value = table[from][to] * temp->value;
             } 
        
             check = 1;
             printf("new balace: %f %s", temp->value, temp -> type);
             /*temp = temp->next;*/
        }
        else
        {
            temp = temp->next;
        }
    }
    if(check == 0)
    {
        printf("\naccount not found\n");
    }

    if(debug == 1)
    {
        printf("function modifyRecord is called, with parameters struct pointer: start, account name: %s, type: %s\n", name, type);
    }
        return 0;

}

/*******************************************************************************
* FUNCTION NAME: printAllRecords
* 
* DESCRIPTION: print out all the records on the list
*
* PARAMETERS: struct record* start  :  the pointer to the start of the list
*
* RETURN VALUE: 0
******************************************************************************/
void printAllRecords(struct record* start)
{
    struct record* temp;
    temp = start;
    while(temp!=NULL)
    {
        printf("\nname: %s, type: %s, balance: %f\n", temp->name, temp->type, temp->value);
        temp = temp->next;
    }
    if(debug == 1)
    { 
        printf("function printAllRecord is called, with parameters struct pointer: start\n");
    }
}


/*******************************************************************************
* FUNCTION NAME: deleteRecord
* 
* DESCRIPTION: delete the selected record on the list
*
* PARAMETERS: struct record** start  :  the address of the pointer to the start of the list
*             int accountno : account number the user entered  
*
* RETURN VALUE: 0
******************************************************************************/
int deleteRecord(struct record** start, char name[])
{
    struct record* current;
    struct record* before;
    current = *start;
    while(current!=NULL)
    {
        if(strcmp((*start)->name, name) == 0)
        {
            (*start) = (*start)->next;
            free(current);
            current = (*start);
        }
        else if(strcmp(current->name, name) != 0)
        {
            before = current;
            current = current->next;
        }
        else
        {
        before->next = current-> next;
        free(current);
        current = before->next;
        }
    }

    if(debug == 1)
    {
        printf("function deleteRecord is called, with parameters struct double pointer: start,  accountname: %s\n", name);
    }
        return 0;

}


/*******************************************************************************
* FUNCTION NAME: login
* 
* DESCRIPTION: verify username and password
*
* PARAMETERS: struct record** start  :  the address of the pointer to the start of the list
*             char name[] : username the user entered  
*             char pw[] : pw the user entered
*
* RETURN VALUE: 0 : account not found
*               1 : login success
*               2 : invalid pw
******************************************************************************/
int login(struct record* start, char name[], char pw[])
{
    int rvalue = 0;
    time_t t;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char salt[6];
    char ps_salt[50];
    int check = 0;
    struct record* temp;
    temp = start;
    srand((unsigned) time(&t));
printf("%s|%d\n", name,strlen(name));
printf("%s|%d\n", temp->name, strlen(temp->name));
    while(temp != NULL && check != 1)
    {
        if(strcmp((temp->name), name) == 0)
        {
            strcpy(salt, (temp->salt));
            strcpy(ps_salt,pw);
            strcat(ps_salt , salt);
            SHA256((const unsigned char*)ps_salt, strlen(ps_salt), hash);
for(int i = 0; i < 32; i++) printf("%02X ",hash[i]);
printf("\n");
for(int i = 0; i < 32; i++) printf("%02X ",(unsigned char*)temp->hash[i]);
printf("\n");
            if(strcmp((char*)(temp -> hash), (char*)hash) == 0)
            {
                rvalue = 0;
                check = 1;
            }
            else
            {
		rvalue =1;
		check = 1;
            }
printf("%d",rvalue);
        }
        else
        {
            temp = temp->next;
        }
    }
    if(check == 0)
    {
        rvalue = 0;
    }
    else
    {
        if(rvalue == 0)
        {
            rvalue = 1;
        }
        else
        {
            rvalue = 2;
        }
    }
    return rvalue;
}  

/*******************************************************************************
* FUNCTION NAME: transfer
* 
* DESCRIPTION: verify and transfer balance
*
* PARAMETERS: struct record* start  :  the address of the pointer to the start of the list
*             char name[] : username
*             char client[] : client username
*             int value : transfer amount
*
* RETURN VALUE: 0 : client account not found
*               1 : not enough balance
*               2 : transfer succeed
******************************************************************************/
int transfer(struct record* start, char name[], char client[], float value)
{
    int check = 0;
    int money = 0;
    int rvalue = 0;
    struct record* user;
    struct record* to;
    user = start;
    to = start;
    while(user != NULL && check !=1)
    {
        if(strcmp((user->name), name) == 0)
        {
            check = 1;
            if( (user->value) >= value )
            {
                money = 1;
            }
        }
        else
        {
            user = user->next;
        }
    }
    check = 0;
    while(to != NULL && check != 1)
    {
        if(strcmp((to->name), client) == 0)
        {
            if( money == 1)
            {
                user->value = (user->value)-value;
                to->value = (to->value)+value;
                rvalue = 2;
                check = 1;
            }
            else
            {
                rvalue = 1;
                check =1;
            }
        }
        else
        {
            to = to->next;
        }
    }
    return rvalue;
}         


/*******************************************************************************
* FUNCTION NAME: readFile
* 
* DESCRIPTION: restore data from file to array
*
* PARAMETERS: struct account accarray[]: the array the function is writting from
*             char filename: the file the function is writing to
*
* RETURN VALUE: 1 if error intercept function, 0 if the function went through  
******************************************************************************/
int readfile(struct record** start, char filename[], char hashname[])
{
    char name[25];
    char salt[6];
    unsigned char hash[33];
    char type[10];
    float value;
    char trash[80];
    FILE *file1;
    FILE *file2;
    file1 = fopen(filename,"r");
    file2 = fopen(hashname,"rb");
    if(!file1)
    {
        return 1;
    }
    if(!file2)
    {
        return 1;
    }
    while(!(feof(file1)))
    {
        strcpy(name, "\0");
        strcpy(salt, "\0");
        strcpy((char*)hash, "\0");
        strcpy(type, "\0");
        fscanf(file1, "%s", name);
        fscanf(file1, "%s", salt);
        fread(hash, SHA256_DIGEST_LENGTH, 1, file2);
        fscanf(file1, "%s", type);
        fscanf(file1, "%f", &value);
        fgets(trash, 1, file1);
        if(feof(file1))
        {
            break;
        }
        else
        {
        loadRecord(start, name, salt, hash, type, value);
        }
    }
    fclose(file1);
    fclose(file2);
    if(debug == 1)
    {
        printf("\nfunction readfile is called, with parameters struct record**: start, filename: %s", filename);
    }

    return 0;
}


/*******************************************************************************
* FUNCTION NAME: writeFile
* 
* DESCRIPTION: write data into a .txt file
*
* PARAMETERS: struct account accarray[]: the array the function is writting from
*             int numcust: number of customer provided
*             char filename: the file the function is writing to
*
* RETURN VALUE: void
******************************************************************************/
void writefile(struct record* start, char filename[], char hashname[])
{
    struct record* temp;
    FILE *file1;
    FILE *file2;
    temp = start;
    file1 = fopen(filename, "w");
    file2 = fopen(hashname, "wb");
    if(!file1)
    {
        printf("file not opened");   
    }
    if(!file2)
    {
        printf("file not opened");   
    }
    while(temp != NULL)
    {
        fprintf(file1, "%s\n", temp->name);
        fprintf(file1, "%s\n", temp->salt);
        fwrite(temp->hash, SHA256_DIGEST_LENGTH, 1 ,file2);
        fprintf(file1, "%s\n", temp->type);
        fprintf(file1, "%f\n", temp->value);
        temp = temp->next;
    }
    if(fclose(file1)!=0)
    {
        printf("file not opened");
    }
    if(fclose(file2)!=0)
    {
        printf("file not opened");
    }

    if(debug == 1)
    {
        printf("\nfunction writefile is called, with parameers struct record*: start, filename: %s", filename);
    }
}
        

/*******************************************************************************
* FUNCTION NAME: loadRecord
* 
* DESCRIPTION: add new account into the list, use with readfile
*
* PARAMETERS: struct record** start  :  the address of the pointer to the start of the list
*             char name[] : name for the account the user input
              char salt[] :
              char hash[] :
*             char type[] : currency type
*             int value : account balance
*
* RETURN VALUE: 0
******************************************************************************/
int loadRecord(struct record** start, char name[],char salt[],unsigned char hash[], char type[], float value)
{
    struct record* temp;
    temp = (struct record*)malloc(sizeof(struct record));
    strcpy(temp->name , name);
    strcpy(temp->salt , salt);
    //strcpy(temp->hash , hash);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        temp->hash[i] = hash[i];
    strcpy(temp->type , type);
    temp->value = value;
    temp->next = NULL;
    if(*start == NULL)
    {
        *start = temp;
    }else
    {
        struct record *temp2;
        struct record *before;
        temp2 = *start;
        while(temp2 != NULL)
        {
            before = temp2;
            temp2 = temp2->next;
        }
        before->next = temp;
    }

    if(debug == 1)
    {
        printf(" function addRecord is called, with parameters struct double pointer: &start, name:%s, currency type:%s, value:%f\n " , name, type, value);
    }

    return 0;

}

