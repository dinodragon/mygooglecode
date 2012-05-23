#include <string>
#include <stdio.h>
#include <math.h>
#include "BitStringModifier.h"

void BitStringModifier::Modify(const char* in, size_t inlen,
                               const ctemplate::PerExpandData* per_expand_data,
                               ctemplate::ExpandEmitter* outbuf, const std::string& arg) const 
{
  int x = atoi(std::string(in, inlen).c_str());
  unsigned int len = atoi(arg.c_str() + 1);
  char buf[64];
  std::string sID = itoa(x,buf, 2);

  while(sID.size() < len)
    sID = "0" + sID;

  outbuf->Emit(sID);
}