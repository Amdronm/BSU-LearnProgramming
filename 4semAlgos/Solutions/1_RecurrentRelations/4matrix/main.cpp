#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <algorithm>

void print_vec(const std::vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		printf("%d ", vec[i]);
	}
	printf("\n");
}

void print_mat(const std::vector<std::vector<int>>& mat) {
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[i].size(); j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

int get(std::vector<int>& vec);
void give(int res);

int main() {
	std::vector<int> vec;
	int n = get(vec);
	std::vector<std::vector<int>> triangle(n - 1);
	for (int i = 0; i < triangle.size(); i++) {
		triangle[i].resize(n - i - 1, 0);
	}
	for (int i = 0; i < triangle.size(); i++) {
		triangle[0][i] = vec[i] * vec[i + 1] * vec[i + 2];
	}
	//print_vec(triangle[0]);
	std::vector<int> sup(n, 0);
	for (int i = 1; i < triangle.size(); i++) {
		for (int j = 0; j < triangle[i].size(); j++) {
			std::fill(sup.begin(), sup.end(), INT_MAX);
			for (int k = 0; k <= i; k++) {
				int p = vec[j];
				int q = vec[n - triangle[i].size() + j + 1];
				if (k == 0) {
					sup[k] = triangle[i - 1][j + 1] + p * q * vec[j + 1];
				}
				else if (k == i) {
					sup[k] = triangle[i - 1][j] + p * q * vec[n - triangle[i].size() + j];
				}
				else {
					sup[k] = triangle[i - k - 1][j + k + 1] + triangle[k - 1][j] + p * q * vec[j + k + 1];
				}
			}
			auto it = std::min_element(sup.begin(), sup.end());
			triangle[i][j] = *it;
		}
	}
	//print_vec(vec);
	//print_mat(triangle);
	give(triangle.back().back());	
	return 0;
}

int get(std::vector<int>& vec) {
	FILE* input = fopen("input.txt", "r");
	int n = 0;
	fscanf_s(input, "%d", &n);
	vec.resize(n + 1);
	int a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		fscanf_s(input, "%d %d", &a, &b);
		vec[i] = a;
	}
	vec[n] = b;
	fclose(input);
	return n;
}

void give(int res) {
	FILE* output = fopen("output.txt", "w");
	fprintf(output, "%d", res);
	fclose(output);
}