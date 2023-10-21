/****************************************************************************************************************************
* @function:校友管理系统注册登录子函数
* @version:v1.5
* @author:chenjunlong
* @description:Realize the registration and login of alumni information and the login of administrators.
* @github:https://github.com/Kayll2000/Alumni-Management-System.git
* @date:2023.04.06
* @lmodauthor:chenjunlong
* @lmoddate:2023.10.21
*           FUCTION:
                    1、校友登录入口
                    2、管理员登录入口&注册校友信息
            BUGFIX: 1、修复了当使用新闻或者问卷功能保存信息时，即Debug文件夹已经创建情况下，不会创建AlumniData文件夹来保存校友信息的bug。
                    2、[2023.05.10]修复问卷收集答案异常的bug。
            MODIFY:
                    1、[2023.04.10]添加在菜单和问卷界面时主动退出当前菜单的选项
                    2、[2023.04.11]增加校友信息保存功能
                    3、[2023.04.28]优化代码。
                    4、[2023.05.09]优化代码，规范化。
                    5、[2023.05.09]优化在使用新闻和问卷功能时，是否退出信息一直弹出的bug。
                    6、[2023.05.10]优化刷新机制。


****************************************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<algorithm>
#include<io.h>
#include<direct.h>
#include <list>
#include "login.h"
#include "news.h"
#include "question.h"
using namespace std;

Alumni::Alumni(string name, string student_id, string password, string gender, string birthdate, string phone, string email,int flagid) {
    this->name = name;
    this->student_id = student_id;
    this->password = password;
    this->gender = gender;
    this->birthdate = birthdate;
    this->phone = phone;
    this->email = email;
    this->flagid = flagid;
}
string Alumni::GCU_AL_GetName() {
    return name;
}
string Alumni::GCU_AL_GetStudentId() {
    return student_id;
}
string Alumni::GCU_AL_GetPassword() {
    return password;
}
string Alumni::GCU_AL_GetGender() {
    return gender;
}
string Alumni::GCU_AL_GetBirthdate() {
    return birthdate;
}
string Alumni::GCU_AL_GetPhone() {
    return phone;
}
string Alumni::GCU_AL_GetEmail() {
    return email;
}
int Alumni::GCU_AL_GetFlagId() {
    return flagid;
}
void Alumni::GCU_AL_SetPassword(string password) {
    this->password = password;
}
void Alumni::GCU_AL_SetPhone(string phone) {
    this->phone = phone;
}
void Alumni::GCU_AL_SetEmail(string email) {
    this->email = email;
}

void AlumniManager::GCU_ALM_SaveAlumniInfo(void){
    cout <<"正在保存信息···"<< endl;
    if(_access("Debug", 0) == -1)
    {
        _mkdir("Debug");//创建Debug文件夹
    }
    if(_access("Debug/AlumniData", 0) == -1)
    {
        _mkdir("Debug/AlumniData");//创建AlumniData文件夹
    }
    ofstream fo;
    fo.open(ALUMNIFILE,ios::out);
    for(int i=0;i<alumni_list.size();i++)
    {
        fo << "名字：" << alumni_list[i].GCU_AL_GetName() << endl
        << "学号：" << alumni_list[i].GCU_AL_GetStudentId() << endl
        << "密码：" << alumni_list[i].GCU_AL_GetPassword() << endl
        << "性别：" << alumni_list[i].GCU_AL_GetGender() << endl
        << "生日：" << alumni_list[i].GCU_AL_GetBirthdate() << endl
        << "电话：" << alumni_list[i].GCU_AL_GetPhone() << endl
        << "邮箱：" << alumni_list[i].GCU_AL_GetEmail() << endl;
    }
    fo.close();
    cout << "请稍后···"  << endl;
    cout << "校友信息保存成功！" << endl;

}
void AlumniManager::GCU_ALM_AddAlumni(Alumni alumni) {
        alumni_list.push_back(alumni);
        GCU_ALM_SaveAlumniInfo();
    }
bool AlumniManager::login(string student_id, string password) {
for (int i = 0; i < alumni_list.size(); i++) {
    if (alumni_list[i].GCU_AL_GetStudentId() == student_id && alumni_list[i].GCU_AL_GetPassword() == password) {
        return true;
        }
    }
    return false;
}
Alumni* AlumniManager::GCU_ALM_GetAlumni(string student_id){
    for (int i = 0; i < alumni_list.size(); i++) {
        if (alumni_list[i].GCU_AL_GetStudentId() == student_id) {
            return &alumni_list[i];
        }
    }
    return NULL;
}
vector<Alumni> AlumniManager::GCU_ALM_GetAlumniList() {
    return alumni_list;
}
void AlumniManager::GCU_ALM_ModifyAlumni(Alumni alumni) {
    for (int i = 0; i < alumni_list.size(); i++) {
        if (alumni_list[i].GCU_AL_GetStudentId() == alumni.GCU_AL_GetStudentId()) {
            alumni_list[i] = alumni;
            break;
        }
    }
    GCU_ALM_SaveAlumniInfo();
}
void AlumniManager::GCU_ALM_DeleteAlumni(string student_id) {
    for (int i = 0; i < alumni_list.size(); i++) {
        if (alumni_list[i].GCU_AL_GetStudentId() == student_id) {
            alumni_list.erase(alumni_list.begin() + i);
            break;
        }
    }
    GCU_ALM_SaveAlumniInfo();
}
bool AdminManager::login(string username, string password) {
    for (int i = 0; i < admin_list.size(); i++) {
        if (admin_list[i].login(username, password)) {
            return true;
        }
    }
    return false;
}
void AdminManager::GCU_ADM_AddAdmin(Admin admin) {
    admin_list.push_back(admin);
}
void AdminManager::GCU_ADM_NewsFun()
{
    int select = 0;
    bool quit = false;
    string exitflag = "";
        //Flag:
        while(true)
        {
            gm.GCU_News_ShowMenu();
            cout  << "input your select:" << endl;
            cin >> select;
            while(cin.fail())//解决 当输入的select非数字时导致程序奔溃
            {
                cin.clear();//清除cin的错误信息
                cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
                cout << "请输入整数: ";
                cin.ignore();//EOF位置，接收下一个cin函数
                cin >> select;
            }
            switch(select)
            {
                case 0:
                    system("cls");
                    break;
                case 1:
                    gm.GCU_NewsOp_Add();
                    break;
                case 2:
                    gm.GCU_NewsOp_Del();
                    break;
                case 3:
                    gm.GCU_NewsOp_Mod();
                    break;
                case 4:
                    gm.GCU_NewsOp_Find();
                    break;
                case 5:
                    gm.GCU_News_ShowInfo();
                    break;
                case 6:
                    quit = true;
                    break;
                default:
                    GCU_ATError();
                    //system("cls");
                    break;
            }
            if(quit == true)
            {
                cout << "是否退出当前新闻(News)菜单[Y/N]" << endl;
                cin >> exitflag;
                if(exitflag == "Y" || exitflag == "y"){
                    system("pause");
                    system("cls");
                    break;
                 }else{
                        quit = false;
                        system("cls");
                 }
            }
        }
}
void AdminManager::GCU_ADM_QuestionFun()
{
    int myflag;
    bool quit = false;
    string exitflag = "";
    var.qsize = 0;//初始化为 0
    //vat.asize = 0;
    vac.csize = 0;//cs
    while(true)
    {
    GCU_ShowQuestion_Menu();
    cout << "输入您的选择 :" << endl;
    cin >> myflag;
    while(cin.fail())//解决 当输入的myflag非数字时导致程序奔溃
    {
        cin.clear();//清除cin的错误信息
        cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
        cout<<"请输入整数: ";
        cin.ignore();//EOF位置，接收下一个cin函数
        cin >> myflag;
    }

    switch(myflag)
    {
        case 1:GCU_QuestionOp_ADD(&var);break;//增加问卷
        case 2:GCU_QuestionOp_DEL(&var);break;//删除指定问卷
        case 3:GCU_QuestionOp_MOD(&var);break;//修改指定问卷
        case 4:GCU_QuestionOp_Search(&var);break;//查询问卷
        case 5:GCU_ShowQuestio_ALL(&var);break;//显示所有问卷
        case 6:GCU_ShowQuestion_Published(&var);break;//显示已经发布的问卷
        case 7:GCU_QuestionOp_Publish(&var);break;//发布问卷
        case 8:GCU_CollectAnswer_Admin(&vac);break;//GCU_CollectAnswer_Admin();break;//收集问卷答案【在校友角色中去调用问卷填写并将答案存在answer结构体中】
        #if SYS_1
        case 9:GCU_Temp();break;//GCU_AnswerQuestion_User(&var,&vat);break;
        case 10:GCU_ClearQuestion_Published(&var);break;//清空已经发布的额问卷
        case 11:GCU_ClearQuestion_ALL(&var);break;//清空所有问卷
        case 12:system("cls");break;//清屏操作
        case 13:quit = true;break;//退出当前菜单
        #elif SYS_2
        case 9:quit = true;break;//退出当前菜单
        #else
            #error SYS宏未打开
        #endif
        default:GCU_ATError();break;//清屏操作
    }
    if(quit == true){
        cout << "是否退出当前问卷(Question)菜单[Y/N]" << endl;
        cin >> exitflag;
        if(exitflag == "Y" || exitflag == "y"){
            system("pause");
            system("cls");
            break;
        }else{
            quit = false;
            system("cls");
        }
    }
    }
}
void AdminManager::GCU_ADM_AnswerQuestion_User(int tempid,string name)
{
    int t_id = tempid;
    string t_name = name;
    GCU_AnswerQuestion_User(&var,&vac,t_id,t_name);
    //system("pause");
    //system("cls");
}
void AdminManager::GCU_ADM_ViewNews_User()
{
    gm.GCU_News_ShowInfo();
    // system("pause");
    // system("cls");
}

Admin::Admin(string username, string password) {
    this->username = username;
    this->password = password;
}
string Admin::GCU_AD_GetUsername() {
    return username;
}
bool Admin::login(string username, string password) {
    return this->username == username && this->password == password;
}
