/****************************************************************************************************************************
* @function:校友管理系统注册登录子函数
* @version:v1.0.1
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
            MODIFY:
                    1、[2023.04.10]添加在菜单和问卷界面时主动退出当前菜单的选项
                    2、[2023.04.11]增加校友信息保存功能

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

Alumni::Alumni(string name, string student_id, string password, string gender, string birthdate, string phone, string email) {
    this->name = name;
    this->student_id = student_id;
    this->password = password;
    this->gender = gender;
    this->birthdate = birthdate;
    this->phone = phone;
    this->email = email;
}
string Alumni::getName() {
    return name;
}
string Alumni::getStudentId() {
    return student_id;
}
string Alumni::getPassword() {
    return password;
}
string Alumni::getGender() {
    return gender;
}
string Alumni::getBirthdate() {
    return birthdate;
}
string Alumni::getPhone() {
    return phone;
}
string Alumni::getEmail() {
    return email;
}

void Alumni::setPassword(string password) {
    this->password = password;
}
void Alumni::setPhone(string phone) {
    this->phone = phone;
}
void Alumni::setEmail(string email) {
    this->email = email;
}
void AlumniManager::savealumniinfo(void){
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
        fo << "名字：" << alumni_list[i].getName() << endl
        << "学号：" << alumni_list[i].getStudentId() << endl
        << "密码：" << alumni_list[i].getPassword() << endl
        << "性别：" << alumni_list[i].getGender() << endl
        << "生日：" << alumni_list[i].getBirthdate() << endl
        << "电话：" << alumni_list[i].getPhone() << endl
        << "邮箱：" << alumni_list[i].getEmail() << endl;
    }
    fo.close();
    cout << "请稍后···"  << endl;
    cout << "校友信息保存成功！" << endl;

}

void AlumniManager::addAlumni(Alumni alumni) {
        alumni_list.push_back(alumni);
        savealumniinfo();
    }
bool AlumniManager::login(string student_id, string password) {
for (int i = 0; i < alumni_list.size(); i++) {
    if (alumni_list[i].getStudentId() == student_id && alumni_list[i].getPassword() == password) {
        return true;
        }
    }
    return false;
}

Alumni* AlumniManager::getAlumni(string student_id){
    for (int i = 0; i < alumni_list.size(); i++) {
        if (alumni_list[i].getStudentId() == student_id) {
            return &alumni_list[i];
        }
    }
    return NULL;
}

vector<Alumni> AlumniManager::getAlumniList() {
    return alumni_list;
}

void AlumniManager::modifyAlumni(Alumni alumni) {
    for (int i = 0; i < alumni_list.size(); i++) {
        if (alumni_list[i].getStudentId() == alumni.getStudentId()) {
            alumni_list[i] = alumni;
            break;
        }
    }
    savealumniinfo();
}

void AlumniManager::deleteAlumni(string student_id) {
    for (int i = 0; i < alumni_list.size(); i++) {
        if (alumni_list[i].getStudentId() == student_id) {
            alumni_list.erase(alumni_list.begin() + i);
            break;
        }
    }
    savealumniinfo();
}

Admin::Admin(string username, string password) {
    this->username = username;
    this->password = password;
}

string Admin::getUsername() {
    return username;
}

bool Admin::login(string username, string password) {
    return this->username == username && this->password == password;
}

bool AdminManager::login(string username, string password) {
    for (int i = 0; i < admin_list.size(); i++) {
        if (admin_list[i].login(username, password)) {
            return true;
        }
    }
    return false;
}

void AdminManager::addAdmin(Admin admin) {
    admin_list.push_back(admin);
}

void AdminManager::Newsfun()
{
    int select = 0;
    bool quit = false;
    string exitflag = "";
        //Flag:
        while(true)
        {
            gm.Show_menu();
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
                    gm.News_add();
                    break;
                case 2:
                    gm.News_del();
                    break;
                case 3:
                    gm.News_mod();
                    break;
                case 4:
                    gm.News_find();
                    break;
                case 5:
                    gm.News_show();
                    break;
                default:
                    system("cls");
                    break;
            }
            if(quit != false)
            {
                system("pause");
                system("cls");
                break;
            }else{
                cout << "是否退出当前新闻(News)菜单[Y/N]" << endl;
                cin >> exitflag;
                if(exitflag == "Y" || exitflag == "y"){

                    system("pause");
                    system("cls");
                    break;
                 }
            }
        }
}

void AdminManager::questionfun()
{
    int myflag;
    bool quit = false;
    string exitflag = "";
    var.qsize = 0;//初始化为 0
    vat.asize = 0;
    while(true)
    {
    showquestionmenu();
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
        case 1:addquestion(&var);break;//增加问卷
        case 2:delquestion(&var);break;//删除指定问卷
        case 3:modquestion(&var);break;//修改指定问卷
        case 4:searchquestion(&var);break;
        case 5:showquestion(&var);break;//显示所有问卷
        case 6:showpublish(&var);break;//显示已经发布的问卷
        case 7:publish(&var);break;//发布问卷
        case 8:collectanswer(&vat);break;//collectanswer();break;//收集问卷答案【在校友角色中去调用问卷填写并将答案存在answer结构体中】
        case 9:useranswer(&var,&vat);break;
        case 10:clearpublished(&var);break;//清空已经发布的额问卷
        case 11:clearallquestion(&var);break;//清空所有问卷
        case 12:system("cls");break;//清屏操作
        default:system("cls");break;//清屏操作
    }
    if(quit != false)
    {
        system("pause");
        system("cls");
        break;

    }else{
        cout << "是否退出当前问卷(Question)菜单[Y/N]" << endl;
        cin >> exitflag;
        if(exitflag == "Y" || exitflag == "y"){
            system("pause");
            system("cls");
            break;
        }
    }
    }
}

void AdminManager::alumni_answerquestion()
{
    useranswer(&var,&vat);
    system("pause");
    system("cls");
}
void AdminManager::alumni_viewnews()
{
    gm.News_show();
    system("pause");
    system("cls");
}
