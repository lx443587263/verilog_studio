//
// Created by 狂飙的西红柿 on 2022/8/19.
//

#ifndef VERILOG_STUDIO_PARSE_HPP
#define VERILOG_STUDIO_PARSE_HPP

/************************************************
 *******************header***********************
 ************************************************/
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <memory>
#include <algorithm>
#include "../Module/Module.hpp"
#include "../../rapidjson/document.h"
#include "../../rapidjson/filereadstream.h"
#include "../../rapidjson/stringbuffer.h"
#include "../../IService.hpp"


namespace VerilogStudio{
    /**********************************************/
    using namespace std;
    using namespace rapidjson;


/*******************class**********************/
    class finder
    {
    public:
        finder(const std::string &cmp_string) :s_(cmp_string){}
        bool operator ()(const unordered_map<string, string>::value_type &item)
        {
            return item.second == s_;
        }
    private:
        const std::string &s_;
    };

/*******************class**********************/
    class Parse: public IService{
        /********************************************/
    public:
        Parse() {}

        ~Parse() {}


        /*********************************************
        ****************parse verilog*****************
        **********************************************/
        void ReadJson(string &JsonFile);

        void ParseVerilog(string &FileName);

        string RepeatInstStruct(Value::MemberIterator &RepeatBitItr);

        void RepeatBitWidth(Value::MemberIterator &RepeatBitItr);

        void RepeatStruct(Value::MemberIterator &RepeatItr);

        void GetModuleName(Value::MemberIterator &ModuleNameItr);

        void GetPortName(Value::MemberIterator &PortNameItr);

        void GetRegName(Value::MemberIterator &RegNameItr);

        void GetPortDec(Value::MemberIterator &PortDecItr);

        void GetInstName(Value::MemberIterator &InstNameItr);

        void GetInstPort(Value::MemberIterator &InstPortItr);

        void GetParameter(Value::MemberIterator &ParameterItr);

        void GetParameterInst(Value::MemberIterator &ParameterItr);

        /*********************************************
        ****************create guid*******************
        **********************************************/
        unsigned int random_char();

        string generate_hex(const unsigned int len);

        /*********************************************
        ****************parse verilog*****************
        **********************************************/
        set<string> GetModuleNameGuid(string& ModuleName);

        set<string> GetIncludeModuleSet(const string& guid);

        string GetFileName(string& ModuleName);

        /********************************************/
    private:
        Document                                    doc;
        string                                      guid;
        unordered_map<string, string>               FileNameGuid;
        unordered_map<string,shared_ptr<Module>>    ModuleGuid;
        shared_ptr<Module>                          pModule;
        vector<string>                              UnInstModuleName;
        vector<string>                              InstModuleName;
        string                                      tempPortDec;
        vector<string>                              ModuleNames;
        unordered_map<string, vector<string>>       KVFileModule;
        unordered_map<string, string>               KVModuleGuid;
    };

}


#endif //VERILOG_STUDIO_PARSE_HPP
