/*
 * @file    H_pic24e_spi.c
 * @author
 * @version
 * @date    15.08.2017
 * @brief   
 */


//******************************************************************************
// ������ include: ����� ������������ ������������ ���� � ������
#include "pic24e_spi.h"
//******************************************************************************


//******************************************************************************
//------------------------------------------------------------------------------
// ���������� ����������
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// ��������� ����������
//------------------------------------------------------------------------------
//******************************************************************************


//******************************************************************************
// ������ ���������� ��������� �������
uint8_t IO_SPI1_Master(uint8_t txData);
void CheckRxErrorSPI1(void);
//******************************************************************************


//******************************************************************************
// ������ �������� ������� (������� ����������, ����� ���������)

/*============================================================================*/

/*
 * @brief   ������� ������������� ������ SPI1
 * @param   None
 * @retval  None
 */
void Init_SPI1_Master(void)
{
    IFS0bits.SPI1IF = 0; //             Clear the Interrupt flag
    IEC0bits.SPI1IE = 0; //             Disable the interrupt

    SPI1CON1bits.DISSCK = 0; //         Internal serial clock is enabled
    SPI1CON1bits.DISSDO = 0; //         SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 1; //         Communication is word-wide (16 bits)
    SPI1CON1bits.SMP = 0; //            Input data is sampled at the middle of data output time
    SPI1CON1bits.CKE = 0; //            Serial output data changes on transition from
    //                                  Idle clock state to active clock state
    SPI1CON1bits.CKP = 0; //            Idle state for clock is a low-level;
    //                                  active state is a high-level
    SPI1CON1bits.MSTEN = 1; //          Master mode enabled
    SPI1STATbits.SPIEN = 1; //          Enable SPI module
}

/*
 * @brief   ������� ��������� ������ SPI �� ������� ������������ � ���������� ����
 * @param   None
 * @retval  None
 */
void CheckRxErrorSPI1(void)
{
    if (SPI1STATbits.SPIROV == 1)
    {
        SPI1STATbits.SPIROV = 0;
    }
} // void CheckRxErrorSPI1(void)

/*
 * @brief   ������� ���������� 1 ��� ������ �� ���� SPI � ������ ��������� ������ 
 *          � ���� SPI
 * @param   txData: ������ ��� �������� �� ���� SPI
 * @retval  ������, ��������� � ���� SPI
 */
uint8_t IO_SPI1_Master(uint8_t txData)
{
    CheckRxErrorSPI1();
    SPI1BUF = txData;
    while (SPI1STATbits.SPIRBF != 1); //    1 = Receive complete, SPIxRXB is full
    //                                      0 = Receive is incomplete, SPIxRXB is empty
    return SPI1BUF;
} // uint8_t IO_SPI1_Master(uint8_t txData)

/*
 * @brief   ������� ���������� 1 ��� ������ �� ���� SPI � ������ ��������� ������ 
 *          � ���� SPI
 * @param   *pTxData:   ��������� �� ������ ������, ������� ���������� �������� ��
 *                      ���� SPI
 *          *pRxData:   ��������� �� ������, � ������� ����� �������� ����������� 
 *                      �� ���� SPI ������
 *          Cnt:    ���������� �����������/������������ ������
 * @retval  None
 */
void SPI1_TransmitReceive_Master(uint8_t *pTxData, uint8_t *pRxData, uint16_t Cnt)
{
    uint16_t i = 0;
    for (i = 0; i < Cnt; i++)
    {
        *pRxData = IO_SPI1_Master(*pTxData);
        pRxData++;
        pTxData++;
    }
}
/*============================================================================*/
//******************************************************************************


////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
