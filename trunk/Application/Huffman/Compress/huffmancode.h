// Huffman.h: interface for the Huffman class. 
// 
////////////////////////////////////////////////////////////////////// 

#if !defined(NULL) 
#include <stdio.h> 
#endif 

#if !defined(AFX_HUFFMAN_H__B1F1A5A6_FB57_49B2_BB67_6D1764CC04AB__INCLUDED_) 
#define AFX_HUFFMAN_H__B1F1A5A6_FB57_49B2_BB67_6D1764CC04AB__INCLUDED_ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 

#define MAX_COUNT 65536 //最大计数值，大于此值时 
#define MAX_VALUE 255 //编码的最大值 
#define CODE_ESCAPE MAX_VALUE+1 //转义码 
#define CODE_FINISH MAX_VALUE+2 //结束码 
#define LIST_LENGTH MAX_VALUE+3 //编码列表长度 
#define SHRINK_FACTOR 2 //减小的比例，通过右移位实现 
#define LEFT 0 //左孩子索引 
#define RIGHT 1 //右孩子索引 
#define NOT_CHAR -1 //非字符 

#define TOP_BIT 7 //字符最高位 
#define BOTTOM_BIT 0 //字符最低位 
#define BUFFER_SIZE 81920 //缓冲区大小 

//输出函数 
typedef bool (Output)(unsigned char *s,int len); 

//哈夫曼树的节点定义 
typedef struct Hnode{ 
	int count;//计数器 
	int index;//父节点的孩子索引（0--左孩子，1--右孩子） 
	Hnode* child[2]; 
	Hnode* parent; 
	int value; 
}Hbtree; 

class Huffman 
{ 
private: 
	//输出一个解码的字符 
	int OutputChar(unsigned char c); 
	//从指定位置开始解码 
	int Decode(unsigned char c,int start); 
	//插入一个新节点 
	void InsertNewNode(int value); 
	//重新调整哈夫曼树构型 
	void RearrangeTree(); 
	//对各节点重新计数 
	int RecountNode(Hbtree *node); 
	//打印哈夫曼树节点 
	void PrintNode(Hbtree *node,int level); 
	//输出一个值的编码 
	int OutputEncode(int value); 
	//调节哈夫曼树节点使之平衡 
	void BalanceNode(Hbtree *node); 
	//输出一位编码 
	int OutputBit(int bit); 
	//释放哈夫曼树节点 
	void ReleaseNode(Hbtree *node); 
	//新建一个节点 
	Hbtree *NewNode(int value,int index, Hbtree *parent); 
	//输出函数地址 
	Output *output; 
	//哈夫曼树根地址 
	Hbtree *root; 
	//哈夫曼编码单元列表 
	Hbtree *list[LIST_LENGTH]; 
	//输出缓冲区 
	unsigned char buffer[BUFFER_SIZE]; 
	//缓冲区顶 
	int char_top,bit_top; 
	//收缩哈夫曼树参数 
	int max_count,shrink_factor; 
	//工作模式，true--编码，false--解码 
	bool mode; 
	//解码的当前节点 
	Hbtree *current; 
	int remain;//当前字符剩余的位数 
	unsigned char literal;//按位输出的字符 
	bool finished; 


public: 

	//解码指定长度的字符串 
	int Decode(unsigned char *s,int len); 
	//解码一个字符 
	int Decode(unsigned char c); 
	//打印哈夫曼树 
	void PrintTree(); 
	//编码指定长度的字符串 
	int Encode(unsigned char *s,int len); 
	//编码一个字符 
	int Encode(unsigned char c); 
	//清空缓冲区 
	int Flush(); 

	//output指输出函数，mode指工作模式，true--编码，false--解码 
	Huffman(Output *output,bool mode); 

	//析构函数 
	virtual ~Huffman(); 
}; 

#endif // !defined(AFX_HUFFMAN_H__B1F1A5A6_FB57_49B2_BB67_6D1764CC04AB__INCLUDED_) 