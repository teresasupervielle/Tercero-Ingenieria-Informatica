/***************************************************************************//**
 * \file   iocon_lpc40xx.h
 *
 * \brief  Configuración de pines del LPC40xx.
 */

#ifndef IOCON_LPC40XX_H
#define IOCON_LPC40XX_H

#include <LPC407x_8x_177x_8x.h>
#include "gpio_lpc40xx.h"

/*===== Constantes =============================================================
 */

/* Número máximo de funciones en cada pin del LPC40xx.
 */
#define IOCON_MAXIMO_FUNCIONES_POR_PIN  8

/* Máscaras para seleccionar la configuración de la etapa de entrada o salida
 * de un pin.
 */
#define IOCON_NO_PULL_UP_NO_PULL_DOWN   0
#define IOCON_PULL_DOWN                 (1 << 3)
#define IOCON_PULL_UP                   (1 << 4)
#define IOCON_REPEATER_MODE             (3 << 3)
#define IOCON_HYS                       (1 << 5)
#define IOCON_INV                       (1 << 6)
#define IOCON_ADMODE                    (1 << 7)
#define IOCON_FILTER                    (1 << 8)
#define IOCON_HS                        (1 << 8)
#define IOCON_SLEW                      (1 << 9)
#define IOCON_HIDRIVE                   (1 << 9)
#define IOCON_OD                        (1 << 10)
#define IOCON_DACEN                     (1 << 16)

/*===== Tipos de datos =========================================================
 */

/* Funciones posibles de los pines.
 */
typedef enum
{
    GPIO,
    AD0_0, AD0_1, AD0_2, AD0_3, AD0_4, AD0_5, AD0_6, AD0_7,
    CAN_RD1, CAN_RD2, CAN_TD1, CAN_TD2,
    CLKOUT,
    CMP_RESET, CMP_ROSC, CMP_VREF,
    CMP0_IN_1, CMP0_IN_2, CMP0_IN_3, CMP0_IN_4, CMP0_OUT,
    CMP1_IN_1, CMP1_IN_2, CMP1_IN_3, CMP1_IN_4, CMP1_OUT,
    DAC_OUT,
    EINT0, EINT1, EINT2, EINT3,
    EMC_A_0, EMC_A_1, EMC_A_2, EMC_A_3,
    EMC_A_4, EMC_A_5, EMC_A_6, EMC_A_7,
    EMC_A_8, EMC_A_9, EMC_A_10, EMC_A_11,
    EMC_A_12, EMC_A_13, EMC_A_14,EMC_A_15,
    EMC_A_16, EMC_A_17, EMC_A_18, EMC_A_19,
    EMC_A_20, EMC_A_21, EMC_A_22, EMC_A_23,
    EMC_A_24, EMC_A_25,
    EMC_BLS0, EMC_BLS1, EMC_BLS2, EMC_BLS3,
    EMC_CAS,
    EMC_CKE0, EMC_CKE1, EMC_CKE2, EMC_CKE3,
    EMC_CLK0, EMC_CLK1,
    EMC_CS0, EMC_CS1, EMC_CS2, EMC_CS3,
    EMC_D_0, EMC_D_1, EMC_D_2, EMC_D_3,
    EMC_D_4, EMC_D_5, EMC_D_6, EMC_D_7,
    EMC_D_8, EMC_D_9, EMC_D_10, EMC_D_11,
    EMC_D_12, EMC_D_13, EMC_D_14, EMC_D_15,
    EMC_D_16, EMC_D_17, EMC_D_18, EMC_D_19,
    EMC_D_20, EMC_D_21, EMC_D_22, EMC_D_23,
    EMC_D_24, EMC_D_25, EMC_D_26, EMC_D_27,
    EMC_D_28, EMC_D_29, EMC_D_30, EMC_D_31,
    EMC_DQM0, EMC_DQM1, EMC_DQM2, EMC_DQM3,
    EMC_DYCS0, EMC_DYCS1, EMC_DYCS2, EMC_DYCS3,
    EMC_OE,
    EMC_RAS,
    EMC_WE,
    ENET_COL, ENET_CRS, ENET_MDC, ENET_MDIO,
    ENET_RX_CLK, ENET_RX_DV, ENET_RX_ER,
    ENET_RXD0, ENET_RXD1, ENET_RXD2, ENET_RXD3,
    ENET_TX_CLK, ENET_TX_EN, ENET_TX_ER,
    ENET_TXD0, ENET_TXD1, ENET_TXD2, ENET_TXD3,
    I2C0_SCL, I2C0_SDA, I2C1_SCL, I2C1_SDA, I2C2_SCL, I2C2_SDA,
    I2S_RX_MCLK, I2S_RX_SCK, I2S_RX_SDA, I2S_RX_WS, I2S_TX_MCLK, I2S_TX_SCK,
    I2S_TX_SDA, I2S_TX_WS,
    LCD_CLKIN, LCD_DCLK, LCD_ENAB_M, LCD_FP, LCD_LE, LCD_LP, LCD_PWR,
    LCD_VD_0, LCD_VD_1, LCD_VD_2, LCD_VD_3,
    LCD_VD_4, LCD_VD_5, LCD_VD_6, LCD_VD_7,
    LCD_VD_8, LCD_VD_9, LCD_VD_10, LCD_VD_11,
    LCD_VD_12, LCD_VD_13, LCD_VD_14, LCD_VD_15,
    LCD_VD_16, LCD_VD_17, LCD_VD_18, LCD_VD_19,
    LCD_VD_20, LCD_VD_21, LCD_VD_22, LCD_VD_23,
    MC_0A, MC_0B, MC_1A, MC_1B, MC_2A, MC_2B,
    MC_ABORT, MC_FB0, MC_FB1, MC_FB2,
    NMI,
    PWM0_1, PWM0_2, PWM0_3, PWM0_4, PWM0_5, PWM0_6, PWM0_CAP0,
    PWM1_1, PWM1_2, PWM1_3, PWM1_4, PWM1_5, PWM1_6, PWM1_CAP0, PWM1_CAP1,
    QEI_IDX, QEI_PHA, QEI_PHB,
    RTC_EV0, RTC_EV1, RTC_EV2,
    SD_CLK, SD_CMD, SD_DAT_0, SD_DAT_1, SD_DAT_2, SD_DAT_3, SD_PWR,
    SPIFI_CLK, SPIFI_CS, SPIFI_IO_0, SPIFI_IO_1, SPIFI_IO_2, SPIFI_IO_3,
    SSP0_MISO, SSP0_MOSI, SSP0_SCK, SSP0_SSEL,
    SSP1_MISO, SSP1_MOSI, SSP1_SCK, SSP1_SSEL,
    SSP2_MISO, SSP2_MOSI, SSP2_SCK, SSP2_SSEL,
    STCLK,
    T0_CAP0, T0_CAP1, T0_MAT0, T0_MAT1, T1_CAP0, T1_CAP1,
    T1_MAT0, T1_MAT1, T1_MAT2,
    T2_CAP0, T2_CAP1, T2_MAT0, T2_MAT1, T2_MAT2, T2_MAT3,
    T3_CAP0, T3_CAP1, T3_MAT0, T3_MAT1, T3_MAT2, T3_MAT3,
    TRACECLK, TRACEDATA_0, TRACEDATA_1, TRACEDATA_2, TRACEDATA_3,
    U0_OE, U0_RXD, U0_TXD,
    U1_CTS, U1_DCD, U1_DSR, U1_DTR, U1_RI, U1_RTS, U1_RXD, U1_TXD,
    U2_OE, U2_RXD, U2_TXD,
    U3_OE, U3_RXD, U3_TXD,
    U4_OE, U4_RXD, U4_SCLK, U4_TXD,
    USB_CONNECT1, USB_CONNECT2, USB_DM1, USB_DP1, USB_DP2,
    USB_HSTEN1, USB_HSTEN2,
    USB_INT1, USB_LS1, USB_OVRCR1, USB_OVRCR2,
    USB_PPWR1, USB_PPWR2, USB_PWRD1, USB_PWRD2,
    USB_RCV1, USB_RX_DM1, USB_RX_DP1,
    USB_SCL1, USB_SDA1, USB_SSPND1,
    USB_TX_DM1,
    USB_TX_DP1, USB_TX_E1,
    USB_UP_LED1, USB_UP_LED2,
    USB_VBUS,
    RESERVED
} funcion_pin_t;

/* Estructura para describir la configuración de la función de un pin.
 */
typedef struct
{
    LPC_GPIO_TypeDef    *gpio_regs;
    uint32_t            mascara_pin;
    funcion_pin_t       funcion;
    uint32_t            configuracion_es;
} configuracion_funcion_pin_t;

/*===== Prototipos de funciones ================================================
 */

void iocon_configurar_pin(LPC_GPIO_TypeDef *gpio_regs,
                          uint32_t mascara_pin,
                          funcion_pin_t funcion,
                          uint32_t configuracion_es);

void iocon_configurar_grupo_pines(const configuracion_funcion_pin_t* pf);

#endif  /* IOCON_LPC40XX_H */
