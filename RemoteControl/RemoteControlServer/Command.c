#include "Command.h"
#include "Server.h"
#include <windows.h>

// Add an Element to the Command Stack
struct CommandList *Add_Command(struct CommandList *pNode,struct CommandDS Command)
{
	// Add an Item at the End of the List
	if (pNode->pNext = (struct CommandList *)malloc(sizeof(struct CommandList)))
	{
		pNode = pNode->pNext;
		strcpy(pNode->Command.szElement,Command.szElement);
		pNode->pNext = NULL;
		return pNode;
	}
	return NULL;
}

// Completely clear the CommandList of Commands
void Clear_Command(struct CommandList *pStart)
{
	struct	CommandList	*pPrev;
	struct	CommandList	*pNode;
	while (pNode = pStart->pNext)
	{
		pPrev = pStart;
		pPrev->pNext = pNode->pNext;
		free(pNode);
	}
}