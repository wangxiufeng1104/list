/*
1. INIT_LIST_HEAD:创建链表
2. list_add:在链表头插入节点
3. list_add_tail:在链表尾插入节点
4. list_del:删除节点
5. list_entry:取出节点
6. list_for_each:遍历链表
*/
//创建链表
//在链表头插入节点
//在链表尾插入节点
//删除节点
//取出节点
//遍历链表
#include <stdio.h>  
#include <stdlib.h>
#include "list.h"
enum res{
    Image,
    font,
    other
};
struct test_list  {  
    int index;            //资源编号    
    enum res type;        //资源类型
    struct list_head test;//链表域
    void *data;     //资源域 
};
struct numlist{
    int num;                        //数据
    struct list_head list;          //指向双链表的前后节点的指针
};
//struct numlist numhead;             //头结点
struct list_head head = LIST_HEAD_INIT(head);
struct list_head Image_head = LIST_HEAD_INIT(Image_head);
struct list_head Font_head = LIST_HEAD_INIT(Font_head);
struct list_head Other_head = LIST_HEAD_INIT(Other_head);
//全部资源指针
struct list_head RES_Table[3] = {&Image_head,&Font_head,&Other_head};   
#define N 10
static int doublelist(void){
    //初始化头结点
    struct numlist *listnode;//每次申请链表结点时使用的指针
    struct list_head *pos;
    struct numlist *p;
    int i;
 //   INIT_LIST_HEAD(&numhead.list);
    printf("head:%p  head->next:%p head->prev:%p\n",&head,head.next,head.prev);
    printf("head:%p  &head->next:%p &head->prev:%p\n",&head,&head.next,&head.prev);
    printf("doublelist is staring .......\n");
    printf("链表插入:\n");
    for(i = 0; i < N; i++){
        listnode = (struct numlist *)malloc(sizeof(struct numlist));
        if(listnode == NULL){
            printf("malloc failed\n");
            return -1;
        }
        listnode->num = i+1;
        list_add_tail(&listnode->list,&head);
        //打印地址信息
        // printf("node %d has addad to the doublelist, \
        // listnode:%p,listnode->prev:%p,listnode->next:%p,\
        // &listnode->prev:%p,&listnode->next:%p\n", \
        // i+1,listnode,listnode->list.prev,listnode->list.next,\
        // &listnode->list.prev,&listnode->list.next);
    }
    i = 1;
    list_for_each(pos,&head){    //遍历链表
        p = list_entry(pos,struct numlist,list);
        printf("Node %d`s data:%d\n",i,p->num);
        i++;
    }
    return 0;
}
static void doublelist_exit(void)
{
    struct list_head *pos,*n;
    struct numlist *p;
    int i;
    //依次删除N个结点
    i = 1;
    list_for_each_safe(pos,n,&head){              //为了安全删除结点而进行的遍历
        list_del(pos);                            //从双链表中删除当前结点
        p = list_entry(pos,struct numlist,list);  //得到当前数据结点的首地址，即指针
        free(p);                                  //释放当前结点所占用的空间
        printf("node %d has removed from the doublelist...\n",i++);
    }
    printf("doublelist is exit\n");
}
int main(int argv, char *argc[])
{  
#if 1    //链表资源的移动

#endif
#if 0    //链表删除和添加  OK
    printf("list_entry:%d\n",list_empty(&head));
    doublelist();
    printf("list_entry:%d\n",list_empty(&head));
    doublelist_exit();
    printf("list_entry:%d\n",list_empty(&head));

#endif
    return 0;  
}  
