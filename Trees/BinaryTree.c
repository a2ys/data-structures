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

TreeNode* deleteNode(TreeNode* root, int key) {
  if (root == NULL) return NULL;

  if (root->left == NULL && root->right == NULL) {
    if (root->data == key) {
      free(root);
      return NULL;
    }
    return root;
  }

  TreeNode* keyNode = NULL;
  TreeNode* temp;
  TreeNode* last;

  TreeNode* queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;

  while (front < rear) {
    temp = queue[front++];

    if (temp->data == key) {
      keyNode = temp;
    }

    if (temp->left) {
      queue[rear++] = temp->left;
      last = temp;
    }

    if (temp->right) {
      queue[rear++] = temp->right;
      last = temp;
    }
  }

  if (keyNode) {
    keyNode->data = temp->data;

    if (last->right == temp) {
      last->right = NULL;
    } else {
      last->left = NULL;
    }

    free(temp);
  }

  return root;
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
  TreeNode* root = NULL;
  root = insert(root, 1);
  root = insert(root, 2);
  root = insert(root, 3);
  root = insert(root, 4);
  root = insert(root, 5);
  root = insert(root, 6);
  root = insert(root, 7);
  
  inOrder(root);
  printf("\n");

  BFS(root);
  printf("\n");

  return 0;
}

