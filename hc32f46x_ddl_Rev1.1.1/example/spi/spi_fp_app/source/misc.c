/******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd. All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co.,Ltd ("HDSC").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with HDSC
 * components. This software is licensed by HDSC to be adapted only
 * for use in systems utilizing HDSC components. HDSC shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein. HDSC is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * Disclaimer:
 * HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACCOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 */
/******************************************************************************/
/** \file misc.c
 **
 ** A detailed description is available at
 ** @link
        This file includes misc I/F for goodix app.
    @endlink
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ddl.h"
#include "misc.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* SPI_SCK Port/Pin definition */
#define SPI_SCK_PORT                    (PortB)
#define SPI_SCK_PIN                     (Pin13)
#define SPI_SCK_FUNC                    (Func_Spi3_Sck)

/* SPI_MOSI Port/Pin definition */
#define SPI_MOSI_PORT                   (PortB)
#define SPI_MOSI_PIN                    (Pin15)
#define SPI_MOSI_FUNC                   (Func_Spi3_Mosi)

/* SPI_MISO Port/Pin definition */
#define SPI_MISO_PORT                   (PortB)
#define SPI_MISO_PIN                    (Pin14)
#define SPI_MISO_FUNC                   (Func_Spi3_Miso)

/* SPI unit and clock definition */
#define SPI_UNIT_CLOCK                  (PWC_FCG1_PERIPH_SPI3)

#define SPI_DUMMY_BYTE_VALUE            (0xffu)

#define SPI_DMA_TX_UNIT                 (M4_DMA1)
#define SPI_DMA_TX_CH                   (DmaCh0)
#define SPI_MASTER_DMA_TX_IRQn          (Int000_IRQn)
#define SPI_MASTER_DMA_TX_INT_SRC       (INT_DMA1_TC0)
#define SPI_DMA_TX_TRIG_SOURCE          (EVT_SPI3_SPTI)

#define SPI_DMA_RX_UNIT                 (M4_DMA1)
#define SPI_DMA_RX_CH                   (DmaCh1)
#define SPI_MASTER_DMA_RX_IRQn          (Int001_IRQn)
#define SPI_MASTER_DMA_RX_INT_SRC       (INT_DMA1_TC1)
#define SPI_DMA_RX_TRIG_SOURCE          (EVT_SPI3_SPRI)

#define DP_PORT                         (PortA)
#define DP_PIN                          (Pin12)
#define DP_EXINT_CH                     (ExtiCh12)
#define DP_INT_IRQn                     (Int002_IRQn)
#define DP_INT_SRC                      (INT_PORT_EIRQ12)

#define DM_PORT                         (PortA)
#define DM_PIN                          (Pin11)
#define DM_EXINT_CH                     (ExtiCh11)
#define DM_INT_IRQn                     (Int003_IRQn)
#define DM_INT_SRC                      (INT_PORT_EIRQ11)

#define EC_PORT                         (PortA)
#define EC_PIN                          (Pin05)
#define EC_EXINT_CH                     (ExtiCh05)
#define EC_INT_IRQn                     (Int004_IRQn)
#define EC_INT_SRC                      (INT_PORT_EIRQ5)

#define FP_PORT                         (PortA)
#define FP_PIN                          (Pin00)
#define FP_EXINT_CH                     (ExtiCh00)
#define FP_INT_IRQn                     (Int005_IRQn)
#define FP_INT_SRC                      (INT_PORT_EIRQ0)
////////////////////////////////////////////////////////////////////////

/* USART channel definition */
#define USART_UNIT                      (M4_USART4)
#define USART_UNIT_CLOCK                (PWC_FCG1_PERIPH_USART4)

/* USART baudrate definition */
//#define USART_BAUDRATE                  (3000000ul)

/* USART CK Port/Pin definition */
#define USART_CK_PORT                   (PortB)
#define USART_CK_PIN                    (Pin00)
#define USART_CK_FUNC                   (Func_Usart_Ck)
/* USART RX Port/Pin definition */
#define USART_RX_PORT                   (PortB)
#define USART_RX_PIN                    (Pin03)
#define USART_RX_FUNC                   (Func_Usart4_Rx)
#define USART_RX_EXINT_CH               (ExtiCh03)
#define USART_RX_INT_IRQn               (Int009_IRQn)
#define USART_RX_INT_SRC                (INT_PORT_EIRQ3)

/* USART TX Port/Pin definition */
#define USART_TX_PORT                   (PortB)
#define USART_TX_PIN                    (Pin04)
#define USART_TX_FUNC                   (Func_Usart4_Tx)

/* DMAC */
#define USART_TX_DMA_UNIT               (M4_DMA2)
#define USART_TX_DMA_CH                 (DmaCh0)
#define USART_TX_DMA_TRG_SEL            (EVT_USART4_TI)

#define USART_RX_DMA_UNIT               (M4_DMA2)
#define USART_RX_DMA_CH                 (DmaCh1)
#define USART_RX_DMA_TRG_SEL            (EVT_USART4_RI)

/* USART interrupt number  */
#define USART_EI_NUM                    (INT_USART4_EI)
#define USART_EI_IRQn                   (Int006_IRQn)

/* DMA block transfer complete interrupt */
#define TX_DMA_BTC_INT_NUM              (INT_DMA2_TC0)
#define TX_DMA_BTC_INT_IRQn             (Int007_IRQn)

#define RX_DMA_BTC_INT_NUM              (INT_DMA2_TC1)
#define RX_DMA_BTC_INT_IRQn             (Int008_IRQn)


////////////////////////////////////////////////////////////


/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
//extern  USB_OTG_CORE_HANDLE      USB_OTG_dev;
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static const uint8_t SpiDummyByte = 0xFFu;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief  NVIC priority group config
 ** \param  None
 ** \retval None
 ******************************************************************************/
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    NVIC_SetPriorityGrouping(PriorityGroup);
}

/**
 *******************************************************************************
 ** \brief  NVIC priority config
 ** \param  None
 ** \retval None
 ******************************************************************************/
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    uint32_t prioritygroup = 0x00UL;

    prioritygroup = NVIC_GetPriorityGrouping();

    NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
}

/**
 *******************************************************************************
 ** \brief  NVIC enable IRQ
 ** \param  None
 ** \retval None
 ******************************************************************************/
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    NVIC_EnableIRQ(IRQn);
}

/**
 *******************************************************************************
 ** \brief  NVIC clear pending
 ** \param  None
 ** \retval None
 ******************************************************************************/
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    NVIC_ClearPendingIRQ(IRQn);
}

/**
 *******************************************************************************
 ** \brief  NVIC disable IRQ
 ** \param  None
 ** \retval None
 ******************************************************************************/
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
    NVIC_DisableIRQ(IRQn);
}

/**
 *******************************************************************************
 ** \brief  SPI init
 ** \param  None
 ** \retval None
 ******************************************************************************/
void MasterSpiInit(void)
{
    stc_spi_init_t stcSpiInit;
    stc_port_init_t stcPortInit;

    /* configuration structure initialization */
    MEM_ZERO_STRUCT(stcSpiInit);
    MEM_ZERO_STRUCT(stcPortInit);

    /* Configuration peripheral clock */
    PWC_Fcg1PeriphClockCmd(SPI_UNIT_CLOCK, Enable);

    /* Flash NSS */
    SPI_NSS_HIGH();
    stcPortInit.enPinMode = Pin_Mode_Out;
    PORT_Init(SPI_NSS_PORT, SPI_NSS_PIN, &stcPortInit);

    /* Configuration SPI pin */
    PORT_SetFunc(SPI_SCK_PORT, SPI_SCK_PIN, SPI_SCK_FUNC, Disable);
    PORT_SetFunc(SPI_MOSI_PORT, SPI_MOSI_PIN, SPI_MOSI_FUNC, Disable);
    PORT_SetFunc(SPI_MISO_PORT, SPI_MISO_PIN, SPI_MISO_FUNC, Disable);

    /* Configuration SPI structure */
    stcSpiInit.enClkDiv = SpiClkDiv16;
    stcSpiInit.enFrameNumber = SpiFrameNumber1;
    stcSpiInit.enDataLength = SpiDataLengthBit8;
    stcSpiInit.enFirstBitPosition = SpiFirstBitPositionMSB;
    stcSpiInit.enSckPolarity = SpiSckIdleLevelLow;
    stcSpiInit.enSckPhase = SpiSckOddSampleEvenChange;
    stcSpiInit.enReadBufferObject = SpiReadReceiverBuffer;
    stcSpiInit.enWorkMode = SpiWorkMode3Line;
    stcSpiInit.enTransMode = SpiTransFullDuplex;
    stcSpiInit.enCommAutoSuspendEn = Disable;
    stcSpiInit.enModeFaultErrorDetectEn = Disable;
    stcSpiInit.enParitySelfDetectEn = Disable;
    stcSpiInit.enParityEn = Disable;
    stcSpiInit.enParity = SpiParityEven;
    stcSpiInit.enMasterSlaveMode = SpiModeMaster;
    stcSpiInit.stcDelayConfig.enSsSetupDelayOption = SpiSsSetupDelayCustomValue;
    stcSpiInit.stcDelayConfig.enSsSetupDelayTime = SpiSsSetupDelaySck1;
    stcSpiInit.stcDelayConfig.enSsHoldDelayOption = SpiSsHoldDelayCustomValue;
    stcSpiInit.stcDelayConfig.enSsHoldDelayTime = SpiSsHoldDelaySck1;
    stcSpiInit.stcDelayConfig.enSsIntervalTimeOption = SpiSsIntervalCustomValue;
    stcSpiInit.stcDelayConfig.enSsIntervalTime = SpiSsIntervalSck6PlusPck2;

    SPI_Init(SPI_UNIT, &stcSpiInit);
    SPI_Cmd(SPI_UNIT, Enable);
}

/**
 *******************************************************************************
 ** \brief  SPI write/read single byte
 ** \param  None
 ** \retval None
 ******************************************************************************/
uint8_t SpiFlash_WriteReadByte(uint8_t u8Data)
{
    uint8_t u8Byte;

    /* Wait tx buffer empty */
    while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSendBufferEmpty))
    {
    }
    /* Send data */
    SPI_SendData8(SPI_UNIT, u8Data);
    /* Wait rx buffer full */
    while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagReceiveBufferFull))
    {
    }
    /* Receive data */
    u8Byte = SPI_ReceiveData8(SPI_UNIT);

    return u8Byte;
}

/**
 *******************************************************************************
 ** \brief  SPI read bytes  (read ID) //todo
 ** \param  None
 ** \retval None
 ******************************************************************************/
en_result_t SpiFlash_ReadData(uint32_t u32Addr, uint8_t pData[], uint16_t len)
{
    en_result_t enRet = Ok;
    uint16_t u16Index = 0u;

    if (NULL == pData)
    {
        enRet = Error;
    }
    else
    {
//        SpiFlash_WriteEnable();
        /* Send data to flash */
        SPI_NSS_LOW();
        SpiFlash_WriteReadByte(0xF0);
//        SpiFlash_WriteReadByte((uint8_t)((u32Addr & 0xFF0000ul) >> 16u));
        SpiFlash_WriteReadByte((uint8_t)((u32Addr & 0xFF00u) >> 8u));
        SpiFlash_WriteReadByte((uint8_t)(u32Addr & 0xFFu));
        SPI_NSS_HIGH();
        Ddl_Delay1ms(100);
        SPI_NSS_LOW();
        SpiFlash_WriteReadByte(0xF1);
        while (len--)
        {
            pData[u16Index] = SpiFlash_WriteReadByte(SPI_DUMMY_BYTE_VALUE);
            u16Index++;
        }

        while (Reset == SPI_GetFlag(SPI_UNIT, SpiFlagSpiIdle))
        {
        }
        SPI_NSS_HIGH();
    }
    return enRet;
}

void SPI_RxCmplt(void)
{
    SPI_NSS_HIGH();
    DMA_ClearIrqFlag(SPI_DMA_RX_UNIT, SPI_DMA_RX_CH, TrnCpltIrq);
    DMA_ClearIrqFlag(SPI_DMA_RX_UNIT, SPI_DMA_RX_CH, BlkTrnCpltIrq);
    DMA_ClearIrqFlag(SPI_DMA_TX_UNIT, SPI_DMA_TX_CH, TrnCpltIrq);
    DMA_ClearIrqFlag(SPI_DMA_TX_UNIT, SPI_DMA_TX_CH, BlkTrnCpltIrq);
}

void SPI_TxCmplt(void)
{
    __asm("nop");
}

void MasterSpiDmaInit(void)
{
    stc_irq_regi_conf_t stcIrqRegiConf;
    stc_dma_config_t stcDmaCfg;

    /* configuration structure initialization */
    MEM_ZERO_STRUCT(stcDmaCfg);

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_PERIPH_AOS | PWC_FCG0_PERIPH_DMA1, Enable);

    /* Configure TX DMA */
    stcDmaCfg.u16BlockSize = 1u;
//    stcDmaCfg.u16TransferCnt = u16BufferLen;
    stcDmaCfg.u32SrcAddr = (uint32_t)(&SpiDummyByte);
    stcDmaCfg.u32DesAddr = (uint32_t)(&SPI_UNIT->DR);
    stcDmaCfg.stcDmaChCfg.enSrcInc = AddressFix;
    stcDmaCfg.stcDmaChCfg.enDesInc = AddressFix;
    stcDmaCfg.stcDmaChCfg.enTrnWidth = Dma8Bit;
    stcDmaCfg.stcDmaChCfg.enIntEn = Disable;
    DMA_InitChannel(SPI_DMA_TX_UNIT, SPI_DMA_TX_CH, &stcDmaCfg);

    /* Configure RX DMA */
    stcDmaCfg.u16BlockSize = 1u;
//    stcDmaCfg.u16TransferCnt = u16BufferLen;
    stcDmaCfg.u32SrcAddr = (uint32_t)(&SPI_UNIT->DR);
//    stcDmaCfg.u32DesAddr = (uint32_t)(&u8RxBuffer[0]);
    stcDmaCfg.stcDmaChCfg.enSrcInc = AddressFix;
    stcDmaCfg.stcDmaChCfg.enDesInc = AddressIncrease;
    stcDmaCfg.stcDmaChCfg.enTrnWidth = Dma8Bit;
    stcDmaCfg.stcDmaChCfg.enIntEn = Enable;
    DMA_InitChannel(SPI_DMA_RX_UNIT, SPI_DMA_RX_CH, &stcDmaCfg);

    DMA_SetTriggerSrc(SPI_DMA_TX_UNIT, SPI_DMA_TX_CH, SPI_DMA_TX_TRIG_SOURCE);
    DMA_SetTriggerSrc(SPI_DMA_RX_UNIT, SPI_DMA_RX_CH, SPI_DMA_RX_TRIG_SOURCE);

    /* interrupt */
//    stcIrqRegiConf.enIntSrc = SPI_MASTER_DMA_TX_INT_SRC;
//    stcIrqRegiConf.enIRQn = SPI_MASTER_DMA_TX_IRQn;
//    stcIrqRegiConf.pfnCallback = &SPI_TxCmplt;
//    enIrqRegistration(stcIrqRegiConf);
//    DMA_EnableIrq(SPI_DMA_TX_UNIT, SPI_DMA_TX_CH, TrnCpltIrq);

    stcIrqRegiConf.enIntSrc = SPI_MASTER_DMA_RX_INT_SRC;
    stcIrqRegiConf.enIRQn = SPI_MASTER_DMA_RX_IRQn;
    stcIrqRegiConf.pfnCallback = &SPI_RxCmplt;
    enIrqRegistration(&stcIrqRegiConf);
    DMA_EnableIrq(SPI_DMA_RX_UNIT, SPI_DMA_RX_CH, TrnCpltIrq);

//    HAL_NVIC_SetPriority(SPI_MASTER_DMA_TX_IRQn, 0, 1);
//    HAL_NVIC_EnableIRQ(SPI_MASTER_DMA_TX_IRQn);

    HAL_NVIC_SetPriority(SPI_MASTER_DMA_RX_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(SPI_MASTER_DMA_RX_IRQn);

    DMA_Cmd(SPI_DMA_TX_UNIT, Enable);
    DMA_Cmd(SPI_DMA_RX_UNIT, Enable);
}

/**
 *******************************************************************************
 ** \brief  Receive SPI data with DMA
 ** \param  [in] SPIx                   SPI Unit
 **              SPI_UNIT               SPI Master unit
 **              SPI_SLAVE_UNIT         SPI Slave unit(USART)
 ** \param  [in] pu8Data
 ** \param  [in] len
 ** \retval None
 ******************************************************************************/
en_result_t HAL_SPI_Receive_DMA(const M4_SPI_TypeDef *SPIx, uint8_t pu8Data[], uint16_t len)
{
    en_result_t enRet = Ok;
    stc_dma_ch_cfg_t stcDmaChCfg;

    if ((NULL == SPIx) || (NULL == pu8Data))
    {
        enRet = ErrorInvalidParameter;
    }
    else if(SPI_UNIT == SPIx)
    {
        /* SPI master data receive */
        SPI_Cmd(SPI_UNIT, Disable);
//        DMA_SetSrcAddress(SPI_DMA_TX_UNIT, SPI_DMA_TX_CH, &SpiDummyByte);
//        DMA_SetDesAddress(SPI_DMA_TX_UNIT, SPI_DMA_TX_CH, (uint32_t)&SPIx->DR);
        DMA_SetTransferCnt(SPI_DMA_TX_UNIT, SPI_DMA_TX_CH, len);
        DMA_SetTransferCnt(SPI_DMA_RX_UNIT, SPI_DMA_RX_CH, len);

//        DMA_SetSrcAddress(SPI_DMA_RX_UNIT, SPI_DMA_RX_CH, (uint32_t)&SPIx->DR);
        DMA_SetDesAddress(SPI_DMA_RX_UNIT, SPI_DMA_RX_CH, (uint32_t)pu8Data);

        DMA_ChannelCmd(SPI_DMA_RX_UNIT, SPI_DMA_RX_CH, Enable);
        DMA_ChannelCmd(SPI_DMA_TX_UNIT, SPI_DMA_TX_CH, Enable);

        SPI_Cmd(SPI_UNIT, Enable);
    }
    //else if(SPI_SLAVE_UNIT == SPIx)
    else
    {
        MEM_ZERO_STRUCT(stcDmaChCfg);

         /* DMA src and des inc config */
        stcDmaChCfg.enSrcInc = AddressFix;
        stcDmaChCfg.enDesInc = AddressIncrease;
        stcDmaChCfg.enTrnWidth = Dma8Bit;
        stcDmaChCfg.enIntEn = Enable;
        DMA_ChannelCfg(USART_RX_DMA_UNIT, USART_RX_DMA_CH, &stcDmaChCfg);

        /* SPI slave data receive */
        //SPI_Cmd(SPI_SLAVE_UNIT, Disable);

        DMA_SetTransferCnt(USART_RX_DMA_UNIT, USART_RX_DMA_CH, len);
        DMA_SetDesAddress(USART_RX_DMA_UNIT, USART_RX_DMA_CH, (uint32_t)pu8Data);

        DMA_ChannelCmd(USART_RX_DMA_UNIT, USART_RX_DMA_CH, Enable);

        USART_FuncCmd(USART_UNIT, UsartTxAndTxEmptyInt, Disable);
        USART_FuncCmd(USART_UNIT, UsartRx, Enable);
        USART_FuncCmd(USART_UNIT, UsartRxInt, Enable);
    }
    //else
    //{
    //    enRet = ErrorInvalidParameter;
    //}

    return enRet;
}

/**
 *******************************************************************************
 ** \brief  Transmit SPI data with DMA
 ** \param  [in] SPIx                   SPI Unit
 **              SPI_SLAVE_UNIT         SPI Slave unit
 ** \param  [in] pu8Data
 ** \param  [in] len
 ** \retval None
 ******************************************************************************/
en_result_t HAL_SPI_Transmit_DMA(const M4_SPI_TypeDef *SPIx, uint8_t pu8Data[], uint16_t len)
{
    en_result_t enRet = Ok;
    stc_dma_ch_cfg_t stcDmaChCfg;

    if ((NULL == SPIx) || (NULL == pu8Data))
    {
        enRet = ErrorInvalidParameter;
    }
    //else if(SPI_UNIT == SPIx)
    //{
    //    /* SPI master data receive */
    //
    //}
    //else if(SPI_SLAVE_UNIT == SPIx)
    else
    {
        MEM_ZERO_STRUCT(stcDmaChCfg);
        /* DMA src and des inc config */
        stcDmaChCfg.enSrcInc = AddressIncrease;
        stcDmaChCfg.enDesInc = AddressFix;
        stcDmaChCfg.enTrnWidth = Dma8Bit;
        stcDmaChCfg.enIntEn = Enable;
        DMA_ChannelCfg(USART_TX_DMA_UNIT, USART_TX_DMA_CH, &stcDmaChCfg);

        /* SPI slave data receive */
        DMA_SetSrcAddress(USART_TX_DMA_UNIT, USART_TX_DMA_CH, (uint32_t)pu8Data);

        DMA_SetTransferCnt(USART_TX_DMA_UNIT, USART_TX_DMA_CH, len);
        DMA_ChannelCmd(USART_TX_DMA_UNIT, USART_TX_DMA_CH, Enable);

        USART_FuncCmd(USART_UNIT, UsartRx, Disable);
        USART_FuncCmd(USART_UNIT, UsartRxInt, Disable);
        /*Enable TX interupt function*/
        USART_FuncCmd(USART_UNIT, UsartTxAndTxEmptyInt, Enable);
    }
    //else
    //{
    //    enRet = ErrorInvalidParameter;
    //}

    return enRet;
}

/**
 *******************************************************************************
 ** \brief  Callback function for DP wakeup
 ** \param  None
 ** \retval None
 ******************************************************************************/
//void USB_DP_ExintCallback(void)
//{
//    /* add your code here */
//    HAL_NVIC_DisableIRQ(DP_INT_IRQn);
//    EXINT_IrqFlgClr(DP_EXINT_CH);
//}

/**
 *******************************************************************************
 ** \brief  Callback function for DM wakeup
 ** \param  None
 ** \retval None
 ******************************************************************************/
//void USB_DM_ExintCallback(void)
//{
//    /* add your code here */
//    HAL_NVIC_DisableIRQ(DM_INT_IRQn);
//    EXINT_IrqFlgClr(DM_EXINT_CH);
//}

/**
 *******************************************************************************
 ** \brief  Callback function for EC exint
 ** \param  None
 ** \retval None
 ******************************************************************************/
void EC_ExintCallback(void)
{
    /* add your code here */
    EXINT_IrqFlgClr(EC_EXINT_CH);
}

/**
 *******************************************************************************
 ** \brief  Callback function for FP exint
 ** \param  None
 ** \retval None
 ******************************************************************************/
void FP_ExintCallback(void)
{
    /* add your code here */
    EXINT_IrqFlgClr(FP_EXINT_CH);
}

/**
 *******************************************************************************
 ** \brief  Exint configure for DP DM wakeup from stop mode
 ** \param  None
 ** \retval None
 ** \note   Call before enter stop mode
 ******************************************************************************/
//void USB_DPDMWakeupConfig(void)
//{
//    stc_exint_config_t stcExtiConfig;
//    stc_irq_regi_conf_t stcIrqRegiConf;
//    stc_port_init_t stcPortInit;
//
//    /* GPIO input and exint enable */
//    MEM_ZERO_STRUCT(stcPortInit);
//    stcPortInit.enPinMode = Pin_Mode_In;
//    stcPortInit.enExInt = Enable;
//    PORT_Init(DP_PORT, DP_PIN, &stcPortInit);  /* DP */
//    PORT_Init(DM_PORT, DM_PIN, &stcPortInit);  /* DM */
//
//    /* Exint config */
//    stcExtiConfig.enExitCh = DP_EXINT_CH;
//    stcExtiConfig.enFilterEn = Enable;
//    stcExtiConfig.enFltClk = Pclk3Div8;
//    stcExtiConfig.enExtiLvl = ExIntBothEdge;
//    EXINT_Init(&stcExtiConfig);
//    stcExtiConfig.enExitCh = DM_EXINT_CH;
//    EXINT_Init(&stcExtiConfig);
//
//    /* Select External Int Ch.12 */
//    stcIrqRegiConf.enIntSrc = DP_INT_SRC;
//    stcIrqRegiConf.enIRQn = DP_INT_IRQn;
//    stcIrqRegiConf.pfnCallback = &USB_DP_ExintCallback;
//    enIrqRegistration(&stcIrqRegiConf);
////    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
////    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_15);
////    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);
//    HAL_NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
//    HAL_NVIC_SetPriority(stcIrqRegiConf.enIRQn, 1, 0);
//    HAL_NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);
//
//    /* Select External Int Ch.11 */
//    stcIrqRegiConf.enIntSrc = DM_INT_SRC;
//    stcIrqRegiConf.enIRQn = DM_INT_IRQn;
//    stcIrqRegiConf.pfnCallback = &USB_DM_ExintCallback;
//    enIrqRegistration(&stcIrqRegiConf);
////    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
////    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_15);
////    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);
//    HAL_NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
//    HAL_NVIC_SetPriority(stcIrqRegiConf.enIRQn, 1, 0);
//    HAL_NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);
//
//    /* Enbale exint ch11 and ch12 wakeup from stop mode */
//    enIntWakeupEnable(Extint12WU | Extint11WU);
//}

/**
 *******************************************************************************
 ** \brief  Exint configure for DP DM wakeup from stop mode
 ** \param  None
 ** \retval None
 ** \note   Call after wakeup from stop mode
 ******************************************************************************/
//void USB_DPDM_PortInit(void)
//{
//    stc_port_init_t stcPortInit;
//
//    MEM_ZERO_STRUCT(stcPortInit);
//    stcPortInit.enPinMode = Pin_Mode_Ana;
//    PORT_Init(DP_PORT, DP_PIN, &stcPortInit);
//    PORT_Init(DM_PORT, DM_PIN, &stcPortInit);
//
//    /* un-gate USB Core clock */
//    USB_OTG_EnableUSBCoreClock(&USB_OTG_dev);
//}

/**
 *******************************************************************************
 ** \brief  Exint configure for EC pin
 ** \param  None
 ** \retval None
 ******************************************************************************/
void EcIntConfig(void)
{
    stc_exint_config_t stcExtiConfig;
    stc_irq_regi_conf_t stcIrqRegiConf;
    stc_port_init_t stcPortInit;

    /* GPIO input and exint enable */
    MEM_ZERO_STRUCT(stcPortInit);
    stcPortInit.enPinMode = Pin_Mode_In;
    stcPortInit.enExInt = Enable;
    PORT_Init(EC_PORT, EC_PIN, &stcPortInit);

    /* Exint config */
    stcExtiConfig.enExitCh = EC_EXINT_CH;
    stcExtiConfig.enFilterEn = Enable;
    stcExtiConfig.enFltClk = Pclk3Div8;
    stcExtiConfig.enExtiLvl = ExIntBothEdge;  /* Rising and falling edge */
    EXINT_Init(&stcExtiConfig);

    /* Select External Int Ch.11 */
    stcIrqRegiConf.enIntSrc = EC_INT_SRC;
    stcIrqRegiConf.enIRQn = EC_INT_IRQn;
    stcIrqRegiConf.pfnCallback = &EC_ExintCallback;
    enIrqRegistration(&stcIrqRegiConf);
//    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
//    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_15);
//    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);
    HAL_NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    HAL_NVIC_SetPriority(stcIrqRegiConf.enIRQn, 2, 1);
    HAL_NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);

    /* Enable wakeup */
    enIntWakeupEnable(Extint5WU);
}

/**
 *******************************************************************************
 ** \brief  Get EC pin status
 ** \param  None
 ** \retval None
 ******************************************************************************/
uint32_t GetECStatus(void)
{
    return PORT_GetBit(EC_PORT, EC_PIN);
}

/**
 *******************************************************************************
 ** \brief  Exint configure for FP pin
 ** \param  None
 ** \retval None
 ******************************************************************************/
void FPIntConfig(void)
{
    stc_exint_config_t stcExtiConfig;
    stc_irq_regi_conf_t stcIrqRegiConf;
    stc_port_init_t stcPortInit;

    /* GPIO input and exint enable */
    MEM_ZERO_STRUCT(stcPortInit);
    stcPortInit.enPinMode = Pin_Mode_In;
    stcPortInit.enExInt = Enable;
    PORT_Init(FP_PORT, FP_PIN, &stcPortInit);

    /* Exint config */
    stcExtiConfig.enExitCh = FP_EXINT_CH;
    stcExtiConfig.enFilterEn = Enable;
    stcExtiConfig.enFltClk = Pclk3Div8;
    stcExtiConfig.enExtiLvl = ExIntRisingEdge;  /* Rising edge */
    EXINT_Init(&stcExtiConfig);

    /* Select External Int Ch.11 */
    stcIrqRegiConf.enIntSrc = FP_INT_SRC;
    stcIrqRegiConf.enIRQn = FP_INT_IRQn;
    stcIrqRegiConf.pfnCallback = &FP_ExintCallback;
    enIrqRegistration(&stcIrqRegiConf);
//    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
//    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_15);
//    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);
    HAL_NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    HAL_NVIC_SetPriority(stcIrqRegiConf.enIRQn, 2, 0);
    HAL_NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);

    /* Enable wakeup */
    enIntWakeupEnable(Extint0WU);
}

uint8_t u8TestRev = 0;
uint8_t u8TestTrans = 0;

void USART_TxCmplt(void)
{
    u8TestTrans = 1;

    USART_FuncCmd(USART_UNIT, UsartTxAndTxEmptyInt, Disable);
    DMA_ClearIrqFlag(USART_TX_DMA_UNIT, USART_TX_DMA_CH, TrnCpltIrq);
    DMA_ClearIrqFlag(USART_TX_DMA_UNIT, USART_TX_DMA_CH, BlkTrnCpltIrq);
}

void USART_RxCmplt(void)
{
    u8TestRev = 1;

    USART_FuncCmd(USART_UNIT, UsartRx, Disable);
    USART_FuncCmd(USART_UNIT, UsartRxInt, Disable);
    DMA_ClearIrqFlag(USART_RX_DMA_UNIT, USART_RX_DMA_CH, TrnCpltIrq);
    DMA_ClearIrqFlag(USART_RX_DMA_UNIT, USART_RX_DMA_CH, BlkTrnCpltIrq);
}

/**
 *******************************************************************************
 ** \brief  Stop mode config for power consumption
 ** \param  None
 ** \retval None
 ******************************************************************************/
void StopModeConfig(void)
{
    stc_pwc_stop_mode_cfg_t stcPwcStopCfg;
    MEM_ZERO_STRUCT(stcPwcStopCfg);
    stcPwcStopCfg.enStpDrvAbi = StopUlowspeed;
    stcPwcStopCfg.enStopClk = ClkFix;
    stcPwcStopCfg.enStopFlash = Wait;
    stcPwcStopCfg.enPll = Enable;

    PWC_StopModeCfg(&stcPwcStopCfg);
}

static void UsartDmaInit(void)
{
    stc_irq_regi_conf_t stcIrqRegiConf;
    stc_dma_config_t stcDmaCfg;

    /* configuration structure initialization */
    MEM_ZERO_STRUCT(stcDmaCfg);

    PWC_Fcg0PeriphClockCmd(PWC_FCG0_PERIPH_AOS | PWC_FCG0_PERIPH_DMA2, Enable);

    DMA_ClearIrqFlag(USART_TX_DMA_UNIT, USART_TX_DMA_CH, TrnCpltIrq);
    DMA_ClearIrqFlag(USART_TX_DMA_UNIT, USART_TX_DMA_CH, BlkTrnCpltIrq);
    DMA_ClearIrqFlag(USART_RX_DMA_UNIT, USART_RX_DMA_CH, TrnCpltIrq);
    DMA_ClearIrqFlag(USART_RX_DMA_UNIT, USART_RX_DMA_CH, BlkTrnCpltIrq);
    DMA_DeInit(USART_TX_DMA_UNIT, USART_TX_DMA_CH);
    DMA_DeInit(USART_TX_DMA_UNIT, USART_RX_DMA_CH);

    /* Configure TX DMA */
    stcDmaCfg.u16BlockSize = 1u;
    //stcDmaCfg.u16TransferCnt = u16BufferLen;
    //stcDmaCfg.u32SrcAddr = NULL;
    stcDmaCfg.u32DesAddr = (uint32_t)&USART_UNIT->DR;
    stcDmaCfg.stcDmaChCfg.enSrcInc = AddressIncrease;
    stcDmaCfg.stcDmaChCfg.enDesInc = AddressFix;
    stcDmaCfg.stcDmaChCfg.enTrnWidth = Dma8Bit;
    stcDmaCfg.stcDmaChCfg.enIntEn = Enable;
    DMA_InitChannel(USART_TX_DMA_UNIT, USART_TX_DMA_CH, &stcDmaCfg);

    /* Configure RX DMA */
    stcDmaCfg.u16BlockSize = 1u;
    //stcDmaCfg.u16TransferCnt = u16BufferLen;
    stcDmaCfg.u32SrcAddr = ((uint32_t)(&USART_UNIT->DR)+2ul);
    //stcDmaCfg.u32DesAddr = NULL;
    stcDmaCfg.stcDmaChCfg.enSrcInc = AddressFix;
    stcDmaCfg.stcDmaChCfg.enDesInc = AddressIncrease;
    stcDmaCfg.stcDmaChCfg.enTrnWidth = Dma8Bit;
    stcDmaCfg.stcDmaChCfg.enIntEn = Enable;
    DMA_InitChannel(USART_RX_DMA_UNIT, USART_RX_DMA_CH, &stcDmaCfg);

    DMA_SetTriggerSrc(USART_TX_DMA_UNIT, USART_TX_DMA_CH, USART_TX_DMA_TRG_SEL);
    DMA_SetTriggerSrc(USART_RX_DMA_UNIT, USART_RX_DMA_CH, USART_RX_DMA_TRG_SEL);

    /* interrupt */
    stcIrqRegiConf.enIntSrc = TX_DMA_BTC_INT_NUM;
    stcIrqRegiConf.enIRQn = TX_DMA_BTC_INT_IRQn;
    stcIrqRegiConf.pfnCallback = &USART_TxCmplt;
    enIrqRegistration(&stcIrqRegiConf);
    DMA_EnableIrq(USART_TX_DMA_UNIT, USART_TX_DMA_CH, TrnCpltIrq);

    stcIrqRegiConf.enIntSrc = RX_DMA_BTC_INT_NUM;
    stcIrqRegiConf.enIRQn = RX_DMA_BTC_INT_IRQn;
    stcIrqRegiConf.pfnCallback = &USART_RxCmplt;
    enIrqRegistration(&stcIrqRegiConf);
    DMA_EnableIrq(USART_RX_DMA_UNIT, USART_RX_DMA_CH, TrnCpltIrq);

    HAL_NVIC_SetPriority(TX_DMA_BTC_INT_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(TX_DMA_BTC_INT_IRQn);

    HAL_NVIC_SetPriority(RX_DMA_BTC_INT_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RX_DMA_BTC_INT_IRQn);

    DMA_Cmd(USART_TX_DMA_UNIT, Enable);
    DMA_Cmd(USART_RX_DMA_UNIT, Enable);
}

/**
 *******************************************************************************
 ** \brief USART RX error irq callback function.
 **
 ** \param [in] None
 **
 ** \retval None
 **
 ******************************************************************************/
static void UsartErrIrqCallback(void)
{
    //m_enTestResult = Error;

    if (Set == USART_GetStatus(USART_UNIT, UsartFrameErr))
    {
        USART_ClearStatus(USART_UNIT, UsartFrameErr);
    }
    else
    {
    }

    if (Set == USART_GetStatus(USART_UNIT, UsartParityErr))
    {
        USART_ClearStatus(USART_UNIT, UsartParityErr);
    }
    else
    {
    }

    if (Set == USART_GetStatus(USART_UNIT, UsartOverrunErr))
    {
        USART_ClearStatus(USART_UNIT, UsartOverrunErr);
    }
    else
    {
    }
}

/**
 *******************************************************************************
 ** \brief  SPI slave init(USART)
 ** \param  None
 ** \retval None
 ******************************************************************************/
void SlaveSpiInit(void)
{
    stc_irq_regi_conf_t stcIrqRegiCfg;
    const stc_usart_clksync_init_t stcInitCfg = {
        UsartExtClk,
        UsartClkDiv_1,
        UsartDataMsbFirst,
        UsartRtsEnable,
    };

    UsartDmaInit();

     /* Enable peripheral clock */
    PWC_Fcg1PeriphClockCmd(USART_UNIT_CLOCK, Enable);
    /* Initialize USART IO */
    PORT_DebugPortSetting(TDO_SWO, Disable);
    PORT_DebugPortSetting(TRST, Disable);
    PORT_SetFunc(USART_CK_PORT, USART_CK_PIN, USART_CK_FUNC, Disable);
    PORT_SetFunc(USART_RX_PORT, USART_RX_PIN, USART_RX_FUNC, Disable);
    PORT_SetFunc(USART_TX_PORT, USART_TX_PIN, USART_TX_FUNC, Disable);

    USART_DeInit(USART_UNIT);
    /* Initialize USART */
    USART_CLKSYNC_Init(USART_UNIT, &stcInitCfg);
    //USART_SetBaudrate(USART_UNIT, USART_BAUDRATE);

    /* Set USART RX error IRQ */
    stcIrqRegiCfg.enIRQn = USART_EI_IRQn;
    stcIrqRegiCfg.pfnCallback = &UsartErrIrqCallback;
    stcIrqRegiCfg.enIntSrc = USART_EI_NUM;
    enIrqRegistration(&stcIrqRegiCfg);
    NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
    NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);

    /*Enable RX && RX interupt function*/
    //USART_FuncCmd(USART_UNIT, UsartRx, Enable);
    //USART_FuncCmd(USART_UNIT, UsartRxInt, Enable);
}

/**
 *******************************************************************************
 ** \brief  SPI slave de-init(USART)
 ** \param  None
 ** \retval None
 ******************************************************************************/
void SlaveSpiDeInit(void)
{
    USART_DeInit(USART_UNIT);

    PORT_SetFunc(USART_CK_PORT, USART_CK_PIN, Func_Gpio, Disable);
    PORT_SetFunc(USART_RX_PORT, USART_RX_PIN, Func_Gpio, Disable);
    PORT_SetFunc(USART_TX_PORT, USART_TX_PIN, Func_Gpio, Disable);

    DMA_DeInit(USART_TX_DMA_UNIT, USART_TX_DMA_CH);
    DMA_DeInit(USART_TX_DMA_UNIT, USART_RX_DMA_CH);

    HAL_NVIC_DisableIRQ(USART_EI_IRQn);
    HAL_NVIC_DisableIRQ(TX_DMA_BTC_INT_IRQn);
    HAL_NVIC_DisableIRQ(RX_DMA_BTC_INT_IRQn);
}

/**
 *******************************************************************************
 ** \brief  MCU_CPU_IRQ pin init
 ** \param  None
 ** \retval None
 ******************************************************************************/
void MCU_CPU_IRQ_PinInit(void)
{
    stc_port_init_t stcPortInit;

    /* configuration structure initialization */
    MEM_ZERO_STRUCT(stcPortInit);

    stcPortInit.enPinMode = Pin_Mode_Out;
    PORT_Init(MCU_CPU_IRQ_PORT, MCU_CPU_IRQ_PIN, &stcPortInit);
}

/**
 *******************************************************************************
 ** \brief  Callback function for USART RX exint
 ** \param  None
 ** \retval None
 ******************************************************************************/
void USART_RX_ExintCallback(void)
{
    /* add your code here */
    EXINT_IrqFlgClr(USART_RX_EXINT_CH);
}

/**
 *******************************************************************************
 ** \brief  Exint configure for USART RX pin
 ** \param  None
 ** \retval None
 ******************************************************************************/
void USART_RX_IntConfig(void)
{
    stc_exint_config_t stcExtiConfig;
    stc_irq_regi_conf_t stcIrqRegiConf;
    stc_port_init_t stcPortInit;

    /* GPIO input and exint enable */
    MEM_ZERO_STRUCT(stcPortInit);
    stcPortInit.enPinMode = Pin_Mode_In;
    stcPortInit.enExInt = Enable;
    PORT_Init(USART_RX_PORT, USART_RX_PIN, &stcPortInit);

    /* Exint config */
    stcExtiConfig.enExitCh = USART_RX_EXINT_CH;
    stcExtiConfig.enFilterEn = Enable;
    stcExtiConfig.enFltClk = Pclk3Div8;
    stcExtiConfig.enExtiLvl = ExIntRisingEdge;  /* Rising edge */
    EXINT_Init(&stcExtiConfig);

    /* Select External Int Ch.11 */
    stcIrqRegiConf.enIntSrc = USART_RX_INT_SRC;
    stcIrqRegiConf.enIRQn = USART_RX_INT_IRQn;
    stcIrqRegiConf.pfnCallback = &USART_RX_ExintCallback;
    enIrqRegistration(&stcIrqRegiConf);

    HAL_NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    HAL_NVIC_SetPriority(stcIrqRegiConf.enIRQn, 2, 0);
    HAL_NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);

    /* Enable wakeup */
    enIntWakeupEnable(Extint3WU);
}

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
