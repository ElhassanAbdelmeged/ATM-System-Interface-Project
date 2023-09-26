/*
 ============================================================================
 Name        : payment_project.c
 Author      : EL_HASSAN_ABDELMAGED
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "std_types.h"



int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	uint8 i;
	ST_cardData_t X ={0};
	EN_cardError_t y;
 	y=getCardHolderName(&X);
	printf("%d",y);

 	y=getCardExpiryDate(&X);
	printf("%d",y);


 	y=getCardPAN(&X);
	printf("%d",y);


	return 0;
}
