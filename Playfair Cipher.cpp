#include<bits/stdc++.h>
using namespace std;
#define size 30

void removeUpperCase(char text[]){
    for(int i=0;i<strlen(text);i++){
        if(text[i]>=65 && text[i]<=90){
            text[i]=text[i]+32;
        }
    }
}

int removeSpaces(char text[]){
    int count=0;
    for(int i=0;i<strlen(text);i++){
        if(text[i]!=' '){
            text[count]=text[i];
            count++;
        }
    }
    text[count]='\0';
    return count;
}

int prepare(char text[],int l){
    if(l%2!=0){
        text[l++]='z';
        text[l]='\0';
    }
    return l;
}

void generateKeyTable(char key[],int keylength,char keyT[5][5]){
    int i,j,k,flag;
    int dict[26]={0};
    //for every corresponding alphabet in key, dict[value]=2 (EXCEPT J)
    for(int i=0;i<keylength;i++){
        if(key[i]!='j'){
            dict[key[i]-97]=2;
        }
    }
    dict['j'-97]=1;//Count of j=1
    
    i=0;
    j=0;
    for(int k=0;k<keylength;k++){
        if(dict[key[k]-97]==2){
            dict[key[k]-97]-=1;
            keyT[i][j]=key[k];
            j++;
            if(j==5){
                i++;
                j=0;
            }
        }
    }
    
    //fill rest of the matrix
    for(int k=0;k<26;k++){
        if(dict[k]==0){
            //IMPORTANT NEXT LINE
            keyT[i][j]=char(k+97);
            j++;
            if(j==5){
                i++;
                j=0;
            }
        }
    }
}

void search(char keyT[5][5],char x,char y,int a[]){
    if(x=='j'){
        x='i';
    }
    else if(y=='j'){
        y='i';
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(keyT[i][j]==x){
                a[0]=i;
                a[1]=j;
            }
            else if(keyT[i][j]==y){
                a[2]=i;
                a[3]=j;
            }
        }
    }
}

int mod5(int a){
    return a%5;
}

void encrypt(char str[],char keyT[5][5],int stringlength){
    int a[4];
    int row,col;
    for(int i=0;i<stringlength;i+=2){
        search(keyT,str[i],str[i+1],a);
        
        //same row
        if(a[0]==a[2]){
            str[i] = keyT[a[0]][mod5 (a[1] + 1)];
		    str[i + 1] = keyT[a[0]][mod5 (a[3] + 1)];
        }
        //same column
        else if(a[1]==a[3]){
            str[i] = keyT[mod5 (a[0] + 1)][a[1]];
		    str[i + 1] = keyT[mod5 (a[2] + 1)][a[1]];
        }
        //diff row,diff column
        else{
            str[i]=keyT[a[0]][a[3]];
            str[i+1]=keyT[a[2]][a[1]];
        }
    }
}

void encryptByPlayFair(char str[],char key[]){
    int stringlength=strlen(str);
    int keylength=strlen(key);
    char keyT[5][5];
    
    removeUpperCase(str);
    stringlength=removeSpaces(str);
    removeUpperCase(key);
    keylength=removeSpaces(key);
    
    stringlength=prepare(str,stringlength);
    generateKeyTable(key,keylength,keyT);
    encrypt(str,keyT,stringlength);
}

int main(){
    char str[size],key[size];
    strcpy(str,"Nishtha");
    strcpy(key,"Monarchy");
    cout<<"Key is: "<<key<<" and String is: "<<str<<"\n";
    encryptByPlayFair(str,key);
    cout<<"Cipher Text is: "<<str;
}