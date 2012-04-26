//
//  filelist.cpp
//  Huffman
//
//  Created by 飞 杨 on 12-4-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "filelist.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<FileList::FileStruct> FileList::GetList()
{
    return filelist;
}

void FileList::AddFile(std::string fileName)
{
    FileList::FileStruct fs;
    fs.fileName = fileName;
    fs.fileSize = 0;
    std::ifstream targetFile;
    targetFile.open(fileName.c_str(),std::ios::in|std::ios::binary);
    if (targetFile.is_open())
    {
        targetFile.seekg(0, std::ios::end);
        std::streamoff length = targetFile.tellg();
        fs.fileSize = length;
    }
    targetFile.close();
    filelist.push_back(fs);
}

std::vector<unsigned char> FileList::serialization()
{
    std::stringstream ssfiles;
    for (unsigned i = 0;i < filelist.size(); ++i)
    {
        ssfiles << ";" << filelist[i].fileName.c_str();
        ssfiles << "," << filelist[i].fileSize;
    }
    offset = ssfiles.str().size() + sizeof(offset);
    std::vector<unsigned char> ss;
    ss.resize(offset);
    memcpy((char *)&(ss[0]),(const char *)(&offset),sizeof(offset));
    memcpy((char *)&(ss[sizeof(offset)]),
           ssfiles.str().c_str(),
           ssfiles.str().length());
    return ss;
};