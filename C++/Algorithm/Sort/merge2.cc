#include <bits/stdc++.h>
using namespace std;

int cnt = 0; // number of reverse order pair
// during merging, when we copy an element x on the right to tmp,
// the remaining elements on the left are all larger than x
void mergeSort(int arr[], int left, int right) {
	if (left + 1 == right) return;
	int mid = (left + right) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid, right);
	int l = left, r = mid, k = left;
	int *tmp = new int[right - left];
	while (l < mid || r < right) {
		if (l < mid && (r >= right || arr[l] <= arr[r]))
			tmp[k++] = arr[l++];
		else {
			tmp[k++] = arr[r++];
			cnt += mid - l;
		}
	}
	for (l = left; l < right; l++) arr[l] = tmp[l];
	delete [] tmp;
    return;
}
void mergeSort2(int arr[], int left, int right) {
	if (left == right) return;
	int mid = (left + right) / 2;
	mergeSort2(arr, left, mid);
	mergeSort2(arr, mid + 1, right);
	int l = left, r = mid + 1, k = left;
	int *tmp = new int[right - left + 1];
	while (l <= mid || r <= right) {
		if (l <= mid && (r > right || arr[l] <= arr[r]))
			tmp[k++] = arr[l++];
		else {
			tmp[k++] = arr[r++];
			cnt += mid - l + 1;
		}
	}
	for (l = left; l <= right; l++) arr[l] = tmp[l];
	delete [] tmp;
    return;
}
int main() {
	int arr[] = {3, 2, 9, 13, 4, 5};
	mergeSort2(arr, 0, 5);
	for (int i = 0; i < 6; i++) cout << arr[i] << " ";
	cout << endl;
    cout << cnt << endl;
}