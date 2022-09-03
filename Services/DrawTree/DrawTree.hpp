//
// Created by 狂飙的西红柿 on 2022/9/2.
//

#ifndef VERILOG_STUDIO_DRAWTREE_HPP
#define VERILOG_STUDIO_DRAWTREE_HPP

/************************************************
 *******************header***********************
 ************************************************/
#include <string>
#include <vector>
#include "../../graphviz/gvc.h"
#include "../../Common/Supporting/Tree.hpp"
#include "../../IService.hpp"

namespace VerilogStudio {
    /**********************************************/
    using namespace std;

    /*******************class**********************/
    class DrawTree : public IService {
    public:
        /********************************************/
        DrawTree() {}

        ~DrawTree() {}

        /*********************************************
        *****************draw tree********************
        **********************************************/
        string get_node_name(string &root_str, string &leaf_str);

        Agnode_t *__draw_rb_node(Agraph_t *g, Agnode_t *_parent, char *name, char *label);

        void __draw_rb(Agraph_t *g, Agnode_t *_parent, htree_node <string> *parent_node, htree_node <string> *_node);

        void draw_rb(htree_node <string> *root, string filename);

    /********************************************/
    private:
        string              __node_name;

    };
}

#endif //VERILOG_STUDIO_DRAWTREE_HPP
