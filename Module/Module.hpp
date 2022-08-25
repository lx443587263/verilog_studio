//
// Created by 狂飙的西红柿 on 2022/8/24.
//

#ifndef VERILOG_STUDIO_MODULE_HPP
#define VERILOG_STUDIO_MODULE_HPP

/************************************************
 *******************header***********************
 ************************************************/
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>


/**********************************************/
using namespace std;

/*******************class**********************/
class Module {
public:
    /********************************************/
    Module() {}

    ~Module() {}

    /*********************************************
    *******************add element****************
    **********************************************/
    void AddModuleNameGuid(const string& guid, const string ModuleName);

    void AddPortName(const string &PortName);

    void AddIncludeModuleName(vector<string> &UnInstModuleName, vector<string> &InstModuleName);

    void AddParameter(vector<string> &ParameterName, vector<string> &ParameterValue);

    void AddInstPort(string& PortInstPort);

    void AddParameterOutSideMap(string& ParameterOutSideParameter);

    void AddPortDeclaration(string& PortDec);

    /*********************************************
    *******************get element****************
    **********************************************/
    void ShowInstNameUnMap();


private:
    vector<string>                          PortNameVec;
    unordered_multimap<string, string>      IncludeModuleName;
    unordered_map<string, string>           ParameterValueUnMap;
    unordered_map<string, string>           PortInstNameUnMap;
    unordered_map<string, string>           ParameterOutSideMap;
    vector<string>                          PortDeclaration;
    unordered_map<string, string>           ModuleNameGuid;

};


#endif //VERILOG_STUDIO_MODULE_HPP
