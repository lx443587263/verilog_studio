//
// Created by 狂飙的西红柿 on 2022/9/2.
//

#include "DrawTree.hpp"



string VerilogStudio::DrawTree::get_node_name(string& root_str,string &leaf_str) {
    if(leaf_str.empty()){
        __node_name = root_str;
    } else{
        __node_name = leaf_str;
    }
    return __node_name;
}

Agnode_t *VerilogStudio::DrawTree::__draw_rb_node(Agraph_t *g, Agnode_t *_parent, char *name, char *label) {
    Agnode_t* _node = agnode(g,name,1);
    if(label != nullptr){
        // 如果注释下面这一句, 不设置label, 输出的图上结点显示name属性
        // 设置了label之后则会显示label
        agsafeset(_node, (char*)"label", label, "");
    }
    // 必须加这一句，否则下面的fillcolor属性设置无效
    agsafeset(_node, (char*)"style", "filled", "");

    agsafeset(_node, (char*)"fillcolor", "black", ""); // 填充黑色
    agsafeset(_node, (char*)"fontcolor", "white", ""); // 字体白色

    if (_parent != NULL)
    {
        agedge(g, _parent, _node, NULL, 1);
    }

    return _node;
}

void VerilogStudio::DrawTree::__draw_rb(Agraph_t *g, Agnode_t *_parent, VerilogStudio::htree_node<string> *parent_node, VerilogStudio::htree_node<string> *_node) {
    if(_node != nullptr){
        // 当前结点不是叶结点
        string temp = "";
        if(_node->children.empty()) {
            _parent = __draw_rb_node(g, _parent, (char*)get_node_name(_node->ModuleName, temp).data(), nullptr);
        }else{
            if(_node->KVInstModule.empty()){
                _parent = __draw_rb_node(g, _parent, (char*)get_node_name(_node->ModuleName, temp).data(), nullptr);
            }
            else{
                for(auto& it:_node->KVInstModule){
                    auto tempStr = it.first+":"+it.second;
                    _parent = __draw_rb_node(g, _parent, (char*)get_node_name(tempStr, temp).data(), nullptr);
                }
            }

        }


    }
    if(!_node->children.empty()){
        // 孩子不是叶结点
        for(auto& it:_node->children){
            __draw_rb(g, _parent, _node, it);
        }
    }/*else{
        string value,temp;
        for(auto &it:_node->KVInstModule)
            temp = it.first+":"+it.second;
        temp="lnil";
        __draw_rb_node(g, _parent, get_node_name(value,temp).data(), (char*)"NIL");
    }*/
}

void VerilogStudio::DrawTree::draw_rb(VerilogStudio::htree_node<string> *root,string filename) {
    // 1 创建上下文，存储graph和渲染方法等
    GVC_t * gvc = gvContext();
    // 2 创建一个 graph
    Agraph_t * g = agopen((char*)"g", Agdirected, 0);
    // 3 开始绘图
    __draw_rb(g, NULL, NULL, root);  // tree绘图方法
    // 4 指定输出的图像质量
    agsafeset(g, (char*)"dpi", "1000", "");
    // 5 指定布局方式，文档中有8种布局方式可选，这里选择"dot"生成树
    gvLayout(gvc, g, "dot");
    // 6 输出图片
    gvRenderFilename(gvc, g, "png", filename.c_str());
    // 7 释放内存
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
}

