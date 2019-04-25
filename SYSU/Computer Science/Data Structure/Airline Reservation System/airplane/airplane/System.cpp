//
//  System.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/4.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"
#include<ctime>
#include <cstdio>
System::System():prior(0){
    ofstream file("/Users/dujinhong/Documents/study/数据结构/数据结构实验/大作业/airplane/airplane/log.txt",ios::app);
    time_t t;
    t=time(&t);
    file<<ctime(&t)<<endl;
    file.close();
    Init();
}

System::~System(){
    Save();
    delete airplane;
}

void System::Init(){
    airplane = new Airplane;
    airplane->Init();   // 航班信息初始化
    GetKey();
    int flag=1;
    cout      <<"                ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓                  "<<endl;
    cout      <<"                ┃                                    ┃                  "<<endl;
    cout      <<"                ┃                                    ┃                  "<<endl;
    cout      <<"                ┃                                    ┃                  "<<endl;
    cout      <<"                ┃           航空客运订票系统            ┃                  "<<endl;
    cout      <<"                ┃                                    ┃                  "<<endl;
    cout      <<"                ┃       Designed By Jinhong Du       ┃                  "<<endl;
    cout      <<"                ┃                                    ┃                  "<<endl;
    cout      <<"                ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛                  "<<endl<<endl;
    while (flag) {
        int n;
        cout<<"---------------------------------------------------------------------"<<endl;
        cout<<"请选择对应操作:"<<endl;
        cout<<"1.查询航班"<<endl;
        cout<<"2.管理员登录";
        if (prior) {
            cout<<"(已登录)";
        }
        cout<<endl;
        if (prior) {
            cout<<"3.查看日志信息"<<endl;
            cout<<"4.修改管理员密码"<<endl;
            cout<<"5.修改航班信息"<<endl;
            cout<<"6.保存航班信息"<<endl;
            cout<<"7.注销登录"<<endl;
        }
        cout<<"任意键退出"<<endl;
        cin>>n;
        if (n<1 || n>2+5*prior) {
            return;
        }
        switch (n) {
            case 1:
                Check();break;
            case 2:
                AmdinLogin();break;
            case 3:
                Log();break;
            case 4:
                ChangeKey();break;
            case 5:
                Change();break;
            case 6:
                Save();break;
            case 7:
                AmdinLogout();break;
            default:
                break;
        }
    }
}

void System::Sort(){
    airplane->Sort();
}

void System::Check(){
    Sort();
    string ID,year,month,day,start,arrive,start_city,arrive_city;
    cout<<"---------------------------------------------------------------------"<<endl;
    cout<<"请输入相应查询信息（'NA'跳过,'-1'返回）"<<endl;
    cout<<"1.航班号:";cin>>ID;if (ID=="-1"){return;}
    cout<<"2.年:";cin>>year;if (year=="-1"){return;}
    cout<<"3.月:";cin>>month;if (month=="-1"){return;}
    cout<<"4.日:";cin>>day;if (day=="-1"){return;}
    cout<<"5.出发城市:";cin>>start_city;if (start_city=="-1"){return;}
    cout<<"6.到达城市:";cin>>arrive_city;if (arrive_city=="-1"){return;}
    cout<<"7.出发时间:";cin>>start;if (start=="-1"){return;}
    cout<<"8.到达时间:";cin>>arrive;if (arrive=="-1"){return;}
    cout<<endl<<"Searching..."<<endl;
    Search(ID,year,month,day,start,arrive,start_city,arrive_city);
}

void System::Search(string ID,string year,string month,string day,string start,string arrive,string start_city,string arrive_city){
    Check_Table c;
    (*airplane).Search(c,ID,year,month,day,start,arrive,start_city,arrive_city);
    if (c.num_plane>0) {
        int i=0;
        if (c.num_plane>1) {
            cout<<"---------------------------------------------------------------------"<<endl;
            cout<<"请选择相应航班(任意键返回):";cin>>i;
            if (i<1 || i>c.num_plane) {
                return;
            }
            i--;
        }
        int n=1;
        while (n) {
            cout<<"---------------------------------------------------------------------"<<endl;
            cout<<"请选择对应操作:"<<endl;
            cout<<"1.购票"<<endl;
            cout<<"2.退票"<<endl;
            if (prior==1) {
                cout<<"3.修改航班信息"<<endl;
                cout<<"4.删除航班"<<endl;
                cout<<"5.查看订票客户"<<endl;
                cout<<"6.查看候补客户"<<endl;
            }
            cout<<"任意键返回"<<endl;
            cin>>n;
            if (n<1 || n>2+3*prior) {
                return;
            }
            int flag=1;
            switch (n) {
                case 1:{
                    while (flag==1) {
                        int d;
                        if (arrive_city!="NA" && c.plane[i][1]!=airplane->citytonum[arrive_city]) {
                            d = Book(airplane->citytonum[start_city],c.plane[i][1],c.plane[i][0]);
                            if(d>=0){
                                cout<<"订票成功!"<<endl;
                            }
                            else if(d!=-1){
                                cout<<"订票失败!已加入替补客户名单。"<<endl;
                                
                            }
                            d = Book(c.plane[i][1],airplane->citytonum[arrive_city],c.plane[i][2]);
                            if (d>=0) {
                                cout<<"订票成功!"<<endl;
                            }
                            else if(d!=-1){
                                cout<<"订票失败!已加入替补客户名单。"<<endl;
                            }
                        }
                        else{
                            d = Book(c.plane[i][0], c.plane[i][1], c.plane[i][2]);
                            if(d>=0){
                                cout<<"订票成功!"<<endl;
                            }
                            else if(d!=-1){
                                cout<<"订票失败!已加入替补客户名单。"<<endl;
                            }
                        }
                        cout<<"是否继续订票？"<<endl<<"1.是"<<endl<<"任意键返回"<<endl;
                        cin>>flag;
                    }
                }
                    break;
                case 2:{
                    while (flag==1) {
                        if (arrive_city!="NA" && c.plane[i][1]!=airplane->citytonum[arrive_city]) {
                            cout<<"请分别退票!"<<endl;
                            break;
                        }
                        string name,ID;
                        cout<<"请输入退票客户信息，退出请输入'-1'"<<endl;
                        cout<<"请输入退票客户姓名:";cin>>name;
                        if (name=="-1") {
                            break;
                        }
                        cout<<"请输入退票客户证件号码:";cin>>ID;
                        if (ID=="-1") {
                            break;
                        }
                        string kind = airplane->deleteBooked(c.plane[i][0],c.plane[i][1],c.plane[i][2],name,ID);
                        if (kind=="") {
                            cout<<"输入错误或该用户未订票!"<<endl;
                        }
                        airplane->informAlternative(c.plane[i][0],c.plane[i][1],c.plane[i][2],kind);
                        cout<<"退票成功!"<<endl<<"是否继续退票？"<<endl<<"1.是"<<endl<<"任意键返回"<<endl;
                        cin>>flag;
                    }
                }
                    break;
                case 3:
                    while (flag==1) {
                        if (arrive_city!="NA" && c.plane[i][1]!=airplane->citytonum[arrive_city]) {
                            cout<<"请分别修改航班信息!"<<endl;
                            break;
                        }
                        airplane->Change(c.plane[i][0],c.plane[i][1],c.plane[i][2]);
                        cout<<"修改成功!"<<endl;
                        cout<<"是否继续修改？"<<endl<<"1.是"<<endl<<"任意键返回"<<endl;
                        cin>>flag;
                    }
                    break;
                case 4:
                    if (arrive_city!="NA" && c.plane[i][1]!=airplane->citytonum[arrive_city]) {
                        cout<<"请选择直达航线!"<<endl;
                        break;
                    }
                    airplane->DeletePlane(c.plane[i][0],c.plane[i][1],c.plane[i][2]);
                    break;
                case 5:
                    if (arrive_city!="NA" && c.plane[i][1]!=airplane->citytonum[arrive_city]) {
                        cout<<"请选择直达航线!"<<endl;
                        break;
                    }
                    airplane->showBooked(c.plane[i][0],c.plane[i][1],c.plane[i][2]);
                    break;
                case 6:
                    if (arrive_city!="NA" && c.plane[i][1]!=airplane->citytonum[arrive_city]) {
                            cout<<"请选择直达航线!"<<endl;
                            break;
                        }
                    airplane->showAlternative(c.plane[i][0],c.plane[i][1],c.plane[i][2]);
                    break;
                default:
                    break;
            }
        }
    }
}

int System::Book(int i, int j, int k){
    string name, kindId, ID, num, state, kind, ticket;
    cout<<"正在订购的航班为";airplane->show(i,j,k);
    cout<<"请输入订票乘客信息(返回请输入'-1'):"<<endl;
    cout<<"姓名:";cin>>name;if (atoi(name.c_str())==-1) {return -1;}
    cout<<"证件类型:";cin>>kindId;
    if (atoi(kindId.c_str())==-1) {return -1;}
    cout<<"证件号码:";cin>>ID;
    if (atoi(ID.c_str())==-1) {return -1;}
    cout<<"订票数量:";cin>>num;
    if (atoi(name.c_str())==-1) {return -1;}
    cout<<"航班情况:";cin>>state;
    if (atoi(state.c_str())==-1) {return -1;}
    cout<<"舱位等级:";cin>>kind;
    if (atoi(kind.c_str())==-1) {return -1;}
    cout<<"订单编号:";cin>>ticket;if (atoi(ticket.c_str())==-1){return -1;}
    return airplane->addBooked(i,j,k,name, kindId, ID, num, state, kind, ticket);
}

void System::Change(){
    int flag = 1;
    while (flag) {
        int n;
        cout<<"---------------------------------------------------------------------"<<endl;
        cout<<"请输入相应操作序号:"<<endl;
        cout<<"1.添加航班"<<endl;
        cout<<"2.删除航班"<<endl;
        cout<<"3.修改航班"<<endl;
        cout<<"任意键返回"<<endl;
        cin>>n;
        if (n<1 || n>3) {
            return;
        }
        int i=1;
        switch (n) {
            case 1:{
                while (i==1) {
                    AddPlane();
                    cout<<"添加成功!是否继续添加航班?"<<endl<<"1.是"<<endl<<"任意键返回"<<endl;
                    cin>>i;
                }
            }
                break;
            case 2:{
                cout<<"请搜索相应的航班进行删除:"<<endl;
                while (i==1) {
                    Check();
                    cout<<"是否继续修改？"<<endl<<"1.是"<<endl<<"任意键返回"<<endl;
                    cin>>i;
                }
            }
                break;
            case 3:{
                cout<<"请搜索相应的航班进行修改:"<<endl;
                while (i==1) {
                    Check();
                    cout<<"是否继续修改？"<<endl<<"1.是"<<endl<<"任意键返回"<<endl;
                    cin>>i;
                }
            }
            default:
                break;
        }
    }
}

void System::Save(){
    airplane->Save();
    cout<<"保存成功!"<<endl;
}


void System::AmdinLogin(){
    string key2="";
    cout<<"请输入管理员密码:";cin>>key2;
    while (key2!=key) {
        if (key2=="-1") {
            return;
        }
        cout<<"密码错误！请重新输入(返回请输入-1):";cin>>key2;
    }
    prior = 1;
    cout<<"             ╔════════════════════════════════════════╗             "<<endl;
    cout<<"             ║            Administrator               ║             "<<endl;
    cout<<"             ╚════════════════════════════════════════╝             "<<endl;
}

void System::AmdinLogout(){
    prior = 0;
    cout<<"注销成功!"<<endl;
}

void System::GetKey(){
    ifstream fileIn("/Users/dujinhong/Documents/study/数据结构/数据结构实验/大作业/airplane/airplane/Key");
    if (fileIn) {
        getline(fileIn,key);
        fileIn.close();
    }
}

void System::ChangeKey(){
    string key2;
    cout<<"请输入原密码:";cin>>key2;
    while (key2!=key) {
        if (key2=="-1") {
            return;
        }
        cout<<"密码错误！请重新输入(返回请输入-1):";cin>>key2;
    }
    cout<<"请输入新密码:";cin>>key;
    ofstream fileOut("/Users/dujinhong/Documents/study/数据结构/数据结构实验/大作业/airplane/airplane/Key");
    if (fileOut.is_open()) {
        fileOut<<key;
        fileOut.close();
    }
    cout<<"管理员密码修改成功!"<<endl;
}

void System::Log(){
    ifstream fileIn("/Users/dujinhong/Documents/study/数据结构/数据结构实验/大作业/airplane/airplane/Log.txt");
    if (fileIn) {
        string s;
        while (getline(fileIn,s)) {
            cout<<s<<endl;
        }
        fileIn.close();
    }
}

void System::AddPlane(){
    string ss,name,start_city,arrive_city,year,month,day,date,shape,discount,kind,price,num_now,num_max,start,arrive,schedule;
    int n;
    cout<<"请输入新航班信息('-1'返回):"<<endl;
    cout<<"航班编号:";cin>>name;if(name=="-1"){return;}
    cout<<"出发城市及机场英文代码:";cin>>start_city;if(start_city=="-1"){return;}
    cout<<"到达城市及机场英文代码:";cin>>arrive_city;if(arrive_city=="-1"){return;}
    cout<<"年:";cin>>year;if(year=="-1"){return;}
    cout<<"月:";cin>>month;if(month=="-1"){return;}
    cout<<"日:";cin>>day;if(day=="-1"){return;}
    cout<<"星期:";cin>>date;if(date=="-1"){return;}
    cout<<"出发时间:";cin>>start;if(start=="-1"){return;}
    cout<<"到达时间:";cin>>arrive;if(arrive=="-1"){return;}
    cout<<"班期:";cin>>schedule;if(schedule=="-1"){return;}
    cout<<"机型:";cin>>shape;if(shape=="-1"){return;}
    cout<<"折扣:";cin>>discount;if(discount=="-1"){return;}
    cout<<"舱位种类:";cin>>n;if(n==-1){return;}
    ss=name+'\t'+start_city+'\t'+arrive_city+'\t'+schedule+'\t'+start+'\t'+arrive+'\t'+shape+'\t'+discount;
    for (int i=0; i<n; i++) {
        cout<<"舱位("<<i+1<<")名称:";cin>>kind;
        cout<<"舱位("<<i+1<<")价格:";cin>>price;
        ss=ss+'\t'+kind+'\t'+price+'\t'+"0"+'\t'+"0";
    }
    airplane->addPlane(year, month, day, date, ss+"\nNA\nNA");
}
