//
// Created by 狂飙的西红柿 on 2022/8/26.
//

#ifndef VERILOG_STUDIO_B_OBJECT_HPP
#define VERILOG_STUDIO_B_OBJECT_HPP
#include <memory>

namespace VerilogStudio{
    /*************************************************************/
/* basic memory management, from which all objects inherited*/
/*************** categories of B-Object.*********************/
/************************************************************/
    using namespace std;

    enum class B_OBJ_CATEGORY
    {
        BLOCK = 0,
        Visitor,
        SERVICE,
        AtomicState,
        CmdLine,
    };
/******************************************************/
    template <typename T>
    class B_Object
    {
    public:
        /******************************************************/
        virtual B_OBJ_CATEGORY B_OBJ_Catetory(void) const = 0;

        /******************************************************/
        template <typename T1> static shared_ptr<T1> makeB_OBJ(void)
        {
            auto obj = dynamic_pointer_cast<B_Object<T>>(shared_ptr<T1>(new T1));
            if(!obj)
                return nullptr;

            obj->_thisB_Obj = obj;
            return dynamic_pointer_cast<T1>(obj);
        }

        /*************************************************************/
        static shared_ptr<T> makeB_OBJ(void)
        {
            auto obj = dynamic_pointer_cast<B_Object<T>>(std::shared_ptr<T>(new T));
            if(!obj)
                return nullptr;
            obj->_thisB_Obj = obj;
            return dynamic_pointer_cast<T>(obj);
        }

        /*************************************************************/
        shared_ptr<T> thisB_OBJ(void)
        {
            if (!this)
                return nullptr;
            return dynamic_pointer_cast<T>(this->_thisB_Obj.lock());
        }

        /*************************************************************/
        template <typename T1> shared_ptr<T1> thisB_OBJ(void)
        {
            if(!this)
                return nullptr;
            return std::dynamic_pointer_cast<T1>(this->_thisB_Obj.lock());
        }
    private:
        weak_ptr<B_Object> _thisB_Obj;
    };
}



#endif //VERILOG_STUDIO_B_OBJECT_HPP
