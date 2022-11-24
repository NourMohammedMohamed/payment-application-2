#include "card.h"


/*
*Check Name function 
*Check If the cardholder name is NULL, less than 20 characters or more than 24 will return WRONG_NAME error, else return OK
*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	return ((strlen((char*)cardData->cardHolderName) <= 24) & (strlen((char*)cardData->cardHolderName) >= 20))
		? EN_cardError_t::OK : EN_cardError_t::WRONG_NAME;
}

/*
*Check Exp Date function
*Check If the card expiry date is NULL, less or more than 5 characters, or has the wrong format will return WRONG_EXP_DATE error, else return OK
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	if (strlen((char*)cardData->cardExpirationDate) == 5)
	{
		int month, year;
		sscanf((char*)cardData->cardExpirationDate, "%d\/%d", &month, &year);

		if ((month >= 1 & month <= 12) & (year >= 00 & year <= 30)) 
		{
			return EN_cardError_t::OK;
		}
		else {
			return EN_cardError_t::WRONG_EXP_DATE;
		}
	}
	else {
		return EN_cardError_t::WRONG_EXP_DATE;
	}
}

/*
*Check PIN function
*Check If the PAN is NULL, less than 16 or more than 19 characters, will return WRONG_PAN error, else return OK.
*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	return ((strlen((char*)cardData->primaryAccountNumber) <= 19) & (strlen((char*)cardData->primaryAccountNumber) >= 16))
		? EN_cardError_t::OK : EN_cardError_t::WRONG_PAN;
}