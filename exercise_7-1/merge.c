#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// 定义posting 的结构，除了指向下一个节点之外，还有docid、gd域
struct posting {
    struct posting* next;
    float gd;
    int docid;
};

// 打印一个postings list的函数
void print_list(struct posting* p_ori)
{
    struct posting* p = p_ori;
    printf("(%.2f,%d)",p->gd,p->docid);
    while(p)
    {
        if(p->next)
            p = p->next;
        else
            break;
        printf(" -> (%.2f,%d)",p->gd,p->docid);
    }
    printf("\n");
}

// 随机创建一个指定长度的postings list
struct posting* create(int length)
{
    srand(time(NULL)+length);
    int r = rand() % 10 ;

    struct posting* head = (struct posting*)malloc(64);
    head->gd = 1-(float)r/1000;
    head->docid = r;
    head->next = NULL;
    struct posting* prev = head;
    struct posting* cur;
    for(int i = 0;i < length - 1; ++i)
    {
        //printf("%d,%f,%d\n",i,prev->gd,prev->docid);
        cur = (struct posting*)malloc(64);
        cur->gd = (float)(length + 10 + r - i) / (float)(length + 20);
        cur->docid = rand() % 100;
        cur->next = NULL;
        prev->next = cur;
        prev = prev->next;
    }
    return head;
}

// 将两个posting list 合并的函数，两个posting 都是按照gd降序排列的，合并后的list也一样
struct posting* combine(struct posting* p1, struct posting* p2)
{
    struct posting* result = (struct posting*)malloc(64);
    struct posting* prev = result;
    while(p1 && p2)
    {
        if(p1->gd > p2->gd)
        {
            prev->next = p1;
            prev->next->gd = p1->gd;
            prev->next->docid = p1->docid;
            p1 = p1->next;
        }
        else
        {
            prev->next = p2;
            prev->next->gd = p2->gd;
            prev->next->docid = p2->docid;
            p2 = p2->next;
        }
        prev = prev->next;
    }
    // 可能还有部分剩余的尾部，append
    while(p1)
    {
        prev->next = p1;
        prev->next->gd = p1->gd;
        prev->next->docid = p1->docid;
        p1 = p1->next;
        prev = prev->next;
    }
    while(p2)
    {
        prev->next = p2;
        prev->next->gd = p2->gd;
        prev->next->docid = p2->docid;
        p2 = p2->next;
        prev = prev->next;
    }

    return result->next;
}


int main()
{
    // 随机生成两个posting list
    struct posting* p1 = create(5);
    struct posting* p2 = create(4);

    printf("original p1 list:\n");
    print_list(p1);
    printf("original p2 list:\n");
    print_list(p2);

    printf("combine p1 and p2, the result is:\n");
    struct posting* comb = combine(p1,p2);
    print_list(comb);
    return 0;

}
