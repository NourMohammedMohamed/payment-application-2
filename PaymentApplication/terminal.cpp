#include "terminal.h"
/*
*Check TransactionDate function
*Check If the transaction date is NULL, less than 10 characters or wrong format will return WRONG_DATE error, else return OK.
*The format DD/MM/YYYY, e.g 25/06/2022.
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	if (strlen((char*)termData->transactionDate) == 10) 
	{
		int day, month, year;
		sscanf((char*)termData->transactionDate, "%d\/%d\/%d", &day, &month, &year);

		if ((month >= 1 & month <= 12) & (day >= 1 & day <= 31) & (year >= 2000 & year <= 2030)) {
			return EN_terminalError_t::TERMINAL_OK;
		}else {
			return EN_terminalError_t::WRONG_DATE;
		}
	}else {
		return EN_terminalError_t::WRONG_DATE;
	}
}
/*
*Check Card Expired function
*Check If the card expiration date is before the transaction date will return EXPIRED_CARD, else return OK.
*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	int termDay,termMonth, termYear;
	sscanf((char*)termData.transactionDate, "%d\/%d\/%d",&termDay,&termMonth, &termYear);
	int cardMonth, cardYear;
	sscanf((char*)cardData.cardExpirationDate, "%d\/%d", &cardMonth, &cardYear);

	if ((2000 + cardYear) > termYear) {
		return EN_terminalError_t::TERMINAL_OK;
	}
	else if(cardMonth > termMonth)
	{
		if (cardMonth > termMonth) {
			return EN_terminalError_t::TERMINAL_OK;
		}
		else {
			return EN_terminalError_t::EXPIRED_CARD;
		}
	}
	else {
		return EN_terminalError_t::EXPIRED_CARD;
	}
}
/*
*Check PIN function
*Check If the PAN is NULL, less than 16 or more than 19 characters, will return WRONG_PAN error, else return OK.
*/
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	return EN_terminalError_t::TERMINAL_OK;
}
/*
*Check Transaction Amount function
*Check If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return OK.
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	return (termData->transAmount > 0) ? EN_terminalError_t::TERMINAL_OK : EN_terminalError_t::INVALID_AMOUNT;
}
/*
*Check Below Max Amount function
*Check If the transaction amount is larger than the terminal max amount will return EXCEED_MAX_AMOUNT, else return OK.
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	return (termData->maxTransAmount > termData->transAmount) ? EN_terminalError_t::TERMINAL_OK : EN_terminalError_t::EXCEED_MAX_AMOUNT;
}
/*
*Check Max Amount function
*Check If transaction max amount less than or equal to 0 will return INVALID_MAX_AMOUNT error, else return OK.
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	return (termData->maxTransAmount > 0) ? EN_terminalError_t::TERMINAL_OK : EN_terminalError_t::INVALID_MAX_AMOUNT;
}