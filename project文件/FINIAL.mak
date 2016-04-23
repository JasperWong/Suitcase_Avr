CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -DATMega128  -l -g -MLongJump -MHasMul -MEnhanced -Wf-use_elpm 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x20000 -ucrtatmega.o -bfunc_lit:0x8c.0x20000 -dram_end:0x10ff -bdata:0x100.0x10ff -dhwstk_size:30 -beeprom:0.4096 -fihx_coff -S2
FILES = encoder.o pwm.o uart.o alarm_message.o lock.o init.o usart0.o sim900a.o gps.o 

FINIAL:	$(FILES)
	$(CC) -o FINIAL $(LFLAGS) @FINIAL.lk   -lstudio -lfpatm128 -lcatm128
encoder.o: .\..\encoder_uart_v4\encoder.h .\..\..\..\..\..\..\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h .\..\encoder_uart_v4\uart.h .\..\..\..\..\..\..\iccv7avr\include\iom128v.h .\..\encoder_uart_v4\pwm.h .\..\encoder_uart_v4\pid.h .\..\encoder_uart_v4\usart0.h .\..\encoder_uart_v4\gps.h C:\iccv7avr\include\string.h C:\iccv7avr\include\_const.h .\..\encoder_uart_v4\sim900a.h .\..\encoder_uart_v4\lock.h .\..\encoder_uart_v4\data_get.h .\..\encoder_uart_v4\alarm_message.h .\..\encoder_uart_v4\init.h
encoder.o:	..\encoder_uart_v4\encoder.c
	$(CC) -c $(CFLAGS) ..\encoder_uart_v4\encoder.c
pwm.o: .\..\encoder_uart_v4\pwm.h .\..\..\..\..\..\..\iccv7avr\include\iom128v.h
pwm.o:	..\encoder_uart_v4\pwm.c
	$(CC) -c $(CFLAGS) ..\encoder_uart_v4\pwm.c
uart.o: .\..\encoder_uart_v4\uart.h .\..\..\..\..\..\..\iccv7avr\include\iom128v.h
uart.o:	..\encoder_uart_v4\uart.c
	$(CC) -c $(CFLAGS) ..\encoder_uart_v4\uart.c
alarm_message.o: C:\iccv7avr\include\iom128v.h .\..\encoder_uart_v4\gps.h .\..\encoder_uart_v4\alarm_message.h .\..\encoder_uart_v4\encoder.h .\..\..\..\..\..\..\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h .\..\encoder_uart_v4\data_get.h .\..\encoder_uart_v4\sim900a.h .\..\encoder_uart_v4\usart0.h
alarm_message.o:	..\encoder_uart_v4\alarm_message.c
	$(CC) -c $(CFLAGS) ..\encoder_uart_v4\alarm_message.c
lock.o: C:\iccv7avr\include\iom128v.h .\..\encoder_uart_v4\lock.h
lock.o:	..\encoder_uart_v4\lock.c
	$(CC) -c $(CFLAGS) ..\encoder_uart_v4\lock.c
init.o: C:\iccv7avr\include\iom128v.h .\..\encoder_uart_v4\init.h
init.o:	..\encoder_uart_v4\init.c
	$(CC) -c $(CFLAGS) ..\encoder_uart_v4\init.c
usart0.o: C:\iccv7avr\include\iom128v.h C:\iccv7avr\include\string.h C:\iccv7avr\include\_const.h .\..\encoder_uart_v4\usart0.h
usart0.o:	..\encoder_uart_v4\usart0.c
	$(CC) -c $(CFLAGS) ..\encoder_uart_v4\usart0.c
sim900a.o: .\..\encoder_uart_v4\sim900a.h .\..\encoder_uart_v4\delay.h .\..\encoder_uart_v4\usart0.h .\..\..\..\..\..\..\iccv7avr\include\string.h C:\iccv7avr\include\_const.h C:\iccv7avr\include\iom128v.h
sim900a.o:	..\encoder_uart_v4\sim900a.c
	$(CC) -c $(CFLAGS) ..\encoder_uart_v4\sim900a.c
gps.o: .\..\encoder_uart_v4\gps.h .\..\..\..\..\..\..\iccv7avr\include\stdio.h C:\iccv7avr\include\stdarg.h C:\iccv7avr\include\_const.h .\..\..\..\..\..\..\iccv7avr\include\string.h .\..\..\..\..\..\..\iccv7avr\include\math.h C:\iccv7avr\include\iom128v.h
gps.o:	..\encoder_uart_v4\gps.c
	$(CC) -c $(CFLAGS) ..\encoder_uart_v4\gps.c
