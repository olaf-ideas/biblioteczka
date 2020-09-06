#include <bits/stdc++.h>
#include <sys/time.h>
#include <ctime>
using namespace std;

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp() {
  static timeval now;
  gettimeofday(&now, NULL);
  return (now.tv_usec + (timestamp_t)now.tv_sec * 1000000);
}

const float DIVIDE = 1000000.0L;

double seconds_elapsed(timestamp_t t1, timestamp_t t2) {
  return (t2 - t1) / DIVIDE;
}

int main() {
  timestamp_t t0 = get_timestamp();

  long long score = 0;
  for(int i = 0; i < 10000; i++) {
    for(int j = i + 1; j < 10000; j++)
      score += __gcd(i, j);
  }

  timestamp_t t1 = get_timestamp();
 
  double secs = seconds_elapsed(t0, t1);
}
