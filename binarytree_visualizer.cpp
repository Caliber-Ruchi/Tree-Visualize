#include <graphics.h>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class TreeNode {
public:
    TreeNode* left;
    TreeNode* right;
    int data;

    TreeNode(int x){
        this->data = x;
        this->left = nullptr;
        this->right = nullptr;
    }
    ~TreeNode() {
        delete left;
        delete right;
    }
};

// Function to perform Inorder traversal
void Inorder(TreeNode* root) {
    if (!root) return;
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}

// Function to perform Preorder traversal
void Preorder(TreeNode* root) {
    if (!root) return;
    cout << root->data << " ";
    Preorder(root->left);
    Preorder(root->right);
}

// Function to perform Postorder traversal
void Postorder(TreeNode* root) {
    if (!root) return;
    Postorder(root->left);
    Postorder(root->right);
    cout << root->data << " ";
}

// Function to print tree using graphics.h
void printTree(int x, int y, TreeNode* root, int index) {
    if (!root) return;

    // Convert int value into string
    string str = to_string(root->data);

    // Set color of the boundary of circle as green
    setcolor(RED);

    // Draw the circle of radius 15 that represent node of Tree
    circle(x, y, 15);
    delay(200);
    floodfill(x, y, RED);
    delay(200);

    // Print the values of the node in the circle
    outtextxy(x - 2, y - 3, const_cast<char*>(str.c_str()));
    delay(200);

    // Set the color of the line from parent to child as green
    setcolor(RED);

    // Evaluating left and right child
    int lx = 2 * index + 1;
    int ry = 2 * index + 2;

    // Recursively draw the left subtree and the right subtree
    printTree(x - y / (index + 1), y + 50, root->left, lx);
    printTree(x + y / (index + 1), y + 50, root->right, ry);

    // Draw the line (or link) when the node is not the leaf node
    if (root->left) {
        delay(200);
        line(x, y + 14, x - y / (index + 1), y + 50 - 14);
    }
    if (root->right) {
        delay(200);
        line(x, y + 14, x + y / (index + 1), y + 50 - 14);
    }
}

int main() {
    int gd = DETECT, gm, x, lc, rc, choice;
    TreeNode* root = nullptr;
    queue<TreeNode*> q;

    initgraph(&gd, &gm,nullptr);
    cleardevice();

    cout << "NOTE: For tree input take -1 as NULL\n\n";
    cout << "Enter root node data: ";
    cin >> x;
    root = new TreeNode(x);
    q.push(root);

    while (!q.empty()) {
        TreeNode* temp = q.front();
        q.pop();

        cout << "Enter left child of " << temp->data << ": ";
        cin >> lc;
        if (lc != -1) {
            temp->left = new TreeNode(lc);
            q.push(temp->left);
        }

        cout << "Enter right child of " << temp->data << ": ";
        cin >> rc;
        if (rc != -1) {
            temp->right = new TreeNode(rc);
            q.push(temp->right);
        }
    }

    bool running = true;
    while (running) {
        cout << "1. In-order Traversal\n2. Pre-order Traversal\n3. Post-order traversal\n4. Visualize Tree\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "In-order Traversal: ";
                Inorder(root);
                cout << endl;
                break;
            case 2:
                cout << "Pre-order Traversal: ";
                Preorder(root);
                cout << endl;
                break;
            case 3:
                cout << "Post-order Traversal: ";
                Postorder(root);
                cout << endl;
                break;
            case 4:
                cleardevice();
                printTree(300, 100, root, 0);
                getch();
                cleardevice();
                break;
            case 5:
                running = false;
                break;
            default:
                cout << "Invalid choice! Try again!\n";
        }
        cout << endl;
    }

    getch();
    closegraph();
    delete root;
    return 0;
}

