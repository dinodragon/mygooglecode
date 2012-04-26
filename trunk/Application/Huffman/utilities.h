//
//  utilities.h
//  Huffman
//
//  Created by 飞 杨 on 12-4-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef Huffman_utilities_h
#define Huffman_utilities_h
#include <vector>
#include <sstream>
#include <string.h> 
#include <iostream>
#include <fstream>


int CommandLineParser(int argc,char *args[],std::vector<std::string> &inFiles,std::string &outFile);
bool Compress(const std::vector<std::string> & inFiles ,const std::string & outFile);
bool Decompress(const std::string & tarFile);
void PrintUsage();


#endif
