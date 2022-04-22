#include "doublylist.h"
#include <stdlib.h>
#include <stdio.h>

DoublyList* createDoublyList()
{
    DoublyList *tmp;

    tmp = (DoublyList *)malloc(sizeof(DoublyList));
    if (!tmp)
        return (FALSE);
    tmp->currentElementCount = 0;
    tmp->headerNode.data = 0;
    tmp->headerNode.pLLink = NULL;
    tmp->headerNode.pRLink = NULL;
    return (tmp);
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
    int idx;
    DoublyListNode  *tmp;
    DoublyListNode  *input;

    if (pList == NULL)
        return (FALSE);
    if (position < 0)
        return (FALSE);
    if (position > pList->currentElementCount)
        return (0);
    if (pList->currentElementCount == 0)
    {
        input = (DoublyListNode *)malloc(sizeof(DoublyListNode));
        if (!input)
            return (FALSE);
        *input = element;
        input->pRLink = input;
        input->pLLink = input;
        pList->headerNode.pRLink = input;
    }
    else
    {
        idx = -1;
        tmp = pList->headerNode.pRLink;
        while (++idx < position - 1)
            tmp = tmp->pRLink;
        input = (DoublyListNode *)malloc(sizeof(DoublyListNode));
        if (!input)
            return (FALSE);
        *input = element;
        input->pRLink = tmp->pRLink;
        input->pLLink = tmp;
        if (tmp->pRLink)
            tmp->pRLink->pLLink = input;
        tmp->pRLink = input;
    }
    pList->currentElementCount++;
    return (TRUE);
}

int removeDLElement(DoublyList* pList, int position)
{
    int             idx;
    DoublyListNode  *tmp;
    DoublyListNode  *rm;

    if (pList == NULL)
        return (FALSE);
    if (position < 0)
        return (FALSE);
	if (position >= pList->currentElementCount)
		return (FALSE);
    idx = -1;
    tmp = pList->headerNode.pRLink;
    while (++idx < position - 1)
        tmp = tmp->pRLink;
    rm = tmp->pRLink;
    tmp->pRLink = tmp->pRLink->pRLink;
    tmp->pRLink->pLLink = tmp;
    free(rm);
    pList->currentElementCount--;
    return (TRUE);
}

DoublyListNode* getDLElement(DoublyList* pList, int position)
{
    int             idx;
    int		    mid;
    DoublyListNode  *tmp;

    if (pList == NULL)
        return (FALSE);
    if (position < 0)
        return (FALSE);
	if (position >= pList->currentElementCount)
		return (FALSE);
    idx = -1;
    tmp = pList->headerNode.pRLink;
    mid = pList->currentElementCount / 2;
    if (position < mid)
        while (++idx < position)
            tmp = tmp->pRLink;
    else
        while (++idx < pList->currentElementCount - position)
            tmp = tmp->pLLink;
    return (tmp);
}

void clearDoublyList(DoublyList* pList)
{
    int             idx;
    DoublyListNode  *tmp;
    DoublyListNode  *tmp2;

    if (pList == NULL)
        return ;
	if (pList->currentElementCount == 0)
		return ;
    tmp = pList->headerNode.pRLink;
    idx = -1;
    while (++idx < pList->currentElementCount - 1)
    {
        tmp2 = tmp->pRLink;
        free(tmp);
        tmp = tmp2;
    }
    free(tmp);
    pList->currentElementCount = 0;
    pList->headerNode.pRLink = NULL;
    pList->headerNode.pLLink = NULL;
}

int getDoublyListLength(DoublyList* pList)
{
    if (pList == NULL)
        return (FALSE);
    return (pList->currentElementCount);
}

void deleteDoublyList(DoublyList* pList)
{
    if (pList == NULL)
        return ;
    if (pList->currentElementCount != 0)
        clearDoublyList(pList);
    free(pList);
}

void displayDoublyList(DoublyList* pList)
{
    DoublyListNode  *tmp;
    int             idx;

    if (pList == NULL)
        return ;
    if (pList->currentElementCount == 0)
    {
        printf("list is empty\n");
        return ;
    }
    tmp = pList->headerNode.pRLink;
    idx = -1;
    while (++idx < pList->currentElementCount - 1)
    {
        printf("%d -> ", tmp->data);
        tmp = tmp->pRLink;
    }
    printf("%d\n", tmp->data);
}

void revdisplayDoublyList(DoublyList* pList)
{
    DoublyListNode *tmp;
    int idx;

    if (pList == NULL)
        return ;
    if (pList->headerNode.pRLink == NULL)
        return ;
    if (pList->currentElementCount == 0)
    {
        printf("list is empty\n");
        return ;
    }
	tmp = pList->headerNode.pRLink;
    idx = -1;
    while (++idx < pList->currentElementCount - 1)
        tmp = tmp->pRLink;
    printf("Reverse : ");
    idx = -1;
    while (++idx < pList->currentElementCount - 1)
    {
        printf("%d -> ", tmp->data);
        tmp = tmp->pLLink;
    }
    printf("%d\n", tmp->data);
}

int main(void)
{
    DoublyList *list;
    DoublyListNode *temp;
    DoublyListNode element;

    list = createDoublyList();
    for (int i = 0; i < 10; i++)
    {
        element.data = i;
        element.pLLink = NULL;
        element.pRLink = NULL;
        addDLElement(list, i, element);
    }
    displayDoublyList(list);
    revdisplayDoublyList(list);
    removeDLElement(list, 5);
    displayDoublyList(list);
    temp = getDLElement(list, 5);
    printf("data : %d\n", temp->data);
    printf("length : %d\n", getDoublyListLength(list));
    clearDoublyList(list);
    displayDoublyList(list);
    deleteDoublyList(list);
    return (0);
}
