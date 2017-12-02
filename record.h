/*******************************************************************************
 *
 * Name: Jiaqi Li
 *
 * Class: ICS 355
 *
 * File: record.h
 *
 * Description: header file contains functionn prototype and struct record
 *
 * *****************************************************************************/
 
struct record
{
    char salt[6];
    unsigned char hash[33];
    char name[25];
    char type[10];
    float value;
    struct record* next;
};

int loadRecord(struct record **, char[], char[], unsigned char[], char[], float);

int addRecord(struct record **,  char[], char[],char[], float);

int modifyRecordValue(struct record*, char[], float);

int modifyRecordType(struct record*, char[], char[], float(*)[3]);

int deleteRecord(struct record**, char[]);

int printRecord(struct record*, char[]);

void printAllRecords(struct record*);
 
void writefile(struct record*, char[], char[]);

int readfile(struct record** start, char[], char[]);

int transfer(struct record*, char[], char[], float);

int login(struct record*, char[], char[]);

int debug;
