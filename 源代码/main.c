#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "sportmeet.h"
#include "listfun.h"

const char* position = "D:/socer.txt"; //�ɼ�������·��
//���Ժ���Ⱥ������ʱʹ�ã�
void testDataPrintPlayer(STPlayer* prnode)
{
	printf(" %d %d %s %s %d\n", prnode->schoolNumber, prnode->itemNumber, prnode->name, prnode->sex, prnode->rank);
}
void testDataPrintdata(STDataRrsult* prnode)
{
	printf("��%dѧУ %d %d %d\n",prnode->schoolNumber,  prnode->manTeamScore, prnode->womenTeamScore, prnode->schoolScore);
}

int main(void)
{
	printf("�����룺\n");
	printf("��Ŀ��ţ��������ձ�ѧУ�� ����\n");
	void* ptrToData = dataInput();
	printf("------------------------------\n");
	STDataRrsult* rhead = NULL;
	//list_print(ptrToData, (void*)testDataPrintPlayer);
	rhead = totalScoreFun(((STPlayer*)ptrToData));
	//rhead = list_sort(rhead);
	rhead = SelectSort(rhead);
	//list_print(rhead, (void*)testDataPrintdata);
	dataPrint((STPlayer*)ptrToData, rhead);
	char str[64];
	int flag = 1;
	printf("����Ҫ��ӡ�ɼ���������yes������Ҫ������no\n");
	do
	{
		rewind(stdin);						//��ջ�����
		scanf("%s", str);
		if (strcmp(str, "yes") == 0)
		{
			flag = 0;
			printSocer((STPlayer*)ptrToData, rhead, position);
		}
		else if (strcmp(str, "no") == 0)
		{
			flag = 0;
			printf("��ȡ���ɼ�����ӡ\n");
		}
		else	//�Ƿ������ж�
		{
			flag = 1;
			printf("�����쳣,���������룬yes or no.\n");
			rewind(stdin);						//��ջ�����
		}
			
	} while (flag);
	//��������
	list_destory(ptrToData);
	list_destory(rhead);

	return 0;
}