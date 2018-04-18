/* Yixiong Ding, <yixiongd@student.unimelb.edu.au>
 * 12 September, 2016
 * The University of Melbourne */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

int
main(int argc, char *argv[]) {

  /* Create an empty tree*/
  Node_t *root = NULL;

  /* Read the input file, and construct the bianry search tree */
  root = Read_Input_File(root, argv[1]);

  /* Read the key file, search key nodes and write the output file */
  Write_Output_File(root, argv[2]);

  /* Free all memory used by the binary search tree "root" */
  Free_Node(root);

  return 0;
}
