/***************************************************************************//**
 * \file    joystick.h
 *
 * \brief   Función básica de lectura del joystick de la tarjeta Embedded
 *          Artist LPC4088.
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "tipos.h"

/*******************************************************************************
 * Constantes.
 */
#define JOYSTICK_NADA       0
#define JOYSTICK_ARRIBA     1
#define JOYSTICK_ABAJO      2
#define JOYSTICK_IZQUIERDA  3
#define JOYSTICK_DERECHA    4
#define JOYSTICK_CENTRO     5

/*******************************************************************************
 * Prototipos de funciones.
 */
int32_t leer_joystick(void);

#endif  /* JOYSTICK_H */
