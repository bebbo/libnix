#include <exec/lists.h>
#include <clib/alib_protos.h>

VOID NewList(struct List *_NewList_list)
{
	_NewList_list->lh_TailPred = (struct Node *) _NewList_list;
	_NewList_list->lh_Head = (struct Node *) &_NewList_list->lh_Tail;
	_NewList_list->lh_Tail = 0;
}
