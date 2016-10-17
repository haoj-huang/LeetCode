vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
{
	vector<Interval> vo;
	bool is_insert = false;
	for (auto interval : intervals) {
		if (interval.end < newInterval.start)
			vo.push_back(interval);
		else if (interval.start > newInterval.end) {
			if (!is_insert) {
				vo.push_back(newInterval);
				is_insert = true;
			}
			vo.push_back(interval);
		}
		else {
			newInterval.start = min(newInterval.start, interval.start);
			newInterval.end = max(newInterval.end, interval.end);
		}
	}
	if (!is_insert) vo.push_back(newInterval);
	return vo;
}