#include "linkedlistpolynomial.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList* createLinkedList()
{
    LinkedList  *pList;

    pList = malloc(sizeof(LinkedList));
    if (!pList)
        return (FALSE);
    pList->headerNode.pLink = NULL;
    pList->headerNode.cnt = 0;
    pList->headerNode.exp = 0;
    pList->currentElementCount = 0;
    return (pList);
}

int addLLElement(LinkedList* pList, int position, ListNode element)
{
    int         idx;
    ListNode    *tmp;
    ListNode    *tmp2;

    if (position < 0)
        return (FALSE);
    if (position >= pList->currentElementCount)//맨 뒤
    {
        if (pList->headerNode.pLink == NULL)
        {
            tmp = malloc(sizeof(ListNode));
            if (!tmp)
                return (FALSE);
            *tmp = element;
            pList->headerNode.pLink = tmp;
        }
        else
        {
            tmp = pList->headerNode.pLink;
            while (tmp->pLink != NULL)
                tmp = tmp->pLink;
            tmp2 = malloc(sizeof(ListNode));
            if (!tmp2)
                return (FALSE);
            *tmp2 = element;
            tmp->pLink = tmp2;
        }
    }
    else
    {
        idx = -1;
        tmp = pList->headerNode.pLink;
        while (++idx < position - 1)
            tmp = tmp->pLink;
        tmp2 = malloc(sizeof(ListNode));
        if (!tmp2)
            return (FALSE);
        *tmp2 = element;
        tmp2->pLink = tmp->pLink;
        tmp->pLink = tmp2;
    }
    pList->currentElementCount++;
    return (TRUE);
}

int removeLLElement(LinkedList* pList, int position)
{
    int         idx;
    ListNode    *tmp;
    ListNode    *rm;

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

ListNode* getLLElement(LinkedList* pList, int position)
{
    int         idx;
    ListNode    *tmp;

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

void clearLinkedList(LinkedList* pList)
{
    ListNode    *tmp;
    ListNode    *tmp2;
    int         idx;

    tmp = pList->headerNode.pLink;
    idx = -1;
    while (++idx < pList->currentElementCount)
    {
        tmp2 = tmp->pLink;
        free(tmp);
        tmp = tmp2;
    }
    pList->currentElementCount = 0;
}

int getLinkedListLength(LinkedList* pList)
{
    return (pList->currentElementCount);
}

void deleteLinkedList(LinkedList* pList)
{
    if (pList->currentElementCount != 0)
        clearLinkedList(pList);
    free(pList);
}

void displayLinkedList(LinkedList* pList)
{
    ListNode *temp;

    if (pList->currentElementCount == 0)
    {
        printf("empty list!!\n");
        return ;
    }
    temp = pList->headerNode.pLink;
    while (temp->pLink != NULL)
    {
        printf("%dx^%d + ", temp->cnt, temp->exp);
        temp = temp->pLink;
    }
    printf("%dx^%d\n", temp->cnt, temp->exp);
}

LinkedList* addLinkedList(LinkedList* pList, LinkedList* qList)
{
    LinkedList  *tmp;
    ListNode    *p;
    ListNode    *q;
    ListNode    input;
    int         count;

    tmp = createLinkedList();
    p = pList->headerNode.pLink;
    q = qList->headerNode.pLink;
    count = 0;
    while (p && q)
    {
        if (p->exp == q->exp)
        {
            input.cnt = p->cnt + q->cnt;
            input.exp = p->exp;
            input.pLink = NULL;
            addLLElement(tmp, count++, input);
            p = p->pLink;
            q = q->pLink;
        }
        else if (p->exp > q->exp)
        {
            input.cnt = p->cnt;
            input.exp = p->exp;
            input.pLink = NULL;
            addLLElement(tmp, count++, input);
            p = p->pLink;
        }
        else
        {
            input.cnt = q->cnt;
            input.exp = q->exp;
            input.pLink = NULL;
            addLLElement(tmp, count++, input);
            q = q->pLink;
        }
    }
    while (p)
    {
        input.cnt = p->cnt;
        input.exp = p->exp;
        input.pLink = NULL;
        addLLElement(tmp, count++, input);
        p = p->pLink;
    }
    while (q)
    {
        input.cnt = q->cnt;
        input.exp = q->exp;
        input.pLink = NULL;
        addLLElement(tmp, count++, input);
        q = q->pLink;
    }
    return (tmp);
}

int main()
{   
    LinkedList *list;
    LinkedList *list2;
    LinkedList *sum;
    ListNode element;
    int i;

    list = createLinkedList();
    list2 = createLinkedList();
    i = 0;
    element.cnt = 5;
    element.exp = 4;
    element.pLink = NULL;
    addLLElement(list, i++, element);
    element.cnt = -3;
    element.exp = 2;
    element.pLink = NULL;
    addLLElement(list, i++, element);
    element.cnt = 2;
    element.exp = 1;
    element.pLink = NULL;
    addLLElement(list, i++, element);
    i = 0;
    element.cnt = 7;
    element.exp = 6;
    element.pLink = NULL;
    addLLElement(list2, i++, element);
    element.cnt = 4;
    element.exp = 4;
    element.pLink = NULL;
    addLLElement(list2, i++, element);
    element.cnt = 3;
    element.exp = 0;
    element.pLink = NULL;
    addLLElement(list2, i++, element);
    sum = addLinkedList(list, list2);
    displayLinkedList(sum);
}
