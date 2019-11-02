/*********************************************************************************************************
**
**                                    �й������Դ��֯
**
**                                   Ƕ��ʽʵʱ����ϵͳ
**
**                                       SylixOS(TM)
**
**                               Copyright  All Rights Reserved
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**
** ��   ��   ��: bspMap.h
**
** ��   ��   ��: Han.Hui (����)
**
** �ļ���������: 2008 �� 12 �� 23 ��
**
** ��        ��: C ������ڲ���. �����ҳ�ռ���ȫ��ӳ���ϵ����.
*********************************************************************************************************/

#ifndef __BSPMAP_H
#define __BSPMAP_H

/*********************************************************************************************************
   �ڴ�����ϵͼ

    +-----------------------+--------------------------------+
    |       ͨ���ڴ���      |          VMM ������            |
    |         CACHE         |                                |
    +-----------------------+--------------------------------+

*********************************************************************************************************/
/*********************************************************************************************************
  physical memory
*********************************************************************************************************/
#ifdef  __BSPINIT_MAIN_FILE

LW_MMU_PHYSICAL_DESC    _G_physicalDesc[] = {
    {                                                                   /*  �ж�������                  */
        BSP_CFG_RAM_BASE,
        0,
        LW_CFG_VMM_PAGE_SIZE,
        LW_PHYSICAL_MEM_VECTOR
    },

    {                                                                   /*  �ں˴����                  */
        BSP_CFG_RAM_BASE,
        BSP_CFG_RAM_BASE,
        BSP_CFG_TEXT_SIZE,
        LW_PHYSICAL_MEM_TEXT
    },

    {                                                                   /*  �ں����ݶ�                  */
        BSP_CFG_RAM_BASE + BSP_CFG_TEXT_SIZE,
        BSP_CFG_RAM_BASE + BSP_CFG_TEXT_SIZE,
        BSP_CFG_DATA_SIZE,
        LW_PHYSICAL_MEM_DATA
    },

    {                                                                   /*  DMA ������                  */
        BSP_CFG_RAM_BASE + BSP_CFG_TEXT_SIZE + BSP_CFG_DATA_SIZE,
        BSP_CFG_RAM_BASE + BSP_CFG_TEXT_SIZE + BSP_CFG_DATA_SIZE,
        BSP_CFG_DMA_SIZE,
        LW_PHYSICAL_MEM_DMA
    },

    {                                                                   /*  APP ͨ���ڴ�                */
        BSP_CFG_RAM_BASE + BSP_CFG_TEXT_SIZE + BSP_CFG_DATA_SIZE + BSP_CFG_DMA_SIZE,
        BSP_CFG_RAM_BASE + BSP_CFG_TEXT_SIZE + BSP_CFG_DATA_SIZE + BSP_CFG_DMA_SIZE,
        BSP_CFG_APP_SIZE,
        LW_PHYSICAL_MEM_APP
    },

    {                                                                   /*  system control              */
        0x01c00000,
        0x01c00000,
        LW_CFG_VMM_PAGE_SIZE,
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  LCD                         */
        0x1c0c000,
        0x1c0c000,
        LW_CFG_VMM_PAGE_SIZE,
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  UART0 ~ 4                   */
        0x01C28000,
        0x01C28000,
        2 * LW_CFG_VMM_PAGE_SIZE,
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  USB OTG                     */
        0x01c19000,
        0x01c19000,
        LW_CFG_VMM_PAGE_SIZE,
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  USB OHCI0                   */
        0x01c1a000,
        0x01c1a000,
        LW_CFG_VMM_PAGE_SIZE,
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  CCU,PIO,TIMER               */
        0x01c20000,
        0x01c20000,
        LW_CFG_VMM_PAGE_SIZE,
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  R_PIO                       */
        0x01f02000,
        0x01f02000,
        LW_CFG_VMM_PAGE_SIZE,
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  GIC                         */
        0x01C80000,
        0x01C80000,
        (LW_CFG_VMM_PAGE_SIZE * 4),
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  DEBE                         */
        0x01E60000,
        0x01E60000,
        (LW_CFG_VMM_PAGE_SIZE * 16),
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  R_CPUCFG                    */
        0x01f01000,
        0x01f01000,
        LW_CFG_VMM_PAGE_SIZE,
        LW_PHYSICAL_MEM_BOOTSFR
    },

    {                                                                   /*  ����                        */
        0,
        0,
        0,
        0
    }
};
/*********************************************************************************************************
  virtual memory
*********************************************************************************************************/
LW_MMU_VIRTUAL_DESC    _G_virtualDesc[] = {
    {                                                                   /*  Ӧ�ó�������ռ�            */
        BSP_CFG_VAPP_START,
        BSP_CFG_VAPP_SIZE,
        LW_VIRTUAL_MEM_APP
    },
    {
        BSP_CFG_VIO_START,                                              /*  ioremap �ռ�                */
        BSP_CFG_VIO_SIZE,
        LW_VIRTUAL_MEM_DEV
    },
    {                                                                   /*  ����                        */
        0,
        0,
        0
    }
};

#endif                                                                  /*  __BSPINIT_MAIN_FILE         */
#endif                                                                  /*  __BSPMAP_H                  */
/*********************************************************************************************************
  END
*********************************************************************************************************/
