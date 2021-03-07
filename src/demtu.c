#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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
  printf("%d ",head->data.count);
  printf("%s ",head->data.string);
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
int main(){
   int i=0,n;
  char buff[30];
  stop_w stop_arr[30];
   f = fopen("stopw.txt","r");
     while (fscanf(f, "%s", stop_arr[i].w) != EOF) {
      i++;
   }
   fclose(f);

 
  head=NULL;
  int line=0;
  char *str = (char *)malloc(sizeof(char) * 1000);
  f = fopen("vanban.txt","r");
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
            
            node * is_existed= search(head,token);  
            if(is_existed==NULL){ 
            //printf("Tu moi ");
             strcpy(data.string,token);
              data.line[0]=line;
              data.count=1;
            insert(&head,data);
            }
            else{
               for( int i=0;i<=30;i++){
                 if(is_existed->data.line[i]==line) break;
                 if(is_existed->data.line[i]==0){
                  // printf(" \t%d \n",line);
                    is_existed->data.line[i]=line;
                    break;
                 }
               }
               is_existed->data.count++;
            }
          memset(data.line,0,120);
          memset(data.string,0,120);    
            token = strtok(NULL, " ");
        }
    }
  fclose(f);
  inorder(head);
  freeTree(head);
  
}