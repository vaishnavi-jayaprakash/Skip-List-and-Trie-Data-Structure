/*Program to implement Trie ADT using list
This trie contains only lowercase alphabets(a-z)
Vaishnavi - insertion
Rithani - search
Pradeepaa - deletion
    */
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define N 26
class Trie
{
    struct node
    {
        char data;
        node* children[N];
        int is_end;
    };
    struct node*root;
    public:
        Trie()
        {
            root=NULL;
        }
        node* getroot();
        node* insert(char*);
        node* getnode(char);
        void freenode(node*);
        void freenode_help();
        bool search(char*);
        int isempty(node*);
        int word_len(char*word);
        bool delete_word(char*);
        node* delete_rec(node*,char*,int);
};
int main()
{
    Trie t1;
    int choice,result;
    while(choice!=4)
    {
        char word[50];
        printf("\n1.Insertion\n2.Search\n3.Deletion\n4.Exit\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            {
                printf("Enter string to be inserted into Trie: ");
                scanf("%s",word);
                //Check for empty string
                if(word[0]=='\0')
                {
                    printf("String is empty....Enter a valid string\n");
                    break;
                }
                else
                {
                    t1.insert(word);
                    printf("Successfully inserted");
                }
                break;
            }
            case 2:
            {
                printf("Enter a word to search : ");
                scanf("%s",word);
                result=t1.search(word);
                if(result!=false)
                {
                    printf("Word found");
                }
                else
                {
                    printf("Word not found");
                }
                break;
            }
            case 3:
            {
                printf("Enter a word to delete : ");
                scanf("%s",word);
                result=t1.delete_word(word);
                if(result!=0)
                {
                    printf("Word Deleted");
                }
                else
                {
                    printf("Word not found or Empty list!!");
                }
                break;

            }
            case 4:
            {
                t1.freenode_help();
                printf("Exiting..\n");
                break;
            }
            default:
            {
                printf("Incorrect choice");
                break;
            }
        }
    }
}
Trie::node* Trie::getroot()
{
    return root;
}
//Method to insert a word into Trie
Trie::node* Trie::insert(char* word) 
{
  if (root==NULL)
  {
    root=getnode('\0');
  }
  node* temp = root;
  for (int i = 0; word[i] != '\0'; i++) 
  {
    int idx = (int)word[i] - 'a';
    if (temp->children[idx] == NULL)//Segmentation fault resolved by using the previous if condition
    {
      temp->children[idx] = getnode(word[i]);
    }
    temp = temp->children[idx];
  }

  temp->is_end = 1;
  return temp;
}
//Method to create a newnode
Trie::node* Trie::getnode(char data)
{
    node* newnode = (node*) malloc (sizeof(node));
    for (int i=0; i<N; i++)
    {
        newnode->children[i] = NULL;
    }
    newnode->is_end = 0;
    newnode->data = data;
    return newnode;
}
//Method to free the nodes 
void Trie::freenode(node* nnode) 
{
    if (nnode == NULL) 
    {
        return;
    }
    for(int i=0; i<N; i++) 
    {
        if (nnode->children[i] != NULL) 
        {
            freenode(nnode->children[i]);
            nnode->children[i] = NULL;

        }
    }
    free(nnode);
}
// Method to search for a word in the Trie
bool Trie::search(char* word) 
{
    if(root == NULL)//Segmentation fault of searching in empty trie resolved
    {
        printf("Empty TRIE\n");
        return false;
    }
    node* temp = root;
    temp = temp->children[(int)word[0]-'a'];
    if(temp==NULL)
    {
        return 0;
    }
    for(int i = 0; word[i] != '\0'; i++) 
    {
        if(temp==NULL)
        {
            return 0;
        }
        if(temp->data == word[i]) 
        {
            if (word[i+1] == '\0')
            {
                break;
            } 
            else 
            {
                temp = temp->children[(int)word[i+1]-'a'];
            }
        } 
        else 
        {
            return false;
        }
    }
    if (temp->is_end != 1) 
    {
        return false;
    }
    return true;
}

//Method to check if a node's children are empty(leaf node)
int Trie ::isempty(node* temp)
{
    for (int i = 0; i< N; i++)
    {
        if(temp ->children [i] != NULL )
        {
            return 0;
        }
    }
    return 1;
}
//Method to count length of word
int Trie:: word_len(char* word)
{
    int i =0 ;
    while(word[i] != '\0')
    {
        i++;
    }
    return i;
}
//Method to delete a word in trie
//Deletion helper function
bool Trie::delete_word(char* word)
{
    if(root == NULL || !search(word))//Segmentation fault of root being null resolved
    {
        return false;
    }
    node* temp = delete_rec(root,word,0);
    return true;
} 
//Deletion recursion function
Trie:: node* Trie::delete_rec(node* temp,char* word,int level)
{
    if(level == word_len(word))
    {
        if(temp ->is_end)
        {
            temp->is_end = 0;
        }
        if (isempty(temp))
        {
            free(temp);
            temp = NULL;//Segmentation fault resolved by assignig NULL
        }
        return temp;
    }
    int ind = word[level] -'a';
    temp -> children[ind]= delete_rec(temp ->children[ind],word,level+1);

    if(isempty(temp) && temp->is_end == 0)
    {
        free(temp);
        temp = NULL;
    }
    return temp;
}
//Method to pass root to freenode() method
void Trie::freenode_help()
{
    freenode(root);
}
