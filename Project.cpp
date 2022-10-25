#include<iostream>
#include<string.h>
#include <stdlib.h>

using namespace std;

typedef struct dictionary
{
    struct dictionary *right;
    struct dictionary *left;
    string word,meaning;
} node;

node* create();
void addnew(node*);
void deleteword(node*,string);
void Search(node *);
void Search2(node *);
int check(string, string);
void Similar1(node *, string);
void Similar2(node *, string);
void similar3(node *, node *);

node* create()
{
    node *root, *newnode, *tmp, *parent;
    char cCh;
    int n;
    root=nullptr;
    do
    {
        newnode=new node;
        newnode->left= nullptr;
        newnode->right=nullptr;

        cout<<"Enter Word: ";
        cin>>newnode->word;

        cout<<"Enter Meaning: ";
        cin>>newnode->meaning;

        if(root==nullptr)
        {
            root=newnode;
        }
        else
        {
            tmp=root;
            while(tmp!=nullptr)
            {
                parent=tmp;
                if(tmp->word<newnode->word)
                    tmp=tmp->right;
                else
                    tmp=tmp->left;

            }
            if(parent->word<newnode->word)
            {
                parent->right=newnode;
            }
            else
            {
                parent->left=newnode;
            }

        }
        cout<< "Press 1 for continue otherwise press 0 : ";
        cin>> n;
    }
    while(n==1);
    return root;
}

void addnew(node *root)
{
    node *tmp, *newnode,  *parent;
    newnode=new node;
    newnode->left=nullptr;
    newnode->right=nullptr;

    cout<<"Enter Word: ";
    cin>>newnode->word;

    cout<<"Enter Meaning: ";
    cin>>newnode->meaning;

    tmp=root;
    while(tmp!=nullptr)
    {
        parent=tmp;
        if(tmp->word<newnode->word)
        {
            tmp=tmp->right;
        }
        else
        {
            tmp=tmp->left;
        }
    }
    if(parent->word < newnode->word)
    {
        parent->right=newnode;
    }
    else
    {
        parent->left=newnode;
    }
    cout<<"Word is Successfully added. "<< endl;
}

void deleteword(node *root,string w)
{
    node *tmp;
    while(root)
    {
        if(root->word==w)
        {
            break;
        }
        tmp=root;
        if(root->word<w)
        {
            root=root->right;
        }
        else
        {
            root=root->left;
        }

    }
    if(root->left==NULL&&root->right==NULL)
    {
        if(tmp->right==root)
        {
            tmp->right=NULL;
        }
        else
        {
            tmp->left=NULL;
        }
        delete(root);
        cout<<"Word is deleted."<< endl;
    }

    else if(root->left==nullptr)
    {
        if(tmp->right==root)
        {
            tmp->right=root->right;
        }
        else
        {
            tmp->left=root->right;
        }
        delete(root);
        cout<<"Word is deleted. "<< endl;
    }

    else if(root->right==nullptr)
    {
        if(tmp->right==root)
        {
            tmp->right=root->left;
        }
        else
        {
            tmp->left=root->left;
        }
        delete(root);
        cout<<"Word is deleted. "<< endl;
    }

    else
    {
        tmp=root;
        node *tmp1;
        tmp1=root->right;
        while(tmp1->left)
        {
            tmp=tmp1;
            tmp1=tmp1->left;
        }
        root->word=tmp1->word;
        root->meaning=tmp1->meaning;
        if(tmp==root)
        {
            root->right=tmp1->right;
        }
        else
        {
            tmp->left=NULL;
        }
        delete(tmp1);
        cout<<"Word is deleted. "<< endl;
    }
}

int check(string a, string b)
{
    int i,c,k;
    for(i=0,k=0 ; a[i]!='\0' && b[k]!='\0' ; i++,k++)
    {
        if(a[i]>b[k])
        {
            c=1;
            break;
        }
        else if(b[k]>a[i])
        {
            c=-1;
            break;
        }
        else
            c=0;
    }
    if(c==1)
    {
        return 1;
    }
    else if(c==-1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int c = 0;

void Similar1(node *Root, string q)
{
    string st, w;

    if(Root!=nullptr)
    {
        w = q;
        st = Root->word;
        Similar1(Root->left,q);

        if(st[0]==w[0] || st[1] == w[1])
        {
            c++;
        }

        Similar1(Root->right,q);
    }
}

void Similar2(node *Root, string q)
{
    string st, w;

    if(Root!=nullptr)
    {
        w = q;
        st = Root->word;
        Similar2(Root->left,q);

        if(st[0]==w[0] || st[1] == w[1])
        {
            cout<< Root->word << "  " ;
        }

        Similar2(Root->right,q);
    }
}


void Search(node *Root)
{
    int p=0;
    node *tmp;
    tmp= Root ;
    char w[10];
    cout<< "Enter Word :";
    cin>>w;
    while(tmp!=nullptr && p==0)
    {
        if(check(w,tmp->word )>0)
        {
            tmp=tmp->right;
        }
        else if(check(w,tmp->word )<0)
        {
            tmp=tmp->left ;
        }
        else if(check(w,tmp->word )==0)
        {
            p=1;
            cout<< tmp->meaning;
        }
    }
    if(p==0)
    {
        cout<< "The word "<< w << " Was not found. "<< endl;

        Similar1(Root,w);
        if(c!=0)
        {
            cout<< "Did you mean : ";
            Similar2(Root,w);
            c=0;
        }
    }
}

void Search2(node *Root)
{
    int p=0;
    node *tmp;
    tmp= Root ;
    char w[10];
    cout<< "Enter Word :";
    cin>>w;
    while(tmp!=nullptr && p==0)
    {
        if(check(w,tmp->word )>0)
        {
            tmp=tmp->right;
        }
        else if(check(w,tmp->word )<0)
        {
            tmp=tmp->left ;
        }
        else if(check(w,tmp->word )==0)
        {
            p=1;
            cout<< "Similar Words : ";
            similar3(Root,tmp);
        }
    }
}

void similar3(node *Root, node *tmp)
{
    if(Root!= nullptr)
    {
        similar3(Root->left,tmp);
        similar3(Root->right,tmp);
        if((check(Root->meaning, tmp->meaning) == 0))
        {
            cout<< Root->word<<" ";
        }
    }
}

int main()
{
    node *Root;
    string st;
    char e[15];
    int w,in;
    do
    {
        cout<<"1.Create dictionary"<< endl;
        cout<<"2.Add new Word to the Dictionary"<< endl;
        cout<<"3.Delete a word from Dictionary"<< endl;
        cout<<"4.Search"<< endl;
        cout<<"5.Similar Meaning "<< endl;

        cout<<"Enter your Choice : ";
        cin>>in;
        if(in==1)
        {
            Root=create();
        }
        else if(in==2)
        {
            addnew(Root);
        }
        else if(in==3)
        {
            cout<<"enter word to delete : ";
            cin>>st;
            deleteword(Root,st);
        }
        else if(in==4)
        {
            Search(Root);
        }
        else if(in == 5 )
        {
            Search2(Root);
        }

        cout<< endl <<"press 1 for main Or press 2 for exit : ";
        cin>>w;
        cout<< endl;
    }
    while(w==1);
}



