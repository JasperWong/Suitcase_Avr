NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   008C   0002 =      2. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       008C  __func_lit_start
       008E  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   008E   01A0 =    416. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       008E  __lit_start
       00C0  __ctype
       022E  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   022E   0139 =    313. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       022E  __idata_start
       0367  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0368   38B6 =  14518. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       01B4  __start
       01B4  __text_start
       01D6  _exit
       01D7  _PIDInit_1
       0262  _PIDInit_3
       02ED  _Gps_Msg_Show
       034E  _delay_ms
       035F  _INT_T1_ICP
       0377  _INT_T3_ICP
       038F  _INT_T1_OV
       0633  _stolen
       0655  _uart1_receive
       0697  _main
       0725  _io_init
       072C  _t3_init
       0741  _uart_init
       076B  _uart1_init
       0798  _uart0_transmit
       079C  _sent
       07C5  _uart0_str
       07D2  _uart0_receive
       07D6  _clean_data
       07E7  _data_get
       07FD  _alarm_mes
       0809  _lock_open
       0810  _lock_close
       0817  _ICP_1_init
       0830  _ICP_2_init
       0839  _ICP_3_init
       085C  _usart0_sent_char
       0860  _usart0_sent_string
       0870  _sim900a_sms_test
       08A9  _NMEA_Comma_Pos
       08C8  _NMEA_Pow
       08F2  _NMEA_Str2num
       0AF2  _NMEA_GPRMC_Analysis
       0BDB  _GPS_Analysis
       0BE4  _Ublox_CheckSum
       0C06  __print
       1073  _strlen
       107F  _strstr
       1095  push_arg4
       1097  push_arg2
       109A  asr32
       10A6  mod16s
       10AA  div16s
       10C4  mod16u
       10C6  div16u
       10C7  xdiv16u
       10E0  div32u
       10E2  mod32u
       10E6  div32s
       10E8  mod32s
       1114  long_div_prolog
       1127  long_div_epilog
       1137  tst_R16_R19
       113C  tst_R24_R27
       1141  neg_R24_R27
       114A  mod8u
       114C  div8u
       114D  xdiv8u
       1162  elpm32
       1176  empy16s
       1186  empy32s
       1186  empy32u
       11BA  pop_xgset003C
       11BF  pop_xgsetF0FC
       11CA  push_xgsetF0FC
       11CC  push_xgset30FC
       11CE  push_xgset00FC
       11D0  push_xgset003C
       11D5  push_xgsetF000
       11DA  pop_xgsetF000
       11DF  push_xgsetF00C
       11E6  pop_xgsetF00C
       11ED  push_xgset303C
       11F4  pop_xgset303C
       11FB  push_xgsetF03C
       1204  pop_xgsetF03C
       120D  xicallx
       1216  neg32
       121F  long_prolog
       122D  long_epilog
       1238  tstzero1
       123E  tstzero2
       1244  lsl32
       1250  fpsub
       1252  fpadd
       1253  fpadd_alt
       12BA  fpadd1
       12C4  fpadd1x
       12D1  fpadd2
       12DC  fpsub1
       12E6  fpint
       1318  uint2fp
       131A  int2fp
       1323  ulong2fp
       1325  long2fp
       133C  fpdiv1
       1345  fpdiv2
       134F  fpdiv1x
       135B  fpdiv2x
       13D6  unpacks
       13DE  tstR16_R19
       13E6  unpacku
       13FF  normalize_and_pack
       1434  pack
       1444  saveFPRegs
       1453  restoreFPRegs
       1462  fpmule
       14B5  fpmule1
       14BF  fpmule1x
       14CC  fpcmp
       14D9  fpcmp1
       14E4  fpcmp2
       14F0  _cstrcpy
       14FA  _cstrlen
       1507  _atoi
       154D  _itoa
       15B8  _ltoa
       1670  _ultoa
       16D7  _utoa
       1717  _ftoa
       18A6  _isdigit
       18B0  _islower
       18BA  _isspace
       18C4  _toupper
       18D7  __sdepi
       18E1  _sprintf
       1925  __FormatFP_1
       1E0F  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0100   0139 =    313. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0100  _data_rec_done_flag
       0100  __data_start
       0101  _app_data
       0106  _gps_data
       01CE  _uart1_receive_flag
       01CF  _lock_flag
       01D0  _sec_time
       01D1  _now_time
       01D3  _num_pulse_1
       01D5  _get_num_pulse_1
       01D7  _num_pulse_3
       01D9  _get_num_pulse_3
       01DB  _vino
       01DD  encoder.c:st_bit
       0239  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0239   0D1E =   3358. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0239  __bss_start
       0239  _latitude
       026B  _longitude
       029D  _gpsx
       0304  _data
       0EBC  _v
       0EBE  _vPID
       0EEA  _p
       0EEC  _sPID
       0F18  _num
       0F1C  _doc
       0F20  _miao
       0F24  _fen
       0F28  _du
       0F2C  _n
       0F57  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   007C =    124. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
encoder.o	[ encoder.c ]
pwm.o	[ pwm.c ]
uart.o	[ uart.c ]
alarm_message.o	[ alarm_message.c ]
lock.o	[ lock.c ]
init.o	[ init.c ]
usart0.o	[ usart0.c ]
sim900a.o	[ sim900a.c ]
gps.o	[ gps.c ]
<library>	[ _printf.s, strlen.s, strstr.s, asave.s, asr32.s, div16s.s, div16u.s, div32.s, div8u.s, elpm32.s, emul16s.s ]
[ emul32.s, gpop2.s, gpop5.s, gpush.s, gpushy.s, gpushz.s, gpusha.s, gpushb.s, icallx.s, lneg.s, longutil.s ]
[ lsl32.s, fpadd.s, fpadd1.s, fpadd1x.s, fpadd2.s, fpsub1.s, fpint.s, int2fp.s, fpdiv_new.s, fputil.s ]
[ fpmule.s, fpmule1.s, fpmule1x.s, fpcmp.s, fpcmp1.s, fpcmp2.s, cstrcpy.s, cstrlen.s, atoi.s, itoa.s ]
[ ltoa.s, ultoa.s, utoa.s, ftoa.s, isdigit.s, islower.s, isspace.s, ctype.s, toupper.s, sprintf.s, formatfp1.s ]


User Global Definitions

ram_end = 0x10ff
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x8c
data = 0x100
eeprom:0.4096

