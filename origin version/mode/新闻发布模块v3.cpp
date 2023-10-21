/***********************************************************************************************
* @function:新闻发布子模块 
* @version:v3
* @author:chenjunlong
* @description:Programming the news release sub module program and testing its functionality
* @github:
* @date:2023.04.01
* @lmodauthor:chenjunlong
* @lmoddate:2023.04.04
*
*                       FUNCTION:
                                    1、新闻信息的添加
                                    2、新闻信息的删除
                                    3、新闻信息的修改
                                    4、新闻信息的查询
                                    5、新闻信息的发布
                        BUGFIX:
                            1、去除自定义的ID，改为系统自定义新闻编号（ID）
                        MODIFY:
                            1、增加显示所有新闻API
                            2、增加交互界面输入的合法检测
                            3、增加新闻信息写入到特定文件夹中的特定txt文件功能
* 
*
***********************************************************************************************/
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include<io.h>
#include<direct.h> 
using namespace std;

#define FILENAME "./NewsData/NewsFILE.txt"    //保存为TXT文本格式

int num = 0;//记录新闻条数

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

class GM//admin
{
public:
    GM();
    int IDIsExist(int id);
    void Show_menu();
    void News_add();
    void News_del();
    void News_mod();
    void News_find();
    void News_show();
    void Save_Info();       //输出新闻信息到文件
    vector<News*> *News_Array;
    ~GM();
};

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
    cout <<"---------------------0、清屏-------------------------------"<< endl;
    cout <<"---------------------1、增加新闻信息-----------------------"<< endl;
    cout <<"---------------------2、删除新闻信息------------------------"<< endl;
    cout <<"---------------------3、修改新闻信息------------------------"<< endl;
    cout <<"---------------------4、查询新闻信息-----------------------"<< endl; 
    cout <<"---------------------5、发布所有新闻信息-------------------"<< endl; 
    cout <<"-----------------------------------------------------------"<< endl;
    cout << endl;
}

void GM::Save_Info()//保存新闻信息API
{

    cout <<"正在保存信息···"<< endl;
    
    if(_access("NewsData", 0) == -1)  
    {   
        _mkdir("NewsData");//创建文件夹
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
        fo << "ID:" << this -> News_Array -> at(i) -> id << endl
        << "Title:" <<this -> News_Array -> at(i) -> title << endl
        << "Content:" << this -> News_Array -> at(i) -> content <<endl
        << "Author:" << this -> News_Array-> at(i) -> author <<endl
        << "Date" << this -> News_Array-> at(i) -> date << endl;
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
        _id = num+1;
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
        num++;
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
            cout << "继续添加第" << num + 1 << "条新闻 >>>" << endl;
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
        cout <<"查询成功，该条新闻信息如下："<< endl;
        this -> News_Array -> at(index) -> News_display();//显示信息
    }else{
        cout <<"查无此条新闻！"<< endl;
    }
    system("pause");
    system("cls");
}

void GM::News_show()
{
    cout <<"新闻条数为：" << this -> News_Array -> size() << endl;
    //cout <<"新闻条数为：" << num << endl; //这个也可以显示新闻条数
    for(int i = 0;i < this ->News_Array -> size();++i)
    {
        this -> News_Array -> at(i) ->News_display();
    }
    system("pause");
    system("cls");
}

int main()
{
    GM gm;//实例化管理员
    int select;
while(true)
{
    gm.Show_menu();
    cout  << "input your select:" << endl;
    cin >> select;
    while(cin.fail())//解决 当输入的select非数字时导致程序奔溃
    {
        cin.clear();//清除cin的错误信息
        cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
        cout<<"请输入整数: ";
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
}
    return 0;
}