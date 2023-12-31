#include <algorithm>
#include <queue>
#include <fstream>
#include "BST.h"

std::string to_lower_case(const std::string& str) {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

Node* BST::backtrack_insert(Node *root, Node *new_node){
    if (root == nullptr) {
        return new_node;
    }
    if (to_lower_case(new_node->stu_info.last_name) > to_lower_case(root->stu_info.last_name)){
        root->right = backtrack_insert(root->right, new_node);
    }
    else{
        root->left = backtrack_insert(root->left, new_node);
    }
    return root;
}

void BST::insert(StuInfo stu_info){
    Node * new_node = new Node(stu_info);
    root = backtrack_insert(root, new_node);
}

void BST::backtrack_traverse(Node *root, std::ofstream& output_file){
    if (root == nullptr){
        return;
    }
    backtrack_traverse(root->left, output_file);
    output_file << root->stu_info.last_name << " " << root->stu_info.number \
    << " " << root->stu_info.home_department << " " << root->stu_info.program \
    << " " << root->stu_info.year << std::endl;
    backtrack_traverse(root->right, output_file);
}

void BST::in_order_traverse(){
    std::string output_filename = "in_order_traverse.txt";
    std::ofstream output_file(output_filename);

    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file: " << output_filename << std::endl;
        return;
    }
    backtrack_traverse(root, output_file);
    output_file.close();
}

void BST::level_traverse(){
    if (root == nullptr) {
        return;
    }
    std::string output_filename = "level_traverse.txt";
    std::ofstream output_file(output_filename);

    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file: " << output_filename << std::endl;
        return;
    }
    std::queue<Node*> que;
    que.push(root);
    while(!que.empty()) {
        int size = que.size();
        while (size--){
            Node * tmp = que.front();
            que.pop();
            output_file << tmp->stu_info.last_name << " " << tmp->stu_info.number \
            << " " << tmp->stu_info.home_department << " " << tmp->stu_info.program \
            << " " << tmp->stu_info.year << std::endl;
            if (tmp->left != nullptr) {
                que.push(tmp->left);
            }
            if(tmp->right != nullptr) {
                que.push(tmp->right);
            }
        }
    }
    output_file.close();
}