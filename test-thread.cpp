#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <cassert>

using namespace std;


void * threadEntryPoint(void *threadid) {
  long tid;
   tid = (long)threadid;
   cout << endl << "Thread Entry Point! Thread ID, " << tid << endl;
   pthread_exit(NULL);
}

void createThread(const std::string &name, void *(*start_routine)(void *), uint32_t prio)

{

  pthread_t thread_id;
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  if (prio != UINT32_MAX) { //Use UINT32_MAX in unit test

    struct sched_param param;

    param.sched_priority = prio;

    std::cout << name << " 1 thread priority is " << prio << std::endl;
    auto ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

    if (ret != 0) {
      std::cout << name << " could not set sched policy, errno " << ret << std::endl;
    }

    ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

    if (ret != 0) {
      std::cout << name << " could not set inherit sched, errno " << ret << std::endl;
    }

    ret = pthread_attr_setschedparam(&attr, &param);

    if (ret != 0) {
      std::cout << name << " could not set sched param, errno " << ret << std::endl;
    }
  }

  auto ret2 = pthread_create(&thread_id, &attr, start_routine, NULL);

  std::cout << name << " 2 thread priority is " << prio << std::endl;

  if (ret2 != 0) {
    std::cout << name << " could not create thread, errno " << ret2 << std::endl;
  } else {
    std::cout << name << " thread created, errno " << ret2 << std::endl;
  }

  assert(0 == ret2); //This assert is getting raised .

  pthread_setname_np(thread_id, name.c_str());
  pthread_attr_destroy(&attr);

}

int main () {

  const std::string tname="testThread";

  createThread(tname, threadEntryPoint, 2);
}
