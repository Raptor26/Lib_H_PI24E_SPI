/** 
 * File:   Lib_H_PIC_spi_New.c
 * Author: m.isaev
 *
 * Created on 26 октября 2017 г., 10:52
 */

//******************************************************************************
//  Секция include: здесь подключается заголовочный файл к модулю
#include "Lib_H_pic_spi.h"
//******************************************************************************


//******************************************************************************
//------------------------------------------------------------------------------
//  Глобальные переменные
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Локальные переменные
//------------------------------------------------------------------------------
//******************************************************************************


//******************************************************************************
//  Секция прототипов локальных функций
uint8_t PIC_SPI1_Master_IO_8bits(uint8_t txData);
void PIC_SPI1_CheckRxError(void);
//******************************************************************************


//******************************************************************************
//  Секция описания функций (сначала глобальных, потом локальных)
//==============================================================================
#if defined (__dsPIC33E__) || (__PIC24H__) || (__PIC24E__)

/**
 *  @brief  Функция выполняет конфигурирование модуля SPI_1 со следующими 
 *  параметрами:
 *      Главный предделитель - 1/64;
 *      Вторичный предделитель - 1/1;
 *      Прерывания - отключены;
 *  @note   Функция конфигурирования проверена на работе с датчиком MPU6000;
 */
void PIC_Init_SPI_1_PriPRES_64_1_SecPRES_1_1_IntDis_8bits(void)
{
    CloseSPI1();
    unsigned int spi_con_1_value = ENABLE_SCK_PIN
            & ENABLE_SDO_PIN
            & SPI_MODE16_OFF
            & SPI_SMP_ON
            & SPI_CKE_ON
            & SLAVE_ENABLE_OFF
            & CLK_POL_ACTIVE_HIGH
            & MASTER_ENABLE_ON
            & SEC_PRESCAL_1_1
            & PRI_PRESCAL_64_1;
    unsigned int spi_con_2_value = FRAME_ENABLE_OFF
            & FRAME_SYNC_OUTPUT
            & FRAME_POL_ACTIVE_LOW
            & FRAME_SYNC_EDGE_PRECEDE
            & FIFO_BUFFER_DISABLE;
    unsigned int spi_stat_value = SPI_ENABLE
            & SPI_IDLE_CON
            & SPI_RX_OVFLOW_CLR;

    OpenSPI1(spi_con_1_value,
             spi_con_2_value,
             spi_stat_value);
}

void PIC_Init_SPI_1_PriPRES_64_1_SecPRES_1_1_IntDis_16bits(void)
{
    CloseSPI1();
    unsigned int spi_con_1_value = ENABLE_SCK_PIN
            & ENABLE_SDO_PIN
            & SPI_MODE16_ON
            & SPI_SMP_ON
            & SPI_CKE_ON
            & SLAVE_ENABLE_OFF
            & CLK_POL_ACTIVE_HIGH
            & MASTER_ENABLE_ON
            & SEC_PRESCAL_1_1
            & PRI_PRESCAL_64_1;
    unsigned int spi_con_2_value = FRAME_ENABLE_OFF
            & FRAME_SYNC_OUTPUT
            & FRAME_POL_ACTIVE_LOW
            & FRAME_SYNC_EDGE_PRECEDE
            & FIFO_BUFFER_DISABLE;
    unsigned int spi_stat_value = SPI_ENABLE
            & SPI_IDLE_CON
            & SPI_RX_OVFLOW_CLR;

    OpenSPI1(spi_con_1_value,
             spi_con_2_value,
             spi_stat_value);
}

/**
 *  @brief  Функция выполняет конфигурирование модуля SPI_1 со следующими 
 *  параметрами:
 *      Главный предделитель - 1/4;
 *      Вторичный предделитель - 1/1;
 *      Прерывания - отключены;
 *  @note   Функция конфигурирования проверена на работе с датчиком MPU6000;
 */
void PIC_Init_SPI_1_PriPRES_4_1_SecPRES_1_1_IntDis_8bits(void)
{
    CloseSPI1();
    unsigned int spi_con_1_value = ENABLE_SCK_PIN
            & ENABLE_SDO_PIN
            & SPI_MODE16_OFF
            & SPI_SMP_ON
            & SPI_CKE_ON
            & SLAVE_ENABLE_OFF
            & CLK_POL_ACTIVE_HIGH
            & MASTER_ENABLE_ON
            & SEC_PRESCAL_1_1
            & PRI_PRESCAL_4_1;
    unsigned int spi_con_2_value = FRAME_ENABLE_OFF
            & FRAME_SYNC_OUTPUT
            & FRAME_POL_ACTIVE_LOW
            & FRAME_SYNC_EDGE_PRECEDE;
    unsigned int spi_stat_value = SPI_ENABLE
            & SPI_IDLE_CON
            & SPI_RX_OVFLOW_CLR;

    OpenSPI1(spi_con_1_value,
             spi_con_2_value,
             spi_stat_value);
}

void PIC_Init_SPI_1_PriPRES_1_1_SecPRES_2_1_IntDis_8bits(void)
{
    CloseSPI1();
    unsigned int spi_con_1_value = ENABLE_SCK_PIN
            & ENABLE_SDO_PIN
            & SPI_MODE16_OFF
            & SPI_SMP_ON
            & SPI_CKE_ON
            & SLAVE_ENABLE_OFF
            & CLK_POL_ACTIVE_HIGH
            & MASTER_ENABLE_ON
            & SEC_PRESCAL_2_1
            & PRI_PRESCAL_1_1;
    unsigned int spi_con_2_value = FRAME_ENABLE_OFF
            & FRAME_SYNC_OUTPUT
            & FRAME_POL_ACTIVE_LOW
            & FRAME_SYNC_EDGE_PRECEDE;
    unsigned int spi_stat_value = SPI_ENABLE
            & SPI_IDLE_CON
            & SPI_RX_OVFLOW_CLR;

    OpenSPI1(spi_con_1_value,
             spi_con_2_value,
             spi_stat_value);
}

/**
 * @brief   Функция отправляет на шину SPI массив данных и принимает с шины SPI 
 *          массив данных. Буфер данных шины SPI является и приемником и передатчиков одновременно
 * @param   *pTxData:   Указатель на массив данных, который необходимо передать по
 *                      шине SPI
 * @param   *pRxData:   Указатель на массив, в который будут записаны принимаемые 
 *                      по шине SPI данные
 *          cnt:    Количество принимаемых/передаваемых данных
 * @retval  None
 */
void PIC_SPI1_Master_TransmitReceive_8bits(uint8_t *pTxData,
                                           uint8_t *pRxData,
                                           uint16_t cnt)
{
    uint16_t i = 0;
    for (i = 0; i < cnt; i++)
    {
        *pRxData++ = PIC_SPI1_Master_IO_8bits(*pTxData++);
    }
}

/**
 * @brief   Функция отправляет на шину SPI массив данных и принимает с шины SPI 
 *          массив данных. Буфер данных шины SPI является и приемником и передатчиков одновременно
 * @param   *pTxData:   Указатель на массив данных, который необходимо передать по
 *                      шине SPI
 * @param   *pRxData:   Указатель на массив, в который будут записаны принимаемые 
 *                      по шине SPI данные
 *          cnt:    Количество принимаемых/передаваемых данных
 * @retval  None
 */
void PIC_SPI1_Master_TransmitReceive_16bits(uint16_t *pTxData,
                                            uint16_t *pRxData,
                                            uint16_t cnt)
{
    uint16_t i = 0;
    for (i = 0; i < cnt; i++)
    {
        *pRxData++ = PIC_SPI1_Master_IO_16bits(*pTxData++);
    }
}

/**
 *  @brief  Функция отправляет массиив данных на шину SPI
 *  @param  *pTxData:   Указатель на массив данных с которого берутся данные для 
 *                      отправки на шину SPI
 *  @param  cnt:    Количество принимаемых/передаваемых данных
 *  @retval None
 */
void PIC_SPI1_Master_Transmit_8bits(uint8_t *pTxData, uint16_t cnt)
{
    uint16_t i = 0;
    for (i = 0; i < cnt; i++)
    {
        PIC_SPI1_Master_IO_8bits(*pTxData++);
    }
}

/**
 *  @brief  Функция отправляет массиив данных на шину SPI
 *  @param  *pTxData:   Указатель на массив данных с которого берутся данные для 
 *                      отправки на шину SPI
 *  @param  cnt:    Количество принимаемых/передаваемых данных
 *  @retval None
 */
void PIC_SPI1_Master_Transmit_16bits(uint16_t *pTxData, uint16_t cnt)
{
    uint16_t i = 0;
    for (i = 0; i < cnt; i++)
    {
        PIC_SPI1_Master_IO_16bits(*pTxData++);
    }
}

/**
 *  @brief  Функция принимает массив данных с шины SPI
 *  @param  *pRxData:   Указатель на массив, куда будут записаны принимаемые данные
 *  @param  cnt     Количество принимаемых/передаваемых данных
 *  @retval None
 */
void PIC_SPI1_Maste_Receiver_8bits(uint8_t *pRxData, uint16_t cnt)
{
    uint8_t emptData = 0xFF; //         Пустые данные для отправки на шину SPI
    uint16_t i = 0;
    for (i = 0; i < cnt; i++)
    {
        *pRxData++ = PIC_SPI1_Master_IO_8bits(emptData);
    }
}

/**
 *  @brief  Функция принимает массив данных с шины SPI
 *  @param  *pRxData:   Указатель на массив, куда будут записаны принимаемые данные
 *  @param  cnt     Количество принимаемых/передаваемых данных
 *  @retval None
 */
void PIC_SPI1_Maste_Receiver_16bits(uint16_t *pRxData, uint16_t cnt)
{
    uint16_t emptData = 0xFFFF; //       Пустые данные для отправки на шину SPI
    uint16_t i = 0;
    for (i = 0; i < cnt; i++)
    {
        *pRxData++ = PIC_SPI1_Master_IO_16bits(emptData);
    }
}

/**
 * @brief   Функция отправляет 1 байт данных на шину SPI и читает пришедший байт 
 *          с шины SPI
 * @param   txData: данные для отправки на шину SPI
 * @retval  Данные, пришедние с шины SPI
 */
uint8_t PIC_SPI1_Master_IO_8bits(uint8_t txData)
{
    IFS0bits.SPI1IF = 0; //                 Сброс флага прерываний
    PIC_SPI1_CheckRxError();
    SPI1BUF = (unsigned int) txData;
    while (SPI1STATbits.SPITBF != 0);
    while (IFS0bits.SPI1IF != 1);
    IFS0bits.SPI1IF = 0; //                 сброс флага прерываний
    while (SPI1STATbits.SPIRBF != 1); //    1 = Receive complete, SPIxRXB is full
    //                                      0 = Receive is incomplete, SPIxRXB is empty
    return SPI1BUF;
}

/**
 * @brief   Функция отправляет 2 байта данных на шину SPI и читает пришедшие 2 байта 
 *          с шины SPI
 * @param   txData: данные для отправки на шину SPI
 * @retval  Данные, пришедние с шины SPI
 */
uint16_t PIC_SPI1_Master_IO_16bits(uint16_t txData)
{
    IFS0bits.SPI1IF = 0; //                 Сброс флага прерываний
    PIC_SPI1_CheckRxError();
    SPI1BUF = (unsigned int) txData;
    while (SPI1STATbits.SPITBF != 0);
    while (IFS0bits.SPI1IF != 1);
    IFS0bits.SPI1IF = 0; //                 сброс флага прерываний
    while (SPI1STATbits.SPIRBF != 1); //    1 = Receive complete, SPIxRXB is full
    //                                      0 = Receive is incomplete, SPIxRXB is empty
    return SPI1BUF;
}

/**
 * @brief   Функция проверяет модуль SPI1 на наличие переполнения и сбрасывает флаг
 * @param   None
 * @retval  None
 */
void PIC_SPI1_CheckRxError(void)
{
    if (SPI1STATbits.SPIROV == 1)
    {
        SPI1STATbits.SPIROV = 0;
    }
}
#endif //   (__dsPIC33E__) || (__PIC24H__) || (__PIC24E__)
//==============================================================================
//==============================================================================
//******************************************************************************


////////////////////////////////////////////////////////////////////////////////
//  END OF FILE
////////////////////////////////////////////////////////////////////////////////
