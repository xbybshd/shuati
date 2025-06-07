/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node *pre, *head;
    void dfs(Node* cur) {
        if (cur == nullptr)
            return;
        dfs(cur->left);
        if (pre != nullptr) // 非头节点的时候，pre此时指向的是当前节点的上一个，就是左节点，因为中序遍历
            pre->right = cur;
        else // 只有在最左边的节点才会发生，此时最开始，head头节点就是最左边的
            head = cur;
        cur->left = pre; // 当前节点反过来指向上一个节点
        pre = cur; // pre指向当前节点
        dfs(cur->right);
    }
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr)
            return nullptr;
        dfs(root);
        head->left = pre; //最后pre是在尾部，与head接上
        pre->right = head;
        return head;
    }
};