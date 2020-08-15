/* source - https://github.com/rashup/Porters-Stemming-Algorithm/blob/master/PorterStemming.cpp
*/
#include<bits/stdc++.h>
using namespace std;

static int k0,k;
static char *b;
char temp[20];
char add_array[5];
static int parameter;

/*Function to check individually for consonants and vowels.
Vowels here are: a,e,i,o,u and y preceded by a consonant.
k0 here is the first element.
*/

int cons(char a[],int i)
{
    switch (a[i])
    { case 'a': case 'e': case 'i': case 'o': case 'u': return 0;
    case 'y': {if (i==k0) return 1; else !cons(a,i-1);}
    default: return 1;
    }
}


/*
If C- consonant sequence (c,cc,ccc,ccc,..)
V- vowel sequence (v, vv, vvv,...)
This function m() gives the count of (VC) formed.
Example
m=0 TR, EE, TREE, Y, BY.
m=1 TROUBLE, OATS, TREES, IVY.
m=2 TROUBLES, PRIVATE, OATEN, ORRERY.
*/

int m(char a[],int j,int k)
{
    int n = 0;
    int r = k0;
    int flag;
    int c=0;
    int v=0;
    int value1=0;
    int value2=0;
    int value=0;
    int loop=0;
    while (1)
    {

        while(r<=k)
        {
            {

                if (r > j) break;
                if (! cons(a,r)) {c++; value1=1; break;} /*checks for vowel*/
                r++;
            }
            if (value1==1) break;
        }
        value1=0;
        r++;


        while(r<=k)
        {
            {

                if (r > j) break;
                if (cons(a,r)) {v++; value2=1; break;} /*checks for consonant*/
                r++;
            }
            if (value2==1) break;
        }
        value2=0;
        r++;
        if ((c==v)&&(r<=k+1))
        {

            value=value+1;c=0;v=0; /*counts the number of VC sequences*/
        }
        if (r>k) break;
    }

    return value; /*returns the value of VC count found out*/

}

/*checks in a word, if it has a vowel*/

int vowelinstem(char a[],int j)
{

    int last_w=j;
    int i;
    for (i = k0; i <= last_w; i++) if (! cons(a,i)) return 1;
    return 0;
}


/*checks for double consonants. Checks for the last position and the last but one-th position. Of the form say -ss */

int doublec(char a[],int j)
{
    int last_w=j;
    if (j < k0+1) return 0;
    if (a[j] != a[j-1]) return 0;
    return cons(a,j);
}

/*Checks for the form CVC*/

int cvc(int i,char a[],int j)
{

    if (i <= k0+2)
    {
        if (!cons(a,i) || cons(a,i-1) || !cons(a,i-2))
        {
            int ch = a[i];
            if (ch == 'w' || ch == 'x' || ch == 'y') return 0; /* In CVC, the last C should not be w,x,y as per the algo.*/
        }
    }
    return 1;
}


/* Readjusts the string as per requirement. Adds new suffixes or changes to different forms as required.*/

void setto(int len_inc,char *add,char a[])
{
    // cout<<"\nI am here now";
    int len3=len_inc;
    if (parameter==1)
    {
        char temp1[15];
        memset(temp1,0,sizeof(temp1)); /*setting temp1 to null*/
        memcpy(temp1,a,k+1); /*copying the contents of array a till the parameter k passed into temp1*/
        memset(a,'\0',sizeof(a)); /*setting a to null. Basically to remove out the junk values when used later in the func*/
        strcpy(a,temp1); /*Copying temp1 to a*/
        //cout<<a;
        parameter=0;
    }
    k+=len_inc;
    strcat(a,add); /*Concatenating the suffix passed. Eg:pon(a)+i(add)=poni(a)*/
    char temp[15];
    memset(temp,0,sizeof(temp));
    memcpy(temp,a,k+1);
    memset(a,0,sizeof(a));
    memcpy(a,temp,k+1);
    return;
}

/*This part matches the suffix passed and checks if the suffix is present in the word*/

int ends(char a[],char * s,int length, int j)
{
    int last_w;
    int len=length;
    int pos=k-length+1;
    char temp[20];
    memset(temp,0,sizeof(temp));
    for(int m=0;m<=len-1;m++)
            {

        temp[m]=a[pos];
        pos++;
        }
    int r;
    if ((r=strcmp(s,temp))==0){return 1;} /*Compares and returns 1 if suffix found.*/
    else
        return 0;

}


/* step1ab() gets rid of plurals and -ed or -ing. e.g.

caresses -> caress
ponies -> poni
ties -> ti
caress -> caress
cats -> cat

feed -> feed
agreed -> agree
disabled -> disable

matting -> mat
mating -> mate
meeting -> meet
milling -> mill
messing -> mess

meetings -> meet

*/


void step1ab(char a[],int j)
{ //cout<<"Enter 1AB";
    int last_w=j;
    int h=0;
    if (a[k] == 's')
    {
        if (ends(a,"sses",4,last_w)==1) { k-= 2;} else
            if (ends(a,"ies",3,last_w)==1) { k-=3;setto(1,"i",a);} else
                if (a[k-1] != 's') {k--;return;}
    } else
        if (ends(a,"eed",3,last_w)==1) {if (m(a,last_w,k)>1)k--;} else
            if ((ends(a,"ed",2,last_w)==1)||(ends(a,"ing",3,last_w)==1))
            {
                if ((ends(a,"ed",2,last_w)==1)&&vowelinstem(a,last_w)) { k-=2;}
                if ((ends(a,"ing",3,last_w)==1)&&vowelinstem(a,last_w)) {k-=3;}
                j=k;
                
                if (ends(a,"at",2,j)==1) { k-=2;setto(3,"ate",a);} else
                    if (ends(a,"bl",2,j)==1) { k-=2;setto(3,"ble",a);} else
                        if (ends(a,"iz",2,j)==1) { k-=2;setto(3,"ize",a);} else
                            if (doublec(a,k) ) { k--; {int ch=a[k]; if (ch == 'l' || ch == 's' || ch == 'z') k++;}}
            }
            if((ends(a,"at",2,j)==1) && (ends(a,"bl",2,j)==1) && (ends(a,"iz",2,j)==1))
            {
            if (m(a,j,k) == 1 && cvc(k,a,0)) {parameter=1;setto(1,"e",a);}
            }
            return;
}

/*turns terminal y to i when there is another vowel in the stem. */

void step1c(char a[]) {
     //cout<<"Enter 1C";
     //cout<<k;
     
if (ends(a,"y",1,k) && vowelinstem(a,k))
{ parameter=1;
    k-=1;
    setto(1,"i",a);
}}

 
 /* step2() maps double suffices to single ones. so -ization ( = -ize plus
-ation) maps to -ize etc. note that the string before the suffix must give
m() > 0. */

void step2(char a[],int j) {

    if ((m(a,j,k)>0)){
        switch (a[k-1])
        {

        case 'a': if (ends(a,"ational",7,k)) {k-=7; parameter=1;cout<<"The value is "<<" "<<k; setto(3,"ate",a); break; }
                  if (ends(a,"tional",6,k)) {k-=6;setto(4,"tion",a); break; }
                  break;
        case 'c': if (ends(a,"enci",4,k)) { k-=4;parameter=1;setto(4,"ence",a); break; } else
                      if (ends(a,"anci",4,k)) { k-=4;parameter=1;setto(4,"ance",a); break; }
                      break;
        case 'e': if (ends(a,"izer",4,k)) {{k-=4;parameter=1;setto(3,"ize",a); break; }}
                  break;
        case 'l': if (ends(a,"bli",3,k)) {k-=3;parameter=1;setto(3,"ble",a); break; }
                  if (ends(a,"eli",3,k)) {k-=3;setto(1,"e",a); break; }
                  if (ends(a,"alli",4,k)) {k-=4;parameter=1;setto(2,"al",a); break; }
                  if (ends(a,"entli",5,k)) {k-=5;parameter=1;setto(3,"ent",a); break; }
                  if (ends(a,"ousli",5,k)) {k-=5;parameter=1;setto(3,"ous",a); break; }
                  break;
        case 'o': if (ends(a,"ator",4,k)) { k-=4;parameter=1;setto(3,"ate",a); break; }
                  if (ends(a,"ization",7,k)) { k-=7;parameter=1;setto(3,"ize",a); break; }
                  if (ends(a,"ation",5,k)) {k-=5;parameter=1;setto(3,"ate",a); break; }
                  break;
        case 's': if (ends(a,"alism",5,k)) { k-=5;parameter=1;setto(2,"al",a); break; }
                  if (ends(a,"iveness",7,k)) { k-=7;parameter=1;setto(3,"ive",a); break; }
                  if (ends(a,"fulness",7,k)) { k-=7;parameter=1;setto(3,"ful",a); break; }
                  if (ends(a,"ousness",7,k)) { k-=7;parameter=1;setto(3,"ous",a); break; }
                  break;
        case 't': if (ends(a,"aliti",5,k)) { k-=5;parameter=1;setto(2,"al",a); break; }
                  if (ends(a,"iviti",5,k)) { k-=5;parameter=1;setto(3,"ive",a); break; }
                  if (ends(a,"biliti",6,k)) { k-=6;parameter=1;setto(3,"ble",a); break; }
                  break;
        case 'g': if (ends(a,"logi",4,k)) { k-=4;parameter=1;setto(3,"log",a); break; }

        } }}
        
/* step3() deals with -ic-, -full, -ness etc. similar strategy to step2. */

void step3(char a[],int j) {
    if (m(a,j,k)>0){
        switch (a[k])
        {

        case 'e': if (ends(a,"icate",5,k)) { k-=5;parameter=1;setto(2,"ic",a); break; }
                  if (ends(a,"ative",5,k)) { k-=5;parameter=1;setto(0," ",a); break; }
                  if (ends(a,"alize",5,k)) { k-=5;parameter=1;setto(2,"al",a); break; }
                  break;
        case 'i': if (ends(a,"iciti",5,k)) { k-=5;parameter=1;setto(2,"ic",a); break; }
                  break;
        case 'l': if (ends(a,"ical",4,k)) { k-=4;parameter=1;setto(2,"ic",a); break; }
                  if (ends(a,"ful",3,k)) { k-=3;parameter=1;setto(0," ",a); break; }
                  break;
        case 's': if (ends(a,"ness",4,k)) { k-=4;parameter=1;setto(0,"",a); break; }
                  break;
        } }}


/* step4() takes off -ant, -ence etc., in context <c>vcvc<v>,i.e. m()>1. */

void step4(char a[],int j)
{ if ((m(a,j,k)>1))
{ switch (a[k-1])
{ case 'a': if (ends(a,"al",2,k)) {k-=2;parameter=1;setto(0," ",a);return;}
       case 'c': if (ends(a,"ance",4,k)){k-=4;parameter=1;setto(0," ",a);return;}
                 if (ends(a,"ence",4,k)){k-=4;parameter=1;setto(0," ",a);return;}
       case 'e': if (ends(a,"er",2,k)) {k-=2;parameter=1;setto(0," ",a);return;}
       case 'i': if (ends(a,"ic",2,k)){k-=2;parameter=1;setto(0," ",a);return;}
       case 'l': if (ends(a,"able",4,k)){k-=4;parameter=1;setto(0," ",a);return;}
                 if (ends(a,"ible",4,k)){k-=4;parameter=1;setto(0," ",a);return;}
       case 'n': if (ends(a,"ant",3,k)) {k-=3;parameter=1;setto(0," ",a);return;}
                 if (ends(a,"ement",5,k)){k-=5;parameter=1;setto(0," ",a);return;}
                 if (ends(a,"ment",4,k)) {k-=4;parameter=1;setto(0," ",a);return;}
                 if (ends(a,"ent",3,k)) {k-=3;parameter=1;setto(0," ",a);return;}
       case 'o': if (ends(a,"ion",3,k) && (a[k-3] == 's' || a[k-3] == 't')){k-=3;parameter=1;setto(0," ",a);return;}
                 if (ends(a,"ou",2,k)) {k-=2;parameter=1;setto(0," ",a);return;}
       case 's': if (ends(a,"ism",3,k)) {k-=3;parameter=1;setto(0," ",a);return;}
       case 't':
           if (ends(a,"ate",3,k)) {k-=3;parameter=1;setto(0," ",a);return;} //========================discuss
           if (ends(a,"iti",3,k)) {k-=3;parameter=1;setto(0," ",a);return;}
       case 'u': if (ends(a,"ous",3,k)) {k-=3;parameter=1;setto(0," ",a);return;}
       case 'v': if (ends(a,"ive",3,k)) {k-=3;parameter=1;setto(0," ",a);return;}
       case 'z': if (ends(a,"ize",3,k)) {k-=3;parameter=1;setto(0," ",a);return;}
       default: return;
}
if (m(a,j,k) > 1) j=k;
}}

/* step5() removes a final -e if m() > 1, and changes -ll to -l if
m() > 1. */

void step5(char a[],int j)
{
    j = k;
    if (a[k] == 'e')
    { int x = m(a,j,k);
    if (x > 1 ){k--;} else
        if ((x == 1) && !cvc(k-1,a,0)) k--;
    }
    if (m(a,j,k) > 1)
    {
        if (doublec(a,k))
        {
            if (a[k] == 'l') k--;
        }
    }
}

/*Initialisatin and calls all 5 steps. */

int stem(char a[], int i, int j)
{
    k = j; k0 = i; /* copy the parameters into statics */
    if (k <= k0+1) return k;
    step1ab(a,j);
    step1c(a); step2(a,j);
    step3(a,j);
    step4(a,j);
    step5(a,j);

    return k;
}
string lowercase(string data){
    transform(data.begin(), data.end(), data.begin(),
    [](unsigned char c){ return std::tolower(c); });
    return data;
}
string portstem(string data){
    // data-> input string
    int iCount = -1 ;
    int n = data.length();
    char a [n+1];
    strcpy(a,data.c_str());
    iCount = strlen(a) ;
    //j = j-1;
    --iCount ;
    a[stem(a,0,iCount)+1] = 0;
    data = a;
    return data;
}