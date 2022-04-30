#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////start tree code
//tree code reference : form Canvas by proffessor George Okeyo

struct TreeNode
{
    int frequency;
    string data;
    TreeNode *left, *right;
    TreeNode()
    {
        left = NULL;
        right = NULL;
        data = "000";
        frequency = 0;
    }
    TreeNode(string value, int value2)
    {
        data = value;
        frequency = value2;
        left = NULL;
        right = NULL;
    }
    void setLeft(TreeNode *left) { this->left = left; }
    void setRight(TreeNode *right) { this->right = right; }
    TreeNode *getLeft() { return left; }
    TreeNode *getRight() { return right; }
    bool hasLeft() { return left != NULL; }
    bool hasRight() { return right != NULL; }
    void setData(string data) { this->data = data; }
    string getData() { return data; }
    int getFreq() { return frequency; }
};

class BinaryTree
{
private:
    TreeNode *root;
    TreeNode *insert(TreeNode *root, TreeNode *newNode);
    TreeNode *find(string data, TreeNode *root);

public:
    int height = 0;
    int sumProbes = 0;
    int countWords = 0;
    string outString = "";
    BinaryTree();
    BinaryTree(TreeNode *root);
    void setRoot(TreeNode *root) { this->root = root; }
    TreeNode *getRoot() { return root; }

    int size(TreeNode *);
    TreeNode *find(string data);
    //   TreeNode* update(string data);
    void deleteTree(TreeNode *root);
    void preorderTraversal(TreeNode *);
    void postorderTraversal(TreeNode *);
    void inorderTraversal(TreeNode *);
    void MaxAvinorderTraversal(TreeNode *);
    void insert(string data, int freq);
    int getLevelUtil(TreeNode *node, string data, int level);
    int getLevel(TreeNode *node, string data);
};

BinaryTree::BinaryTree()
{
    root = NULL;
}

BinaryTree::BinaryTree(TreeNode *root)
{
    this->root = root;
}

int BinaryTree::size(TreeNode *root)
{
    if (root == NULL)
        return 0; //empty tree
    else
    {
        int counter = 1;
        //recursively process left and right
        counter += size(root->getLeft());  //add size from left subtree
        counter += size(root->getRight()); //also the right
        return counter;
    }
}

void BinaryTree::insert(string data, int freq)
{
    if (data == " " || data == "  " || data == "")
    {
        // cout<<"ppppp";
    }
    else
    {
        TreeNode *temp = root;
        TreeNode *newNode = new TreeNode;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->data = data;
        newNode->frequency = freq;
        //insert to temp and keep result in root
        root = insert(temp, newNode);
    }
}

/*
This member function implements insertion based on binary search tree principles
*/
TreeNode *BinaryTree::insert(TreeNode *root, TreeNode *newNode)
{
    if (root == NULL)
        root = newNode;
    else if (root->data > newNode->data)
    {
        insert(root->left, newNode);
        if (root->left == NULL)
            root->left = newNode;
    }
    else
    {
        insert(root->right, newNode);
        if (root->right == NULL)
            root->right = newNode;
    }
    return root;
}

TreeNode *BinaryTree::find(string data, TreeNode *root)
{
    //check case where root is null or data is present in root
    if (root == NULL || root->getData() == data)
        return root;
    /*Inelegant solution---think of Binary Search Tree strategy*/
    //search left
    bool found = false;
    TreeNode *foundItem = find(data, root->getLeft());
    if (foundItem != NULL)
    {
        found = true;
    }
    if (!found)
    {
        //search right
        foundItem = find(data, root->getRight()); //will only be reached if item is  not left
    }
    return foundItem;
}

TreeNode *BinaryTree::find(string data)
{
    TreeNode *temp = root;
    TreeNode *foundNode = find(data, temp);
    return foundNode;
}
void BinaryTree::deleteTree(TreeNode *root)
{
    //figure out how to implement this
}

void BinaryTree::preorderTraversal(TreeNode *root)
{
    //root first, then left, then  right
    if (root != NULL)
    {
        // cout << root->data << " "; //print root
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void BinaryTree::postorderTraversal(TreeNode *root)
{
    //left first, then right, then root
    if (root != NULL)
    {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        // cout << root->data << " "; //print root
    }
}

void BinaryTree::inorderTraversal(TreeNode *root)
{
    //left first, then root, then rignt
    if (root != NULL)
    {
        TreeNode *keep = this->root;
        inorderTraversal(root->left);
        outString = outString + (root->data) + " " + to_string(root->frequency) + " (" + to_string(getLevel(keep, root->data)) + ")\n";
        inorderTraversal(root->right);
    }
}

void BinaryTree::MaxAvinorderTraversal(TreeNode *root)
{
    TreeNode *keep = this->root;
    //left first, then root, then rignt
    if (root != NULL)
    {

        MaxAvinorderTraversal(root->left);
        // cout << root->data << " " << root->frequency << " ("; //print root
        // cout << getLevel(keep, root->data) << ")" << endl;
        if (this->height < getLevel(keep, root->data)) //replacing with the biggest probe number
            this->height = getLevel(keep, root->data);

        this->sumProbes = this->sumProbes + getLevel(keep, root->data) + 1;
        this->countWords++;

        MaxAvinorderTraversal(root->right);
    }
    else
    {
        // cout << " this it it: " << this->height << endl;
    }
}

int BinaryTree::getLevelUtil(TreeNode *node, string data, int level)
{
    //left first, then root, then rignt
    if (node != NULL)
    {

        if (node->data == data)
            return level;

        int downlevel = getLevelUtil(node->left, data, level + 1);

        if (downlevel != 0)
            return downlevel;

        downlevel = getLevelUtil(node->right,
                                 data, level + 1);
        return downlevel;
    }
    else
    {
        return 0;
    }
}
int BinaryTree::getLevel(TreeNode *node, string data)
{
    //left first, then root, then rignt
    if (node != NULL)
    {
        return getLevelUtil(node, data, 1) - 1;
    }
    return getLevelUtil(node, data, 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////end tree code
//refrence: Canvas files folder by Gearge Okeyo
int main()
{
    TreeNode *searchedNode = NULL; //tree node for tree operations like traversal

    char inputFilePath[1024], outputFilePath[1024];
    sprintf(inputFilePath, "%s", "input.txt");   //hardcoding the file to read from input file
    sprintf(outputFilePath, "%s", "output.txt"); //with set name and output file with set name

    FILE *inputFileStream = fopen(inputFilePath, "r"); //open for reading
    if (!inputFileStream)
    {
        char message[1024];
        sprintf(message, "Cannot open input file for reading: %s", inputFilePath);
        throw std::ios_base::failure(message);
    }
    FILE *outputFileStream = fopen(outputFilePath, "w"); //open for writiing
    if (!outputFileStream)
    {
        char message[1024];
        sprintf(message, "Cannot open output file for writing: %s", outputFilePath);
        throw std::ios_base::failure(message);
    }

    else
    {

        fprintf(outputFileStream, "mngongng \n");
    }

    bool ending = false;
    bool preEnd = false;

    while (!feof(inputFileStream))
    {

        //declaring variables
        char subPath[300];
        string sinput;
        char input1[300];

        //reading the paths line by line
        fgets(input1, 255, inputFileStream) != NULL;

        if (!feof(inputFileStream))
        {

            if (input1[0] == '\n') //skip empty lines
            {
                continue; //use recursive function here
            }

            //new string to delete the \n
            sinput = string(input1);
            int len = sinput.length() - 1;
            sinput.replace(len, 1, ""); //deleting the new line character \n

            sprintf(subPath, "%s", sinput.c_str());
            // cout << subPath;
            FILE *subPathstream = fopen(subPath, "r"); //opening the subfile

            char input2[25555];
            fgets(input2, 25555, subPathstream);
            if (input2[0] == '\n')
            {
                // cout << "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn\n";
                // input2[0] = ' ';

                continue;
            }

            // cout << input2 << endl;

            char a[20];
            string s = input2;
            std::for_each(s.begin(), s.end(), [](char & c){
    c = ::tolower(c);
});
            if (s.back() != '\n')
            {
                s = s + "\n";
            }
            //         std::for_each(s.begin(), s.end(), [](char & c){
            //     c = ::tolower(c);
            // });
            bool endOLine = false; //bool to check if end of line has been reached
            strcpy(a, s.c_str());  //strcpy uses token varable to extract data using , as delimiter
            char *token = strtok(a, " ");
            printf("\n");
            string wordT = token;

            //if the word has \n at the end remove the \n before printing
            char pp = wordT.back();
            if (pp == '\n')
            {
                int lenT = wordT.length() - 1;
                wordT.replace(lenT, 1, "");
                endOLine = true;
            }

            // cout << "this1root root : " << wordT << endl;
            // creating the tree in the while loop so that each file has its own tree
            int firstCheck = 0;
            TreeNode *root = new TreeNode(); //dynamically allocated tree size
            root->data = wordT;              //setting the first word of the file as root and then inserting the rest below when inside the while loop
            root->frequency = 1;             //the frequency of the root is still 1
            root->left = NULL;               //initiallizing the left and right to null becaus etree is still empty
            root->right = NULL;
            BinaryTree *bTree = new BinaryTree(root);
            // cout << "\n\nTree size: " << bTree->size(root);
            // endOLine = true;

            while (endOLine == false)
            {
                token = strtok(NULL, " ");
                string wordI = token;
                // cout<<"the last : : "<<wordI.back()<<endl;
                char l = wordI.back();
                if (l == '\n')
                { //if the word has \n at the end remove the \n before printing
                    int len = wordI.length() - 1;
                    wordI.replace(len, 1, "");
                    //
                    //add to tree here
                    //start instert tree
                    searchedNode = bTree->find(wordI); //node to hold the node if it is in the tree
                    // cout << "\n\t>>>searching for {" << wordI << "}: ";
                    if (searchedNode != NULL) //if the node is in the tree then just increment the frequency
                    {
                        // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                        searchedNode->frequency = searchedNode->frequency + 1;
                        // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                    }
                    else //sles if the node is not in the tree create a node with frequency 1
                    {
                        // cout << wordI << " NOT found!";
                        bTree->insert(wordI, 1);
                    }
                    //end insert tree
                    endOLine = true; //set this true to imply that the end of the line has been reached then break while loop
                    //that loop through the line
                    break;
                }
                else //else if the word is not the last word ie not ending with \n, do same as before but dont break at the end, so continue the while loop
                {
                    // cout << "ll :" << wordI << endl;
                    //add to tree here
                    //start instert tree
                    searchedNode = bTree->find(wordI);
                    // cout << "\n\t>>>searching for {" << wordI << "}: ";
                    if (searchedNode != NULL)
                    {
                        // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                        searchedNode->frequency = searchedNode->frequency + 1;
                        // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                    }
                    else
                    {
                        // cout << wordI << " NOT found!";
                        bTree->insert(wordI, 1);
                    }
                    //end insert tree
                }
            }

            // cout << " first line -------------------------" << endl;

            while (!feof(subPathstream))
            {
                cout << "in file";
                char input3[25555];
                fgets(input3, 25555, subPathstream);
                if (input3[0] == '\n')
                {
                    continue;
                }

                char a3[20];
                string s3 = input3;
                std::for_each(s3.begin(), s3.end(), [](char & c){
    c = ::tolower(c);
});
                if (s3.back() != '\n')
                {
                    s3 = s3 + "\n";
                }

                bool endOLine3 = false; //bool to check if end of line has been reached
                strcpy(a3, s3.c_str()); //strcpy uses token varable to extract data using , as delimiter
                char *token3 = strtok(a3, " ");
                printf("\n");
                string wordT3 = token3;

                char pp3 = wordT3.back();
                if (pp3 == '\n')
                {
                    int lenT3 = wordT3.length() - 1;
                    wordT3.replace(lenT3, 1, "");
                    endOLine3 = true;
                }
                //start instert tree
                searchedNode = bTree->find(wordT3);
                // cout << "\n\t>>>searching for {" << wordI << "}: ";
                if (searchedNode != NULL)
                {
                    // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                    searchedNode->frequency = searchedNode->frequency + 1;
                    // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                }
                else
                {
                    // cout << wordI << " NOT found!";
                    bTree->insert(wordT3, 1);
                }
                //end insert tree
                while (endOLine3 == false)
                {
                    char *token3 = strtok(NULL, " ");
                    cout <<"baaaaaaaaaaaaa  "<<token3<<endl;
                    string wordI3 = token3;
                    char l3 = wordI3.back();
                    if (l3 == '\n')
                { //if the word has \n at the end remove the \n before printing
                    int len3 = wordI3.length() - 1;
                    wordI3.replace(len3, 1, "");
                    searchedNode = bTree->find(wordI3); //node to hold the node if it is in the tree
                    // cout << "\n\t>>>searching for {" << wordI << "}: ";
                    if (searchedNode != NULL) //if the node is in the tree then just increment the frequency
                    {
                        // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                        searchedNode->frequency = searchedNode->frequency + 1;
                        // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                    }
                    else //sles if the node is not in the tree create a node with frequency 1
                    {
                        // cout << wordI << " NOT found!";
                        bTree->insert(wordI3, 1);
                    }
                    //end insert tree
                    endOLine3 = true; //set this true to imply that the end of the line has been reached then break while loop
                    //that loop through the line
                    break;
                }
                else //else if the word is not the last word ie not ending with \n, do same as before but dont break at the end, so continue the while loop
                {
                    // cout << "ll :" << wordI << endl;
                    //add to tree here
                    //start instert tree
                    searchedNode = bTree->find(wordI3);
                    // cout << "\n\t>>>searching for {" << wordI << "}: ";
                    if (searchedNode != NULL)
                    {
                        // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                        searchedNode->frequency = searchedNode->frequency + 1;
                        // cout << searchedNode->getData() << " ; " << searchedNode->getFreq() << " found!";
                    }
                    else
                    {
                        // cout << wordI << " NOT found!";
                        bTree->insert(wordI3, 1);
                    }
                    //end insert tree
                }
                        
                    // cout << wordI3 << endl;
                }
            }

            fclose(subPathstream);

            bTree->MaxAvinorderTraversal(root);
            // cout << "///  ---------------------------------------\n";
            cout << "the max height : " << bTree->height + 1 << endl;

            fprintf(outputFileStream, "Maximum number of probes:%d\n", bTree->height + 1);

            // cout<<"word count"<<bTree->countWords<<endl;
            // cout<<"probes sum"<<bTree->sumProbes<<endl;
            cout << "the average : " << float(bTree->sumProbes) / bTree->countWords << endl;
            string avgP = to_string(float(bTree->sumProbes) / bTree->countWords);
            fprintf(outputFileStream, "Average number of probes:%s\n", avgP.c_str());

            bTree->inorderTraversal(root);

            fprintf(outputFileStream, "%s", bTree->outString.c_str());
            cout << bTree->outString;

            fprintf(outputFileStream, "--------------------\n");
            cout << "--------------------\n";
        }
        else
        {
            break;
        }
    }

    // fflush(outputFileStream);
    // fclose(outputFileStream);
    // fclose(inputFileStream);
    return 0;
}