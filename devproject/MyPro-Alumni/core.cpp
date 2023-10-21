/****************************************************************************************************************************
* @function:校友管理系统核心函数
* @version:v1.5
* @author:chenjunlong
* @description:Encapsulated core function.
* @github:https://github.com/Kayll2000/Alumni-Management-System.git
* @date:2023.05.08
* @lmodauthor:chenjunlong
* @lmoddate:2023.10.21
* @compile:Compile the environment is Dev-C++(Embarcadero Dev-C++)
*           FUCTION:
                    1、校友登录
                        	1.1 修改个人信息
	                        1.2 查看其他校友信息
	                        1.3 填写问卷
	                        1.4 查看新闻
	                        1.5 退出登录
                    2、管理员登录
                    	    2.1 查看校友列表
	                        2.2 添加校友信息
	                        2.3 修改校友信息
	                        2.4 删除校友信息
	                        2.5 新闻功能
	                        2.6 问卷功能
	                        2.7 退出登录
            BUGFIX:
                   [2023.05.10]修复问卷功能异常的bug。
                   [2023.05.11]修复了在校友查看其他校友信息时，信息存在情况下仍然打印出“暂无信息”的bug。
            MODIFY:[2023.04.24]增加主函数登录界面输入的容错性，优化主界面，优化UI。
                   [2023.05.08]封装核心函数。
                   [2023.05.08]增加无校友信息时的提醒。
                   [2023.05.09]优化代码，规范化。
                   [2023.05.11]增加退出系统功能选项。
                   [2023.05.12]增加UI界面的逐字输出功能。
                   [2023.05.12]增加系统退出时的的逐字问候语功能，设置开关宏对部分功能进行分离。
                   [2023.05.12]加入输入1024后的隐藏功能。
                   [2023.05.12]加入多线程随机打印字符串功能。
                   [2023.05.15]去除多线程功能。
        

*
****************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <io.h>
#include<direct.h> 
#include <list>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "login.h"
#include "core.h"

using namespace std;

// void GCU_Core(AlumniManager _alumni_manager,AdminManager _admin_manager,Admin _admin)
void GCU_Core()
{
    AlumniManager alumni_manager;
    AdminManager admin_manager;
    Admin admin("admin", "1024");//管理员登录账号及密码
    admin_manager.GCU_ADM_AddAdmin(admin);

    while (true) {
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        GCU_PrintWord();
        cout << ">>> 请选择登录身份 >>>" << endl;
        cout << ">>> 1. 校友 >>>"  << endl;
        cout << ">>> 2. 管理员 >>>" << endl;
        cout << ">>> 3. 退出系统 >>>" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        int choice;
        cin >> choice;
        while(cin.fail())//解决 当输入的choice非数字时导致程序奔溃
        {
            cin.clear();//清除cin的错误信息
            cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
            cout << "请输入整数: \t";
            cin.ignore();//EOF位置，接收下一个cin函数
            cin >> choice;
        }
        if (choice == 1) {
            cout << "请输入学号和密码：" << endl;
            string student_id, password;
            cin >> student_id >> password;
            if (alumni_manager.login(student_id, password)) {
                while (true) {
                    Alumni* alumni = alumni_manager.GCU_ALM_GetAlumni(student_id);
                    cout << "欢迎您，" << alumni->GCU_AL_GetName() << "！" << endl;
                    cout << "请选择操作：" << endl;
                    cout << "\t\t\t\t[1] 修改个人信息" << endl;
                    cout << "\t\t\t\t[2] 查看其他校友信息" << endl;
                    cout << "\t\t\t\t[3] 填写问卷" << endl;
                    cout << "\t\t\t\t[4] 查看新闻" << endl;
                    cout << "\t\t\t\t[5] 退出登录" << endl;
                    cin >> choice;
                    if (choice == 1) {
                        cout << "请输入新密码、联系电话和电子邮件：" << endl;
                        string new_password, phone, email;
                        cin >> new_password >> phone >> email;
                        alumni->GCU_AL_SetPassword(new_password);
                        alumni->GCU_AL_SetPhone(phone);
                        alumni->GCU_AL_SetEmail(email);
                        alumni_manager.GCU_ALM_ModifyAlumni(*alumni);
                        cout << "修改成功！" << endl;
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 2) {
                        vector<Alumni> alumni_list = alumni_manager.GCU_ALM_GetAlumniList();
                        if(alumni_list.size() == 1)
                        {
                            cout << "暂无信息！" << endl;
                        }
                        for (int i = 0; i < alumni_list.size(); i++) {
                            if (alumni_list[i].GCU_AL_GetStudentId() != student_id) {
                                cout << "姓名：" << alumni_list[i].GCU_AL_GetName() << endl;
                                cout << "学号：" << alumni_list[i].GCU_AL_GetStudentId() << endl;
                                cout << "性别：" << alumni_list[i].GCU_AL_GetGender() << endl;
                                cout << "出生日期：" << alumni_list[i].GCU_AL_GetBirthdate() << endl;
                                cout << "联系电话：" << alumni_list[i].GCU_AL_GetPhone() << endl;
                                cout << "电子邮件：" << alumni_list[i].GCU_AL_GetEmail() << endl;
                                cout << endl;
                            }//else{
                            //     cout << "暂无信息！" << endl;
                            // }
                        }
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 3){
                        int tid = alumni->GCU_AL_GetFlagId();
                        string tname = alumni->GCU_AL_GetName();
                        admin_manager.GCU_ADM_AnswerQuestion_User(tid,tname);
                    }
                    else if (choice == 4){
                        admin_manager.GCU_ADM_ViewNews_User();
                    }
                    else if (choice == 5) {
                        system("pause");
                        system("cls");
                        break;
                    }
                    else {
                        cout << "输入有误，请重新输入！" << endl;
                        // system("pause");
                        // system("cls");
                    }
                }
            }
            else {
                cout << "学号或密码错误，请重新输入！" << endl;
                system("pause");
                system("cls");
            }
        }
        else if (choice == 2) {
            cout << "请输入管理员账号和密码：" << endl;
            string username, password;
            cin >> username >> password;
            
            if (admin_manager.login(username, password)) {
                while (true) {
                    cout << "请选择操作：" << endl;
                    cout << "\t\t\t\t[1] 查看校友列表" << endl;
                    cout << "\t\t\t\t[2] 添加校友信息" << endl;
                    cout << "\t\t\t\t[3] 修改校友信息" << endl;
                    cout << "\t\t\t\t[4] 删除校友信息" << endl;
                    cout << "\t\t\t\t[5] 新闻功能" << endl;
                    cout << "\t\t\t\t[6] 问卷功能" << endl;
                    cout << "\t\t\t\t[7] 退出登录" << endl;
                    cin >> choice;
                    if (choice == 1) {
                        vector<Alumni> alumni_list = alumni_manager.GCU_ALM_GetAlumniList();
                        if(alumni_list.size() != 0)
                        {
                            for (int i = 0; i < alumni_list.size(); i++) {
                            //cout << "flag id:" <<  alumni_list[i].GCU_AL_GetFlagId() << endl;//debug
                            cout << "姓名：" << alumni_list[i].GCU_AL_GetName() << endl;
                            cout << "学号：" << alumni_list[i].GCU_AL_GetStudentId() << endl;
                            cout << "性别：" << alumni_list[i].GCU_AL_GetGender() << endl;
                            cout << "出生日期：" << alumni_list[i].GCU_AL_GetBirthdate() << endl;
                            cout << "联系电话：" << alumni_list[i].GCU_AL_GetPhone() << endl;
                            cout << "电子邮件：" << alumni_list[i].GCU_AL_GetEmail() << endl;
                            cout << endl;
                            }
                        }else{
                            cout << "暂无信息！"  << endl;
                        }

                        system("pause");
                        system("cls");
                    }
                    else if (choice == 2) {
                        cout << "请输入新增校友的姓名、学号、密码、性别、出生日期、联系电话和电子邮件：" << endl;
                        string name, student_id, password, gender, birthdate, phone, email;
                        cin >> name >> student_id >> password >> gender >> birthdate >> phone >> email;
                        Alumni alumni(name, student_id, password, gender, birthdate, phone, email,stuid);
                        alumni_manager.GCU_ALM_AddAlumni(alumni);
                        stuid++;
                        cout << "添加成功！" << endl;
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 3) {
                        cout << "请输入要修改的校友学号：" << endl;
                        string student_id;
                        cin >> student_id;
                        Alumni* alumni = alumni_manager.GCU_ALM_GetAlumni(student_id);
                        if (alumni == NULL) {
                            cout << "校友不存在，请重新输入！" << endl;
                            system("pause");
                            system("cls");
                        }
                        else {
                            cout << "请输入新密码、联系电话和电子邮件：" << endl;
                            string new_password, phone, email;
                            cin >> new_password >> phone >> email;
                            alumni->GCU_AL_SetPassword(new_password);
                            alumni->GCU_AL_SetPhone(phone);
                            alumni->GCU_AL_SetEmail(email);
                            alumni_manager.GCU_ALM_ModifyAlumni(*alumni);
                            cout << "修改成功！" << endl;
                            system("pause");
                            system("cls");
                        }
                    }
                    else if (choice == 4) {
                        cout << "请输入要删除的校友学号：" << endl;
                        string student_id;
                        cin >> student_id;
                        alumni_manager.GCU_ALM_DeleteAlumni(student_id);
                        stuid--;
                        cout << "删除成功！" << endl;
                        system("pause");
                        system("cls");
                    }
                    else if(choice == 5){
                        //if(admin_manager.GCU_ADM_NewsFun() == -1){
                        // system("pause");
                        // system("cls");
                        //goto here;
                           // cout << "test " << endl;
                       // }
                       system("cls");
                        admin_manager.GCU_ADM_NewsFun();//新闻功能
                    }
                    else if(choice == 6){
                        system("cls");
                        admin_manager.GCU_ADM_QuestionFun();//问卷功能
                    }
                    else if (choice == 7) {
                        system("pause");
                        system("cls");
                        break;
                    }                    
                    else {
                        cout << "输入有误，请重新输入！" << endl;
                        system("pause");
                        system("cls");
                    }
                }
            }
            else {
                cout << "管理员账号或密码错误，请重新输入！" << endl;
                system("pause");
                system("cls");
            }
        }
        else if (choice == 3) {
            #if SYS_PRINT
            GCU_Quit();
            #else
            cout << "感谢您的使用！" << endl;
            #endif
            exit(0);
        }
        else if (choice == 1024) {
            cout << "进入开发者模式！" << endl;
            string mychoice;
            while(true)
            {
                do {
                    cout << "这是个测试模式，输入256退出！" << endl;
                    cin >> mychoice;
                    if (!GCU_IsNumeric(mychoice)) {
                        cout << "输入不合法，请重新输入！" << endl;
                    }
                } while (!GCU_IsNumeric(mychoice));

                if(mychoice == "256")
                {
                    #if SYS_PRINT
                    GCU_Quit();
                    #endif
                    exit(0);
                }
            }
        }
        else {
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
        }
    }   
}

// 逐字输出文字
void GCU_PrintCharByChar(string s, int delay) {
    for (int i = 0; i < s.size(); i++) {
        cout << s[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delay)); // 延时
    }
}

//初始化
void GCU_Init(void)
{
    string s = "欢迎使用GCU校友管理系统!";
    int delay = 100; // 每个字符输出后延时的时间（单位为毫秒）
    GCU_PrintCharByChar(s, delay);
    cout << endl;
}

//退出问候语
void GCU_Quit(void)
{
    string s = "感谢您的使用，期待您的下一次使用，系统即将退出!";
    int delay = 100; // 每个字符输出后延时的时间（单位为毫秒）
    GCU_PrintCharByChar(s, delay);
    cout << endl;
    cout << "系统已退出,使用请重新运行程序！" << endl;
}
//输入数字合法检测API
bool GCU_IsNumeric(string str) {
    bool numeric = true;
    for (int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            numeric = false;
            break;
        }
    }
    return numeric;
}

//随机打印字符串
void GCU_PrintWord(void)
{
    //string arr[] = {"Hello", "World", "Good", "Morning", "Night", "Bye"};
    string arr[] = {"坚持不懈，你会取得成功。", 
                    "珍惜当下，每一天都是宝贵的礼物。", 
                    "保持积极心态，生活便会更加美好", 
                    "让自己快乐起来，幸福源于内心。", 
                    "越努力，越幸运，把握机会，迎接美好未来。",
                    "与人为善，让世界充满爱和温暖。"};
    int size = sizeof(arr) / sizeof(arr[0]);
    srand(time(nullptr));
    /*
    while (true) {
        int randomIndex = rand() % size;
        cout << arr[randomIndex] << endl;
        this_thread::sleep_for(chrono::seconds(3)); // 暂停 3 秒钟
    }
    */
    int randomIndex = rand() % size;
    cout << arr[randomIndex] << endl;

}