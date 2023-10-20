#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold course information
struct Course {
    string number; // unique identifier
    string name;
    vector<string> preRequisites;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseNum);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equal to null ptr
    if (root == nullptr)
    {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else
    {
        // add Node root and course
        addNode(root, course);
    }
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNum) {
    // set current node equal to root
    Node* currNode = root;

    // keep looping downwards until bottom reached or matching courseNum found
    while (currNode != nullptr)
    {
        // if match found, return current course
        if (currNode->course.number == courseNum)
        {
            return currNode->course;
        }
        // if course is smaller than current node then traverse left
        else if (currNode->course.number > courseNum)
        {
            currNode = currNode->left;
        }
        // else larger so traverse right
        else
        {
            currNode = currNode->right;
        }
    }
    // if not found return empty course
    Course emptyCourse;
    return emptyCourse;
}

/**
 * Add a course to some node (recursive)
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (node->course.number > course.number)
    {
        // if no left node
        if (node->left == nullptr)
        {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else
        {
            addNode(node->left, course);
        }
    }
    // else
    else
    {
        // if no right node
        if (node->right == nullptr)
        {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else
        {
            // recurse down the right node
            addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr)
    {
        //InOrder not left
        inOrder(node->left);
        //output bidID, title, amount, fund
        cout << "Course Number: " << node->course.number << ", ";
        cout << "Course Name: " << node->course.name << " ";
        // if else to check for prereq courses
        if (node->course.preRequisites.empty() == true) 
        {
            // no prerequisites
        }
        else {
            for (int i = 0; i < node->course.preRequisites.size(); i++) 
            {
                // print prerequisite course info
                cout << "- " << node->course.preRequisites.at(i) << " ";
            }
        }
        cout << endl;
        //InOder right
        inOrder(node->right);
    }
}

/**
 * Load a txt file containing courses into a binary tree
 */
void loadCourses(BinarySearchTree* bst) {
    // print loading message
    cout << "Loading course txt file " << endl;

    // open course file
    ifstream courseFile("Courses.txt");

    // if file fails to open
    if (courseFile.is_open()) 
    {
        string line;
        string courseNumber, courseName, tempString;

        while (getline(courseFile, line))
        {
            stringstream ss(line);
            Course newCourse;
            getline(ss, courseNumber, ',');
            newCourse.number = courseNumber;
            getline(ss, courseName, ',');
            newCourse.name = courseName;
            // if there are prerequisites, loop until stringstream is empty
            while (getline(ss, tempString, ','))
            {
                newCourse.preRequisites.push_back(tempString);
            }
            bst->Insert(newCourse);
        }
    }
    else
    {
        cout << "File failed to open" << endl;
        return;
    }

    // close file when done
    courseFile.close();
}


/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "Welcome to the course planner:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Complete the method call to load the courses
            loadCourses(bst);
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            cout << "Enter course number: " << endl;
            string searchNum;
            cin >> searchNum;
            course = bst->Search(searchNum);
            if (course.number.empty()) 
            {
                cout << "Course number " << searchNum << " not found." << endl;
            }
            else {
                cout << "Course Info: " << course.number << " " << course.name << " ";
                for (int i = 0; i < course.preRequisites.size(); i++)
                {
                    cout << "Prerequisites: " << course.preRequisites.at(i);
                }
                cout << endl;
            }
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
