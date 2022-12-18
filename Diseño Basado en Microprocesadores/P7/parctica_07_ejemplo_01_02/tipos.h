/***************************************************************************//**
 * \file    tipos.h
 *
 * \brief   Definiciones de tipos para el compilador ARM.
 *
 * \detail  Basado en mc3_types.h de MISRA-C 2012.
 */

#ifndef TIPOS_H
#define TIPOS_H

/*------------------------------------------------------------------------------
 * Incluir stddef.h, que contiene definiciones para NULL, size_t, ptrdiff_t
 * y wchar_t
 */
#include <stddef.h>

/*------------------------------------------------------------------------------
 * Si el compilador C99 estarán disponible stdint.h y stdbool.h así que los
 * aprovechamos. El tipo bool_t de define en base al _Bool de stdbool.h.
 */
#if defined ( __STDC_VERSION__ ) && ( __STDC_VERSION__ >= 199901L ) /* C99 */

#include <stdint.h>
#include <stdbool.h>
typedef _Bool bool_t;


/*------------------------------------------------------------------------------
 * Si no estamos en un compilador C99 y no está definido el símbolo __stdint_h,
 * definir los tipos enteros.
 */
#else

#ifndef __stdint_h

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef signed long long    int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

#endif  /* __stdint_h */

#endif  /* defined ( __STDC_VERSION__ ) && ( __STDC_VERSION__ >= 199901L ) */

/*------------------------------------------------------------------------------
 * Si no está definido el símbolo __bool_true_false_are_defined definir el tipo
 * bool_t como unsigned char. Si está definido definir bool_t a partir de bool.
 */
#ifndef __bool_true_false_are_defined
typedef unsigned char       bool_t;
#else
typedef bool                bool_t;
#endif

/*------------------------------------------------------------------------------
 * Si no están definidor los símbolos FALSE y TRUE, definirlos.
 */
#ifndef FALSE
#define FALSE ((bool_t)0)
#endif

#ifndef TRUE
#define TRUE  ((bool_t)1)
#endif

/*------------------------------------------------------------------------------
 * Definir tipos para datos flotantes que indiquen claramente su tamaño.
 */
typedef float               float32_t;
typedef double              float64_t;

#endif  /* TIPOS_H */
