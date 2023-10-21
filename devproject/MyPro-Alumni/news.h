#ifndef NEWS_H
#define NEWS_H
// "news.h"
#include <string>
#include <vector>
#include "global.h"
using namespace std;

class News {//新闻类
public:
    News(int _id,string _title,string _content,string _date,string _author);
    int id;//新闻编号
    string title;//新闻标题
    string content;//新闻内容
    string author;//新闻作者
    string date;//新闻日期
    void News_display();//发布
};

class GM//admin
{
public:
    GM();
    int IDIsExist(int id);
    void GCU_News_ShowMenu();       //显示新闻菜单
    void GCU_NewsOp_Add();       //增加新闻信息
    void GCU_NewsOp_Del();        //删除新闻信息
    void GCU_NewsOp_Mod();        //修改新闻信息
    void GCU_NewsOp_Find();       //查询指定编号的新闻信息
    void GCU_News_ShowInfo();       //显示新闻内容
    void GCU_News_SaveInfo();       //输出新闻信息到文件
    vector<News*> *News_Array;
    ~GM();
};

#endif