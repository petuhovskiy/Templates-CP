const int sN = 10000000;
int lp[sN];
vector<int> pr;

bool initSieve() {
	for (int i = 2; i < sN; i++) {
		if (!lp[i]) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; j < pr.size() && pr[j] <= lp[i] && 1ll * i * pr[j] < sN; j++)
			lp[i * pr[j]] = pr[j];
	}
}
bool sieve = initSieve();
