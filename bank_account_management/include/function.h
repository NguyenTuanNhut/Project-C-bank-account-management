#include"../include/datatype.h"
void findAccountByID(Account accounts[], int size, const char* ID) ;
void showMenu();
void showUserManagement();
void addCount();
void loadFromFile();
void saveToFile();
void displayAccounts();
void showAcc(int i);
void findAccountByName(Account accounts[], int size, const char* name); // Khai báo nguyên mẫu
void addUser();
void showMenuFind();
void showMenuAdd();
int compareAscending(const void *a, const void *b);
int compareDescending(const void *a, const void *b);
void sortUsersByName();
void showLockUser();
void clearScreen();
int findIndexByID(const char *ID);
int isIDExists(const char *id);
int isPhoneExists(const char *phone);
int isEmailExists(const char *email);
int isValidPhone(const char *phone);
int isValidEmail(const char *email);
void adminLogin();
void loginUser();
void showMenuUser();
void editUserInfo();