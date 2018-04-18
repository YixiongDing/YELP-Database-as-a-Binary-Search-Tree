/* Yixiong Ding, <yixiongd@student.unimelb.edu.au>
 * 12 September, 2016
 * The University of Melbourne */

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
	NewNode->Left = NewNode->Right = NewNode->Mid = NULL;

	return NewNode;
}

/* Traverse the linked list "Mid" in the binary search tree, used in Stage 2 only */
Node_t *Traverse_Mid(Node_t *root) {

	if (root->Mid == NULL) {
    	return root;
  	} else {
    	return Traverse_Mid(root->Mid);
  	}
}

/* Insert a node with "name" and "data" into the binary search tree */

Node_t *Insert_Node(Node_t *root, char *name, char *data) {

	if(root == NULL) {
		root = Create_New_Node(name, data);
	}

	/* Use "strcmp" to compare if two strings are the same or not */
	else if(strcmp(name, root->Name) == 0) {

	/* If names are the same we put the node into the linked list Mid */
		Node_t *Node = Traverse_Mid(root);
    	Node->Mid = Create_New_Node(name, data);
	} else if(strcmp(name, root->Name) < 0) {
    	root->Left = Insert_Node(root->Left, name, data);
  	} else {
		root->Right = Insert_Node(root->Right, name, data);
	}
	return root;
}

/* Search the binary search tree with "key", and write the found data into the output file */
Node_t *Search_Node(Node_t *root, char *key, int *comparisons, int *found, FILE *file) {

	if(root == NULL) {
    	return Create_New_Node(key, "NOTFOUND");
	} else if(strcmp(key, root->Name) == 0) {

		/* The difference between Stage 1 and Stage 2, only valid comparision makes comparision numbers plus one */
		(*comparisons)++;

		/* If the key is found, the flag is true and write the node into the output file */
    	(*found)++;
    	Node_t *Node = root->Mid;
    	fprintf(file, "%s -- > %s\n", root->Name, root->Data);
    	while (Node != NULL) {
    		fprintf(file, "%s -- > %s\n",  Node->Name, Node->Data);
    		Node = Node->Mid;
    	}
    	return root;
	} else if(strcmp(key, root->Name) < 0) {
		(*comparisons)++;
		return Search_Node(root->Left, key, comparisons, found, file);
	} else {
		(*comparisons)++;
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
  	Node_t *Node;

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
}

/* Free all memory used by the binary search tree "root" */
void Free_Node(Node_t *root) {
	
	if(root != NULL) {
    	Free_Node(root->Left);
    	Free_Node(root->Mid);
    	Free_Node(root->Right);
    	free(root);
  	}
}
