#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
  
  vector <int> vSize;
  vector <int> vPosition;
  vector <int> vKey;
  int numOfDisks;
  
  cout<<"number of disks: \n";
  cin>>numOfDisks;
  //num of disks
  for(int i = 0;i<numOfDisks;i++){
    int c;
    cin>>c;
    vSize.push_back(c);
    
  }
  
  //position of disks
  for(int i = 0;i<numOfDisks;i++){
    int pos;
    cin>>pos;
    vPosition.push_back(pos);
  }
  
  //the key of disks
  for(int i = 0;i<numOfDisks;i++){
    int k;
    cin>>k;
    vKey.push_back(k);
  }

  int counter = 0;
  vector <int> neww;
  for(int i = 0;i<numOfDisks;i++){
    neww[i] = 1;
  }
  //4 5 3 size
  //1 3 3 -> 4 1 3
  while (vPosition != vKey)
  {
    for (int i = 0; i < vSize.size(); i++)
    {
      if(vPosition[i]>vSize[i]){
        vPosition[i] = neww[i];
      }
      else{
        vPosition[i] = vPosition[i] + 1;
      }
      
    }
    counter=counter + 1;
  }
  
  
  cout<<"result is:  "<<counter<<endl;
  
  return 0;
}
