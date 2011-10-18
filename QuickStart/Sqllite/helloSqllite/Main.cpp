#include <iostream>
#include "sqlite3/sqlite3.h"


using namespace std;

//callback回调函数print_result_cb的编写，其中data为sqlite3_exec中的第四个参数，第二个参数是栏的数目，第三个是栏的名字，第四个为查询得到的值得。这两个函数输出所有查询到的结果

void print_row(int n_values, char** values)
{
  int i;
  for (i = 0; i < n_values; ++i) {
    if (i > 0) {
      printf("\t");
    }
    printf("%s", values[i]);
  }
  printf("\n");
}



int print_result_cb(void* data, int n_columns, char** column_values,char** column_names)
{
  static int column_names_printed = 0;
  if (!column_names_printed) {
    print_row(n_columns, column_names);
    column_names_printed = 1;
  }
  print_row(n_columns, column_values);
  return 0;
}



int main()
{
  sqlite3 *pDB = NULL;
  char * errMsg = NULL;
  //打开一个数据库，如果改数据库不存在，则创建一个名字为databaseName的数据库文件
  char databaseName[80] = "test.db";
  int rc = sqlite3_open(databaseName, &pDB);
  if(rc)
  {
    cout << " Open the database " << databaseName << " failed" << endl;
    return 1;
  }
  else
  {
    cout << "create the database successful!" << endl;
  }

  //插入一个表，返回值为SQLITE_OK为成功，否则输出出错信息
  //函数参数：第一个为操作数据库的指针，第二句为SQL命令字符串
  //第三个参数为callback函数，这里没有用，第四个参数为callback函数
  //中的第一个参数，第五个为出错信息
  rc = sqlite3_exec(pDB, "CREATE TABLE eng_to_chn(chinese QString, english QString)", 0, 0, &errMsg);
  if(rc == SQLITE_OK)
    cout << "create the chn_to_eng table successful!" << endl;
  else
    cout << errMsg << endl;

  //往表中添加数据

  char chn[]="jisuanji";
  char eng[]="computer";

  char sql[500];
  //定义一条参数SQL命令，其中chn,eng为需要插入的数据    
  sprintf_s(sql,sizeof(sql),"INSERT INTO eng_to_chn(chinese, english) VALUES(\'%s\', \'%s\')",chn,eng);
  //use the SQLITE C/C++ API to create and adjust a database.
  rc = sqlite3_exec(pDB,sql,0, 0, &errMsg);
  if(rc != SQLITE_OK)
    cout << errMsg << endl;

  //查询一条记录
  char target[50] = "computer";
  sprintf_s(sql,sizeof(sql), "SELECT chinese FROM eng_to_chn where english=\'%s\' ",target);
  rc = sqlite3_exec(pDB,sql,print_result_cb, 0, &errMsg);
  if(rc != SQLITE_OK)
  {
   cout << errMsg << endl;  
  }
}
