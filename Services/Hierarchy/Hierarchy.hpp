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
        htree_node<string> *make_node(const string &ModuleName, const unordered_map<string,string>& KVModuleNameMap ,const unordered_map<string, string>& IncludeModuleNameUnMap);

        htree_node<string> *make_root(const string &ModuleName, const unordered_map<string, string>& IncludeModuleNameUnMap);

        htree<string> CreateTree(string &TopName, shared_ptr<Parse>& pPar);

        void ShowTree(htree<string> &tr);

        vector<string> DeepFirstSearch(htree_node<string>& Root, string& ModuleName, vector<string>& Path);

        void GetShortestPath(htree_node<string>& Root, string& start, string& end);

        vector<string> MergePath(vector<string> path1,vector<string> path2);

        string GetFlipModule();

        /*********************************************
        *******************create tree****************
        **********************************************/
        template<typename T>
        vector<T> slice(std::vector<T> const &v, int m, int n);


        template<typename T,typename U>
        vector<T> sliceVec(U m, U n);

    /********************************************/
    private:
        typedef htree_node<string>      node_type;
        typedef htree<string>           tree_type;
        shared_ptr<Parse>               pParse;
        vector<string>                  tempPath1;
        vector<string>                  tempPath2;
        vector<string>                  resPath;
        string                          FlipModule;
        bool flag               =       true;
    };

    template<typename T>
    vector<T> Hierarchy::slice(const vector<T> &v, int m, int n) {
        auto first = v.cbegin() + m;
        auto last = v.cbegin() + n + 1;

        std::vector<T> vec(first, last);
        return vec;
    }

    template<typename T,typename U>
    vector<T> Hierarchy::sliceVec(U m, U n)
    {
        vector<T> vec(m, n);
        return vec;
    }

}


#endif //VERILOG_STUDIO_HIERARCHY_HPP
