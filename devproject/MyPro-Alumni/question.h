#ifndef QUESTION_H
#define QUESTION_H
// "news.h"
#include <string>
#include <vector>
#include "global.h"

using namespace std;
//全局变量


struct Questionnaire
{
    int id;
    string title;         // 问卷标题
    vector<string> items; // 问卷选项
    //vector<int> results;  // 选项结果
};

struct QArray
{
    Questionnaire qarray[MAX_QUESTION_NUM];//所有问卷
    Questionnaire parray[MAX_QUESTION_NUM];//已发布问卷
    int qsize;
};

struct Answer
{
    string stus;  //填写人
    //Questionnaire answerarr[MAX_QUESTION_NUM];//答案   这里如果不注释掉，就会邮箱stus的push_back
    vector<int> results;  // 选项结果
    int asize;
};

struct Collect
{
    Answer collectarr[20];//每个校友 后改宏 设置20个校友为上限
    int csize;
};

extern int IsidExit(QArray *var,int id);
extern int Ispublish(QArray *var,int id);
extern void GCU_ShowQuestion_Menu(void);
extern void GCU_ShowQuestio_ALL(QArray *var);
extern void GCU_SaveAnswer_Info(Collect *vac ,QArray *var,int temp,string name);
extern void GCU_SaveQuestion_Info(QArray *var);
extern void GCU_ClearQuestion_ALL(QArray *var);
extern void GCU_ClearQuestion_Published(QArray *var);
extern void GCU_QuestionOp_Publish(QArray *var);
extern void GCU_QuestionOp_ADD(QArray *var);
extern void GCU_QuestionOp_DEL(QArray *var);
extern void GCU_QuestionOp_MOD(QArray *var);
extern void GCU_QuestionOp_Search(QArray *var);
extern void GCU_ShowQuestion_Published(QArray *var);
extern void GCU_AnswerQuestion_User(QArray *var,Collect *vac,int temp,string name) ;//用户回答问卷
extern void GCU_CollectAnswer_Admin(Collect *vac);
extern void GCU_Test(void);
extern void GCU_Temp(void);
extern void GCU_ATError(void);


#endif