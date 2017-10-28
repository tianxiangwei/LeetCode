#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "test.h"
/*
 * You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * */
//输入两个倒序的多位数，输出它们的和
//Input:(2->4->3)+(5+6+4)=(7->0->8)
struct ListNode* addTwoNumbers(struct ListNode* l1,struct ListNode* l2) {
    struct ListNode *head=(struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *cur=NULL;
    struct ListNode *node=NULL;
	int plus=0,num=0;
	cur=head;
    while(l1||l2)
    {
        num=(l1?l1->val:0)+(l2?l2->val:0)+plus;
        if(num>=10)
        {
            num-=10;
            plus=1;
        }
        else
            plus=0;
        node=(struct ListNode *)malloc(sizeof(struct ListNode));
        node->val=num;
        cur->next=node;
        cur=cur->next;
        //printf("Node(%p:%d) cur:%p\n",node,node->val,cur);
        if(l1)
            l1=l1->next;
        if(l2)
            l2=l2->next;
    }
    if(plus)
    {
        node=(struct ListNode *)malloc(sizeof(struct ListNode));
        node->val=1;
        cur->next=node;
        //printf("Plus--Node(%p:%d) cur:%p",node,node->val,cur);
    }
    //printf("head:%p head->next:%p",head,head->next);
    return head;
}
void main()
{
	struct ListNode *result,*test1,*test2;
	result=addTwoNumbers(test1,test2);
	getchar();
}
