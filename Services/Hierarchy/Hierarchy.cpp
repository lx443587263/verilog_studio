//
// Created by 狂飙的西红柿 on 2022/8/26.
//

#include "Hierarchy.hpp"


VerilogStudio::htree<string>
VerilogStudio::Hierarchy::createTree(string &TopName, shared_ptr<Parse> &pPar) {
    pParse = pPar;
    set<string> tempSet = pParse->GetModuleNameGuid(TopName);
    node_type *root = make_node(TopName, tempSet);
    tree_type::iterator iter(root);
    tree_type tr(root);

    for (auto it = tempSet.begin(); it != tempSet.end(); ++it) {
        iter = tr.insert(iter, make_node(*it, pParse->GetIncludeModuleSet(*it)));
    }

    return tr;
}

VerilogStudio::htree_node<string> *
VerilogStudio::Hierarchy::make_node(const string &ModuleName, const set<string> &ModuleNameSet) {
    node_type *node = new node_type;
    node->ModuleName = ModuleName;
    node->IncludeModules = ModuleNameSet;
    return node;
}


