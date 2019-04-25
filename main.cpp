#include "main.h"

int main()
{
    int new_flag = 1;
    menu main_menu("Main menu",5,WIDTH);
    menu continue_menu("Continue ?",2,WIDTH);
    string main_choices[3] = {"1. Business Words","2. Physics Words","3. Computer Science Words","4. Reset all procedure","4. Exit"};
    string continue_choices[2] = {"1. I want to continue last process.","2. I don't want to continue last process."};
    main_menu.setMenuChoices(main_choices);             // Created the main menu
    continue_menu.setMenuChoices(continue_choices);     //Created the menu asking you whether or not to continue last process
    //Check which file has been opened using a check file
    if(!check_file(files_condition))
        return 0;
    else
    {
       int cmd_main;
       while(1)
       {
        main_menu.menuPrint();
        cout<<"Your Choice: "<<endl;
        flag: cin<<cmd_main;
        
        switch cmd_main
        {
            case 1:
            if(files_condition[0]==0)
            {
                kernel kernel_one(1,"1",0);
                kernel_one.kernel_run();
            }
            else
            {   continue_menu.menuPrint();
                cout<<"Your Choice: ";
                cin<<cmd_main;
                if(cmd_main==1)
                {
                    kernel kernel_one(1,"1",1);
                    kernel_one.kernel_run();
                }
                else
                {
                    kernel kernel_one(1,"1",0);
                    kernel_one.kernel_run();
                }
            }
            break;
            case 2:
            if(files_condition[1]==0)
            {
                kernel kernel_two(2,"2",0);
                kernel_two.kernel_run();
            }
            else
            {   continue_menu.menuPrint();
                cout<<"Your Choice: ";
                cin<<cmd_main;
                if(cmd_main==1)
                {
                    kernel kernel_two(2,"2",1);
                    kernel_two.kernel_run();
                }
                else
                {
                    kernel kernel_two(2,"2",0);
                    kernel_two.kernel_run();
                }
            }
            break;
            case 3:
            if(files_condition[2]==0)
            {
                kernel kernel_three(3,"3",0);
                kernel_three.kernel_run();
            }
            else
            {   continue_menu.menuPrint();
                cout<<"Your Choice: ";
                cin<<cmd_main;
                if(cmd_main==1)
                {
                    kernel kernel_three(3,"3",1);
                    kernel_three.kernel_run();
                }
                else
                {
                    kernel kernel_three(3,"3",0);
                    kernel_three.kernel_run();
                }
            }
            break;
            case 4:
                reset_check_file(3,files_condition);
                break;
            case 5:
                return;
        }
       }
    }
    
}