#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>

//��ر���
int p;
int lineofnum;
int rowofnum;
int lineofge;
int rowofge;
int lengthOftemp;
int **num;
int **ge;
bool** charge;
double** opportunity;

using namespace std;

//��Ҫ�õ�����

//���
template <class T>
struct Node
{
    T data;
    Node<T> *next;
};

//����
template <class T>
class LinkList
{
private:
    Node<T> *first, *last;
public:
    LinkList()
    {
        first = new Node<T>;
        first->next = NULL;
        last = first;
    }

    LinkList(T a[], int n)  //tail insertion style
    {
        Node<T>* r, *s;
        first = new Node<T>;
        r=first;
        for(int i=0; i<n; i++)
        {
            s = new Node<T>;
            s->data = a[i];
            r->next = s;
            r = s;
        }
        r->next = NULL;
        last = r;
    }

    ~LinkList()
    {
        Node<T> *q = NULL;
        while(first!=NULL)
        {
            q=first;
            first=first->next;
            delete q;
        }
    }

    void Insert(int i, T x)
    {
        Node<T> *p = first, *s = NULL;
        int count = 0;
        if(i<=0)
            throw "Bad index";
        while(p!=NULL && count < i-1)  //seek (i-1)-th point
        {
            p = p-> next;
            count++;
        }
        if(p==NULL)
            throw "Bad index";
        else
        {
            s = new Node<T>;
            s->data = x;
            s->next = p->next;
            p->next = s;
            if(s->next==NULL)
                last=s;
        }
    }

    void InsertLast(T x)
    {
        Node<T> *s = NULL;
        s = new Node<T>;
        s->data = x;
        s->next = NULL;
        last->next = s;
        last = s;
    }

    T Delete(int i)
    {
        Node<T> *p = first, *q = NULL;
        T x;
        int count=0;
        if(i<=0)
            throw "Bad index";
        while(p!=NULL && count < i-1)  //seek (i-1)-th point
        {
            p = p-> next;
            count++;
        }
        if(p==NULL || p->next == NULL)
            throw "Bad index";
        else
        {
            q=p->next;
            x=q->data;
            p->next = q->next;
            if(last==q)
                last=p;
            delete q;
            return x;
        }
    }

    int Locate(T x)
    {
        Node<T> *p = first->next;
        int count=1;
        while(p!=NULL)
        {
            if(p->data == x)
            {
                return count;
            }
            p = p->next;
            count++;
        }
        return 0;
    }

    void printList()
    {
        //print all the elements in this list, but will not give an "endl" at the end.
        Node<T> *p = first->next;
        while(p!=NULL)
        {
            cout << p->data << " ";
            p = p->next;
        }
    }

    T Get(int i)
    {
        Node<T> *p = first;
        int count=0;
        if(i<=0)
            throw "Bad index";
        while(p!=NULL && count < i)  //seek i-th point
        {
            p = p-> next;
            count++;
        }
        if(p==NULL)
            throw "Bad index";
        return p->data;
    }
};

//����
template <class T>
class LinkQueue
{
private:
    int length;
    LinkList<T> q;
public:
    LinkQueue()
    {
        length = 0;
    }
    ~LinkQueue()
    {

    }
    void EnQueue(T x)
    {
        q.InsertLast(x);
        length++;
    }
    T DeQueue()
    {
        if(length==0)
            throw "Queue Empty";
        length--;
        return q.Delete(1);
    }
    T PeekQueue()
    {
        if(length==0)
            throw "Queue Empty";
        return q.Get(1);
    }
    bool IsEmpty()
    {
        return (length==0);
    }
    void PrintQueue()
    {
        cout << "Front of queue: ";
        q.printList();
        cout << "end of queue" << endl;
    }
};
struct fangge
{
    int li;
    int ro;
};
struct fangge1
{
    int li;
    int ro;
    int data;
};
//����±��Ƿ�Խ�磬��ûԽ��ش�1������ش�0��
int helper(int i,int j)
{
    if(i>=0&&i<lineofnum-1&&j>=0&&j<rowofnum-1)
        return 1;
    else
        return 0;
}
//����Ŀǰ�ж��ٸ������Ǵ����ġ�����ʱû�б�Ϳ�ɰ׸���ߺڸ񡣣�
int getNumOfGrayge(int i,int j)
{
    int count=0;
    if(helper(i,j)&&!charge[i][j])
        count++;
    if(helper(i,j-1)&&!charge[i][j-1])
        count++;
    if(helper(i-1,j)&&!charge[i-1][j])
        count++;
    if(helper(i-1,j-1)&&!charge[i-1][j-1])
        count++;
    return count;
}
//����Ŀǰ�ж��ٸ������Ǳ�Ϳ�ڵġ�
int getNumOfBlack(int i,int j)
{
    int count=0;
    if(helper(i,j)&&charge[i][j]&&opportunity[i][j]==1)
        count++;
    if(helper(i,j-1)&&charge[i][j-1]&&opportunity[i][j-1]==1)
        count++;
    if(helper(i-1,j)&&charge[i-1][j]&&opportunity[i-1][j]==1)
        count++;
    if(helper(i-1,j-1)&&charge[i-1][j-1]&&opportunity[i-1][j-1]==1)
        count++;
    return count;
}
//����Ŀǰ�ж��ٸ������Ǳ�Ϳ�ڻ���Ϳ�׵ġ�
int getNumOfBlackOrWhite(int i,int j){
    int count=0;
    if(helper(i,j)&&charge[i][j])
        count++;
    if(helper(i,j-1)&&charge[i][j-1])
        count++;
    if(helper(i-1,j)&&charge[i-1][j])
        count++;
    if(helper(i-1,j-1)&&charge[i-1][j-1])
        count++;
    return count;
}

//���룬����ʼ��������ݡ�

void initial()
{
    int numberofgray,i,j;
    cin>>lineofnum>>rowofnum;
    lineofge=lineofnum-1;
    rowofge=rowofnum-1;
    numberofgray=lineofge*rowofge;
    num=new int*[lineofnum];
    for(i=0; i<lineofnum; i++)
    {
        num[i]=new int[rowofnum];
    }
    int **blackofnum=new int*[lineofnum];
    for(i=0; i<lineofnum; i++)
    {
        blackofnum[i]=new int[rowofnum];
        for(int j=0; j<rowofnum; j++)
            blackofnum[i][j]=0;
    }
    ge=new int*[lineofge];
    for(i=0; i<lineofge; i++)
    {
        ge[i]=new int[rowofge];
        for(int j=0; j<rowofge; j++)
            ge[i][j]=0;               //0��ʾ�Ҹ�δ���1��ʾ�ڸ�,-1��ʾ���ܶ��İ׸�
    }
    for(i=0; i<lineofnum; i++)
    {
        for(j=0; j<rowofnum; j++)
        {
            char tmp;
            cin>>tmp;
            if(tmp=='-')
                num[i][j]=-1;
            else
                num[i][j]=int(tmp-48);
        }
    }
    opportunity=new double*[lineofge];
    charge=new bool*[lineofge];
    for(i=0; i<lineofge; i++)
    {
        opportunity[i]=new double[rowofge];
        charge[i]=new bool[rowofge];
        for(j=0; j<rowofge; j++)
        {
            opportunity[i][j]=0;
            charge[i][j]=false;
        }
    }
    //Case1:num=0&&num=numofge;
    for(i=0; i<lineofnum; i++)
    {
        for(j=0; j<rowofnum; j++)
        {
            if(num[i][j]==0)
            {
                if(helper(i,j))
                {
                    opportunity[i][j]=-1;
                    charge[i][j]=true;
                }
                if(helper(i-1,j))
                {
                    opportunity[i-1][j]=-1;
                    charge[i-1][j]=true;
                }
                if(helper(i,j-1))
                {
                    opportunity[i][j-1]=-1;
                    charge[i][j-1]=true;
                }
                if(helper(i-1,j-1))
                {
                    opportunity[i-1][j-1]=-1;
                    charge[i-1][j-1]=true;
                }
            }
            int count;
            count=helper(i,j)+helper(i-1,j)+helper(i,j-1)+helper(i-1,j-1);
            if(num[i][j]==count)
            {
                if(helper(i,j))
                {
                    opportunity[i][j]=1;
                    charge[i][j]=true;
                }
                if(helper(i-1,j))
                {
                    opportunity[i-1][j]=1;
                    charge[i-1][j]=true;
                }
                if(helper(i,j-1))
                {
                    opportunity[i][j-1]=1;
                    charge[i][j-1]=true;
                }
                if(helper(i-1,j-1))
                {
                    opportunity[i-1][j-1]=1;
                    charge[i-1][j-1]=true;
                }
            }
        }
    }
    //Case2:special situations of num=3
    for(i=1;i<lineofnum;i++){
        for(j=1;j<rowofnum;j++){
            if(num[i][j]==3){
                if(num[i][j+1]==1){
                    opportunity[i-1][j-1]=1;
                    opportunity[i][j-1]=1;
                    charge[i-1][j-1]=true;
                    charge[i][j-1]=true;
                    if(helper(i-1,j+1))
                    {opportunity[i-1][j+1]=-1;charge[i-1][j+1]=true;}
                    if(helper(i,j+1))
                    {opportunity[i][j+1]=-1;charge[i][j+1]=true;}
                    }
                if(num[i][j-1]==1){
                    opportunity[i-1][j]=1;
                    opportunity[i][j]=1;
                    charge[i-1][j]=true;
                    charge[i][j]=true;
                    if(helper(i,j-2)){
                        opportunity[i][j-2]=-1;charge[i][j-2]=true;
                    }
                    if(helper(i-1,j-2)){
                    opportunity[i-1][j-2]=-1;charge[i-1][j-2]=true;
                    }

                }
                if(num[i-1][j]==1){
                    opportunity[i][j-1]=1;
                    opportunity[i][j]=1;
                    charge[i][j-1]=true;
                    charge[i][j]=true;
                    if(helper(i-2,j-1)){
                        opportunity[i-2][j-1]=-1;charge[i-2][j-1]=true;
                    }
                    if(helper(i-2,j)){
                        opportunity[i-2][j]=-1;charge[i-2][j]=true;
                    }
                }
                if(num[i+1][j]==1){
                    opportunity[i-1][j-1]=1;
                    opportunity[i-1][j]=1;
                    charge[i-1][j-1]=true;
                    charge[i-1][j]=true;
                    if(helper(i+1,j-1)){
                        opportunity[i+1][j-1]=-1;
                        charge[i+1][j-1]=true;
                    }
                    if(helper(i+1,j)){
                        opportunity[i+1][j]=-1;
                        charge[i+1][j]=true;
                    }
                }
                //��helper()ֻ��ȷ��*fangge,����num��i��jҪ��һ;
                if(helper(i,j)&&num[i+1][j+1]==3){
                    opportunity[i][j]=1;
                    charge[i][j]=true;
                }
                if(helper(i-2,j)&&num[i-1][j+1]==3){
                    opportunity[i-1][j]=1;
                    charge[i-1][j]=true;
                }
                if(helper(i,j-2)&&num[i+1][j-1]==3){
                    opportunity[i][j-1]=1;
                    charge[i][j-1]=true;
                }

            }
        }

    }


    //Case3:
    if(num[0][1]==1&&opportunity[1][0]==1){
        opportunity[0][0]=1;
        charge[0][0]=true;
    }
    if(num[1][0]==1&&opportunity[0][1]==1){
        opportunity[0][0]=1;
        charge[0][0]=true;
    }
    if(num[0][rowofnum-2]==1&&opportunity[1][rowofge-1]==1){
        opportunity[0][rowofge-1]=1;
        charge[0][rowofge-1]=true;
    }
    if(num[1][rowofnum-1]==1&&opportunity[0][rowofge-2]==1){
        opportunity[0][rowofge-1]=1;
        charge[0][rowofge-1]=true;
    }

    if(num[lineofnum-2][0]==1&&opportunity[lineofge-1][1]==1){
        opportunity[lineofge-1][0]=1;
        charge[lineofge-1][0]=true;
    }

    if(num[lineofnum-1][1]==1&&opportunity[lineofge-2][0]==1){
        opportunity[lineofge-1][0]=1;
        charge[lineofge-1][0]=true;

    }

    if(num[lineofnum-1][rowofnum-2]==1&&opportunity[lineofge-2][rowofge-1]==1){
        opportunity[lineofge-1][rowofge-1]=1;
        charge[lineofge-1][rowofge-1]=true;
    }

    if(num[lineofnum-2][rowofnum-1]==1&&opportunity[lineofge-1][rowofge-2]==1){
        opportunity[lineofge-1][rowofge-1]=1;
        charge[lineofge-1][rowofge-1]=true;
    }
    //Case 4:����֪��remainer�Լ�**num��ȷ��
    for( i=0; i<lineofnum; i++)
    {
        for(j=0; j<rowofnum; j++)
        {
            if(num[i][j]-getNumOfBlack(i,j)==getNumOfGrayge(i,j)){
                 if(helper(i,j)&&!charge[i][j]){
                    opportunity[i][j]=1;charge[i][j]=true;
                    }
                if(helper(i-1,j)&&!charge[i-1][j]){
                    opportunity[i-1][j]=1;charge[i-1][j]=true;
                    }
                if(helper(i,j-1)&&!charge[i][j-1]){
                    opportunity[i][j-1]=1;charge[i][j-1]=true;
                    }
                if(helper(i-1,j-1)&&!charge[i-1][j-1]){
                    opportunity[i-1][j-1]=1;charge[i-1][j-1]=true;
                    }
            }
        }
    }
}
//check if continue
bool checkcontinue() //���ֻ��һ����ͨ����
{
    int numberofcontinue=1,i,j,numberofgray=0,judge=0;
    fangge tmp;
    LinkQueue<fangge> q;
	 for(i=0; i<lineofge; i++)
    {
        for(j=0; j<rowofge; j++)
        {
			if(ge[i][j]!=1)judge=1;
		}
	 }
	 if(judge==0)return true;
	 int judge2=0;
    for(i=0; i<lineofge; i++)
    {
        for(j=0; j<rowofge; j++)
        {
            if(ge[i][j]==0||ge[i][j]==-1)
            {
                tmp.li=i;
                tmp.ro=j;
                judge2=1;
                break;
            }
        }
        if(judge2)break;
    }
    for(i=0; i<lineofge; i++)
    {
        for(j=0; j<rowofge; j++)
        {
            if(ge[i][j]==0||ge[i][j]==-1)                  //0��ʾ�Ҹ�
                numberofgray++;
        }
    }
    int **visited=new int*[lineofge];
    for(i=0; i<lineofge; i++)
    {
        visited[i]=new int[rowofge];
        for(j=0; j<rowofge; j++)
            visited[i][j]=0;               //0��ʾδ���ʣ�1��ʾ�ѷ���
    }
	q.EnQueue(tmp);
    visited[tmp.li][tmp.ro] = 1;
    while(!q.IsEmpty())
    {
        tmp = q.DeQueue();
        if(tmp.ro>=1&&visited[tmp.li][tmp.ro-1]==0&&ge[tmp.li][tmp.ro-1]!=1)
        {
            visited[tmp.li][tmp.ro-1] = 1;
            fangge ttmp;
            ttmp.li=tmp.li;
            ttmp.ro=tmp.ro-1;
            q.EnQueue(ttmp);
            numberofcontinue++;
        }
        if(tmp.ro<=rowofge-2&&!visited[tmp.li][tmp.ro+1]&&ge[tmp.li][tmp.ro+1]!=1)
        {
            visited[tmp.li][tmp.ro+1] = 1;
            fangge ttmp;
            ttmp.li=tmp.li;
            ttmp.ro=tmp.ro+1;
            q.EnQueue(ttmp);
            numberofcontinue++;
        }
        if(tmp.li>=1&&!visited[tmp.li-1][tmp.ro]&&ge[tmp.li-1][tmp.ro]!=1)
        {
            visited[tmp.li-1][tmp.ro] = 1;
            fangge ttmp;
            ttmp.li=tmp.li-1;
            ttmp.ro=tmp.ro;
            q.EnQueue(ttmp);
            numberofcontinue++;
        }
        if(tmp.li<=lineofge-2&&!visited[tmp.li+1][tmp.ro]&&ge[tmp.li+1][tmp.ro]!=1)
        {
            visited[tmp.li+1][tmp.ro] = 1;
            fangge ttmp;
            ttmp.li=tmp.li+1;
            ttmp.ro=tmp.ro;
            q.EnQueue(ttmp);
            numberofcontinue++;
        }
    }
    for(i=0;i<lineofge;i++)
        delete[] visited[i];
    delete[] visited;
    if(numberofcontinue!=numberofgray)
        return false;
    else
        return true;
}
bool checknumberblack1() //������е���<=�ڸ�
{
    for(int i=0; i<lineofnum; i++)
    {
        for(int j=0; j<rowofnum; j++)
        {
            int count=0;
            if(i<=lineofge-1&&j<=rowofge-1&&ge[i][j]==1)
                count++;
            if(i>=1&&i-1<=lineofge-1&&j<=rowofge-1&&ge[i-1][j]==1)
                count++;
            if(j>=1&&i<=lineofge-1&&j-1<=rowofge-1&&ge[i][j-1]==1)
                count++;
            if(i>=1&&j>=1&&i-1<=lineofge-1&&j-1<=rowofge-1&&ge[i-1][j-1]==1)
                count++;
            if(num[i][j]>=0&&count>num[i][j])
                return false;
        }
    }
    return true;
}

bool tryMakeBlack()//����ܰ�һ����ͨ����ȫ������Ǿͱ��
{
    fangge tmp;
	int i,j;
    bool del=false;
    bool add=true;
    int **visited=new int*[lineofge];
    for(i=0; i<lineofge; i++)
    {
        visited[i]=new int[rowofge];
        for(int j=0; j<rowofge; j++)
            visited[i][j]=0;               //0��ʾδ���ʣ�1��ʾ�ѷ���
    }
    for(i=0; i<lineofge; i++)
    {
        for(j=0; j<rowofge; j++)
        {
            if(ge[i][j]!=1&&visited[i][j]==0)
            {
                LinkQueue<fangge> q;
                LinkQueue<fangge1> black;
                add=true;
                tmp.li=i;
                tmp.ro=j;
                q.EnQueue(tmp);
                visited[tmp.li][tmp.ro] = 1;
                while(!q.IsEmpty())
                {
                    tmp = q.DeQueue();
                    fangge1 tttmp;
                    tttmp.li=tmp.li;
                    tttmp.ro=tmp.ro;
                    tttmp.data=ge[tmp.li][tmp.ro];
                    black.EnQueue(tttmp);
                    ge[tmp.li][tmp.ro]=1;
                    if(tmp.ro>=1&&!visited[tmp.li][tmp.ro-1]&&ge[tmp.li][tmp.ro-1]!=1)
                    {
                        visited[tmp.li][tmp.ro-1] = 1;
                        fangge ttmp;
                        ttmp.li=tmp.li;
                        ttmp.ro=tmp.ro-1;
                        q.EnQueue(ttmp);
                    }
                    if(tmp.ro<=rowofge-2&&!visited[tmp.li][tmp.ro+1]&&ge[tmp.li][tmp.ro+1]!=1)
                    {
                        visited[tmp.li][tmp.ro+1] = 1;
                        fangge ttmp;
                        ttmp.li=tmp.li;
                        ttmp.ro=tmp.ro+1;
                        q.EnQueue(ttmp);
                    }
                    if(tmp.li>=1&&!visited[tmp.li-1][tmp.ro]&&ge[tmp.li-1][tmp.ro]!=1)
                    {
                        visited[tmp.li-1][tmp.ro] = 1;
                        fangge ttmp;
                        ttmp.li=tmp.li-1;
                        ttmp.ro=tmp.ro;
                        q.EnQueue(ttmp);
                    }
                    if(tmp.li<=lineofge-2&&!visited[tmp.li+1][tmp.ro]&&ge[tmp.li+1][tmp.ro]!=1)
                    {
                        visited[tmp.li+1][tmp.ro] = 1;
                        fangge ttmp;
                        ttmp.li=tmp.li+1;
                        ttmp.ro=tmp.ro;
                        q.EnQueue(ttmp);
                    }
                }
                if(checknumberblack1()==false)
                {
                    while(!black.IsEmpty())
                    {
                        fangge1 tttmp=black.DeQueue();
                        ge[tttmp.li][tttmp.ro]=tttmp.data;
                    }
                }
                else del=true;
                if(add==true)
                {
                    i=0;
                    j=0;
                }
            }
        }
    }
    for(i=0;i<lineofge;i++)
        delete[] visited[i];
    delete[] visited;
    return del;
}
//����
void insertionAscB(double* arr, int n){
    for(int i=1;i<n;i++){
        for(int j=i-1;j>=0;j--){
            if(arr[j+1] > arr[j]){
                double tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
            else
                break;
        }
    }
}

//����ð������һ���Ľ���ѭ��
void UpdateOpportunityAndCharge01(){
    //cout<<"UpdateOpportunityAndCharge01"<<endl;
    bool exchanged;
    int i,j;
    do{
        exchanged=false;
    for( i=0; i<lineofnum; i++)
    {
        for(j=0; j<rowofnum; j++)
        {
            if(num[i][j]>0&&num[i][j]==getNumOfBlack(i,j)){
                if(helper(i,j)&&!charge[i][j])
                    {opportunity[i][j]=-1;charge[i][j]=true;exchanged=true;}
                if(helper(i-1,j)&&!charge[i-1][j])
                    {opportunity[i-1][j]=-1;charge[i-1][j]=true;exchanged=true;}
                if(helper(i,j-1)&&!charge[i][j-1])
                    {opportunity[i][j-1]=-1;charge[i][j-1]=true;exchanged=true;}
                if(helper(i-1,j-1)&&!charge[i-1][j-1])
                    {opportunity[i-1][j-1]=-1;charge[i-1][j-1]=true;exchanged=true;}

            }
        }
    }
        for( i=0; i<lineofnum; i++)
            {
            for(j=0; j<rowofnum; j++)
            {
                if(num[i][j]==getNumOfGrayge(i,j)+getNumOfBlack(i,j))
            {
                //cout<<"UpdateOpportunityAndChargeRemark01"<<endl;
                if(helper(i,j)&&!charge[i][j])
                    {opportunity[i][j]=1;charge[i][j]=true;exchanged=true;}
                if(helper(i-1,j)&&!charge[i-1][j])
                    {opportunity[i-1][j]=1;charge[i-1][j]=true;exchanged=true;}
                if(helper(i,j-1)&&!charge[i][j-1])
                    {opportunity[i][j-1]=1;charge[i][j-1]=true;exchanged=true;}
                if(helper(i-1,j-1)&&!charge[i-1][j-1])
                    {opportunity[i-1][j-1]=1;charge[i-1][j-1]=true;exchanged=true;}

            }
        }
    }
    }while(exchanged);

}
void UpdateOpportunity(){
    int i,j;
    for(i=0;i<lineofge;i++){
        for(j=0;j<rowofge;j++){
            if(!charge[i][j]){
                opportunity[i][j]=0;
            }
    }
    }
    for( i=0; i<lineofnum; i++)
    {
        for(j=0; j<rowofnum; j++)
        {
            if(num[i][j]-getNumOfBlack(i,j)>0)
            {
                double remainerOfNum=num[i][j]-getNumOfBlack(i,j);
                double remainerOfge=getNumOfGrayge(i,j);
                if(helper(i,j)&&!charge[i][j])
                    opportunity[i][j]+=remainerOfNum/remainerOfge;
                if(helper(i-1,j)&&!charge[i-1][j])
                    opportunity[i-1][j]+=remainerOfNum/remainerOfge;
                if(helper(i,j-1)&&!charge[i][j-1])
                    opportunity[i][j-1]+=remainerOfNum/remainerOfge;
                if(helper(i-1,j-1)&&!charge[i-1][j-1])
                    opportunity[i-1][j-1]+=remainerOfNum/remainerOfge;
            }
        }
    }
}

//�����charge[i][j]==false&&opportunity[i][j]>0�ĸ��ӣ�ͨ�����򣬰���opportunity�Ӵ�С�������*temp��
fangge* whattoadd()
{
    //cout<<"fun begin!"<<endl;
    fangge* tmp=new fangge[lineofge*rowofge];
    int i,j,k=0;
    double* helpSort=new double[lineofge*rowofge];
    for(i=0;i<lineofge;i++){
        for(j=0;j<rowofge;j++){
            if(!charge[i][j]&&opportunity[i][j]>0){
                helpSort[k++]=opportunity[i][j];
            }
        }
    }
    //����
    lengthOftemp=k;
    insertionAscB(helpSort,k);
    //��ֵ
    int s=0,p=0;
    while(s<k){
    for(i=0;i<lineofge;i++){
        for(j=0;j<rowofge;j++){
            if(!charge[i][j]&&opportunity[i][j]==helpSort[s]){
                tmp[p].li=i;
                tmp[p].ro=j;
                p++;s++;
            }
        }
    }
    }
    delete[]helpSort;
    return tmp;
}
//���Ų���Ϳ�ڷ��񣬸���������ݡ�
void UpdateGe(){
    int i,j;
    //cout<<"void UpdateGe"<<endl;
    for(i=0;i<lineofge;i++){
        for(j=0;j<rowofge;j++){
            if(opportunity[i][j]==1&&charge[i][j])
                ge[i][j]=1;
            else if(opportunity[i][j]==-1&&charge[i][j])
                ge[i][j]=-1;
            else ge[i][j]=0;
            }
    }
}
//���Ų���Ϳ�ڷ��񣬸���������ݡ�
void UpdateOpportunityAndChargeByge(){
    //cout<<"UpdateOpportunityAndCharge"<<endl;
    int i,j;
    for(i=0;i<lineofge;i++){
        for(j=0;j<rowofge;j++){
                if(ge[i][j]==1){
                    opportunity[i][j]=1;
                    charge[i][j]=true;
                }
        }
    }

}
bool checknumberblack2() //������е���==�ڸ�
{
    int count,i,j;
    bool flag=true;
    for(i=0; i<lineofnum; i++)
    {
        for(j=0; j<rowofnum; j++)
        {
            count=0;
            if(num[i][j]>=0){

            if(helper(i,j)&&charge[i][j]&&opportunity[i][j]==1)
                count++;
            if(helper(i,j-1)&&charge[i][j-1]&&opportunity[i][j-1]==1)
                count++;
            if(helper(i-1,j)&&charge[i-1][j]&&opportunity[i-1][j]==1)
                count++;
            if(helper(i-1,j-1)&&charge[i-1][j-1]&&opportunity[i-1][j-1]==1)
                count++;
                if(num[i][j]>=0&&num[i][j]!=count){
                    flag=false;
                    break;
                }
        }
        }
        if(!flag)
            break;
    }
    return flag;
}
//�Զ������
void printge()
{
    int i,j;
    for(i=0; i<lineofge; i++)
    {
        for(j=0; j<rowofge; j++)
        {
            //cout<<setw(10)<<left<<opportunity[i][j];
            if(opportunity[i][j]==1&&charge[i][j])
                cout<<setw(5)<<left<<"��";
            //else if(opportunity[i][j]==-1&&charge[i][j])
               //cout<<setw(5)<<left<<"";
            else cout<<setw(5)<<left<<"��";

        }
        cout<<endl;
    }
}
//�������
void printgem()
{
    int i,j;
    for(i=0; i<lineofge; i++)
    {
        for(j=0; j<rowofge; j++)
        {
            //cout<<setw(10)<<left<<opportunity[i][j];
            if(opportunity[i][j]==1&&charge[i][j])
                cout<<"X";
            //else if(opportunity[i][j]==-1&&charge[i][j])
               // cout<<setw(5)<<left<<"��";
            else cout<<"-";

        }
    }
}

bool checkOfRecursion(){
    bool flag=true;
    for(int i=0;i<lineofnum;i++){
        for(int j=0;j<rowofnum;j++){
            if(num[i][j]>=0&&num[i][j]>getNumOfGrayge(i,j)+getNumOfBlack(i,j)){
                flag=false;
            }

        }
        if(!flag)break;
    }
    return flag;
}
//�ݹ麯��
void Recursion(fangge* temp,int length){
    int i;
    double ** opportunityCopy=new double*[lineofge];
	for(i=0;i<lineofge;i++)
	opportunityCopy[i]=new double[rowofge];
	bool ** chargeCopy=new bool*[lineofge];
	for(i=0;i<lineofge;i++)
	chargeCopy[i]=new bool[rowofge];

    //cout<<"����ݹ�:length="<<length<<endl;

            for(i=0;i<length;i++){
                //printge();
                //cout<<temp[i].li<<"  "<<temp[i].ro<<endl;
                for(int k=0; k<lineofge; k++)
                {
                    for(int j=0; j<rowofge; j++)
                {
                    opportunityCopy[k][j]=opportunity[k][j];
                    chargeCopy[k][j]=charge[k][j];
                }
                }
                opportunity[temp[i].li][temp[i].ro]=1;
                charge[temp[i].li][temp[i].ro]=true;
                UpdateOpportunityAndCharge01();
                UpdateOpportunity();
                UpdateGe();
                if(checkcontinue()){
                    //cout<<"����"<<endl;
                    //��������ȷ��
                    if(checknumberblack2()){
						if(p==1)
                        printge();
						else 
						printgem();
                        exit(0);
                    }
                    //else cout<<"checknumberblack Wrong!"<<endl;
                    fangge* ttmp=whattoadd();
                    Recursion(ttmp,lengthOftemp);
                    delete[]ttmp;
                    for(int s=0; s<lineofge; s++){
                        {for(int j=0; j<rowofge; j++)
                            {
                            opportunity[s][j]=opportunityCopy[s][j];
                            charge[s][j]=chargeCopy[s][j];
                            }
                        }
                    }

                    opportunity[temp[i].li][temp[i].ro]=-1;
                    charge[temp[i].li][temp[i].ro]=true;
                    }
                else{
                        //cout<<"������"<<endl;
                        if(tryMakeBlack())
                        {
                        //cout<<"CX function"<<endl;
                        UpdateOpportunityAndChargeByge();
                        UpdateOpportunityAndCharge01();
                        UpdateOpportunity();
                        fangge* ttmp=whattoadd();
                        Recursion(ttmp,lengthOftemp);
                        delete[]ttmp;
                        for(int r=0; r<lineofge; r++)
                            {for(int j=0; j<rowofge; j++)
                                {
                                    opportunity[r][j]=opportunityCopy[r][j];
                                    charge[r][j]=chargeCopy[r][j];
                                }
                            }

                        opportunity[temp[i].li][temp[i].ro]=-1;
                        charge[temp[i].li][temp[i].ro]=true;
                        }
                        else{
                           // printge();
                            //cout<<"Ϳ����Ȼ������i++"<<endl;
                            for(int p=0; p<lineofge; p++)
                                {for(int j=0; j<rowofge; j++)
                                {
                                    opportunity[p][j]=opportunityCopy[p][j];
                                    charge[p][j]=chargeCopy[p][j];
                                }
                                }

                            opportunity[temp[i].li][temp[i].ro]=-1;
                            charge[temp[i].li][temp[i].ro]=true;
                            if(checkOfRecursion()==false){
                                //cout<<"checkOfRecursion:false!"<<endl;

                                return;
                                }

                    }
                }
                        //UpdateOpportunityAndCharge01();
                        //UpdateGe();
            }
            if(i==length&&!checknumberblack2()){
                    for(int p=0; p<lineofge; p++)
                                {for(int j=0; j<rowofge; j++)
                                {
                                    opportunity[p][j]=opportunityCopy[p][j];
                                    charge[p][j]=chargeCopy[p][j];
                                }
                                }

                opportunity[temp[0].li][temp[0].ro]=-1;
                charge[temp[0].li][temp[0].ro]=true;
                UpdateOpportunityAndCharge01();
                UpdateOpportunity();
                fangge* ttmp=whattoadd();
                Recursion(ttmp,lengthOftemp);
            }


	for(i=0;i<lineofge;i++)
	delete []opportunityCopy[i];
	delete []opportunityCopy;
	for(i=0;i<lineofge;i++)
	delete []chargeCopy[i];
	delete []chargeCopy;
    }


int main()
{
	char fn[100];
	cin>>fn;
	freopen(fn,"r",stdin);

    int i,j,k;
    int count=0;
	cin>>p;
    initial();
    UpdateOpportunityAndCharge01();
    UpdateOpportunity();
    //printge();

    /*int m,n;
    for(i=0;i<3;i++){
        cin>>m>>n;
        opportunity[m][n]=1;
        charge[m][n]=true;
    }
    UpdateOpportunityAndCharge01();
    UpdateGe();
    printge();
    cout<<tryMakeBlack()<<endl;
    UpdateOpportunityAndCharge();
    printge();*/
    fangge* temp=whattoadd();
    //cout<<"�ݹ鿪ʼ��"<<endl;

    Recursion(temp,lengthOftemp);
    delete[]temp;

    return 0;
}



