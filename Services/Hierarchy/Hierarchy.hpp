//
// Created by 狂飙的西红柿 on 2022/8/26.
//

#ifndef VERILOG_STUDIO_HIERARCHY_HPP
#define VERILOG_STUDIO_HIERARCHY_HPP

/************************************************
 *******************header***********************
 ************************************************/
#include <string>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include "../../IService.hpp"
#include "../../Common/Supporting/Tree.hpp"
#include "../../Services/Parse/Parse.hpp"


namespace VerilogStudio {
    /**********************************************/
    using namespace std;

    /*******************class**********************/
    class Hierarchy : public IService {
    public:
        /********************************************/
        Hierarchy() {}

        ~Hierarchy() {}

        /*********************************************
        *******************create tree****************
        **********************************************/
        htree_node<string> *make_node(const string &ModuleName, const set<string>& ModuleNameSet);

        htree<string> createTree(string &TopName, shared_ptr<Parse>& pPar);

    /********************************************/
    private:
        typedef htree_node<string>      node_type;
        typedef htree<string>           tree_type;
        shared_ptr<Parse>               pParse;
    };

}


#endif //VERILOG_STUDIO_HIERARCHY_HPP
