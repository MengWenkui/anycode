
//list_head双链表结构定义
struct list_head
{
     struct list_head *prev;
     struct list_head *next;
};


//   链表的定义与初始化,宏的参数用小括号括起来防止出现扩展异常
#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
        struct list_head name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
        (ptr)->next = (ptr); (ptr)->prev = (ptr);} while(0)


//2.6版本中内联函数实现版本如下：
/*static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}*/

//通用链表操作-----添加结点

//1, _list_add在prev与next间插入_new结点
static inline void _list_add(struct list_head *_new, struct list_head *prev,
                               struct list_head *next)
{
    next->prev = _new;
    _new->next = next;
    _new->prev = prev;
    prev->next = _new;
}

//2, list_add在head后面插入结点_new
static inline void list_add(struct list_head *_new, struct list_head *head)
{
    _list_add(_new, head, head->next);
}

//3, 在head所指链表的末尾插入结点_new
static inline void list_add_tail(struct list_head *_new, struct list_head *head)
{
    _list_add(_new, head->prev, head);
}


/*
    通用链表操作-----删除结点，仅仅是把节点从双循环链表中拿掉，
    用户需要自己负责释放该节点对应的数据结构所占用的空间，而这
    个空间本来就是用户分配的
*/
//1, _list_del删除prev与next之间的结点
static inline void _list_del(struct list_head *prev, struct list_head *next)
{
    prev->next = next;
    next->prev = prev;
}
//2，list_del删除entry所指结点
/*对LIST_POISON1,LIST_POISON2的解释说明：
These are non-NULL pointers that will result
in page faults under normal circumstances, used to
 verify that nobody uses  non-initialized list entries.*/

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)

static inline void list_del(struct list_head *entry)
{
    _list_del(entry->prev, entry->next);
    entry->next = (struct list_head*)LIST_POISON1;  //常规思想将其设为NULL
    entry->prev = (struct list_head*)LIST_POISON2;
}

//3, 删除entry所指向的结点，同时调用LIST_INIT_HEAD()
//把被删除节点为作为链表头构建一个新的空双循环链表。
static inline void list_del_init(struct list_head *entry)
{
    _list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}


//通用链表操作-----移动结点
//1, list_move删除list结点，并将其插入到head结点之后
static inline void list_move(struct list_head *list, struct list_head *head)
{
    _list_del(list->prev, list->next);
    list_add(list, head);
}

//2, list_move_tail删除list结点，并将其插入到head所指链表的最后面
static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
    _list_del(list->prev, list->next);
    list_add_tail(list, head);
}


//通用链表操作-----链表判空
static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}

static inline int list_empty_careful(const struct list_head *head)
{
       struct list_head *next = head->next;
       return (next == head) && (next == head->prev);
}


//通用链表操作-----链表合并
//1, _list_splice讲list的头结点去掉，添加到head的后面, 对list不做非空检查
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

//2, list_splice讲list的头结点去掉，添加到head的后面, 对list做非空检查
static inline void list_splice(struct list_head *list, struct list_head *head)
{
    if(!list_empty(list))
        _list_splice(list, head);
}

//3, list_splice_init讲list的头结点去掉并初始化，添加到head的后面, 对list做非空检查
static inline void list_splice_init(struct list_head *list, struct list_head *head)
{
    if(!list_empty(list))
    {
        _list_splice(list, head);
        INIT_LIST_HEAD(list);
    }
}


//通用链表操作-----获取宿主对象指针


#define offsetof(TYPE, MEMBER) (&((TYPE *)0)->MEMBER)  //获取member在type中的偏移量

#define container_of(ptr, type, member) ({                \
        const typeof(((type*)0)->member) *_mptr = (ptr);    \
        (type*)((char*)_mptr - (char*) offsetof(type,member));})
        //ptr(member成员)的地址减去偏移量即为宿主结构的地址(指针)

#define list_entry(ptr, type, member) \
       container_of(ptr, type, member)

//将上述宏进行扩展，可得如下结果
 /*#define list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))*/


/*
详解：1.(type *)0->member为设计一个type类型的结构体，起始地址为0，
编译器将结构体的起始的地址加上此结构体成员变量的偏移得到此结构体成
员变量的地址，由于结构体起始地址为0，所以此结构体成员变量的偏移地址
就等于其成员变量在结构体内距离结构体开始部分的偏移量。
即：&(type *)0->member就是取出其成员变量的偏移地址。而其等于
其在结构体内的偏移量:即为：(size_t)(& ((type *)0)->member)
经过size_t的强制类型转换后，其数值为结构体内的偏移量。
该偏移量这里由offsetof()求出。
2.typeof( ( (type *)0)->member )为取出member成员的变量类型。
用其定义__mptr指针.ptr为指向该成员变量的指针。__mptr为member
数据类型的常量指针，其指向ptr所指向的变量处。
3.(char *)__mptr转换为字节型指针。
(char *)__mptr - offsetof(type,member) )用来求出
结构体起始地址（为char *型指针），
然后(type *)( (char *)__mptr - offsetof(type,member) )
在(type *)作用下进行将字节型的结构体起始指针转换为type *型的结构体起始指针。

这就是从结构体某成员变量指针来求出该结构体的首指针。
*/

//通用链表操作-------遍历
#define list_for_each(pos, head) \
       for(pos = (head)->next; pos != (head);pos = pos->next)


//反向遍历
#define list_for_each_prev(pos, head) \
       for(pos = (head)->prev; pos != (head); pos = pos->prev)

/*如果在遍历过程中，包含有删除或移动当前链接节点的操作，由于这些操作会
修改遍历指针，这样会导致遍历的中断。这种情况下，必须使用list_for_each_safe宏，
在操作之前将遍历指针缓存下来：*/

#define list_for_each_safe(pos, n, head) \
       for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

//通用链表操作-------正向遍历宿主对象
#define list_for_each_entry(pos, head, member)                       \
        for(pos = list_entry((head)->next, typeof(*pos), member);       \
            &pos->member != (head);        \
            pos = list_entry(pos->member.next, typeof(*pos), member))
//反向遍历宿主对象
#define list_for_each_entry_reverse(pos, head, member)                  \
        for(pos = list_entry((head)->prev, typeof(*pos), m+ember);     \
            &pos->member != (head);        \
            pos = list_entry(pos->member.prev, typeof(*pos), member))

//安全遍历宿主对象，遍历完允许删除遍历过的结点
#define list_for_each_entry_safe(pos, n, head, member)                   \
        for(pos = list_entry((head)->next, typeof(*pos), member),       \
            n = list_entry(pos->member.next, typeof(*pos), member);  \
            &pos->member != (head);                              \
            pos = n, n = list_entry(n->member.next, typeof(*n), member))


//应用实例

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

    //插入五个元素
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

