#include"iom128v.h"

#define uchar unsigned char
#define uint unsigned int

//==========����PID�ṹ��===============
typedef struct PID
{
	double Kp;		//��������
	double Ki;		//���ֳ���
	double Kd;		//΢�ֳ���
	double Vsp;		//����ֵ
	double Vpv;		//ʵ��ֵ
	double Vle;		//�ϴ����
	double Vpe;		//��ǰ���
	double Vse;		//�����
	double dError;	//ƫ��
	double Error;	//΢��
	double Pwm;		//�ﵽԤ���ٶ�ʱPwm��ֵ
}PID;

struct PID sPID;
struct PID *p;

struct PID vPID;
struct PID *v;

//===========PID��ʼ���ӳ���=============
void PIDInit_1(void)
{
  p = &sPID;
  p->Kp = /*0.394*/0.4;
  p->Ki = /*0.085*/0.1;
  p->Kd = 0.0085;
  p->Vsp = 0;
  p->Vpv = 0;
  p->Vle = 0;
  p->Vpe = 0;	
  p->Vse = 0;	
  p->dError = 0;
  p->Error = 0;
  p->Pwm = 0;
}

//===========PID��ʼ���ӳ���=============
void PIDInit_3(void)
{
  v = &vPID;
  v->Kp = /*0.394*/0.4;
  v->Ki = /*0.085*/0.1;
  v->Kd = 0.0085;
  v->Vsp = 0;
  v->Vpv = 0;
  v->Vle = 0;
  v->Vpe = 0;	
  v->Vse = 0;	
  v->dError = 0;
  v->Error = 0;
  v->Pwm = 0;
}


/********************************


//==========����PID�ṹ��===============
typedef struct PID
{
	float Kp;		//��������
	float Ki;		//���ֳ���
	float Kd;		//΢�ֳ���
	int Vsp;		//����ֵ
	int Vpv;		//ʵ��ֵ
	int LastError;		
	int PrevError;		
	int SumError;		//�����
}PID;

struct PID sPID;
struct PID *p;

void PIDinit(void)
{
	p = &sPID;
	p->Kp = 0;		//��������
	p->Ki = 0;		//���ֳ���
	p->Kd = 0;		//΢�ֳ���
	p->Vsp = 0;		//����ֵ
	p->Vpv = 0;		//ʵ��ֵ
	p->LastError = 0;		
	p->PrevError = 0;		
	p->SumError = 0;		//����� 
}

void PID(void)
{
	
}

**********************************************/