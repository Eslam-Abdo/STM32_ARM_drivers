/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 22 SEP 2020                                                       */
/*********************************************************************************/
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H



/************* Options:     RCC_HSE_CRYSTAL
                            RCC_HSE_RC
                            RCC_HSI
                            RCC_PLL                     ****************/

#define RCC_CLOCK_TYPE      RCC_PLL


/************* Options:     RCC_PLL_IN_HSI_DIV_2
                            RCC_PLL_IN_HSE_DIV_2
                            RCC_PLL_IN_HSE             ****************/

/*** Note: Select value only if you  have PLL as input clock source ***/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT       RCC_PLL_IN_HSE
#endif

/************************ 				 Options:  						***********************/
/* 								 ClockFactor For PLL  Maybe :                                */
/*                              1-PLL_CLOCKk_MULTIPLE_BY_2                                   */
/*                              2-PLL_CLOCKk_MULTIPLE_BY_3                                   */
/*                              3-PLL_CLOCKk_MULTIPLE_BY_4                                   */
/*                              4-PLL_CLOCKk_MULTIPLE_BY_5                                   */
/*                              5-PLL_CLOCKk_MULTIPLE_BY_6                                   */
/*                              6-PLL_CLOCKk_MULTIPLE_BY_7                                   */
/*                              7-PLL_CLOCKk_MULTIPLE_BY_8                                   */
/*                              8-PLL_CLOCKk_MULTIPLE_BY_9                                   */
/*                              9-PLL_CLOCKk_MULTIPLE_BY_10                                  */
/*                              10-PLL_CLOCKk_MULTIPLE_BY_11                                 */
/*                              11-PLL_CLOCKk_MULTIPLE_BY_12                                 */
/*                              12-PLL_CLOCKk_MULTIPLE_BY_13                                 */
/*                              13-PLL_CLOCKk_MULTIPLE_BY_14                                 */
/*                              14-PLL_CLOCKk_MULTIPLE_BY_15                                 */
/*                              15-PLL_CLOCKk_MULTIPLE_BY_16                                 */
/*                                                                                           */
/*																						   	 */
/*** Note: Select value only if you  have PLL as input clock source ***/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_MUL_VAL     PLL_CLOCK_MULTIPLE_BY_9
#endif



#endif // RCC_CONFIG_H
