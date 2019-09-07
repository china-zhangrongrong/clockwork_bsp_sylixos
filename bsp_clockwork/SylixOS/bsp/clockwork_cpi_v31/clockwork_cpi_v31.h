/*
 * clockwork_cpi_v31.h
 *
 *  Created on: Jun 3, 2019
 *      Author: databus
 */

#ifndef SYLIXOS_BSP_CLOCKWORK_CPI_V31_CLOCKWORK_CPI_V31_H_
#define SYLIXOS_BSP_CLOCKWORK_CPI_V31_CLOCKWORK_CPI_V31_H_

/*********************************************************************************************************
  �弶������
*********************************************************************************************************/
#define BSP_CFG_PLATFORM_NAME               "ClockworkPI (CPI v3.1) development board"

/*********************************************************************************************************
  ��׼�����������
*********************************************************************************************************/
#define BSP_CFG_STD_FILE                    "/dev/ttyS0"
#define BSP_CFG_DEBUG_CH                    0                           /* ������Ϣ���ͨ��             */

/*********************************************************************************************************
  CPU ���
*********************************************************************************************************/
#define ARM_SW_INT_VECTOR(cpuid)            cpuid                       /*  ��������ж� ID             */
#define ARM_SW_INT_PRIORITY                 0                           /*  ��������ж����ȼ�          */
#define ARM_TICK_INT_VECTOR                 50                          /*  TICK �ж� ID                */
#define ARM_TICK_INT_PRIORITY               1                           /*  TICK �ж����ȼ�             */
#define ARM_DEFAULT_INT_PRIORITY            127                         /*  Ĭ�ϵ��ж����ȼ�            */
#define BSP_CFG_CPU_NUM                     4                           /*  CPU��                       */
/*********************************************************************************************************
  ROM RAM �������
*********************************************************************************************************/
#define BSP_CFG_ROM_BASE                    (0x00000000)
#define BSP_CFG_ROM_SIZE                    (4 * 1024 * 1024)           /*  ���� 4M �ռ�                */

#define BSP_CFG_RAM_START                   0x40000000                  /*  �ڴ��ַ                    */
#define BSP_CFG_RAM_BASE                    (BSP_CFG_RAM_START)
#define BSP_CFG_RAM_SIZE                    (1 * 1024 * 1024 * 1024)

#define BSP_CFG_TEXT_SIZE                   (6   * 1024 * 1024)
#define BSP_CFG_DATA_SIZE                   (121 * 1024 * 1024)

#define BSP_CFG_DMA_SIZE                    (128 * 1024 * 1024)
#define BSP_CFG_APP_SIZE                    (BSP_CFG_RAM_SIZE  - BSP_CFG_TEXT_SIZE - \
                                             BSP_CFG_DATA_SIZE - BSP_CFG_DMA_SIZE)

#define BSP_CFG_BOOT_STACK_SIZE             (4 * 128 * 1024)

/*********************************************************************************************************
  �����ڴ�ռ� �������
*********************************************************************************************************/
#define BSP_CFG_VAPP_START                  0x80000000
#define BSP_CFG_VAPP_SIZE                   (1 * LW_CFG_GB_SIZE)

#define BSP_CFG_VIO_START                   0xC0000000
#define BSP_CFG_VIO_SIZE                    (64  * LW_CFG_MB_SIZE)

/*********************************************************************************************************
  ���ļ�ϵͳ�����豸����(ֻ��ѡ��һ��)
*********************************************************************************************************/
#define BSP_CFG_NAND_ROOTFS_EN              0                           /*  �� NAND ��Ϊ���ļ�ϵͳ�洢  */
#define BSP_CFG_SD_ROOTFS_EN                0                           /*  �� SD ����Ϊ���ļ�ϵͳ�洢  */
#define BSP_CFG_HDD_ROOTFS_EN               0                           /*  ��Ӳ����Ϊ���ļ�ϵͳ�洢    */
#define BSP_CFG_RAM_ROOTFS_EN               1                           /*  ���ڴ����洢(ͨ��Ϊ����)    */

/*********************************************************************************************************
  ��ȷ�������ϵĸ��ļ�ϵͳ�洢�豸��
  ����������������:
  BSP_CFG_BOOT_DIR: ���ϵͳ������������
  BSP_CFG_WORK_DIR: ϵͳ������Ŀ¼
  ����Ѵ洢�豸һ���������, һ����ר�Ŵ����boot�йص�����, ��һ����Ϊ������
  ��ȻҲ����ֻ��һ������, ��ֻ�轫�����Ӧ�������궨��Ϊ��ͬ����
*********************************************************************************************************/
#if BSP_CFG_NAND_ROOTFS_EN > 0
#define BSP_CFG_FS_DIR                      "rfsmap=/boot:/yaffs2/n0,/:/yaffs2/n1"
#endif

#if BSP_CFG_SD_ROOTFS_EN > 0
#define BSP_CFG_FS_DIR                      "rfsmap=/boot:/media/sdcard0,/:/media/sdcard1"
#endif

#if BSP_CFG_HDD_ROOTFS_EN > 0
#define BSP_CFG_FS_DIR                      "rfsmap=/boot:/media/hdd0,/:/media/hdd1"
#endif

#if BSP_CFG_RAM_ROOTFS_EN > 0
#define BSP_CFG_FS_DIR                      "rfsmap=/:/dev/ram"
#endif
/*********************************************************************************************************
**  �����������ļ�ϵͳ��������
*********************************************************************************************************/
#define MOUNT_PARAMETERS                    BSP_CFG_FS_DIR
/*********************************************************************************************************
  �ں�����������ض���
*********************************************************************************************************/
#define __STR__(x)                          __STRING(x)
#if defined(BSP_CFG_CPU_NUM)
#define NCPUS                              "ncpus=" __STR__(BSP_CFG_CPU_NUM)
#else
#define NCPUS                              "ncpus=4"
#endif

#endif /* SYLIXOS_BSP_CLOCKWORK_CPI_V31_CLOCKWORK_CPI_V31_H_ */
