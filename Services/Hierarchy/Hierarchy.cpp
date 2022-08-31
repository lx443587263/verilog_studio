//
// Created by 狂飙的西红柿 on 2022/8/26.
//

#include "Hierarchy.hpp"


VerilogStudio::htree<string>
VerilogStudio::Hierarchy::CreateTree(string &TopName, shared_ptr<Parse> &pPar) {
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


void VerilogStudio::Hierarchy::ShowTree(VerilogStudio::htree<string> &tr) {
    map<int, vector<string>> MapVec;
    MapVec = tr.levelOrder(tr.root);

    for (auto &it: MapVec) {
        cout << it.first << endl;
        for (auto &it2: it.second) {
            cout << it2 << endl;
        }
    }
}


vector<string> VerilogStudio::Hierarchy::DeepFirstSearch(VerilogStudio::htree_node<string> &Root, string &ModuleName, vector<string> &Path) {
    Path.emplace_back(Root.ModuleName);
    if (Root.ModuleName == ModuleName) {
        flag = true;
        return Path;
    }

    if (Root.children.empty())
        flag = false;

    for (auto &it: Root.children) {
        vector<string> tPath = Path;
        Path = DeepFirstSearch(*it, ModuleName, tPath);
        if (!flag)
            continue;
        else
            return Path;
    }
    flag = false;
    return vector<string>();
}

void VerilogStudio::Hierarchy::GetShortestPath(VerilogStudio::htree_node<string> &Root, string &start, string &end) {
    vector<string> path1 = DeepFirstSearch(Root, start, tempPath1);
    vector<string> path2 = DeepFirstSearch(Root, end, tempPath2);
    if (!flag)
        cout << "can't find it" << endl;
    auto len1 = path1.size();
    auto len2 = path2.size();


//    for(auto i = path1.rbegin();i!=path1.rend();++i){
//        //cout << *i <<endl;
//        for(auto j = path2.begin();j!=path2.end();++j){
//             if((*i)==(*j)){
//                path2 = slice<string>(j,path2.end());
//                tempPath1 = slice<string>(path1.rbegin(),i);
//                reverse(tempPath1.begin(),tempPath1.end());
//                break;
//            }
//        }
//    }

    int i,j;
    for (i = len1; i >= 0 ; --i) {
        for (j = 0; j < len2; ++j) {
            if(path1[i]==path2[j]){
                path2 = slice(path2,j,len2-1);
                path1 = slice(path1,i+1,len1-1);
                reverse(path1.begin(),path1.end());
                break;
            }
        }
    }

    resPath.insert(resPath.end(),path1.begin(),path1.end());
    resPath.insert(resPath.end(),path2.begin(),path2.end());

    for(auto it : resPath){
        cout<<it<<endl;
    }
}


