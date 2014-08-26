#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <iostream>
#include <vector>
#include <string>
//#include <echo/rio.h>
/*
 *该类有三个函数，功能分别为
 *txtToDoc---转换txt文档为指定格式
 *readFile---遍历当前路径下的所有子目录和文档
 *buildOddset---把所有转换后的文档内容写入到一个库中
 *这里用到了一个vector容器，用来存放每一个转换过程中的文档内容
 */
class Document
{
    public:
        void txtToDoc(const std::string &);
        int readFile(char *);
        void buildLib(const std::string &, const std::string &);
        void buildIndex(const std::string &);
    private:
        std::vector<std::string> Vec_;
       // Rio Rio_;

};

#endif  /*_DOCUMENT_H_*/
