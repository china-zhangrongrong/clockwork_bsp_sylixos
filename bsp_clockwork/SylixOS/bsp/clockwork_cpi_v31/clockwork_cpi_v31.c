/*
 * clockwork_cpi_v31.c
 *
 *  Created on: Jun 3, 2019
 *      Author: databus
 */
#define  __SYLIXOS_KERNEL
#include <SylixOS.h>
#include "clockwork_cpi_v31.h"
#include "driver/uart/uart.h"
#include "driver/sio/sio.h"
#include "driver/gpio/gpio.h"
#include "driver/pinmux/pinmux.h"
#include "driver/sd/sunxi_mmc.h"
#include "driver/display/display.h"

VOID  bspBoardTargetInit (VOID)
{
}

VOID  bspBoardTimeInit (VOID)
{
}

VOID  bspBoardPmInit (VOID)
{
}

/*
 *  ��ʼ����������ϵͳ
 */
VOID  bspBoardBusInit (VOID)
{
    API_I2cLibInit();                                                   /*  ��ʼ�� i2c �����           */

    API_SpiLibInit();                                                   /*  ��ʼ�� spi �����           */
}

/*
 *  ������ʼ��
 */
VOID  bspBoardDrvInit (VOID)
{
    gpioDrvInstall();
}

/*
 *  �豸��ʼ��
 */
VOID bspBoardDevInit (VOID)
{
    SIO_CHAN  *psio;

    psio = sioChanCreate(0);                                            /*  �������� 0 ͨ��             */
    if (psio) {
        ttyDevCreate("/dev/ttyS0", psio, 1024, 1024);                   /*  ���� tty �豸               */
    }

    lcdDevCreate();

    sdDrvInstall(0, GPIO_B_03, GPIO_NONE, TRUE);
}

/*
 *  nandflash�豸��ʼ��
 */
VOID  bspBoardNandInit (VOID)
{
}

/*
 *  �����ʼ��
 */
VOID  bspBoardNetifAttch (VOID)
{
}

VOID  bspBoardDebugChInit (UINT  uiIndex)
{
}

/*
 *  ��ӡ������Ϣ
 */
VOID  bspBoardDebugMsg (CPCHAR  cpcMsg)
{
    CHAR cChar;

    if (!cpcMsg) {                                                       /*  ָ��Ϊ��                    */
        return;
    }

    while ((cChar = *cpcMsg) != '\0') {                                  /*  �����ַ���                  */
        uartPutChar(BSP_CFG_DEBUG_CH, cChar);
        cpcMsg++;
    }
}

VOID  bspBoardSymbolInit (VOID)
{
}

/*
 *  ������������
 */
VOID  bspBoardkernelStartParam (VOID)
{
    API_KernelStartParam(NCPUS
                         " sldepcache=yes kdlog=no kderror=no kfpu=no heapchk=yes hz=1000 hhz=1000 "
                         MOUNT_PARAMETERS);                             /*  ����ϵͳ������������        */
}
