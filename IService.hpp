//
// Created by 狂飙的西红柿 on 2022/8/26.
//

#ifndef VERILOG_STUDIO_ISERVICE_HPP
#define VERILOG_STUDIO_ISERVICE_HPP

/*************************************************************/
/**************************headers****************************/
/*************************************************************/
#include <vector>
#include "./Common/Foundation/B_Object.hpp"

namespace VerilogStudio{
    /*************************************************************/
    class IService:public B_Object<IService>
    {
    public:
        /*************************************************************/
        virtual B_OBJ_CATEGORY B_OBJ_Catetory(void) const final { return B_OBJ_CATEGORY::SERVICE;};
        /*************************************************************/
        ~IService(){};

        /*************************************************************/
    };
}


#endif //VERILOG_STUDIO_ISERVICE_HPP
