#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

void output(string &s1,vector<int> &s2){
  
  
    int count = 0;
    string neww;
 
 
    int n = s1.length();
 
    // declaring character array
    char c[n + 1];
    char ch[n + 1];
    
    // copying the contents of the string to char array
    strcpy(c, s1.c_str());
    
 

 //decreapting
    for(int i = 0;i<s1.length();i++){
        
    
        if((c[i]>='A' && c[i]<='Z') || (c[i]>='a' && c[i]<='z') ){
      
        int position = i + (s2[count]);
        ch[position] = c[i];
       
       
        count++;
        
        
      
        }
        else{
        ch[i] = s1[i];    
        
        }
    
  }
  
     cout<<"output:\n";
     for (int i = 0; i < n; i++)
        cout << ch[i];
  
}



int main(){
    
    vector<string> listTEXT ;
    vector<int> listNUMS;
    int lines;
    string encreapted;
    int counter = 0;
    //канча линия
    
    cin>>lines;
    
    //encreapted text cin болот плюс вектордун ичине салып салабыз
    for(int i = 0;i<(lines);i++){
    
    
    cin>>ws;
    getline (cin, encreapted);
    listTEXT.push_back(encreapted);
   
  }
  
  //текстВектордун элементтерин в стринг впихиваем
    string newS;
    for(int i =0;i<listTEXT.size();i++){
    newS = listTEXT[i];
    }
    
    
    
   int s = newS.size();
   for(int j = 0;j<s;j++){
       
      if((newS[j]>='a' && newS[j]<='z') || (newS[j]>='A' && newS[j]<='Z') ){
          
          counter++;
      }
      else{
          continue;
      }
  }
    
    
    
    for(int i = 0;i<counter;i++){
    string numbers;
    int num;
    
    cin>>num;
    listNUMS.push_back(num);
  }
        

    
    output(newS,listNUMS);
    
    
    
    
    
    
    
    
    return 0;
}