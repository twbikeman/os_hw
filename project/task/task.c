#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>


int task_lister_linear_init(void) {
  struct task_struct *task;
  printk(KERN_INFO "Loading module ...\n");
 
  for_each_process(task) {
    printk(KERN_INFO "pid: %d | pname: %s | state: %ld\n", task->pid, task->comm, task->state);
  }

  printk(KERN_INFO "Module loaded.\n");
  return 0;
}


void task_lister_linear_exit(void) {
  printk(KERN_INFO "Module removed.\n");
}

module_init(task_lister_linear_init);
module_exit(task_lister_linear_exit);

MODULE_LICENSE("GPL");
