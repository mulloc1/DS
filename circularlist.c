#include "circularlist.h"
#include <stdio.h>
#include <stdlib.h>

CircularList* createCircularList()
{
    CircularList  *pList;

    pList = malloc(sizeof(CircularList));
    if (!pList)
        return (FALSE);
    pList->headerNode.pLink = NULL;
    pList->headerNode.data = 0;
    pList->currentElementCount = 0;
    return (pList);
}

int addLLElement(CircularList* pList, int position, CircularNode element)
{
    int idx;
    CircularNode    *tmp;
    CircularNode    *tmp2;

    if (pList == NULL)
        return (FALSE);
    if (position < 0)
        return (FALSE);
    if (position > pList->currentElementCount)
        return (FALSE);
    if (pList->currentElementCount == 0)
    {
        tmp = malloc(sizeof(CircularNode));
        if (!tmp)
            return (FALSE);
        tmp->data = element.data;
        tmp->pLink = tmp;
        pList->headerNode.pLink = tmp;
    }
    else
    {
        idx = -1;
        tmp = pList->headerNode.pLink;
        while (++idx < position - 1)
            tmp = tmp->pLink;
        tmp2 = (CircularNode *)malloc(sizeof(CircularNode));
        if (!tmp2)
            return (FALSE);
        tmp2->data = element.data;
        tmp2->pLink = tmp->pLink;
        tmp->pLink = tmp2;
    }
    pList->currentElementCount++;
    return (TRUE);
}

int removeLLElement(CircularList* pList, int position)
{
    int             idx;
    CircularNode    *tmp;
    CircularNode    *rm;

	if (pList == NULL)
		return (FALSE);
    if (position < 0)
        return (FALSE);
    if (position >= pList->currentElementCount)
        return (FALSE);
    idx = -1;
    tmp = pList->headerNode.pLink;
    while (++idx < position - 2)
        tmp = tmp->pLink;
    rm = tmp->pLink;
    tmp->pLink = rm->pLink;
    free(rm);
    pList->currentElementCount--;
    return (TRUE);
}

CircularNode* getLLElement(CircularList* pList, int position)
{
    int             idx;
    CircularNode    *tmp;

    if (pList == NULL)
        return (FALSE);
    if (position < 0)
        return (FALSE);
    if (position >= pList->currentElementCount)
        return (FALSE);
    idx = -1;
    tmp = pList->headerNode.pLink;
    while (++idx < position - 1)
        tmp = tmp->pLink;
    return (tmp);
}

void clearCircularList(CircularList* pList)
{
    int             idx;
    CircularNode    *tmp;
    CircularNode    *tmp2;

    if (pList == NULL)
        return ;
	if (pList->currentElementCount == 0)
		return ;
    tmp = pList->headerNode.pLink;
    idx = -1;
    while (++idx < pList->currentElementCount - 1)
    {
        tmp2 = tmp->pLink;
        free(tmp);
        tmp = tmp2;
    }
    free(tmp);
    pList->currentElementCount = 0;
    pList->headerNode.pLink = NULL;
}

int getCircularListLength(CircularList* pList)
{
    if (pList == NULL)
        return (FALSE);
    return (pList->currentElementCount);
}

void deleteCircularList(CircularList* pList)
{
    if (pList == NULL)
        return ;
    if (pList->currentElementCount != 0)
        clearCircularList(pList);
    free(pList);
}

void displayCircularList(CircularList* pList)
{
    CircularNode    *temp;
    int             idx;

    if (pList == NULL)
        return ;
    if (pList->currentElementCount == 0)
    {
        printf("empty list!!\n");
        return ;
    }
    temp = pList->headerNode.pLink;
    idx = -1;
    while (++idx < pList->currentElementCount - 1)
    {
        printf("%d -> ", temp->data);
        temp = temp->pLink;
    }
    printf("%d\n", temp->data);
}

int main(void)
{
    CircularList *list;
    CircularNode *temp;
    CircularNode element;

    list = createCircularList();
    for (int i = 0; i < 10; i++)
    {
        element.data = i;
        element.pLink = NULL;
        addLLElement(list, i, element);
    }
    displayCircularList(list);
    removeLLElement(list, 5);
    displayCircularList(list);
    temp = getLLElement(list, 5);
    printf("data : %d\n", temp->data);
    printf("length : %d\n", getCircularListLength(list));
    clearCircularList(list);
    displayCircularList(list);
    deleteCircularList(list);
    return (0);
}
