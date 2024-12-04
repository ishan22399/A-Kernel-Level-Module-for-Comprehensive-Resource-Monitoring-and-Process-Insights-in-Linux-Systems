# KMonPro: Kernel-Level Module for Comprehensive Resource Monitoring and Process Insights in Linux Systems

![High-Level Architecture](https://github.com/user-attachments/assets/7301644a-152f-4ba2-8ef9-df4219736a31)

## Overview
**KMonPro** is an innovative Linux kernel module designed for real-time resource monitoring and process insights. It integrates directly with the Linux kernel, enabling accurate, low-latency monitoring of system performance, resource allocation, and process management. 

### Features
- **Real-Time Resource Monitoring**: Monitors CPU, memory, network, and process activity with precision.
- **CLI-Based Operation**: Lightweight and command-line-friendly for ease of use by system administrators.
- **Dynamic Resource Allocation**: Utilizes adaptive policies for efficient resource management.
- **Process-Level Network Correlation**: Links network activity to specific processes for enhanced analysis.
- **Security Integration**: Enforces access control and isolation for improved system stability and security.

## Architecture
KMonPro's architecture bridges **kernel-space** and **user-space** interactions, providing an intuitive interface (`/proc/kmonpro`) for continuous resource monitoring. The core layers include:
1. **User Interface Layer**: Command-line operations for technical users.
2. **Userspace Communication Layer**: Handles communication between user commands and the kernel module.
3. **Kernel Module Layer**: Implements hooks into resource management subsystems like CPU scheduling and memory management.
4. **Resource Management Layer**: Dynamically adjusts resource allocation and enforces security.

Refer to the architecture diagram above for a detailed visual representation.

## Installation

### Prerequisites
- Linux-based operating system.
- Kernel development tools (e.g., `make`).
- Superuser (root) privileges.

### Steps
1. **Clone the Repository**
   ```bash
    git clone https://github.com/ishan22399/A-Kernel-Level-Module-for-Comprehensive-Resource-Monitoring-and-Process-Insights-in-Linux-Systems.git
    cd A-Kernel-Level-Module-for-Comprehensive-Resource-Monitoring-and-Process-Insights-in-Linux-Systems

2. **Compile the Module**
   ```bash
   make
   
3. **Load the Module**
    ```bash
    sudo insmod kmonpro.ko
    
4. **Verify Module Loading**
    ```bash
    dmesg | tail
    cat /proc/kmonpro

## Usage

### Monitoring Script
Use the provided script for real-time monitoring of system resources:

    ```bash
    #!/bin/bash
    while true; do
        cat /proc/kmonpro
        echo "-------------------------------------------"
        sleep 5
    done
    
1. **Make the script executable:**
   ```bash
    chmod +x monitor.sh
   
2. **Run the script:**
   ```bash
   ./monitor.sh

  ### Module Unloading
  To safely remove the module:

      sudo rmmod kmonpro
      dmesg | tail

## Contribution
Contributions are welcome! Please open an issue or submit a pull request.
