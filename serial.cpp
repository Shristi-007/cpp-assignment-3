#include <bits/stdc++.h>
#include <fstream>
using namespace std;
struct Node
{
    char val[500];
    struct Node *left;
    struct Node *right;
};

/* Helper function that allocates a new Node with the
given key and NULL left and right pointers. */
Node *newNode(char p[101])
{
    Node *temp = new Node;
    strcpy(temp->val, p);
    temp->left = NULL;
    temp->right = NULL;
    return (temp);
}

void serialize(Node *root, FILE *fp)
{
    if (root == NULL)
    {
        std::string str("Null,Null");
        fprintf(fp, "(%s) ", str.c_str());
        return;
    }
    std::string str1(root->val);
    fprintf(fp, "(%s) ", str1.c_str());
    serialize(root->left, fp);
    serialize(root->right, fp);
}

void deserialize(Node *&root, FILE *fp)
{

    char value[101];
    if ((!fscanf(fp, "%s ", value) || strcmp(value, "(Null,Null)") == 0))
        return;
    // cout << value << " ";
    root = newNode(value);
    // cout << "hello";
    deserialize(root->left, fp);
    deserialize(root->right, fp);
}

// A simple inorder traversal used for testing the constructed tree
void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        printf("%s ", root->val);
        inorder(root->right);
    }
}

/* Driver program to test above functions*/
int main()
{
    char arr[7][101];
    char lat[101], lon[50], s[100];
    for (int i = 0; i < 7; i++)
    {
        cout << "Enter the latitude and the longitude: ";
        cin >> lat >> lon;
        strcat(lat, ",");
        strcat(lat, lon);
        // cout << s << "\n";
        strcpy(arr[i], lat);
        // cout << arr[i] << "\n";
    }
    // This is a demo tree consisting of 7 nodes
    struct Node *root = newNode(arr[0]);
    root->left = newNode(arr[1]);
    root->right = newNode(arr[2]);
    root->left->left = newNode(arr[3]);
    root->left->right = newNode(arr[4]);
    root->left->right->left = newNode(arr[5]);
    root->left->right->right = newNode(arr[6]);

    // Let us open a file and serialize the tree into the file
    FILE *fp = fopen("tree.txt", "w");
    if (fp == NULL)
    {
        puts("Could not open file");
        return 0;
    }
    serialize(root, fp);
    fclose(fp);

    // Let us deserialize the stored tree into root1
    Node *root1 = NULL;
    fp = fopen("tree.txt", "r");
    deserialize(root1, fp);

    printf("Inorder Traversal of the tree constructed from file:\n");
    inorder(root1);

    return 0;
}
