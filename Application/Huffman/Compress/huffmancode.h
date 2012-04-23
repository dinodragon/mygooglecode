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

#define MAX_COUNT 65536 //������ֵ�����ڴ�ֵʱ 
#define MAX_VALUE 255 //��������ֵ 
#define CODE_ESCAPE MAX_VALUE+1 //ת���� 
#define CODE_FINISH MAX_VALUE+2 //������ 
#define LIST_LENGTH MAX_VALUE+3 //�����б��� 
#define SHRINK_FACTOR 2 //��С�ı�����ͨ������λʵ�� 
#define LEFT 0 //�������� 
#define RIGHT 1 //�Һ������� 
#define NOT_CHAR -1 //���ַ� 

#define TOP_BIT 7 //�ַ����λ 
#define BOTTOM_BIT 0 //�ַ����λ 
#define BUFFER_SIZE 81920 //��������С 

//������� 
typedef bool (Output)(unsigned char *s,int len); 

//���������Ľڵ㶨�� 
typedef struct Hnode{ 
	int count;//������ 
	int index;//���ڵ�ĺ���������0--���ӣ�1--�Һ��ӣ� 
	Hnode* child[2]; 
	Hnode* parent; 
	int value; 
}Hbtree; 

class Huffman 
{ 
private: 
	//���һ��������ַ� 
	int OutputChar(unsigned char c); 
	//��ָ��λ�ÿ�ʼ���� 
	int Decode(unsigned char c,int start); 
	//����һ���½ڵ� 
	void InsertNewNode(int value); 
	//���µ��������������� 
	void RearrangeTree(); 
	//�Ը��ڵ����¼��� 
	int RecountNode(Hbtree *node); 
	//��ӡ���������ڵ� 
	void PrintNode(Hbtree *node,int level); 
	//���һ��ֵ�ı��� 
	int OutputEncode(int value); 
	//���ڹ��������ڵ�ʹ֮ƽ�� 
	void BalanceNode(Hbtree *node); 
	//���һλ���� 
	int OutputBit(int bit); 
	//�ͷŹ��������ڵ� 
	void ReleaseNode(Hbtree *node); 
	//�½�һ���ڵ� 
	Hbtree *NewNode(int value,int index, Hbtree *parent); 
	//���������ַ 
	Output *output; 
	//������������ַ 
	Hbtree *root; 
	//���������뵥Ԫ�б� 
	Hbtree *list[LIST_LENGTH]; 
	//��������� 
	unsigned char buffer[BUFFER_SIZE]; 
	//�������� 
	int char_top,bit_top; 
	//���������������� 
	int max_count,shrink_factor; 
	//����ģʽ��true--���룬false--���� 
	bool mode; 
	//����ĵ�ǰ�ڵ� 
	Hbtree *current; 
	int remain;//��ǰ�ַ�ʣ���λ�� 
	unsigned char literal;//��λ������ַ� 
	bool finished; 


public: 

	//����ָ�����ȵ��ַ��� 
	int Decode(unsigned char *s,int len); 
	//����һ���ַ� 
	int Decode(unsigned char c); 
	//��ӡ�������� 
	void PrintTree(); 
	//����ָ�����ȵ��ַ��� 
	int Encode(unsigned char *s,int len); 
	//����һ���ַ� 
	int Encode(unsigned char c); 
	//��ջ����� 
	int Flush(); 

	//outputָ���������modeָ����ģʽ��true--���룬false--���� 
	Huffman(Output *output,bool mode); 

	//�������� 
	virtual ~Huffman(); 
}; 

#endif // !defined(AFX_HUFFMAN_H__B1F1A5A6_FB57_49B2_BB67_6D1764CC04AB__INCLUDED_) 