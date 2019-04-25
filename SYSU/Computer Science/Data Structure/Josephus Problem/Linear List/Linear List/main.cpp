//
//  main.cpp
//  DataStructure
//
//  Created by 杜金鸿 on 2017/3/8.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include <iostream>
using namespace std;
#include "Ring.h"
#include "time.h"
int main(int argc, const char * argv[]) {
    clock_t start1,finish1,start2,finish2,start3,finish3,start4,finish4;
    cout<<"约瑟夫环问题求解"<<endl;
    cout<<"链式存储结构——循环链表："<<endl;
    Ring a[100];
    start1=clock();
    for(int n=1;n<100;n++){
        a[n].run();
    }
    finish1=clock();
    cout<<endl<<"------------------------------------------"<<endl;
    cout<<"链式存储结构——静态链表："<<endl;
    Ring2 b[100];
    start2=clock();
    for(int n=1;n<100;n++){
        b[n].run();
    }
    finish2=clock();
    cout<<endl<<"------------------------------------------"<<endl;
    cout<<"顺序存储结构——顺序表："<<endl;
    Ring3 c[100];
    start3=clock();
    for(int n=1;n<100;n++){
        c[n].run();
    }
    finish3=clock();
    cout<<endl;
    
    Ring4 d[100];
    start4=clock();
    for(int n=1;n<100;n++){
        d[n].run();
    }
    finish4=clock();
    cout<<endl;
    cout<< (double)(finish1 - start1) / CLOCKS_PER_SEC<<endl;
    cout<< (double)(finish2 - start2) / CLOCKS_PER_SEC<<endl;
    cout<< (double)(finish3 - start3) / CLOCKS_PER_SEC<<endl;
    cout<< (double)(finish4 - start4) / CLOCKS_PER_SEC<<endl;
    return 0;
}

