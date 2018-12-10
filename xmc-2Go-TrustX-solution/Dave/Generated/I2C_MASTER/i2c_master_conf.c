/*********************************************************************************************************************
* DAVE APP Name : I2C_MASTER       APP Version: 4.1.26
*
* NOTE:
* This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
*********************************************************************************************************************/

/**
 * @cond
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015-2018, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-02-16:
 *     - Initial version<br>
 *
 * 2015-04-06:
 *     - Optimized generation of config code<br>
 *
 * 2015-07-29:
 *     - Added DMA, direct mode support<br>
 *
 * 2018-02-20:
 *     - Within dma_tx_handler() tx_callback only called if transmitting
 *     - Added digital filter
 *
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "i2c_master.h" 
#if (UC_FAMILY == XMC1)
#include "xmc_scu.h"
#endif
/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/
/*
 * Function implements the data transmission. It is called from the transmit interrupt service handler.
 * Function pushes data to the output block and releases control. It is called again when the previous data is
 * transmitted. When transmit FIFO is used, the function sets the trigger limit based on the size of data to be
 * transmitted. This makes sure that the CPU usage is optimum.
 *
 * I2C_MASTER_t * pointer to the I2C_MASTER APP instance handle
 *
 */
void I2C_MASTER_TransmitHandler(I2C_MASTER_t * const handle);

/*
 * Function implements the data reception. It is called from the receive interrupt service handler.
 * Function reads data from the receive block and updates the user's buffer. It is called again when the data is
 * received again. When receive FIFO is used, the function sets the trigger limit based on the size of data to be
 * received. This makes sure that the CPU usage is optimum.
 *
 * I2C_MASTER_t * pointer to the I2C_MASTER APP instance handle
 *
 */
void I2C_MASTER_ReceiveHandler(I2C_MASTER_t * const handle);

void i2c_master_0_init(void);
#if (I2C_MASTER_DMA_TX_ENABLED == 1)
void i2c_master_0_dma_tx_handler(XMC_DMA_CH_EVENT_t event);
#endif
#if (I2C_MASTER_DMA_RX_ENABLED == 1)
void i2c_master_0_dma_rx_handler(XMC_DMA_CH_EVENT_t event);
#endif
  static const XMC_GPIO_CONFIG_t i2c_master_0_sda_pin_config   =
  { 
    .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7,
    .output_level   = XMC_GPIO_OUTPUT_LEVEL_HIGH,
  }; 
  static const XMC_GPIO_CONFIG_t i2c_master_0_scl_pin_config   =
  { 
    .mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT6,
    .output_level  = XMC_GPIO_OUTPUT_LEVEL_HIGH,
  }; 
const XMC_I2C_CH_CONFIG_t i2c_master_0_channel_config =
{
  .baudrate = (uint32_t)(400000U),
  .address  = 0
};

static void i2c_master_0_disable_io(void)
{
  XMC_GPIO_SetMode((XMC_GPIO_PORT_t *)PORT2_BASE, (uint8_t)10, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_GPIO_SetMode((XMC_GPIO_PORT_t *)PORT2_BASE, (uint8_t)11, XMC_GPIO_MODE_INPUT_TRISTATE);
}

static void i2c_master_0_enable_io(void)
{
  XMC_GPIO_SetMode((XMC_GPIO_PORT_t *)PORT2_BASE, (uint8_t)10, i2c_master_0_sda_pin_config.mode);
  XMC_GPIO_SetMode((XMC_GPIO_PORT_t *)PORT2_BASE, (uint8_t)11, i2c_master_0_scl_pin_config.mode);
}

const I2C_MASTER_CONFIG_t i2c_master_0_config =
{
  .brg_config = &i2c_master_0_channel_config,
  .fptr_i2c_config = i2c_master_0_init,
  .fptr_i2c_enable_io = i2c_master_0_enable_io,
  .fptr_i2c_disable_io = i2c_master_0_disable_io,
  .tx_cbhandler = i2c_master_end_of_transmit_callback,
  .rx_cbhandler = i2c_master_end_of_receive_callback,
  .nack_cbhandler = i2c_master_nack_received_callback,
  .arbitration_cbhandler = i2c_master_arbitration_lost_callback,
  .error_cbhandler = i2c_master_error_detected_callback,
  .transmit_mode = I2C_MASTER_TRANSFER_MODE_INTERRUPT,
  .receive_mode = I2C_MASTER_TRANSFER_MODE_INTERRUPT,
  .txFIFO_size = XMC_USIC_CH_FIFO_SIZE_16WORDS,
 
  .rxFIFO_size = XMC_USIC_CH_FIFO_SIZE_16WORDS,
  
#if defined(i2c_master_0_TX_IRQN)
  .tx_irqn = i2c_master_0_TX_IRQN,
#else
  .tx_irqn = -1,
#endif

#if defined(i2c_master_0_RX_IRQN)
  .rx_irqn = i2c_master_0_RX_IRQN
#else
  .rx_irqn = -1
#endif

};
I2C_MASTER_RUNTIME_t i2c_master_0_runtime =
{
  .tx_ack_sr = 0x4U,
  .tx_busy = false,
  .rx_sr = 0x2U,
  .rx_busy = false,
  .bus_acquired = false
};

I2C_MASTER_t i2c_master_0 =
{
  .channel = XMC_I2C0_CH1,
  .config = &i2c_master_0_config,
  .runtime = &i2c_master_0_runtime,
};

void i2c_master_0_init(void)
{
 
  const uint32_t enabled_protocol_events = (uint32_t)(XMC_I2C_CH_EVENT_NACK | 
                               XMC_I2C_CH_EVENT_ARBITRATION_LOST | 
                               XMC_I2C_CH_EVENT_ERROR); 

  const uint32_t tx_fifo_events = (uint32_t)(0);
  const uint32_t rx_fifo_events = (uint32_t)(XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE | XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD);
  XMC_I2C_CH_Init(XMC_I2C0_CH1, &i2c_master_0_channel_config);

  XMC_USIC_CH_SetInputSource(XMC_I2C0_CH1, XMC_USIC_CH_INPUT_DX0, 5);
  XMC_USIC_CH_SetInputSource(XMC_I2C0_CH1, XMC_USIC_CH_INPUT_DX1, 4);

  XMC_USIC_CH_SetInputSource(XMC_I2C0_CH1, XMC_USIC_CH_INPUT_DX3, 0U);
  XMC_USIC_CH_SetInputSource(XMC_I2C0_CH1, XMC_USIC_CH_INPUT_DX4, 0U);
  XMC_USIC_CH_SetInputSource(XMC_I2C0_CH1, XMC_USIC_CH_INPUT_DX5, 0U);
  /* configure i2c tx fifo */
  XMC_USIC_CH_TXFIFO_Configure(XMC_I2C0_CH1,
                               16,
                               XMC_USIC_CH_FIFO_SIZE_16WORDS,
                               (uint32_t)1);
  XMC_USIC_CH_TXFIFO_SetInterruptNodePointer(XMC_I2C0_CH1,
                                               XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD,
                                             ((uint32_t)4));
  XMC_USIC_CH_TXFIFO_EnableEvent(XMC_I2C0_CH1, tx_fifo_events);
  /* configure i2c rx fifo */
  XMC_USIC_CH_RXFIFO_Configure(XMC_I2C0_CH1,
                               0,
                               XMC_USIC_CH_FIFO_SIZE_16WORDS,
                                (uint32_t)(15));
  XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(XMC_I2C0_CH1,
                                               XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD,
                                              ((uint32_t)0x2));
  XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(XMC_I2C0_CH1,
                                               XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE,
                                              ((uint32_t)0x2));
  XMC_USIC_CH_RXFIFO_EnableEvent(XMC_I2C0_CH1, rx_fifo_events);
  XMC_USIC_CH_SetInterruptNodePointer(XMC_I2C0_CH1,
                                      XMC_USIC_CH_INTERRUPT_NODE_POINTER_PROTOCOL,
                                       ((uint32_t)0));
  XMC_I2C_CH_EnableEvent(XMC_I2C0_CH1, enabled_protocol_events);
  XMC_I2C_CH_Start(XMC_I2C0_CH1);

  XMC_GPIO_Init((XMC_GPIO_PORT_t *)PORT2_BASE, (uint8_t)10, &i2c_master_0_sda_pin_config);
  XMC_GPIO_Init((XMC_GPIO_PORT_t *)PORT2_BASE, (uint8_t)11, &i2c_master_0_scl_pin_config);

  NVIC_SetPriority((IRQn_Type)13, 3);
  NVIC_EnableIRQ((IRQn_Type)13);
  NVIC_SetPriority((IRQn_Type)11, 3);
  NVIC_EnableIRQ((IRQn_Type)11);}
/*Transmit ISR*/
void i2c_master_0_TX_HANDLER()
{
  I2C_MASTER_TransmitHandler(&i2c_master_0);
}
/*Receive ISR*/
void i2c_master_0_RX_HANDLER()
{
  I2C_MASTER_ReceiveHandler(&i2c_master_0);
}

