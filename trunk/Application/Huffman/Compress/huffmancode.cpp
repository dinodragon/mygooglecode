// Huffman.cpp: implementation of the Huffman class. 
// 
////////////////////////////////////////////////////////////////////// 

#include "Huffmancode.h" 

////////////////////////////////////////////////////////////////////// 
// Construction/Destruction 
////////////////////////////////////////////////////////////////////// 

Huffman::Huffman(Output *output,bool mode) 
{ 
	Hbtree *tmp; 
	int i; 

	this->mode=mode; 

	//�����������������������ʱ�������øú������ 
	this->output=output; 

	//��ʼ���б� 
	for(i=0;i<LIST_LENGTH;i++)this->list[i]=NULL; 

	//��ʼ���������� 
	this->root=this->NewNode(NOT_CHAR,LEFT,NULL); 
	this->current=this->root; 
	tmp=this->NewNode(CODE_ESCAPE,RIGHT,root); 
	tmp->count=1; 
	tmp=this->NewNode(CODE_FINISH,LEFT,root); 
	tmp->count=0; 
	root->count=root->child[LEFT]->count+root->child[RIGHT]->count; 

	//���û�����ָ�� 
	this->char_top=BOTTOM_BIT; 
	this->bit_top=TOP_BIT; 
	this->buffer[0]=0; 

	//�ع�����������������ֵ 
	this->max_count=MAX_COUNT; 
	this->shrink_factor=SHRINK_FACTOR; 
	this->finished=false; 
} 

Huffman::~Huffman() 
{ 
	if(this->mode==true){//����Ǳ��� 
		//��������� 
		this->OutputEncode(CODE_FINISH); 
		this->char_top++; 
	} 

	//ǿ����ջ����� 
	this->Flush(); 

	//�ͷſռ� 
	this->ReleaseNode(this->root); 
} 

Hbtree * Huffman::NewNode(int value, int index, Hbtree *parent) 
{ 
	Hbtree *tmp=new Hbtree; 
	tmp->parent=parent; 
	tmp->child[0]=NULL; 
	tmp->child[1]=NULL; 
	tmp->count=(1 << SHRINK_FACTOR); 
	tmp->index=(index==0) ? 0 : 1; 
	tmp->value=value; 

	if(value!=NOT_CHAR)this->list[tmp->value]=tmp; 
	if(parent!=NULL)parent->child[tmp->index]=tmp; 
	return tmp; 
} 

void Huffman::ReleaseNode(Hbtree *node) 
{ 
	if(node!=NULL){ 
		this->ReleaseNode(node->child[LEFT]); 
		this->ReleaseNode(node->child[RIGHT]); 
		delete node; 
	} 
} 

//���һλ���� 
int Huffman::OutputBit(int bit) 
{ 
	unsigned char candidates[]={1,2,4,8,16,32,64,128}; 

	if(bit!=0) 
		this->buffer[this->char_top] |= candidates[this->bit_top]; 
	this->bit_top--; 
	if(this->bit_top < BOTTOM_BIT){ 
		this->bit_top=TOP_BIT; 
		this->char_top++; 

		if(this->char_top >= BUFFER_SIZE){//��������� 
			this->output(this->buffer,BUFFER_SIZE); 
			this->char_top=0; 
		} 

		this->buffer[this->char_top]=0; 
	} 
	return 0; 
} 

//��������� 
int Huffman::Flush() 
{ 
	this->output(this->buffer,this->char_top); 
	this->char_top=0; 
	return 0; 
} 

int Huffman::Encode(unsigned char c) 
{ 
	int value=c;
	int candidates[]={128,64,32,16,8,4,2,1};
	int	i;

	if(this->list[value]==NULL)//�ַ��������ڹ��������� 
	{
		//���ת���� 
		this->OutputEncode(CODE_ESCAPE); 
		
		//����ַ� 
		for(i=0;i<8;i++)
			this->OutputBit(value & candidates[i]); 
		this->InsertNewNode(value); 
	}
	else
	{ 
		//����ַ����� 
		this->OutputEncode(value); 
		//���µ����������� 
		this->BalanceNode(this->list[value]->parent); 
	} 

	//����������� 
	if(this->root->count >= this->max_count) 
		this->RearrangeTree(); 

	return 0; 
} 

void Huffman::BalanceNode(Hbtree *node) 
{ 
	Hbtree *parent,*child,*brother; 
	int i,j; 

	parent=node->parent; 
	if(parent==NULL)return;//���ڵ�������� 

	if(node->value==NOT_CHAR){//��Ҷ�ӽڵ� 
		child=node->child[LEFT]->count > node->child[RIGHT]->count ? 
			node->child[LEFT] : node->child[RIGHT]; 

		if(child->count > parent->count - node->count){ 
			//ʧ�� 

			i=!(node->index); 
			j=child->index; 
			node->count=parent->count - child->count; 
			brother=parent->child[i]; 

			node->child[j]=brother; 
			brother->index=j; 
			brother->parent=node; 

			parent->child[i]=child; 
			child->index=i; 
			child->parent=parent; 
		} 
	} 
	this->BalanceNode(parent); 
} 

//���һ���ַ��ı��� 
int Huffman::OutputEncode(int value) 
{ 
	int stack[CODE_FINISH+2],top=0; 
	Hbtree *tmp=this->list[value]; 

	//������� 
	if(value<=MAX_VALUE){//�ַ� 
		while(tmp!=NULL){ 
			stack[top++]=tmp->index; 
			tmp->count++; 
			tmp=tmp->parent; 
		} 
	}else{//������ 
		while(tmp!=NULL){ 
			stack[top++]=tmp->index; 
			tmp=tmp->parent; 
		} 
	} 
	top--; 
	while(top>0){ 
		this->OutputBit(stack[--top]); 
	} 

	return 0; 
} 

void Huffman::PrintNode(Hbtree *node,int level) 
{ 
	int i; 
	if(node){ 
		for(i=0;i<level*3;i++)printf(" "); 
		printf("%p P:%p L:%p R:%p C:%d",node,node->parent,node->child[0],node->child[1],node->count); 
		if(node->value!=NOT_CHAR)printf(" V:%d",node->value); 
		printf("\n"); 

		this->PrintNode(node->child[LEFT],level+1); 
		this->PrintNode(node->child[RIGHT],level+1); 
	} 
} 

int Huffman::Encode(unsigned char *s, int len) 
{ 
	for(int i=0;i<len;i++)
		this->Encode(s[i]); 
	return 0; 
} 

void Huffman::PrintTree() 
{ 
	this->PrintNode(this->root,0); 
} 

int Huffman::RecountNode(Hbtree *node) 
{ 
	if(node->value!=NOT_CHAR)return node->count; 
	node->count= 
		this->RecountNode(node->child[LEFT]) + 
		this->RecountNode(node->child[RIGHT]); 
	return node->count; 
} 

void Huffman::RearrangeTree() 
{ 
	int i,j,k; 
	Hbtree *tmp,*tmp2; 

	//���зǿ�����ļ���ֵ����shrink_factorλ����ɾ������ֵΪ��Ľڵ� 
	for(k=0;k<=MAX_VALUE;k++){ 
		if(this->list[k]!=NULL){ 
			tmp=this->list[k]; 
			tmp->count >>= this->shrink_factor; 
			if(tmp->count ==0){ 
				this->list[k]=NULL; 
				tmp2=tmp->parent; 
				i=tmp2->index; 
				j=!(tmp->index); 
				if(tmp2->parent!=NULL){ 
					tmp2->parent->child[i]=tmp2->child[j]; 
					tmp2->child[j]->parent=tmp2->parent; 
					tmp2->child[j]->index=i; 
				}else{ 
					this->root=tmp2->child[j]; 
					this->current=this->root; 
					this->root->parent=NULL; 
				} 
				delete tmp; 
				delete tmp2; 
			} 
		} 
	} 

	//���¼��� 
	this->RecountNode(this->root); 

	//���µ���ƽ�� 
	for(i=0;i<=MAX_VALUE;i++){ 
		if(this->list[i]!=NULL) 
			this->BalanceNode(this->list[i]->parent); 
	} 
} 

void Huffman::InsertNewNode(int value) 
{ 
	int i; 
	Hbtree *tmp,*tmp2; 

	//���ַ������������ 
	tmp2=this->list[CODE_FINISH]; 
	tmp=this->NewNode(NOT_CHAR, tmp2->index, tmp2->parent); 
	tmp->child[LEFT]=tmp2; 
	tmp2->index=LEFT; 
	tmp2->parent=tmp; 

	tmp2=this->NewNode(value,RIGHT,tmp); 
	tmp->count=tmp->child[LEFT]->count+tmp->child[RIGHT]->count; 
	i=tmp2->count; 
	while((tmp=tmp->parent)!=NULL)tmp->count+=i; 
	//�ӵ����ϵ����������� 
	this->BalanceNode(tmp2->parent); 
} 

int Huffman::Decode(unsigned char c) 
{ 
	this->Decode(c,7); 
	return 0; 
} 

int Huffman::Decode(unsigned char *s,int len) 
{ 
	int i; 
	for(i=0;i<len;i++)this->Decode(s[i]); 
	return 0; 
} 

int Huffman::Decode(unsigned char c, int start) 
{ 
	int value=c, 
		candidates[]={1,2,4,8,16,32,64,128}, 
		i,j; 
	Hbtree *tmp; 

	if(this->finished)return 0; 

	i=start; 
	if(this->current==NULL){//ת��״̬�� 
		while(this->remain >= 0 && i>=0){ 
			if((candidates[i] & value) !=0){ 
				this->literal |= candidates[this->remain]; 
			} 
			this->remain--; 
			i--; 
		} 

		if(this->remain < 0){//�ַ������� 

			//����ַ� 
			this->OutputChar(this->literal); 
			//���ַ������������ 
			this->InsertNewNode(literal); 
			//����������� 
			if(this->root->count>=this->max_count) 
				this->RearrangeTree(); 

			//���û��� 
			this->current=this->root; 
		} 
	}else{ 
		j=((value & candidates[i])!=0)?1:0; 
		tmp=this->current->child[j]; 
		i--; 
		while(tmp->value==NOT_CHAR && i>=0){ 
			j=((value & candidates[i])!=0)?1:0; 
			tmp=tmp->child[j]; 
			i--; 
		} 

		if(tmp->value==NOT_CHAR){//�м�ڵ� 
			this->current=tmp; 
		}else{ 
			if(tmp->value<=MAX_VALUE){//�������� 
				j=tmp->value; 
				this->OutputChar((unsigned char)j); 

				//�޸ļ����� 
				tmp=this->list[j]; 
				while(tmp!=NULL){ 
					tmp->count++; 
					tmp=tmp->parent; 
				} 
				//����ƽ��� 
				this->BalanceNode(this->list[j]->parent); 

				//����������� 
				if(this->root->count>=this->max_count) 
					this->RearrangeTree(); 

				//���û��� 
				this->current=this->root; 
			}else{ 
				if(tmp->value==CODE_ESCAPE){//ת���� 
					this->current=NULL; 
					this->remain=7; 
					this->literal=0; 
				}else{//������ 
					this->finished=true; 
					return 0; 
				} 
			} 
		} 

	} 

	if(i>=0)this->Decode(c,i); 
	return 0; 
} 

int Huffman::OutputChar(unsigned char c) 
{ 
	this->buffer[this->char_top++]=c; 
	if(this->char_top>=BUFFER_SIZE){//��������� 
		this->output(this->buffer,BUFFER_SIZE); 
		this->char_top=0; 
	} 
	return 0; 
} 
