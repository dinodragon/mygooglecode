//调节器使用Demo
//http://www.cnblogs.com/zealsoft/archive/2008/10/15/1312137.html

#include <ctemplate/template.h>
#include <ctemplate/template_modifiers.h>


class BitStringModifier : public ctemplate::TemplateModifier {
  void Modify(const char* in, size_t inlen,
    const ctemplate::PerExpandData* per_expand_data,
    ctemplate::ExpandEmitter* outbuf, const std::string& arg) const;
};