#include "func.c"
#define MAX_SEATS 100
#define MAX_FIELD_SIZE 50
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

int main()
{
	FILE *file_pointer;
	char filename[100] = "seats.txt";
	char filename1[100] = "data.txt";
	Seat seats[MAX_SEATS];
	int num_seats = 0;
	int flag=0;

	file_pointer = fopen(filename, "r");
	if (file_pointer == NULL)
	{
		printf("Error opening file.\n");
		return 1; 
	}
	while (fscanf(file_pointer, "%d %s %d", &seats[num_seats].seat_number, seats[num_seats].seat_class, &seats[num_seats].availability) == 3)
	{
		num_seats++;
	}
	fclose(file_pointer);

	int choice;
	char *source = malloc(50 * sizeof(char));
	char *destination = malloc(50 * sizeof(char));
	node *priorityQueue = NULL;
	displayAirports();
	printf("Enter source as the airport code : ");
	scanf("%s", source);
	printf("Enter destination as the airport code : ");
	scanf("%s", destination);
	int num;
	printf("Enter the number of passengers : ");
	scanf("%d", &num);
	int x = num;
	FILE *file_pointer1;
	file_pointer1 = fopen(filename1, "w");
	do
	{
		displayMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			for (int i = 0; i < MAX_SEATS; i++)
			{
				Seat s = seats[i];
				insert(&priorityQueue, s, priority(s));
			}
			while (priorityQueue->next)
			{
				Seat s = dequeue(&priorityQueue);
				if (s.availability)
					printf("The seat number %d of \x1b[34m %s \x1b[0m class is available \n", s.seat_number, s.seat_class);
				else
					printf("The seat number %d of \x1b[31m %s \x1b[0m class is not available \n", s.seat_number, s.seat_class);
			}
			Seat s = dequeue(&priorityQueue);
			if (s.availability)
				printf("\nThe seat number %d of \x1b[34m %s \x1b[0m class is available \n", s.seat_number, s.seat_class);
			else
				printf("\nThe seat number %d of \x1b[3m %s \x1b[0m class is not available \n", s.seat_number, s.seat_class);
			
			printf("enter the seat number");
			scanf("%d", &stack[++top]);
			for (int i = 0; i < MAX_SEATS; i++)
			{
				if (stack[top] == seats[i].seat_number && seats[i].availability==1)
				{
					seats[i].availability = 0;
					flag=1;
					break;
				}
				
			}
			if(flag==1){
				printf("Seat is empty\n");
				addCustomer();
				num--;
			}
			else{
				printf("the seat is already taken\n");
				top--;
			}		
			printf("\n");
			for (int i = 0; i < num_seats; i++)
			{
				fprintf(file_pointer1, "%d %s %d\n", seats[i].seat_number, seats[i].seat_class, seats[i].availability);
			}
			break;
		case 2:
			printf("Exiting program.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
		}
		
	} while (choice != 2 && num > 0);
	fclose(file_pointer1);
	printf("Passenger details : \n");
	displaypassengers(source, destination);
	for(int i=0;i<MAX_SEATS;i++){
		if(stack[top]==seats[i].seat_number){
			printf("Seat_Number: %d\n",stack[top--]);
			printf("Seat_Class: %s \n",seats[i].seat_class);
		}
	}		
	printf("\n");
	printf("THANK YOU FOR CHOOSING OUR SERVICES! WISH YOU SAFE TRAVELS!\n");
	for (int i = 0; i < HASH_SIZE; i++)
	{
		Customer *current = hashTable[i];
		while (current != NULL)
		{
			Customer *next = current->next;
			free(current);
			current = next;
		}
	}
	return 0;
}
