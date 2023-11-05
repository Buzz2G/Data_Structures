#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

//Initialize the Nodes
struct TreeNode
{
    std::string data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& val) : data(val), left(nullptr), right(nullptr) {}//initialize member variables
};


// Inserting nodes in the BST
TreeNode* insert(TreeNode* root, const std::string& data)
{
    if (!root)//If root(tree) is empty
    {
        return new TreeNode(data);//New a node and return as root
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else
    {
        root->right = insert(root->right, data);
    }

    return root;
}

// Search nodes in BST and store the path in the vector
std::vector<TreeNode> search(TreeNode* root, const std::string& data)
{
    std::vector<TreeNode> path;

    while (root)
    {
        path.push_back(*root);  // Add the node in path

        if (data == root->data)
        {
            // Find the matched node and return the path
            return path;
        }
        else if (data < root->data)
        {
            // If the data is smaller,continue in the left subtree
            root = root->left;
        }
        else
        {
            // If the data is bigger,continue in the right subtree
            root = root->right;
        }
    }

    // If don't find the matched node, return empty path;
    return std::vector<TreeNode>();
}

int main()
{
    //Initialize variables
    TreeNode* root = nullptr;//Root of BST

    std::string name01;//Line 1: 1st person's name
    std::string name02;//Line 2: 2nd person's name
    int treeNum;//Line 3: The number of the total people
    std::string longString;//Line 4~Line (3+N): Name of each person

    // Use loop to read input
    std::string line;
    int i = 1;
    while (std::getline(std::cin, line))
    {
        if (i == 1)//Read line1
        {
            name01 = line;
        }
        else if (i == 2)//Read line2
        {
            name02 = line;
        }
        else if (i == 3)//Read line3
        {
            treeNum = std::stoi(line);//Data Type Conversions
        }
        else
        {
            root = insert(root, line);//Insert the data
        }
        i++;

    }

    // Search the names and store the path in vector
    std::vector<TreeNode> path01 = search(root, name01);
    std::vector<TreeNode> path02 = search(root, name02);

    //Traverse the two paths and print the same ancestors
    for (const TreeNode& node1 : path01)
    {
        for (const TreeNode& node2 : path02)
        {
            if (node1.data == node2.data)
            {
                std::cout << node1.data << std::endl;
            }
        }
    }

    return 0;
}
