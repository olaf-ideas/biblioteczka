#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

/*
benchmark:

olaf@ubuntu:~/Coding/C++/Biblioteczka/Other/Parallelization$ time ./brut 
584509280

real	0m6,125s
user	0m6,113s
sys	0m0,009s

olaf@ubuntu:~/Coding/C++/Biblioteczka/Other/Parallelization$ time ./par 
584509280

real	0m2,099s
user	0m7,784s
sys	0m0,021s

SUMMARY: (THREADS - 1) faster than normal
*/

template<int THREADS>
struct Parallel {
  int fd[THREADS][2];
  vector<pid_t> cpids;
  int my_fd[2], my_i = -1;
  bool is_master = true;

  vector<FILE*> writing, reading;

  Parallel(){
    for(int i = 0; i < THREADS; i++){
      pid_t cpid;
      assert(pipe(fd[i]) >= 0);
      cpid = fork();
      assert(cpid >= 0);
      if(cpid == 0){
        cpids.clear();
        my_fd[0] = fd[i][0];
        my_fd[1] = fd[i][1];
        my_i = i;
        is_master = false;
        break;
      }
      cpids.push_back(cpid);
    }
    if(cpids.size()){
      for(int i = 0; i < THREADS; i++){
        reading.push_back(fdopen(fd[i][0], "r"));
        writing.push_back(fdopen(fd[i][1], "w"));
      }
    }else{
      reading.push_back(fdopen(my_fd[0], "r")); 
      writing.push_back(fdopen(my_fd[1], "w"));
    }
  }

  void run(){
    if(is_master){
      master();
      for(int i = 0; i < THREADS; i++)
        wait(NULL);
    }else child();
  }

  void master(){
/*
  fscanf(reading[THREAD_ID], "<format>", &input...);
*/
    long long sum = 0;
    for(int i = 0; i < THREADS; i++){
      long long x;
      fscanf(reading[i], "%lld", &x);
      sum += x;
    }
    printf("%lld\n", sum);
  }

  void child(){
/*
  fprintf(writing[0], "<format>", output..);
*/
    const int n = 10000;
    int L = n * my_i / THREADS + 1, R = n * (my_i + 1) / THREADS;
    long long sum = 0;
    for(int i = L; i <= R; i++)
      for(int j = 1; j <= n; j++)
        sum += gcd(i, j);
    fprintf(writing[0], "%lld\n", sum);
  }
};

int main(){
  Parallel<4> p;
  p.run(); 
}
