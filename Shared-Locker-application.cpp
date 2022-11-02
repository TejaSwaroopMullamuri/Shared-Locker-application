
#include<bits/stdc++.h>
using namespace std;
//prints the main operations of the program
void main_menu()
{
  cout<<"MAIN MENU"<<endl;
  cout<<"1.CONFIGURE"<<endl;
  cout<<"2.USE"<<endl;
  cout<<"3.EXIT"<<endl;
}
//prints the operations present in the configure module
void configure_menu()
{
  cout<<endl<<"CONFIGURE MODULE"<<endl;
  cout<<"1.Add new locker entry"<<endl;
  cout<<"2.Delete a locker entry"<<endl;
  cout<<"3.Return"<<endl;
}
//checks whether a number is prime or not
int is_prime(long long int L)
{
    if (L == 1) {
        return 0;
    }

    long long int n = 2;
    while (n*n<= L) {
        if (L% n == 0) {
            return 0;
        }
        n += 1;
    }
    return 1;
}
//generates k number of primes whose product is strictly greater than L
void construct_k_primes(vector<long long int>&v,int k,long long int L)
{
  long long int n=ceil(pow(L,1.0/k));
  cout<<n<<endl;
  while(k>0)
  {
    n=n+1;
    if(is_prime(n))
    {
        v.push_back(n);
        k--;
    }
  }

}
//compares characters in two strings and check whether both are same or not
int compare(char locker_id[],string line)
{
      int flag=0;
      if(line[0]==locker_id[0])
      {
        flag++;
      }
      if(line[1]==locker_id[1])
      {
        flag++;
      }
      if(line[2]==locker_id[2])
      {
        flag++;
      }
      if(line[3]==locker_id[3])
      {
        flag++;
      }
      if(line[4]==locker_id[4])
      {
        flag++;
      }
      if(flag==5)
      {
          return 1;
      }
      return 0;
}
//checks whether the entered lockerid is present in the textfile or not
int is_present(char locker_id[])
{
  fstream fin;
  fin.open("config.txt",ios::in);
  if(!fin)
  {
      fin.close();
      return 0;
  }
  string line;
  while(getline(fin,line))
  {
      int flag=compare(locker_id,line);
      if(flag==1)
      {
        fin.close();
        return 1;
      }
  }
  fin.close();
  return 0;
}
//calls the is_present function and if id is not present in the text file it adds the entry to the text file
void Add()
{
  char locker_id[5];
  int k;
  long long int L;
  cout<<"Enter Lockerid:";
  cin>>locker_id;
  if(is_present(locker_id))
    {
      cout<<"This locker id is already present"<<endl;
      return ;
    }
  cout<<"Enter Number of users:";
  cin>>k;
  cout<<"Enter the 10 digit Locker key L:";
  cin>>L;
  fstream fout;
  fout.open("config.txt",ios::app);
  vector<long long int>p;
  long long int u[k];
  construct_k_primes(p,k,L);
  fout<<locker_id<<" "<<k<<" ";
  for(int i=0;i<k;i++)
    fout<<p[i]<<" ";
  fout<<"\n";
  fout.close();
  for(int i=0;i<k;i++)
  {
  u[i]=L%p[i];
  if(u[i]==0)
    cout<<"0000"<<"  ";
  else if(u[i]/10==0)
    cout<<"000"<<u[i]<<"  ";
  else if(u[i]/100==0)
    cout<<"00"<<u[i]<<"  ";
  else if(u[i]/1000==0)
    cout<<"0"<<u[i]<<"  ";
  else
    cout<<u[i]<<"  ";

  }
}
//calls the is_present function and if id is present in the text file it deletes the id
void Delete()
{
  char locker_id[5];
  cout<<"Enter the locker id:";
  cin>>locker_id;
  fstream fp;
  fp.open("config.txt",ios::in);
  if(!fp)
  {
    cout<<"Deletion operation failed. No such file"<<endl;
    fp.close();
    return ;
  }
  if(!is_present(locker_id))
  {
    cout<<"This locker id is not present in the file"<<endl;
    cout<<"Deletion operation failed"<<endl;
    fp.close();
    return ;
  }
  fstream fp1;
  fp1.open("temp.txt",ios::out);
  string line;
  while(getline(fp,line))
  {
      if(!compare(locker_id,line))
          fp1<<line<<endl;
  }
  fp.close();
  fp1.close();
  remove("config.txt");
  rename("temp.txt","config.txt");
  cout<<"Deletion operation Successful...."<<endl;
}
//prints the opeartions present in the configure module and takes the choice as input
void configure()
{
  while(1)
  {
  configure_menu();
  int flag=0;
  cout<<"\n"<<"Mention your prefence(1/2/3):";
  int choice;
  cin>>choice;
  switch (choice)
  {
  case 1:
  {
    Add();
    break;
  }
  case 2:
  {
    Delete();
    break;
  }
  case 3:
  {
    cout<<"Back to main menu"<<endl;
    flag=1;
    break;
  }
  default:
  {
    cout<<"Try again. Enter a valid integer"<<endl;
    exit(1);
    break;
  }
  }
  if(flag==1)
  {
    break;
  }
  }
}
long long int find_L(vector<long long int>&p, long long int u[], int k)
{
    long long int L = 1;
    while (true)
    {
        int j;
        for (j=0; j<k; j++ )
            if (L%p[j] != u[j])
              break;
        // If all remainders are matched, we found L
        if (j == k)
            return L;
        L++;
    }
    return L;
}
/*checks whether the lockerid is present in the text file or not.If present it takes the secondary user keys as input and regenerate the key L.*/
void Use()
{
  char lockerid[5];
  cout<<"Enter Locker id:";
  cin>>lockerid;
  fstream fp;
  fp.open("config.txt",ios::in);
  if(!fp)
  {
    cout<<"Text has no data in it"<<endl;
    fp.close();
    return;
  }
  if(!is_present(lockerid))
  {
    cout<<"This lockerid is not present in the text file"<<endl;
    fp.close();
    return ;
  }
  string line;
  int line_count=1;
  while(getline(fp,line))
  {
      if(compare(lockerid,line))
          break;
      line_count++;
  }
  vector<long long int>v;
  int k=0;
  int i=6;
  while(line[i]!=' ')
  {
    k=k*10+(line[i]-'0');
    i++;
  }
  i++;
  int temp=0;
  while(line[i]!='\0')
  {
      if(line[i]!=' ')
      {
        temp=temp*10+(line[i]-'0');
      }
      else
      {
        v.push_back(temp);
          temp=0;
      }
      i++;
  }
  long long int u[k];
  cout<<"Enter the user keys in the respective order"<<endl;
  for(i=0;i<k;i++)
  {
    cout<<"key["<<i+1<<"]=";
    cin>>u[i];
  }
  long long int L=find_L(p,u, k);
  cout<<"The Locker key L for this lockerid is "<<L<<endl;
}
//main function
int main()
{
  //menu driven program
  while(1)
  {
    main_menu();
    cout<<"\n"<<"Mention your prefence(1/2/3):";
    int choice;
    cin>>choice;
    switch (choice)
  {
      case 1:
    {
      configure();
      break;
    }
    case 2:
    {
      Use();
      break;
    }
    case 3:
    {
      cout<<"Exited"<<endl;
      exit(1);
    }
    default:
    {
      cout<<"Try again. Enter a valid integer"<<endl;
      exit(1);
    }
  }
  }

  return 0;
}

