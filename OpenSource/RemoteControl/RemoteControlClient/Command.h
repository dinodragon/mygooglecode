#if !defined(COMMAND_H)
#define COMMAND_H

#include <windows.h>

// The Command Stack Data Structure
struct CommandDS
{
	char	szElement[81];
};

// The Command Stack Linked List
struct CommandList
{
	struct	CommandDS	Command;
	struct	CommandList	*pNext;
};

// Function Prototypes
struct	CommandList	*Add_Command(struct CommandList *pNode,struct CommandDS Command);
void				Clear_Command(struct CommandList *pStart);

#endif // #define COMMAND_H