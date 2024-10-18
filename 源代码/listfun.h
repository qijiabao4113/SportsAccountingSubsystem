#ifndef  __MY_STLIST_H__ 
#define __MY_STLIST_H__

#define SUCCESS 0
#define FAILURE -1

//���Զ�����������node���ж�Ӧ
typedef struct Node {
	struct Node* next;
}STNode;

//����ͷ���
typedef struct LinkList {
	struct Node head;
	int size;				//���������С��Ϊ��ȡ�����Сʱ����Ҫÿ�α���(�������������������ʱ��)
}STLinkList;

void* linklist_init(void);														//��ʼ������
int linklist_push_back(void* temp_list_ptr, void* temp_data);					//β����
int linklist_push_front(void* temp_list_ptr, void* temp_data);					//ͷ����
void list_destory(void* temp_list_ptr);											//��������(����ڵ����Ϊ�ѿռ䣬���������Զ�����)
void list_print(void* temp_list_ptr, void* TEMP_PRINTLIST);						//����������Ҫ�ṩTEMP_PRINTLIST�Զ��������������
int list_get_size(void* temp_list_ptr);											//��ȡ������

#endif