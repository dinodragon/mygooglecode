#include <iostream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <ctemplate/template.h>
#include <ctemplate/template_modifiers.h>
#include "BitStringModifier.h"

void test();

int  main( int  argc,  char ** argv)
{
  test();
}

void test()
{
  BitStringModifier bitStringModifier;
  /// 注册自定义的Modifier
  ctemplate::AddModifier("x-bitstring=", &bitStringModifier);

  ctemplate::TemplateDictionary dict("ctexample");
  dict.SetValue("NAME", "John Smith");
  dict.SetFormattedValue("AGE","%d",12);
  ctemplate::Template* tpl = ctemplate::Template::GetTemplate("./tpl1.tpl", ctemplate::DO_NOT_STRIP);
  std::string output;
  tpl->Expand(&output, &dict);
  std::cout << output;
  ctemplate::Template::ClearCache();
}

int test2()
{
  ctemplate::TemplateDictionary dict("ctexample");
  dict.SetValue("NAME", "John Smith");
  int  winnings = rand() % 100000;
  dict.SetIntValue("VALUE", winnings);
  ctemplate::TemplateDictionary *dict1 = dict.AddSectionDictionary( "IN_TABLE" );
  ctemplate::TemplateDictionary *dict2 = dict.AddSectionDictionary( "IN_TABLE" );
  dict1->SetValue("ITEM", "Lihaibo");
  dict1->SetFormattedValue("TAXED_VALUE", "%.2f", winnings * 0.83);
  dict2->SetValue("ITEM", "Qiyuehua");
  dict.SetValue("INCLUDE_VAR", "Qiyuehua");
  dict2->SetFormattedValue("TAXED_VALUE", "%.2f", winnings * 0.73);
  if  (1)
  {
    dict.ShowSection( "IN_TABLE" );
  }

  ctemplate::TemplateDictionary *dict3 = dict.AddIncludeDictionary("INCLUDED_TEMPLATE" );
  dict3->SetFilename("./example.tpl" );   
  dict3->SetValue("INCLUDE_VAR" , "This is a include template.");
  dict3->SetValue("NAME", "MEEE");
  dict3->SetIntValue("VALUE", winnings); 
  dict3->SetFormattedValue("TAXED_VALUE","%.2f", winnings *0.83);
  if(1) 
  {
    dict.ShowSection("IN_CA");
  }


  ctemplate::Template* tpl = ctemplate::Template::GetTemplate("./example.tpl", ctemplate::DO_NOT_STRIP);
  std::string output;
  tpl->Expand(&output, &dict);
  std::cout << output;
  ctemplate::Template::ClearCache();
  return  0;
}