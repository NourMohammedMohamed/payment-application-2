#include "server.h"

ST_accountsDB_t accountsDB[255] = {0};
ST_transaction transaction[255] = {0};

/*
*Check  recieve Transaction Data function
*Check If the account does not exist return DECLINED_STOLEN_CARD,
if the amount is not available will return DECLINED_INSUFFECIENT_FUND,
if a transaction can't be saved will return INTERNAL_SERVER_ERROR and will not save the transaction, else returns APPROVED
It will update the database with the new balance.
*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	//If the account does not exist
	if (isValidAccount(&transData->cardHolderData))
		return EN_transState_t::DECLINED_STOLEN_CARD;

	//if the amount is not available
	if (isAmountAvailable(&transData->terminalData))
		return EN_transState_t::DECLINED_INSUFFECIENT_FUND;
	
	//if a transaction can't be saved
	if (saveTransaction(transData))
		return EN_transState_t::INTERNAL_SERVER_ERROR;
	
	//
	return EN_transState_t::APPROVED;
}
/*
This function will take card data and validate these data.
It checks if the PAN exists or not in the server's database.
If the PAN doesn't exist will return DECLINED_STOLEN_CARD, else will return OK
*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	int i = 0;

	for (i = 0; i < 255; i++)
	{
		if (accountsDB[i].primaryAccountNumber == cardData->primaryAccountNumber) {
			return EN_serverError_t::SERVER_OK;
		}
	}
	if (i == 255)
	{
		//If the account does not exist
		return EN_serverError_t::ACCOUNT_NOT_FOUND;
	}
}
/*
This function will take terminal data and validate these data.
It checks if the transaction's amount is available or not.
If the transaction amount is greater than the balance in the database will return LOW_BALANCE, else will return OK
You should deliver a maximum 2min video to discuss your implementation and run different test cases on this function
*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	return (getTransactionAmount(termData)) ? EN_serverError_t::LOW_BALANCE : EN_serverError_t::SERVER_OK;
}

/*
This function will take all transaction data into the transactions database.
It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
If saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
If transaction can't be saved will return SAVING_FAILED, else will return OK
*/
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	static int transactionSequenceNumber = 0;
	if (transData->transState == EN_transState_t::APPROVED) {
		if (transaction->transactionSequenceNumber < 255) 
		{
			transaction[transactionSequenceNumber] = *transData;
			transData->transactionSequenceNumber = transactionSequenceNumber;
			transactionSequenceNumber++;
			return EN_serverError_t::SERVER_OK;
		}
		else {
			return EN_serverError_t::SAVING_FAILED;
		}
	}
	else {
		return EN_serverError_t::SAVING_FAILED;
	}
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	if (transData->transactionSequenceNumber == transactionSequenceNumber)
	{
		return EN_serverError_t::SERVER_OK;
	}
	else {
		return EN_serverError_t::TRANSACTION_NOT_FOUND;
	}

}