// tony.c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/sched/signal.h>
#include <linux/seq_file.h>
#include <linux/vmstat.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cpu.h>
#include <linux/netdevice.h>
#include <linux/sysinfo.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Tony Kernel Module for Resource Monitoring");

// Function declarations
static int show_resources(struct seq_file *m, void *v);
static int resource_open(struct inode *inode, struct file *file);

// Define proc_ops structure
static const struct proc_ops fops = {
    .proc_open = resource_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int show_resources(struct seq_file *m, void *v) {
    unsigned long cpu_load; // Variable for CPU load
    struct sysinfo i;       // Variable for system info
    struct net_device *dev; // Variable for network devices
    struct task_struct *task; // Variable for tasks

    // Placeholder for CPU Usage (no actual idle time retrieval)
    cpu_load = 0;

    // Print CPU usage
    seq_printf(m, "CPU Usage: %lu jiffies\n", cpu_load);

    // Get and print memory information
    si_meminfo(&i);
    seq_printf(m, "Total RAM: %lu MB\n", i.totalram >> 10);
    seq_printf(m, "Free RAM: %lu MB\n", i.freeram >> 10);

    // Print network interface statistics
    for_each_netdev(&init_net, dev) {
        seq_printf(m, "Interface: %s\n", dev->name);
        seq_printf(m, "RX Packets: %lu\n", dev->stats.rx_packets);
        seq_printf(m, "TX Packets: %lu\n", dev->stats.tx_packets);
    }

    // Print process information
    seq_printf(m, "\nProcesses:\n");
    for_each_process(task) {
        if (task->mm) { // Check if task has a memory descriptor
            seq_printf(m, "PID: %d, Command: %s, Virtual Runtime: %llu, Memory Usage: %lu KB\n",
                       task->pid, task->comm, task->se.vruntime, task->mm->total_vm >> 10);
        } else {
            seq_printf(m, "PID: %d, Command: %s, Kernel thread\n",
                       task->pid, task->comm);
        }
    }

    return 0; // Return 0 on success
}

static int resource_open(struct inode *inode, struct file *file) {
    return single_open(file, show_resources, NULL); // Open the proc file
}

static int __init tony_init(void) {
    // Create the /proc/tony entry
    if (!proc_create("tony", 0, NULL, &fops)) {
        return -ENOMEM; // Return error if proc entry creation fails
    }
    printk(KERN_INFO "Tony Monitor Module Loaded\n"); // Log message
    return 0; // Return 0 on success
}

static void __exit tony_exit(void) {
    remove_proc_entry("tony", NULL); // Remove the proc entry
    printk(KERN_INFO "Tony Monitor Module Unloaded\n"); // Log message
}

module_init(tony_init); // Module initialization
module_exit(tony_exit); // Module cleanup

