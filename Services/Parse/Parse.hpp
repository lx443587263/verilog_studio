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
    };

}


#endif //VERILOG_STUDIO_PARSE_HPP
