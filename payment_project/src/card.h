#ifndef CARD_H_
#define CARD_H_

#include "std_types.h"





/*******************************************************************************
 *                                Types Declarations                          *
 *******************************************************************************/

typedef struct ST_cardData_t
{
     uint8 cardHolderName[25];
     uint8 primaryAccountNumber[20];
     uint8 cardExpirationDate[6];
}ST_cardData_t;


typedef enum EN_cardError_t
{
     CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;





/**************************************************************************
 *								Functions Prototypes
 *************************************************************************/

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
uint8 stringToInteger(uint8 *string,uint8 start,uint8 end);







#endif /* CARD_H_ */