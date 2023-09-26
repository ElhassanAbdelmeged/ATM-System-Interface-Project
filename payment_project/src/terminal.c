#include "terminal.h"

#define cardMonthStartInd (0u) // start index of month of card expire date
#define cardMonthEndInd (1u)   // end index of month of card expire date
#define cardYearStartInd (3u)  // start index of year of card expire date
#define cardYearEndInd (4u)    // end index of year of card expire date

#define transMonthStartInd (3u) // start index of month of transaction date
#define transMonthEndInd (4u)   // end index of month of transaction date
#define transYearStartInd (6u)  // start index of year of transaction date
#define transYearEndInd (9u)    // end index of year of transaction date

extern float32 g_MaxTransAmount;
//1

typedef enum EN_terminalError_t
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    EN_terminalError_t transicton_state = TERMINAL_OK;


    if (termData == NULL)
    {
    	transicton_state  = WRONG_DATE;
    }
    else
    {
        time_t CurrentTime = time(NULL);
        struct tm* CurrentDate = localtime(&CurrentTime);

        // Store the date in format of DD/MM/YYYY
        sprintf(termData->transactionDate, "%02d/%02d/%4d",/*The sprintf function returns the number of characters stored in the array s, not including the terminating null character. */
            CurrentDate->tm_mday,
            CurrentDate->tm_mon + 1,
            CurrentDate->tm_year + 1900);
    }
    return transicton_state;
}



/*2*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    uint8 card_Month;
    uint16 card_Year;
    uint8 terminal_Month;
    uint16 terminal_Year;

    EN_terminalError_t transicton_state = TERMINAL_OK;

    // cardExpirationDate format MM/YY
    card_Month = convertDateToInteger(cardData.cardExpirationDate, cardMonthStartInd, cardMonthEndInd);
    card_Year = convertDateToInteger(cardData.cardExpirationDate, cardYearStartInd, cardYearEndInd);

    // transactionDate format YY/MM/YYYY
    terminal_Month = convertDateToInteger(termData.transactionDate, transMonthStartInd, transMonthEndInd);
    terminal_Year = convertDateToInteger(termData.transactionDate, transYearStartInd, transYearEndInd);

    card_Year = (terminal_Year / 100) * 100 + card_Year; // to  make card expire year date consist of four digits  instead of 22 to be 2022 so can be compared with term year date

    if (card_Year == terminal_Year)
    {
        if (card_Month > terminal_Month)
        {
        	transicton_state = TERMINAL_OK;
        }
        else
        {
        	transicton_state = EXPIRED_CARD;
        }
    }
    else if (card_Year > terminal_Year)
    {
    	transicton_state = TERMINAL_OK;
    }
    else if (card_Year < terminal_Year)
    {
    	transicton_state = EXPIRED_CARD;
    }

    return transicton_state;
}

/*3 is optional  see it plz after the mid_term*/

/*4*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    float transaction_Amount;
    EN_cardError_t transaction_state = TERMINAL_OK;

    printf("Please enter the transaction amount and press enter: ");
    scanf("%f", &transaction_Amount);
    printf("\n");

    if (termData == NULL)
    {
    	transaction_state = INVALID_AMOUNT;
    }
    else if (transaction_Amount <= 0.0f)
    {
    	transaction_state = INVALID_AMOUNT;
    }
    else
    {
        termData->transAmount = transaction_Amount;
        transaction_state = TERMINAL_OK;
    }

    return transaction_state;
}


/*5*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
    EN_cardError_t transaction_state = TERMINAL_OK;

    if (termData == NULL)
    {
    	transaction_state = INVALID_MAX_AMOUNT;
    }
    else if (g_MaxTransAmount > 0)
    {
        termData->maxTransAmount = g_MaxTransAmount;
    }
    else
    {
    	transaction_state = INVALID_MAX_AMOUNT;
    }

    return transaction_state;
}


/*6*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{

    EN_cardError_t transaction_state = TERMINAL_OK;

    if (termData == NULL)
    {
    	transaction_state = EXCEED_MAX_AMOUNT;
    }
    else if (termData->transAmount > termData->maxTransAmount || termData->maxTransAmount == 0.0f)
    {
    	transaction_state = EXCEED_MAX_AMOUNT;
    }
    else
    {
    	transaction_state = TERMINAL_OK;
    }

    return transaction_state;
}





