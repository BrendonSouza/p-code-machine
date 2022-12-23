#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 12

typedef struct Node {
  int value;
  struct Node* children[MAX_CHILDREN];
} Node;

Node* createNode(int value) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->value = value;
  for (int i = 0; i < MAX_CHILDREN; i++) {
    newNode->children[i] = NULL;
  }
  return newNode;
}

void insertNode(Node* root, int value) {
  if (root->value == value) {
    printf("Node with value %d already exists in tree\n", value);
    return;
  }

  for (int i = 0; i < MAX_CHILDREN; i++) {
    if (root->children[i] == NULL) {
      root->children[i] = createNode(value);
      printf("Inserted node with value %d\n", value);
      return;
    } else if (root->children[i]->value == value) {
      printf("Node with value %d already exists in tree\n", value);
      return;
    }
  }

  printf("No more space to insert node with value %d\n", value);
}

//depth first search
void dfs(Node* root) {
  if (root == NULL) {
    return;
  }

  printf("%d ", root->value);

  for (int i = 0; i < MAX_CHILDREN; i++) {
    dfs(root->children[i]);
  }
}

int main() {
  Node* root = createNode(0);

  insertNode(root, 1);
  insertNode(root, 2);
  insertNode(root, 3);
  insertNode(root, 4);
  insertNode(root, 5);
  insertNode(root, 5);
  insertNode(root, 6);
  //insert children to node 1
    insertNode(root->children[0], 7);
    insertNode(root->children[0], 8);

    dfs(root);
  

  return 0;
}