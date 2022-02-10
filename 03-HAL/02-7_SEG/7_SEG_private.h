/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 25 SEP 2020                                                       */
/*********************************************************************************/
#ifndef _7_SEG_PRIVATE_H
#define _7_SEG_PRIVATE_H



	/***************   check of 7-SEG type (Common Type)      *******************/
#if CommonType == COMMON_CATHODE
	#define SEVEN_SEG_HIGH 		 HIGH
	#define	SEVEN_SEG_LOW  		 LOW
#elif CommonType == COMMON_ANODE
	#define SEVEN_SEG_HIGH 		 LOW
	#define SEVEN_SEG_LOW  		 HIGH
#endif

#endif // _7_SEG_PRIVATE_H
