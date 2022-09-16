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
#include "../../IService.hpp"

namespace VerilogStudio {
    /**********************************************/
    using namespace std;

    /*******************class**********************/
    class ChangeLine : public IService {
    public:
        ChangeLine() {}

        ~ChangeLine() {}

        void OpenFile(string &fileName);

        void RegexReplace(string &srcStr, string &desStr);

        void AddPort(string &fileName,string &PortName,string& portEnd,string& sourceModule);

        void AddInstPort(string& fileName,string &PortName);

        void RemoveTopModule(string &TopModuleName, vector<string> &Vec);

        void WriteFile(string &fileName);

        string FlipPort(string &PortName);

    /********************************************/
    private:
        string FileContent;
    };
}


#endif //VERILOG_STUDIO_CHANGELINE_HPP
