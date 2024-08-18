#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
	int id;
	char name [50];
	int age;
	float GPA;
};

/*------------ Defining a structure to represent the linked list ------------ */

struct node
{
	struct student data;
	struct node *next;
};
struct node *head=NULL; // Defining a pointer to point to the top of the linked list

/*------------ Defining the prototypes of the functions ------------ */

void addStudent(const struct student *const ptr);
int SearchID(int ID);
void displayStudents(void);
void searchStudentByID(int ID);
void updateStudentByID(int ID);
void deleteStudentByID(int ID);
float calculateAverageGPA(void);
void searchHighestGPA(void);
int CheckName(char *Name);

/*------------ The main program ------------ */

int main (void)
{
	setvbuf (stdout,NULL,_IONBF,0);
	setvbuf (stderr,NULL,_IONBF,0);
	unsigned int Choice; // Defining an integer to receive the choice of the required operation from the user
	int ID; // Defining a variable to receive the ID from the user in the operations that require the ID
	while (1)
	{
		printf ("\n-----------------------------\nMain Program\n-----------------------------\n");
		printf ("1.Add Student\n");
		printf ("2.Display Student\n");
		printf ("3.Search by ID\n");
		printf ("4.Update student by ID\n");
		printf ("5.Delete student by ID\n");
		printf ("6.Calculate average GPA\n");
		printf ("7.Search for highest GPA\n");
		printf ("8.Exit");
		printf ("\n-----------------------------\n");
		printf ("Please enter your choice: ");
		scanf ("%u",&Choice); // Receiving the choice from the user
		switch (Choice)
		{
		case 1: // (Add student) operation
		{
			struct student * const NewStd=(struct student*)malloc(sizeof(struct student)); // Allocating a structure with size of the student's structure and define a constant pointer to point to this structure
			printf ("Enter the name: ");
			scanf ("%s",(NewStd->name)); // Receiving the name of the student
			if (CheckName(NewStd->name)) // Check that the entered name is valid and if not, free the allocated structure and return to the main menu
			{
				printf ("The name is invalid");
				free (NewStd); // Free the allocated structure
				break;
			}
			printf ("Enter the ID: ");
			scanf ("%d",&(NewStd->id)); // Receiving the ID of the student
			if (NewStd->id <= 0) // Check that the entered ID is valid and if not, free the allocated structure and return to the main menu
			{
				printf ("The entered ID is invalid, please enter a number greater than 0");
				free(NewStd);
				break;
			}
			printf ("Enter the age: ");
			scanf ("%d",&(NewStd->age)); // Receiving the age of the student
			if (NewStd->age <= 0) // Check that the entered age is valid and if not, free the allocated structure and return to the main menu
			{
				printf ("The entered age is invalid, please enter a number greater than 0");
				free(NewStd);
				break;
			}
			printf ("Enter the GPA: ");
			scanf ("%f",&(NewStd->GPA)); // Receiving the GPA of the student
			if (NewStd->GPA < 0 || NewStd->GPA > 3) // Check that the entered GPA is valid and if not, free the allocated structure and return to the main menu
			{
				printf ("The GPA is invalid");
				free (NewStd); // Free the allocated structure
				break;
			}
			addStudent(NewStd); // Calling the add student function by sending the pointer to the structure to it
			free(NewStd); // Deleting the allocated structure after adding it to the list to free up the memory
		}
		break;
		case 2: // (Display student) operation
			displayStudents(); // Calling the operation to display the students
			break;
		case 3: // (Search student by ID) operation
			printf ("Please enter the ID of the student: ");
			scanf ("%d",&ID); // Receiving the ID from the user
			if (ID <= 0) // Check that the entered ID is valid
			{
				printf ("The entered ID is invalid, please enter a number greater than 0");
				break;
			}
			searchStudentByID (ID); // Calling the searching function by sending the received ID
			break;
		case 4: // (Update student by ID) operation
			printf ("Please enter the ID of the student you want to update: ");
			scanf ("%d",&ID); // Receiving the ID from the user
			if (ID <= 0) // Check that the entered ID is valid
			{
				printf ("The entered ID is invalid, please enter a number greater than 0");
				break;
			}
			updateStudentByID (ID); // Calling the updating student's info's function by sending the received ID
			break;
		case 5: // (Delete student by ID) operation
			printf ("Please enter the ID you want to delete: ");
			scanf ("%d",&ID); // Receiving the ID from the user
			if (ID <= 0) // Check that the entered ID is valid
			{
				printf ("The entered ID is invalid, please enter a number greater than 0");
				break;
			}
			deleteStudentByID (ID); // Calling the delete function by sending the received ID
			break;
		case 6: // (Calculate average GPA) operation
			if (calculateAverageGPA()==-1) // If the returned value from the function equals -1, it means that the list is empty and return to the main menu
			{
				break;
			}
			else // If the list is not empty, calculate and display the average of the GPA
			{
				printf ("\n-----------------------------\n");
				printf ("The average of GPA=%f",calculateAverageGPA());
			}
			break;
		case 7: // (Search for highest GPA) operation
			searchHighestGPA(); // Calling the searching of the highest GPA's function by sending the received ID
			break;
		case 8: // Termination of the program
			printf ("The program is terminated");
			return 0;
		default: // If the entered number is not valid then return to the main menu
			printf ("The entered operation is not valid");
			break;
		}
	}
}

/*------------------------------ Add Student function ------------------------------*/

void addStudent (const struct student *const ptr)
{
	struct node *NewStudent= (struct node*)malloc(sizeof(struct node)); // Allocating a new node in the linked list with its size
	struct node *current=head; // Defining a pointer to use it move on the nodes and point to the head of the linked list
	if (NewStudent==NULL) // If the pointer used to allocate the new node equals NULL, it means that memory allocation fails, hence an error message occurs and then return to the main menu
	{
		printf ("-----------------------------\n");
		printf ("There is no enough storage");
		return;
	}
	else // If the pointer used to allocate the new node not equals NULL, it means that memory allocation success
	{
		if (head==NULL) // If the head equals NULL, then the list is empty and hence insert the created node and make it the head of the list
		{
			NewStudent->next=NULL; // Make the next of the created node points to NULL as it will be added to the end of the list
			strcpy (NewStudent->data.name,ptr->name); // Copy the received name from the main program to the name in the created node
			NewStudent->data.id=ptr->id; // Copy the received ID from the main program to the ID in the created node
			NewStudent->data.age=ptr->age; // Copy the received age from the main program to the age in the created node
			NewStudent->data.GPA=ptr->GPA; // Copy the received GPA from the main program to the GPA in the created node
			head=NewStudent; // Make the head points to it
			printf ("The student has been added successfully");
		}
		else if (SearchID(ptr->id) == 1) // Check if the received ID is existing in the list by sending the ID to the function to check it and if the function returns 1, then the ID is already existing and return to the main menu
		{
			printf ("-----------------------------\n");
			printf ("This ID is existed\n");
			return;
		}
		else // If the list is not empty and the ID is free to be added in the list
		{
			NewStudent->next=NULL; // Make the next of the created node points to NULL as it will be added to the end of the list
			strcpy (NewStudent->data.name,ptr->name); // Copy the received name from the main program to the name in the created node
			NewStudent->data.id=ptr->id; // Copy the received ID from the main program to the ID in the created node
			NewStudent->data.age=ptr->age; // Copy the received age from the main program to the age in the created node
			NewStudent->data.GPA=ptr->GPA; // Copy the received GPA from the main program to the GPA in the created node
			while (current->next!=NULL) // Loop to get the last node in the list
			{
				current=current->next; // Move the current to the next node
			}
			current->next=NewStudent; // Make the last node points to the created node
			printf ("-----------------------------\n");
			printf ("The student has been added successfully");
		}
	}
}

/*------------------------------ Check name's validation function ------------------------------*/

int CheckName(char *Name)
{
	int i=0; // Defining a counter for the string's characters
	while (Name[i]!='\0') // While loop to loop on each character
	{
		if ((Name[i] < 'A') || ((Name[i] > 'Z') && (Name[i] < 'a')) || (Name[i] > 'z') ) // If the character is not an alphabet then return 1
		{
			return 1;
		}
		i++; // Move to the next character
	}
	return 0; // If all character are checked and valid return 0
}

/*------------------------------ Search ID function to check if the ID is existed or not to create a new node ------------------------------*/

int SearchID (int ID)
{
	struct node *current=head; // Defining a pointer to use it to move on the nodes and point to the head of the linked list
	while (current!=NULL) // Loop to check each node
	{
		if (ID==(current->data.id)) // Check if the entered ID equals any ID already existed in the list and if found, return 1
		{
			return 1;
		}
		current=current->next; // If not equal, move the current pointer to the next node
	}
	return 0; // If the ID is not existed in any student's infos, return 0 which means that it is free to be added
}

/*------------------------------ Display Student function ------------------------------*/

void displayStudents(void)
{
	struct node *current=head; // Defining a pointer to use it to move on the nodes and point to the head of the linked list
	if (head==NULL) // If the head points to NULL then it means that the list is empty and hence return to the main menu
	{
		printf ("\n-----------------------------\n");
		printf ("The list is empty\n");
		return;
	}
	else // If the head doesn't point to NULL then it means that the list is not empty
	{
		printf ("\n-----------------------------\n");
		while (current != 0) // Loop on each node in the list and print all the details of each student
		{
			printf ("[ ID= %d, Name=%s, Age=%d, GPA=%f ]\n",current->data.id,current->data.name,current->data.age,current->data.GPA);
			current=current->next; // Move the pointer to the next node (student)
		}
		return;
	}
}

/*------------------------------ Search Student By ID function ------------------------------*/

void searchStudentByID(int ID)
{
	struct node *current=head; // Defining a pointer to use it to move on the nodes and point to the head of the linked list
	if (head==NULL) // If the head points to NULL then it means that the list is empty and hence return to the main menu
	{
		printf ("\n-----------------------------\n");
		printf ("The list is empty");
		return;
	}
	else // If the head doesn't point to NULL then it means that the list is not empty
	{
		while (current != NULL) // Loop on each node in the list to find the ID which equals to the received ID
		{
			if (ID == current->data.id) // If the received ID from the user equals the student's ID, the print that the ID is found and the details of the student and return to the menu
			{
				printf ("\n-----------------------------\n");
				printf ("The student is found and here are the details:\n");
				printf ("[ ID= %d, Name=%s, Age=%d, GPA=%f ]\n",current->data.id,current->data.name,current->data.age,current->data.GPA);
				return;
			}
			else // If not equal, move to the next node (student)
			{
				current=current->next;
			}
		}
		printf ("\n-----------------------------\n");
		printf ("The student is not found\n"); // If the function looped on all nodes and doesn't return, the it means that is not found and return to the main menu
		return;
	}
}

/*------------------------------ Update Student By ID function ------------------------------*/

void updateStudentByID(int ID)
{
	struct node *current=head; // Defining a pointer to use it to move on the nodes and point to the head of the linked list
	char name [50]; // Defining a string to receive the required updated name
	int age; // Defining an integer to receive the required updated age
	float GPA; // Defining a float to receive the required updated GPA
	if (head==NULL) // If the head points to NULL then it means that the list is empty and hence return to the main menu
	{
		printf ("\n-----------------------------\n");
		printf ("The list is empty");
		return;
	}
	else // If the head doesn't point to NULL then it means that the list is not empty
	{
		while (current != NULL) // Loop on each node in the list to find the ID which equals to the received ID
		{
			if (ID == current->data.id) // If the ID is found then replace the old data with the updated data
			{
				printf ("-----------------------------\n");
				printf ("The ID is found and here are the details:\n");
				printf ("[ ID= %d, Name=%s, Age=%d, GPA=%f ]\n",current->data.id,current->data.name,current->data.age,current->data.GPA); // The old details of the student
				printf ("Update the new details:\n");
				printf ("Please enter the name: ");
				scanf ("%s",name); // Receive the updated name of the student
				if (CheckName(name)) // Check that the entered name is valid
				{
					printf ("-----------------------------\n");
					printf ("The name is invalid");
					return;
				}
				printf ("Please enter the age: ");
				scanf ("%d",&age); // Receive the updated age of the student
				if (age <= 0) // Check that the entered age is valid
				{
					printf ("The entered age is invalid");
					return;
				}
				printf ("Please enter the GPA: ");
				scanf ("%f",&GPA); // Receive the updated GPA of the student
				if (GPA < 0 || GPA > 3) // Check that the entered GPA is valid
				{
					printf ("The GPA is invalid");
					return;
				}
				strcpy (current->data.name,name); // Overwrite the received name in the name of the node
				current->data.age=age; // Overwrite the received age in the age of the node
				current->data.GPA=GPA; // Overwrite the received GPA in the GPA of the node
				printf ("-----------------------------\n");
				printf ("The updated details are:\n");
				printf ("[ ID= %d, Name=%s, Age=%d, GPA=%f ]\n",current->data.id,current->data.name,current->data.age,current->data.GPA); // Print the updated details
				return; // Return to the main menu
			}
			else // If the ID not equal to the node's ID, move to the next node
			{
				current=current->next;
			}
		}
		printf ("The ID is not found\n");
		return; // If the function looped on all nodes and doesn't return, the it means that is not found and return to the main menu
	}
}

/*------------------------------ Delete Student By ID function ------------------------------*/

void deleteStudentByID(int ID)
{
	struct node* current=head; // Defining a pointer to use it to move on the nodes and point to the head of the linked list
	struct node* delete; // Defining a pointer to use it in deleting the required node without losing any data in the list
	if (head == NULL) // If the head points to NULL then it means that the list is empty and hence return to the main menu
	{
		printf ("\n-----------------------------\n");
		printf ("The list is empty");
		return;
	}
	else if (head->data.id == ID) // Check if the received ID equals to the head's ID
	{
		printf ("\n-----------------------------\n");
		delete=head; // Equating the delete pointer to the head node
		head=head->next; // Moving the head to the next node so not to lose the list
		free(delete); // Deleting the node
		printf ("The student has been deleted successfully"); // Print that the node has been deleted
		return; // Return to main menu
	}
	else // If the required ID not equals to the head's ID the loop on the other nodes
	{
		while (current->next != NULL) // Loop on each node in the list to find the ID which equals to the received ID
		{

			if (current->next->data.id == ID) // If the ID is found in the next node (starting the current from the head of the list)
			{
				printf ("\n-----------------------------\n");
				delete=current->next; // Equating the delete node with the next node
				current->next=current->next->next; // Connecting the two nodes (Before and after the node will be deleted) with each other so not to lose the list's nodes
				free (delete); // Delete the node
				printf ("The student has been deleted successfully");
				return;
			}
			current=current->next; // If the ID is not found in the next node, then move the pointer to the next node
		}
	}
	printf ("\n-----------------------------\n");
	printf ("The ID is not found");
	return; // If the function looped on all nodes and doesn't return, the it means that is not found and return to the main menu
}

/*------------------------------ Calculate Average GPA function ------------------------------*/

float calculateAverageGPA(void)
{
	struct node *current=head; // Defining a pointer to use it to move on the nodes and point to the head of the linked list
	int NumberOfStudents=0; // Define an integer to calculate the number of students
	float Sum=0; // Define a float to calculate the total summation of the GPAs
	if (head == NULL) // If the head points to NULL then it means that the list is empty and hence return to the main menu
	{
		printf ("\n-----------------------------\n");
		printf ("The list is empty");
		return -1; // If the list is empty then return -1
	}
	else // If the head doesn't point to NULL then it means that the list is not empty
	{
		while (current != NULL) // Loop on each node in the list
		{
			Sum=Sum+current->data.GPA; // Add the GPA of each student together
			NumberOfStudents++; // Increasing the number of students by one
			current=current->next; // Move to the next node (student)
		}
	}
	return (Sum/NumberOfStudents); // Return the Average (Total GPAs divided by the number of the students)
}

/*------------------------------ Search Highest GPA function ------------------------------*/

void searchHighestGPA(void)
{
	struct node *current=head; // Defining a pointer to use it to move on the nodes and point to the head of the linked list
	struct node *MaxGPA=current; // Defining a pointer to point to the maximum student's GPA, and make it initially equals to the head (first node) so it has the maximum GPA
	if (head == NULL) // If the head points to NULL then it means that the list is empty and hence return to the main menu
	{
		printf ("\n-----------------------------\n");
		printf ("The list is empty");
		return;
	}
	else // If the head doesn't point to NULL then it means that the list is not empty
	{
		while (current!=NULL) // Loop on each node in the list
		{
			if (current->data.GPA > MaxGPA->data.GPA) // If any node's GPA greater than the last updated MaxGPA's value
			{
				MaxGPA=current; // Make the MaxGPA pointer point to this node
			}
			current=current->next; // Move to the next node (student)
		}
	}
	printf ("\n-----------------------------\n");
	printf ("The details of the student that has the highest GPA:\n");
	printf ("[ ID= %d, Name=%s, Age=%d, GPA=%f ]\n",MaxGPA->data.id,MaxGPA->data.name,MaxGPA->data.age,MaxGPA->data.GPA); // Print the details of the MaxGPA that has the maximum GPA
	return; // Return to the main menu
}
