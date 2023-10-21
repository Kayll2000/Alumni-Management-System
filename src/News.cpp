/****************************************************************************************************************************
* @function:校友管理系统新闻功能子函数
* @version:v1.0.1
* @author:chenjunlong
* @description:Implement the news editing and publishing functions of the system.
* @github:https://github.com/Kayll2000/Alumni-Management-System.git
* @date:2023.04.06
* @lmodauthor:chenjunlong
* @lmoddate:2023.10.21
*           FUCTION:
                    1、添加新闻
                    2、删除新闻
                    3、修改新闻
                    4、查询新闻
                    5、发布新闻
                    6、新闻信息保存到指定文件夹，输出文本文件
            BUGFIX:
                    1、[2023.04.11]修复新闻信息保存的文件夹创建错误的bug。
                    2、[2023.04.24]修复当使用问卷后再使用新闻功能时，即创建了Debug文件夹后，新闻功能将不会创建对应的文件夹NewsData的bug。
            MODIFY:
                    1、[2023.04.10]修改菜单界面函数。
                    2、[2023.04.24]优化UI。

****************************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include<io.h>
#include<direct.h>
#include <cstdlib>
#include "news.h"
using namespace std;

News::News(int _id,string _title,string _content,string _date,string _author)
{
    this->id = _id;
    this->title = _title;
    this->content = _content;
    this->author = _author;
    this->date = _date;
}

void News::News_display()
{
    //cout << "test display!" << endl;
    cout <<"新闻编号："<<(this -> id)<<"\n新闻标题："
    <<this -> title<<"\n新闻内容："
    <<this -> content<<"\n新闻作者："<< this->author << "\n新闻日期：" << this->date <<endl;
    cout << endl;
}

GM::GM()//构造函数
{
    this -> News_Array = new vector<News*>;
}

GM::~GM()//析构函数
{
    if(this -> News_Array)//容器非空
    {
        this -> News_Array -> clear();
        delete[] this -> News_Array;
        this -> News_Array = NULL;//删除后，让对象指针指向空，防止悬空
    }
}

void GM::Show_menu()
{
    cout <<"-----------------------------------------------------------"<< endl;
    cout <<"----------------------欢迎使用新闻发布功能------------------"<< endl;
    cout <<"---------------------[0] 清屏-------------------------------"<< endl;
    cout <<"---------------------[1] 增加新闻信息-----------------------"<< endl;
    cout <<"---------------------[2] 删除新闻信息------------------------"<< endl;
    cout <<"---------------------[3] 修改新闻信息------------------------"<< endl;
    cout <<"---------------------[4] 查询新闻信息-----------------------"<< endl;
    cout <<"---------------------[5] 发布所有新闻信息-------------------"<< endl;
    cout <<"---------------------[6] 退出当前新闻菜单-------------------"<< endl;
    cout <<"-----------------------------------------------------------"<< endl;
    cout << endl;
}

void GM::Save_Info()//保存新闻信息API
{

    cout <<"正在保存信息···"<< endl;
    if(_access("Debug", 0) == -1)
    {
        _mkdir("Debug");//创建Debug文件夹
    }
    if(_access("Debug/NewsData", 0) == -1)
    {
        _mkdir("Debug/NewsData");//创建AlumniData文件夹
    }
    //写入到文件

    ofstream fo;
    /*
    at 用于获得指定字符
    string str;
    cin>>str;  //str=="12345"
    char ch;
    ch = str.at(0);
    cout<<ch;   //ch=='1';
    */
    fo.open(FILENAME,ios::out);//允许输出(写入操作)到流。
    for(int i = 0;i < this -> News_Array -> size();++i)
    {
        /*
        fo << "新闻ID[" << this -> News_Array -> at(i) -> id << "]" << endl
        << "新闻Title:" <<this -> News_Array -> at(i) -> title << endl
        << "新闻Content:" << this -> News_Array -> at(i) -> content <<endl
        << "Author:" << this -> News_Array-> at(i) -> author <<endl
        << "Date" << this -> News_Array-> at(i) -> date << endl;
        */
        fo << "新闻ID[" << this -> News_Array -> at(i) -> id << "]" << endl
        << "新闻标题：" <<this -> News_Array -> at(i) -> title << endl
        << "新闻内容：" << this -> News_Array -> at(i) -> content <<endl
        << "作者：" << this -> News_Array-> at(i) -> author <<endl
        << "日期：" << this -> News_Array-> at(i) -> date << endl;

    }
    fo.close();
    cout << "保存成功！" << endl;
}

int GM::IDIsExist(int id)
{
    int _len = this -> News_Array -> size();//获取news信息容器存放的数量
    int index = -1;
    //int _id = id - 1;
    for(int i = 0; i < _len; ++i)//遍历容器
    {
        if(this -> News_Array -> at(i) -> id == id)
        {
            index = i;
            break;
        }
    }
    return index;//index = -1说明该编号不存在
}

void GM::News_add()
{
    while(true)
    {
        //针对string类型，getline可以接收空格，遇到回车键结束
        int choice,_id;
        string flag;
        char ch;//吃掉回车
        string _title,_content,_date,_author;
        _id = newsnum+1;
        cin.get(ch);//吃掉回车\n
        cout << "input title: " << endl;
        getline(cin,_title);
        cout << "input content " << endl;
        getline(cin,_content);
        cout << "input date " << endl;
        getline(cin,_date);
        cout << "input author " << endl;
        getline(cin,_author);

        News *pnews = NULL;
        pnews = new News(_id,_title,_content,_date,_author);
        this->News_Array -> push_back(pnews);//存进容器array中
        newsnum++;
        //cout << "size :" << this->News_Array ->size() << endl;
        cout << "新闻添加成功！" << endl;
        cout << "是否继续添加？[Y/N] " << endl;
        while(true)
        {
            cin >> flag;
            if(flag == "Y" || flag == "y" || flag == "N" || flag == "n")
            {
                break;
            }else{
                cout << "输入指令错误，请重新输入！" << endl;
            }
        }

        if(flag == "Y" || flag == "y")
        {
            cout << "继续添加第" << newsnum + 1 << "条新闻 >>>" << endl;
        }else{
            break;
        }
    }
    this -> Save_Info();//保存信息
    system("pause");
    system("cls");

}

void GM::News_del()
{
    int de_id;
    cout << "输入需要删除的id：" << endl;
    cin >> de_id;
    int index = this -> IDIsExist(de_id);
    if(index != -1)
    {
    this -> News_Array -> erase(this -> News_Array -> begin()+index);
    cout <<"删除成功！"<< endl;
    }else{
    cout <<"新闻信息不存在，删除失败！"<< endl;
    }
    this -> Save_Info();//保存信息
    system("pause");
    system("cls");
}

void GM::News_mod()
{
    int mod_id;
    cout << "输入要修改的id： " << endl;
    cin >> mod_id;
    int index = IDIsExist(mod_id);
    if(IDIsExist(mod_id) != -1)
    {
        News *_pnews = NULL;
        int newid;
        string newtitle;
        string newcontent;
        string newauthor;
        string newdate;
        cout <<"input id: " << endl;
        cin >> newid;
        cout << "input new title: " << endl;
        cin >> newtitle;
        cout << "input new content " << endl;
        cin >> newcontent;
        cout << "input new date " << endl;
        cin >> newdate;
        cout << "input new author " << endl;
        cin >> newauthor;
        _pnews = new  News(newid,newtitle,newcontent,newdate,newauthor);
        this -> News_Array -> at(index) = _pnews;
    }
    this -> Save_Info();//保存信息
    system("pause");
    system("cls");
}

void GM::News_find()
{
    cout <<"输入需要查询的新闻编号："<< endl;
    int find_id;
    cin >> find_id;
    int index = IDIsExist(find_id);
    if(index != -1)
    {
        cout <<"查询成功，该条新闻信息如下 >>>"<< endl;
        this -> News_Array -> at(index) -> News_display();//显示信息
    }else{
        cout <<"ERROR!查无此条新闻！"<< endl;
    }
    system("pause");
    system("cls");
}

void GM::News_show()
{
    if(newsnum != 0){
        cout <<"新闻条数为：" << this -> News_Array -> size() << "条！" << endl;
        //cout <<"新闻条数为：" << newsnum << endl; //这个也可以显示新闻条数
        for(int i = 0;i < this ->News_Array -> size();++i)
        {
            this -> News_Array -> at(i) ->News_display();
        }
    }else{
        cout << "目前暂无新闻！>>>" << endl;
    }
    system("pause");
    system("cls");
}
