ListNode* mergeKLists(vector<ListNode*>& lists) {
	ListNode *p = NULL;
	ListNode *q = NULL;
	int n = lists.size();
	if (n == 0) return q;
	while (lists.back() == NULL)
	{
		lists.pop_back();
		--n;
	}
	if (n == 0) return q;
	int s = n - 1;
	for (int i = 0; i <= s; i++)
		if (lists[i] == NULL)
		{
			swap(lists[i], lists[s]);
			--s;
			lists.pop_back();
		}
	n = lists.size();
	if (n == 0) return q;
	if (n == 1) return lists.front();
	sort(lists.begin(), lists.end(), [](ListNode* node1, ListNode* node2) {return node1->val < node2->val; });
	for(int i = 0; i < lists.size() - 1; i++)
	{
		while (lists[i] != NULL)
		{
			if (p)
			{
				p->next = new ListNode(lists[i]->val);
				p = p->next;
			}
			else
			{
				p = new ListNode(lists[i]->val);
				q = p;
			}
			lists[i] = lists[i]->next;
			if (lists[i] == NULL) break;
			int j = i;
			while (j < lists.size() - 1 && lists[j]->val > lists[j + 1]->val)
			{
				swap(lists[j], lists[j + 1]);
				++j;
			}
		}
	}
	p->next = lists[lists.size() - 1];
	p = p->next;
	return q;
}