//
//  graph.hpp
//  graph
//
//  Created by 杜金鸿 on 2017/5/20.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
const int Maxsize=10;

template<class T>
class Graph{
public:
    Graph(T a[], int n, int e);     // 构造函数1
    Graph(T a[], int n, int g[]);   // 构造函数2
    ~Graph();                       // 析构函数
    void DFS(int v);                // 取消回溯的深度优先遍历算法
    void DFS_find();                // 遍历各初始结点
    void show_graph();              // 输出图
    void show();                    // 输出
private:
    T vertex[Maxsize];              // 结点数组
    int arc[Maxsize][Maxsize];      // 邻接矩阵
    int vertexNum,arcNum;           // 结点数、边数
    int* visited;                   // 遍历标志数组
    int* S;                         // 遍历结果数组
    int count;                      // 计数器
    bool flag;                      // 哈密顿路存在标志
};



#endif /* graph_hpp */
