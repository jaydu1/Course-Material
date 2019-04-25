//
//  Egde.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/4.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"

Edge::Edge(){
    Init();
}

Edge::~Edge(){
    if (num_plane>0) {
        delete[] plane;
    }
    
}

void Edge::Init(){
    num_plane = 0;
    max_num = 1;
    plane = new Plane[max_num];
}

void Edge::addPlane(Plane &p){
    if (num_plane==max_num) {
        Plane *q;
        max_num = 2*max_num;
        q = new Plane[max_num];
        for (int i=0; i<num_plane; i++) {
            q[i] = plane[i];
        }
        if (max_num/2>0) {
            delete[] plane;
        }
        plane = q;
    }
    plane[num_plane++] = p;
}
