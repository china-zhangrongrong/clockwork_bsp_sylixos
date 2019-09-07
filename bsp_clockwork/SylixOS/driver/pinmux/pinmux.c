/*
 * pinmux.c
 *
 *  Created on: Jun 9, 2019
 *      Author: databus
 */

#define __SYLIXOS_KERNEL
#include <SylixOS.h>
#include <linux/compat.h>
#include "driver/pinmux/pinmux.h"

/*********************************************************************************************************
 SylixOS GPIO��ź�R16оƬGPIO���ӳ���
*********************************************************************************************************/
static const  UINT16  _G_usSunxiR16Gpios[] = {
    GPIO_NUM(GPIO_PORT_B, GPIO_PIN_00),
    GPIO_NUM(GPIO_PORT_B, GPIO_PIN_01),
    GPIO_NUM(GPIO_PORT_B, GPIO_PIN_02),
    GPIO_NUM(GPIO_PORT_B, GPIO_PIN_03),
    GPIO_NUM(GPIO_PORT_B, GPIO_PIN_04),
    GPIO_NUM(GPIO_PORT_B, GPIO_PIN_05),
    GPIO_NUM(GPIO_PORT_B, GPIO_PIN_06),
    GPIO_NUM(GPIO_PORT_B, GPIO_PIN_07),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_00),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_01),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_02),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_03),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_04),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_05),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_06),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_07),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_08),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_09),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_10),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_11),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_12),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_13),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_14),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_15),
    GPIO_NUM(GPIO_PORT_C, GPIO_PIN_16),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_00),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_01),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_02),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_03),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_04),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_05),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_06),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_07),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_08),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_09),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_10),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_11),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_12),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_13),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_14),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_15),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_16),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_17),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_18),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_19),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_20),
    GPIO_NUM(GPIO_PORT_D, GPIO_PIN_21),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_00),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_01),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_02),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_03),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_04),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_05),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_06),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_07),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_08),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_09),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_10),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_11),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_12),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_13),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_14),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_15),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_16),
    GPIO_NUM(GPIO_PORT_E, GPIO_PIN_17),
    GPIO_NUM(GPIO_PORT_F, GPIO_PIN_00),
    GPIO_NUM(GPIO_PORT_F, GPIO_PIN_01),
    GPIO_NUM(GPIO_PORT_F, GPIO_PIN_02),
    GPIO_NUM(GPIO_PORT_F, GPIO_PIN_03),
    GPIO_NUM(GPIO_PORT_F, GPIO_PIN_04),
    GPIO_NUM(GPIO_PORT_F, GPIO_PIN_05),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_00),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_01),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_02),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_03),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_04),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_05),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_06),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_07),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_08),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_09),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_10),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_11),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_12),
    GPIO_NUM(GPIO_PORT_G, GPIO_PIN_13),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_00),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_01),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_02),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_03),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_04),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_05),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_06),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_07),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_08),
    GPIO_NUM(GPIO_PORT_H, GPIO_PIN_09),
};
/*********************************************************************************************************
** ��������: gpioSysToSoc
** ��������: ��GPIO ��ϵͳ�еı��ת��ΪSOC�е�pin��ź�port���
** ��  ��  : uiNum    GPIO ��ϵͳ�еı��
** ��  ��  : uiOffset  ��5λ��pin��ţ���λΪport���;���Ϸ���ΪPX_ERROR
*********************************************************************************************************/
INT32  gpioSysToSoc (UINT32  uiNum)
{
   if (uiNum < (sizeof(_G_usSunxiR16Gpios) / sizeof(_G_usSunxiR16Gpios[0]))) {
       return  (_G_usSunxiR16Gpios[uiNum]);
   }

   return  (PX_ERROR);
}
/*********************************************************************************************************
** ��������: GpioPinmuxSet
** ��������: ���� GPIO �ܽŵĹ���ѡ��
** ��  ��  : uiNum    GPIO ��ϵͳ�еı��
**           uiCfg       �ܽŹ������� 0��7
** ��  ��  : 0: ��ȷ -1:����
** ��    ע: ���Ź���ѡ��Ĵ���ֻ�ܰ�4�ֽڶ����ַ����
*********************************************************************************************************/
INT32  gpioPinmuxSet (UINT32  uiNum, UINT32 uiCfg)
{
    addr_t  ulAddr;
    UINT32  uiValue;
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

    /*
     *  ������ź����ź�ȷ��Ҫ�����ĸ��Ĵ���
     */
    ulAddr = ((uiPinNum / 8) * 4) + (uiPortNum * 0x24) + GPIO_BASE;

    /*
     *  ������ֵ
     */
    uiCfg   &= 0x00000007;
    uiValue  = readl(ulAddr);
    uiValue &= ~(0x0f << ((uiPinNum % 8) * 4));
    uiValue |= (uiCfg << ((uiPinNum % 8) * 4));
    writel(uiValue, ulAddr);

    return  (ERROR_NONE);
}
/*********************************************************************************************************
** ��������: GpioPinmuxGet
** ��������: ��ȡ GPIO �ܽŵĹ���ѡ��
** ��  ��  : uiNum    GPIO ��ϵͳ�еı��
** ��  ��  : �ܽŹ������� 0��7,����ʱ����-1
** ��    ע: ���Ź���ѡ��Ĵ���ֻ�ܰ�4�ֽڶ����ַ����
*********************************************************************************************************/
INT32  gpioPinmuxGet (UINT32  uiNum)
{
    addr_t  ulAddr;
    UINT32  uiValue;
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

    /*
     *  ������ź����ź�ȷ��Ҫ�����ĸ��Ĵ���
     */
    ulAddr = ((uiPinNum / 8) * 4) + (uiPortNum * 0x24) + GPIO_BASE;

    uiValue  = readl(ulAddr);
    uiValue  = uiValue >> ((uiPinNum % 8) * 4);
    uiValue &= 0x00000007;

    return  (uiValue);
}
/*********************************************************************************************************
  END
*********************************************************************************************************/
