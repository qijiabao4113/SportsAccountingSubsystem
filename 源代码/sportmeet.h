#include "listfun.h"

#ifndef  __MY_SPORTMEET_H__ 
#define __MY_SPORTMEET_H__

#define MAXARR 21													//���ѧУ���

//�ṹ��
typedef struct Player
{
	STNode node;
	int itemNumber;													//��Ŀ���
	char name[64];													//����
	char sex[64];													//�Ա�
	int schoolNumber;												//ѧУ���
	int rank;														//����
}STPlayer;

typedef struct TempPlayer
{
	STNode node;
	char itemNumber[64];											//��Ŀ���
	char name[64];													//����
	char sex[64];													//�Ա�
	char schoolNumber[64];											//ѧУ���
	char rank[64];													//����

}TSTPlayer;

typedef struct DataRrsult
{									
	STNode node;
	int schoolNumber;												//ѧУ���
	int womenTeamScore;												//Ů�ŵ÷�
	int manTeamScore;												//���ŵ÷�
	int schoolScore;												//ѧУ�÷�
}STDataRrsult;

//����

int legalInput(TSTPlayer* node);									//�ж��Ƿ�Ϸ�����Ϸ�����1�Ƿ�����-1
int ifstrdig(const char* str);										//�ж��Ƿ�Ϊ����
int strchadig(const char* str);										//�ַ���ת������
void* dataInput(void);												//�Ӽ��̻�ȡ�����������Ϸ����뷵�ؽṹ������
																	//�����Ϸ�����Ҫ���û����������״�������0�����˳�����
																	//��ǲβ���ѧУ���,��߱��MAXARR-1��С���1
bool findThisNode(STDataRrsult* node, STDataRrsult* ptrHead);		//�жϴ����Խڵ��Ƿ����
STDataRrsult* totalScoreFun(STPlayer* ptrHead);						//ͳ�Ƶ÷ֺ���
void dataPrint(STPlayer* nodeSP, STDataRrsult* nodeSD);				//��ӡ���
int getSocer(STPlayer* node);										//����÷�
STDataRrsult* SelectSort(STDataRrsult* t);							//���������
void printSocer(STPlayer* nodeSP, STDataRrsult* nodeSD, const char* position); //��ӡ�ɼ���
#endif