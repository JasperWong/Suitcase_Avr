#include"iom128v.h"

#define uchar unsigned char
#define uint unsigned int

//==========定义PID结构体===============
typedef struct PID
{
	double Kp;		//比例积分
	double Ki;		//积分常数
	double Kd;		//微分常数
	double Vsp;		//期望值
	double Vpv;		//实际值
	double Vle;		//上次误差
	double Vpe;		//当前误差
	double Vse;		//总误差
	double dError;	//偏差
	double Error;	//微分
	double Pwm;		//达到预期速度时Pwm的值
}PID;

struct PID sPID;
struct PID *p;

struct PID vPID;
struct PID *v;

//===========PID初始化子程序=============
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

//===========PID初始化子程序=============
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


//==========定义PID结构体===============
typedef struct PID
{
	float Kp;		//比例积分
	float Ki;		//积分常数
	float Kd;		//微分常数
	int Vsp;		//期望值
	int Vpv;		//实际值
	int LastError;		
	int PrevError;		
	int SumError;		//总误差
}PID;

struct PID sPID;
struct PID *p;

void PIDinit(void)
{
	p = &sPID;
	p->Kp = 0;		//比例积分
	p->Ki = 0;		//积分常数
	p->Kd = 0;		//微分常数
	p->Vsp = 0;		//期望值
	p->Vpv = 0;		//实际值
	p->LastError = 0;		
	p->PrevError = 0;		
	p->SumError = 0;		//总误差 
}

void PID(void)
{
	
}

**********************************************/