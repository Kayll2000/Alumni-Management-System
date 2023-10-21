/**
* @function:校友系统注册登录子模块 
* @version:v1
* @author:chenjunlong
* @description:Design and test the registration and login program for the alumni system
* @github:
* @date:2023.03.31
* @lmodauthor:chenjunlong
* @lmoddate:2023.04.04

                        FUNCTION:
                                1、校友和管理员登录功能
                                2、管理员注册校友账户功能
                                3、管理员查看校友列表
                                4、管理员添加校友信息
                                5、管理员修改校友信息
                                6、管理员删除校友信息
                                7、校友修改个人信息
                                8、校友查看其他校友信息
                        BUGFIX:NULL
                        MODIFY:
                                1、增加system("pause")和sytem("cls")界面刷新部分

*
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Alumni {
private:
    string name;        //姓名
    string student_id;  //学号
    string password;    //密码
    string gender;      //性别
    string birthdate;   //出生日期
    string phone;       //联系电话
    string email;       //电子邮件
public:
    Alumni(string name, string student_id, string password, string gender, string birthdate, string phone, string email) {
        this->name = name;
        this->student_id = student_id;
        this->password = password;
        this->gender = gender;
        this->birthdate = birthdate;
        this->phone = phone;
        this->email = email;
    }
    string getName() {
        return name;
    }
    string getStudentId() {
        return student_id;
    }
    string getPassword() {
        return password;
    }
    string getGender() {
        return gender;
    }
    string getBirthdate() {
        return birthdate;
    }
    string getPhone() {
        return phone;
    }
    string getEmail() {
        return email;
    }
    void setPassword(string password) {
        this->password = password;
    }
    void setPhone(string phone) {
        this->phone = phone;
    }
    void setEmail(string email) {
        this->email = email;
    }
};

class AlumniManager {
private:
    vector<Alumni> alumni_list;  //校友列表
public:
    AlumniManager() {}
    void addAlumni(Alumni alumni) {
        alumni_list.push_back(alumni);
    }
    bool login(string student_id, string password) {
        for (int i = 0; i < alumni_list.size(); i++) {
            if (alumni_list[i].getStudentId() == student_id && alumni_list[i].getPassword() == password) {
                return true;
            }
        }
        return false;
    }
    Alumni* getAlumni(string student_id) {
        for (int i = 0; i < alumni_list.size(); i++) {
            if (alumni_list[i].getStudentId() == student_id) {
                return &alumni_list[i];
            }
        }
        return NULL;
    }
    vector<Alumni> getAlumniList() {
        return alumni_list;
    }
    void modifyAlumni(Alumni alumni) {
        for (int i = 0; i < alumni_list.size(); i++) {
            if (alumni_list[i].getStudentId() == alumni.getStudentId()) {
                alumni_list[i] = alumni;
                break;
            }
        }
    }
    void deleteAlumni(string student_id) {
        for (int i = 0; i < alumni_list.size(); i++) {
            if (alumni_list[i].getStudentId() == student_id) {
                alumni_list.erase(alumni_list.begin() + i);
                break;
            }
        }
    }
};

class Admin {
private:
    string username;  //管理员账号
    string password;  //管理员密码
public:
    Admin(string username, string password) {
        this->username = username;
        this->password = password;
    }
    string getUsername() {
        return username;
    }
    bool login(string username, string password) {
        return this->username == username && this->password == password;
    }
};

class AdminManager {
private:
    vector<Admin> admin_list;  //管理员列表
public:
    AdminManager() {}
    void addAdmin(Admin admin) {
        admin_list.push_back(admin);
    }
    bool login(string username, string password) {
        for (int i = 0; i < admin_list.size(); i++) {
            if (admin_list[i].login(username, password)) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    AlumniManager alumni_manager;
    AdminManager admin_manager;
    Admin admin("admin", "admin");
    admin_manager.addAdmin(admin);
    while (true) {
        cout << "请选择登录身份：" << endl;
        cout << "1. 校友" << endl;
        cout << "2. 管理员" << endl;
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "请输入学号和密码：" << endl;
            string student_id, password;
            cin >> student_id >> password;
            if (alumni_manager.login(student_id, password)) {
                while (true) {
                    Alumni* alumni = alumni_manager.getAlumni(student_id);
                    cout << "欢迎您，" << alumni->getName() << "！" << endl;
                    cout << "请选择操作：" << endl;
                    cout << "1. 修改个人信息" << endl;
                    cout << "2. 查看其他校友信息" << endl;
                    cout << "3. 退出登录" << endl;
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
                    else if (choice == 3) {
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
                    cout << "1. 查看校友列表" << endl;
                    cout << "2. 添加校友信息" << endl;
                    cout << "3. 修改校友信息" << endl;
                    cout << "4. 删除校友信息" << endl;
                    cout << "5. 退出登录" << endl;
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
                    else if (choice == 5) {
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