#ifndef __SIM900A_H__
#define __SIM900A_H__	 

#define swap16(x) (x&0XFF)<<8|(x&0XFF00)>>8		//�ߵ��ֽڽ����궨��

unsigned char sim900a_send_cmd(unsigned char *cmd,unsigned int waittime);
unsigned char sim900a_chr2hex(unsigned char chr);
unsigned char sim900a_hex2chr(unsigned char hex);
unsigned char sim900a_sms_test(void);			//���Ų���

#endif
