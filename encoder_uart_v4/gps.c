#include "gps.h" 					    								   
#include "stdio.h"	 
#include "stdarg.h"	 
#include "string.h"	 
#include "math.h"
#include <iom128v.h>
					  
unsigned char n;
unsigned long du,fen,miao;
float doc;

unsigned char NMEA_Comma_Pos(unsigned char *buf,unsigned char cx)
{	 		    
	unsigned char *p=buf;
	while(cx)
	{		 
		if(*buf=='*'||*buf<' '||*buf>'z')return 0XFF;//����'*'���߷Ƿ��ַ�,�򲻴��ڵ�cx������
		if(*buf==',')cx--;
		buf++;
	}
	return buf-p;	 
}
//10^n����
//����ֵ:10^n�η�.
unsigned long NMEA_Pow(unsigned char n)
{
	unsigned long result=1;	
	unsigned char k; 
	for(k=0;k<n;k++)result*=10;    
	return result;
}

//strת��Ϊ����,��','����'*'����
//buf:���ִ洢��
//dx:С����λ��,���ظ����ú���
//����ֵ:ת�������ֵ
unsigned char NMEA_Str2num(unsigned char *buf,unsigned char *dx,unsigned char length)
{
	unsigned char *p=buf,t[9];
	unsigned char ilen=0,flen=0,i;
	unsigned char mask=0;
	unsigned char res=0;

	while(1) //�õ�������С���ĳ���
	{
		if(*p==','||(*p=='*'))break;//����������
		if(*p=='.')mask=1;//����С������
		else if(*p>'9'||(*p<'0'))	//�зǷ��ַ�
		{	
			ilen=0;
			flen=0;
			break;
		}
		if(*p>'0'&&*p<'9')
		{
		 if(mask==1)flen++;
		 if(mask==0)ilen++;
		}
		p++;
	}
	ilen=length;
	for(i=0;i<ilen;i++)	//�õ�������������
	{
		t[i]=buf[i];
	}
	*dx=3;	 		//С����λ��
	for(i=0;i<3;i++)	//�õ�С����������
	{  
		t[i+ilen]=buf[i+1+ilen];
	}  
	t[length+3]='\0';
	//usart0_sent_string((char*)t);
	//res=atoi(t);
	
	if(length+3==8)
	{
		du=(t[0]-'0')*100+(t[1]-'0')*10+(t[2]-'0');
   		fen=(t[3]-'0')*10+(t[4]-'0');
   		miao=(t[5]-'0')*100+(t[6]-'0')*10+(t[7]-'0');
   		miao=(miao*10)/6;   
   		fen=fen*1000+miao;
   		fen=fen/6;
	}
	if(length+3==7)
	{
		du=(t[0]-'0')*10+(t[1]-'0');
   		fen=(t[2]-'0')*10+(t[3]-'0');
   		miao=(t[4]-'0')*100+(t[5]-'0')*10+(t[6]-'0');
   		miao=(miao*10)/6;   
   		fen=fen*1000+miao;
   		fen=fen/6;
	}
	//for(i=0;i<9;i++)
		//usart0_sent_char(t[i]-'0');
		//usart0_sent_char(t[i]);
		//res+=NMEA_Pow(length+2-i)*((unsigned long)(t[i]-'0'));
   
	//usart0_sent_char(t[0]);
	//usart0_sent_char(t[1]);
	//usart0_sent_char(t[]);
	
	return res;
}	  							 

//����GPRMC��Ϣ
//gpsx:nmea��Ϣ�ṹ��
//buf:���յ���GPS���ݻ������׵�ַ
void NMEA_GPRMC_Analysis(nmea_msg *gpsx,unsigned char *buf)
{
	unsigned char *p1,dx;			 
	unsigned char posx;     
	unsigned long temp;	   
	unsigned long rs;  
	p1=(unsigned char*)strstr((const char *)buf,"$GPGLL");//"$GPRMC",������&��GPRMC�ֿ������,��ֻ�ж�GPRMC.
	//usart0_sent_string(p1);
	//posx=NMEA_Comma_Pos(p1,1);								//�õ�UTCʱ��
	//if(posx!=0XFF)
	//{
	//	temp=NMEA_Str2num(p1+posx,&dx)/NMEA_Pow(10,dx);	 	//�õ�UTCʱ��,ȥ��ms
	//	gpsx->utc.hour=temp/10000;
	//	gpsx->utc.min=(temp/100)%100;
	//	gpsx->utc.sec=temp%100;	 	 
	//}	
	//sscanf()
	posx=NMEA_Comma_Pos(p1,1);								//�õ�γ��
	if(posx!=0XFF)
	{
		temp=NMEA_Str2num(p1+posx,&dx,4);	
		//gpsx->latitude=temp; 
		//temp=2302515;
		gpsx->latitude=du;	//�õ���
		rs=fen;				//�õ�'		 
		gpsx->latitude=gpsx->latitude*10000+rs;//ת��Ϊ�� 
	}
	posx=NMEA_Comma_Pos(p1,2);								//��γ���Ǳ�γ 
	if(posx!=0XFF)gpsx->nshemi=*(p1+posx);					 
 	posx=NMEA_Comma_Pos(p1,3);								//�õ�����
	if(posx!=0XFF)
	{												  
		temp=NMEA_Str2num(p1+posx,&dx,5);
		//gpsx->longitude=temp;
		//temp=11321676;	 
		gpsx->longitude=du;	//�õ���
		rs=fen;				//�õ�'		 
		gpsx->longitude=gpsx->longitude*10000+rs;//ת��Ϊ�� 
	}
	posx=NMEA_Comma_Pos(p1,4);								//������������
	if(posx!=0XFF)gpsx->ewhemi=*(p1+posx);		 
	//posx=NMEA_Comma_Pos(p1,9);								//�õ�UTC����
	//if(posx!=0XFF)
	//{
	//	temp=NMEA_Str2num(p1+posx,&dx);		 				//�õ�UTC����
	//	gpsx->utc.date=temp/10000;
	//	gpsx->utc.month=(temp/100)%100;
	//	gpsx->utc.year=2000+temp%100;	 	 
	//} 
}

//��ȡNMEA-0183��Ϣ
//gpsx:nmea��Ϣ�ṹ��
//buf:���յ���GPS���ݻ������׵�ַ
void GPS_Analysis(nmea_msg *gpsx,unsigned char *buf)
{
	//NMEA_GPGSV_Analysis(gpsx,buf);	//GPGSV����
	//NMEA_GPGGA_Analysis(gpsx,buf);	//GPGGA���� 	
	//NMEA_GPGSA_Analysis(gpsx,buf);	//GPGSA����
	NMEA_GPRMC_Analysis(gpsx,buf);	//GPRMC����
	//NMEA_GPVTG_Analysis(gpsx,buf);	//GPVTG����
}

//GPSУ��ͼ���
//buf:���ݻ������׵�ַ
//len:���ݳ���
//cka,ckb:����У����.
void Ublox_CheckSum(unsigned char *buf,unsigned int len,unsigned char* cka,unsigned char*ckb)
{
	unsigned int i;
	*cka=0;*ckb=0;
	for(i=0;i<len;i++)
	{
		*cka=*cka+buf[i];
		*ckb=*ckb+*cka;
	}
}
