/*
 * gpio.c
 *
 *  Created on: Jun 9, 2019
 *      Author: databus
 */


#define __SYLIXOS_KERNEL
#include <SylixOS.h>
#include <linux/compat.h>
#include "driver/include/irq_numbers.h"
#include "driver/pinmux/pinmux.h"
/*********************************************************************************************************
  �ܽŹ��̶ܹ�ֵѡ���
*********************************************************************************************************/
#define GPIO_INPUT                 ALT0                                 /*  �ܽ�Ϊ�������빦��          */
#define GPIO_OUTPUT                ALT1                                 /*  �ܽ�Ϊ�����������          */
#define GPIO_EINT                  ALT4                                 /*  �ܽ�Ϊ�жϴ���              */
#define GPIO_DISABLE               ALT7                                 /*  �ܽŹر�                    */
/*********************************************************************************************************
 �жϴ�������ѡ���
*********************************************************************************************************/
#define EINT_MODE_POSITIVE_EDGE    (0X00)                               /*  �����ش���                  */
#define EINT_MODE_NEGATIVE_EDGE    (0X01)                               /*  �½��ش���                  */
#define EINT_MODE_HIGH_LEVEL       (0X02)                               /*  �ߵ�ƽ����                  */
#define EINT_MODE_LOW_LEVEL        (0X03)                               /*  �͵�ƽ����                  */
#define EINT_MODE_DOUBLE_EDGE      (0X04)                               /*  ˫���ش���                  */
/*********************************************************************************************************
  GPIO���ƼĴ���ƫ�������� (R16ֻ��PB��PG�������жϹ���)
*********************************************************************************************************/
#define GPIO_CFG                   (0x00)                               /*  GPIO �������üĴ���         */
#define GPIO_DAT                   (0x10)                               /*  GPIO ���ݼĴ���             */
#define GPIO_DRV                   (0x14)                               /*  GPIO �����������üĴ���     */
#define GPIO_PUL                   (0x1C)                               /*  GPIO ���������üĴ���       */

#define GPIO_B_INT_CFG             (0x220)                              /*  GPIOB �жϴ����������üĴ���*/
#define GPIO_B_INT_CTL             (0x230)                              /*  GPIOB �жϿ��ƼĴ���        */
#define GPIO_B_INT_STA             (0x234)                              /*  GPIOB �ж�״̬�Ĵ���        */
#define GPIO_B_INT_DEB             (0x238)                              /*  GPIOB �ж�Ƶ�����üĴ���    */

#define GPIO_G_INT_CFG             (0x240)                              /*  GPIOG �жϴ����������üĴ���*/
#define GPIO_G_INT_CTL             (0x250)                              /*  GPIOG �жϿ��ƼĴ���        */
#define GPIO_G_INT_STA             (0x254)                              /*  GPIOG �ж�״̬�Ĵ���        */
#define GPIO_G_INT_DEB             (0x258)                              /*  GPIOG �ж�Ƶ�����üĴ���    */
/*********************************************************************************************************
** ��������: sunxiR16GpioRequest
** ��������: ʵ�� GPIO �ܽŵ� PINMUX ����
** ��  ��  : pGpioChip GPIO оƬ
**           uiNum     GPIO��ϵͳ�еı��
** ��  ��  : ERROR CODE
*********************************************************************************************************/
static INT  sunxiR16GpioRequest (PLW_GPIO_CHIP  pGpioChip, UINT uiNum)
{
    return  (gpioPinmuxSet(uiNum, GPIO_DISABLE));
}
/*********************************************************************************************************
** ��������: sunxiR16GpioFree
** ��������: �ͷ�һ�����ڱ�ʹ�õ� GPIO, �����ǰ���ж�ģʽ��, �����ж����빦��.
** ��  ��  : pGpioChip   GPIO оƬ
**           uiNum     GPIO��ϵͳ�еı��
** ��  ��  : ERROR CODE
*********************************************************************************************************/
static VOID  sunxiR16GpioFree (PLW_GPIO_CHIP  pGpioChip, UINT uiNum)
{
    INT     iRet;
    addr_t  ulAddr;
    UINT32  uiValue;
    UINT32  uiINTN;
    INT32   iGpioSoc = gpioSysToSoc(uiNum);

    if (iGpioSoc == PX_ERROR) {
        return  ;
    }

    /*
     *  ��������IO���ܹر�
     */
    iRet = gpioPinmuxSet(uiNum, GPIO_DISABLE);
    if (PX_ERROR == iRet){
        return  ;
    }


    /*
     *  ��������жϿ��ƼĴ�����ַ
     */
    if (iGpioSoc >= GPIO_NUM(GPIO_PORT_B, GPIO_PIN_00) &&
        iGpioSoc <= GPIO_NUM(GPIO_PORT_B, GPIO_PIN_07)) {
        uiINTN = iGpioSoc - GPIO_NUM(GPIO_PORT_B, GPIO_PIN_00);          /*  GPIOB�ж�EINT0-7           */
        ulAddr = GPIO_B_INT_CTL + GPIO_BASE;                             /*  �жϿ��ƼĴ�����ַ         */
    } else if (iGpioSoc >= GPIO_NUM(GPIO_PORT_G, GPIO_PIN_00) &&
               iGpioSoc <= GPIO_NUM(GPIO_PORT_G, GPIO_PIN_13)) {
        uiINTN = iGpioSoc - GPIO_NUM(GPIO_PORT_G, GPIO_PIN_00);          /*  GPIOG�ж�EINT0-13          */
        ulAddr = GPIO_G_INT_CTL + GPIO_BASE;                             /*  �жϿ��ƼĴ�����ַ         */
    } else {
        return;                                                          /*  �ö˿�û���жϹ���         */
    }

    /*
     *  �ر������жϹ���
     */
    uiValue = readl(ulAddr);
    uiValue &= ~BIT(uiINTN);
    writel(uiValue, ulAddr);

    return  ;
}
/*********************************************************************************************************
** ��������: sunxiR16GpioGetDirection
** ��������: ���ָ�� GPIO ����
** ��  ��  : pGpioChip   GPIO оƬ
**           uiNum       GPIO��ϵͳ�еı��
** ��  ��  : 0: ���� 1:��� -1:����
*********************************************************************************************************/
static INT  sunxiR16GpioGetDirection (PLW_GPIO_CHIP  pGpioChip, UINT uiNum)
{
    UINT32  uiRegVal;

    uiRegVal = gpioPinmuxGet(uiNum);
    if (uiRegVal == GPIO_INPUT) {
        return  (0);
    } else if(uiRegVal == GPIO_OUTPUT) {
        return  (1);
    } else {
        return  (PX_ERROR);
    }
}
/*********************************************************************************************************
** ��������: sunxiR16GpioDirectionInput
** ��������: ����ָ�� GPIO Ϊ����ģʽ
** ��  ��  : pGpioChip   GPIO оƬ
**           uiNum       GPIO��ϵͳ�еı��
** ��  ��  : 0: ��ȷ -1:����
*********************************************************************************************************/
static INT  sunxiR16GpioDirectionInput (PLW_GPIO_CHIP  pGpioChip, UINT uiNum)
{
    return  (gpioPinmuxSet(uiNum, GPIO_INPUT));
}
/*********************************************************************************************************
** ��������: sunxiR16GpioGet
** ��������: ���ָ�� GPIO ��ƽ
** ��  ��  : pGpioChip   GPIO оƬ
**           uiNum       GPIO��ϵͳ�еı��
** ��  ��  : 0: �͵�ƽ 1:�ߵ�ƽ -1:����
*********************************************************************************************************/
static INT  sunxiR16GpioGet (PLW_GPIO_CHIP  pGpioChip, UINT  uiNum)
{
    addr_t  ulAddr;
    UINT32  uiPortNum;
    UINT32  uiPinNum;
    INT32   iGpioSoc = gpioSysToSoc(uiNum);

    if (iGpioSoc == PX_ERROR) {
        return  (PX_ERROR);
    }

    /*
     *  ������ź����ź�
     */
    uiPortNum  = GET_SOC_PORT_NUM(iGpioSoc);
    uiPinNum   = GET_SOC_PIN_NUM(iGpioSoc);

    if (uiPinNum > GPIO_PIN_31) {
        return  (PX_ERROR);
    }

    ulAddr = GPIO_DAT + uiPortNum * 0x24 + GPIO_BASE;

    return  (readl(ulAddr) & (BIT(uiPinNum))) ? 1 : 0;
}
/*********************************************************************************************************
** ��������: sunxiR16GpioSet
** ��������: ����ָ�� GPIO ��ƽ
** ��  ��  : pGpioChip   GPIO оƬ
**           uiNum       GPIO��ϵͳ�еı��
**           iValue      �����ƽ
** ��  ��  : 0: ��ȷ -1:����
*********************************************************************************************************/
static VOID  sunxiR16GpioSet (PLW_GPIO_CHIP  pGpioChip, UINT  uiNum, INT  iValue)
{
    addr_t  ulAddr;
    UINT32  uiRegister;
    UINT32  uiPortNum;
    UINT32  uiPinNum;
    INT32   iGpioSoc = gpioSysToSoc(uiNum);

    if (iGpioSoc == PX_ERROR) {
        return  ;
    }

    /*
     *  ������ź����ź�
     */
    uiPortNum  = GET_SOC_PORT_NUM(iGpioSoc);
    uiPinNum   = GET_SOC_PIN_NUM(iGpioSoc);

    if (uiPinNum > GPIO_PIN_31) {
        return  ;
    }

    ulAddr = GPIO_DAT + uiPortNum * 0x24 + GPIO_BASE;

    uiRegister = readl(ulAddr);
    if (0 == iValue) {
        uiRegister &= ~BIT(uiPinNum);
    } else {
        uiRegister |= BIT(uiPinNum);
    }
    writel(uiRegister, ulAddr);

    return  ;
}
/*********************************************************************************************************
** ��������: sunxiR16GpioDirectionOutput
** ��������: ����ָ�� GPIO Ϊ���ģʽ
** ��  ��  : pGpioChip   GPIO оƬ
**           uiNum       GPIO��ϵͳ�еı��
**           iValue      �����ƽ
** ��  ��  : 0: ��ȷ -1:����
*********************************************************************************************************/
static INT  sunxiR16GpioDirectionOutput (PLW_GPIO_CHIP  pGpioChip, UINT  uiNum, INT  iValue)
{
    INT32  iGpioSoc = gpioSysToSoc(uiNum);

    if (iGpioSoc == PX_ERROR) {
        return  (PX_ERROR);
    }

    gpioPinmuxSet(uiNum, GPIO_OUTPUT);
    sunxiR16GpioSet (pGpioChip, uiNum, iValue);

    return  (ERROR_NONE);
}
/*********************************************************************************************************
** ��������: sunxiR16GpioSetupIrq
** ��������: ����ָ�� GPIO Ϊ�ⲿ�ж�����ܽ�
** ��  ��  : pGpioChip   GPIO оƬ
**           uiNum       GPIO��ϵͳ�еı��
**           bIsLevel    �Ƿ�Ϊ��ƽ����, 1 ��ʾ��ƽ������0 ��ʾ���ش���
**           uiType      ���Ϊ��ƽ����, 1 ��ʾ�ߵ�ƽ����, 0 ��ʾ�͵�ƽ����
**                       ���Ϊ���ش���, 1 ��ʾ�����ش���, 0 ��ʾ�½��ش���, 2 ˫���ش���
** ��  ��  : IRQ ������ -1:����
*********************************************************************************************************/
static ULONG  sunxiR16GpioSetupIrq (PLW_GPIO_CHIP  pGpioChip, UINT  uiNum, BOOL  bIsLevel, UINT  uiType)
{
    addr_t  ulIntCfgAddr;
    addr_t  ulIntCtlAddr;
    UINT32  uiValue;
    UINT32  uiCfg;
    INT     iIRQn;
    UINT32  uiINTN;
    INT32   iGpioSoc = gpioSysToSoc(uiNum);

    if (iGpioSoc == PX_ERROR) {
        return  (PX_ERROR);
    }

    if (iGpioSoc >= GPIO_NUM(GPIO_PORT_B, GPIO_PIN_00) &&
        iGpioSoc <= GPIO_NUM(GPIO_PORT_B, GPIO_PIN_07)) {
        uiINTN = iGpioSoc - GPIO_NUM(GPIO_PORT_B, GPIO_PIN_00);          /*  GPIOB�ж�EINT0-7           */
        ulIntCfgAddr = GPIO_B_INT_CFG + GPIO_BASE + (uiINTN / 8 * 4);    /*  �ж����ͼĴ�����ַ         */
        ulIntCtlAddr = GPIO_B_INT_CTL + GPIO_BASE;
        iIRQn  = PB_EINT;
    } else if (iGpioSoc >= GPIO_NUM(GPIO_PORT_G, GPIO_PIN_00) &&
               iGpioSoc <= GPIO_NUM(GPIO_PORT_G, GPIO_PIN_13)) {
        uiINTN = iGpioSoc - GPIO_NUM(GPIO_PORT_G, GPIO_PIN_00);          /*  GPIOG�ж�EINT0-13          */
        ulIntCfgAddr = GPIO_G_INT_CFG + GPIO_BASE + (uiINTN / 8 * 4);    /*  �ж����ͼĴ�����ַ         */
        ulIntCtlAddr = GPIO_G_INT_CTL + GPIO_BASE;
        iIRQn  = PG_EINT;
    } else {
        return  (-1);                                                    /*  �ö˿�û���жϹ���         */
    }

    /*
     * �����жϴ�������
     */
    if (bIsLevel) {                                                     /*  ����ǵ�ƽ�����ж�          */
        if (uiType) {
            uiCfg = EINT_MODE_HIGH_LEVEL;                               /*  �ߵ�ƽ����                  */
        } else {
            uiCfg = EINT_MODE_LOW_LEVEL;                                /*  �͵�ƽ����                  */
        }
    } else {
        if (uiType == 0) {                                              /*  �½��ش���                  */
            uiCfg = EINT_MODE_NEGATIVE_EDGE;
        } else if (uiType == 1) {                                       /*  �����ش���                  */
            uiCfg = EINT_MODE_POSITIVE_EDGE;
        } else {                                                        /*  ˫���ش���                  */
            uiCfg = EINT_MODE_DOUBLE_EDGE;
        }
    }

    uiValue = readl(ulIntCfgAddr);
    uiValue &= ~(0x0f << ((uiINTN % 8) * 4));
    uiValue |= (uiCfg << ((uiINTN % 8) * 4));
    writel(uiValue, ulIntCfgAddr);

    /*
     * ��������Ϊ�ж����빦��
     */
    gpioPinmuxSet(uiNum, GPIO_EINT);

    /*
     * ʹ�������ж���Ӧ
     */
    uiValue = readl(ulIntCtlAddr);
    uiValue |= BIT(uiINTN);
    writel(uiValue, ulIntCtlAddr);

    return  (iIRQn);
}
/*********************************************************************************************************
** ��������: sunxiR16GpioClearIrq
** ��������: ���ָ�� GPIO �жϱ�־
** ��  ��  : pGpioChip   GPIO оƬ
**           uiNum       GPIO��ϵͳ�еı��
** ��  ��  : NONE
*********************************************************************************************************/
static VOID  sunxiR16GpioClearIrq (PLW_GPIO_CHIP  pGpioChip, UINT  uiNum)
{
    addr_t  ulAddr;
    UINT32  uiINTN;
    INT32   iGpioSoc = gpioSysToSoc(uiNum);

    if (iGpioSoc == PX_ERROR) {
        return  ;
    }

    if (iGpioSoc >= GPIO_NUM(GPIO_PORT_B, GPIO_PIN_00) &&
        iGpioSoc <= GPIO_NUM(GPIO_PORT_B, GPIO_PIN_07)) {
        uiINTN = iGpioSoc - GPIO_NUM(GPIO_PORT_B, GPIO_PIN_00);          /*  GPIOB�ж�EINT0-7           */
        ulAddr = GPIO_B_INT_STA + GPIO_BASE;                             /*  �ж�״̬�Ĵ�����ַ         */
    } else if (iGpioSoc >= GPIO_NUM(GPIO_PORT_G, GPIO_PIN_00) &&
               iGpioSoc <= GPIO_NUM(GPIO_PORT_G, GPIO_PIN_13)) {
        uiINTN = iGpioSoc - GPIO_NUM(GPIO_PORT_G, GPIO_PIN_00);          /*  GPIOG�ж�EINT0-13          */
        ulAddr = GPIO_G_INT_STA + GPIO_BASE;                             /*  �ж�״̬�Ĵ�����ַ         */
    } else {
        return;                                                          /*  �ö˿�û���жϹ���         */
    }

    writel(BIT(uiINTN), ulAddr);

    return  ;
}
/*********************************************************************************************************
** ��������: sunxiR16GpioSvrIrq
** ��������: �ж� GPIO �жϱ�־
** ��  ��  : pGpioChip   GPIO оƬ
**           uiNum       GPIO��ϵͳ�еı��
** ��  ��  : �жϷ���ֵ
*********************************************************************************************************/
static irqreturn_t  sunxiR16GpioSvrIrq (PLW_GPIO_CHIP  pGpioChip, UINT  uiNum)
{
    addr_t  ulAddr;
    UINT32  uiRegister;
    UINT32  uiINTN;
    INT32   iGpioSoc = gpioSysToSoc(uiNum);

    if (iGpioSoc == PX_ERROR) {
        return  (PX_ERROR);
    }

    if (iGpioSoc >= GPIO_NUM(GPIO_PORT_B, GPIO_PIN_00) &&
        iGpioSoc <= GPIO_NUM(GPIO_PORT_B, GPIO_PIN_07)) {
        uiINTN = iGpioSoc - GPIO_NUM(GPIO_PORT_B, GPIO_PIN_00);          /*  GPIOB�ж�EINT0-7           */
        ulAddr = GPIO_B_INT_STA + GPIO_BASE;                             /*  �ж�״̬�Ĵ�����ַ         */
    } else if (iGpioSoc >= GPIO_NUM(GPIO_PORT_G, GPIO_PIN_00) &&
               iGpioSoc <= GPIO_NUM(GPIO_PORT_G, GPIO_PIN_13)) {
        uiINTN = iGpioSoc - GPIO_NUM(GPIO_PORT_G, GPIO_PIN_00);          /*  GPIOG�ж�EINT0-13          */
        ulAddr = GPIO_G_INT_STA + GPIO_BASE;                             /*  �ж�״̬�Ĵ�����ַ         */
    } else {
        return  (PX_ERROR);;                                                          /*  �ö˿�û���жϹ���         */
    }

    uiRegister = readl(ulAddr);
    if (uiRegister & (BIT(uiINTN))) {
        return  (LW_IRQ_HANDLED);
    } else {
        return  (LW_IRQ_NONE);
    }
}

/*********************************************************************************************************
** ��������: sunxiR16GpioGetIrq
** ��������: ��ȡGPIO�жϺ�
** ��  ��  : pgchip      GPIO оƬ
**           uiNum       GPIO��ϵͳ�еı��
**           bIsLevel    �Ƿ�Ϊ��ƽ����, 1 ��ʾ��ƽ������0 ��ʾ���ش���
**           uiType      ���Ϊ��ƽ����, 1 ��ʾ�ߵ�ƽ����, 0 ��ʾ�͵�ƽ����
**                       ���Ϊ���ش���, 1 ��ʾ�����ش���, 0 ��ʾ�½��ش���, 2 ˫���ش���
** ��  ��  : IRQ ������ -1:����
*********************************************************************************************************/
static ULONG  sunxiR16GpioGetIrq (PLW_GPIO_CHIP  pgchip, UINT  uiNum,
                            BOOL  bIsLevel, UINT  uiType)
{
    UINT32  uiPortNum;
    INT32   iGpioSoc = gpioSysToSoc(uiNum);

    if (iGpioSoc == PX_ERROR) {
        return  (-1);
    }

    /*
     *  �������
     */
    uiPortNum  = GET_SOC_PORT_NUM(iGpioSoc);

    if (uiPortNum == GPIO_PORT_B) {
        return  (PB_EINT);
    } else if (uiPortNum == GPIO_PORT_G) {
        return  (PG_EINT);
    } else {
        return  (-1);
    }
}

/*********************************************************************************************************
** ��������: gpioDrvInstall
** ��������: ��װ GPIO ����
** ��  ��  : NONE
** ��  ��  : ERROR_CODE
*********************************************************************************************************/
INT  gpioDrvInstall (VOID)
{
    static LW_GPIO_CHIP  t3GpioChip = {
        .GC_pcLabel              = "sunxi R16 GPIO",
        .GC_ulVerMagic           = LW_GPIO_VER_MAGIC,
        .GC_uiBase               = 0,
        .GC_uiNGpios             = GPIO_AMOUNT,
        .GC_pfuncRequest         = sunxiR16GpioRequest,
        .GC_pfuncFree            = sunxiR16GpioFree,
        .GC_pfuncGetDirection    = sunxiR16GpioGetDirection,
        .GC_pfuncDirectionInput  = sunxiR16GpioDirectionInput,
        .GC_pfuncGet             = sunxiR16GpioGet,
        .GC_pfuncDirectionOutput = sunxiR16GpioDirectionOutput,
        .GC_pfuncSetDebounce     = LW_NULL,
        .GC_pfuncSetPull         = LW_NULL,
        .GC_pfuncSet             = sunxiR16GpioSet,
        .GC_pfuncSetupIrq        = sunxiR16GpioSetupIrq,
        .GC_pfuncClearIrq        = sunxiR16GpioClearIrq,
        .GC_pfuncSvrIrq          = sunxiR16GpioSvrIrq,
        .GC_pfuncGetIrq          = sunxiR16GpioGetIrq,
    };

    return  (API_GpioChipAdd(&t3GpioChip));
}
/*********************************************************************************************************
  END
*********************************************************************************************************/
