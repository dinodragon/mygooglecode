#include <iostream>
#include <vector>
#include "utilities.h"
#include "filelist.h"

int main(int argc,char *args[])
{
	std::vector<std::string> inFiles;
	std::string tarFile;
	int mode = CommandLineParser(argc,args,inFiles,tarFile);
	switch(mode)
	{
        case 1:
			if (!Compress(inFiles,tarFile))
			{
				return 1;
			}
            break;
        case 2:
            if (!Decompress(tarFile))
			{
				return 1;
			}
            break;
        default:
            PrintUsage();
	}
    return 0;
}



