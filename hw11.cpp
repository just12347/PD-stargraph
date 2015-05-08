#include<iostream>
#include<string>
#include<cstdlib>
#include<sstream>
using namespace std;

class Node
{
	friend class Network;

	public:
		
		void setNode(int,int);
	protected:
		int id;
		int weight;
		int arcnums;
};
void Node::setNode(int id, int weight)
{
	this->id=id;
	this->weight=weight;
	this->arcnums=0;
}
class Arc
{
	friend class Network;
	public:
		
		void setArc(int,int,int);
	protected:
		int nodeFrom;
		int nodeTo;
		int weight;
};

void Arc::setArc(int nodeFrom,int nodeTo, int weight)
{
	this->nodeFrom=nodeFrom;
	this->nodeTo=nodeTo;
	this->weight=weight;
}
class Network
{
	protected:
		int n;
		int m;
		int nMax;
		int mMax;
		Node* node;
		Arc* arc;
	public:
		Network();
		Network(int nmax, int mmax);
		~Network();
		void addNode(Node v);
		void addArc(Arc e);
		void removeNode(int nodeID);
		void removeArc(int arcID);
		void removeArc(int nodeFrom, int nodeTo);
		void printt(int i);
		void ini();
		void findpath(int* ,int );
};

void Network::ini()
{
	for(int i=0;i<100000;i++)
	{
		node[i].id=-1;
		node[i].weight=-1;
		arc[i].nodeFrom=-1;
		arc[i].nodeTo=-1;
		arc[i].weight=-1;
	}
}
void Network::printt(int i)
{
	cout<<arc[i].nodeFrom<<" ";
	
}
Network::Network()
{
	n,m=0;
	nMax=100000;
	mMax=100000;
	node = new Node [nMax]; 
	arc = new Arc [mMax];
	
}
Network::Network(int nmax, int mmax)
{
	n,m=0;
	nMax=nmax;
	mMax=mmax;
	node= new Node [nMax];
	arc = new Arc [mMax];
}


Network::~Network()
{
	delete []node;
	delete []arc;
}

void Network::addNode(Node v)
{
	bool checkexist = false;
	bool check=false;
	if(n==0)
	{
		node[n]=v;
		n++;
		
	}
	else
	{
	
	for (int i=0; i<n; i++)
	{
		if(node[i].id==v.id)
		{
			check = true;
			//cout<<"here";
		}
				
	}
		if(check==true)
			checkexist=true;
		else
			checkexist=false;
		 
	if (checkexist==false)
	{
		if(n>nMax-1)
		{
			Node* oldnodes = node;
			node = new Node [nMax];
			nMax = 2*nMax;
			node = new Node [nMax];
			for (int index=0; index < nMax; index++)
			{
				node[index] = oldnodes[index];
			}
			for(int j=n;j<nMax;j++)
			{
				node[j].weight=0;
				node[j].id=0;
			}
			delete oldnodes;
			
		}
		node[n]=v;
		n++;
		
	}
}
}

void Network::addArc(Arc e)
{
		bool checkexist = false;
	bool check=false;
	if(m==0)
	{
		arc[m]=e;
		
		for(int i=0;i<n;i++)
		{
			if(node[i].id==e.nodeFrom&&node[i].id!=1&&e.nodeTo!=1)
				node[i].arcnums++;
			if(node[i].id==e.nodeTo&&node[i].id!=1&&e.nodeFrom!=1)
				node[i].arcnums++;	
		}
		m++;
		
	}
	else
	{
	
	for (int i=0; i<m; i++)
	{
		if(arc[i].nodeFrom==e.nodeFrom && arc[i].nodeTo==e.nodeTo)
		{
			check = true;
			//cout<<"hehe";
		}
	}
		if(check==true)
			checkexist=true;
		else
			checkexist=false;
	if (checkexist==false)
	{
		if(m>mMax-1)
		{
			Arc* oldarcs = arc;
			arc = new Arc [mMax];
			mMax = 2*mMax;
			arc = new Arc [mMax];
			for (int index=0; index < mMax; index++)
			{
				arc[index] = oldarcs[index];
			}
			for(int j=m;j<mMax;j++)
			{
				arc[j].weight=-1;
				arc[j].nodeTo=-1;
				arc[j].nodeFrom=-1;
			}
			delete oldarcs;
			
		}
		bool cando=true;
		bool cando1,cando2=true;
		for(int i=0;i<n;i++)
		{
			if(node[i].id==e.nodeFrom&&e.nodeFrom!=1&&e.nodeTo!=1)
				if(node[i].arcnums>=2)
				{
					cando1=false;	
				}
					
			if(node[i].id==e.nodeTo&&e.nodeTo!=1&&e.nodeFrom!=1)
				if(node[i].arcnums>=2)
				{
					cando2=false;
				}
		}
		
		if(cando1==true&&cando2==true)
			cando=true;
		if(cando==true)
		{
			arc[m]=e;
			for(int i=0;i<n;i++)
			{
				if(node[i].id==e.nodeFrom&&node[i].id!=1&&e.nodeTo!=1)
					node[i].arcnums++;
				if(node[i].id==e.nodeTo&&node[i].id!=1&&e.nodeFrom!=1)
					node[i].arcnums++;	
			}
			m++;
		}
		//cout<<m;
	}
	else;
	}
}

void Network::removeNode(int nodeID)
{
	
	for (int i=0; i<n ; i++)
	{
		if (node[i].id==nodeID)
		{
			for (int j=i;j<n;j++)
			{
				node[j]=node[j+1];
			}
			n--;
			
			for ( int k=0; k<m ; k++)
			{
				if ( nodeID== arc[k].nodeTo || nodeID== arc[k].nodeFrom)
				{
					for (int t=k;t<m;t++)
					{
						arc[t]=arc[t+1];
					}
					m--;
				}
			}
		}
	}
}

void Network::removeArc(int nodeFrom,int nodeTo)
{
	for (int i=0;i<m;i++)
	{
		if(arc[i].nodeFrom==nodeFrom&&arc[i].nodeTo==nodeTo)
		{
			for (int t=i;t<m;t++)
			{
				arc[t]=arc[t+1];
			}
			m--;
		}
	}
}


void Network::findpath(int* cal ,int total)
{
	int distance=0;
	int supply=0;
	bool route=true;
	bool find= false;
	int cur=0;
	int now=0;
	int to=0;
	int* sup= new int [total];
	
	for(int i=0;i<total;i++)
	{
		sup[i]=cal[i];
		//cout<<sup[i]<<" ";
	}
	for(int i=0;i<total;i++)
	{
		int piv=sup[i];
		for(int j=i+1;j<total;j++)
		{
			if(piv==sup[j])
			sup[j]=0;
			
		}
	}

	for(int i=0;i<total;i++)
	{
		if(sup[i]!=0)
		{
		 cur=sup[i];
		//cout<<cur<<" ";
		
		 for(int j=0;j<n;j++)
		 {
		 	if(node[j].id==cur)
		 	supply+=node[j].weight;
		 }
		}
	}
	for(int i=0;i<total-1;i++)
	{
		now=cal[i];
		to=cal[i+1];
		for(int k=0;k<m;k++)
		{
			if(arc[k].nodeFrom==now&&arc[k].nodeTo==to)
			{
				distance+=arc[k].weight;
				//cout<<distance<<" ";
				find=true;
			}
			
				
		}
		if(find==false)
			route=false; 
		find=false;
		
	}
	
	
	
	if(route==true)
	cout<<distance<<" "<<supply<<endl;
	else
	cout<<"0"<<endl;
}

class StarNetwork: public Network
{
	public:;
		StarNetwork(){ Network();
		};
		//void addArc(Arc e);
		
};
/*void StarNetwork::addArc(Arc e)
{
	bool checkexist = false;
	bool check=false;
	if(m==0)
	{
		arc[m]=e;
		
		for(int i=0;i<n;i++)
		{
			if(node[i].id==e.nodeFrom)
				node[i].arcnums++;
			if(node[i].id==e.nodeTo)
				node[i].arcnums++;	
		}
		m++;
		
	}
	else
	{
	
	for (int i=0; i<m; i++)
	{
		if(arc[i].nodeFrom==e.nodeFrom && arc[i].nodeTo==e.nodeTo)
		{
			check = true;
			//cout<<"hehe";
		}
	}
		if(check==true)
			checkexist=true;
		else
			checkexist=false;
	if (checkexist==false)
	{
		if(m>mMax-1)
		{
			Arc* oldarcs = arc;
			arc = new Arc [mMax];
			mMax = 2*mMax;
			arc = new Arc [mMax];
			for (int index=0; index < mMax; index++)
			{
				arc[index] = oldarcs[index];
			}
			for(int j=m;j<mMax;j++)
			{
				arc[j].weight=-1;
				arc[j].nodeTo=-1;
				arc[j].nodeFrom=-1;
			}
			delete oldarcs;
			
		}
		bool cando=true;
		for(int i=0;i<n;i++)
		{
			if(node[i].id==e.nodeFrom||e.nodeFrom!=1)
				if(node[i].arcnums>=2)
					cando=false;
			if(node[i].id==e.nodeTo||e.nodeTo!=1)
				if(node[i].arcnums>=2)
					cando=false;
		}
		if(cando==true)
		{
			arc[m]=e;
			m++;
		}
		//cout<<m;
	}
	else;
	}

}*/
int main()

{
	StarNetwork aStarNetwork;
	string get;
	int a,b,c;
	aStarNetwork.ini();
	int counter=0;
	while (cin)
	{
		cin>>get;
		
		
		if(get=="AN")
		{
			cin>>a>>b;
			Node* temp= new Node;
			temp->setNode(a,b);
			aStarNetwork.addNode(*temp);
		}
		else if(get=="AA")
		{
			cin>>a>>b>>c;
			Arc* temp= new Arc;
			temp->setArc(a,b,c);
			
			
			aStarNetwork.addArc(*temp);
		}
		else if(get=="RN")
		{
			cin>>a;
			aStarNetwork.removeNode(a);
		}
		else if(get=="RA")
		{
			cin>>a>>b;
			aStarNetwork.removeArc(a,b);
		}
		/*else if(get=="JI")
		{
			for(int i=0;i<30;i++)
			aNetwork.printt(i);
		}*/
		else if(get=="P")
		{
			counter++;
			char path[10000];
			int thepath[10000];
			stringstream s;
			cin.getline(path,10000);
			int c=0;
			s<<path;
			while(s>>thepath[c])
			{
				//cout<< thepath[c]<<" ";
				c++;
			}
			
			aStarNetwork.findpath(thepath,c);
		
			if (counter==5||counter==20)
			{
				aStarNetwork.ini();
				
			}
		}
		
	}
	
}
