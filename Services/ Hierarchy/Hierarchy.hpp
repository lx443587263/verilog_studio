//
// Created by 狂飙的西红柿 on 2022/8/26.
//

#ifndef VERILOG_STUDIO_HIERARCHY_HPP
#define VERILOG_STUDIO_HIERARCHY_HPP

#include <string>
#include <algorithm>
#include <unordered_map>
#include "../../IService.hpp"
#include "../../Common/Supporting/Tree.hpp"

using namespace std;
namespace VerilogStudio {
    class Hierarchy : public IService {
    public:
        Hierarchy() {}

        ~Hierarchy() {}

        void GetIncludeModule(unordered_multimap<string, string> &IncludeModuleNameUnMap);

        htree_node<string>* make_node(int layer, string& ModuleName,vector<string> &IncludeModuleName);

        htree<string> createTree(vector<string> &ModuleName);

    private:
        typedef htree_node<string> node_type;
        typedef htree<string> tree_type;
        vector<string> IncludeModuleName;
    };

}


#endif //VERILOG_STUDIO_HIERARCHY_HPP
