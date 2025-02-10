#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/datatype.h"
#include "../include/function.h"

#define MAX_ACCOUNTS 100 // Định nghĩa số lượng tài khoản tối đa

// Mảng tĩnh chứa danh sách tài khoản
Account accounts[MAX_ACCOUNTS];
int totalAccounts = 0;

void showRole()
{
    printf("======Bank Management System=======\n");
    printf("%10sCHOOSE YOUR ROLE\n");
    printf("[1]Admin\n");
    printf("[2]User\n");
    printf("[0]Exit the program\n");
}

void showUserManagement()
{
    printf("======User Management======\n");
    printf("%10sMENU\n");
    printf("[1]Add a new user\n");       // thêm mới
    printf("[2]Show all users\n");       // xem danh sách
    printf("[3]lock(unlock) an user\n"); // khóa(mở khóa)
    printf("[0]Exit\n");
}

void showLogin()
{
    char email[20], password[10];
    printf("======Bank Management System=======\n");
    printf("%10sLOGIN\n");
    printf("Email: ");
    fflush(stdin);
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0; // Xóa ký tự xuống dòng
    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;
}

void addAccount()
{
    if (totalAccounts >= MAX_ACCOUNTS)
    {
        printf("Error: Account limit reached!\n");
        return;
    }
    
    Account acc;
    printf("Input Account number: ");
    if (scanf("%d", &acc.accountNumber) != 1)
    {
        printf("Invalid account number!\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    printf("Input Account holder: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0';

    printf("Input balance: ");
    if (scanf("%lf", &acc.balance) != 1)
    {
        printf("Invalid balance!\n");
        while (getchar() != '\n');
        return;
    }

    accounts[totalAccounts++] = acc; // Lưu tài khoản mới vào danh sách
    printf("Account added successfully!\n");
}

void displayAccounts() {
    if (totalAccounts == 0) {
        printf("No accounts available!\n");
        return;
    }

    printf("\n==================================================================\n");
    printf("| %-10s | %-20s | %15s |\n", "Account", "Name", "Balance");
    printf("==================================================================\n");

    for (int i = 0; i < totalAccounts; i++) {
        printf("| %-10d | %-20s | %15.2f |\n",
               accounts[i].accountNumber,
               accounts[i].name,
               accounts[i].balance);
    }

    printf("==================================================================\n");
}


void saveToFile()
{
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL)
    {
        printf("File opening error!\n");
        return;
    }
    for (int i = 0; i < totalAccounts; i++)
    {
        fprintf(file, "%d %s %.2f\n",
                accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
    fclose(file);
}

void loadFromFile()
{
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL)
    {
        return; // Nếu file chưa tồn tại, bỏ qua
    }
    while (totalAccounts < MAX_ACCOUNTS &&
           fscanf(file, "%d %49s %lf",
                  &accounts[totalAccounts].accountNumber,
                  accounts[totalAccounts].name,
                  &accounts[totalAccounts].balance) == 3)
    {
        totalAccounts++;
    }
    fclose(file);
}