#ifndef LOGIN_H
#define LOGIN_H

#include "news.h"
#include "question.h"
#include <string>
#include <vector>
using namespace std;

//"login.h"
//校友信息
class Alumni {
private:
    int flagid;//id标识
    string name;        //姓名
    string student_id;  //学号
    string password;    //密码
    string gender;      //性别
    string birthdate;   //出生日期
    string phone;       //联系电话
    string email;       //电子邮件
public:
    Alumni(string name, string student_id, string password, string gender, string birthdate, string phone, string email,int flagid);
    string GCU_AL_GetName();
    string GCU_AL_GetStudentId();
    string GCU_AL_GetPassword();
    string GCU_AL_GetGender();
    string GCU_AL_GetBirthdate();
    string GCU_AL_GetPhone();
    string GCU_AL_GetEmail();
    int GCU_AL_GetFlagId();

    void GCU_AL_SetPassword(string password);
    void GCU_AL_SetPhone(string phone);
    void GCU_AL_SetEmail(string email);

};

//管理员对校友信息的操作
class AlumniManager {
private:
    vector<Alumni> alumni_list;  //校友列表
public:
    AlumniManager(){};
    bool login(string student_id, string password);
    Alumni* GCU_ALM_GetAlumni(string student_id);
    vector<Alumni> GCU_ALM_GetAlumniList();

    void GCU_ALM_AddAlumni(Alumni alumni);
    void GCU_ALM_ModifyAlumni(Alumni alumni);
    void GCU_ALM_DeleteAlumni(string student_id);
    void GCU_ALM_SaveAlumniInfo();
};

class Admin {
private:
    string username;  //管理员账号
    string password;  //管理员密码
public:
    Admin(string username, string password);
    string GCU_AD_GetUsername();
    bool login(string username, string password);
};

class AdminManager {
private:
    vector<Admin> admin_list;  //管理员列表
public:
    //AdminManager() {}
    GM gm;
    QArray var;//实例化问卷对象
    //Answer vat;//实例化答案对象
    Collect vac;//实例化校友答案列表
    AdminManager():gm() {}
    void GCU_ADM_AddAdmin(Admin admin);
    bool login(string username, string password);
    void GCU_ADM_NewsFun();
    void GCU_ADM_QuestionFun();
    void GCU_ADM_AnswerQuestion_User(int tempid,string name);
    void GCU_ADM_ViewNews_User();
};

#endif