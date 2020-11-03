#include <iostream>
#include <list>
#include <vector>
#include <map>

using namespace std;

class	Node
{
	public:
		int a;
		char c;
		Node *left, *right;

		Node(){}

		Node(Node *L, Node *R)
		{
			left = L;
			right = R;
			a = L->a + R->a;
		}
};

vector<bool> code;
map <char, vector<bool> > table;

struct	MyCompare
{
	bool operator() (Node* l, Node* r) const
	{ return l->a < r->a; }
};

void	print(Node* root, unsigned k=0)
{
	if (root != NULL)
	{
		print(root->left, k + 3);

		for (unsigned i = 0; i < k; i++)
		{
			cout << " ";
		}

		if (root->c)
			cout << root->a << " (" << root->c << ")" << endl;
		else
			cout << root->a << "\n";
		print (root->right, k + 3);
	}
}

void BuildTable(Node* root)
{
	if (root->left != NULL)
	{
		code.push_back(0);
		BuildTable(root->left);
	}
	if (root->right != NULL)
	{
		code.push_back(1);
		BuildTable(root->right);
	}
	if (root->c)
		table[root->c] = code;

	code.pop_back();
}

int		main()
{
	string str= "HelllllWoorld!!!";

	map<char,int> m;


	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		m[c]++;
	}

	list<Node*> t;

	map<char,int>::iterator i;
	for (i = m.begin(); i != m.end(); ++i)
	{
		Node* p = new Node;
		p->c = i->first;
		p->a = i->second;
		t.push_back(p);
	}
	


	while (t.size() != 1)
	{
		t.sort(MyCompare());
		Node* SonL = t.front();
		t.pop_front();
		Node* SonR = t.front();
		t.pop_front();

		Node *parent = new Node(SonL,SonR);
		t.push_front(parent);
	}

	Node* root = t.front();
	print(root);
	BuildTable(root);
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		vector<bool> x = table[c];

		for (int n = 0; n < x.size(); n++)
			cout << x[n];
	}
}
