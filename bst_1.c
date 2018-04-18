/* COMP20003 Assignment 1, September 2016.
   Yixiong Ding, 671499 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

/* Read the input file, and construct the bianry search tree */
Node_t *Read_Input_File(Node_t *root, char *input_file) {

	FILE *file = NULL;
  	file = fopen(input_file, "r");
	char temp[DATAMAX+1];
	char *read_temp = NULL, *file_temp = NULL, *name = NULL, *data = NULL;

	if (file == NULL) {
    	printf("Error Reading File!\n");
		exit(EXIT_FAILURE);
	}

	/* Read the input file and store into the binary search tree */
	while ((file_temp = fgets(temp, DATAMAX+1, file)) != NULL) {

		/* Use "strtok" intercept the string beyond "," */
		read_temp = strtok(file_temp, ",");
		while (read_temp != NULL) {
			name = read_temp;
			read_temp = strtok(NULL, ",");
			data = read_temp;
			read_temp = strtok(NULL, ",");
      		if (name != NULL && data != NULL) {
        		root = Insert_Node(root, name, data);
      		}
		}
	}
	fclose(file);

	return root;
}

/* Create a new node with "name" and "data" */
Node_t *Create_New_Node(char *name, char *data) {

	/* Allocate memory for the new node */
	Node_t *NewNode = (Node_t *)malloc(sizeof(Node_t));

	/* Use "strcpy" to copy a string from one variable to another */
	strcpy(NewNode->Name, name);
	strcpy(NewNode->Data, data);
	NewNode->Left = NewNode->Right = NULL;

	return NewNode;
}

/* Insert a node with "name" and "data" into the binary search tree */
Node_t *Insert_Node(Node_t *root, char *name, char *data) {

	if(root == NULL) { 
		root = Create_New_Node(name, data);
	}

	/* Use "strcmp" to compare if two strings are the same or not */
	else if(strcmp(name, root->Name)<=0) {
		root->Left = Insert_Node(root->Left, name, data);
	} else {
		root->Right = Insert_Node(root->Right, name, data);
	}

	return root;
}

/* Search the binary search tree with "key", and write the found data into the output file */
Node_t *Search_Node(Node_t *root, char *key, int *comparisons, int *found, FILE *file) {

	/* Every run the search function will make comparision numbers plus one */
	(*comparisons)++;

	/* If can't find the key, create and return a new node with name key and data "NOTFOUND" */
	if(root == NULL) {
    	return Create_New_Node(key, "NOTFOUND");
	}

	/* If the key is found, the flag is true and write the node into the output file */
	else if(strcmp(key, root->Name) == 0) {
    	(*found)++;
    	fprintf(file, "%s -- > %s\n", root->Name, root->Data);
    	return Search_Node(root->Left, key, comparisons, found, file);
	}

	/* Keep search the binary search tree till reach a leaf */
	else if(strcmp(key, root->Name) < 0) {
		return Search_Node(root->Left, key, comparisons, found, file);
	} else {
		return Search_Node(root->Right, key, comparisons, found, file);
	}
}

/* Read the key file, search key nodes and write the output file */
void Write_Output_File(Node_t *root, char *output_file) {

	FILE *file = NULL;
  	file = fopen(output_file, "w");
  	char key[NAMEMAX+1];
  	int comparisons = 0;
  	int found = 0;
  	Node_t *Node ;

	if (file == NULL) {
    	printf("Error Writing File!\n");
    	exit(EXIT_FAILURE);
	}

	/* Use "fgets" and "strtok" to get the keys from stdin */
 	while (fgets(key, NAMEMAX+5, stdin) != NULL) {
  		comparisons = 0;
    	found = 0;
		Node = Search_Node(root, strtok(key, "\n"), &comparisons, &found, file);

		/* If can't find the key node, print the new node into file and free this new node */
    	if (!found) {
      		fprintf(file, "%s -- > %s\n\n", Node->Name, Node->Data);
      		free(Node);
    	}
  		printf("%s -- > %d\n", Node->Name, comparisons);
	}
	fclose(file);
	Free_Node(Node);
}

/* Free all memory used by the binary search tree "root" */
void Free_Node(Node_t *root) {

	if(root != NULL) {
    	Free_Node(root->Left);
    	Free_Node(root->Right);
    	free(root);
  	}
}
