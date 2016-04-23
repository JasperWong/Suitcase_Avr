#ifndef __GPS_H
#define __GPS_H	 
					   						    
typedef struct  
{										    
 	unsigned char num;		//卫星编号
	unsigned char eledeg;	//卫星仰角
	unsigned int azideg;	//卫星方位角
	unsigned char sn;		//信噪比		   
}nmea_slmsg; 

//UTC时间信息
typedef struct  
{										    
 	unsigned int year;	//年份
	unsigned char month;	//月份
	unsigned char date;	//日期
	unsigned char hour; 	//小时
	unsigned char min; 	//分钟
	unsigned char sec; 	//秒钟
}nmea_utc_time;

//NMEA 0183 协议解析后数据存放结构体
typedef struct  
{										    
 	unsigned char svnum;					//可见卫星数
	nmea_slmsg slmsg[12];		//最多12颗卫星
	nmea_utc_time utc;			//UTC时间
	unsigned long latitude;				//纬度 分扩大100000倍,实际要除以100000
	unsigned char nshemi;					//北纬/南纬,N:北纬;S:南纬				  
	unsigned long longitude;			    //经度 分扩大100000倍,实际要除以100000
	unsigned char ewhemi;					//东经/西经,E:东经;W:西经
	unsigned char gpssta;					//GPS状态:0,未定位;1,非差分定位;2,差分定位;6,正在估算.				  
 	unsigned char posslnum;				//用于定位的卫星数,0~12.
 	unsigned char possl[12];				//用于定位的卫星编号
	unsigned char fixmode;					//定位类型:1,没有定位;2,2D定位;3,3D定位
	unsigned int pdop;					//位置精度因子 0~500,对应实际值0~50.0
	unsigned int hdop;					//水平精度因子 0~500,对应实际值0~50.0
	unsigned int vdop;					//垂直精度因子 0~500,对应实际值0~50.0 

	int altitude;			 	//海拔高度,放大了10倍,实际除以10.单位:0.1m	 
	unsigned int speed;					//地面速率,放大了1000倍,实际除以10.单位:0.001公里/小时	 
}nmea_msg;

//////////////////////////////////////////////////////////////////////////////////////////////////// 	
//UBLOX NEO-6M 配置(清除,保存,加载等)结构体
typedef struct  
{										    
 	unsigned int header;					//cfg header,固定为0X62B5(小端模式)
	unsigned int id;						//CFG CFG ID:0X0906 (小端模式)
	unsigned int dlength;				//数据长度 12/13
	unsigned long clearmask;				//子区域清除掩码(1有效)
	unsigned long savemask;				//子区域保存掩码
	unsigned long loadmask;				//子区域加载掩码
	unsigned char  devicemask; 		  	//目标器件选择掩码	b0:BK RAM;b1:FLASH;b2,EEPROM;b4,SPI FLASH
	unsigned char  cka;		 			//校验CK_A 							 	 
	unsigned char  ckb;			 		//校验CK_B							 	 
}_ublox_cfg_cfg; 

//UBLOX NEO-6M 消息设置结构体
typedef struct  
{										    
 	unsigned int header;					//cfg header,固定为0X62B5(小端模式)
	unsigned int id;						//CFG MSG ID:0X0106 (小端模式)
	unsigned int dlength;				//数据长度 8
	unsigned char  msgclass;				//消息类型(F0 代表NMEA消息格式)
	unsigned char  msgid;					//消息 ID 
								//00,GPGGA;01,GPGLL;02,GPGSA;
								//03,GPGSV;04,GPRMC;05,GPVTG;
								//06,GPGRS;07,GPGST;08,GPZDA;
								//09,GPGBS;0A,GPDTM;0D,GPGNS;
	unsigned char  iicset;					//IIC消输出设置    0,关闭;1,使能.
	unsigned char  uart1set;				//UART1输出设置	   0,关闭;1,使能.
	unsigned char  uart2set;				//UART2输出设置	   0,关闭;1,使能.
	unsigned char  usbset;					//USB输出设置	   0,关闭;1,使能.
	unsigned char  spiset;					//SPI输出设置	   0,关闭;1,使能.
	unsigned char  ncset;					//未知输出设置	   默认为1即可.
 	unsigned char  cka;			 		//校验CK_A 							 	 
	unsigned char  ckb;			    	//校验CK_B							 	 
}_ublox_cfg_msg; 

//UBLOX NEO-6M UART端口设置结构体
typedef struct  
{										    
 	unsigned int header;					//cfg header,固定为0X62B5(小端模式)
	unsigned int id;						//CFG PRT ID:0X0006 (小端模式)
	unsigned int dlength;				//数据长度 20
	unsigned char  portid;					//端口号,0=IIC;1=UART1;2=UART2;3=USB;4=SPI;
	unsigned char  reserved;				//保留,设置为0
	unsigned int txready;				//TX Ready引脚设置,默认为0
	unsigned long mode;					//串口工作模式设置,奇偶校验,停止位,字节长度等的设置.
 	unsigned long baudrate;				//波特率设置
 	unsigned int inprotomask;		 	//输入协议激活屏蔽位  默认设置为0X07 0X00即可.
 	unsigned int outprotomask;		 	//输出协议激活屏蔽位  默认设置为0X07 0X00即可.
 	unsigned int reserved4; 				//保留,设置为0
 	unsigned int reserved5; 				//保留,设置为0 
 	unsigned char  cka;			 		//校验CK_A 							 	 
	unsigned char  ckb;			    	//校验CK_B							 	 
}_ublox_cfg_prt; 

//UBLOX NEO-6M 时钟脉冲配置结构体
typedef struct  
{										    
 	unsigned int header;					//cfg header,固定为0X62B5(小端模式)
	unsigned int id;						//CFG TP ID:0X0706 (小端模式)
	unsigned int dlength;				//数据长度
	unsigned long interval;				//时钟脉冲间隔,单位为us
	unsigned long length;				 	//脉冲宽度,单位为us
	signed char status;			//时钟脉冲配置:1,高电平有效;0,关闭;-1,低电平有效.			  
	unsigned char timeref;			   		//参考时间:0,UTC时间;1,GPS时间;2,当地时间.
	unsigned char flags;					//时间脉冲设置标志
	unsigned char reserved;				//保留			  
 	signed short antdelay;	 	//天线延时
 	signed short rfdelay;		//RF延时
	signed int userdelay; 	 	//用户延时	
	unsigned char cka;						//校验CK_A 							 	 
	unsigned char ckb;						//校验CK_B							 	 
}_ublox_cfg_tp; 

//UBLOX NEO-6M 刷新速率配置结构体
typedef struct  
{										    
 	unsigned int header;					//cfg header,固定为0X62B5(小端模式)
	unsigned int id;						//CFG RATE ID:0X0806 (小端模式)
	unsigned int dlength;				//数据长度
	unsigned int measrate;				//测量时间间隔，单位为ms，最少不能小于200ms（5Hz）
	unsigned int navrate;				//导航速率（周期），固定为1
	unsigned int timeref;				//参考时间：0=UTC Time；1=GPS Time；
 	unsigned char  cka;					//校验CK_A 							 	 
	unsigned char  ckb;					//校验CK_B							 	 
}_ublox_cfg_rate; 
				 
unsigned char NMEA_Str2num(unsigned char *buf,unsigned char*dx,unsigned char length);
void GPS_Analysis(nmea_msg *gpsx,unsigned char *buf);
void NMEA_GPGSV_Analysis(nmea_msg *gpsx,unsigned char *buf);
void NMEA_GPGGA_Analysis(nmea_msg *gpsx,unsigned char *buf);
void NMEA_GPGSA_Analysis(nmea_msg *gpsx,unsigned char *buf);
void NMEA_GPGSA_Analysis(nmea_msg *gpsx,unsigned char *buf);
void NMEA_GPRMC_Analysis(nmea_msg *gpsx,unsigned char *buf);
void NMEA_GPVTG_Analysis(nmea_msg *gpsx,unsigned char *buf);
unsigned char Ublox_Cfg_Cfg_Save(void);
unsigned char Ublox_Cfg_Msg(unsigned char msgid,unsigned char uart1set);
unsigned char Ublox_Cfg_Prt(unsigned long baudrate);
unsigned char Ublox_Cfg_Tp(unsigned long interval,unsigned long length,signed char status);
unsigned char Ublox_Cfg_Rate(unsigned int measrate,unsigned char reftime);
#endif
