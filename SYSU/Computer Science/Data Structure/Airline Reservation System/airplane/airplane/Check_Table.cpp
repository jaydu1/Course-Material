//
//  Check_Table.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/4.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"

Check_Table::Check_Table():num_plane(0),max_num(1){
    plane = new int*[max_num];
    time = new string*[max_num];
    for (int i=0; i<max_num; i++) {
        plane[i] = new int[3]();
        time[i] = new string[4];
    }
}

Check_Table::~Check_Table(){
    if (max_num>0) {
        for (int i=0; i<max_num; i++) {
            delete[] plane[i];
            delete[] time[i];
        }
        delete[] plane;
        delete[] time;
    }
}

Check_Table& Check_Table::operator=(Check_Table &c){
    if (max_num>0) {
        for (int i=0; i<max_num; i++) {
            delete[] plane[i];
            delete[] time[i];
        }
        delete[] plane;
        delete[] time;
    }
    num_plane = c.num_plane;max_num = c.max_num;
    plane = new int*[max_num];
    time = new string*[max_num];
    for (int i=0; i<max_num; i++) {
        plane[i] = new int[3];
        time[i] = new string[4];
    }
    for (int i=0; i<num_plane; i++) {
        for (int j=0; j<3; j++) {
            plane[i][j]=c.plane[i][j];
        }
        for (int j=0; j<4; j++) {
            time[i][j] = c.time[i][j];
        }
    }
    return *this;
}


void Check_Table::addPlane(int m, int n, int o,string year/*=""*/,string month/*=""*/,string day/*=""*/,string date/*=""*/){
    if (num_plane==max_num) {
        int** p;
        string** q;
        max_num = 2*max_num;
        p = new int*[max_num];
        q = new string*[max_num];
        for (int i=0; i<max_num; i++) {
            p[i] = new int[3];
            q[i] = new string[4];
        }
        for (int i=0; i<num_plane; i++) {
            for (int j=0; j<3; j++) {
                p[i][j] = plane[i][j];
            }
            for (int j=0; j<4; j++) {
                q[i][j] = time[i][j];
            }
        }
        for (int i=0; i<max_num/2; i++) {
            delete[] plane[i];
            delete[] time[i];
        }
        delete[] plane;
        delete[] time;
        plane = p;
        time = q;
    }
    plane[num_plane][0] = m;
    plane[num_plane][1] = n;
    plane[num_plane][2] = o;
    time[num_plane][0] = year;
    time[num_plane][1] = month;
    time[num_plane][2] = day;
    time[num_plane++][3] = date;

}

void Check_Table::Clear(){
    if (max_num>0) {
        for (int i=0; i<max_num; i++) {
            delete[] plane[i];
            delete[] time[i];
        }
        delete[] plane;
        delete[] time;
    }
    num_plane = 0;
    max_num = 1;
    plane = new int*[max_num];
    time = new string*[max_num];
    for (int i=0; i<max_num; i++) {
        plane[i] = new int[3];
        time[i] = new string[4];
    }
}

