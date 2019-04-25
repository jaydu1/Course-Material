//
//  graph.cpp
//  graph
//
//  Created by 杜金鸿 on 2017/5/20.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "graph.hpp"
#include <iostream>
using namespace std;


template<class T>
Graph<T>::Graph(T a[], int n, int e){
    vertexNum = n;arcNum = e;count = 0;flag = false;
    visited = new int[vertexNum]();
    S = new int[vertexNum]();
    for (int i=0; i<vertexNum; i++) {
        vertex[i]=a[i];
    }
    for (int i=0; i<vertexNum; i++) {
        for (int j=0;j<vertexNum; j++) {
            arc[i][j] = 0;
        }
    }
    for (int i,j,k = 0; k<arcNum; k++) {
        cout<<"请输入边的两个顶点的序号：";
        cin>>i>>j;
        arc[i][j] = 1;arc[j][i] = 1;
    }
}

template<class T>
Graph<T>::Graph(T a[], int n, int* g){
    vertexNum = n;count = 0; arcNum = 0;
    visited = new int[vertexNum];
    S = new int[vertexNum];
    for (int i=0; i<vertexNum; i++) {
        vertex[i]=a[i];
        visited[i] = 0;
    }
    for (int i=0; i<vertexNum; i++) {
        for (int j=0;j<vertexNum; j++) {
            arcNum++;
            arc[i][j]=g[i*vertexNum+j];
        }
    }
}

template<class T>
Graph<T>::~Graph(){
    delete[] visited;
    delete[] S;
}



template<class T>
void Graph<T>::DFS(int v){
    visited[v] = 1; S[count++]=v; int j=0;
    for (j = 0; j<vertexNum; j++) {
        if (v!=j && arc[v][j] == 1 && visited[j] == 0) {
            DFS(j);
        }
    }
    if (count==vertexNum) {
        flag = true;
        return;
    }
    if (j == vertexNum) {
        visited[v] = 0; count--;
    }

}

template<class T>
void Graph<T>::DFS_find(){
    for (int i=0; i<vertexNum; i++) {
        flag = false;
        count = 0;
        for (int j=0; j<vertexNum; j++) {
            visited[j]=0;
        }
        DFS(i);
        show();
    }
}

template<class T>
void Graph<T>::show_graph(){
    cout<<"图："<<endl<<'\t';
    for (int k=0; k<vertexNum; k++) {
        cout<<vertex[k]<<'\t';
    }
    cout<<endl;
    for (int i=0; i<vertexNum; i++) {
        cout<<vertex[i]<<'\t';
        for (int j=0; j<vertexNum; j++) {
            cout<<arc[i][j]<<'\t';
        }
        cout<<endl;
    }
}

template<class T>
void Graph<T>::show(){
    if (flag) {
        cout<<"汉密顿路：";
        for (int i=0; i<vertexNum; i++) {
            cout<<vertex[S[i]];
            if (i!=vertexNum-1) {
                cout<<"-->";
            }
        }
        cout<<endl;
    }
    else
        cout<<"不存在从"<<vertex[S[0]]<<"出发的哈密顿路"<<endl;
}

