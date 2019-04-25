//
//  main.cpp
//  StringPattern
//
//  Created by 杜金鸿 on 2017/4/5.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include <iostream>
using namespace std;


void ASM(char P[],char T[],int m, int n){
    int D[m+1][n+1];
    char B[m][n];
    int X[m][n];
    int Y[m][n];
    for (int j=0; j<=n; j++) {
        D[0][j]=0;
    }
    for (int j=0; j<=m; j++) {
        D[j][0]=j;
    }

    for (int j=1; j<=n; j++) {
        for (int i=1; i<=m; i++) {
            if(P[i-1]==T[j-1]){
                D[i][j]=min(D[i-1][j-1],D[i-1][j]+1);
                D[i][j]=min(D[i][j],D[i][j-1]+1);
                if (D[i][j]==D[i-1][j-1]) {
                    B[i-1][j-1]='_';
                    X[i-1][j-1]=i-2;
                    Y[i-1][j-1]=j-2;
                }
                else if (D[i][j]==D[i-1][j]+1) {
                    B[i-1][j-1]='d';
                    X[i-1][j-1]=i-2;
                    Y[i-1][j-1]=j-1;
                }
                else{
                    B[i-1][j-1]='i';
                    X[i-1][j-1]=i-1;
                    Y[i-1][j-1]=j-2;
                }
            }
            else{
                D[i][j]=min(D[i-1][j-1]+1,D[i-1][j]+1);
                D[i][j]=min(D[i][j],D[i][j-1]+1);
                if (D[i][j]==D[i-1][j-1]+1) {
                    B[i-1][j-1]='r';
                    X[i-1][j-1]=i-2;
                    Y[i-1][j-1]=j-2;
                }
                else if (D[i][j]==D[i-1][j]+1){
                    B[i-1][j-1]='d';
                    X[i-1][j-1]=i-2;
                    Y[i-1][j-1]=j-1;
                }
                else{
                    B[i-1][j-1]='i';
                    X[i-1][j-1]=i-1;
                    Y[i-1][j-1]=j-2;
                }
            }
        }
    }
    
    for (int i=0; i<=m; i++) {
        if (i>0) {
            cout<<P[i-1]<<'\t';
        }
        else
            cout<<'\t';
        for (int j=0; j<=n; j++){
            cout<<D[i][j]<<'\t';
            
        }
        cout<<endl;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Matrix X:"<<endl;
    for (int i=0; i<m; i++) {
        cout<<P[i]<<'\t'<<'\t';
        for (int j=0; j<n; j++){
            cout<<X[i][j]<<'\t';
            
        }
        cout<<endl;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Matrix Y:"<<endl;
    for (int i=0; i<m; i++) {
        cout<<P[i]<<'\t'<<'\t';
        for (int j=0; j<n; j++){
            cout<<Y[i][j]<<'\t';
            
        }
        cout<<endl;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"Matrix B:"<<endl;
    for (int i=0; i<m; i++) {
            cout<<P[i]<<'\t'<<'\t';
        for (int j=0; j<n; j++){
            cout<<B[i][j]<<'\t';
            
        }
        cout<<endl;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
    for (int k=0; k<n; k++) {
        char c[m+n];
        int l=0;
        int i2,j2;
        for (int i=m-1,j=k;(i>=0 && j>=0);) {
            c[l]=B[i][j];
            l++;
            i2=X[i][j];
            j2=Y[i][j];
            i=i2;j=j2;

        }
        // 若子串长度不足$m$，则前面部分的对应关系必为删除delete
        for (int i=l; i<m; i++) {
            cout<<'d';
        }
        // 逆序输出对应关系
        for (int i=l-1; i>=0; i--) {
            cout<<c[i];
        }
        cout<<endl;
    }
    
}



int main(int argc, const char * argv[]) {

    char T[]="Have a hsppy day";//"agbgdaproxiomally";
    char P[]="happy";//"ggdapproximatly";
    int m=5,n=16;
    
//    char T[30],P[30];
//    cout<<"Please input P(<30 chars):"<<endl;
//    cin.getline(P,30,'\n');
//    cout<<"Please input T(<30 chars):"<<endl;
//    cin.getline(T,30,'\n');
//    int m,n;
//    cout<<"Please input m:"<<endl;
//    cin>>m;
//    cout<<"Please input m:"<<endl;
//    cin>>n;
//    cout<<"The cost matrix is:"<<endl;
    cout<<'\t'<<'\t';
    for (int i=0; i<n; i++) {
        cout<<T[i]<<'\t';
    }
    cout<<endl;
    ASM(P,T,m,n);
//    cout<<a;
//    cout<<"K="<<S(P,T,m,n)<<endl;
    return 0;
}
