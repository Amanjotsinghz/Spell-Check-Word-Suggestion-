#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int found=0;

class small{
    public:
        class small* ptrs[230];
        string Word;
        char min;
        small(){
            for(int i=0;i<230;i++){
                ptrs[i]=NULL;
            }
            min=NULL;
            Word="";
        }
};

void insertword(string word,int pos,class small * under){
    if(word.length()==pos){
        under->Word=word;
        return;
    }
    if( under-> ptrs[word[pos]]==NULL ){
        small *newsmall;
        newsmall= new small;
        newsmall->min=word[pos];
        under->ptrs[word[pos]]=newsmall;
        insertword(word,pos+1,under->ptrs[word[pos]]);
    }
    else
        insertword(word,pos+1,under->ptrs[word[pos]]);
}

void find(string lock,int pos, class small * under){
    if((lock != under->Word) && (under->ptrs[lock[pos]] != NULL))
        find(lock,pos+1,under->ptrs[lock[pos]]);
    else if(lock==under->Word){
        cout<<"The spelling of the word '"<<under->Word<<"' is correct"<<endl;
        found=1;
    }
}

void no(class small * under){
    for(int i=0;i<230;i++)
        if(under->ptrs[i]!=NULL){
            no(under->ptrs[i]);
        }
    if(under->Word != "")
        cout<<" -> "<<under->Word<<endl;
}

void suggest(string lock,int pos, class small * under){
    if((lock != under->Word) && (under->ptrs[lock[pos]] != NULL)){
            suggest(lock,pos+1,under->ptrs[lock[pos]]);
    }
    else{
            no(under);
    }
}

int main(){
    ifstream in("dict.txt");
    string word,current="",lock;
    small *under;
    under = new small;
    while(in){
        in>>word;
        insertword(word,0,under);
    }
    in.close();
cout<<"                                   SPELL CHECK AND WORD SUGGESTION BY AMANJOT SINGH   "<<endl;
cout<<"Enter your word : ";
    cin>>lock;
    find(lock,0,under);
    if(!found){
        cout<<endl<<"No.....The spellings you entered are not correct, Possible suggestions are :"<<endl;
        suggest(lock,0,under);
    }
    return 0;
}
