#ifndef DATA_STRUCTURE_AAA_TREE
#define DATA_STRUCTURE_AAA_TREE

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <cstddef>
#include <stdexcept>
#include <cassert>
#include <utility>
#include <vector>

namespace DataStructure
{
template <class Data>
class AAATree
{

    class SplayNode;
    void link(int x, int y);
    
    std::vector<SplayNode*> reflection;
    
    class TreapNode
    {
    public:
        TreapNode *left, *right;
        int size, num;
        Data sum; 
        SplayNode *node;
        TreapNode() {}
        TreapNode(Data data, SplayNode *node, int num) : sum(data), node(node), num(num) 
        {
            left = right = NULL;
            size = 1;
        }
        TreapNode(TreapNode &other)
        {
            num = other.num;
            sum = other.sum;
            node = NULL;
            size = other.size();
            left = right = NULL;
        }
        ~TreapNode() {}
    };
    
    class SplayNode
    {
    public:
        Data data, linksum, subsum, sum, plus, same;
        int size, num;
        bool isroot, reverse;
        SplayNode *child[2], *parent;
        TreapNode *node, *root;
        SplayNode() {}
        SplayNode(Data data, int num) : data(data), num(num)
        {
            size = 1;
            isroot = true; 
            reverse = false;
            child[0] = child[1] = parent = NULL;
            node = new TreapNode(data, this, num);
            root = node; 
        } 
        SplayNode(SplayNode &other)
        {
            num = other.num;
            size = other.size();
            isroot = other.isroot;
            reverse = other.reverse;
            child[0] = child[1] = parent = NULL;
            node = new TreapNode(*(other.node));
            node -> node = this;
        }
        ~SplayNode() 
        {
            if(node) delete(node);
        }
    };
    
    
    
    AAATree() {}
    AAATree(std::vector <Data> datas, std::vector <Edge> edges) 
    {
        reflection.push_back(NULL);
        for (int i = 0; i < datas.size(); i++)
            reflection.push_back(new SplayNode(datas[i], i));
            
        for(int i = 0; i < edges.size(); i++) 
            link(edges[i].u, edges[i].v);
    }
    AAATree(AAATree &other)
    {
        reflection.pushback(0);
        for (int i = 1; i <= other.reflection.size(); i++)
            reflection.pushback(new SplayNode(*(other.reflection[i])));
        for (int i = 1; i <= other.reflection.size(); i++)
        {
            int now = other.reflection[i] -> num;
            int tmp;
            if(other.reflection[i] -> root)
            {
            	tmp = other.reflection[i] -> child[0] -> num;
            	reflection[i].root = reflection[tmp].node;
			}
            if(other.reflection[i] -> child[0])
            {
                tmp = other.reflection[i] -> child[0] -> num;
                reflection[i].child[0] = reflection[tmp];
            }
            if(other.reflection[i] -> child[1])
            {
                tmp = other.reflection[i] -> child[1] -> num;
                reflection[i].child[1] = reflection[tmp];
            }
            if(other.reflection[i] -> parent)
            {
                tmp = other.reflection[i] -> parent -> num;
                reflection[i].parent = reflection[tmp];
            }
            if(other.reflection[i] -> node -> left)
            {
                tmp = other.reflection[i] -> node -> left -> num;
                reflection[i]-> node -> left = reflection[tmp] -> node;
            }
            if(other.reflection[i] -> node -> right)
            {
                tmp = other.reflection[i] -> node -> right -> num;
                reflection[i]-> node -> right = reflection[tmp] -> node;
            }
        }
    }
    ~AAATree() 
    {
        for (int i = 1; i <= reflection.size(); i++)
            delete reflection[i];
        reflection.clear();
    }
    
    //Maintain Data of TreapNode x
    void maintain(TreapNode *x)
    {
        
    }
    //pushdown flags of TreapNode x 
    void treapPushdown(TreapNode *x)
    {
    
    }
    TreapNode* merge(TreapNode *x, TreapNode *y)
    {
        
    }
    std::pair<TreapNode*, TreapNode*> split(TreapNode *x, int sz)
    {
        
    }
    //Delete TreapNode x from it's Treap
    void treapDel()
    {
        
    }
    //Insert TreapNode y into the splay which contain TreapNode x
    void treapInsert(TreapNode *x, TreapNode *y)
    {
    
    }
    //Insert SplayNode y into the splay which contain SplayNode x
    void insert(SplayNode *y, SplayNode *x)
    {
    
    }
    //Maintain Data of SplayNode x
    void maintain(SplayNode *x)
    {
        
    }
    //pushdown flags of SplayNode x 
    void pushdown(SplayNode *x)
    {
        
    }
    void splay(SplayNode *x)
    {
        
    }
public:
    //cut the edge between x and it's parent
    void cut(int x)
    {
        
    }
    //link node x and node y 
    void link(int x, int y)
    {
    
    }
    //return the sum of the subtree whose root is x
    Data query(int x)
    {
        
    }
    //return the sum of every node in the link (u, v)
    Data query(int x, int y)
    {
        
    }
    //Modify data of every node in the link (u, v) to value
    void modify(int x, int y, Data value)
    {
        
    }
    //Add value to every node in the link (u, v)
    void plus(int x, int y, Data val)
    {
        
    }
    void access(int x)
    {
        
    }
    //Make x be the root of it's tree.
    void evert(int x)
    {
    
    }
};
}
#endif
