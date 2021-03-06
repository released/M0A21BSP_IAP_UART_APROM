/**************************************************************************//**
 * @file     gpio.c
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 20/06/18 6:28p $
 * @brief    M0A21 Series General Purpose I/O (GPIO) Driver Source File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 ****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Set GPIO operation mode
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT5 for PA
 *                          It could be BIT4 ~ BIT7 for PB
 *                          It could be BIT0 ~ BIT7 for PC
 *                          It could be BIT0 ~ BIT7 for PD
 * @param[in]   u32Mode     Operation mode.  It could be
 *                          - \ref GPIO_MODE_INPUT
 *                          - \ref GPIO_MODE_OUTPUT
 *                          - \ref GPIO_MODE_OPEN_DRAIN
 *                          - \ref GPIO_MODE_QUASI
 * @return      None
 * @details     This function is used to set specified GPIO operation mode.
 */
void GPIO_SetMode(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t i;

    for(i = 0; i < GPIO_PIN_MAX; i++)
    {
        if(u32PinMask & (1 << i))
        {
            port->MODE = (port->MODE & ~(GPIO_MODE_MODE0_Msk << (i << 1))) | (u32Mode << (i << 1));
        }
    }
}

/**
 * @brief       Enable GPIO interrupt
 * @param[in]   port            GPIO port. It could be PA, PB, PC, PD.
 * @param[in]   u32Pin          The pin of specified GPIO port.
 *                              It could be 0 ~ 5 for PA
 *                              It could be 4 ~ 7 for PB
 *                              It could be 0 ~ 7 for PC
 *                              It could be 0 ~ 7 for PD
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be
 *                            - \ref GPIO_INT_RISING
 *                            - \ref GPIO_INT_FALLING
 *                            - \ref GPIO_INT_BOTH_EDGE
 *                            - \ref GPIO_INT_HIGH
 *                            - \ref GPIO_INT_LOW
 * @return      None
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_EnableInt(GPIO_T *port, uint32_t u32Pin, uint32_t u32IntAttribs)
{
    /* Configure interrupt mode of specified pin */
    port->INTTYPE |= (((u32IntAttribs >> 24) & 0xFFUL) << u32Pin);

    /* Enable interrupt function of specified pin */
    port->INTEN |= ((u32IntAttribs & 0xFFFFFFUL) << u32Pin);
}

/**
 * @brief       Disable GPIO interrupt
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD.
 * @param[in]   u32Pin      The pin of specified GPIO port. \n
 *                          It could be 0 ~ 5 for PA
 *                          It could be 4 ~ 7 for PB
 *                          It could be 0 ~ 7 for PC
 *                          It could be 0 ~ 7 for PD
 * @return      None
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_DisableInt(GPIO_T *port, uint32_t u32Pin)
{
    /* Configure interrupt mode of specified pin */
    port->INTTYPE &= ~(1UL << u32Pin);

    /* Disable interrupt function of specified pin */
    port->INTEN &= ~((0x00010001UL) << u32Pin);
}

/**
 * @brief       Set GPIO Pull-up and Pull-down control
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *                          It could be BIT0 ~ BIT5 for PA
 *                          It could be BIT4 ~ BIT7 for PB
 *                          It could be BIT0 ~ BIT7 for PC
 *                          It could be BIT0 ~ BIT7 for PD
 * @param[in]   u32Mode     The pin mode of specified GPIO pin. It could be
 *                              \ref GPIO_PUSEL_DISABLE
 *                              \ref GPIO_PUSEL_PULL_UP
 * @return      None
 * @details     Set the pin pull-up mode of specified GPIO pin.
 */
void GPIO_SetPullCtl(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t i;

    for(i = 0ul; i < GPIO_PIN_MAX; i++)
    {
        if(u32PinMask & (BIT0 << i))
        {
            port->PUSEL = (port->PUSEL & ~(GPIO_PUSEL_PUSEL0_Msk << i)) | (u32Mode << i);
        }
    }
}

/*@}*/ /* end of group GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group GPIO_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2020 Nuvoton Technology Corp. ***/
