//
//  airplane.hpp
//  airplane
//
//  Created by 杜金鸿 on 2017/5/22.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#ifndef airplane_hpp
#define airplane_hpp

#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#include<string>
#include <cstdlib>

// 客户信息类
class Booked{                                       // 已订票客户类
public:
    Booked():name(" "),kindID(" "),ID(" "),num(" "),state(" "),kind(" "),ticket(" "){};
                                                    // 默认构造函数
    Booked(string name,string kindID,string ID,string book_num,string state,string kind,string ticket);
                                                    // 构造函数
    ~Booked(){};                                    // 析构函数
    Booked& operator=(Booked &b);                   // 重载 = 运算符
    void show();                                    // 输出已订票客户信息
    string Save();                                  // 保存
    string name,kindID,ID,num,state,kind,ticket;    // 已订票客户信息
};

class Alternative{                                  // 候补客户类
public:
    Alternative():name(" "),kindID(" "),ID(" "),num(" "),kind(" "){};
                                                    // 默认构造函数
    Alternative(string name,string kindID,string ID,string book_num,string kind);
                                                    // 构造函数
    ~Alternative(){};                               // 析构函数
    Alternative& operator=(Alternative &a);         // 重载 = 运算符
    void show();                                    // 输出候补客户信息
    string inform();                                // 输出候补客户信息
    string Save();                                  // 保存
    string name,kindID,ID,num,kind;                 // 候补客户信息
};

class Customer{                                 // 客户类
public:
    Customer();                                 // 默认构造函数
    ~Customer();                                // 析构函数
    Customer& operator=(Customer &p);           // 重载 = 运算符
    void addBooked(string name,string kindID,string ID,string book_num,string state,string kind,string ticket);
                                                // 添加已订票客户
    void addAlternative(string name,string kindID,string ID,string book_num,string kind);
                                                // 添加替补客户
    void showBooked();                          // 输出已订票客户
    void showAlternative();                          // 输出替补客户
    void informAlternative(string kind);          // 通知替补客户
    string deleteBooked(int de);                // 退票
    string Save();                              // 保存客户信息
    Booked* booked;                             // 已订票客户
    Alternative* alternative;                   // 候补客户
    int num_booked,num_alternative;             // 已订票客户数、候补客户数
    int max_booked,max_alternative;             // 最大已订票客户数、最大候补客户数
};

class Check_Table{                                  // 航班索引表
public:
    Check_Table();                                  // 默认构造函数
    ~Check_Table();                                 // 析构函数
    Check_Table& operator=(Check_Table &c);         // 重载 = 运算符
    void addPlane(int m,int n,int o,string year="",string month="",string day="",string date="");
                                                    // 添加航班索引
    void Clear();                                   // 清除索引表
    int** plane;                                    // 三元组
    string** time;                                  // 日期四元组
    int num_plane,max_num;                          // 航班数、最大容量
};

// 航班结点
class Plane{                                                        // 航班结点类
public:
    Plane(){kind=nullptr;price=num_now=num_max=nullptr;};   // 默认构造函数
    Plane(string name,string year,string month,string day,string date,string schedule,string start,string arrive,string shape,string discount,int num,string* kind,int* price,int* num_now,int* num_max,int plat_start,int plat_arrive);
                                                            // 构造函数
    ~Plane();                                               // 析构函数
    Plane& operator=(Plane &p);                             // 重载 = 运算符
    string Save(string start_city, string arrive_city);     // 保存该航班
    void show();
    int Minprice();                                         // 返回最低票价
    string name;                                            // 航班编号
    string year,month,day,date;                             // 日期
    string start;                                           // 出发时间
    string arrive;                                          // 到达时间
    int plat_start,plat_arrive;                             // 出发机场、到达机场序号
    string schedule;                                        // 班期
    string shape,discount;                                  // 机型、折扣
    int num;                                                // 舱位类型数
    string* kind;                                           // 舱位类型名称
    int* price;                                             // 价格
    int* num_now;                                           // 已订乘客数
    int* num_max;                                           // 最大乘客数
    Customer customer;                                      // 客户类
};



// 边类
class Edge{                             // 有向边类
public:
    Edge();                             // 默认构造函数
    ~Edge();                            // 析构函数
    void Init();                        // 初始化
    void addPlane(Plane &p);            // 添加航班
    Plane* plane;                       // 航班
    int num_plane,max_num;              // 航班数量、最大容量
};

// 邻接矩阵
class Arc{                              // 邻接矩阵类
public:
    Arc(){};                            // 默认构造函数
    ~Arc();                             // 析构函数
    void Init(int size);                // 初始化
    int size;                           // 大小
    Edge* arc;                          // 有向边
};

// 城市结点
class City{                             // 城市结点类
public:
    City();                             // 默认构造函数
    ~City();                            // 析构函数
    void addAirport(string airport);    // 添加机场
    string name,ID;                     // 城市名称、城市英文代码
    string* airport;                    // 机场
    int num_airport,max_num;            // 机场个数、最大容量
};


class CitytoNum{                        // 城市名称-城市序号索引表类
public:
    CitytoNum();                        // 默认构造函数
    ~CitytoNum();                       // 析构函数
    int operator[](string cityname);    // 重载[]运算符
    void addcity(City city[],int num);  // 添加城市索引
    string* name,*ID;                   // 城市名称、城市英文代码
    int num;                            // 城市个数
};

// 航线信息类(有向图)
class Airplane{
public:
    Airplane(int num_city=5);                                   // 默认构造函数
    ~Airplane();                                                // 析构函数
    /*-----------------------  初始化  -----------------------*/
    void Init();                                                // 航班初始化
    void addCity(const string &s, int i);                       // 添加城市结点
    void addArc(string &year,string &month,string &day,string &date,const string &s,int city0,int city1,int plat0,int plat1);
                                                                // 添加有向边
    void addPlane(string &year,string &month,string &day,string &date,const string &s);
                                                                // 添加航班记录
    /*-----------------------排序与查找-----------------------*/
    void Sort();                                                // 基数排序
    void Distribute(Check_Table q[],int m,int j);               // 分配
    void Collect(Check_Table q[],int m);                        // 收集
    void Search(Check_Table &c,string ID,string year,string month,string day,string start,string arrive,string start_city,string arrive_city);
                                                                // 查找航班
    void Transfer(Check_Table &c,string year,string month,string day,string start_city,string arrive_city);
                                                                // 筛选航班
    int SearchTransfer(Check_Table c[],string start_city,string arrive_city);
                                                                // 查找中转航班
    /*-----------------------订票与退票-----------------------*/

    int addBooked(int m,int n,int l,string name,string kindID,string ID,string book_num,string state,string kind,string ticket);
                                                                // 添加订票客户
    int addAlternative(int m,int n,int l,string name,string kindID,string ID,string book_num,string kind);
                                                                // 添加候补客户
    void showBooked(int m,int n,int l);                          // 输出某航班已订票客户
    void showAlternative(int m,int n,int l);                          // 输出某航班候补客户
    string deleteBooked(int m,int n,int l,string name,string ID);     // 退票
    void informAlternative(int m,int n,int l,string kind);       // 通知候补客户
    /*-----------------------修改与保存-----------------------*/
    void Change(int m,int n,int l);                             // 修改航班信息
    void DeletePlane(int m,int n,int l);                        // 删除航班
    void Save();                                                // 保存航班信息
    void show(int i,int j,int k);                               // 输出航班基本信息
    CitytoNum citytonum;                                        // 城市名称-城市序号索引表
private:
    City* city;                                                 // 城市结点
    Arc* arc;                                                   // 有向边
    int num_city;                                               // 城市个数
    string cityname,planename;                                  // 存储文件名称
    Check_Table check_table,check_table_time;                   // 索引表
};


// 中央系统类
class System{
public:
    System();                       // 默认构造函数
    ~System();                      // 析构函数
private:
    /*---------------------- 初始化 ----------------------*/
    void Init();                    // 系统初始化
    void Input();                   // 录入航班情况
    /*--------------------- 普通用户 ---------------------*/
    void Sort();                    // 对航班进行排序
    void Check();                   // 查询航线
    void Search(string ID,string year,string month,string day,string start,string arrive,string start_city,string arrive_city);// 查找航班
    int Book(int i, int j, int k);  // 订票
    /*---------------------- 管理员 ----------------------*/
    void AddPlane();                // 添加航班
    void Change();                  // 修改航班信息
    void Save();                    // 保存航班信息
    void AmdinLogin();              // 管理员登录
    void AmdinLogout();             // 管理员注销
    void GetKey();                  // 读取密码文件
    void ChangeKey();               // 修改管理员密码
    void Log();                     // 输出日志信息
    Airplane* airplane;             // Airplane类
    int prior;                      // 权限级别
    string key;                     // 密码
};


#endif /* airplane_hpp */
