#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/datatype.h"
#include "../include/function.h"
#include <ctype.h>

#define MAX_ACCOUNTS 100 // Định nghĩa số lượng tài khoản tối đa

// Mảng tĩnh chứa danh sách tài khoản
Account accounts[MAX_ACCOUNTS];

int totalAccounts = 0;
int choice = 1;
void clearScreen()
{
    printf("\033[H\033[J");
}
void showMenuUser(){
    printf("===============User===============\n");
    printf("[1]update profile\n");
    printf("[2]transfer money\n");
}
void adminLogin()
{
    Admin admin;
    char input_username[30];
    char input_password[15];

    strcpy(admin.username, "admin@gmail.com"); // Tài khoản
    strcpy(admin.password, "0327563534");      // Mật khẩu

    do
    {
        printf("=== ADMIN LOGIN ===\n");
        printf("Username: ");
        fgets(input_username, sizeof(input_username), stdin);
        input_username[strcspn(input_username, "\n")] = 0;
        if (strcmp(input_username, admin.username) != 0)
        {
            printf("Invalid username!\n");
            continue;
        }
        break;
    } while (1);
    do
    {
        printf("Password: ");
        fgets(input_password, sizeof(input_password), stdin);
        input_password[strcspn(input_password, "\n")] = 0;

        // Kiểm tra password
        if (strcmp(input_password, admin.password) != 0)
        { // So sánh với trường password
            printf("Invalid password!\n");
            continue;
        }

        printf("Login Successful!\n");
        break;

    } while (1);
}

void loginUser()
{
    char username[50]; // Kích thước lớn hơn để khớp với struct
    char password[15];

    do
    {
        printf("=== USER LOGIN ===\n");
        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0';

        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

        int flag = 0;

        for (int i = 0; i < totalAccounts; i++)
        {
            if (strcmp(username, accounts[i].email) == 0)
            {
                if (strcmp(accounts[i].status, "locked") == 0)
                {
                    flag = 2;
                    break;
                }
                if (strcmp(password, accounts[i].numberPhone) == 0)
                {
                    flag = 1;
                    break;
                }
            }
        }

        if (flag == 1)
        {
            printf("Login successful!\n");
            break;
        }
        else if (flag == 2)
        {
            printf("Your account has been locked.\n");
        }
        else
        {
            printf("Incorrect account or password.\n");
        }

    } while (1);
}
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
    printf("[2]Show all Account\n");     // xem danh sách
    printf("[3]lock(unlock) an user\n"); // khóa(mở khóa)
    printf("[4]Find account\n");
    printf("[5]Sortbyname\n");
    printf("[6]Edit user information\n");
        printf("[0]Exit\n");
}
void addAccount()
{
    if (totalAccounts >= MAX_ACCOUNTS)
    {
        printf("Error: Account limit reached!\n");
        return;
    }
    Account acc;
    do
    {
        printf("Input Id: ");
        scanf("%19s", acc.ID);
        while (getchar() != '\n')
            ; // Xóa bộ đệm

        if (strlen(acc.ID) == 0)
        {
            printf("Error: ID cannot be empty!\n");
            continue;
        }
        if (isIDExists(acc.ID))
        {
            printf("Error: ID already exists!\n");
            continue;
        }
        break;
    } while (1);
    do
    {
        printf("Input Account holder: ");
        fgets(acc.name, sizeof(acc.name), stdin);
        acc.name[strcspn(acc.name, "\n")] = '\0';

        if (strlen(acc.name) == 0)
        {
            printf("Error: Name cannot be empty!\n");
            continue;
        }
        break;
    } while (1);
    do
    {
        printf("Input numberPhone: ");
        fgets(acc.numberPhone, sizeof(acc.numberPhone), stdin);
        acc.numberPhone[strcspn(acc.numberPhone, "\n")] = '\0';
        if (!isValidPhone(acc.numberPhone))
        {
            printf("Error: Phone must be 10-14 digits!\n");
            continue;
        }
        if (isPhoneExists(acc.numberPhone))
        {
            printf("Error: Phone number already exists!\n");
            continue;
        }
        break;
    } while (1);
    do
    {
        printf("Input email: ");
        fgets(acc.email, sizeof(acc.email), stdin);
        acc.email[strcspn(acc.email, "\n")] = '\0';
        if (!isValidEmail(acc.email))
        {
            printf("Error: Invalid email format!\n");
            continue;
        }
        if (isEmailExists(acc.email))
        {
            printf("Error: Email already exists!\n");
            continue;
        }
        break;
    } while (1);
    do{
        printf("input balance: ");
        scanf("%lf",&acc.balance);
        while (getchar() != '\n');
        if(acc.balance<0){
            printf("Error: Invalid balance ");
            continue;
        }
        break;
    }while(1);
    strcpy(acc.status, "open");
    accounts[totalAccounts++] = acc;
    saveToFile();
    printf("Account added successfully!\n");
}
int isIDExists(const char *id)
{
    for (int i = 0; i < totalAccounts; i++)
    {
        if (strcmp(accounts[i].ID, id) == 0)
            return 1;
    }
    return 0;
}
int isPhoneExists(const char *phone)
{
    for (int i = 0; i < totalAccounts; i++)
    {
        if (strcmp(accounts[i].numberPhone, phone) == 0)
            return 1;
    }
    return 0;
}
int isEmailExists(const char *email)
{
    for (int i = 0; i < totalAccounts; i++)
    {
        if (strcmp(accounts[i].email, email) == 0)
            return 1;
    }
    return 0;
}
int isValidPhone(const char *phone)
{
    if (strlen(phone) < 10 || strlen(phone) > 14)
        return 0;
    for (int i = 0; phone[i]; i++)
    {
        if (!isdigit(phone[i]))
            return 0;
    }
    return 1;
}
int isValidEmail(const char *email)
{
    int at_count = 0, dot_count = 0;
    for (int i = 0; email[i]; i++)
    {
        if (email[i] == '@')
            at_count++;
        else if (email[i] == '.')
            dot_count++;
    }
    return (at_count == 1 && dot_count >= 1);
}

// Hàm tìm kiếm tài khoản theo tên
void findAccountByName(Account accounts[], int size, const char *name) // Khai báo nguyên mẫu
{

    int count = 0;
    int displayed = 0; // Cờ để kiểm soát displayAccounts()

    for (int i = 0; i < size; i++)
    {
        if (strcmp(accounts[i].name, name) == 0)
        {
            count++;

            if (count == 1 && displayed == 0)
            {
                displayAccounts(); // Chỉ hiển thị danh sách một lần
                displayed = 1;     // Đánh dấu đã hiển thị
            }

            showAcc(i);
        }
    }

    if (count == 0)
    {
        printf("Account not found.\n");
    }
}

void saveToFile()
{
    FILE *file = fopen("accounts.bin", "wb");
    if (file == NULL)
    {
        printf("File opening error!\n");
        return;
    }
    for (int i = 0; i < totalAccounts; i++)
    {
        fprintf(file, "%s %s %s %s %s %.2f\n",
                accounts[i].ID, accounts[i].name, accounts[i].numberPhone, accounts[i].status, accounts[i].email, accounts[i].balance);
    }
    fclose(file);
}

void loadFromFile()
{
    FILE *file = fopen("accounts.bin", "rb");
    if (file == NULL)
    {
        return; // Nếu file chưa tồn tại, bỏ qua
    }
    while (totalAccounts < MAX_ACCOUNTS &&
           fscanf(file, "%s %49s %s %s %s %lf",
                  accounts[totalAccounts].ID,
                  accounts[totalAccounts].name,
                  accounts[totalAccounts].numberPhone,
                  accounts[totalAccounts].status,
                  accounts[totalAccounts].email,
                  &accounts[totalAccounts].balance) == 6)
    {
        totalAccounts++;
    }

    fclose(file);
}
void displayAccounts()
{

    if (totalAccounts == 0)
    {
        printf("No accounts available!\n");
        return;
    }

    printf("\n=======================================================================================================================\n");
    printf("| %-10s | %-20s | %15s | %15s | %25s | %15s |\n", "ID", "Name", "NumberPhone", "status", "Email","Balance");
    printf("=======================================================================================================================\n");
}
void showAcc(int i)
{

    printf("| %-10s | %-20s | %15s | %15s | %25s | %15lf |\n",
           accounts[i].ID,
           accounts[i].name,
           accounts[i].numberPhone,
           accounts[i].status,
           accounts[i].email,
           accounts[i].balance);

    printf("=======================================================================================================================\n");
}
void showMenuAdd()
{

    do
    {
        printf("[0]Exit\n");
        printf("[1]Add a new user\n");
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice != 1 && choice != 0)
        {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n')
                ;     // Xóa bộ đệm nhập
            continue; // Quay lại đầu vòng lặp để nhập lại
        }

        if (choice == 0)
        {
            return;
        }
        clearScreen();
        while (1)
        {
            printf("=============== Add New User ===============\n");
            addAccount();
            printf("Press 0 to exit, 1 to add another user\n");
            printf("Choice: ");
            scanf("%d", &choice);
            clearScreen();
            if (choice == 0)
            {
                return;
            }
            if (choice == 1)
            {
                continue;
            }
        }
    } while (choice != 0);
    clearScreen();
}

void showMenuFind()
{

    do
    {
        printf("[1]Find by name\n");
        printf("[2]Find by id\n");
        printf("[0]Exit");
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice != 1 && choice != 2)
        {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n')
                ; // Xóa bộ đệm
            continue;
        }
        while (getchar() != '\n')
            ; // phai xoa bo nho dem de tranh loi
        printf("===============Find Account===============\n");
        switch (choice)
        {
        case 1:
            char nameSearch[20];
            printf("Input name search: ");
            fgets(nameSearch, sizeof(nameSearch), stdin);
            nameSearch[strcspn(nameSearch, "\n")] = 0;

            findAccountByName(accounts, totalAccounts, nameSearch);
            break;
        case 2:
            char Id[20];
            printf("Input ID: ");
            scanf("%s", Id);
            Id[strcspn(Id, "\n")] = 0;
            findAccountByID(accounts, totalAccounts, Id);
        }

    } while (choice != 0);
}

void sortUsersByName()

{

    do
    {
        printf("[1] Compare Ascending\n");
        printf("[2] Compare Descending\n");
        printf("[0] Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice != 1 && choice != 2)
        {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n')
                ; // Xóa bộ đệm
            continue;
        }

        printf("=============== Sort Users By Name ===============\n");
        switch (choice)
        {
        case 1:
            qsort(accounts, totalAccounts, sizeof(Account), compareAscending);
            saveToFile();
            break;
        case 2:
            qsort(accounts, totalAccounts, sizeof(Account), compareDescending);
            saveToFile();
            break;
        }

        displayAccounts();
        for (int i = 0; i < totalAccounts; i++)
        {
            showAcc(i);
        }
    } while (choice != 0);
}
int compareAscending(const void *a, const void *b)
{
    printf("Successfully sorted\n");
    return strcmp(((Account *)a)->name, ((Account *)b)->name);
}
int compareDescending(const void *a, const void *b)
{
    printf("Successfully sorted\n");
    return strcmp(((Account *)b)->name, ((Account *)a)->name);
}

int findIndexByID(const char *ID)
{
    for (int i = 0; i < totalAccounts; i++)
    {
        if (strcmp(accounts[i].ID, ID) == 0)
        {
            return i;
        }
    }
    return -1; // Không tìm thấy
}

// Hàm xử lý khóa/mở tài khoản
void showLockUser()
{
    char ID[20];
    printf("Input ID: ");
    scanf("%19s", ID);
    int index = findIndexByID(ID);
    if (index == -1)
    {
        printf("ID not found!\n");
        return;
    }
    displayAccounts();
    showAcc(index);
    // Kiểm tra trạng thái và xác nhận
    if (strcmp(accounts[index].status, "open") == 0)
    {
        printf("The account is currently open. Confirm LOCK? (1: Yes, 0: No): ");
    }
    else
    {
        printf("The account is locked. Confirm UNLOCK? (1: Yes, 0: No): ");
    }
    int confirm;
    scanf("%d", &confirm);
    if (confirm == 1)
    {
        // Đảo ngược trạng thái
        if (strcmp(accounts[index].status, "open") == 0)
        {
            strcpy(accounts[index].status, "locked");
        }
        else
        {
            strcpy(accounts[index].status, "open");
        }
        saveToFile();
        printf("Status updated successfully.!\n");
    }
    else
    {
        printf("Invalid.\n"); // khong hop le
    }
}
void findAccountByID(Account accounts[], int size, const char *ID)
{
    int found = 0;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(accounts[i].ID, ID) == 0)
        {
            displayAccounts();
            showAcc(i);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Id not found: %s\n", ID);
    }
}
void editUserInfo() {
    char ID[20];
    printf("Enter user ID to edit: ");
    scanf("%19s", ID);
    while(getchar() != '\n'); // Xóa bộ đệm

    int index = findIndexByID(ID);
    if (index == -1) {
        printf("User not found!\n");
        return;
    }

    // Hiển thị thông tin hiện tại
    printf("\nCurrent information:\n");
    displayAccounts();
    showAcc(index);

    Account *acc = &accounts[index];
    int choice;
    do {
        printf("\nSelect field to edit:\n");
        printf("[1] Name\n");
        printf("[2] Phone number\n");
        printf("[3] Email\n");
        printf("[0] Finish editing\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n'); // Xóa bộ đệm

        switch(choice) {
            case 1: {
                do {
                    printf("Enter new name: ");
                    fgets(acc->name, sizeof(acc->name), stdin);
                    acc->name[strcspn(acc->name, "\n")] = '\0';
                    
                    if(strlen(acc->name) == 0) {
                        printf("Name cannot be empty!\n");
                    } else {
                        break;
                    }
                } while(1);
                break;
            }
            
            case 2: {
                do {
                    printf("Enter new phone number: ");
                    fgets(acc->numberPhone, sizeof(acc->numberPhone), stdin);
                    acc->numberPhone[strcspn(acc->numberPhone, "\n")] = '\0';
                    
                    if(!isValidPhone(acc->numberPhone)) {
                        printf("Invalid phone number! Must be 10-14 digits.\n");
                    } else if(isPhoneExists(acc->numberPhone) && strcmp(acc->numberPhone, accounts[index].numberPhone) != 0) {
                        printf("Phone number already exists!\n");
                    } else {
                        break;
                    }
                } while(1);
                break;
            }
            
            case 3: {
                do {
                    printf("Enter new email: ");
                    fgets(acc->email, sizeof(acc->email), stdin);
                    acc->email[strcspn(acc->email, "\n")] = '\0';
                    
                    if(!isValidEmail(acc->email)) {
                        printf("Invalid email format!\n");
                    } else if(isEmailExists(acc->email) && strcmp(acc->email, accounts[index].email) != 0) {
                        printf("Email already exists!\n");
                    } else {
                        break;
                    }
                } while(1);
                break;
            }
            
            case 0:
                printf("Exiting edit mode...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 0);

    saveToFile();
    printf("User information updated successfully!\n");
}