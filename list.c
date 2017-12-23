/*
1. INIT_LIST_HEAD:��������
2. list_add:������ͷ����ڵ�
3. list_add_tail:������β����ڵ�
4. list_del:ɾ���ڵ�
5. list_entry:ȡ���ڵ�
6. list_for_each:��������
*/
//��������
//������ͷ����ڵ�
//������β����ڵ�
//ɾ���ڵ�
//ȡ���ڵ�
//��������
#include <stdio.h>  
#include <stdlib.h>
#include "list.h"
enum res{
    Image,
    font,
    other
};
struct numlist{
    int index;                        //��Դ���
    enum res type;        //��Դ����
    struct list_head list;          //ָ��˫�����ǰ��ڵ��ָ��
    void *data;     //��Դ��
};
//struct numlist numhead;             //ͷ���
struct list_head head = LIST_HEAD_INIT(head);
struct list_head Image_head = LIST_HEAD_INIT(Image_head);
struct list_head Font_head = LIST_HEAD_INIT(Font_head);
struct list_head Other_head = LIST_HEAD_INIT(Other_head);
//ȫ����Դָ��
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
    list_for_each(pos,&head){    //��������
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
    list_for_each(pos,&head){    //��������
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
    //����ѭ��˫����ֻ����A��B�����ڵ�
    if(Pre1 == Post1 && Post1 == list2)
        return;
    //�����������
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
    //�ٿ�������һ�����
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
    list_for_each(pos,&head){    //��������
        p = list_entry(pos,struct numlist,list);
        printf("Node %d`s data:%d\n",i,p->index);
        i++;
    }
    printf("\n");
}
static int doublelist_init(void){
    //��ʼ��ͷ���
    struct numlist *listnode;//ÿ������������ʱʹ�õ�ָ��
    struct list_head *pos;
    struct numlist *p;
    int i;
 //   INIT_LIST_HEAD(&numhead.list);
    printf("head:%p  head->next:%p head->prev:%p\n",&head,head.next,head.prev);
    printf("head:%p  &head->next:%p &head->prev:%p\n",&head,&head.next,&head.prev);
    printf("doublelist is staring .......\n");
    printf("�������:\n");
    for(i = 0; i < N; i++){
        listnode = (struct numlist *)malloc(sizeof(struct numlist));
        if(listnode == NULL){
            printf("malloc failed\n");
            return -1;
        }
        listnode->index = i+1;
        list_add_tail(&listnode->list,&head);
        //��ӡ��ַ��Ϣ
        // printf("node %d has addad to the doublelist, \
        // listnode:%p,listnode->prev:%p,listnode->next:%p,\
        // &listnode->prev:%p,&listnode->next:%p\n", \
        // i+1,listnode,listnode->list.prev,listnode->list.next,\
        // &listnode->list.prev,&listnode->list.next);
    }
    i = 1;
    list_for_each(pos,&head){    //��������
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
    //����ɾ��N�����
    i = 1;
    list_for_each_safe(pos,n,&head){              //Ϊ�˰�ȫɾ���������еı���
        list_del(pos);                            //��˫������ɾ����ǰ���
        p = list_entry(pos,struct numlist,list);  //�õ���ǰ���ݽ����׵�ַ����ָ��
        free(p);                                  //�ͷŵ�ǰ�����ռ�õĿռ�
        printf("node %d has removed from the doublelist...\n",i++);
    }
    printf("doublelist is exit\n");
}
/**********************************************************
 *��������������滻
 *nodenum��Ҫ�滻�Ľ��
 *new    ���µĽ��
 *ע��   ���µĽ��Ҫ����malloc������ʹ���Ѿ����ڵģ��ᵼ���������
 *********************************************************/
static void doublelist_replace(int nodenum,struct list_head *new){
    struct list_head *pos,*n;
    struct numlist *p;
    int i = 1;
    if(list_empty(&head) || new == NULL) return ;
    list_for_each_safe(pos,n,&head){
        if(i == nodenum){
            list_del(pos);                            //��˫������ɾ����ǰ���
            p = list_entry(pos,struct numlist,list);  //�õ���ǰ���ݽ����׵�ַ����ָ��
            printf("p->index:%d\n",p->index);
            free(p);                                //�ͷŵ�ǰ�����ռ�õĿռ�
            list_add_tail(new,n);
            break;
        }
        i++;
    }
    i = 1;
    list_for_each(pos,&head){    //��������
        p = list_entry(pos,struct numlist,list);
        printf("Node %d`s data:%d\n",i,p->index);
        i++;
    }
    printf("\n");
}
int main(int argv, char *argc[])
{  
#if 0      //�������滻
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
#if 0    //������Դ���ƶ��ͽ���  OK
    doublelist_init();
    doublelist_move(3);       //�ƶ�������ͷ
    doublelist_move_tail(5);  //�ƶ�������β
    doublelist_move_swap(3,9);//�����㽻��  ����
    doublelist_move_swap(4,5);//�����㽻��  ����
#endif
#if 0    //����ɾ�������  OK
    printf("list_entry:%d\n",list_empty(&head));
    doublelist();
    printf("list_entry:%d\n",list_empty(&head));
    doublelist_exit();
    printf("list_entry:%d\n",list_empty(&head));

#endif
    return 0;  
}  
