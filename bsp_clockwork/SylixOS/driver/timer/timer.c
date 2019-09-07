/*
 * timer.c
 *
 *  Created on: Jun 6, 2019
 *      Author: databus
 */
#define  __SYLIXOS_KERNEL
#include <SylixOS.h>
#include <linux/compat.h>
#include "timer.h"
/*********************************************************************************************************
  timer �Ĵ���ƫ��
*********************************************************************************************************/
#define TIMER_BASE     0x01c20c00
#define TIMER_IRQ_EN   0x00
#define TIMER_IRQ_STA  0x04
#define TIMER0_CTRL    0x10
#define TIMER0_INTV    0x14
#define TIMER0_CUR     0x18
#define TIMER1_CTRL    0x20
#define TIMER1_INTV    0x24
#define TIMER1_CUR     0x28

#define WDT_IRQ_EN     0xA0
#define WDT_IRQ_STA    0xA4
#define WDT_CTRL       0xB0
#define WDT_CFG        0xB4
#define WDT_MODE       0xB8

/*********************************************************************************************************
  tick ��ʱ������
*********************************************************************************************************/
#define TICK_TIMER_FREQ  (24 * 1000 * 1000 / 2)

/*********************************************************************************************************
** ��������: timerStart
** ��������: ���� timer
** �䡡��  : iNum  timer��ʱ�����
**           uiHZ  ���ö�ʱ���ж�Ƶ��
** �䡡��  : NONE
*********************************************************************************************************/
VOID  timerStart (INT32  iNum, UINT32  uiHZ)
{
    UINT32  uiCount;
    UINT32  uiIntvOffset;
    UINT32  uiCtrlOffset;

    if (0 == iNum) {
        uiIntvOffset = TIMER0_INTV;
        uiCtrlOffset = TIMER0_CTRL;
    } else if (1 == iNum) {
        uiIntvOffset = TIMER1_INTV;
        uiCtrlOffset = TIMER1_CTRL;
    } else {
        return ;
    }

    uiCount  = TICK_TIMER_FREQ;
    uiCount /= uiHZ;
    writel(uiCount, TIMER_BASE + uiIntvOffset);
    writel(BIT(1) | BIT(2) | BIT(4), TIMER_BASE + uiCtrlOffset);
    while ((readl(TIMER_BASE + uiCtrlOffset) >> 1) & 0x01);
    writel(readl(TIMER_BASE + uiCtrlOffset) | BIT(0), TIMER_BASE + uiCtrlOffset);
    writel(readl(TIMER_BASE + TIMER_IRQ_EN) | BIT(iNum), TIMER_BASE + TIMER_IRQ_EN);
}
/*********************************************************************************************************
** ��������: timerStop
** ��������: �ر� timer
** �䡡��  : iNum  timer��ʱ�����
** �䡡��  : NONE
*********************************************************************************************************/
VOID  timerStop (INT32  iNum)
{
    UINT32  uiCtrlOffset;

    if (0 == iNum) {
        uiCtrlOffset = TIMER0_CTRL;
    } else if (1 == iNum) {
        uiCtrlOffset = TIMER1_CTRL;
    } else {
        return ;
    }

    writel(readl(TIMER_BASE + uiCtrlOffset) & (~BIT(0)), TIMER_BASE + uiCtrlOffset);
}
/*********************************************************************************************************
** ��������: timerClearirq
** ��������: ��� timer �жϱ�־
** �䡡��  : iNum  timer��ʱ�����
** �䡡��  : NONE
*********************************************************************************************************/
VOID  timerClearirq (INT32  iNum)
{
    if ((0 != iNum) && (1 != iNum))
        return ;

    writel(readl(TIMER_BASE + TIMER_IRQ_STA) | BIT(iNum), TIMER_BASE + TIMER_IRQ_STA);
}
/*********************************************************************************************************
** ��������: timerIsIrqPending
** ��������: ����Ƿ���timer�жϲ���
** �䡡��  : iNum  timer��ʱ�����
** �䡡��  : TRUE  : ��timer�жϲ���
**           FALSE : û��timer�жϲ���
*********************************************************************************************************/
BOOL  timerIsIrqPending (INT32  iNum)
{
    if ((0 != iNum) && (1 != iNum))
        return  FALSE;

    return  (readl(TIMER_BASE + TIMER_IRQ_STA) & BIT(iNum)) ? TRUE : FALSE;
}
/*********************************************************************************************************
** ��������: timerCurGet
** ��������: ��ȡtimer��ǰ����ֵ
** �䡡��  : iNum  timer��ʱ�����
** �䡡��  : timer��ǰ����ֵ
*********************************************************************************************************/
UINT32  timerCurGet (INT32  iNum)
{
    if ((0 != iNum) && (1 != iNum))
        return 0;

    return  readl(TIMER_BASE + (TIMER0_CUR + iNum * 0x10));
}
/*********************************************************************************************************
** ��������: timerInputFreqGet
** ��������: ��ȡtimerģ������Ƶ��
** �䡡��  : iNum  timer��ʱ�����
** �䡡��  : timer��ǰ����ֵ
*********************************************************************************************************/
UINT32  timerInputFreqGet (INT32  iNum)
{
    if ((0 != iNum) && (1 != iNum))
        return 0;

    return  TICK_TIMER_FREQ;
}
