#ifndef GLOBAL_H
#define GLOBAL_H

#define SYS_1 false //去掉一些功能前
#define SYS_2 true  //去掉一些功能后
#define SYS_PRINT true  //是否开启“逐字输出”功能
#define DEBUG false
#define CLC false

#define MAX_QUESTION_NUM 100 //最多的问卷数
#define MAXITEM 10//最多的选项个数
#define QUEFILENAME "./Debug/QuestionData/QuestionFILE.txt"//保存问卷信息的路径
#define ANSWERFILE "./Debug/AnswerData/AnswerFILE.txt"//保存问卷回答的答案
#define NEWSFILE "./Debug/NewsData/NewsFILE.txt"    //保存新闻数据的路径
#define ALUMNIFILE "./Debug/AlumniData/AlumniFILE.txt"    //保存校友数据的路径

extern int newsnum;//记录新闻条数
extern int questionallnum;// 记录所有问卷的数量
extern int questionpublishnum;//记录已经发布问卷的数量
extern int answerflag[MAX_QUESTION_NUM];//记录已经填写的问卷个数
extern int answersave[MAX_QUESTION_NUM];//记录已经填写的问卷个数
extern int stuid;//校友id标识
// extern bool runningflag;//执行的flag

#endif
