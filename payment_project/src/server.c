#include"server.h"
#include "terminal.h"


/**************************************************************************
 *								 Global Variables
 *************************************************************************/


uint8 g_IndexOfValidAccount;
uint16 g_LastIndexSavedTrans = 0;
uint32 g_LastSequenceNumber = 1;


ST_transaction_t ST_Transactions_DB_t[0] = {0};

ST_accountsDB_t ST_Accounts_DB_t[255] = {
		2000.0, RUNNING, "12345678901234567890"
		,500000.0,RUNNING,"12345678901234567891"
		,100000.0,RUNNING,"12345678901234567892"
		,1500000.0,RUNNING,"12345678901234567893"
		,5000.0,BLOCKED,"12345678901234567894"
		,500000.0,BLOCKED,"12345678901234567895"
};






//1

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    EN_transState_t transState = APPROVED;


    if (transData == NULL)
    {
    	transState = INTERNAL_SERVER_ERROR;
    }
    else
    {


    	EN_serverError_t checkAcountValidity = isValidAccount(&transData->cardHolderData);

    	EN_serverError_t checkAmountAvilabilty = isAmountAvailable(transData);


        if (checkAcountValidity != SERVER_OK)
        {
        	transState = DECLINED_STOLEN_CARD;
        }
        else if (checkAmountAvilabilty != SERVER_OK)
        {
        	transState = DECLINED_INSUFFECIENT_FUND;
        }
        else
        {
            EN_serverError_t checkSavedTrans = SAVING_FAILED;

            checkSavedTrans = saveTransaction(transData);

            if (checkSavedTrans != SERVER_OK)
            {
            	transState = INTERNAL_SERVER_ERROR;
            }
            else
            {
                float newBalance = 0.0;

                newBalance = ST_Accounts_DB_t[255].balance - transData->terminalData.transAmount;
                ST_Accounts_DB_t[255].balance = newBalance;
                transData->transState = APPROVED;
            }
        }
    }

    return transState;
}




EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);





void listSavedTransactions(void){


    EN_serverError_t retResult = SERVER_OK;

    if (transData == NULL)
    {
        transData->transState = INTERNAL_SERVER_ERROR;
        retResult = SAVING_FAILED;
    }
    else
    {
        if (g_LastIndexSavedTrans < 255)
        {
            transData->transactionSequenceNumber = g_LastSequenceNumber;
            ST_Transactions_DB_t[gLastIndexSavedTrans].transactionSequenceNumber = transData->transactionSequenceNumber;

            strcpy(ST_Transactions_DB_t[g_LastIndexSavedTrans].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
            strcpy(ST_Transactions_DB_t[g_LastIndexSavedTrans].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);
            strcpy(ST_Transactions_DB_t[g_LastIndexSavedTrans].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);

            ST_Transactions_DB_t[g_LastIndexSavedTrans].terminalData.transAmount = transData->terminalData.transAmount;
            ST_Transactions_DB_t[g_LastIndexSavedTrans].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
            strcpy(ST_Transactions_DB_t[g_LastIndexSavedTrans].terminalData.transactionDate, transData->terminalData.transactionDate);

            ST_Transactions_DB_t[g_LastIndexSavedTrans].transState = APPROVED;
            transData->transState = APPROVED;

            gLastSequenceNumber++;
            gLastIndexSavedTrans++;
            retResult = OK_SERVER;
        }
        else
        {
            transData->transState = INTERNAL_SERVER_ERROR;
            retResult = SAVING_FAILED;
        }
    }

    return retResult;

}

