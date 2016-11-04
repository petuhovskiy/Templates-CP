vector<int> prefix(string s) {
	vector<int> res(s.size(), 0);
	for (int i = 1; i < s.size(); i++) {
		int j = res[i - 1];
		while (j && s[i] != s[j]) j = res[j - 1];
		res[i] = j + (s[i] == s[j]);
	}
	return res;
}
