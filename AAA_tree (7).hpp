#ifndef DATA_STRUCTURE_AAA_TREE
#define DATA_STRUCTURE_AAA_TREE

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cstddef>
#include <stdexcept>
#include <cassert>
#include <utility>
#include <vector>
#include <ctime> 
namespace DataStructure
{
    class Edge
    {
    public:
        int u, v;
        Edge(){}
        Edge(int u, int v) : u(u), v(v) {};
    };

    bool visit[100005];
    class AAATree
    {
    public:
        class SplayNode;
        
        std::vector<SplayNode*> reflection;
        
        class TreapNode
        {
        public:
            TreapNode *left, *right;
            int size, num, priority;
            int sum;
            SplayNode *node;
            
            TreapNode() {}
            TreapNode(int data, SplayNode *node, int num, int priority) : sum(data), node(node), num(num), priority(priority)
            {
                sum = 0;
                left = right = NULL;
                size = 1;
            }
            TreapNode(TreapNode &other)
            {
                num = other.num;
                sum = other.sum;
                priority = other.priority;
                node = NULL;
                size = other.size;
                left = right = NULL;
            }
            
            ~TreapNode() {}
        };
        
        class SplayNode
        {
        public:
            
            int data, linksum, subsum, plus, same;
            int size, num;
            bool  reverse;
            SplayNode *child[2], *par;
            TreapNode *node, *root;
            
            SplayNode() {}
            SplayNode(int data, int num) : data(data), num(num)
            {
                size = 1;
                reverse = false;
                child[0] = child[1] = par = NULL;
                plus = same = 0;
                linksum = data; subsum = 0;
                node = new TreapNode(data, this, num, 0);
                root = NULL;
            }
            SplayNode(SplayNode &other)
            {
                num = other.num;
                plus = other.plus;
                same = other.same;
                linksum = other.linksum;
                subsum = other.subsum;
                data = other.data;
                size = other.size;
                reverse = other.reverse;
                child[0] = child[1] = par = NULL;
                node = new TreapNode(*(other.node));
                node -> node = this;
            }
            bool isroot()
            {
                return (!par || (par -> child[0] != this && par -> child[1] != this));
            }
            ~SplayNode()
            {
                if(node) delete(node);
            }
        };
        
        
public:
        AAATree() {}
        AAATree(std::vector <int> datas, std::vector <Edge> edges)
        {
            memset(visit, false, sizeof(visit));
            //std::srand(time(0));
            reflection.push_back(NULL);
            for (int i = 0; i < datas.size(); i++)
                reflection.push_back(new SplayNode(datas[i], i + 1));
            
            for(int i = 0; i < edges.size(); i++) {
                link(edges[i].v, edges[i].u);
            //    printf("%d\n", i);
            }
        }
        AAATree(AAATree &other)
        {
            reflection.push_back(NULL);
            for (int i = 1; i <= other.reflection.size(); i++)
                reflection.push_back(new SplayNode(*(other.reflection[i])));
            for (int i = 1; i <= other.reflection.size(); i++)
            {
                int tmp;
                if(other.reflection[i] -> root)
                {
                    tmp = other.reflection[i] -> child[0] -> num;
                    reflection[i] -> root = reflection[tmp] -> node;
                }
                if(other.reflection[i] -> child[0])
                {
                    tmp = other.reflection[i] -> child[0] -> num;
                    reflection[i] -> child[0] = reflection[tmp];
                }
                if(other.reflection[i] -> child[1])
                {
                    tmp = other.reflection[i] -> child[1] -> num;
                    reflection[i] -> child[1] = reflection[tmp];
                }
                if(other.reflection[i] -> par)
                {
                    tmp = other.reflection[i] -> par -> num;
                    reflection[i] -> par = reflection[tmp];
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
private:
        /*void debug()
        {
            for (int i = 1; i <= 10; i++)
            {
                printf("_____________________\n");
                printf("id = %d check_id = %d\n", i, reflection[i] -> num);
                printf("left = %d right = %d\n",reflection[i] -> child[0] ? reflection[i] -> child[0] -> num : -1, reflection[i] -> child[1] ? reflection[i] -> child[1] -> num : -1);
                printf("parent = %d \n", reflection[i] -> par ? reflection[i] -> par -> num : -1);
                printf("\n");
            }
            for (int i = 1; i <= 8; i++)
            printf("over");printf("\n\n\n");
        }*/
        void TreapUpdate(TreapNode *t)
        { 
            t -> sum = t -> node -> subsum + t -> node -> linksum;
            if(t -> left != NULL) t -> sum = t -> sum + t -> left -> sum;
            if(t -> right != NULL) t -> sum = t -> sum + t -> right -> sum;
            t -> size = 1;
            if(t -> left != NULL) t -> size = t -> size + t -> left -> size;
            if(t -> right != NULL) t -> size = t -> size + t -> right -> size;
        }
        
        void TreapLL(TreapNode *&node)
        {
            TreapNode *tmp = node -> left;
            node -> left = tmp -> right;
            tmp -> right = node;
            TreapUpdate(node);
            TreapUpdate(tmp);
            node = tmp;
        }
        
        void TreapRR(TreapNode *&node)
        {
            TreapNode *tmp = node -> right;
            node -> right = tmp -> left;
            tmp -> left = node;
            TreapUpdate(node);
            TreapUpdate(tmp);
            node = tmp;
        }
        
        void TreapInsert(TreapNode *&t, SplayNode *node, int num0)
        {
            if(t == NULL)
            {                                 
                int priority = std::rand();
                //maintain(node);
                node -> node -> left = NULL;
                node -> node -> right = NULL;
                t = node -> node;
                t -> sum = node -> linksum + node -> subsum;
                t -> priority = priority;
                //t = new TreapNode(node->linksum + node->node, node, num0, priority);
            }
            else if(num0 < t -> num)
            {    
                //t -> size++;
                //t -> sum = t -> sum + node -> subsum + node -> linksum;
                TreapInsert(t -> left, node, num0);
                if(t -> left -> priority < t -> priority) TreapLL(t);
            }   
            else if(num0 > t -> num)
            {
                //t -> size++;
                //t -> sum = t -> sum + node -> subsum + node -> linksum;
                TreapInsert(t -> right, node, num0);
                if(t -> right -> priority < t -> priority) TreapRR(t);
            }
            if(t) TreapUpdate(t);
        }
        
        void TreapRemove(TreapNode *&t, int num0)
        {
            if(t != NULL)
            {
                if(num0 < t -> num) TreapRemove(t -> left, num0);
                else if(num0 > t -> num) TreapRemove(t -> right, num0);
                else
                {
                    if(t -> left == NULL)
                    {
                        TreapNode* tmp = t;
                        t = t -> right; 
                    }
                    else if(t -> right == NULL)
                    {
                        TreapNode* tmp = t;
                        t = t -> left;
                    }
                    else
                    {
                        if(t -> left -> priority < t -> right -> priority) TreapLL(t);
                        else TreapRR(t);
                        TreapRemove(t, num0);
                    }
                }
                if(t) TreapUpdate(t);
            }
        }
        
        /*void DeleteTreap(TreapNode *t)
        {
            if(t != NULL)
            {
                if(t -> left != NULL) DeleteTreap(t -> left);
                if(t -> right != NULL) DeleteTreap(t -> right);
                delete t;
            }
        }*/
    private:  //private functions for splay
        void Plus(SplayNode *x, int val)
        {
            int tmp = x -> plus + val;
            x -> plus = 0;
            /*if(x -> same) 
            {
                for (int i = 0; i <= 1; i++)
                if(x -> child[i]) Same(x -> child[i], x -> same);
                x -> same = 0;
            }*/
            x -> plus = tmp;
            x -> linksum += val * x -> size;
            x -> data += val; 
        }
        void Same(SplayNode *x, int val)
        {
            //pushdown(x);
            x -> plus = 0;
            x -> same = val;
            x -> linksum = val * x -> size;
            x -> data = val;
        }
        void Reverse(SplayNode *x)
        {
            //pushdown(x);
            x -> reverse ^= 1;
            std::swap(x -> child[0], x -> child[1]);
        }
        void SplayUp(SplayNode *x)
        {
            //if(x -> child[0]) SplayDown(x -> child[0]);
            //if(x -> child[1]) SplayDown(x -> child[1]);
            SplayDown(x);
            x -> size = 1;
            if (x -> child[0]) x -> size += x -> child[0] -> size;
            if (x -> child[1]) x -> size += x -> child[1] -> size;
            
            x -> linksum = x -> data;
            if (x -> child[0]) x -> linksum += x -> child[0] -> linksum;
            if (x -> child[1]) x -> linksum += x -> child[1] -> linksum;
            
            x -> subsum = 0;
            if (x -> root) x -> subsum += x -> root -> sum;
            for (int i = 0; i <= 1; i++)
                if(x -> child[i]) 
                    x -> subsum += x -> child[i] -> subsum;
        }
        
        void SplayDown(SplayNode *x)
        {
            if(!x) return;
            if (x -> reverse)
            {
                for (int i = 0; i <= 1; i++)
                if (x -> child[i]) Reverse(x -> child[i]);
                x -> reverse = false;
            }
            if (x -> same != 0)
            {   //To modify: Only consider the case of integer!
                for (int i = 0; i <= 1; i++)
                if (x -> child[i])
                {
                    x -> child[i] -> plus = 0;
                    Same(x -> child[i], x -> same);
                }
                x -> same = 0;
            }
            if (x -> plus != 0)
            {
                for (int i = 0; i <= 1; i++)
                if (x -> child[i]) Plus(x -> child[i], x -> plus);
                x -> plus = 0;
            }
        }
        
        
        void SplayLrot(SplayNode *x)
        {
            SplayNode *p = x -> par;
            SplayDown(p);
            SplayDown(x);
            x -> par = p -> par;
            if (p -> par != NULL)
            {
                if (p -> par -> child[0] == p) p -> par -> child[0] = x;
                if (p -> par -> child[1] == p) p -> par -> child[1] = x;
            }
            p -> par = x;
            if(x -> child[1]) x -> child[1] -> par = p;
            p -> child[0] = x -> child[1];
            x -> child[1] = p;
            SplayUp(p);
            SplayUp(x);
        }
        void SplayRrot(SplayNode *x)
        {
            SplayNode *p = x -> par;
            SplayDown(p); 
            SplayDown(x);
            x -> par = p -> par;
            if (p -> par != NULL)
            {
                if (p -> par -> child[0] == p) p -> par -> child[0] = x;
                if (p -> par -> child[1] == p) p -> par -> child[1] = x;
            }
            p -> par = x;
            if(x -> child[0]) x -> child[0] -> par = p;
            p -> child[1] = x -> child[0];
            x -> child[0] = p;
            SplayUp(p);
            SplayUp(x);
        }
        
        
    public:
        void AAA_remove(SplayNode *tar, int id)
        {
            if(!visit[id]) printf("Remove fault\n");
            maintain(tar);
            TreapRemove(tar -> root, id);
            visit[id] = false;
            maintain(tar);
            while (!tar -> isroot())
            {
                tar = tar -> par;
                maintain(tar);
            }
        }
        
        void AAA_insert(SplayNode *tar, TreapNode *&root, SplayNode *ctx, int num)
        {
           // printf("ok\n"); 
            if(visit[ctx -> num]) printf("Insert_fault\n");
            visit[ctx -> num] = true;
            SplayNode *tmp = ctx;
            while(!ctx -> isroot()) {tmp = tmp -> par; maintain(tmp);}
            tmp = tar;
            while(!tmp -> isroot()) {tmp = tmp -> par; maintain(tmp);}
            maintain(tar);
            maintain(ctx);
            ctx -> node -> left = NULL;
            ctx -> node -> right = NULL;
            ctx -> node -> size = 1;
            TreapInsert(root, ctx, num);
            /*for (int i = 1; i < reflection.size(); i++)
                if(reflection[i] -> root) printf("fine\n");*/
            maintain(tar);
            while (!tar -> isroot())
            {
                tar = tar -> par;
                maintain(tar);
            }
        }
        //Maintain int of SplayNode x
        void maintain(SplayNode *x)
        {
            SplayDown(x);
            SplayUp(x);
        }
        //pushdown flags of SplayNode x
        void pushdown(SplayNode *x)
        {
            SplayDown(x);
        }
        void splay(SplayNode *x)
        {
            SplayDown(x);
            if (x -> isroot()) return;
            while (!x -> isroot())
            {
                if(!x -> par -> isroot()) SplayDown(x -> par -> par);
                SplayDown(x -> par); 
                SplayDown(x);
                if (x -> par -> isroot())
                {
                    if (x -> par -> child[0] == x)
                        SplayLrot(x);
                    else
                        SplayRrot(x);
                }
                else
                {
                    SplayNode *dad = x -> par, *grandpa = x -> par -> par;
                    bool iAmLeft = (dad -> child[0] == x), dadIsLeft = (grandpa -> child[0] == dad);
                    if (iAmLeft == dadIsLeft)
                    {
                        if (iAmLeft)
                        {
                            SplayLrot(dad);
                            SplayLrot(x);
                        }
                        else
                        {
                            SplayRrot(dad);
                            SplayRrot(x);
                        }
                    }
                    else
                    {
                        if (iAmLeft)
                        {
                            SplayLrot(x);
                            SplayRrot(x);
                        }
                        else
                        {
                            SplayRrot(x);
                            SplayLrot(x);
                        }
                    }
                }
            }
        }
        
      	SplayNode* my_access(SplayNode *x)
        {
            splay(x);
            if(x -> child[0] != nullptr)
            {
                SplayNode *tmp = x -> child[0];
                splay(x);
                pushdown(x);
                x -> child[0] = NULL; 
                maintain(x);
                AAA_insert(x, x -> root, tmp, tmp -> num);
            }
            
            SplayNode *y = x;
            if(x -> par != nullptr) 
            {
                y = my_access(x -> par);
                pushdown(x -> par);
                x -> par -> child[0] = x;
                maintain(x -> par);
                AAA_remove(x -> par, x -> num);    
            }
            splay(x);
            return y;
        }

    public:
        SplayNode* get_true_father(SplayNode *x) 
        {
        	splay(x);
            assert(x -> isroot());
            maintain(x);
            if(x -> child[1] == nullptr) 
            {
                return x -> par;
            } 
            else 
            {
                x = x -> child[1];
                maintain(x);
                while(x -> child[0] != nullptr) 
                {
                    x = x -> child[0];
                    maintain(x);
                }
                return x;
            }
        }
        SplayNode* my_evert(SplayNode *x) 
        {
            SplayNode *tmp = my_access(x);
            Reverse(x);
            return tmp;
        }
        
        void access(int x)
        {
            my_access(reflection[x]);
            return ;
        } 
        int lca(int x, int y) {
             my_evert(reflection[x]);
             SplayNode *ans = my_access(reflection[y]);
             return ans -> num;
        }
        void cut(int now)
        {
            SplayNode* x = reflection[now];
            if(x == my_access(x)) return ;	
            SplayNode* y = get_true_father(x);
            my_access(x);
            my_access(y);
            for(int i = 0; i <= 1; i++) 
            {
                if(y -> child[i] == x) 
                {
                    x -> par = nullptr;
                    y -> child[i] = nullptr;
                    AAA_remove(y, x -> num);
                }
            }
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
            // debug();
            SplayNode *x = reflection[nowx];
            SplayNode *y = reflection[nowy];
            my_access(x);
            SplayNode *z = my_access(y);
            splay(x);
            if(x -> par == z || x == z) return ;
            Reverse(x);
            x -> par = y;
            maintain(y);
            AAA_insert(y, y -> root, x, x -> num);
            //debug();
            //my_access(x);
            return ;
        }
        //return the sum of the subtree whose root is x
        int query(int nowx)
        {
            SplayNode *x = reflection[nowx];
            SplayNode *y = get_true_father(x);
            if(y != nullptr) my_evert(y), my_access(y);
            splay(x);
            return x -> subsum + x -> linksum;
        }
        //return the sum of every node in the link (u, v)
        int query(int nowx, int nowy)
        {
            evert(nowx);
            access(nowy);           
            SplayNode *x = reflection[nowx];
            SplayNode *y = reflection[nowy];
            splay(y);
            int ans = y -> linksum;
            return ans;
        }
        //Modify int of every node in the link (u, v) to value
        void modify(int nowx, int nowy, int value)
        {
            evert(nowx);
            access(nowy);
            SplayNode *x = reflection[nowx];
            SplayNode *y = reflection[nowy];
            splay(y);
            Same(y, value);
            return; 
        }
        //Add value to every node in the link (u, v)
        void plus(int nowx, int nowy, int val)
        { 
            evert(nowx);
            access(nowy);
            SplayNode *x = reflection[nowx];
            SplayNode *y = reflection[nowy];
            splay(y);
            Plus(y, val);
            return; 
        }
    };
}

#endif

