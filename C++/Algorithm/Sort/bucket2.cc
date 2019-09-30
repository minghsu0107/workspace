#include <bits/stdc++.h>
using namespace std;
static void BucketSort(int* data, int count) {
	int minValue = data[0];
	int maxValue = data[0];

	for (int i = 1; i < count; i++)
	{
		if (data[i] > maxValue)
			maxValue = data[i];
		if (data[i] < minValue)
			minValue = data[i];
	}

	int bucketLength = maxValue - minValue + 1;
	vector<int>* bucket = new vector<int>[bucketLength];

	for (int i = 0; i < bucketLength; i++)
	{
		bucket[i] = vector<int>();
	}

	for (int i = 0; i < count; i++)
	{
		bucket[data[i] - minValue].push_back(data[i]);
	}

	int k = 0;
	for (int i = 0; i < bucketLength; i++)
	{
		int bucketSize = bucket[i].size();

		if (bucketSize > 0)
		{
			for (int j = 0; j < bucketSize; j++)
			{
				data[k] = bucket[i][j];
				k++;
			}
		}
	}
}
int main() {
	int data[] = { -1, 25, -58964, 8547, -119, 0, 78596 };
	BucketSort(data, 7);
	for (auto &x: data) cout << x << " ";
	cout << endl;
	return 0;
}