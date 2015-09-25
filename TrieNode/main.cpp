#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int KIND = 26;
const int MAXN = 1000;
int cntNode;

struct Trie
{
	bool isword;
	int prefix;
	Trie *next[KIND];
	void init()
	{
		isword=0;
		prefix=0;
		//memset(next,0,sizeof(next));
	}
}HEAP[MAXN];

inline Trie* newTrie()
{
	HEAP[cntNode].init();
	return &HEAP[cntNode++];
}

void insert(Trie* root,char *str)
{
	for(char *p=str;*p;++p)
	{
		int ch=*p-'a';
		if(root->next[ch]==NULL)						//若不存在该结点，则从新创建
		{
			root->next[ch]=newTrie();
		}
		root=root->next[ch];
		root->prefix++;
	}
	root->isword=true;
}

int count(Trie *root,char *str)							//返回前缀数量
{
	for(char *p=str;*p;++p)
	{
		char ch=*p-'a';
		if(root->next[ch]==NULL)
			return 0;
		root=root->next[ch];
	}
	return root->prefix;
}

int dealTrie(Trie *T)
{
    int i;
    if(T==NULL)
		return 0;
	for(i=0;i<KIND;i++)
	{
		if(T->next[i]!=NULL)
			dealTrie(T->next[i]);
	}
	free(T);
	return 0;
}

int main()
{
    char str[12];
    Trie *root=newTrie();
    while(gets(str))
    {
    	if(str[0]==0)
    		break;
    	insert(root,str);
    }
    while(gets(str))
    {
    	printf("%d",count(root,str));
    }
    dealTrie(root);
    return 0;
}
