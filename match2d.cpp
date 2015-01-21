#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

const int N = 100;
const int M = N;
int n, m;

string haystack[N], needle[M];
int A[N][N]; /* filled by successive calls to match */
int p[N]; /* pattern to search for in columns of A */

struct Node
{   Node *a[2]; /* alphabet is binary */
    Node *suff; /* pointer to node with proper prefix = longest proper suffix of this node */
    int flag;

    Node()
    {   a[0] = a[1] = 0;
        suff = 0;
        flag = -1;
    }
};

void insert(Node *x, string s)
{   static int id = 0;
    static int p_size = 0;

    for(int i = 0; i < s.size(); i++)
    {   char c = s[i];
        if(x->a[c - '0'] == 0)
            x->a[c - '0'] = new Node;
        x = x->a[c - '0'];
    }
    if(x->flag == -1)
        x->flag = id++;

    /* update pattern */
    p[p_size++] = x->flag;
}

Node *longest_suffix(Node *x, int c)
{   while(x->a[c] == 0)
        x = x->suff;
    return x->a[c];
}

Node *mk_automaton(void)
{   Node *trie = new Node;
    for(int i = 0; i < m; i++)
    {   insert(trie, needle[i]);
    }

    queue<Node*> q;

    /* level 1 */
    for(int i = 0; i < 2; i++)
    {   if(trie->a[i])
        {   trie->a[i]->suff = trie;
            q.push(trie->a[i]);
        }
        else trie->a[i] = trie;
    }

    /* level > 1 */
    while(q.empty() == false)
    {   Node *x = q.front(); q.pop();
        for(int i = 0; i < 2; i++)
        {   if(x->a[i] == 0) continue;
            x->a[i]->suff = longest_suffix(x->suff, i);
            q.push(x->a[i]);
        }
    }

    return trie;
}

/* search for patterns in haystack[j] */
void match(Node *x, int j)
{   for(int i = 0; i < n; i++)
    {   x = longest_suffix(x, haystack[j][i] - '0');
        if(x->flag != -1)
        {   A[j][i-m+1] = x->flag;
        }
    }
}

int match2d(Node *x)
{   /* init */
    int matches = 0;
    memset(A, -1, sizeof(A));

    /* fill the A matrix */
    for(int i = 0; i < n; i++)
    {   match(x, i);
    }

    /* search for pattern p in columns of A */

    /* build pattern string */
    char pat[M+1];
    for(int i = 0; i < m; i++)
    {   pat[i] = p[i] + '0';
    }
    pat[m] = '\0';

    char col[N+1];
    for(int i = 0; i < n; i++)
    {   /* search for p in column i */
        for(int j = 0; j < n; j++)
        {   if(A[j][i] != -1) col[j] = '0' + A[j][i];
            else col[j] = '-';
        }
        col[n] = '\0';

        char *ptr = col;
        while((ptr = strstr(ptr, pat)))
        {   printf("match at (%d,%d)\n", ptr - col, i);
            matches++;
            ptr++;
        }
    }

    return matches;
}

int main(void)
{   cin >> n >> m;
    for(int i = 0; i < n; i++)
    {   cin >> haystack[i];
    }
    for(int i = 0; i < m; i++)
    {   cin >> needle[i];
    }

    Node *trie = mk_automaton();
    match2d(trie);

    return 0;
}
