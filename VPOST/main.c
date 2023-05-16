/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    N9H26 series VPOST demo code
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wblib.h"
#include "N9H26.h"

UINT32 u32SecCnt;
UINT32 u32backup[10];

#if defined (__GNUC__) && !(__CC_ARM)
__attribute__ ((aligned (32))) UINT16 Vpost_Frame[1024*600]=
#else
__align(32) UINT16 Vpost_Frame[]={
	#include "KAKAO_RGB565.dat"
};
#endif

void initUART(void)
{
	WB_UART_T uart;
	UINT32 u32ExtFreq;
	
	
	/* Please run the path if you want to use normal speed UART */
	
  u32ExtFreq = sysGetExternalClock();
  sysUartPort(1);
  uart.uart_no = WB_UART_1;
  uart.uiFreq = u32ExtFreq;   //use APB clock
  uart.uiBaudrate = 115200;
  uart.uiDataBits = WB_DATA_BITS_8;
  uart.uiStopBits = WB_STOP_BITS_1;
  uart.uiParity = WB_PARITY_NONE;
  uart.uiRxTriggerLevel = LEVEL_1_BYTE;
  sysInitializeUART(&uart);

  sysInvalidCache();
  sysEnableCache(CACHE_WRITE_BACK);
  sysFlushCache(I_D_CACHE);
}

void initTimer(void)
{
	UINT32	u32ExtFreq;	    	    	
	UINT32 	u32Cke = inp32(REG_AHBCLK);

	/* init timer */	
	u32ExtFreq = sysGetExternalClock();    	/* Hz unit */		
	sysSetTimerReferenceClock (TIMER0, u32ExtFreq);	
	sysStartTimer(TIMER0, 100, PERIODIC_MODE);
	sysSetLocalInterrupt(ENABLE_IRQ);
}

int main(void)
{
  
	#ifdef GREEN_TEST
	UINT32 i;
	#endif
	
	S_DRVVPOST_SYNCLCM_INIT HITEK_lcd;
	S_DRVVPOST_SYNCLCM_HTIMING HITEK_ht = {10, 160 ,160}; //Pulse Width, Back Porch, Front Porch
	S_DRVVPOST_SYNCLCM_VTIMING HITEK_vt = {3, 23, 12};  //Vertical Puse Width, Back Porch, Front Porch 
	S_DRVVPOST_CLK_POLARITY HITEK_clk_pol = {TRUE,TRUE,FALSE,TRUE};
	S_DRVVPOST_RESET_CTRL HITEK_rst = {NULL,NULL,NULL,NULL};
	S_DRVVPOST_BACKLIGHT_CTRL HITEK_backlight = { 1, eDRVVPOST_GPA, eDRVVPOST_PIN_0, 1 , 0, NULL, NULL, NULL};
	
	/********************************************************************************************** 
	 * Clock Constraints: 
	 * (a) If Memory Clock > System Clock, the source clock of Memory and System can come from
	 *     different clock source. Suggestion MPLL for Memory Clock, UPLL for System Clock   
	 * (b) For Memory Clock = System Clock, the source clock of Memory and System must come from 
	 *     same clock source	 
	 *********************************************************************************************/

#if 0 
    /********************************************************************************************** 
     * Slower down system and memory clock procedures:
     * If current working clock fast than desired working clock, Please follow the procedure below  
     * 1. Change System Clock first
     * 2. Then change Memory Clock
     * 
     * Following example shows the Memory Clock = System Clock case. User can specify different 
     * Memory Clock and System Clock depends on DRAM bandwidth or power consumption requirement. 
     *********************************************************************************************/
    sysSetSystemClock(eSYS_EXT, 12000000, 12000000);
    sysSetDramClock(eSYS_EXT, 12000000, 12000000);
#else 
    /********************************************************************************************** 
     * Speed up system and memory clock procedures:
     * If current working clock slower than desired working clock, Please follow the procedure below  
     * 1. Change Memory Clock first
     * 2. Then change System Clock
     * 
     * Following example shows to speed up clock case. User can specify different 
     * Memory Clock and System Clock depends on DRAM bandwidth or power consumption requirement.
     *********************************************************************************************/
    sysSetDramClock(eSYS_MPLL, 360000000, 360000000);
    sysSetSystemClock(eSYS_UPLL,            //E_SYS_SRC_CLK eSrcClk,
                      240000000,            //UINT32 u32PllKHz,
                      240000000);           //UINT32 u32SysKHz,
    //sysSetCPUClock(240000000/2);
#endif

	  initUART();
	  initTimer();
	  sysprintf("LCD initialized successfully.\n");	
		
		//Green RGB565 TEST
		#ifdef GREEN_TEST
		for(i=0;i<614400;i++)
		{
			Vpost_Frame[i] = 0x344d;}
		#endif
		
		/* Sync LCD Module Parameter Setting hx8282-a11 + hx8696 */
		
		HITEK_lcd.u32BufAddr = (UINT32)Vpost_Frame; //Address to 32bit type casting
		HITEK_lcd.u16HSize = 1024;
		HITEK_lcd.u16VSize = 600;
		HITEK_lcd.u32PixClock = 51200; //51.2Mhz
		HITEK_lcd.eDataFormat = eDRVVPOST_FRAME_RGB565;
		HITEK_lcd.psHTiming = &HITEK_ht;
		HITEK_lcd.psVTiming = &HITEK_vt;
		HITEK_lcd.psClockPolarity = &HITEK_clk_pol;
		HITEK_lcd.eSyncInterface = eDRVVPOST_RGB888;
		HITEK_lcd.bDoNeedConfigLcm = 0;
		HITEK_lcd.psConfig = (void*)NULL;
		HITEK_lcd.bDoNeedCtrlBacklight = 1;
		HITEK_lcd.psBacklight = &HITEK_backlight;
		HITEK_lcd.psReset = &HITEK_rst;
		HITEK_lcd.eHVDeMode = eDRVVPOST_HSYNC_VSYNC_ONLY; 
		
		vpostSyncLCMInit(&HITEK_lcd);

    sysprintf("LCD initialized successfully.\n");	

	while(1);

}
