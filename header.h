# define V 10
#define MAX_passengers 200
#define HASH_SIZE 101
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

typedef struct Customer {
    char name[50];
    char gender;
    int age;
    char source[50];
    char destination[50];
    struct Customer *next;
} Customer;

int num_passengers = 0;
int stack[MAX_passengers];
int top=-1;

typedef struct Seat{
	int seat_number;
	char seat_class[15];
	int availability;
}Seat;

typedef struct node{
	Seat data;
	int priority;
	struct node *next;
}node;

node *createNode(Seat seat,int );

int priority(Seat seat);

void insert(node **head,Seat seat,int priority);

Seat dequeue(node **head);

int isEmpty(node **head);

void displayMenu();

unsigned int hashFunction(char *key);

void insertCustomer(Customer *new_customer);

Customer *getCustomer(char *name);

void addCustomer();

void displaypassengers(char *source,char *destination);

void displayAirports();
