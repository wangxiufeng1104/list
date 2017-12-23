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
struct numlist{
    int index;                        //资源编号
    enum res type;        //资源类型
    struct list_head list;          //指向双链表的前后节点的指针
    void *data;     //资源域
};
//struct numlist numhead;             //头结点
struct list_head head = LIST_HEAD_INIT(head);
struct list_head Image_head = LIST_HEAD_INIT(Image_head);
struct list_head Font_head = LIST_HEAD_INIT(Font_head);
struct list_head Other_head = LIST_HEAD_INIT(Other_head);
//全部资源指针
struct list_head RES_Table[3] = {&Image_head,&Font_head,&Other_head};   
#define N 10
static void doublelist_move(int num){
    struct list_head *pos,*n;
    struct numlist *p;
    int i = 1;
    printf("doublelist_move\n");
    if(list_empty(&head)){
        return ;
    }
    list_for_each(pos,&head){
        if(i == num){
            list_move(pos,&head);
            break;
        }
        i++;
    }
    i = 1;
    list_for_each(pos,&head){    //遍历链表
        p = list_entry(pos,struct numlist,list);
        printf("Node %d`s data:%d\n",i,p->index);
        i++;
    }
    printf("\n");
}
static void doublelist_move_tail(int num){
    struct list_head *pos,*n;
    struct numlist *p;
    int i = 1;
    printf("doublelist_move_tail\n");
    if(list_empty(&head)){
        return ;
    }
    list_for_each(pos,&head){
        if(i == num){
            list_move_tail(pos,&head);
            break;
        }
        i++;
    }
    i = 1;
    list_for_each(pos,&head){    //遍历链表
        p = list_entry(pos,struct numlist,list);
        printf("Node %d`s data:%d\n",i,p->index);
        i++;
    }
    printf("\n");
}
void list_move_swap(struct list_head *list1, struct list_head *list2)
{
    if(list1==list2)
        return;
    struct list_head* Pre1 = list1->prev;
    struct list_head* Post1 = list1->next;
    struct list_head* Pre2 = list2->prev;
    struct list_head* Post2 = list2->next;
    //假如循环双链表只包含A、B两个节点
    if(Pre1 == Post1 && Post1 == list2)
        return;
    //考虑相邻情况
    if(Post1 == list2)
    {
        Pre1->next = list2;
        list2->prev = Pre1;
        list2->next = list1;
        list1->prev = list2;
        list1->next = Post2;
        Post2->prev = list1;
        return;
    }
    if(Post2 == list1)
    {
        Pre2->next = list1;
        list1->prev = Pre2;
        list1->next = list2;
        list2->prev = list1;
        list2->next = Post1;
        Post1->prev = list2;
        return;
    }
    //再考虑其它一般情况
    Pre1->next = list2;
    list2->prev = Pre1;
    list2->next = Post1;
    Post1->prev = list2;
    Pre2->next = list1;
    list1->prev = Pre2;
    list1->next = Post2;
    Post2->prev = list1;
}
static void doublelist_move_swap(int num1,int num2){
    struct list_head *pos,*pos1,*pos2;
    struct numlist *p;
    int i = 1;
    printf("doublelist_move_swap\n");
    if(num1>num2){
        int temp ;
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
    if(list_empty(&head)||num1 == num2){
        return ;
    }
    list_for_each(pos,&head){
        if(i == num1){
            pos1 = pos;
        }
        else if (i == num2){
            pos2 = pos;
        }
        i++;
    }
    list_move_swap(pos1,pos2);
    i = 1;
    list_for_each(pos,&head){    //遍历链表
        p = list_entry(pos,struct numlist,list);
        printf("Node %d`s data:%d\n",i,p->index);
        i++;
    }
    printf("\n");
}
static int doublelist_init(void){
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
        listnode->index = i+1;
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
        printf("Node %d`s data:%d\n",i,p->index);
        i++;
    }
    printf("\n");
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
/**********************************************************
 *功能描述：结点替换
 *nodenum：要替换的结点
 *new    ：新的结点
 *注意   ：新的结点要重新malloc，不能使用已经存在的，会导致链表断裂
 *********************************************************/
static void doublelist_replace(int nodenum,struct list_head *new){
    struct list_head *pos,*n;
    struct numlist *p;
    int i = 1;
    if(list_empty(&head) || new == NULL) return ;
    list_for_each_safe(pos,n,&head){
        if(i == nodenum){
            list_del(pos);                            //从双链表中删除当前结点
            p = list_entry(pos,struct numlist,list);  //得到当前数据结点的首地址，即指针
            printf("p->index:%d\n",p->index);
            free(p);                                //释放当前结点所占用的空间
            list_add_tail(new,n);
            break;
        }
        i++;
    }
    i = 1;
    list_for_each(pos,&head){    //遍历链表
        p = list_entry(pos,struct numlist,list);
        printf("Node %d`s data:%d\n",i,p->index);
        i++;
    }
    printf("\n");
}
int main(int argv, char *argc[])
{  
#if 0      //链表结点替换
    struct numlist *new;
    new = (struct numlist *)malloc(sizeof(struct numlist));
    if(new == NULL){
        printf("malloc failed\n");
        return -1;
    }
    new->index = 100;
    new->data = "Hello";
    doublelist_init();
    doublelist_replace(7,&(new->list));

#endif
#if 0    //链表资源的移动和交换  OK
    doublelist_init();
    doublelist_move(3);       //移动到链表头
    doublelist_move_tail(5);  //移动到链表尾
    doublelist_move_swap(3,9);//链表结点交换  任意
    doublelist_move_swap(4,5);//链表结点交换  相邻
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
