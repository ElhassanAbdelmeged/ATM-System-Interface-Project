#include <stdio.h>
#include"card.h"


/************************************************************************
* Function Name: getCardPAN
* Purpose      : get card primary Account Number & check the entered wrong or acceptable
* Parameters   : ST_cardData_t* pointer :struct typedef in card.h
* Return value : EN_cardError_t:  enum typedef in card.h
*************************************************************************/

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{

    uint8 cardHolderName[25]={0};
    uint8 cardHolderNameLength=0;
	EN_cardError_t Name_state;
	uint8 Name_flag=0;
	uint8 i;
	printf("Please enter the card holder name then press enter:\n");
	 gets(cardHolderName);
	 cardHolderNameLength = strlen(cardHolderName);


	 if(cardData==NULL)
	 	{
	 		Name_state=WRONG_NAME;
	 	}

	 else if((cardHolderNameLength<25) || (cardHolderNameLength>19))
		{

	for(i=0;i<cardHolderNameLength;i++)
	{
		if (((cardHolderName[i]>='A')&&(cardHolderName[i]<='Z'))
			|| ((cardHolderName[i]>='a')&&(cardHolderName[i]<='z'))
			|| (cardHolderName[i]==' ')|| (cardHolderName[i]=='\0'))

		{
				continue;
		}


		else{
			Name_state=WRONG_NAME;
			Name_flag=1;
			break;
		}

	}


		if(Name_flag==0)
		{

			strcpy(cardData->cardHolderName,cardHolderName); //I WIIL SEE Y
		}


		}
	 else
	 		{
	 		Name_state=WRONG_NAME;
	 		}




	return Name_state;

}


/************************************************************************
* Function Name: getCardExpiryDate
* Purpose      : get card Expire date & check the entered wrong or acceptable
* Parameters   : ST_cardData_t* pointer:struct typedef in card.h
* Return value : EN_cardError_t:enum typeddef in card.h
*************************************************************************/


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{

    uint8 cardExpirationDate[5];
    uint8 cardExpirationDateLength;
    EN_cardError_t Date_state= CARD_OK;
    uint8 month;/*to save the converted string indicates the month*/
    uint8 year;/*to save the converted string indicates the year*/

    printf("\n");
    printf("Please enter the expire date (format \"MM/YY\") then press enter: ");
    gets(cardExpirationDate);

    cardExpirationDateLength = strlen(cardExpirationDate);

  month= stringToInteger(cardExpirationDate,0,1); /*0 index which is the first element of the string*/
  year= stringToInteger(cardExpirationDate,3,4); /*0 index which is the first element of the string*/


  if(cardData==NULL)
  {

	  Date_state=WRONG_EXP_DATE;
  }

  else if((5==cardExpirationDateLength )&& (cardExpirationDate[2]=='/')&&month>0&&month<=12&& year>0 )
  {
	  strcpy(cardData->cardExpirationDate,cardExpirationDate);
  }
  else
	  Date_state=WRONG_EXP_DATE;

  return Date_state;
}









/************************************************************************
* Function Name: getCardPAN
* Purpose      : get card primary Account Number & check the entered wrong or acceptable
* Parameters   : ST_cardData_t* pointer :struct typedef in card.h
* Return value : EN_cardError_t:  enum typedef in card.h
*************************************************************************/


EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    uint8 primaryAccountNumber[20];
    uint8 primaryAccountNumberLength;
    EN_cardError_t PAN_state =CARD_OK;
    uint8 PAN_flag =0;

    printf("\n");
    printf("Please enter the Primary Account Number (PAN) then press enter: ");
    gets(primaryAccountNumber);



    primaryAccountNumberLength = strlen(primaryAccountNumber);

    if (cardData == NULL)
    {
    	PAN_state  = WRONG_NAME;
    }
    else if ((primaryAccountNumberLength >= 16) && (primaryAccountNumberLength <= 19))
    {
        int i;
        for(i=0;i<primaryAccountNumberLength ; i++)
        {

        	            if ((primaryAccountNumber[i] >= '0') && (primaryAccountNumber[i] <= '9'))
        	            {
        	                continue;
        	            }
        	            else
        	            {
        	            	PAN_state  = WRONG_PAN;
        	            	PAN_flag  = 1;
        	                break;
        	            }


								}
		if(PAN_flag==0)
		{
		strcpy(cardData->primaryAccountNumber,primaryAccountNumber);
		}

    }

    else
    {
    	PAN_state  = WRONG_PAN;
    }

return PAN_state;}





/*Description:the function takes a part of string and converts it INT
 * why we need it? as in this case the date will be written as MM/YY so the '/'
 * is the str[2] so if we used the atoi FUN only the RESULT WILL be only (MM)
 * so we need to take the  MM first and then YY
 * */


uint8 stringToInteger(uint8 *string,uint8 start,uint8 end)
{
	uint8 i=0,j=0 ;
	uint8 TEMP[5];
	uint8 RESULT;

	for(i=start;i<=end;i++)
	{
		TEMP[j++]=string[i];
	}

	TEMP[j]='\0';
	RESULT=atoi(TEMP);  /* atoi converts the string to integer*/

	return RESULT;

}
