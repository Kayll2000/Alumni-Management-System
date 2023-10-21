/****************************************************************************
* @function:(校友管理)系统集成
* @version:v1.0
* @author:chenjunlong
* @description:System integration and testing
* @github:
* @date:2023.04.04
* @lmodauthor:chenjunlong
* @lmoddate:2023.04.06
*
                    FUCTION:Alumni Management System
                    BUGFIX:[2023.04.06] 修复在管理员登入后选则进入新闻功能然后退出新闻功能后程序奔溃的bug，在AdminManager类中实例化GM类的对象时，需要在AdminManager的构造函数中初始化GM类的对象.
                           [2023.04.06] 修复在校友登入后问卷填写和新闻查看功能异常的bug.
                    MODIFY:[2023.04.06] 将注册登录功能和新闻功能合并到一起.
                           [2023.04.06] 添加问卷功能到系统中并测试.
                           [2023.04.06] 在校友功能中，添加问卷填写功能和新闻查看功能并测试.
                    BUG:
                        1、[2023.04.04] 管理员登入 --> 选择选项6 --> 退出News --> 程序退出 （读到了野指针，导致内存泄漏，程序返回3221225477）
                        2、[2023.04.06] 校友登入 --> 选择填写问卷 --> 问卷发布了但没有链接到 --> 填写失败（因为一开始把问卷填写的API放在alumni_manager的成员函数中，而此时在alumni_manager类中就重新构造了一个问卷类GM）
                        3、[2023.04,06] 校友登入 --> 选择查看新闻 --> 新闻已发布但查看不到，没有链接到 --> 查看失败（也是把新闻查看的API放在了alumni_manager的成员函数中，而此时的alumni_manager类中重新构造了一个新闻类News）
            
*****************************************************************************/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<algorithm>
#include<io.h>
#include<direct.h> 
#include <list>

#define MAX 100 //最多的问卷数
#define MAXITEM 10//最多的选项个数
#define FILENAME "./NewsData/NewsFILE.txt"    //新闻信息 保存为TXT文本格式
#define QUEFILENAME "./QuestionData/QuestionFILE.txt"//问卷信息 保存问卷信息的路径
#define ANSWERFILE "./AnswerData/AnswerFILE.txt"//问卷答案信息
//全局变量
int newsnum = 0;//记录新闻条数
int num = 0;// 记录所有问卷的数量
int pnum = 0;//记录已经发布问卷的数量
int answerflag = 0;//记录已经填写的问卷个数

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
    if(newsnum != 0)
    {
        cout <<"新闻编号："<<(this -> id)<<"\n新闻标题："
        <<this -> title<<"\n新闻内容："
        <<this -> content<<"\n新闻作者："<< this->author << "\n新闻日期：" << this->date <<endl;
        cout << endl;
    }else{
        cout << "目前暂无新闻！" << endl;
    }
}

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

void showquestionmenu()
{
    cout << "********************************************************" << endl;
    cout << "******************《问卷发布子系统》*********************" << endl;
    cout << "******************1、增加问卷***************************" << endl;//ok
    cout << "******************2、删除问卷***************************" << endl;//ok
    cout << "******************3、修改问卷***************************" << endl;//ok
    cout << "******************4、显示所有问卷***********************" << endl;//ok
    cout << "******************5、显示已经发布的问卷******************" << endl;//ok
    cout << "******************6、发布问卷***************************" << endl;//ok
    cout << "******************7、收集问卷答案***********************" << endl;//ok
    cout << "******************8、填写问卷***************************" << endl;//ok
    cout << "******************9、清空已经发布的问卷******************" << endl;//ok
    cout << "******************10、清空所有问卷***********************" << endl;//ok
    cout << "******************11、清屏*******************************" << endl;//ok
    cout << "********************************************************" << endl;
}

void showquestion(QArray *var)//显示所有问卷及选项
{
    //cout <<"qsize = " <<var->qsize << endl;//debug
    cout << endl;
    cout << "《所有问卷》" << endl;
    for(int i = 0;i<var->qsize;i++)
    {
        cout << "问卷编号：" << var->qarray[i].id << endl;
        cout << "问卷标题：" << var->qarray[i].title << endl;
        for(int j=0;j<var->qarray[i].items.size();j++)
        {
            cout << "选项"<<j+1<<"："  << var->qarray[i].items[j] << endl;
        }
        cout << endl;
    }
    system("pause");
    system("cls");
}
int IsidExit(QArray *var,int id)//问卷id是否存在  存在返回id  不存在返回-1
{
    for(int i=0;i<num;i++)
    {
        if(var->qarray[i].id == id)
        {
            //cout << "此问卷编号存在！" << endl;//debug
            return id;
        }else{
            //cout << "此问卷编号不存在！" << endl;
        }
    }
    return -1;
}

int Ispublish(QArray *var,int id)//问卷id是否已经发布  未发布返回id  已经发布返回-1
{
    if(IsidExit(var,id) != -1)//问卷id存在
    {
        for(int i=0;i<num;i++)
        {
            if(var->parray[i].id == id)
            {
                //cout << "问卷编号为"<< id <<"的问卷已经发布！" << endl;//debug
                return -1;
            }else{
                cout << "编号为"<<id<<"的问卷还未发布！"<< endl;
                return id;
            }
        }
    }else{
        cout << "该问卷编号不存在，请先创建！或者" << endl;
    }
    return -1;
}

void saveanswerinfo(Answer *vat ,QArray *var)
{
    cout << "正在保存答案信息···" << endl;
    if(_access("AnswerData", 0) == -1)  
    {   
        _mkdir("AnswerData");//创建文件夹
    }
    ofstream fo;
    fo.open(ANSWERFILE,ios::out);
    for(int i=0;i<answerflag;i++)
    {
        fo << "问卷ID:" << i+1 << endl
        << "问卷标题：" << var->parray[i].title << endl;
        for(int j=0;j<var->parray[i].items.size() ;j++)
        {
            fo << "选项" << j+1 <<": " << var->parray[i].items[j] << endl;
        }

        fo << "问卷答案：" << vat->results[i] << endl;
        fo << endl;
    }
    fo.close();
    cout << "保存成功！" << endl;
}

void saveinfo(QArray *var)
{
    cout <<"正在保存信息···"<< endl;
    
    if(_access("QuestionData", 0) == -1)  
    {   
        _mkdir("QuestionData");//创建文件夹
    }
    ofstream fo;
    fo.open(QUEFILENAME,ios::out);//允许输出(写入操作)到流。
    for(int i = 0;i < num; ++i)
    {
        fo << "问卷ID:" << var ->qarray[i].id << endl
        << "问卷标题：" << var->qarray[i].title << endl;
            for(int j=0;j<var->qarray[i].items.size();j++)
            {
                fo << "选项" << j+1 <<": " << var->qarray[i].items[j] << endl;
            }
            fo << endl;
    }
    fo.close();
    cout << "保存成功！" << endl;
}

void clearallquestion(QArray *var)//清空所有问卷
{
    for(int i = 0 ;i<var->qsize;i++)
    {
        var->qarray[i] = var->qarray[i+1];//把数组所有元素往前移动
    }
    var->qsize = 0;
    num = 0;
    saveinfo(var);
}
void clearpublished(QArray *var)//清空已经发布的问卷
{
    for(int i = 0 ;i<var->qsize;i++)
    {
        var->parray[i] = var->parray[i+1];//把数组所有元素往前移动
    }
    var->qsize = 0;
    pnum = 0;
}

void publish(QArray *var)//发布问卷
{
    vector<string> batarr;
    string flag;
    int index;//发布的索引
    cout << "是否重新发布修改的问卷[Y/N]" << endl;
    while(true){
        cin >> flag;
        if(flag == "Y" ||flag == "y" || flag == "N" ||flag == "n")
        {
            break;
        }else{
            cout << "输入指令不存在！" << endl;
            cout << "请重新输入！" << endl;
        }
    }
    if(flag == "Y" ||flag == "y")
    {
        index = 0;//全部重新发布
        clearpublished(var);
    }else{
        index = pnum;//从全部问卷中发布未发布的问卷
    }
    for(int i = index;i<num;i++)
    {
    batarr =  var->qarray[i].items;
    var->parray[pnum].id = var->qarray[i].id;
    var->parray[pnum].title = var-> qarray[i].title;
    var->parray[pnum].items.swap(batarr);
    cout << "id:" << var->parray[pnum].id << endl;
    cout << "title: " << var-> parray[pnum].title << endl;
    pnum++;
    }
    cout << "问卷发布成功！" << endl;
    system("pause");
    system("cls");
}

void addquestion(QArray *var)
{
    string _Title,flag;
    string _items[MAXITEM];//最多容纳的选项 ——> MAXITEM 个  10个
    int _nums;//_id;
    char ch;
    while(true)
    {
        cin.get(ch);//吃掉回车\n
        var ->qarray[num].id = num+1;//编号从1开始
        cout << "输入问卷标题：" << endl;
        getline(cin,_Title);
        //cin >> _Title;                                            //修复当输入的字符串包含空格时，只接收到第一个空格前的字符的bug
        var->qarray[num].title = _Title;
        cout << "你想要输入几个选项：" << endl;
        cin >> _nums;
        while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
        {
        cin.clear();//清除cin的错误信息
        cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
        cout<<"请输入整数:";
        cin.ignore();//EOF位置，接收下一个cin函数
        cin>>_nums;
        }
        for(int i=0;i<_nums;i++)
        {
        cout << "输入选项"<<i+1<<"：" << endl;
        cin >> _items[i];
        var->qarray[num].items.push_back(_items[i]);
        }
        num++;
        var->qsize++;
        cout << "是否继续添加？[Y/N]" << endl;
        for(;;){
            cin >> flag;
            if(flag == "Y" ||flag == "y" || flag == "N" ||flag == "n")
            {
                break;
            }else{
                cout << "输入指令不存在！" << endl;
                cout << "请重新输入！" << endl;
            }
        }
        if(flag == "Y" ||flag == "y")
        {
            cout << "继续添加第" << num + 1 << "张问卷" << endl;
        }else{
            break;
        }
    }
    saveinfo(var);
    system("pause");
    system("cls");
}

void delquestion(QArray *var)//删除指定问卷
{
    //通过问卷编号删除，此时已经发布或者未发布的问卷都将被删除
    //cout << "删除test！" << endl;
    int del_id;
    cout << "输入你想要删除的问卷编号：" << endl;
    cin >> del_id;
    while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
    {
    cin.clear();//清除cin的错误信息
    cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
    cout<<"请输入正确的问卷编号:";
    cin.ignore();//EOF位置，接收下一个cin函数
    cin>>del_id;
    }
    if(IsidExit(var,del_id) != -1)//id is exit（存在）
    {
        for(int i = del_id - 1;i<var->qsize;i++)
        {
            var->qarray[i] = var->qarray[i+1];//把数组所有元素往前移动
        }
        var->qsize--;
    }
    num = num - 1;
    cout << "问卷ID为" << del_id << "的问卷删除成功！" << endl;
    saveinfo(var);
    system("pause");
    system("cls");
}

void modquestion(QArray *var)
{
    //通过问卷id修改问卷，此时无论发布的还是未发布的问卷都将被修改

    string mod_Title;
    string mod_items[10];//最多容纳的选项 ——> 10个
    int mod_nums,mod_id;
    cout << "输入需要修改的问卷编号：" << endl;
    cin >> mod_id;
    while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
    {
    cin.clear();//清除cin的错误信息
    cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
    cout<<"请输入整数: ";
    cin.ignore();//EOF位置，接收下一个cin函数
    cin >> mod_id;
    }

    if(IsidExit(var,mod_id) != -1)//问卷id存在
    {
        cout << "输入修改后的标题：" << endl;
        cin >> mod_Title;
        var->qarray[mod_id-1].title = mod_Title;
        cout << "输入修改后的选项个数：" << endl;
        cin >> mod_nums;
        var->qarray[mod_id-1].items.clear();//清空原有的，不会回收空间，但size变成0，后续可能有bug
        for(int i=0;i<mod_nums;i++)
        {
        cout << "输入选项"<<i+1<<"：" << endl;
        cin >> mod_items[i];
        var->qarray[mod_id-1].items.push_back(mod_items[i]);
        //var->parray[]
        }
        cout << "修改成功！" << endl;
    }else{
        cout << "问卷id不存在！修改失败！" << endl;
    }
    saveinfo(var);
    system("pause");
    system("cls");
}

void showpublish(QArray *var)
{
    cout << endl;
    if(pnum != 0)
    {
    cout << "《已经发布的问卷》" << endl;
    for(int i = 0;i<pnum;i++)
    {
        cout << "问卷编号：" << var->parray[i].id << endl;
        cout << "问卷标题：" << var->parray[i].title << endl;
        for(int j=0;j<var->parray[i].items.size();j++)
        {
            cout << "选项"<<j+1<<"："  << var->parray[i].items[j] << endl;
        }
        cout << endl;
    }
    }else{
        cout << "还没有发布问卷！" << endl;
    }
    system("pause");
    system("cls");
}
void useranswer(QArray *var,Answer *vat)//用户回答问卷
{
    int myselect,itemsize;
    bool writeflag = false; 

    for(int i = answerflag;i<pnum;i++)
    {
        cout << "问卷编号：" << var->parray[i].id << endl;
        cout << "问卷标题：" << var->parray[i].title << endl;
        for(int j=0;j<var->parray[i].items.size();j++)
        {
            cout << "选项"<<j+1<<"："  << var->parray[i].items[j] << endl;
            itemsize = var->parray[i].items.size();
        }
        cout << "请选择你的答案 >>> " << endl;
        while(true)
        {
            cin >> myselect;
            if(myselect>0 && myselect <= itemsize)
            {
                break;
            }else{
                cout << "选项不存在！" << endl;
            }
        }
        // vat->answerarr[i].results.push_back(myselect);
        vat->results.push_back(myselect);
        vat->asize++;
        answerflag++;
        writeflag = true;
        cout << "写入成功！" << endl;
    }
    if(writeflag != true)
    {
        cout << "问卷已经全部填写完毕！或者 问卷未发布！" << endl;
    }
    saveanswerinfo(vat,var);//保存用户答案 
        system("pause");
        system("cls");

}
void collectanswer(Answer *vat)
{
    cout << "收集问卷答案test!" << endl;
    cout << "问卷填写数量：" << vat->asize << endl;
    for(int i = 0;i < answerflag;i++)
    {
        cout <<"id["<< i+1 <<"] 的问卷答案为：" << vat->results[i] << endl;
    }
    system("pause");
    system("cls");
}
void test()//测试API
{
    cout << "功能未开发！" << endl;
    cout << "详情联系QQ2825363541" << endl;
    system("pause");
    system("cls");
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
    if(newsnum != 0){
        cout <<"新闻条数为：" << this -> News_Array -> size() << endl;
        //cout <<"新闻条数为：" << newsnum << endl; //这个也可以显示新闻条数
        for(int i = 0;i < this ->News_Array -> size();++i)
        {
            this -> News_Array -> at(i) ->News_display();
        }
    }else{
        cout << "目前暂无新闻！" << endl;
    }
    system("pause");
    system("cls");
}

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
    //GM gm;//实例化管理员
    //QArray var;//实例化问卷对象
    //Answer vat;//实例化答案对象
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
    /*
    void answerquestion(QArray var,Answer vat)//回答问卷问题
    {
        useranswer(&var,&vat);
        system("pause");
        system("cls");
    }
    void viewnews(GM gm)
    {
        gm.News_show();
        system("pause");
        system("cls");
    }
    */
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
    GM gm;
    QArray var;//实例化问卷对象
    Answer vat;//实例化答案对象
    AdminManager():gm() {}//解决bug 1
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
    void Newsfun(){
            int select = 0;
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

            cout << "是否退出当前News菜单[Y/N]" << endl;
            cin >> exitflag; 
            if(exitflag == "Y" || exitflag == "y"){
        
                system("pause");
                system("cls");
  
                break;
             }
        }
            }
    void questionfun()
    {
    int myflag;
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
        case 4:showquestion(&var);break;//显示所有问卷
        case 5:showpublish(&var);break;//显示已经发布的问卷
        case 6:publish(&var);break;//发布问卷
        case 7:collectanswer(&vat);break;//collectanswer();break;//收集问卷答案【在校友角色中去调用问卷填写并将答案存在answer结构体中】
        case 8:useranswer(&var,&vat);break;
        case 9:clearpublished(&var);break;//清空已经发布的额问卷
        case 10:clearallquestion(&var);break;//清空所有问卷
        case 11:system("cls");break;//清屏操作
        default:system("cls");break;//清屏操作
    }
    cout << "是否退出当前News菜单[Y/N]" << endl;
    cin >> exitflag; 
    if(exitflag == "Y" || exitflag == "y"){
        system("pause");
        system("cls");
        break;
    }
    }
    }
    void alumni_answerquestion()
    {
        useranswer(&var,&vat);
        system("pause");
        system("cls");
    }
    void alumni_viewnews()
    {
        gm.News_show();
        system("pause");
        system("cls");
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
                    cout << "3. 填写问卷" << endl;
                    cout << "4. 查看新闻" << endl;
                    cout << "5. 退出登录" << endl;
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
                    cout << "1. 查看校友列表" << endl;
                    cout << "2. 添加校友信息" << endl;
                    cout << "3. 修改校友信息" << endl;
                    cout << "4. 删除校友信息" << endl;
                    cout << "5. 新闻功能" << endl;
                    cout << "6. 问卷功能" << endl;
                    cout << "7. 退出登录" << endl;
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