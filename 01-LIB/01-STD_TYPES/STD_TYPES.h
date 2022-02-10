/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 26 AUG 2021                                                       */
/*********************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Boolean Data Type */
typedef unsigned char  		Bool;

/* Boolean Values */
#define FALSE       (0u)
#define TRUE        (1u)

#define HIGH        (1u)
#define LOW         (0u)

typedef unsigned char  			uint8 ;
typedef unsigned short  		uint16;
typedef unsigned long   		uint32;
typedef unsigned long long  uint64;

typedef signed char       	sint8 ;
typedef signed short 	  		sint16;
typedef signed long 	   		sint32;
typedef signed long long  	sint64;

typedef float 							float32;
typedef double							float64;

/**********************************************/

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;

typedef float f32;
typedef double f64;

/* for compiler use weak in can driver*/

#ifndef   __weak 
  #define __weak                                   __attribute__((weak))
#endif


#endif  // STD_TYPES_H
