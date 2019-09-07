/*
 * uart.c
 *
 *  Created on: Jun 6, 2019
 *      Author: databus
 */
#define  __SYLIXOS_KERNEL
#include <SylixOS.h>
#include <linux/compat.h>
/*********************************************************************************************************
  ����ַ����
*********************************************************************************************************/
#define UART0_BASE            (0x01c28000)
#define UART1_BASE            (0x01c28400)
#define UART2_BASE            (0x01c28800)
#define UART3_BASE            (0x01c28c00)
#define UART4_BASE            (0x01c29000)
/*********************************************************************************************************
  �Ĵ���ƫ��
*********************************************************************************************************/
#define RBR                   0x0
#define THR                   0x0
#define USR                   0x7C
/*********************************************************************************************************
** ��������: uartPutChar
** ��������: ��ͨ�� uiChann ����һ���ֽ�
** �䡡��  : uiChann        ͨ����
**           ucChar         ����
** �䡡��  : NONE
*********************************************************************************************************/
VOID  uartPutChar (UINT32  uiChann, UINT8  ucChar)
{
    addr_t atUartBase;

    switch (uiChann) {
    case 0:
        atUartBase = UART0_BASE;
        break;

    case 1:
        atUartBase = UART1_BASE;
        break;

    case 2:
        atUartBase = UART2_BASE;
        break;

    case 3:
        atUartBase = UART3_BASE;
        break;

    default:
        return;
    }

    /*
     * �� FIFO �������������ݣ�����ȴ�
     */
    while (!(readl(atUartBase + USR) & BIT(1)));

    writel(ucChar, atUartBase + THR);
}
/*********************************************************************************************************
** ��������: uartGetChar
** ��������: ��ͨ�� uiChann ����һ���ֽ�
** �䡡��  : uiChann         ͨ����
** �䡡��  : ���յ�������
*********************************************************************************************************/
UINT8  uartGetChar (UINT32  uiChann)
{
    addr_t atUartBase;
    UINT8  cChar;

    switch (uiChann) {
    case 0:
        atUartBase = UART0_BASE;
        break;

    case 1:
        atUartBase = UART1_BASE;
        break;

    case 2:
        atUartBase = UART2_BASE;
        break;

    case 3:
        atUartBase = UART3_BASE;
        break;

    default:
        atUartBase = UART0_BASE;
        break;
    }

    /*
     * �� FIFO �ǿվͶ�ȡһ�ֽ����ݣ�����ȴ�
     */
    while (!(readl(atUartBase + USR) & BIT(3)));

    cChar = readl(atUartBase + RBR);

    return (cChar);
}

