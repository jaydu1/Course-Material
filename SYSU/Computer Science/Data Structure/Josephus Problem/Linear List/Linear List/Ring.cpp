//
//  Ring.cpp
//  DataStructure
//
//  Created by 杜金鸿 on 2017/3/8.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include <iostream>
using namespace std;
#include "Ring.h"




void Ring::create(int n, int m){
    Node *r,*s;
    first=new Node;
    r=first;
    r->data=1;
    for (int i=1; i<n; i++) {
        s=new Node;
        s->data=i+1;
        r->next=s;
        r=s;
    }
    r->next=first;
    code=m;
}

void Ring::Delete(Node *p){
    cout<<(p->data)<<'\t';
    Node *t;
    if(p->next!=p){        
        if(first==p){
            first=p->next;
        }
        t=p;
        p=p->next;
        delete t;
    }
    else{
        delete p;
    }
}

void Ring::run(){
    Node *pre,*p;
    pre=first;
    p=first->next;
    if(code==1){
        while(pre->next!=first){
            cout<<pre->data<<endl;
            pre=pre->next;
        }
        cout<<pre->data<<endl;
    }
    else{
        int count=2;
        while(p!=pre){
            if(count==code){
                pre->next=p->next;
                Delete(p);
                p=pre->next;
                count=1;
            }
            pre=p;
            p=p->next;
            count++;
        }
        Delete(p);
    }
}





void Ring2::create(int n, int m){
    p=new int[n];
    flag=new int[n];
    for (int i=0; i<n; i++) {
        *(p+i)=i+1;
        *(flag+i)=i+1;
    }
    *(flag+n-1)=0;
    code=m;
    num=n;
}


void Ring2::run(){
    if(code==1){
        for (int i=0; i<num ; i++) {
            cout<<p[i]<<endl;
        }
    }
    else{
        int i,j;
        i=0;
        j=1;
        int count=2;
        while(i!=j){
            if(count==code){
                cout<<p[j]<<'\t';
                flag[i]=flag[j];
                j=flag[i];
                count=1;
            }
            i=j;
            j=flag[j];
            count++;
        }
        cout<<p[i]<<'\t';
    }
}

void Ring3::create(int n, int m){
    p=new int[n];
    for (int i=0; i<n; i++) {
        *(p+i)=i+1;
    }
    code=m;
    num=n;
}
void Ring3::Delete(int n){
    cout<<p[n]<<'\t';
    for (int i=n ; i<num+1 ; i++) {
        p[i]=p[i+1];
    }
    num--;
}

void Ring3::run(){
    if(code==1){
        for (int i=0; i<num ; i++) {
            cout<<p[i]<<endl;
        }
    }
    else{
        int i;
        i=code-1;
        while(num>1){
            Delete(i);
            i=(i+code-1)%num;
        }
        cout<<p[0]<<'\t';
    }
}

void Ring4::create(int n, int m){
    p=new int[n];
    for (int i=0; i<n; i++) {
        *(p+i)=i+1;
    }
    p[n-1]=0;
    code=m;
    num=n;
}


void Ring4::run(){

    if(code==1){
        for (int i=0; i<num ; i++) {
            cout<<i+1<<endl;
        }
    }
    else{
        int i,j;
        i=0;
        j=1;
        int count=2;
        while(i!=j){
            if(count==code){
                cout<<j+1<<'\t';
                p[i]=p[j];
                j=p[i];
                count=1;
            }
            i=j;
            j=p[j];
            count++;
        }
        cout<<i+1<<'\t';
    }
}

