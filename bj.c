#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include<ctype.h>
// Function to initialize the deck
void initializeDeck(char deck[]) {
    int k = 0;
    for (char i = '1'; i <= 'Q'; i++) {
        if (i == '9' + 1) {
            i = 'A';
        }
        if ((i >= '1' && i <= '9') || (i == 'A' || i == 'J' || i == 'K' || i == 'Q')) {
            for (int j = 0; j < 4; j++) {
                deck[k] = i;
                k++;
            }
        }
    }
}
char giving_random_cards(char deck[],int *card_taken,int *user_card_taken) {
    // Generate a random number between 0 and 51
    // to select a card from the deck
    // and remove it from the deck also increase the card_taken variable
    int random_number = (rand() % (52-*card_taken)) + 0;
    char card=  deck[random_number];
    *card_taken+=1;
    *user_card_taken+=1;
    for(int i=random_number;i<52-*card_taken;i++){
        deck[i]=deck[i+1];
    }
    return card;
}
void print_card(){}
void point_calculate(char user_deck[],int *point,int *user_card_taken,int *user_aces) {
    // Calculate the points based on the cards in the user's decks last card
    // and update the point variable accordingly
    // If the point exceeds 21 and there are aces, reduce the point by 10
    // and decrement the ace count
    // If the point is still greater than 21, set it to -1
    if(user_deck[*user_card_taken-1]=='A'){
        *user_aces+=1;
        *point+=11;
    }
    else if(user_deck[*user_card_taken-1]=='K'||user_deck[*user_card_taken-1]=='Q'||user_deck[*user_card_taken-1]=='J'||user_deck[*user_card_taken-1]=='1'){
        *point+=10;
    }
    else if(user_deck[*user_card_taken-1]>='2'&&user_deck[*user_card_taken-1]<='9'){
        *point+=user_deck[*user_card_taken-1]-'0';
    }
    if(*point>21&&*user_aces>0){
        *point-=10;
        *user_aces-=1;
    }

}
int main() {
    //setvbuf(stdout, NULL, _IONBF, 0);
    int card_taken=0;
    srand(time(0));
    char deck[52];
    initializeDeck(deck); // Call the function to initialize the deck
    /*int random_number = (rand() % (53)) + 0;
    printf("Random number: %d\n", random_number);
    // Print the deck
    for (int i = 0; i < 52; i++) {
        printf("%c\n", deck[i]);
    }*/
    printf("Okay first let me tell the rules of the game\n");
    printf("You will be given 2 cards and the dealer will be given 1 card\n");
    printf("You can choose to hit or stay\n");
    printf("If you hit, you will be given another card\n");
    printf("Until you choose to stay or your points exceed 21\n");
    printf("If you stay, the dealer will reveal their cards\n");
    printf("The dealer will hit depending on your point \n");
    printf("If your points exceed 21, you lose\n");
    printf("If the dealer's points exceed 21, you win\n");
    printf("If your points are greater than the dealer's points, you win\n");
    printf("If the dealer's points are greater than your points, you lose\n");
    printf("If your points are equal to the dealer's points, it's a tie\n");
    printf("If you have an ace, it can be counted as 1 or 11 depending on making maximum point\n");

    char user_deck[12];
    int user_card_taken=0;
    int user_point=0;
    int user_aces=0;
    char dealer_deck[12];
    int dealer_card_taken=0;
    int dealer_point=0;
    int dealer_aces=0;
    // Dealer showing his first card
    char dealer_card=giving_random_cards(deck,&card_taken,&dealer_card_taken);
    //dealer_card_taken+=1;
    dealer_deck[dealer_card_taken-1]=dealer_card;
    point_calculate(dealer_deck,&dealer_point,&dealer_card_taken,&dealer_aces);
    if(dealer_deck[dealer_card_taken-1]=='1'){
        printf("Dealer's first card is %c0\n", dealer_card);
    }
    else{
        printf("Dealer's first card is %c\n", dealer_card);
    }
    printf("Another hidden \n", dealer_card);
    dealer_card=giving_random_cards(deck,&card_taken,&dealer_card_taken);
    dealer_deck[dealer_card_taken-1]=dealer_card;
    point_calculate(dealer_deck,&dealer_point,&dealer_card_taken,&dealer_aces);
    //User's First two cards
    //User's First card
    char user_card=giving_random_cards(deck,&card_taken,&user_card_taken);
    //user_card_taken+=1;

    user_deck[user_card_taken-1]=user_card;
    point_calculate(user_deck,&user_point,&user_card_taken,&user_aces);
    //User's Second card
    user_card=giving_random_cards(deck,&card_taken,&user_card_taken);
    user_deck[user_card_taken-1]=user_card;
 //   printf("User card is %c\n", user_card);
    //printf("User card taken is %d\n", user_card_taken);
    point_calculate(user_deck,&user_point,&user_card_taken,&user_aces);
    printf("Your first two cards are %c", user_deck[0]);
    if(user_deck[0]=='1'){
        printf("0 ");
    }
    else{
        printf(" ");
    }
    printf("%c", user_deck[1]);
    if(user_deck[1]=='1'){
        printf("0\n");
    }
    else{
        printf("\n");
    }
    printf("Your points are %d\n", user_point);

    if(dealer_point==21 && user_point!=21){
        printf("Dealer hidden card is %c\n", dealer_deck[dealer_card_taken-1]);
        printf("Dealer points are %d\n", dealer_point);
        printf("Dealer wins by blackjack\n");
        return 0;
    }
    else if(user_point==21 && dealer_point!=21){
        printf("Dealer hidden card is %c\n", dealer_deck[dealer_card_taken-1]);
        printf("Dealer points are %d\n", dealer_point);
        printf("You win by blackjack\n");
        return 0;
    }
    else if(user_point==21 && dealer_point==21){
        printf("Dealer hidden card is %c\n", dealer_deck[dealer_card_taken-1]);
        printf("Dealer points are %d\n", dealer_point);
        printf("Its a blackjacked Draw\n");
        return 0;
    }
    
    //loop for user to hit or stay
    while(1){
        if(user_card_taken==2 &&user_point==21){
            break;
        }
        char choice;
        printf("Do you want to hit or stay? (h/s): ");
      //  fflush(stdout);
        scanf(" %c", &choice);
        if (tolower(choice) == 'h') {
            user_card=giving_random_cards(deck,&card_taken,&user_card_taken);
            user_deck[user_card_taken-1]=user_card;
            point_calculate(user_deck,&user_point,&user_card_taken,&user_aces);
            if(user_deck[user_card_taken-1]=='1'){
            printf("Your new card is %c0\n", user_deck[user_card_taken-1]);
            }
            else{
                printf("Your new card is %c\n", user_deck[user_card_taken-1]);
            }
            printf("Your new deck is:");
            //loop for showing new deck
            for(int i=0;i<user_card_taken;i++){
                    if(user_deck[i]=='1'){
                        printf("%c0 ",user_deck[i]);
                        continue;
                    }

                printf("%c ",user_deck[i]);
            }

            printf("Your points are %d\n", user_point);

           if(user_point>21){
                printf("Dealer wins\n");
                return 0;
            }
        } else if (tolower(choice) == 's') {
            break;
        } else {
            printf("Invalid choice. Please enter 'h' or 's'.\n");
        }
    }
    //loop for dealers turn
   // int j=0;
   if(dealer_deck[dealer_card_taken-1]=='1'){
    printf("Dealer's hidden card is %c0\n", dealer_deck[dealer_card_taken-1]);
 }
    else{
printf("Dealer's hidden card is %c\n", dealer_deck[dealer_card_taken-1]);
}
printf("Dealer's points are %d\n", dealer_point);
    while (1)
    {
        if(dealer_point>21){

            printf("you win\n");
            return 0;
        }
        if(dealer_point>user_point){
            printf("Dealer stays\n");
            printf("Dealer wins\n");
            return 0;
        }
        if(dealer_point<=user_point&&dealer_point<17){
            printf("Dealer hits\n");
            
        }
        if(dealer_point==user_point&&dealer_point>=17){
            printf("Dealer stays\n");
            printf("It's a tie\n");
            return 0;
        }
        if(dealer_point>=17){
            printf("Dealer stays\n");
            if(dealer_point>user_point){
                printf("Dealer wins\n");

            }
            else if(dealer_point<user_point){
                printf("You win\n");
            }
            else{
                printf("It's a tie\n");
            }

            return 0;
        }
        dealer_card=giving_random_cards(deck,&card_taken,&dealer_card_taken);
        dealer_deck[dealer_card_taken-1]=dealer_card;
        point_calculate(dealer_deck,&dealer_point,&dealer_card_taken,&dealer_aces);
        if(dealer_deck[dealer_card_taken-1]=='1'){
        printf("Dealer's new card is %c0\n", dealer_deck[dealer_card_taken-1]);
        }
        else{
            printf("Dealer's new card is %c\n", dealer_deck[dealer_card_taken-1]);
        }
        
        printf("Dealer's points are %d\n", dealer_point);

    }

    //user_deck[user_card_taken-1]=user_card;
    //user_deck[user_card_taken-1]=giving_random_cards(deck,&card_taken);


    return 0;
}
