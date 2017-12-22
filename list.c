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
struct test_list  {  
    int index;            //��Դ���    
    enum res type;        //��Դ����
    struct list_head test;//������
    void *data;     //��Դ�� 
};
struct numlist{
    int num;                        //����
    struct list_head list;          //ָ��˫�����ǰ��ڵ��ָ��
};
//struct numlist numhead;             //ͷ���
struct list_head head = LIST_HEAD_INIT(head);
struct list_head Image_head = LIST_HEAD_INIT(Image_head);
struct list_head Font_head = LIST_HEAD_INIT(Font_head);
struct list_head Other_head = LIST_HEAD_INIT(Other_head);
//ȫ����Դָ��
struct list_head RES_Table[3] = {&Image_head,&Font_head,&Other_head};   
#define N 10
static int doublelist(void){
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
        listnode->num = i+1;
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
int main(int argv, char *argc[])
{  
#if 1    //������Դ���ƶ�

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
