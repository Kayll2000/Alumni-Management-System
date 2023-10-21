/**************************************************************************************************************************************************************
* @function:问卷发布子模块 
* @version:v6
* @author:chenjunlong
* @description:Implement programming and testing functions for the question paper submodule
* @github:
* @date:2023.04.04
* @lmodauthor:chenjunlong
* @lmoddate:2023.04.04
*           FUCTION:
                    1、问卷的产生（增加问卷）
                    2、问卷的删除（指定问卷）
                    3、问卷的修改（指定问卷）
                    4、问卷的查询（包括所有问卷和已经发布的问卷）
                    5、问卷的清空（包括已经发布的或者所有的）
                    6、填写问卷
                    7、收集问卷答案
            BUG:
                1、title:输入有空格的字符串时只会截取第一个空格前的字符；  @bugfix
                2、publish：当发布修改后的问卷时，不会覆盖掉前面的，所以造成了已经发布问卷中本来只有三张，发布后面却变成了六张，需要做的是先清空整个array吧； @bugfix
                3、items:当输入的选项为字符串时，也只会截取第一个字符，不过问题不大； @ not  to do ···
            MODIFY:
                1、增加交互界面输入的合法检测
                2、增加调查问卷信息写入到特定文件夹中的特定txt文件功能
                3、增加将用户填写问卷的结果以及问卷内容输出到指定文件夹的txt文件中的功能
*
*
***************************************************************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<algorithm>
#include<io.h>
#include<direct.h> 
using namespace std;
#define MAX 100 //最多的问卷数
#define MAXITEM 10//最多的选项个数
#define FILENAME "./QuestionData/QuestionFILE.txt"//保存问卷信息的路径
#define ANSWERFILE "./AnswerData/AnswerFILE.txt"

//全局变量
int num = 0;// 记录所有问卷的数量
int pnum = 0;//记录已经发布问卷的数量
int answerflag = 0;//记录已经填写的问卷个数

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

// void publish(QArray *var)//发布指定问卷
// {
//     //cout <<"pnum:" << pnum << endl;//debug
//     int index;
//     vector<string> batarr;
//     cout << "想要发布第几条问卷：" << endl;
//     cin >> index;
// if(Ispublish(var,index) != -1)
// {
//     batarr =  var->qarray[index-1].items;
//     var->parray[pnum].id = var->qarray[index-1].id;
//     var->parray[pnum].title = var-> qarray[index-1].title;
//     var->parray[pnum].items.swap(batarr);
//     cout << "id:" << var->parray[pnum].id << endl;
//     cout << "title: " << var-> parray[pnum].title << endl;
    
//     for(int i = 0;i < var->parray[pnum].items.size();i++)
//     {
//         cout << "选项"<<i<<": "<< var->parray[pnum].items[i] << endl;
//     }
//     pnum++;
//     cout << "问卷编号为"<<index<<"的问卷发布成功！" << endl;
// }else{
//     cout << "该编号的问卷已经发布了！" << endl;
// }
//     system("pause");
//     system("cls");
// }
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
    fo.open(FILENAME,ios::out);//允许输出(写入操作)到流。
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
int main()
{
    QArray var;//实例化问卷对象
    Answer vat;//实例化答案对象
    int myflag;
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
}
    return 0;
}