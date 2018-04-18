/* Yixiong Ding, <yixiongd@student.unimelb.edu.au>
 * 12 September, 2016
 * The University of Melbourne */

#ifndef _BST_H_
#define _BST_H_

#define DATAMAX 1465 /* Maximum length of data that can be stored */
#define NAMEMAX 64 /* Maximum length of name that can be stored */

/* Structures, arrays and variables for storing data */
typedef char Name_t[NAMEMAX+1];
typedef char Data_t[DATAMAX+1];

typedef struct Node {
  Name_t Name;
  Data_t Data;	
  struct Node *Left;

  /* A linked list for storing "duplicates", used in Stage 2 only */
  struct Node *Mid;
  struct Node *Right;
}Node_t;

/* Read the input file, and construct the bianry search tree */
Node_t *Read_Input_File(Node_t *root, char *input_file);

/* Insert a node with "name" and "data" into the binary search tree */
Node_t *Insert_Node(Node_t *root, char *name, char *data);

/* Create a new node with "name" and "data" */
Node_t *Create_New_Node(char *name, char *data);

/* Search the binary search tree with "key", and write the found data into the output file */
Node_t *Search_Node(Node_t *root, char *key, int *comparisons, int *found, FILE *file);

/* Traverse the linked list "Mid" in the binary search tree, used in Stage 2 only */
Node_t *Traverse_Mid(Node_t *root);

/* Read the key file, search key nodes and write the output file */
void Write_Output_File(Node_t *root, char *output_file);

/* Free all memory used by the binary search tree "root" */
void Free_Node(Node_t *root);

#endif
