#include <bits/stdc++.h>
#include <array>
#include <iostream>
#include <random>

namespace ada {
	class Xoroshiro128 {
	public:
		using result_type = uint32_t;
		static constexpr result_type(min)() { return 0; }
		static constexpr result_type(max)() { return UINT32_MAX; }
		static inline result_type rotl(const result_type x, int k) {
			return (x << k) | (x >> (32 - k));
		}
		Xoroshiro128() : Xoroshiro128(1, 2, 3, 4) {}
		Xoroshiro128(result_type a, result_type b, result_type c, result_type d)
			: s{a, b, c, d} {}
		result_type operator()() {
			const result_type result = rotl(s[0] + s[3], 7) + s[0];
			const result_type t = s[1] << 9;
			s[2] ^= s[0];
			s[3] ^= s[1];
			s[1] ^= s[2];
			s[0] ^= s[3];
			s[2] ^= t;
			s[3] = rotl(s[3], 11);
			return result;
		}
	private:
		std::array<result_type, 4> s;
	};

	namespace {
		int c_lead, c_team;
		Xoroshiro128 rng;
	}  // namespace

	int Init() {
		int n;
		uint32_t s1, s2, s3, s4;
		std::cin >> n >> c_lead >> c_team >> s1 >> s2 >> s3 >> s4;
		rng = Xoroshiro128(s1, s2, s3, s4);
		return n;
	}

	int GetLeadership() { return uint64_t(rng()) * c_lead >> 32; }

	int GetTeamValue() {
		int tmp = int(uint64_t(rng()) * c_team >> 32) + 1;
		return int(c_team / sqrt(tmp));
	}

}  // namespace ada
using namespace std;

const int MAXN = 2000010;
const int mod = 1e9 + 7;

long long leadership[MAXN];
long long team_value[MAXN];
long long dp[MAXN], sum[MAXN];
int k;

void init(int n) {
	for (int i = 0; i < n - 1; ++i)
		team_value[i + 1] = team_value[i + 1] + team_value[i];
}

void solve(int n) {
	sum[n + 1] = 0;
	dp[n - 1] = sum[n] = 1;
	sum[n - 1] = 2;
	for (int i = n - 2; i >= 0; --i) {
		k = upper_bound(team_value + i, team_value + n, leadership[i] + team_value[i]) 
		    - begin(team_value);
		dp[i] = (((dp[i] + sum[i + 1]) % mod) - sum[k + 1] + mod) % mod;
		sum[i] = (sum[i + 1] + dp[i]) % mod;
	}
}
int main() {
	int n = ada::Init(); // Get N
	for (int i = 0; i < n; i++) leadership[i] = ada::GetLeadership();
	for (int i = 0; i < n; i++) team_value[i] = ada::GetTeamValue();
	init(n);
	solve(n);
	printf("%lld\n", dp[0]);
}