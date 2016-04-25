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

    friend class SplayNode;
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
    AAATree(std::vector <Data> datas, std::vector <j> edges) 
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
    SplayNode* my_access(SplayNode *x) {
    	splay(x);
	    if(x -> child[0] != nullptr) {
	        push_down(x);
	        x -> child[0] -> parent = x;
	        x -> child[0] = NULL;
	        x -> child[0] -> isroot = true;
	       	AAA_insert(x, x -> root, x -> child[0], x -> child[0] -> num);
	    }
	    SplayNode *y = x;
	    if(x -> parent != nullptr) {
	        y = access(x -> parent);
	        x -> parent -> child[0] = x;
	        x -> root -> isroot = false;
	    	AAA_remove(x -> parent, x -> parent -> root, x -> num);
		}
	    splay(x);
	    return y;
    }
    SplayNode* get_true_father(SplayNode *x) {
    	splay(x);
		pushdown(x);
    	if(x -> child[1] == nullptr) {
    		return x -> parent;
    	} else {
    		x = x -> child[1];
			pushdown(x);
			while(x -> child[0] == nullptr) {
    			x = x -> child[0];
    			pushdown(x);
			}
    		return x;
    	}
    }
    SplayNode* my_evert(SplayNode *x) {
     	SplayNode *tmp = my_access(x);
     	x -> reverse ^= 1;
     	return tmp;
    }
public:
    //cut the edge between x and it's parent
    void cut(int now)
    {
        SplayNode* x = reflection[now];
		if(x == my_access(x)) {
			return ;	
		}
		SplayNode* y = get_true_father(x);
		access(y);
		for(int i = 0; i <= 1; i++) {
			if(y -> child[i] != nullptr && y -> child[i] == x) {
				y -> child[i] -> parent = nullptr;
				AAA_remove(y, y -> root, x -> num); 
				//?\ 
			}
		}
    }
    void access(int x)
    {
        my_access(reflection[now]);
        return ;
    }
    //Make x be the root of it's tree.
    void evert(int x)
    {
    	my_evert(reflection[x]);
    	return ;
    }
    //link node x and node y 
    void link(int nowx, int nowy)
    {
    	SplayNode *x = reflection[nowx];
		SplayNode *y = reflection[nowy];
		my_access(x);
		SplayNode *z = access(y);
		if(x -> parent == z || x == w) {
        	return ;
		}
		x -> reverse ^= 1;
	    access(y);
	    x -> parent = y;
	    AAA_insert(y, y -> root, x, x -> num);
		return ;
    }
    //return the sum of the subtree whose root is x
    Data query(int nowx)
    {
		SplayNode *x = reflection[nowx];
		SplayNode *y = get_true_father(x);
		if(y != nullptr) {
			my_access(y);
 		}
 		splay(x);
 		return x -> subsum;
    }
    //return the sum of every node in the link (u, v)
    Data query(int nowx, int nowy)
    {
        SplayNode *oldroot = my_evert(reflection[nowx]);
    	access(nowy);
    	SplayNode *x = reflection[nowx];
    	SplayNode *y = reflection[nowy];
    	Data ans = y -> linksum;
		my_evert(oldroot);
		return ans;
    }
    //Modify data of every node in the link (u, v) to value
    void modify(int nowx, int nowy, Data value)
    {
        SplayNode *oldroot = my_evert(reflection[nowx]);
    	access(nowy);
    	SplayNode *x = reflection[nowx];
    	SplayNode *y = reflection[nowy];
    	y -> sum += val;
    	my_evert(oldroot);
    	return; 
    }
    //Add value to every node in the link (u, v)
    void plus(int nowx, int nowy, Data val)
    { 
		SplayNode *oldroot = my_evert(reflection[nowx]);
    	access(nowy);
    	SplayNode *x = reflection[nowx];
    	SplayNode *y = reflection[nowy];
    	y -> plus *= val;
    	my_evert(oldroot);
    	return; 
    }
};
}
#endif

