#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "record.h"

int debug = 0;

void getaccountno(int*);
void getvalue(float*);

int main(int argc, char *argv[])
{
    char pw[20];
    int flag = 0;
    float ratio;
    char clear[20];
    char name[30];
    char type[10];
    float value;
    struct record* start = NULL;
    int check =0;
    int result = 0;
    char command[15];
    int i = 0;
    char* pch;
    int from;
    /*rmb 0, dollar 1, euro 2*/
    int to;
    float ratioTable[3][3]= {
        {1, 0.15, 0.13},
        {6.58, 1, 0.85},
        {7.77, 1.18, 1} };

 if(argc == 1)
    {
        debug = 0;
    }
    else if(argc == 2 && (strcmp(argv[1], "debug") == 0))
    {
        debug = 1;
    }
    else
    {
        flag = 1;
        printf("invalid command, please re-enter\n");
     }

if(flag != 1)
{

    readfile(&start, "file.txt", "hash.bin");

    do
    {
        printf("\n");
        printf("1.Add a new account in the database.\n");
        printf("2.Modify an account balance using the accountno as the key.\n");
        printf("3.Modify an account currency type using the accountno as the key.\n");
        printf("4.Print information about a record using the accountno as the key.\n");
        printf("5.Print all information database.\n");
        printf("6.Delete an existing record from the database using the accountno as a key.\n");
        printf("7.Quit the program.\n");

        printf("\nPlease enter the starting number of the option you would like to choose:\n");

        if(scanf("%d",&result)==0)
        {
            i = 0;
            while((i < 20 ) && (command[i] = fgetc(stdin)) != '\n')
            {
            
                i++;
             
            }
            
            command[i] = '\0';
    
            pch = strtok(command, " ");

            if(pch == NULL)
            {
                check = 1;
            }
            else
            {
    
            if(strcmp("MAINT",pch)==0 && check !=1)
            {
            
                pch = strtok(NULL, " ");

                if(pch == NULL)
                {
                    check = 1;
                }
                else
                {
                if(strcmp("rmb",pch) == 0)
                {
                    from = 0; 
                }
                else if(strcmp("dollar", pch) == 0)
                {
                    from = 1;
                }
                else if(strcmp("euro" ,pch) == 0 )
                {
                    from =2;
                }
                else
                {
                check = 1;
                }
                }
         

                pch = strtok(NULL, " ");

                if( pch == NULL)
                {
                     check =1;
                }
                else
                {

                if(strcmp("rmb",pch) == 0)
                {
                    to = 0; 
                }
                else if(strcmp("dollar", pch) == 0)
                {
                    to = 1;
                }
                else if(strcmp("euro" ,pch) == 0 )
                {
                    to =2;
                }
                else
                {
                    check = 1;
                }
                }

               pch = strtok(NULL," ");

               if( pch == NULL)
               {
                   check = 1;
               }
               else
               {
               if(strcmp(pch, "0") == 0)
               {
                   ratio = 0.0;
               }
               else
               {
                   ratio = atof(pch);
                   if(ratio == 0)
                   {
                       check = 1;
                   }
                }
                }
               if(check != 1)
               {
               ratioTable [from] [to] = ratio;
               ratioTable [to] [from] = 1/ratio;
               }
             }
             }
        result = 0;
        while(fgetc(stdin) != '\n')
        {
        }
    }
                
 switch(result){

        case(1) : 
                  do
                  {
			  printf("please register new account name\n");
			  scanf("%s", name);
			  fgets(clear,30,stdin);
                          printf("please register new pw\n");
                          scanf("%s", pw);
                          fgets(clear,30,stdin);
			  do
			  {
				  fgets(clear,30,stdin);
				  printf("please register a preferred currncy type(euro/ rmb / dollar) \n");
				  scanf("%s", type);
			  }while((strcmp("euro", type)!=0) && (strcmp("dollar", type)!=0) && (strcmp("rmb", type)!=0));
			  fgets(clear,30,stdin);
			  printf("please register new account balance\n");
			  getvalue(&value);
			  fgets(clear,30,stdin);
                  }while(addRecord(&start, name, pw,type, value) != 0);
                  result = 0;
                  break;

        case(2) : printf("please enter username to modify account balance\n");
                  scanf("%s", name);
                  fgets(clear,30,stdin);
                  printf("please enter new account balance\n");
                  getvalue(&value);
                  modifyRecordValue(start, name, value);
                  result = 0;
                  break;

        case(3) : printf("please enter username to modify account currency type\n");
                  scanf("%s", name);
                  do
                  {
                  fgets(clear,30,stdin);
                  printf("please register a preferred currncy type(euro/ rmb / dollar) \n");
                  scanf("%s", type);
                  }while((strcmp("euro", type)!=0) && (strcmp("dollar", type)!=0) && (strcmp("rmb", type)!=0));
                  modifyRecordType(start, name, type, ratioTable);
                  result = 0;
                  break;


        case(4) : printf("please enter username to print account record\n");
                  scanf("%s", name);
                  fgets(clear,30,stdin);
                  printRecord(start, name);
                  result = 0;
                  break;

        case(5) : printAllRecords(start);
                  result = 0;
                  break;

        case(6) : printf("please enter username of the account to be deleted\n");
                  scanf("%s", name);
                  fgets(clear,30,stdin);
                  deleteRecord(&start, name);
                  result = 0;
                  break;
                  }
}while(result <1 || result>7);
}
    
    writefile(start,"file.txt","hash.bin");
    return 0;
}


void getaccountno(int* uaccountno)
{
    int termsread;
    char clear[20];
    termsread = scanf("%d" , uaccountno);
    while(termsread == 0)
    {
        fgets(clear, 10, stdin);
        printf("Error: please re-enter account number\n");
        termsread = scanf("%d" , uaccountno);
    }
}

void getvalue(float* value)
{
    int termsread;
    char clear[20];
    termsread = scanf("%f" , value);
    while(termsread == 0)
    {
        fgets(clear, 10, stdin);
        printf("Error: please re-enter account number\n");
        termsread = scanf("%f" , value);
    }
}

