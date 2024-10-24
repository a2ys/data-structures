#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
  int data;
  struct TreeNode* left;
  struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
  TreeNode* newNode = (TreeNode *) malloc(sizeof(TreeNode));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

TreeNode* insert(TreeNode* root, int data) {
  if (root == NULL) return createNode(data);
  
  TreeNode* queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;

  while (front < rear) {
    TreeNode* temp = queue[front++];

    if (temp->left == NULL) {
      temp->left = createNode(data);
      break;
    } else {
      queue[rear++] = temp->left;
    }

    if (temp->right == NULL) {
      temp->right = createNode(data);
      break;
    } else {
      queue[rear++] = temp->right;
    }
  }

  return root;
}

int searchDFS(TreeNode* root, int value) {
  if (root == NULL) return 0;

  if (root->data == value) return 1;

  int leftResult = searchDFS(root->left, value);
  int rightResult = searchDFS(root->right, value);

  return leftResult || rightResult;
}

void inOrder(TreeNode* root) {
  if (root) {
      inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
  }
}

void preOrder(TreeNode* root) {
  if (root) {
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void postOrder(TreeNode* root) {
  if (root) {
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
  }
}

void BFS(TreeNode* root) {
  if (root == NULL) return;

  TreeNode* queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;

  while (front < rear) {
    TreeNode* node = queue[front++];
    printf("%d ", node->data);
    if (node->left) {
      queue[rear++] = node->left;
    }
    if (node->right) {
      queue[rear++] = node->right;
    }
  }
}

int main() {
  TreeNode* root = createNode(1);
  TreeNode* n1 = createNode(2);
  TreeNode* n2 = createNode(3);
  TreeNode* n3 = createNode(4);
  TreeNode* n5 = createNode(6);
  TreeNode* n6 = createNode(7);

  root->left = n1;
  root->right = n2;
  n1->left = n3;
  n2->left = n5;
  n2->right = n6;

  root = insert(root, 5);
  
  // inOrder(root);

  BFS(root);

  return 0;
}

