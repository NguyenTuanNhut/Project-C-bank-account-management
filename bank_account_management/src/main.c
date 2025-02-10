#include<stdio.h>
#include<string.h>
#include"function.c"
#include"../include/datatype.h"
int main()
{
    loadFromFile(); // Đọc dữ liệu từ file khi khởi động
    int choiceRole,choiceMenu;
   do{
    showRole();
    scanf("%d",&choiceRole);
    switch (choiceRole)
    {
    case 1:
       showLogin();
       do{
        showUserManagement();
        scanf("%d",&choiceMenu);
        switch(choiceMenu)
        {
            case 1:
            addAccount();
            break;
            case 2:
            displayAccounts();
            break;
            
           default:
           printf("Incorrect choice");
           break;
    }
        

       }while(choiceMenu!=0);

        
    break;

    default:
    printf("Incorrect choice");
        break;
    }
   }while(choiceRole!=0);
  

    return 0;
}