//
//  main.cpp
//  graph
//
//  Created by 杜金鸿 on 2017/5/20.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include <iostream>
#include "graph.cpp"

int main(int argc, const char * argv[]) {
    char ch[]={'A','B','C','D','E','F'};
    int g[6][6]={{1,0,1,0,1,0},
        {1,1,0,1,0,0},
        {1,1,1,0,0,0},
        {0,1,0,1,0,1},
        {1,0,0,0,1,1},
        {0,0,0,0,0,1}};
    Graph<char> a(ch,6,g[0]);
    a.show_graph();
    a.DFS_find();

    return 0;
}
