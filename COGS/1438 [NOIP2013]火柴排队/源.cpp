#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
int a[100001];
pair<int, int> x[100001], y[100001], z[100001];
int MergeSort(int l, int r)
{
	static int tmp[100001];
	if (l == r) return 0;
	int mid = (l + r) / 2;
	int cnt = (MergeSort(l, mid) + MergeSort(mid + 1, r)) % 99999997;
	int i = l, j = mid + 1, k = 0;
	while (i <= mid&&j <= r)
	{
		if (a[i] < a[j]) tmp[k++] = a[i++];
		else
		{
			tmp[k++] = a[j++];
			(cnt += mid - i + 1) %= 99999997;
		}
	}
	while (i <= mid) tmp[k++] = a[i++];
	while (j <= r) tmp[k++] = a[j++];
	for (int i = 0; i < k; i++) a[i + l] = tmp[i];
	return cnt;
}
int main()
{
	ifstream cin("MatchNOIP2013.in");
	ofstream cout("MatchNOIP2013.out");
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> x[i].first, x[i].second = i;
	for (int i = 1; i <= n; i++) cin >> y[i].first, y[i].second = i;
	sort(x + 1, x + 1 + n);
	sort(y + 1, y + 1 + n);
	for (int i = 1; i <= n; i++) z[i].first = y[i].second, z[i].second = x[i].second;
	sort(z + 1, z + 1 + n);
	for (int i = 1; i <= n; i++) a[i] = z[i].second;
	cout << MergeSort(1, n) << endl;
}
