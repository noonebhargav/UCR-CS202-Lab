#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "user/user.h"
#include "user/thread.h"
#include "riscv.h"

int thread_create(void *(start_routine)(void*), void *arg)
{
  void* stack = (void*)malloc(PGSIZE * sizeof(void));
  if(clone(stack) == 0){
    (*start_routine) (arg);
    exit(0);
  }
  return 0;
}

void lock_init(struct lock_t* lock){
  lock->locked=0;
  return;
}

void lock_acquire(struct lock_t* lock){
  while(__sync_lock_test_and_set(&lock->locked, 1));
  return;
}

void lock_release(struct lock_t* lock){
  __sync_lock_release(&lock->locked);
  return;
}