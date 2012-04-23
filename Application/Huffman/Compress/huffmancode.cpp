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

	//设置输出函数，当缓冲区满时，将调用该函数输出 
	this->output=output; 

	//初始化列表 
	for(i=0;i<LIST_LENGTH;i++)this->list[i]=NULL; 

	//初始化哈夫曼树 
	this->root=this->NewNode(NOT_CHAR,LEFT,NULL); 
	this->current=this->root; 
	tmp=this->NewNode(CODE_ESCAPE,RIGHT,root); 
	tmp->count=1; 
	tmp=this->NewNode(CODE_FINISH,LEFT,root); 
	tmp->count=0; 
	root->count=root->child[LEFT]->count+root->child[RIGHT]->count; 

	//设置缓冲区指针 
	this->char_top=BOTTOM_BIT; 
	this->bit_top=TOP_BIT; 
	this->buffer[0]=0; 

	//重构哈夫曼树的最大计数值 
	this->max_count=MAX_COUNT; 
	this->shrink_factor=SHRINK_FACTOR; 
	this->finished=false; 
} 

Huffman::~Huffman() 
{ 
	if(this->mode==true){//如果是编码 
		//输出结束码 
		this->OutputEncode(CODE_FINISH); 
		this->char_top++; 
	} 

	//强制清空缓冲区 
	this->Flush(); 

	//释放空间 
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

//输出一位编码 
int Huffman::OutputBit(int bit) 
{ 
	unsigned char candidates[]={1,2,4,8,16,32,64,128}; 

	if(bit!=0) 
		this->buffer[this->char_top] |= candidates[this->bit_top]; 
	this->bit_top--; 
	if(this->bit_top < BOTTOM_BIT){ 
		this->bit_top=TOP_BIT; 
		this->char_top++; 

		if(this->char_top >= BUFFER_SIZE){//输出缓冲区 
			this->output(this->buffer,BUFFER_SIZE); 
			this->char_top=0; 
		} 

		this->buffer[this->char_top]=0; 
	} 
	return 0; 
} 

//输出缓冲区 
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

	if(this->list[value]==NULL)//字符不存在于哈夫曼树中 
	{
		//输出转义码 
		this->OutputEncode(CODE_ESCAPE); 
		
		//输出字符 
		for(i=0;i<8;i++)
			this->OutputBit(value & candidates[i]); 
		this->InsertNewNode(value); 
	}
	else
	{ 
		//输出字符编码 
		this->OutputEncode(value); 
		//重新调整哈夫曼树 
		this->BalanceNode(this->list[value]->parent); 
	} 

	//重组哈夫曼树 
	if(this->root->count >= this->max_count) 
		this->RearrangeTree(); 

	return 0; 
} 

void Huffman::BalanceNode(Hbtree *node) 
{ 
	Hbtree *parent,*child,*brother; 
	int i,j; 

	parent=node->parent; 
	if(parent==NULL)return;//根节点无需调整 

	if(node->value==NOT_CHAR){//非叶子节点 
		child=node->child[LEFT]->count > node->child[RIGHT]->count ? 
			node->child[LEFT] : node->child[RIGHT]; 

		if(child->count > parent->count - node->count){ 
			//失衡 

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

//输出一个字符的编码 
int Huffman::OutputEncode(int value) 
{ 
	int stack[CODE_FINISH+2],top=0; 
	Hbtree *tmp=this->list[value]; 

	//输出编码 
	if(value<=MAX_VALUE){//字符 
		while(tmp!=NULL){ 
			stack[top++]=tmp->index; 
			tmp->count++; 
			tmp=tmp->parent; 
		} 
	}else{//控制码 
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

	//所有非控制码的计数值右移shrink_factor位，并删除计数值为零的节点 
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

	//重新计数 
	this->RecountNode(this->root); 

	//重新调整平衡 
	for(i=0;i<=MAX_VALUE;i++){ 
		if(this->list[i]!=NULL) 
			this->BalanceNode(this->list[i]->parent); 
	} 
} 

void Huffman::InsertNewNode(int value) 
{ 
	int i; 
	Hbtree *tmp,*tmp2; 

	//将字符加入哈夫曼树 
	tmp2=this->list[CODE_FINISH]; 
	tmp=this->NewNode(NOT_CHAR, tmp2->index, tmp2->parent); 
	tmp->child[LEFT]=tmp2; 
	tmp2->index=LEFT; 
	tmp2->parent=tmp; 

	tmp2=this->NewNode(value,RIGHT,tmp); 
	tmp->count=tmp->child[LEFT]->count+tmp->child[RIGHT]->count; 
	i=tmp2->count; 
	while((tmp=tmp->parent)!=NULL)tmp->count+=i; 
	//从底向上调整哈夫曼树 
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
	if(this->current==NULL){//转义状态下 
		while(this->remain >= 0 && i>=0){ 
			if((candidates[i] & value) !=0){ 
				this->literal |= candidates[this->remain]; 
			} 
			this->remain--; 
			i--; 
		} 

		if(this->remain < 0){//字符输出完毕 

			//输出字符 
			this->OutputChar(this->literal); 
			//将字符插入哈夫曼树 
			this->InsertNewNode(literal); 
			//重组哈夫曼树 
			if(this->root->count>=this->max_count) 
				this->RearrangeTree(); 

			//设置环境 
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

		if(tmp->value==NOT_CHAR){//中间节点 
			this->current=tmp; 
		}else{ 
			if(tmp->value<=MAX_VALUE){//编码内容 
				j=tmp->value; 
				this->OutputChar((unsigned char)j); 

				//修改计数器 
				tmp=this->list[j]; 
				while(tmp!=NULL){ 
					tmp->count++; 
					tmp=tmp->parent; 
				} 
				//调整平衡度 
				this->BalanceNode(this->list[j]->parent); 

				//重组哈夫曼树 
				if(this->root->count>=this->max_count) 
					this->RearrangeTree(); 

				//设置环境 
				this->current=this->root; 
			}else{ 
				if(tmp->value==CODE_ESCAPE){//转义码 
					this->current=NULL; 
					this->remain=7; 
					this->literal=0; 
				}else{//结束码 
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
	if(this->char_top>=BUFFER_SIZE){//输出缓冲区 
		this->output(this->buffer,BUFFER_SIZE); 
		this->char_top=0; 
	} 
	return 0; 
} 
