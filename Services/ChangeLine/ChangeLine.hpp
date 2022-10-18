//
// Created by 狂飙的西红柿 on 2022/8/31.
//

#ifndef VERILOG_STUDIO_CHANGELINE_HPP
#define VERILOG_STUDIO_CHANGELINE_HPP

/************************************************
 *******************header***********************
 ************************************************/
#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../IService.hpp"
#include "../../spdlog/spdlog.h"
#include "../../spdlog/sinks/basic_file_sink.h"

namespace VerilogStudio {
    /**********************************************/
    using namespace std;

    /*******************class**********************/
    class ChangeLine : public IService {
        /**********************************************/
    public:
        ChangeLine() {}

        ~ChangeLine() {}

        void OpenFile(string &fileName);

        void AddPort(string &fileName,string &PortName,string& portEnd,string& sourceModule,int bracketsLocation, int endBracketsLocation);

        void AddInstPort(string& fileName,string &PortName,string &instModuleName);

        void AddToTopModule(string& fileName,string& PortName,string& portEnd,int bracketsLocation,int endBracketsLocation);

        void RemoveTopModule(string &TopModuleName, vector<string> &Vec);

        void WriteFile(string &fileName);

        string FlipPort(string &PortName);

        void GetTopModuleName(string& TopModuleName);

    /********************************************/
    private:
        string                              FileContent;
        string                              TopModuleFileName;
    };
}


#endif //VERILOG_STUDIO_CHANGELINE_HPP
