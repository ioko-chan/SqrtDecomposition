#include <iostream>
#include <cmath>
#include <vector>
#include <climits>

class SqrtDecomposition {
public:
	explicit SqrtDecomposition(int n)
		: m_n(n), a(n), groupSize(sqrt(n) + 1), groupValue(n / groupSize, 0) , groupSum(n / groupSize, 0) {
		for (int i = 0; i < n; ++i) {
			a[i] = 0;
			groupSum[i / groupSize] += 0;
		}
	}

	void normalize(int group) {
		int groupStart = group * groupSize;
		int nextGroup = std::min(m_n, (group + 1) * groupSize);
		if (groupValue[group] != undef) {
			for (int i = groupStart; i < nextGroup; ++i) {
				a[i] = groupValue[group];
			}
			groupValue[group] = undef;
			groupSum[group] = 0;
		}
	}

	void update(int left, int right, int x) {
		int lg = left / groupSize;
		int rg = right / groupSize;
		if (lg == rg) {
			normalize(lg);
			for (int i = left; i <= right; ++i) {
				a[i] = x;
			}
		}
		else {
			normalize(lg);
			int nextGroup = std::min(m_n, (lg + 1) * groupSize);
			for (int i = left; i < nextGroup; ++i) {
				a[i] = x;
			}
			for (int i = lg + 1; i < rg; ++i) {
				groupValue[i] = x;
			}
			normalize(rg);
			for (int i = rg * groupSize; i <= right; ++i) {
				a[i] = x;
			}
		}
	}

	int sum(int left, int right) {
		int sum = 0;
		int lg = left / groupSize;
		int rg = right / groupSize;
		if (lg == rg) {
			normalize(lg);
			for (int i = left; i <= right; ++i) {
				sum += a[i];
			}
		}
		else {
			normalize(lg);
			int nextGroup = std::min(m_n, (lg + 1) * groupSize);
			for (int i = left; i < nextGroup; ++i) {
				sum += a[i];
			}
			for (int i = lg + 1; i < rg; ++i) {
				if (groupValue[i] == undef) {
					sum += groupSum[i];
				}
				else {
					sum += groupSize * groupValue[i];
				}
			}
			normalize(rg);
			for (int i = rg * groupSize; i <= right; ++i) {
				sum += a[i];
			}
		}
		return sum;
	}

private:
	int m_n;
	int groupSize;
	const int undef = INT_MAX;
	std::vector<int> a;
	std::vector<int> groupValue;
	std::vector<int> groupSum;
};

int main() {
	int N, M;
	std::cin>> N >> M;
	SqrtDecomposition sd(N);

	for (int i = 0; i < M; ++i) {
		int operation, l, r, x, pos;
		std::cin>>operation;
		switch (operation) {
		case 1:
			std::cin >> l >> r>> x;
			sd.update(l, r, x);
			break;
		case 2:
			std::cin >> l>> r;
			std::cout<< sd.sum(l, r)<< std::endl;
			break;
		default:
			std::cout<<"Unknown\n";
			break;
		}
	}
}