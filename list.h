#ifndef __LIST_H
#define __LIST_H


/**********************************************************
 *功能描述：链表结构体
 *********************************************************/
struct list_head {  
    struct list_head *next, *prev;  
};
/**********************************************************
 *功能描述：链表头节点相关操作
 *********************************************************/
#define LIST_HEAD_INIT(name) { &(name),&(name) }                     //仅初始化
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)  //声明并初始化
static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
} 
/**********************************************************
 *功能描述：链表节点插入操作
 *********************************************************/
static void inline __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)  {  
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}
/*****************************从链表头部插入节点   ***************************/
static void inline list_add(struct list_head *new, struct list_head *head){
    __list_add(new, head, head -> next);
}
/*****************************从链表尾部插入节点***************************/
static void inline list_add_tail(struct list_head *new, struct list_head *head){
    __list_add(new, head -> prev, head);
}
/**********************************************************
 *功能描述：链表节点删除操作
 *********************************************************/
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}
static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = NULL;
    entry->prev = NULL;
}
/**********************************************************
 *功能描述：链表节点移动操作
 *********************************************************/
// 这个函数首先调用__list_del()函数让list从链表上卸下了，并且让它的前后节点建立连接
// 然后调用list_add()函数 往头部插入该节点。函数的总体意思是：把某个位置上的节点移动到头节点后插入。  
 static inline void list_move(struct list_head *list, struct list_head *head)
{
    __list_del(list->prev, list->next);// 把节点从链表中卸下来
    list_add(list, head);// 把卸下来的链表插入打到头节点后面
}
// 这个函数和上个功能一样，这是插入的位置是在头节点的尾部
static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
    __list_del(list->prev, list->next); // 把节点从链表上卸下来
    list_add_tail(list, head);// 把卸下来的节点插入到链表头节点的尾部
}
/**********************************************************
 *功能描述：链表节点替换操作
 *********************************************************/
// 这是个替换的通用函数。就是让new节点替换old节点，但
// old指针的前驱和后继都没有改变，就是old节点还是挂在链表上的
static inline void list_replace(struct list_head *old,
        struct list_head *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}
// 这个函数首先调用list_replace() 函数用new替换了old的指针关系。
// 然后调用INIT_LIST_HEAD() 函数让old节点变成空节点
static inline void list_replace_init(struct list_head *old,
        struct list_head *new)
{
    list_replace(old, new);
    INIT_LIST_HEAD(old);
}
/**********************************************************
 *功能描述：链表判空操作和判断是否唯一节点操作
 *********************************************************/
// 判断list节点是否是该链表中最后的一个节点。
// 因为是环链表，所以若是最后一个节点。则该节点的后继为头节点：list->next = head
static inline int list_is_last(const struct list_head *list,
        const struct list_head *head)
{
    return list->next == head;
}
// 判断该链表是否是空链表，只有一个head节点
static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}  //返回1表示链表为空，0表示不空
 // 这个函数和上面的一样，是个判空函数。唯一不同的是这个函数可以防止该该链表
 // 同时正在被另外一个cpu操作，以导致head的前驱和后续不一样。其实换个角度来看
 // 该函数也可以用来判断该链表是否还在被其他CPU操作
static inline int list_empty_careful(const struct list_head *head)
{
    struct list_head *next = head->next;
    return (next == head) && (next == head->prev);
}
 // 这个函数是用来判断该链表中是否只有一个节点。
static inline int list_is_singular(const struct list_head *head)
{
    return !list_empty(head) && (head->next == head->prev);
}
/**********************************************************
 *功能描述：链表节点访问数据项操作
 *********************************************************/
#define list_entry(list_head, type, member_name) \
            (type *)((unsigned int)list_head - (unsigned int)(&(((type*)(0))->member_name)))    //链表的入口
/**********************************************************
 *功能描述：链表节点的遍历操作
 *********************************************************/
// 这是个遍历宏,从头往后遍历，算是个比较简单的函数
#define list_for_each(pos, head) \
for (pos = (head)->next; pos != (head); pos = pos->next)
// 这是个遍历宏,从尾往头遍历，算是个比较简单的函数。
#define list_for_each_prev(pos, head) \
for (pos = (head)->prev; pos != (head); \
        pos = pos->prev)
// 这是个设计比较巧妙的函数，同样也是遍历函数，只是这个函数考虑到了pos在遍历过程中有可能被删除掉
// 如果还是和上面的遍历函数一样，那假若pos被删除了，则整个程序就会出错停止运行。而现在用个临时变量n
// 可以把数据存放在n中，若pos被删除掉了，那pos = n 又会让pos有效。所以程序不会出错。
#define list_for_each_safe(pos, n, head) \
for (pos = (head)->next, n = pos->next; pos != (head); \
pos = n, n = pos->next)
// 函数功能同上面那个，只是遍历是从head->prev(尾部)那端开始
#define list_for_each_prev_safe(pos, n, head) \
for (pos = (head)->prev, n = pos->prev; \
    pos != (head);pos = n, n = pos->prev)
// 这是个有数据项的遍历，
//  typedef struct pos{
//         type date;
//     struct head_list member;
//         }pos;
//  list_entry(&ptr,typeof(pos),ptr);这是个由结构体变量中的某个成员而获取到
//  整个结构体变量的地址指针方法。typeof(pos)是获取到pos的类型
//  这里应该是在创建第一个节点时,让head = &pos->member
#define list_for_each_entry(pos, head, member) \
for (pos = list_entry((head)->next, typeof(*pos), member);\
     &pos->member != (head);\
    pos = list_entry(pos->member.next, typeof(*pos), member))
// 函数功能同上，只是从member.prev(尾部)开始遍历
#define list_for_each_entry_reverse(pos, head, member)\
for (pos = list_entry((head)->prev, typeof(*pos), member);\
    &pos->member != (head);\
    pos = list_entry(pos->member.prev, typeof(*pos), member))
// 这是问号表达式，当问号后一个选项为空时，则不做任何操作。
// 所以这是个判空宏，若pos存在，则不做操作，不存在则通过head来虚拟个pos节点
#define list_prepare_entry(pos, head, member) \
((pos) ? : list_entry(head, typeof(*pos), member))
// 这也是遍历数据项的函数，和前面的函数不同的是，这个函数不是从head开始遍历，
// 而是从任意的节点处遍历，直到到达头节点
#define list_for_each_entry_continue(pos, head, member) \
for (pos = list_entry(pos->member.next, typeof(*pos), member);\
    &pos->member != (head);\
    pos = list_entry(pos->member.next, typeof(*pos), member))
// 函数功能和上面的相同，只是遍历放向是从尾部开始遍历的
#define list_for_each_entry_continue_reverse(pos, head, member)\
for (pos = list_entry(pos->member.prev, typeof(*pos), member);\
    &pos->member != (head);\
    pos = list_entry(pos->member.prev, typeof(*pos), member))
// 这个函数功能和list_for_each_entry_continue()和像，只是遍历的起点不一样。
// list_for_each_entry_continue()是从该节点开始，这个函数则是从该节点的下个节点开始。
#define list_for_each_entry_from(pos, head, member) \
for (;&pos->member != (head);\
    pos = list_entry(pos->member.next, typeof(*pos), member))
// 这个和上个遍历删除节点的函数类似。多了个临时变量n，
// 所以可以防止pos在遍历时，被删除出现的错误。
#define list_for_each_entry_safe(pos, n, head, member)\
for (pos = list_entry((head)->next, typeof(*pos), member),\
n = list_entry(pos->member.next, typeof(*pos), member);\
    &pos->member != (head); \
    pos = n, n = list_entry(n->member.next, typeof(*n), member))
// 函数功能同上面那个，只是遍历是从某个节点开始
#define list_for_each_entry_safe_continue(pos, n, head, member) \
for (pos = list_entry(pos->member.next, typeof(*pos), member),\
n = list_entry(pos->member.next, typeof(*pos), member);\
    &pos->member != (head);\
    pos = n, n = list_entry(n->member.next, typeof(*n), member))
// 函数功能同上面那个，只是遍历是从某个节点的下个节点开始
#define list_for_each_entry_safe_from(pos, n, head, member) \
for (n = list_entry(pos->member.next, typeof(*pos), member);\
    &pos->member != (head);\
    pos = n, n = list_entry(n->member.next, typeof(*n), member))
// 同上个函数，只是从尾部开始
#define list_for_each_entry_safe_reverse(pos, n, head, member)\
for (pos = list_entry((head)->prev, typeof(*pos), member),\
n = list_entry(pos->member.prev, typeof(*pos), member);\
    &pos->member != (head); \
    pos = n, n = list_entry(n->member.prev, typeof(*n), member))
#endif
