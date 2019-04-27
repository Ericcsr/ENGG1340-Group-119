#include "main.h"

int main()
{
//================================INIT_Process==========================================
    int new_flag = 1;
    Menu main_menu("Main menu",5,WIDTH);
    Menu continue_menu("Continue ?",2,WIDTH);
    string main_choices[5] = {"1. Business Words","2. Physics Words","3. Sport Words","4. Reset all procedure","5. Exit"};
    string continue_choices[2] = {"1. I want to continue last process.","2. I don't want to continue last process."};
    main_menu.setMenuChoices(main_choices);             // Created the main menu
    continue_menu.setMenuChoices(continue_choices);     //Created the menu asking you whether or not to continue the last process
    //Check which file has been opened using check.txt
    if(!check_file(file_condition))
        return 0;
    else
    {
       int cmd_main;
//============================Below is a loop=========================================
       while(1)
       {
        main_menu.menuPrint();
        cout<<"Your Choice: ";
        cin>>cmd_main;
        cout<<'\n'<<'\n'<<'\n'<<'\n'<<endl;
        switch (cmd_main)
        {
            case 1://Use choose word list 1
            if(file_condition[0]==0) //User hasn't opened the list
            {
                Kernel kernel_one(1,"1",0);
                file_condition[0] = 1;
                reset_check_file(4,file_condition);//This is set the record of checkfile
                kernel_one.kernel_run();
            }
            else                     //User has opened the list
            {   continue_menu.menuPrint();
                cout<<"Your Choice: ";
                cin>>cmd_main;
                cout<<'\n'<<'\n'<<'\n'<<'\n'<<endl;
                if(cmd_main==1)      //User DON'T want to start a new process
                {
                    Kernel kernel_one(1,"1",1);
                    kernel_one.kernel_run();
                }
                else                 //User want to start a new process
                {
                    Kernel kernel_one(1,"1",0);
                    kernel_one.kernel_run();
                }
            }
            break;                   //User choose list 2
            case 2:
            if(file_condition[1]==0)
            {
                Kernel kernel_two(2,"2",0);
                file_condition[1] = 1;
                reset_check_file(4,file_condition);
                kernel_two.kernel_run();
            }
            else
            {   continue_menu.menuPrint();
                cout<<"Your Choice: ";
                cin>>cmd_main;
                cout<<'\n'<<'\n'<<'\n'<<'\n'<<endl;
                if(cmd_main==1)
                {
                    Kernel kernel_two(2,"2",1);
                    kernel_two.kernel_run();
                }
                else
                {
                    Kernel kernel_two(2,"2",0);
                    kernel_two.kernel_run();
                }
            }
            break;
            case 3:                  //User choose list 3
            if(file_condition[2]==0)
            {
                Kernel kernel_three(3,"3",0);
                file_condition[2] = 1;
                reset_check_file(4,file_condition);
                kernel_three.kernel_run();
            }
            else
            {   continue_menu.menuPrint();
                cout<<"Your Choice: ";
                cin>>cmd_main;
                cout<<'\n'<<'\n'<<'\n'<<'\n'<<endl;
                if(cmd_main==1)
                {
                    Kernel kernel_three(3,"3",1);
                    kernel_three.kernel_run();
                }
                else
                {
                    Kernel kernel_three(3,"3",0);
                    kernel_three.kernel_run();
                }
            }
            break;
            case 4:                  //Reset all learning procedure
                reset_check_file(3,file_condition);
                for(int i=0;i<3;i++)
                {
                  file_condition[i] = 0; //All reset to 0
                }
                break;
            case 5:                  //Exit
                return 0;
        }
       }
    }
}
