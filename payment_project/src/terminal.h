/*
 * terminal.h
 *
 *  Created on: Nov 21, 2022
 *      Author: dell
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_
/*include useful libraries*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>/*to get the currant date from the PC*/
#include "card.h"


/*******************************************************************************
 *                                Types Declarations                          *
 *******************************************************************************/


typedef enum EN_terminalError_t
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8 transactionDate[11];
}ST_terminalData_t;

/**************************************************************************
 *								Functions Prototypes
 *************************************************************************/


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float32 maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional
//uint8 stringToInteger(uint8 *string,uint8 start,uint8 end);








#endif /* TERMINAL_H_ */
