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
		if(*buf=='*'||*buf<' '||*buf>'z')return 0XFF;//遇到'*'或者非法字符,则不存在第cx个逗号
		if(*buf==',')cx--;
		buf++;
	}
	return buf-p;	 
}
//10^n函数
//返回值:10^n次方.
unsigned long NMEA_Pow(unsigned char n)
{
	unsigned long result=1;	
	unsigned char k; 
	for(k=0;k<n;k++)result*=10;    
	return result;
}

//str转换为数字,以','或者'*'结束
//buf:数字存储区
//dx:小数点位数,返回给调用函数
//返回值:转换后的数值
unsigned char NMEA_Str2num(unsigned char *buf,unsigned char *dx,unsigned char length)
{
	unsigned char *p=buf,t[9];
	unsigned char ilen=0,flen=0,i;
	unsigned char mask=0;
	unsigned char res=0;

	while(1) //得到整数和小数的长度
	{
		if(*p==','||(*p=='*'))break;//遇到结束了
		if(*p=='.')mask=1;//遇到小数点了
		else if(*p>'9'||(*p<'0'))	//有非法字符
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
	for(i=0;i<ilen;i++)	//得到整数部分数据
	{
		t[i]=buf[i];
	}
	*dx=3;	 		//小数点位数
	for(i=0;i<3;i++)	//得到小数部分数据
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

//分析GPRMC信息
//gpsx:nmea信息结构体
//buf:接收到的GPS数据缓冲区首地址
void NMEA_GPRMC_Analysis(nmea_msg *gpsx,unsigned char *buf)
{
	unsigned char *p1,dx;			 
	unsigned char posx;     
	unsigned long temp;	   
	unsigned long rs;  
	p1=(unsigned char*)strstr((const char *)buf,"$GPGLL");//"$GPRMC",经常有&和GPRMC分开的情况,故只判断GPRMC.
	//usart0_sent_string(p1);
	//posx=NMEA_Comma_Pos(p1,1);								//得到UTC时间
	//if(posx!=0XFF)
	//{
	//	temp=NMEA_Str2num(p1+posx,&dx)/NMEA_Pow(10,dx);	 	//得到UTC时间,去掉ms
	//	gpsx->utc.hour=temp/10000;
	//	gpsx->utc.min=(temp/100)%100;
	//	gpsx->utc.sec=temp%100;	 	 
	//}	
	//sscanf()
	posx=NMEA_Comma_Pos(p1,1);								//得到纬度
	if(posx!=0XFF)
	{
		temp=NMEA_Str2num(p1+posx,&dx,4);	
		//gpsx->latitude=temp; 
		//temp=2302515;
		gpsx->latitude=du;	//得到°
		rs=fen;				//得到'		 
		gpsx->latitude=gpsx->latitude*10000+rs;//转换为° 
	}
	posx=NMEA_Comma_Pos(p1,2);								//南纬还是北纬 
	if(posx!=0XFF)gpsx->nshemi=*(p1+posx);					 
 	posx=NMEA_Comma_Pos(p1,3);								//得到经度
	if(posx!=0XFF)
	{												  
		temp=NMEA_Str2num(p1+posx,&dx,5);
		//gpsx->longitude=temp;
		//temp=11321676;	 
		gpsx->longitude=du;	//得到°
		rs=fen;				//得到'		 
		gpsx->longitude=gpsx->longitude*10000+rs;//转换为° 
	}
	posx=NMEA_Comma_Pos(p1,4);								//东经还是西经
	if(posx!=0XFF)gpsx->ewhemi=*(p1+posx);		 
	//posx=NMEA_Comma_Pos(p1,9);								//得到UTC日期
	//if(posx!=0XFF)
	//{
	//	temp=NMEA_Str2num(p1+posx,&dx);		 				//得到UTC日期
	//	gpsx->utc.date=temp/10000;
	//	gpsx->utc.month=(temp/100)%100;
	//	gpsx->utc.year=2000+temp%100;	 	 
	//} 
}

//提取NMEA-0183信息
//gpsx:nmea信息结构体
//buf:接收到的GPS数据缓冲区首地址
void GPS_Analysis(nmea_msg *gpsx,unsigned char *buf)
{
	//NMEA_GPGSV_Analysis(gpsx,buf);	//GPGSV解析
	//NMEA_GPGGA_Analysis(gpsx,buf);	//GPGGA解析 	
	//NMEA_GPGSA_Analysis(gpsx,buf);	//GPGSA解析
	NMEA_GPRMC_Analysis(gpsx,buf);	//GPRMC解析
	//NMEA_GPVTG_Analysis(gpsx,buf);	//GPVTG解析
}

//GPS校验和计算
//buf:数据缓存区首地址
//len:数据长度
//cka,ckb:两个校验结果.
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

