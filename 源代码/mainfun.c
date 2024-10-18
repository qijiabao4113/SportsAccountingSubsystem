#define _CRT_SECURE_NO_WARNINGS
#include "sportmeet.h"
#include "listfun.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int legalInput(TSTPlayer* node)								//�ж��Ƿ�Ϸ�����Ϸ�����1�Ƿ�����-1
{
	if ((ifstrdig(node->schoolNumber)) != 1)
	{
		printf("\nѧУ��������ַ��쳣������������\n");
		return -1;
	}
	if (strchadig(node->schoolNumber) < 1 || strchadig(node->schoolNumber) > MAXARR - 1)
	{
		printf("\nѧУ������뷶Χ�쳣����ȷ���뷶ΧΪ1����%d\n", MAXARR - 1);
		return -1;
	}		
	if ((ifstrdig(node->itemNumber)) != 1)
	{
		printf("\n��Ŀ��������ַ��쳣������������\n");
		return -1;
	}
	if ((ifstrdig(node->rank)) != 1)
	{
		printf("\n���������ַ��쳣������������\n");
		return -1;
	}
	if (strcmp(node->sex, "girl") && strcmp(node->sex, "boy") || strcmp(node->sex, "girl") && strcmp(node->sex, "boy"))
	{
		printf("\n�Ա������쳣����������ӦӢ�ĵ���: �У�boy��/Ů��girl��\n");
		return -1;
	}
	return 0;
}

int ifstrdig(const char* str)								//�ж��Ƿ�Ϊ����
{
	for (int i = 0; str[i] != '\0'; i++)
		if (!(isdigit(str[i])))								//�������ַ���-1
			return -1;
	return 1;
}

int strchadig(const char* str)								//�ַ���ת������
{
	int result = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		result *= 10;
	//ASII
		result += str[i] - '0';
	}
	return result;
}

void* dataInput(void)
{
	TSTPlayer tempNode;								//��ʱ�ṹ�����ڴ洢��ʱ��������Ϣ
	
	void* dataListHead = linklist_init();			//�����ʼ����������ͷ������ָ������ͷ��ָ��
	while(1)
	{
		int flag = 1;
		do
		{	
			scanf("%s", tempNode.itemNumber);
			//�ж��Ƿ���Ͻ�����������Ŀ���Ϊ0��tempNode�ڲ����ַ����洢��Ϣ
			//������Ҫstrchadig����tempNode.itemNumberת��Ϊ����
			if (strchadig(tempNode.itemNumber) == 0)
				return dataListHead;
			scanf("%s %s %s %s", tempNode.name, tempNode.sex, tempNode.schoolNumber, tempNode.rank);
			
			if (legalInput(&tempNode) == 0)		//�Ƿ�Ϸ����룬�Ϸ����뷨�����
				flag = 0;						//����Ϸ��ı���
			if (flag)							//�Ƿ�������ʾ��������
				printf("����������\n");
			rewind(stdin);						//��ջ�����
		} while (flag);							//�Ƿ�������Ҫ��������
		//�����ڴ洴������ڵ�
		STPlayer* dataNodep = (STPlayer*)malloc(sizeof(STPlayer));
		if (dataNodep == NULL)					//����ڴ�����״̬
		{
			printf("\nataInput error ������ԭ�������ڴ�ʧ��\n");
			return NULL;
		}
		//���ڴ�鸳ֵ
		dataNodep->itemNumber = strchadig(tempNode.itemNumber);
		strcpy(dataNodep->name, tempNode.name);
		strcpy(dataNodep->sex, tempNode.sex);
		dataNodep->rank = strchadig(tempNode.rank);
		dataNodep->schoolNumber = strchadig(tempNode.schoolNumber);
		//��������ڵ�
		linklist_push_back(dataListHead, dataNodep);
	}
}

//�÷ִ���
STDataRrsult* totalScoreFun(STPlayer* ptrHead)
{
	STLinkList* list_ptr = (STLinkList*)ptrHead;
	STDataRrsult* reslutHead = (STDataRrsult*)linklist_init();			//�����ʼ����������ͷ������ָ������ͷ��ָ��
	if (list_ptr == NULL)	//�쳣����
	{
		printf("\nfunction linklist_push_front : err\n");
		return NULL;
	}
	STNode* p = &(list_ptr->head);
	//����������Ա����
	while (p->next != NULL)
	{
		p = p->next;
		
		STPlayer* tempPtr = (STPlayer*)p;
		STDataRrsult* dataNodep = (STDataRrsult*)malloc(sizeof(STDataRrsult));
		if (dataNodep == NULL)					//����ڴ�����״̬
		{
			printf("\nataInput error ������ԭ�������ڴ�ʧ��\n");
			return NULL;
		}
		//�ڴ�����
		memset(dataNodep, 0, sizeof(STDataRrsult));
		//����ʱ�ڴ�츳ֵ
		if (strcmp(tempPtr->sex, "boy") == 0)
			dataNodep->manTeamScore += getSocer(tempPtr);
		if (strcmp(tempPtr->sex, "girl") == 0)
			dataNodep->womenTeamScore += getSocer(tempPtr);
		dataNodep->schoolNumber = tempPtr->schoolNumber;
		dataNodep->schoolScore = dataNodep->manTeamScore + dataNodep->womenTeamScore;
		//������µĽڵ��ǾͲ���÷�����������
		if (!findThisNode(dataNodep, reslutHead))   
			linklist_push_front(reslutHead, dataNodep);
		else //��ֹ�ڴ�й©
			free(dataNodep);
	}
	return reslutHead;
}

void dataPrint(STPlayer* nodeSP, STDataRrsult* nodeSD)
{
	STLinkList* list_ptrsp = (STLinkList*)nodeSP;
	STLinkList* list_ptrsd = (STLinkList*)nodeSD;
	STNode* psp = &(list_ptrsp->head);
	STNode* psd = &(list_ptrsd->head);
	STNode* tpsp = psp;
	STNode* tpsd = psd;
	STDataRrsult* ttpsd = NULL;
	STPlayer* ttpsp = NULL;
	printf("ѧУ�� ��Ŀ�� ����  �Ա�  ���� �÷�\n");
	while (tpsd->next != NULL)
	{
		//��������
		tpsd = tpsd->next;
		tpsp = psp;
		
		while (tpsp->next != NULL)
		{
			tpsp =tpsp->next;
			//����ת���������ݱȽ�
			ttpsd = (STDataRrsult*)tpsd;
			ttpsp = (STPlayer*)tpsp;
			////������ʾ��������
			//���
			//ѧУ��    ��Ŀ��      ����      �Ա�      ����      �÷�
				// ѧУ�ĳɼ���
				//1��ѧУ�������ܷ�Ϊ��
				//1��ѧУ��Ů���ܷ�Ϊ��
				//1��ѧУ�����ܷ�Ϊ��
				//����n��ѧУ�ĳɼ����ܷ�
			if (ttpsd->schoolNumber == ttpsp->schoolNumber)			
				printf("%-7d %-5d %-5s %-6s %-4d %-10d\n", ttpsp->schoolNumber, ttpsp->itemNumber, ttpsp->name, ttpsp->sex,  ttpsp->rank, getSocer(ttpsp));
		}
		printf("%d��ѧУ�������ܷ�Ϊ %-3d\n%d��ѧУ��Ů���ܷ�Ϊ %-3d\n%d��ѧУ�����ܷ�Ϊ   %-3d\n",ttpsd->schoolNumber, ttpsd->manTeamScore, ttpsd->schoolNumber, ttpsd->womenTeamScore, ttpsd->schoolNumber, ttpsd->schoolScore);
		//��ֹĩ�ж������
		if (tpsd->next != NULL)
			printf("\nѧУ�� ��Ŀ�� ����  �Ա�  ���� �÷�\n");
	}
}

//Ѱ��������ݽڵ�
bool findThisNode(STDataRrsult* node, STDataRrsult* ptrHead)
{
	STLinkList* list_ptr = (STLinkList*)ptrHead;
	if (list_ptr == NULL)
	{
		printf("\nfunction findThisNode : err\n");
		return false;
	}

	STNode* p = &(list_ptr->head);
	while (p->next != NULL)
	{
		p = p->next;
		STDataRrsult* tempNodePtr = (STDataRrsult*)p;
		STDataRrsult* dataNodep = tempNodePtr;		
		if (node->schoolNumber == tempNodePtr->schoolNumber)
		{
			//����������ݽڵ�ֱ�Ӽ�������
			tempNodePtr->schoolScore += node->schoolScore;
			tempNodePtr->manTeamScore += node->manTeamScore;
			tempNodePtr->womenTeamScore += node->womenTeamScore;
			return true;
		}		
	}
	//�������ݽڵ㲻����ʱ����false
	return false;
}

int getSocer(STPlayer* node)
{
	//��ȡ�÷����
	if (node->itemNumber % 2 == 0)
	{
		if (node->rank == 3)
			return 2;
		if (node->rank == 2)
			return 3;
		if (node->rank == 1)
			return 5;
	}
	else
	{
		if (node->rank == 5)
			return 1;
		if (node->rank == 4)
			return 2;
		if (node->rank == 3)
			return 3;
		if (node->rank == 2)
			return 5;
		if (node->rank == 1)
			return 7;
	}
	return 0;
}

STDataRrsult* SelectSort(STDataRrsult* t)
{
	//��������
	STNode* p, * q, * small, * L = (STNode*)t;
	STDataRrsult* tq, * ts;
	int temp;
	int tempsocer;

	for (p = L->next; p->next != NULL; p = p->next)    /*ÿ��ѭ�����ҳ�һ����Сֵ������Сֵ��������һλ��Ȼ��ָ������ƶ�һλ*/
	{
		small = p;
		for (q = p->next; q; q = q->next)    /*��ǰ���������ҳ���С�Ľڵ�*/
		{
			tq = (STDataRrsult*)q;
			ts = (STDataRrsult*)small;
			if (tq->schoolNumber< ts->schoolNumber)
				small = q;
		}
		if (small != p)
		{
			//����ת����������ת��
			tq = (STDataRrsult*)p;
			ts = (STDataRrsult*)small;
			//�������ݰ�
			temp = tq->schoolNumber;
			tq->schoolNumber = ts->schoolNumber;
			ts->schoolNumber = temp;

			tempsocer = tq->manTeamScore;
			tq->manTeamScore = ts->manTeamScore;
			ts->manTeamScore = tempsocer;
			
			tempsocer = tq->womenTeamScore;
			tq->womenTeamScore = ts->womenTeamScore;
			ts->womenTeamScore = tempsocer;

			tempsocer = tq->schoolScore;
			tq->schoolScore = ts->schoolScore;
			ts->schoolScore = tempsocer;
		}
	}
	return (STDataRrsult*)L;
}

void printSocer(STPlayer* nodeSP, STDataRrsult* nodeSD, const char* position)
{
	//��ӡ�ɼ���
	//���ļ��������ļ�ָ��
	FILE* fp = fopen(position, "w");
	if (fp == NULL)
	{
		printf("�ļ�����ʧ�ܣ��ɼ����ӡʧ�ܣ�\n");
		return;
	}
	STLinkList* list_ptrsp = (STLinkList*)nodeSP;
	STLinkList* list_ptrsd = (STLinkList*)nodeSD;
	STNode* psp = &(list_ptrsp->head);
	STNode* psd = &(list_ptrsd->head);
	STNode* tpsp = psp;
	STNode* tpsd = psd;
	STDataRrsult* ttpsd = NULL;
	STPlayer* ttpsp = NULL;
	fprintf(fp,"ѧУ�� ��Ŀ�� ����     �Ա�      ����      �÷�\n");
	while (tpsd->next != NULL)
	{
		//������������
		tpsd = tpsd->next;
		tpsp = psp;

		while (tpsp->next != NULL)
		{
			tpsp = tpsp->next;
			ttpsd = (STDataRrsult*)tpsd;
			ttpsp = (STPlayer*)tpsp;
			////������ʾ��������
			//���
			//ѧУ��    ��Ŀ��      ����      �Ա�      ����      �÷�
				// ѧУ�ĳɼ���
				//1��ѧУ�������ܷ�Ϊ��
				//1��ѧУ��Ů���ܷ�Ϊ��
				//1��ѧУ�����ܷ�Ϊ��
				//����n��ѧУ�ĳɼ����ܷ�
			//�������
			if (ttpsd->schoolNumber == ttpsp->schoolNumber)
				fprintf(fp,"%-10d %-10d %-10s %-10s %-10d %-10d\n", ttpsp->schoolNumber, ttpsp->itemNumber, ttpsp->name, ttpsp->sex, ttpsp->rank, getSocer(ttpsp));
		}
		fprintf(fp,"%d��ѧУ�������ܷ�Ϊ %-3d\n%d��ѧУ��Ů���ܷ�Ϊ %-3d\n%d��ѧУ�����ܷ�Ϊ   %-3d\n", ttpsd->schoolNumber, ttpsd->manTeamScore, ttpsd->schoolNumber, ttpsd->womenTeamScore, ttpsd->schoolNumber, ttpsd->schoolScore);
		if (tpsd->next != NULL)
			fprintf(fp,"\nѧУ�� ��Ŀ�� ����     �Ա�      ����      �÷�\n");
	}
	printf("\n�ɼ�����ӡ��ϣ�����·��Ϊ%s\n", position);
}