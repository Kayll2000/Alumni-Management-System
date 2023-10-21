/****************************************************************************************************************************
* @function:校友管理系统主函数
* @version:v1.0.1
* @author:chenjunlong
* @description:By calling other modules, the main functions are achieved.
* @github:https://github.com/Kayll2000/Alumni-Management-System.git
* @date:2023.04.06
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
            MODIFY:[2023.04.24]增加主函数登录界面输入的容错性，优化主界面，优化UI。

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
//#include "news.h"
#include "login.h"
//#include "question.h"

using namespace std;
//int main(int argc, char** argv)
int main() 
{

    AlumniManager alumni_manager;
    AdminManager admin_manager;

    Admin admin("admin", "1024");//管理员登录账号及密码
    admin_manager.addAdmin(admin);

    while (true) {
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        cout << ">>> 请选择登录身份 >>>" << endl;
        cout << ">>> 1. 校友 >>>"  << endl;
        cout << ">>> 2. 管理员 >>>" << endl;
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
                    Alumni* alumni = alumni_manager.getAlumni(student_id);
                    cout << "欢迎您，" << alumni->getName() << "！" << endl;
                    cout << "请选择操作：" << endl;
                    cout << "[1] 修改个人信息" << endl;
                    cout << "[2] 查看其他校友信息" << endl;
                    cout << "[3] 填写问卷" << endl;
                    cout << "[4] 查看新闻" << endl;
                    cout << "[5] 退出登录" << endl;
                    cin >> choice;
                    if (choice == 1) {
                        cout << "请输入新密码、联系电话和电子邮件：" << endl;
                        string new_password, phone, email;
                        cin >> new_password >> phone >> email;
                        alumni->setPassword(new_password);
                        alumni->setPhone(phone);
                        alumni->setEmail(email);
                        alumni_manager.modifyAlumni(*alumni);
                        cout << "修改成功！" << endl;
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 2) {
                        vector<Alumni> alumni_list = alumni_manager.getAlumniList();
                        for (int i = 0; i < alumni_list.size(); i++) {
                            if (alumni_list[i].getStudentId() != student_id) {
                                cout << "姓名：" << alumni_list[i].getName() << endl;
                                cout << "学号：" << alumni_list[i].getStudentId() << endl;
                                cout << "性别：" << alumni_list[i].getGender() << endl;
                                cout << "出生日期：" << alumni_list[i].getBirthdate() << endl;
                                cout << "联系电话：" << alumni_list[i].getPhone() << endl;
                                cout << "电子邮件：" << alumni_list[i].getEmail() << endl;
                                cout << endl;
                            }
                        }
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 3){
                        //alumni_manager.answerquestion(&var,&vat);//校友回答问卷
                        admin_manager.alumni_answerquestion();
                    }
                    else if (choice == 4){
                        //alumni_manager.viewnews(gm);//校友查看新闻
                        admin_manager.alumni_viewnews();
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
                    cout << "[1] 查看校友列表" << endl;
                    cout << "[2] 添加校友信息" << endl;
                    cout << "[3] 修改校友信息" << endl;
                    cout << "[4] 删除校友信息" << endl;
                    cout << "[5] 新闻功能" << endl;
                    cout << "[6] 问卷功能" << endl;
                    cout << "[7] 退出登录" << endl;
                    cin >> choice;
                    if (choice == 1) {
                        vector<Alumni> alumni_list = alumni_manager.getAlumniList();
                        for (int i = 0; i < alumni_list.size(); i++) {
                            cout << "姓名：" << alumni_list[i].getName() << endl;
                            cout << "学号：" << alumni_list[i].getStudentId() << endl;
                            cout << "性别：" << alumni_list[i].getGender() << endl;
                            cout << "出生日期：" << alumni_list[i].getBirthdate() << endl;
                            cout << "联系电话：" << alumni_list[i].getPhone() << endl;
                            cout << "电子邮件：" << alumni_list[i].getEmail() << endl;
                            cout << endl;
                        }
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 2) {
                        cout << "请输入新增校友的姓名、学号、密码、性别、出生日期、联系电话和电子邮件：" << endl;
                        string name, student_id, password, gender, birthdate, phone, email;
                        cin >> name >> student_id >> password >> gender >> birthdate >> phone >> email;
                        Alumni alumni(name, student_id, password, gender, birthdate, phone, email);
                        alumni_manager.addAlumni(alumni);
                        cout << "添加成功！" << endl;
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 3) {
                        cout << "请输入要修改的校友学号：" << endl;
                        string student_id;
                        cin >> student_id;
                        Alumni* alumni = alumni_manager.getAlumni(student_id);
                        if (alumni == NULL) {
                            cout << "校友不存在，请重新输入！" << endl;
                            system("pause");
                            system("cls");
                        }
                        else {
                            cout << "请输入新密码、联系电话和电子邮件：" << endl;
                            string new_password, phone, email;
                            cin >> new_password >> phone >> email;
                            alumni->setPassword(new_password);
                            alumni->setPhone(phone);
                            alumni->setEmail(email);
                            alumni_manager.modifyAlumni(*alumni);
                            cout << "修改成功！" << endl;
                            system("pause");
                            system("cls");
                        }
                    }
                    else if (choice == 4) {
                        cout << "请输入要删除的校友学号：" << endl;
                        string student_id;
                        cin >> student_id;
                        alumni_manager.deleteAlumni(student_id);
                        cout << "删除成功！" << endl;
                        system("pause");
                        system("cls");
                    }
                    else if(choice == 5){
                        //if(admin_manager.Newsfun() == -1){
                        // system("pause");
                        // system("cls");
                        //goto here;
                           // cout << "test " << endl;
                       // }
                        admin_manager.Newsfun();//新闻功能
                    }
                    else if(choice == 6){
                        admin_manager.questionfun();//问卷功能
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
        else {
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
        }
    }
    return 0;
}