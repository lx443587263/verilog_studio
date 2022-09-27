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
#include <set>

namespace VerilogStudio{
    /**********************************************/
    using namespace std;

    /*******************class**********************/
    class Module {
        /**********************************************/
    public:
        /********************************************/
        Module() {}

        ~Module() {}

        /*********************************************
        *******************add element****************
        **********************************************/
        void AddModuleName(const string& guid,const string& ModuleName);

        void AddPortName(const string &PortName);

        void AddIncludeModuleName(vector<string> &UnInstModuleName, vector<string> &InstModuleName);

        void AddIncludeModuleNameMap(vector<string> &InstModuleName, vector<string> &UnInstModuleName);

        void AddParameter(vector<string> &ParameterName, vector<string> &ParameterValue);

        void AddInstPort(string& PortInstPort);

        void AddParameterOutSideMap(string& ParameterOutSideParameter);

        void AddPortDeclaration(string& PortDec);

        void AddIncludeModule();

        void AddPortEnd(string portEnd);

        void AddBracketsLocation(int location);

        void AddEndBracketsLocation(int loaction);

        void AddPortActualLocation(int location);

        /*********************************************
        *******************get element****************
        **********************************************/
        void ShowInstNameUnMap();

        set<string> GetIncludeModuleName();

        unordered_multimap<string, string> GetIncludeModuleNameUnMap();

        unordered_map<string, string> GetIncludeModuleNameMap();

        string GetPortEnd();

        int GetBracketsLocation();

        int GetEndBracketsLocation();

        int GetPortActualLocation();

    /**********************************************/
    private:
        vector<string>                          PortNameVec;
        unordered_multimap<string, string>      IncludeModuleNameUnMap;
        unordered_map<string,string>            IncludeModuleNameMap;
        unordered_map<string, string>           ParameterValueUnMap;
        unordered_map<string, string>           PortInstNameUnMap;
        unordered_map<string, string>           ParameterOutSideMap;
        vector<string>                          PortDeclaration;
        set<string>                             IncludeModule;
        unordered_map<string, vector<string>>   ModuleNameGuid;
        vector<string>                          ModuleNameVec;
        string                                  PortEnd;
        int                                     BracketsLocation;
        int                                     EndBracketsLocation;
        int                                     PortActualLocation;
    };
}



#endif //VERILOG_STUDIO_MODULE_HPP
