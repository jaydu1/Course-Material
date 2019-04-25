//
//  Arc.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/4.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"

void Arc::Init(int size){
    arc = new Edge[size];
    this->size = size;
    for (int i=0; i<size; i++) {
        arc->Init();
    }
}

Arc::~Arc(){
    if (size>0) {
        delete[] arc;
    }
    
}
