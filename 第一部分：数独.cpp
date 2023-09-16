#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

struct stu{
    int li;
    int ro;
    int num;
	int ** noc;
};

//检查数独第line行中是否有数字k，若有，则回传false；，否则回传true。
bool notinthisline(int a[9][9],int line,int k){
    for(int i=0;i<9;i++){
        if(a[line][i]==k)return false;
    }
    return true;
}

//检查数独第row列中是否有数字k，若有，则回传false；，否则回传true。
bool notinthisrow(int a[9][9],int row,int k){
    for(int i=0;i<9;i++){
        if(a[i][row]==k)return false;
    }
    return true;
}

//检查数独同一个九宫格中是否有数字k，若有，则回传false；，否则回传true。
bool notinnine(int a[9][9],int line,int row,int k){
    for(int i=line/3*3;i<=line/3*3+2;i++){
        for(int j=row/3*3;j<=row/3*3+2;j++){
            if(a[i][j]==k)return false;
        }
    }
    return true;
}

//根据目前数独的情况，确定出可填数字最少的格子，并回传对应的行和列。
void getlocal(int a[9][9],int & li,int & ro){
//	cout<<"haha"<<endl;
	bool c[9][9][9];
	int min=-1,mint=0;
	int i,j,n,m;
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			for(n=0;n<9;n++)
			c[i][j][n]=true;

	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			if(a[i][j]!=-1){
				for(n=0;n<9;n++){
					c[i][j][n]=false;						
					c[n][j][a[i][j]-1]=false;					
					c[i][n][a[i][j]-1]=false;	
				}
				for(n=i/3*3;n<=i/3*3+2;n++)
					for(m=j/3*3;m<=j/3*3+2;m++)
					c[n][m][a[i][j]-1]=false;
			}
		for(i=0;i<9;i++)
				for(j=0;j<9;j++)
					if(a[i][j]==-1){						
						for(n=0;n<9;n++) {
						if(c[i][j][n]!=false)
							mint++;
						}
						if(min==-1||mint<min){
							li=i;
							ro=j;
							min=mint;
						}
						mint=0;
					}
}


int main(){
	char fn[100];
	cin>>fn;
	freopen(fn,"r",stdin);
    int a[9][9];
	int i,j,n,m,num=0;
    stu lastadd[81];
    int index=-1;
    int k=1;
    bool add=false,judge=true;
	//string s="....1..548.................65.4..........273..........21....8..7.....3.....35....";
	int p;
	cin>>p;
	
	//输入
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
			char tmp;
			cin>>tmp;
            if(tmp=='.')
            a[i][j]=-1;
            else {
				num++;
				a[i][j]=int(tmp-48);
				
			}
        }
    }

		i=-1;
		j=-1;


		//开始填格
		while(num!=81){	

			if(i==-1&&j==-1) getlocal(a,i,j);

            add=false;
                for(k;k<=9;k++){//k不需要赋初值，否则会出现死循环。
                    if(notinthisline(a,i,k)&&notinthisrow(a,j,k)&&notinnine(a,i,j,k)){
                        a[i][j]=k;
                        add=true;
                        index++;
						//cout<<"haha"<<endl;
                        lastadd[index].li=i;
                        lastadd[index].ro=j;
                        lastadd[index].num=k;
						i=-1;
						j=-1;
                        k=1;
						num++;
                        break;										
                    }
                }
							 
                if(add==true)continue;
                else{//回溯。
                    i=lastadd[index].li;
                    j=lastadd[index].ro;
                    a[i][j]=-1;
                    k=lastadd[index].num+1;
                    index--;                   
					num--;
                }
            
        }
    

		//输出
		if(p==1){//cout<<num<<endl;
			for(i=0;i<9;i++){
				for(j=0;j<9;j++){
					cout<<a[i][j]<<" ";
				}
			 cout<<endl;
			}
		}
		else{
			for(i=0;i<9;i++){
				for(j=0;j<9;j++)
					cout<<a[i][j];
			}
		}
}
