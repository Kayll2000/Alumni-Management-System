#ifndef QUESTION_H
#define QUESTION_H
// "news.h"
#include <string>
#include <vector>
#define MAX 100 //最多的问卷数
#define MAXITEM 10//最多的选项个数
#define QUEFILENAME "./Debug/QuestionData/QuestionFILE.txt"//保存问卷信息的路径
#define ANSWERFILE "./Debug/AnswerData/AnswerFILE.txt"
using namespace std;
//全局变量
static int num = 0;// 记录所有问卷的数量
static int pnum = 0;//记录已经发布问卷的数量
static int answerflag = 0;//记录已经填写的问卷个数

struct Questionnaire
{
    int id;
    string title;         // 问卷标题
    vector<string> items; // 问卷选项
    //vector<int> results;  // 选项结果
};

struct QArray
{
    Questionnaire qarray[MAX];//所有问卷
    Questionnaire parray[MAX];//已发布问卷
    int qsize;
};

struct Answer
{
    Questionnaire answerarr[MAX];//答案
    vector<int> results;  // 选项结果
    int asize;
    // string content;//填写问卷答案内容
};

extern void showquestionmenu();
extern void showquestion(QArray *var);
extern int IsidExit(QArray *var,int id);
extern int Ispublish(QArray *var,int id);
extern void saveanswerinfo(Answer *vat ,QArray *var);
extern void saveinfo(QArray *var);
extern void clearallquestion(QArray *var);
extern void clearpublished(QArray *var);
extern void publish(QArray *var);
extern void addquestion(QArray *var);
extern void delquestion(QArray *var);
extern void modquestion(QArray *var);
extern void showpublish(QArray *var);
extern void useranswer(QArray *var,Answer *vat);
extern void collectanswer(Answer *vat);
extern void searchquestion(QArray *var);
extern void test();

#endif