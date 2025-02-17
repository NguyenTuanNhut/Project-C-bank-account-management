#include <stdio.h>
#include <string.h>
#include "function.c"
#include "../include/datatype.h"

int main()
{
    loadFromFile(); // Đọc dữ liệu từ file khi khởi động
    int choiceRole, choiceMenu;

    do
    {
        showRole();
        printf("Chose: ");
        scanf("%d", &choiceRole);
        while (getchar() != '\n')
            ;
        clearScreen();
        switch (choiceRole)
        {

        case 1:

            adminLogin();

            do
            {
                clearScreen();
                showUserManagement();
                scanf("%d", &choiceMenu);
                switch (choiceMenu)
                {
                case 1:
                    clearScreen();
                    showMenuAdd();
                    break;
                case 2:
                    displayAccounts();
                    for (int i = 0; i < totalAccounts; i++)
                    {
                        showAcc(i);
                    }
                    printf("Press any key to continue..");
                    system("pause");

                    break;
                case 3:
                    clearScreen();
                    showLockUser();

                    break;
                case 4:
                    showMenuFind();
                    break;
                case 5:
                    sortUsersByName();
                    break;
                    // Trong phần xử lý menu Admin
                case 6:
                    clearScreen();
                    editUserInfo();
                    printf("Press any key to continue..");
                    system("pause");
                    break;
                default:
                    printf("Incorrect choice\n");
                    printf("Press any key to continue..");
                    system("pause");
                    break;
                }

            } while (choiceMenu != 0);
            break;

        default:
            printf("Incorrect choice\n");
            break;
        case 2:
            loginUser();
            clearScreen();
            showMenuUser();
            break;
        }
    } while (choiceRole != 0);

    return 0;
}
