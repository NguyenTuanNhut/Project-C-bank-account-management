#ifndef DATATYPE_H
#define DATATYPE_H

typedef struct {
    char ID[20];
    char name[20];
    char numberPhone[15];
    char status[10];
    char email[30];
    double balance;
} Account;
typedef struct {
    char username[50];
    char password[50];
} Admin;
#endif /* DATATYPE_H */
