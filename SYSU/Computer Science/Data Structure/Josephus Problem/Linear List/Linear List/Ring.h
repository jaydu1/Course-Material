//
//  Ring.h
//  DataStructure
//
//  Created by 杜金鸿 on 2017/3/8.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#ifndef Ring_h
#define Ring_h



struct Node{
    int data;
    Node *next;
};


class Ring{
public:
    Ring(){create(5000, 4);}              // 构造函数
    Ring(int n,int m){create(n,m);};    // 复制构造函数
    ~Ring(){}                           // 析构函数
    void run();                         // 出圈算法
    
private:
    Node *first;                        // 头指针
    void create(int n,int m);           // 初始化
    void Delete(Node *p);               // 某结点出圈
    int code;                           // 密码m
};

class Ring2{
public:
    Ring2(){create(5000, 4);}             // 构造函数
    Ring2(int n,int m){create(n,m);};   // 默认构造函数
    ~Ring2(){                           // 析构函数
        delete[] flag;
        delete[] p;
    }
    void run();                         // 出圈算法
    
private:
    int* p;                             // 逻辑位置数组
    int* flag;                          // 指示数组
    void create(int n,int m);           // 初始化
    void Delete(int n);                 // 某结点出圈
    int num;                            // 总人数n
    int code;                           // 密码m
};

class Ring3{
public:
    Ring3(){create(5000, 4);}             // 构造函数
    Ring3(int n,int m){create(n,m);};   // 默认构造函数
    ~Ring3(){delete[] p;}                          // 析构函数
    void run();                         // 出圈算法
    
private:
    int* p;                             // 数据元素
    void create(int n,int m);           // 初始化
    void Delete(int n);                 // 某元素出圈
    int num;                            // 总人数n
    int code;                           // 密码m
};


class Ring4{
public:
    Ring4(){create(5000, 4);}             // 构造函数
    Ring4(int n,int m){create(n,m);};   // 默认构造函数
    ~Ring4(){delete[] p;}                          // 析构函数
    void run();                         // 出圈算法
    
private:
    int* p;                             // 数据元素
    void create(int n,int m);           // 初始化
    int num;                            // 总人数n
    int code;                           // 密码m
};

#endif /* Ring_h */
