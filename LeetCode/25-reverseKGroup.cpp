ListNode* reverseKGroup(ListNode* head, int k)
{
    if (head == NULL) return head;
	ListNode* o = NULL;
	ListNode* p = NULL;
	ListNode* q = NULL;
	ListNode* r = NULL;
	q = r = o = head;
	int i = 0;
	while (r != NULL)
	{
		r = r->next;
		++i;
	}
	if (i < k) return head;
	int len = (i / k) * k;
	i = 0;
	r = head;
	while (i < len)
	{
		p = o->next;
		++i;
		if (i % k != 0)
		{
			o->next = p->next;
			p->next = q;
			q = p;
			if (i == k - 1) head = p;
		}
		else
		{
			if (i > k && i % k == 0)
			{
				r->next = q;
				r = o;
			}
			o = o->next;
			q = o;
		}
	}
    return head;
}