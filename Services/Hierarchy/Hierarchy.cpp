//
// Created by 狂飙的西红柿 on 2022/8/26.
//

#include "Hierarchy.hpp"

/**********************************************/
VerilogStudio::htree<string>
VerilogStudio::Hierarchy::CreateTree(string &TopName, shared_ptr<Parse> &pPar) {
    pParse = pPar;
    unordered_map<string, string> tempMap = pParse->GetModuleNameGuid(TopName);
    node_type *root = make_root(TopName, tempMap);
    tree_type::iterator iter(root);
    tree_type tr(root);

    for (auto it = tempMap.begin(); it != tempMap.end(); ++it) {
        unordered_map<string,string> tempUnMap;
        tempUnMap[it->first] = it->second;
        tr.insert(iter, make_node(it->first,tempUnMap, pParse->GetModuleNameGuid((*it).second)));
    }

    return tr;
}

//void VerilogStudio::Hierarchy::recursive(tree_type::iterator& iter, htree_node<string>& node) {
//    if(node.KVIncludeInstModule.empty()){
//        return;
//    }
//    tree_type::iterator tempiter;
//    node_type* tempnode;
//    for (auto& it : node.KVIncludeInstModule) {
//        tempnode = make_node(it.first, pParse->GetModuleNameGuid(it.second));
//        tempiter  = tr.insert(iter, tempnode);
//    }
//    recursive(tempiter,*tempnode);
//}

/**********************************************/
VerilogStudio::htree_node<string> *
VerilogStudio::Hierarchy::make_node(const string &ModuleName,const unordered_map<string,string>& KVModuleNameMap,const unordered_map<string, string>& IncludeModuleNameUnMap) {
    node_type *node = new node_type;
    node->KVInstModule = KVModuleNameMap;
    node->KVIncludeInstModule = IncludeModuleNameUnMap;
    node->ModuleName = ModuleName;
    for(auto it:IncludeModuleNameUnMap){
        node->children.emplace_back(make_node(it.first,IncludeModuleNameUnMap,pParse->GetModuleNameGuid(it.second)));
    }
    return node;
}

/**********************************************/
VerilogStudio::htree_node<string> *VerilogStudio::Hierarchy::make_root(const string &ModuleName, const unordered_map<string, string> &IncludeModuleNameUnMap) {
    node_type *root = new node_type;
    root->ModuleName = ModuleName;
    root->KVIncludeInstModule = IncludeModuleNameUnMap;
    return root;
}

/**********************************************/
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

/**********************************************/
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

/**********************************************/
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

/**********************************************/
vector<string> VerilogStudio::Hierarchy::MergePath(vector<string> path1, vector<string> path2) {
    resPath.clear();
    for(auto i = path1.rbegin();i!=path1.rend();++i){
        for(auto j = path2.begin();j!=path2.end();++j){
             if((*i)==(*j)){
                path2 = sliceVec<string>(j,path2.end());
                tempPath1 = sliceVec<string>(path1.rbegin(),i);
                reverse(tempPath1.end(),tempPath1.begin());
                break;
            }
        }
    }
    FlipModule = path2.at(1);
    resPath.insert(resPath.end(),tempPath1.begin(),tempPath1.end());
    resPath.insert(resPath.end(),path2.begin(),path2.end());
    if(!path2.empty())
        virTopModule = path2[0];

    return resPath;
}

/**********************************************/
string VerilogStudio::Hierarchy::GetFlipModule() {
    return FlipModule;
}

string VerilogStudio::Hierarchy::GetVirTopModule() {
    return virTopModule;
}






