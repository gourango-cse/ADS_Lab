#include<stdio.h>
#include<string.h>
char txt[100],pat[100];
int M ,N ,lps[100],j=0,i=0;
void computeLPSArray()
{
  int len = 0, i;
  lps[0] = 0;
  i = 1;
  while(i < M)
  {
   if(pat[i] == pat[len])
   {
   len++;
   lps[i] = len;
   i++;
   }
   else
   {
   if( len != 0 )
     len = lps[len-1];
   else
   {
     lps[i] = 0;
     i++;
   }
   }
  }
}
void KMPSearch()
{
  int j=0,i=0;
  int found = 0; // Flag to track if the pattern is found
  M = strlen(pat);
  N = strlen(txt);
  
  computeLPSArray();
  while(i < N)
  {
  if(pat[j] == txt[i])
  {
    j++;
    i++;
  }

  if (j == M)
  {
    printf("Found pattern at index %d \n", i-j);
    j = lps[j-1];
   found = 1; // Set flag if pattern is found
  }
  
  else if(pat[j] != txt[i])
  {
    if(j != 0)
   j = lps[j-1];
    else
   i = i+1;
  }
  }
   if (!found)
  {
  printf("Pattern don't Match\n");
  }
}

int main()
{
 printf("\n ENTER THE TEXT    : ");
 scanf("%[^\n]%*c",txt);
 printf("\n ENTER THE PATTERN : ");
 scanf("%[^\n]%*c",pat);
 
 if(strlen(pat) == 0){
 
     printf("Pattern cannot be empty  \n");
     return 1;
 }
 
 KMPSearch();
 return 0;
}
