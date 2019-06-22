struct node
{
	int data, lcnt, rcnt, cnt;
	node *left, *right;
	node(int d = 0)
	{
		left = right = nullptr;
		data = d;
		lcnt = rcnt = 0;
		cnt = 1;
	}
};

node *insert(node *root, int val)
{
	if (root == nullptr)
		return node(val);
	root->cnt++;
	if (root->data < val)
	{
		root->right = insert(root->right, val);
		root->rcnt++;
	}
	else
	{
		root->left = insert(root->left, val);
		root->lcnt++;
	}
	// The balancing must be done by you
	// use avl tree or rb tree logic here
	return root;
}

int find_kth(node *root, int k)
{
	if (root == nullptr)
	{
		//You have some Problems here :P
		return 0;
	}
	if (k <= root->lcnt)
		return find_kth(root->left, k);
	if (k == (root->lcnt + 1))
		return root->data;
	k -= root->lcnt + 1;
	return find_kth(root->right, k);
}

/*
	Delete Logic will also alter 
 */