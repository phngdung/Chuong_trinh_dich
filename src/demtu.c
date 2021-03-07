#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
FILE *f, *output;
typedef struct word
{
    char string[30];
    int line[30];
    int count;
} word;
word data;
typedef struct node{
     word data;
  struct node *left, *right;
}node;
node *head;
void makenewnode(node** head,word data){
  (*head)=(node*)malloc(sizeof(node));
  (*head)->left=(*head)->right=NULL;
  (*head)->data=data;
}
void *insert(node **head, word data)
{
  if((*head)==NULL)
    {
    makenewnode(&(*head),data);
    makenewnode(&(*head),data);
    }
  else if(strcmp(data.string,(*head)->data.string)<0)
    insert(&(*head)->left,data);
  else if(strcmp(data.string,(*head)->data.string)>0)
    insert(&(*head)->right,data);
    else return;
}
void inorder(node* head){
  if(head == NULL) return;
  inorder(head->left);
  printf("%s ",head->data.string);
  printf("%d ",head->data.count);
   for( int i=0;head->data.line[i]!=0;i++){
  printf("%d ",head->data.line[i]);}
  printf("\n");
  inorder(head->right);
}
node* search(node *head, char string[]){
    if(head == NULL) return;
    if(strcmp(head->data.string,string)==0) return head;
    if(strcmp(head->data.string,string)>0) return search(head->left,string);
    else return search(head->right,string);
}
void freeTree(node *head)                                     
{
  if( head == NULL ) return;
  freeTree(head->left);
  freeTree(head->right);
  free(head);
  
}
typedef struct stop_w
{
    char w[30];
} stop_w;
 stop_w stop_arr[30];
bool is_topw( char string[]){
  for( int i=0;i<30;i++){
          if(strcmp(stop_arr[i].w,string)==0)
              return true;
        }
    return false;
}
void lower(char a[])
{
    for (int i = 0; i < strlen(a); i++)
    {
        a[i] = tolower(a[i]);
    }
}
bool is_alpha(char a[]){
  for (int i = 0; i < strlen(a); i++)
    {
        if(!isalpha(a[i])) return 0;
    }
    return 1;
}
int main(){
   int i=0,n;
  char buff[30];
   f = fopen("stopw.txt","r");
     while (fscanf(f, "%s", stop_arr[i].w) != EOF) {
      i++;
   }
   fclose(f);
  head=NULL;
  int line=0;
  char *str = (char *)malloc(sizeof(char) * 1000);
  f = fopen("alice30.txt","r");
while (fgets(str, 1000, f) != NULL)
    {
        if (strcmp(str, "\r\n") == 0)
        {
            line++;
            continue;
        }
        line++;
        char *token = strtok(str, " ");
        while (token != NULL)
        {
            
            if (strcmp(token, "\r\n") == 0 || strcmp(token, "\n") == 0 || strcmp(token, "\r") == 0 || strcmp(token, "*") == 0)
                break;
            while (!isalpha(token[0]) && !isdigit(token[0]))
            {
                for (int i = 0; i < strlen(token); i++)
                {
                    token[i] = token[i + 1];
                }
            }
            int a = strlen(token) - 1;
            while (!isalpha(token[a]) && !isdigit(token[a]))
            {
                token[a] = '\0';
                a--;
            }
            lower(token);
         if(!is_topw(token)&& is_alpha(token))
         {
           node * is_existed= search(head,token);  
            if(is_existed==NULL){ 
             strcpy(data.string,token);
              data.line[0]=line;
              data.count=1;
            insert(&head,data);
            }
            else{
               for( int i=0;i<=30;i++){
                 if(is_existed->data.line[i]==line) break;
                 if(is_existed->data.line[i]==0){
                    is_existed->data.line[i]=line;
                    break;
                 }
               }
               is_existed->data.count++;
            }
         }
        token = strtok(NULL, " ");
        }
    }
  fclose(f);
  inorder(head);
  freeTree(head);
  
}