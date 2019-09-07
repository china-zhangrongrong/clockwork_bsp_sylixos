/*
 * armGic.h
 *
 *  Created on: Jun 6, 2019
 *      Author: databus
 */

#ifndef SYLIXOS_DRIVER_GIC_ARMGIC_H_
#define SYLIXOS_DRIVER_GIC_ARMGIC_H_


/*********************************************************************************************************
  �������ж�ѡ��
*********************************************************************************************************/
#define GIC_SW_INT_OPTION_USE_TARGET_LIST   (0)                         /*  ʹ�� TargetList ����        */
#define GIC_SW_INT_OPTION_ALL_OTHER_CPUS    (1)                         /*  �������� CPU �����ж�       */
#define GIC_SW_INT_OPTION_ONLY_THIS_CPU     (2)                         /*  ����ǰ CPU �����ж�         */

VOID  armGicEnable(BOOL  bEnable);
VOID  armGicIrqSecuritySet(UINT32  uiIrqID, BOOL  bSecurity);
VOID  armGicIrqEnable(UINT32  uiIrqID, BOOL  bEnable);
BOOL  armGicIrqIsEnable(UINT32  uiIrqID);
VOID  armGicIrqPrioritySet(UINT32  uiIrqID, UINT32  uiPriority);
VOID  armGicIrqTargetSet(UINT32  uiIrqID, UINT32  uiCpuMask, BOOL  bEnable);
VOID  armGicIrqTargetGet(UINT32  uiIrqID, UINT32  *puiCpuId);
VOID  armGicSoftwareIntSend(UINT32  uiIrqID, UINT32  uiOption, UINT32  uiTargetList);
VOID  armGicCpuEnable(BOOL  bEnable);
VOID  armGicCpuPriorityMaskSet(UINT32  uiPriority);
UINT32  armGicIrqReadAck(VOID);
VOID  armGicIrqWriteDone(UINT32  uiIrqID);
VOID  armGicInit(VOID);
VOID  armGicCpuInit(BOOL  bPreemption,  UINT32  uiPriority);
VOID  armGicIntVecterEnable(ULONG  ulVector,  BOOL  bSecurity, ULONG  ulPriority, ULONG  uiCpuMask);
VOID  armGicIntVecterDisable(ULONG  ulVector);

#endif /* SYLIXOS_DRIVER_GIC_ARMGIC_H_ */
