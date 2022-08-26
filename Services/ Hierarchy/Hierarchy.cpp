//
// Created by 狂飙的西红柿 on 2022/8/26.
//

#include "Hierarchy.hpp"

void VerilogStudio::Hierarchy::GetIncludeModule(unordered_multimap<string, string> &IncludeModuleNameUnMap) {
    for (auto &itr: IncludeModuleNameUnMap) {
        IncludeModuleName.emplace_back(itr.first);
    }
}


VerilogStudio::htree<string>
VerilogStudio::Hierarchy::createTree(vector<string> &ModuleName) {
    node_type *root = nullptr;/*make_node()*/
    tree_type::iterator iter(root);
    tree_type tr(root);
    /*tr.insert*/
    return tr;
}

VerilogStudio::htree_node<string>*
VerilogStudio::Hierarchy::make_node(int layer, string &ModuleName, vector<string> &IncludeModuleName) {
    node_type *node = new node_type;
    node->ModuleName = ModuleName;
    node->layer = to_string(layer);
    return node;
}


