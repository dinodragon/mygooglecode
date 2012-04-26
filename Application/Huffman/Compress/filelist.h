//
//  filelist.h
//  Huffman
//
//  Created by 飞 杨 on 12-4-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Huffman_filelist_h
#define Huffman_filelist_h

#include <vector>
#include <iostream>

class FileList
{
public:
	typedef struct _FileStruct
	{
		std::string fileName;
		long fileSize;
	}FileStruct;
    
private:
	size_t offset;
	std::vector<FileStruct> filelist;
public:
	std::vector<FileStruct> GetList();
	void AddFile(std::string fileName);
	std::vector<unsigned char> serialization();
};

#endif
