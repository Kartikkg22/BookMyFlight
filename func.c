# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "header.h"
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>


Customer *hashTable[HASH_SIZE] = {NULL};
node *createNode(Seat seat,int p){
	node *temp=(node*)malloc(sizeof(node));
	temp->data=seat;
	temp->priority=p;
	temp->next=NULL;
	return temp;
}

int priority(Seat seat){
	if(seat.availability){
		if(strcmp(seat.seat_class,"Business")==0)
			return 2;
		else if(strcmp(seat.seat_class,"Economy")==0)
			return 1;
		else
			return 0;
	}
	else{
		return -1;
	}
}

void insert(node **head,Seat seat,int priority){
	node *start=*head;
	node *temp=createNode(seat,priority);
	if((*head)==NULL||(*head)->priority<priority){
		temp->next=*head;
		(*head)=temp;
	}
	else{
		while(start->next!=NULL && start->next->priority>=priority){
			start=start->next;
            
		}
		temp->next=start->next;
		start->next=temp;
	}
	return;
}

Seat dequeue(node **head){
	if(isEmpty(head)){
		fprintf(stderr,"Error:Queue is empty \n");
		exit(1);
	}
	node *temp=*head;
	Seat seat=temp->data;
	*head=(*head)->next;
	free(temp);
	return seat;
}

int isEmpty(node **head){
	if(*head==NULL)
		return 1;
	else
		return 0;
}

void displayMenu() {
    printf("\nCustomer Details Menu:\n");
    printf("1. Add Customer\n");
    printf("2. Display passengers\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

unsigned int hashFunction(char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_SIZE;
}

void insertCustomer(Customer *new_customer) {
    unsigned int key = hashFunction(new_customer->name);
    new_customer->next = hashTable[key];
    hashTable[key] = new_customer;
    num_passengers++;
}

Customer *getCustomer(char *name) {
    unsigned int key = hashFunction(name);
    Customer *current = hashTable[key];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void addCustomer() {
    if (num_passengers >= MAX_passengers) {
        printf("Maximum number of passengers reached.\n");
        return;
    }

    Customer *new_customer = malloc(sizeof(Customer));
    if (new_customer == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter customer name: ");
    scanf("%s", new_customer->name);

    printf("Enter customer gender (M/F): ");
    scanf(" %c", &new_customer->gender);

    printf("Enter customer age: ");
    scanf("%d", &new_customer->age);
    new_customer->next = NULL;
    insertCustomer(new_customer);
    printf("Customer added successfully.\n");
}

void displaypassengers(char* source, char* destination) {
    int j = 1;
    for (int i = 0; i < HASH_SIZE; i++) {
        Customer *current = hashTable[i];
        while (current != NULL) {
            printf("Passenger %d:\n", j);
            j++;
            printf("Name: %s\t\t Gender: %c\t\t Age: %d\n Source: %s\t\t Destination: %s\t",
                   current->name, current->gender, current->age,
                   source, destination);
            current = current->next;
        }
    }
}
void displayAirports() {
    printf(GREEN"\n**********BOOKMYFLIGHT**********\n"RESET);
    printf("\nWelcome to the Online Airline Booking System!\n\n");
    printf("Source Airports:\n");
    printf("1. Pune Airport \x1b[33m(PNQ)\n"RESET);
    printf("2. Mumbai Airport \x1b[33m(BOM)\n"RESET);
    printf("3. Bengaluru Airport \x1b[33m(BLR)\n"RESET);
    printf("4. Goa Airport \x1b[33m(GOI)\n"RESET);
    printf("5. Delhi Airport \x1b[33m(DEL)\n"RESET);
    printf("6. Kolkata Airport \x1b[33m(CCU)\n"RESET);
    printf("7. Hyderabad Airport \x1b[33m(HYD)\n"RESET);
    printf("8. Lucknow Airport \x1b[33m(LKO)\n"RESET);
    printf("9. Chennai Airport \x1b[33m(MAA)\n"RESET);
    
}
