#include <stdio.h>
#include <stdlib.h>
#define flush_buffer while(getchar()!='\n');
// Define a structure for a linked list node
typedef struct Node
{
    int data;           // Data of the node
    struct Node *next;  // Pointer to the next node
} Node;

// Function to create a new node with given data
Node *newNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node)); // Dynamically allocate memory for a new node
    node->data = data; // Set the data of the node
    node->next = NULL; // Initialize the next pointer to NULL
    return node;
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(Node **head, int new_data)
{
    Node *new_node = newNode(new_data); // Create a new node
    new_node->next = *head; // Link the new node to the current head
    *head = new_node; // Update the head to the new node
}

// Function to insert a new node at the end of the list
void insertAtEnd(Node **head, int new_data)
{
    Node *new_node = newNode(new_data); // Create a new node
    if (*head == NULL) // If the list is empty, make new node the head
    {
        *head = new_node;
    }
    else
    {
        Node *last = *head; // Find the last node
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = new_node; // Link the last node to the new node
    }
}

// Function to insert a new node at a specified position
void insertAtPosition(Node **head, int new_data, int position)
{
    // Check for invalid position
    if (position < 1)
    {
        printf("Invalid position\n");
        return;
    }
    // If inserting at the beginning, use existing function
    if (position == 1)
    {
        insertAtBeginning(head, new_data);
        return;
    }
    Node *new_node = newNode(new_data); // Create a new node
    Node *temp = *head; // Start at the head
    // Traverse the list to find the position
    for (int i = 1; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }
    // Check if position is beyond list length
    if (temp == NULL)
    {
        printf("Position exceeds list length\n");
    }
    else
    {
        new_node->next = temp->next; // Link the new node to the next node
        temp->next = new_node; // Link the current node to the new node
    }
}

// Function to delete the first node of the list
void deleteFromBeginning(Node **head)
{
    // Check if the list is empty
    if (*head == NULL)
    {
        printf("List is empty, nothing to delete\n");
    }
    else
    {
        Node *temp = *head; // Store the current head
        *head = (*head)->next; // Update the head to the next node
        free(temp); // Free the old head node
    }
}

// Function to delete the last node of the list
void deleteFromEnd(Node **head)
{
    // Check if the list is empty
    if (*head == NULL)
    {
        printf("List is empty, nothing to delete\n");
    }
    else if ((*head)->next == NULL) // If only one node
    {
        free(*head); // Free the node
        *head = NULL; // Update head to NULL
    }
    else
    {
        Node *second_last = *head; // Start at the head
        // Traverse to find the second last node
        while (second_last->next->next != NULL)
        {
            second_last = second_last->next;
        }
        free(second_last->next); // Free the last node
        second_last->next = NULL; // Update second last node's next to NULL
    }
}

// Function to delete a node from a specified position
void deleteFromPosition(Node **head, int position)
{
    // Check if the list is empty
    if (*head == NULL)
    {
        printf("List is empty, nothing to delete\n");
        return;
    }
    // Check for invalid position
    if (position < 1)
    {
        printf("Invalid position\n");
        return;
    }
    Node *temp = *head; // Start at the head
    // If deleting the first node, use existing function
    if (position == 1)
    {
        *head = temp->next; // Update head to the next node
        free(temp); // Free the old head node
        return;
    }
    // Traverse to find the node before the one to delete
    for (int i = 1; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }
    // Check if position is beyond list length
    if (temp == NULL || temp->next == NULL)
    {
        printf("Position exceeds list length\n");
    }
    else
    {
        Node *next = temp->next->next; // Store the node after the one to delete
        free(temp->next); // Free the node to delete
        temp->next = next; // Link the current node to the node after the one deleted
    }
}

// Function to display the elements of the list
void displayList(Node *n)
{
    // Check if the list is empty
    if (n == NULL)
    {
        printf("List is empty\n");
        return;
    }
    // Traverse and print each node's data
    while (n != NULL)
    {
        printf("%d ", n->data);
        n = n->next;
    }
    printf("\n");
}

// Function to search for all occurrences of an element and store their positions
int searchElement(Node* head, int key, int positions[], int maxPositions) {
    int count = 0; // Initialize count of occurrences
    int position = 1; // Initialize position
    Node* current = head; // Start at the head
    // Traverse the list
    while (current != NULL) {
        if (current->data == key) {
            if (count < maxPositions) {
                positions[count++] = position; // Store position of occurrence
            } else {
                break; // Avoid exceeding the array size
            }
        }
        current = current->next; // Move to next node
        position++;
    }
    return count; // Return the count of occurrences
}

// Function to get the length of the list
int getLength(Node *head)
{
    int length = 0; // Initialize length
    Node *current = head; // Start at the head
    // Traverse the list to count nodes
    while (current != NULL)
    {
        length++;
        current = current->next;
    }
    return length; // Return the length
}

// Function to reverse the list
void reverseList(Node **head)
{
    Node *prev = NULL, *current = *head, *next = NULL; // Initialize pointers
    // Traverse the list
    while (current != NULL)
    {
        next = current->next; // Store the next node
        current->next = prev; // Reverse the link
        prev = current; // Move prev to current
        current = next; // Move current to next
    }
    *head = prev; // Update head to new front
}

// Function to sort the list using insertion sort
void sortList(Node **head) {
    if (*head == NULL || (*head)->next == NULL)
        return; // List is already sorted if it has 0 or 1 node

    Node *sorted = NULL; // Initialize a new list to store the sorted elements

    Node *current = *head; // Start with the first node in the original list
    while (current != NULL) {
        Node *next = current->next; // Store the next node to process

        // Find the correct position to insert the current node in the sorted list
        if (sorted == NULL || sorted->data >= current->data) {
            // Insert at the beginning of the sorted list
            current->next = sorted;
            sorted = current;
        } else {
            // Traverse the sorted list to find the insertion point
            Node *temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            // Insert the current node
            current->next = temp->next;
            temp->next = current;
        }

        current = next; // Move to the next node in the original list
    }

    *head = sorted; // Update the head to point to the new sorted list
}



int main(void) {
    Node *head = NULL;  // Initialize the head of the list as NULL
    int choice, value, position, length;

    // Prompt user to enter initial list length and populate the list
    printf("\nWelcome to the Linked List :) \n");
    printf("\nEnter the length of the linked list you want to start with: ");
    int r=scanf("%d", &length);
    flush_buffer;
    while(r!=1){
        printf("Wrong input should be integer.Enter length of list: ");
         r=scanf("%d", &length);  
        flush_buffer;
        }
    
 printf("Enter value to insert: ");
    while (length--) {
       
        int r=scanf("%d", &value);
        flush_buffer;
        while(r!=1){
        printf("Wrong input should be integer.Enter value to insert: ");
         r=scanf("%d", &value);  
        flush_buffer;
        }
        
        insertAtEnd(&head, value);
    }

    // Infinite loop for the menu-driven interface
    while (1) {
        // Display menu options
        printf("\nLinked List Operations:\n");
        printf("1. Insert at beginning\n2. Insert at end\n3. Insert at position\n");
        printf("4. Delete from beginning\n5. Delete from end\n6. Delete from position\n");
        printf("7. Display list\n8. Search element\n9. Get length\n");
        printf("10. Reverse list\n11. Sort list\n12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        flush_buffer;

        // Switch case to handle different operations based on user choice
        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            flush_buffer;
            insertAtBeginning(&head, value);
            break;
        case 2:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            flush_buffer;
            insertAtEnd(&head, value);
            break;
        case 3:
            printf("Enter value to insert and position: ");
            scanf("%d %d", &value, &position);
            flush_buffer;
            insertAtPosition(&head, value, position);
            break;
        case 4:
            deleteFromBeginning(&head);
            break;
        case 5:
            deleteFromEnd(&head);
            break;
        case 6:
            printf("Enter position to delete: ");
            scanf("%d", &position);
            flush_buffer;
            deleteFromPosition(&head, position);
            break;
        case 7:
            displayList(head);
            break;
        case 8:{ // Use a block to avoid redeclaration error
            printf("Enter element to search for: ");
            scanf("%d", &value);
            flush_buffer;
            int positions[100]; // Array to store positions
            int numberOfOccurrences = searchElement(head, value, positions, 100);

            if (numberOfOccurrences == 0) {
                printf("Element not found\n");
            } else {
                printf("Element found at position(s): ");
                for (int i = 0; i < numberOfOccurrences; i++) {
                    printf("%d ", positions[i]);
                }
                printf("\n");
            }
            break;
        }
        case 9:
            printf("Length of list: %d\n", getLength(head));
            break;
        case 10:
            reverseList(&head);
            displayList(head);
            break;
        case 11:
            sortList(&head);
            displayList(head);
            break;
        case 12:
            // Free all nodes before exiting
            while (head != NULL) {
                deleteFromBeginning(&head);
            }
            printf("Exiting program\n");
            return 0;
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
