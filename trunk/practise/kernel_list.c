
//list_head˫����ṹ����
struct list_head
{
     struct list_head *prev;
     struct list_head *next;
};


//   ����Ķ������ʼ��,��Ĳ�����С������������ֹ������չ�쳣
#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
        struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
        (ptr)->next = (ptr); (ptr)->prev = (ptr);} while(0)


//2.6�汾����������ʵ�ְ汾���£�
/*static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}*/

//ͨ���������-----��ӽ��

//1, _list_add��prev��next�����_new���
static inline void _list_add(struct list_head *_new, struct list_head *prev,
                               struct list_head *next)
{
    next->prev = _new;
    _new->next = next;
    _new->prev = prev;
    prev->next = _new;
}

//2, list_add��head���������_new
static inline void list_add(struct list_head *_new, struct list_head *head)
{
    _list_add(_new, head, head->next);
}

//3, ��head��ָ�����ĩβ������_new
static inline void list_add_tail(struct list_head *_new, struct list_head *head)
{
    _list_add(_new, head->prev, head);
}


/*
    ͨ���������-----ɾ����㣬�����ǰѽڵ��˫ѭ���������õ���
    �û���Ҫ�Լ������ͷŸýڵ��Ӧ�����ݽṹ��ռ�õĿռ䣬����
    ���ռ䱾�������û������
*/
//1, _list_delɾ��prev��next֮��Ľ��
static inline void _list_del(struct list_head *prev, struct list_head *next)
{
    prev->next = next;
    next->prev = prev;
}
//2��list_delɾ��entry��ָ���
/*��LIST_POISON1,LIST_POISON2�Ľ���˵����
These are non-NULL pointers that will result
in page faults under normal circumstances, used to
 verify that nobody uses  non-initialized list entries.*/

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

static inline void list_del(struct list_head *entry)
{
    _list_del(entry->prev, entry->next);
    entry->next = (struct list_head*)LIST_POISON1;  //����˼�뽫����ΪNULL
    entry->prev = (struct list_head*)LIST_POISON2;
}

//3, ɾ��entry��ָ��Ľ�㣬ͬʱ����LIST_INIT_HEAD()
//�ѱ�ɾ���ڵ�Ϊ��Ϊ����ͷ����һ���µĿ�˫ѭ������
static inline void list_del_init(struct list_head *entry)
{
    _list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}


//ͨ���������-----�ƶ����
//1, list_moveɾ��list��㣬��������뵽head���֮��
static inline void list_move(struct list_head *list, struct list_head *head)
{
    _list_del(list->prev, list->next);
    list_add(list, head);
}

//2, list_move_tailɾ��list��㣬��������뵽head��ָ����������
static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
    _list_del(list->prev, list->next);
    list_add_tail(list, head);
}


//ͨ���������-----�����п�
static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}

static inline int list_empty_careful(const struct list_head *head)
{
       struct list_head *next = head->next;
       return (next == head) && (next == head->prev);
}


//ͨ���������-----����ϲ�
//1, _list_splice��list��ͷ���ȥ������ӵ�head�ĺ���, ��list�����ǿռ��
static inline void _list_splice(struct list_head *list, struct list_head *head)
{
    struct list_head *first = list->next;
    struct list_head *last = list->prev;
    struct list_head *at = head->next;

    head->next = first;
    first->prev = head;

    last->next = at;
    at->prev = last;

}

//2, list_splice��list��ͷ���ȥ������ӵ�head�ĺ���, ��list���ǿռ��
static inline void list_splice(struct list_head *list, struct list_head *head)
{
    if(!list_empty(list))
        _list_splice(list, head);
}

//3, list_splice_init��list��ͷ���ȥ������ʼ������ӵ�head�ĺ���, ��list���ǿռ��
static inline void list_splice_init(struct list_head *list, struct list_head *head)
{
    if(!list_empty(list))
    {
        _list_splice(list, head);
        INIT_LIST_HEAD(list);
    }
}


//ͨ���������-----��ȡ��������ָ��


#define offsetof(TYPE, MEMBER) (&((TYPE *)0)->MEMBER)  //��ȡmember��type�е�ƫ����

#define container_of(ptr, type, member) ({                \
        const typeof(((type*)0)->member) *_mptr = (ptr);    \
        (type*)((char*)_mptr - (char*) offsetof(type,member));})
        //ptr(member��Ա)�ĵ�ַ��ȥƫ������Ϊ�����ṹ�ĵ�ַ(ָ��)

#define list_entry(ptr, type, member) \
       container_of(ptr, type, member)

//�������������չ���ɵ����½��
 /*#define list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))*/


/*
��⣺1.(type *)0->memberΪ���һ��type���͵Ľṹ�壬��ʼ��ַΪ0��
���������ṹ�����ʼ�ĵ�ַ���ϴ˽ṹ���Ա������ƫ�Ƶõ��˽ṹ���
Ա�����ĵ�ַ�����ڽṹ����ʼ��ַΪ0�����Դ˽ṹ���Ա������ƫ�Ƶ�ַ
�͵������Ա�����ڽṹ���ھ���ṹ�忪ʼ���ֵ�ƫ������
����&(type *)0->member����ȡ�����Ա������ƫ�Ƶ�ַ���������
���ڽṹ���ڵ�ƫ����:��Ϊ��(size_t)(& ((type *)0)->member)
����size_t��ǿ������ת��������ֵΪ�ṹ���ڵ�ƫ������
��ƫ����������offsetof()�����
2.typeof( ( (type *)0)->member )Ϊȡ��member��Ա�ı������͡�
���䶨��__mptrָ��.ptrΪָ��ó�Ա������ָ�롣__mptrΪmember
�������͵ĳ���ָ�룬��ָ��ptr��ָ��ı�������
3.(char *)__mptrת��Ϊ�ֽ���ָ�롣
(char *)__mptr - offsetof(type,member) )�������
�ṹ����ʼ��ַ��Ϊchar *��ָ�룩��
Ȼ��(type *)( (char *)__mptr - offsetof(type,member) )
��(type *)�����½��н��ֽ��͵Ľṹ����ʼָ��ת��Ϊtype *�͵Ľṹ����ʼָ�롣

����Ǵӽṹ��ĳ��Ա����ָ��������ýṹ�����ָ�롣
*/

//ͨ���������-------����
#define list_for_each(pos, head) \
       for(pos = (head)->next; pos != (head);pos = pos->next)


//�������
#define list_for_each_prev(pos, head) \
       for(pos = (head)->prev; pos != (head); pos = pos->prev)

/*����ڱ��������У�������ɾ�����ƶ���ǰ���ӽڵ�Ĳ�����������Щ������
�޸ı���ָ�룬�����ᵼ�±������жϡ���������£�����ʹ��list_for_each_safe�꣬
�ڲ���֮ǰ������ָ�뻺��������*/

#define list_for_each_safe(pos, n, head) \
       for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

//ͨ���������-------���������������
#define list_for_each_entry(pos, head, member)                       \
        for(pos = list_entry((head)->next, typeof(*pos), member);       \
            &pos->member != (head);        \
            pos = list_entry(pos->member.next, typeof(*pos), member))
//���������������
#define list_for_each_entry_reverse(pos, head, member)                  \
        for(pos = list_entry((head)->prev, typeof(*pos), m+ember);     \
            &pos->member != (head);        \
            pos = list_entry(pos->member.prev, typeof(*pos), member))

//��ȫ�����������󣬱���������ɾ���������Ľ��
#define list_for_each_entry_safe(pos, n, head, member)                   \
        for(pos = list_entry((head)->next, typeof(*pos), member),       \
            n = list_entry(pos->member.next, typeof(*pos), member);  \
            &pos->member != (head);                              \
            pos = n, n = list_entry(n->member.next, typeof(*n), member))


//Ӧ��ʵ��

#include <stdio.h>
#include <stdlib.h>

struct foo
{
    int from;
    struct list_head list;
    int to;
};
int main()
{
    struct foo *tmp;
    struct foo f_list;
    struct list_head *pos;
    int i;

    INIT_LIST_HEAD(&f_list.list);

    //�������Ԫ��
    for(i = 0; i < 5; i++)
    {
        tmp = (struct foo*)malloc(sizeof(struct foo));
        printf("enter from and to\n");
        scanf("%d%d", &tmp->from, &tmp->to);
        list_add(&(tmp->list), &f_list.list);
    }
    printf("\n");

    printf("traversing the list using list_for_each()\n");
    list_for_each(pos, &f_list.list)
    {
        tmp = list_entry(pos, struct foo, list);
        printf("from= %d to= %d\n", tmp->from, tmp->to);
    }

     printf("traversing the list using list_for_each_entry()\n");
     list_for_each_entry(tmp, &f_list.list, list)
     {
         printf("from= %d to= %d\n", tmp->from, tmp->to);
     }


    return 0;
}

