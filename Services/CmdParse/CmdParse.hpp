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
#include <stdlib.h>
#include "../../IService.hpp"
#include "../../Common/Supporting/cmdline.hpp"
#include "../Parse/Parse.hpp"
#include "../Hierarchy/Hierarchy.hpp"
#include "../DrawTree/DrawTree.hpp"

/*************************************************************/
namespace VerilogStudio {
    using namespace std;
    using namespace cmdline::detail;

    class CmdParse : public IService {
    public:
        void CmdLineParse(int argc, char *argv[]);

        vector<string> ReadFileToVec(const string &FileList);

        string FileNameStr();

        string GetENV();

        string CreateVerilogJson();

        string GetJsonPath();

    private:
        vector<string>              FileNameVec;
        string                      AllFileName;
        string                      TopModuleName;
        shared_ptr<Parse>           pParse;
        shared_ptr<Hierarchy>       pHierarchy;
        shared_ptr<DrawTree>        pDraw;
    };
}


#endif //VERILOG_STUDIO_CMDPARSE_HPP
