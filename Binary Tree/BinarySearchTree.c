#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
  int data;
  struct TreeNode* left;
  struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
  TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
  
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

int search(TreeNode* root, int value) {
  if (root == NULL) return 0;
  if (root->data == value) return 1;
  if (root->data < value) return search(root->right, value);
  if (root->data > value) return search(root->left, value);

  return 0;
}

TreeNode* findMin(TreeNode* node) {
  while (node->left != NULL) node = node->left;
  
  return node;
}

TreeNode* findMax(TreeNode* node) {
  while (node->right != NULL) node = node->right;

  return node;
}

TreeNode* insert(TreeNode* root, int value) {
  if (root == NULL) return createNode(value);

  if (value < root->data) {
    root->left = insert(root->left, value);
  }

  if (value > root->data) {
    root->right = insert(root->right, value);
  }

  return root;
}

TreeNode* delete(TreeNode* root, int value) {
  if (root == NULL) return root;

  if (value < root->data) {
    root->left = delete(root->left, value);
  } else if (value > root->data) {
    root->right = delete(root->right, value);
  } else {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    }

    if (root->left == NULL) {
      TreeNode* temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      TreeNode* temp = root->left;
      free(root);
      return temp;
    }

    TreeNode* temp = findMin(root->right);
    root->data = temp->data;
    root->right = delete(root->right, temp->data);
  }

  return root;
}

void inOrder(TreeNode* root) {
  if (root) {
    inOrder(root->left);
    printf("%d", root->data);
    inOrder(root->right);
  }
}

void preOrder(TreeNode* root) {
  if (root) {
    printf("%d", root->data);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void postOrder(TreeNode* root) {
  if (root) {
    postOrder(root->left);
    postOrder(root->right);
    printf("%d", root->data);
  }
}

void levelOrderTraversal(TreeNode* root) {
  if (root == NULL) return;

  TreeNode* queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;
  
  while (front < rear) {
    TreeNode* node = queue[front++];
    printf("%d", node->data);
    if (node->left) {
      queue[rear++] = node->left;
    }
    if (node->right) {
      queue[rear++] = node->right;
    }
  }
}

int main()
{
  TreeNode* root = NULL;
  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 20);
  root = insert(root, 40);
  root = insert(root, 70);
  root = insert(root, 60);
  root = insert(root, 80);

  printf("InOrder traversal before deletion: ");
  inOrder(root);
  printf("\n");

  root = delete(root, 20);
  printf("InOrder traversal after deleting 20: ");
  inOrder(root);
  printf("\n");

  root = delete(root, 30);
  printf("InOrder traversal after deleting 30: ");
  inOrder(root);
  printf("\n");

  root = delete(root, 50);
  printf("InOrder traversal after deleting 50: ");
  inOrder(root);
  printf("\n");

  return 0;
}

