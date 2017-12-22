#ifndef __LIST_H
#define __LIST_H
struct list_head {  
    struct list_head *next, *prev;  
};   
#define LIST_HEAD_INIT(name) { &(name),&(name) }                     //仅初始化
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)  //声明并初始化
static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
} 
#define list_entry(list_head, type, member_name) \
            (type *)((unsigned int)list_head - (unsigned int)(&(((type*)(0))->member_name)))    //链表的入口
#define list_for_each(pos, head) \
            for(pos = (head)->prev; pos != head; pos = pos->prev)     //遍历链表
// 这是函数同样也是遍历函数，只是这个函数考虑到了pos在遍历过程中有可能被删除掉  
// 如果还是和上面的遍历函数一样，那假若pos被删除了，则整个程序就会出错停止运行。而现在用个临时变量n  
// 可以把数据存放在n中，若pos被删除掉了，那pos = n 又会让pos有效。所以程序不会出错。
#define list_for_each_safe(pos, n, head) \
            for (pos = (head)->next, n = pos->next; pos != (head); \
            pos = n, n = pos->next) 
// 函数功能同上面那个，只是遍历是从head->prev(尾部)那端开始  
#define list_for_each_prev_safe(pos, n, head) \
        for (pos = (head)->prev, n = pos->prev; \
        prefetch(pos->prev), pos != (head); \
        pos = n, n = pos->prev)
static inline int list_empty(const struct list_head  * head) {
    return head->next  ==  head;     
}    //返回1表示链表为空，0表示不空
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

static void inline __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)  {  
    next->prev = new;  
    new->next = next;  
    new->prev = prev;  
    prev->next = new;  
} 
/*****************************头插***************************/
static void inline list_add(struct list_head *new, struct list_head *head){
    __list_add(new, head, head -> next);    
}
/*****************************尾插***************************/
static void inline list_add_tail(struct list_head *new, struct list_head *head){
    __list_add(new, head -> prev, head);
}
#endif