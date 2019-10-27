/*以‘#’作为空节点标识符，先序遍历串构建树
 * 功能：缺省、带参构建的公、私函数、递归、非递归前中后遍历，层数*/
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
struct BiNode
{
    char data;
    BiNode *lchild,*rchild;
    BiNode():data(0),lchild(nullptr),rchild(nullptr){}
    explicit BiNode(char d):data(d),lchild(nullptr),rchild(nullptr){}
};
/*使用结构体，所有数据可以直接访问*/
class BiTree
{
    BiNode *root;
    BiNode* creat_tree_no_ar();
    void creat_tree_with_ar(BiNode *p);
    /*无返回值的构建二叉树函数，封装*/
    void frontTraverse(BiNode *p);
    void midTraverse(BiNode *p);
    void tailTraverse(BiNode *p);
    void tailTraverse_no_recur_checkpre(BiNode* p);
    void tailTraverse_no_recur_checktag(BiNode* root);
    void levelTraverse(BiNode *p);
    int  treeDepth(BiNode *p);
public:
    BiTree():root(nullptr){}
    BiNode* createTree()
    {
        root=new BiNode;
        creat_tree_with_ar(root);
    };

    /*先中后遍历，均封装，外层访问不需要传参*/
    void fTraverse(){frontTraverse(root);cout<<endl;};
    void mTraverse(){midTraverse(root);cout<<endl;};
    void tTraverse(){
        tailTraverse(root);
        tailTraverse_no_recur_checkpre(root);
        tailTraverse_no_recur_checktag(root);
        cout<<endl;};
    /*层次遍历*/
    void lTraverse(){levelTraverse(root);cout<<endl;};
    /*这里二叉树的层数是从1开始*/
    void getDepth()
    {
        cout<<treeDepth(root)-1<<endl;
    }
};
/*无传入参数，返回值为节点指针*/
/*如需建立父节点，需要传入节点参数，同时将上一个节点作为参数传入下一次递归构建*/
BiNode* BiTree::creat_tree_no_ar() {
    char c;
    BiNode *p = new BiNode;
    if (cin >> c) {
        /*使用#代表空节点*/
        if (c == '#') {
            return nullptr;
        } else {
            p = new BiNode(c);
            /*递归创建左右节点，最外层节点在函数内创建*/
            p->lchild = creat_tree_no_ar();
            p->rchild = creat_tree_no_ar();
        }
    }
    return p;
}
/*必须传入已经的根节点，所有子节点在被递归传参之前建立，避免数据丢失*/
void BiTree::creat_tree_with_ar(BiNode *p) {
    char ch;
    if(cin>>ch)
    {
        if (ch != '0') {
            p->data = ch;
            if (ch != '0')
                p->lchild = new BiNode();
            creat_tree_with_ar(p->lchild);
            if (ch != '0')
                p->rchild = new BiNode();
            creat_tree_with_ar(p->rchild);
        }
        else
            p = nullptr;
    }
}
/*递归访问,传入根节点*/
void BiTree::frontTraverse(BiNode *p) {
    if(p== nullptr)
    {
        return;
    }
    else
    {
        cout<<p->data;
        frontTraverse(p->lchild);
        frontTraverse(p->rchild);
    }
}
void BiTree::midTraverse(BiNode *p) {
    if(p== nullptr)
    {
        return;
    }
    else
    {
        midTraverse(p->lchild);
        cout<<p->data;
        midTraverse(p->rchild);
    }
}
void BiTree::tailTraverse(BiNode *p) {
    if(p== nullptr)
    {
        return;
    }
    else
    {
        tailTraverse(p->lchild);
        tailTraverse(p->rchild);
        cout<<p->data;
    }
}
void BiTree::tailTraverse_no_recur_checkpre(BiNode *p) {
    stack<BiNode*> s;
    BiNode *cur;
    BiNode *pre=nullptr;
    s.push(root);
    while (!s.empty())
    {
        cur=s.top();
        /*检查前一个指针是否是子节点，判断子节点是否已经访问*/
        if((cur->lchild== nullptr&&cur->rchild== nullptr)||((pre!=nullptr)&&(pre==cur->rchild||pre==cur->lchild)))
        {//visit all child nides
            cout<<cur->data;
            s.pop();
            pre=cur;
        }
        else{//not yet, push child node;
            if(cur->rchild!= nullptr)
            {
                s.push(cur->rchild);
            }
            if(cur->lchild!= nullptr)
            {
                s.push(cur->lchild);
            }
        }
    }
}
enum Tag{left,right};
typedef struct
{
    BiNode* node;
    Tag tag;
}TagNode;
void BiTree::tailTraverse_no_recur_checktag(BiNode *root) {
    if (root == nullptr)
        return;
    stack<TagNode> s;
    TagNode tagnode;
    BiNode* p = root;
    while (!s.empty() || p)
    {
        while (p)
        {
            tagnode.node = p;
            //该节点的左子树被访问过
            tagnode.tag = Tag::left;
            s.push(tagnode);
            p = p->lchild;
        }
        tagnode = s.top();
        s.pop();
        //左子树被访问过，则还需进入右子树
        if (tagnode.tag == Tag::left)
        {
            //置换标记
            tagnode.tag = Tag::right;
            //再次入栈
            s.push(tagnode);
            p = tagnode.node;
            //进入右子树
            p = p->rchild;
        }
        else//右子树已被访问过，则可访问当前节点
        {
            cout << (tagnode.node)->data;
            //置空，再次出栈(这一步是理解的难点)
            p = nullptr;
        }
    }

}
void BiTree::levelTraverse(BiNode *p) {
    queue<BiNode *> tq;
    BiNode *q = p;
    if (q != nullptr) {
        tq.push(q);
    }
    while (!tq.empty())
    {
        q=tq.front();
        cout<<q->data;
        tq.pop();
        if(q->lchild!= nullptr)
        {
            tq.push(q->lchild);
        }
        if(q->rchild!= nullptr)
        {
            tq.push(q->rchild);
        }
    }
}
int BiTree::treeDepth(BiNode *p) {
    if(!p)

    {
        return 0;
    }
    int nleft=treeDepth(p->lchild);
    int nright=treeDepth(p->rchild);

    return (nleft>nright)?(nleft+1):(nright+1);
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        BiTree biTree;
        biTree.createTree();
//        biTree.fTraverse();
//        biTree.mTraverse();
//        biTree.tTraverse();
//        biTree.lTraverse();
        biTree.getDepth();
    }
}
