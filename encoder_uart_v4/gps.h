#ifndef __GPS_H
#define __GPS_H	 
					   						    
typedef struct  
{										    
 	unsigned char num;		//���Ǳ��
	unsigned char eledeg;	//��������
	unsigned int azideg;	//���Ƿ�λ��
	unsigned char sn;		//�����		   
}nmea_slmsg; 

//UTCʱ����Ϣ
typedef struct  
{										    
 	unsigned int year;	//���
	unsigned char month;	//�·�
	unsigned char date;	//����
	unsigned char hour; 	//Сʱ
	unsigned char min; 	//����
	unsigned char sec; 	//����
}nmea_utc_time;

//NMEA 0183 Э����������ݴ�Žṹ��
typedef struct  
{										    
 	unsigned char svnum;					//�ɼ�������
	nmea_slmsg slmsg[12];		//���12������
	nmea_utc_time utc;			//UTCʱ��
	unsigned long latitude;				//γ�� ������100000��,ʵ��Ҫ����100000
	unsigned char nshemi;					//��γ/��γ,N:��γ;S:��γ				  
	unsigned long longitude;			    //���� ������100000��,ʵ��Ҫ����100000
	unsigned char ewhemi;					//����/����,E:����;W:����
	unsigned char gpssta;					//GPS״̬:0,δ��λ;1,�ǲ�ֶ�λ;2,��ֶ�λ;6,���ڹ���.				  
 	unsigned char posslnum;				//���ڶ�λ��������,0~12.
 	unsigned char possl[12];				//���ڶ�λ�����Ǳ��
	unsigned char fixmode;					//��λ����:1,û�ж�λ;2,2D��λ;3,3D��λ
	unsigned int pdop;					//λ�þ������� 0~500,��Ӧʵ��ֵ0~50.0
	unsigned int hdop;					//ˮƽ�������� 0~500,��Ӧʵ��ֵ0~50.0
	unsigned int vdop;					//��ֱ�������� 0~500,��Ӧʵ��ֵ0~50.0 

	int altitude;			 	//���θ߶�,�Ŵ���10��,ʵ�ʳ���10.��λ:0.1m	 
	unsigned int speed;					//��������,�Ŵ���1000��,ʵ�ʳ���10.��λ:0.001����/Сʱ	 
}nmea_msg;

//////////////////////////////////////////////////////////////////////////////////////////////////// 	
//UBLOX NEO-6M ����(���,����,���ص�)�ṹ��
typedef struct  
{										    
 	unsigned int header;					//cfg header,�̶�Ϊ0X62B5(С��ģʽ)
	unsigned int id;						//CFG CFG ID:0X0906 (С��ģʽ)
	unsigned int dlength;				//���ݳ��� 12/13
	unsigned long clearmask;				//�������������(1��Ч)
	unsigned long savemask;				//�����򱣴�����
	unsigned long loadmask;				//�������������
	unsigned char  devicemask; 		  	//Ŀ������ѡ������	b0:BK RAM;b1:FLASH;b2,EEPROM;b4,SPI FLASH
	unsigned char  cka;		 			//У��CK_A 							 	 
	unsigned char  ckb;			 		//У��CK_B							 	 
}_ublox_cfg_cfg; 

//UBLOX NEO-6M ��Ϣ���ýṹ��
typedef struct  
{										    
 	unsigned int header;					//cfg header,�̶�Ϊ0X62B5(С��ģʽ)
	unsigned int id;						//CFG MSG ID:0X0106 (С��ģʽ)
	unsigned int dlength;				//���ݳ��� 8
	unsigned char  msgclass;				//��Ϣ����(F0 ����NMEA��Ϣ��ʽ)
	unsigned char  msgid;					//��Ϣ ID 
								//00,GPGGA;01,GPGLL;02,GPGSA;
								//03,GPGSV;04,GPRMC;05,GPVTG;
								//06,GPGRS;07,GPGST;08,GPZDA;
								//09,GPGBS;0A,GPDTM;0D,GPGNS;
	unsigned char  iicset;					//IIC���������    0,�ر�;1,ʹ��.
	unsigned char  uart1set;				//UART1�������	   0,�ر�;1,ʹ��.
	unsigned char  uart2set;				//UART2�������	   0,�ر�;1,ʹ��.
	unsigned char  usbset;					//USB�������	   0,�ر�;1,ʹ��.
	unsigned char  spiset;					//SPI�������	   0,�ر�;1,ʹ��.
	unsigned char  ncset;					//δ֪�������	   Ĭ��Ϊ1����.
 	unsigned char  cka;			 		//У��CK_A 							 	 
	unsigned char  ckb;			    	//У��CK_B							 	 
}_ublox_cfg_msg; 

//UBLOX NEO-6M UART�˿����ýṹ��
typedef struct  
{										    
 	unsigned int header;					//cfg header,�̶�Ϊ0X62B5(С��ģʽ)
	unsigned int id;						//CFG PRT ID:0X0006 (С��ģʽ)
	unsigned int dlength;				//���ݳ��� 20
	unsigned char  portid;					//�˿ں�,0=IIC;1=UART1;2=UART2;3=USB;4=SPI;
	unsigned char  reserved;				//����,����Ϊ0
	unsigned int txready;				//TX Ready��������,Ĭ��Ϊ0
	unsigned long mode;					//���ڹ���ģʽ����,��żУ��,ֹͣλ,�ֽڳ��ȵȵ�����.
 	unsigned long baudrate;				//����������
 	unsigned int inprotomask;		 	//����Э�鼤������λ  Ĭ������Ϊ0X07 0X00����.
 	unsigned int outprotomask;		 	//���Э�鼤������λ  Ĭ������Ϊ0X07 0X00����.
 	unsigned int reserved4; 				//����,����Ϊ0
 	unsigned int reserved5; 				//����,����Ϊ0 
 	unsigned char  cka;			 		//У��CK_A 							 	 
	unsigned char  ckb;			    	//У��CK_B							 	 
}_ublox_cfg_prt; 

//UBLOX NEO-6M ʱ���������ýṹ��
typedef struct  
{										    
 	unsigned int header;					//cfg header,�̶�Ϊ0X62B5(С��ģʽ)
	unsigned int id;						//CFG TP ID:0X0706 (С��ģʽ)
	unsigned int dlength;				//���ݳ���
	unsigned long interval;				//ʱ��������,��λΪus
	unsigned long length;				 	//�������,��λΪus
	signed char status;			//ʱ����������:1,�ߵ�ƽ��Ч;0,�ر�;-1,�͵�ƽ��Ч.			  
	unsigned char timeref;			   		//�ο�ʱ��:0,UTCʱ��;1,GPSʱ��;2,����ʱ��.
	unsigned char flags;					//ʱ���������ñ�־
	unsigned char reserved;				//����			  
 	signed short antdelay;	 	//������ʱ
 	signed short rfdelay;		//RF��ʱ
	signed int userdelay; 	 	//�û���ʱ	
	unsigned char cka;						//У��CK_A 							 	 
	unsigned char ckb;						//У��CK_B							 	 
}_ublox_cfg_tp; 

//UBLOX NEO-6M ˢ���������ýṹ��
typedef struct  
{										    
 	unsigned int header;					//cfg header,�̶�Ϊ0X62B5(С��ģʽ)
	unsigned int id;						//CFG RATE ID:0X0806 (С��ģʽ)
	unsigned int dlength;				//���ݳ���
	unsigned int measrate;				//����ʱ��������λΪms�����ٲ���С��200ms��5Hz��
	unsigned int navrate;				//�������ʣ����ڣ����̶�Ϊ1
	unsigned int timeref;				//�ο�ʱ�䣺0=UTC Time��1=GPS Time��
 	unsigned char  cka;					//У��CK_A 							 	 
	unsigned char  ckb;					//У��CK_B							 	 
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