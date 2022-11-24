#include <iostream>
#include <stdio.h>
#include "app.h"

ST_cardData_t usercard = {0};
ST_terminalData_t termData = {0};


void checkCard(ST_cardData_t* mycard)
{
    //to check card Name 
    std::cout << "card Name:" << (getCardHolderName(mycard) ? "Wrong Name" : "OK") << '\n';

    //to check card date 
    std::cout << "card date:" << (getCardExpiryDate(mycard) ? "WRONG_EXP_DATE" : "OK") << '\n';

    //to check card PIN 
    std::cout << "card PIN:" << (getCardPAN(mycard) ? "WRONG_PAN" : "OK") << '\n';
}

void checkTerm(ST_terminalData_t* termData, ST_cardData_t* mycard)
{
    //to check Transaction Date
    std::cout << "Transaction Date:" << (getTransactionDate(termData) ? "WRONG_DATE" : "OK") << '\n';
    //to check Card Expired
    std::cout << "Card Expired:" << (isCardExpired(*mycard, *termData) ? "EXPIRED_CARD" : "OK") << '\n';
    //to check Transaction Amount 
    std::cout << "Transaction Amount:" << (getTransactionAmount(termData) ? "INVALID_AMOUNT" : "OK") << '\n';
    //to check Below Max Amount 
    std::cout << "Below Max Amount:" << (isBelowMaxAmount(termData) ? "EXCEED_MAX_AMOUNT" : "OK") << '\n';
    //to check SET Max Amount
    std::cout << "Max Amount:" << (setMaxAmount(termData) ? "INVALID_MAX_AMOUNT " : "OK") << '\n';

}

void appStart(void)
{
    getCardData();
    //ST_cardData_t mycard{ "Noura Mohamed Mohamed", "12345678901234567", "05/25" };
    //checkCard(&mycard);

    //ST_terminalData_t termData{ 90,0,"25/06/2022" };
    //checkTerm(&termData, &mycard);

}

void getCardData()
{
    //Get card data
    getCardHolderName();
    getCardExpDate();
    //getCardHolderName();
}

void getCardHolderName()
{
    printf("Welcome to Payment Aplication\n");

    //Get Holder Name
    printf("Please inter your name , your name should be more than 20 and less than 24 then press Enter \n");
    printf("Card Holder Name :");
    fgets((char*)usercard.cardHolderName, 50, stdin);

    while (getCardHolderName(&usercard)) 
    {
        printf("wrong Name ,Please inter your name again\n");
        printf("Card Holder Name :");
        fgets((char*)usercard.cardHolderName, 50, stdin);
    };
}

void getCardExpDate()
{
    char cardExpDate;
    //Get Card Exp date
    printf("Please Inter Card Exp Date , your card exp date should be 5\n");
    printf("characters string in the format \"mm / yy\", e.g \"05 / 25\". then press enter \n");
    printf("card exp date :");
    fgets((char*)usercard.cardExpirationDate, 10, stdin);
    
    while (getCardExpiryDate(&usercard)){
        printf((char*)usercard.cardExpirationDate);
        printf("wrong card expiry date ,Please inter your card expiry date again\n");
        printf("card expiry date :");
        fgets((char*)usercard.cardExpirationDate, 10, stdin);
    } ;
}

void getCardPAN() 
{

}
