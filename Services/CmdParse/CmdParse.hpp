//
// Created by 狂飙的西红柿 on 2022/9/6.
//

#ifndef VERILOG_STUDIO_CMDPARSE_HPP
#define VERILOG_STUDIO_CMDPARSE_HPP

/************************************************
 *******************header***********************
 ************************************************/
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "../../IService.hpp"
#include "../../Common/Supporting/cmdline.hpp"
#include "../Parse/Parse.hpp"
#include "../Hierarchy/Hierarchy.hpp"
#include "../DrawTree/DrawTree.hpp"
#include "../../Common/Supporting/ThreadPool.hpp"
#include "../ChangeLine/ChangeLine.hpp"

/*************************************************************/
namespace VerilogStudio {
    /*************************************************************/
    using namespace std;
    using namespace cmdline::detail;
    /***************************class*****************************/
    class CmdParse : public IService {
    public:
        void CmdLineParse(int argc, char *argv[]);

        vector<string> ReadFileToVec(const string &FileList);

        string FileNameStr();

        string GetENV();

        string CreateVerilogJson();

        string GetJsonPath();

        vector<string> split(const string& str,const string& delims);

        string& Trim(string& str);

    private:
        vector<string>              FileNameVec;
        string                      AllFileName;
        string                      TopModuleName;
        shared_ptr<Parse>           pParse;
        shared_ptr<Hierarchy>       pHierarchy;
        shared_ptr<DrawTree>        pDraw;
        shared_ptr<ChangeLine>      pChangeLine;
        vector<string>              ChangeLineContent;
    };
}


#endif //VERILOG_STUDIO_CMDPARSE_HPP
