#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    void *data_p;  //兼容所有类型
    struct node_t *next;
}node_t;

typedef struct list_t
{
    node_t *header;

    //int size;    //元素个数

}list_t;

//初始化一个节点
#define INIT_NODE(node, ptr) \
    do {node->data_p = ptr; node->next = NULL}while(0)

//声明一个节点
#define DECLARE_NODE(name, ptr) \
    node_t *name = (node_t*)malloc(sizeof(node_t)); \
    name->data_p = ptr; \
    name->next = NULL;

//声明一个链表
#define DECLARE_LIST(list_name) \
    list_t *list_name = (list_t*)malloc(sizeof(list_t)); \
    INIT_LIST_HEAD(list_name);

//初始化一个链表
int INIT_LIST_HEAD(list_t *p)
{
    p->header = (node_t*)malloc(sizeof(node_t));
    p->header->next = NULL;

    return 0;
}

//在prev和next间插入一个新的结点
int _list_add(node_t *new_node, node_t *prev, node_t *next)
{
    prev->next = new_node;
    new_node->next = next;

    return 0;
}

//在head的后面加一个结点
int list_add(node_t *new_node, node_t *head)
{
    _list_add(new_node, head, head->next);

    return 0;
}

//在head链表的最后加一个结点
int list_add_tail(node_t *new_node, node_t *head)
{
    node_t *rear = NULL;
    node_t *tmp = NULL;

    rear = head;
    tmp = head->next;

    while(tmp)
    {
        rear = tmp;
        tmp = tmp->next;
    }

    _list_add(new_node, rear, rear->next);

    return 0;
}

//删除单链表上的任意一个节点，当然要有这个节点指针
int _list_del(node_t *entry, node_t *prev, node_t *next)
{
    //prev->entry->next
    prev->next = next;

    entry->data_p = NULL;
    entry->next = NULL;

    free(entry);

    return 0;
}

//从单项链表中删除某个节点
//肯定要遍历查找这个节点的前驱节点， 只需更改前驱节点的next指针即可
int list_del(node_t *entry, list_t *list)
{
    node_t *prev = NULL;
    node_t *cur = NULL;

    prev = list->header;
    cur = list->header->next;

    if(!cur)
    {
        printf("empty list\n");
        return -1;
    }

    while(cur)
    {
        if(cur == entry) break;
        prev = cur;
        cur = cur->next;
    }

    if(!cur)
    {
        printf("no such entry\n");
        return -1;
    }

    _list_del(entry, prev, entry->next);

    return 0;
}

//删除header后面的节点
int list_del_head(list_t *list)
{
    int ret = 0;

    ret = _list_del(list->header->next, list->header, list->header->next->next);

    return ret;
}

//倒置list ， 比如 header -> a -> b -> c 执行convert函数后 变成 header->c->b->a
int list_convert(list_t *list)
{
    node_t *tmp;

    tmp = list->header->next;
    list->header->next = NULL;

    if(!tmp)
    {
        printf("empty list\n");
        return -1;
    }

    while(tmp)
    {
        node_t *new_node = tmp->next;
        list_add(tmp, list->header);
        tmp = new_node;
    }

    return 0;

}

//释放链表
int list_free(list_t *list)
{
    node_t *tmp = list->header;

    while(tmp->next)
    {
        _list_del(tmp->next, tmp, tmp->next->next);
    }
    list->header = NULL;

    return 0;
}

int main()
{
    node_t *p = NULL;

    DECLARE_LIST(list);

    char *s1 = "zhanghello";
    char *s2 = "1234567890";
    char *s3 = "ABCDEFGHIJKLMN";

    DECLARE_NODE(p1, s1);
    DECLARE_NODE(p2, s2);
    DECLARE_NODE(p3, s3);

    //DECLARE_NODE(p1, "zhangyoudong");
    //DECLARE_NODE(p2, "1234567890");
    //DECLARE_NODE(p3, "ABCDEFGHIJKLMN");  //why error?


    list_add_tail(p1, list->header);
    list_add_tail(p2, list->header);
    list_add_tail(p3, list->header);

    p = list->header->next;
    while(p)
    {
        printf("%s\n", (char*)(p->data_p));
        p = p->next;
    }

    printf("\n\n");
    printf("I want to delete the node whose name is %s\n",(char*)(p2->data_p));
    list_del(p2,list);    //删除一个节点

    p = list->header->next;
    while(p)
    {
        printf("%s\n",(char *)(p->data_p));
        p=p->next;
    }

    //倒置链表
    printf("\n\n");
    list_convert(list);
    printf("I have converted the list\n");

    p = list->header->next;
    while(p)
    {
        printf("%s\n",(char *)(p->data_p));
        p=p->next;
    }

    return 0;
}
