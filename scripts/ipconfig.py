import os
import subprocess
import re
import platform
import math
import shutil

if __name__ == "__main__":

    eth_exists = False
    wifi_exists = False
    
    # Find device names of ethernet and Wi-Fi network interfaces
    for root, subdirs, files in os.walk("/sys/class/net"):
        for subdir in subdirs:
            # Ethernet network interface exists if subdirectory name starts with "en"
            if subdir[:2] == "en":
                eth_exits = True
                eth_device_name = subdir
            # Wi-Fi network interface exists if subdirectory name starts with "wlx"
            if subdir[:3] == "wlx":
                wifi_exists = True
                wifi_device_name = subdir
    
    if eth_exits:
        # Find MAC address of ethernet device
        cmd = f"ip addr show {eth_device_name}"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        tokens = output.decode("utf-8").split()
        index = tokens.index("link/ether")
        eth_mac_address = tokens[index + 1]

        # Check if ethernet connection is established
        cmd = f"cat /sys/class/net/{eth_device_name}/carrier"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        if output.decode("utf-8").split()[0] == "0":
            eth_media_state = "Media disconnected"
        else:
            eth_media_state = "Media connected"
    else:
        eth_device_name = "NONE"
        eth_mac_address = "NONE"
        eth_media_state = "NONE"

    if wifi_exists:
        # Find MAC address of Wi-Fi device
        cmd = f"ip addr show {wifi_device_name}"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        tokens = output.decode("utf-8").split()
        index = tokens.index("link/ether")
        wifi_mac_address = tokens[index + 1]

        # Check if Wi-Fi connection is established
        cmd = f"cat /sys/class/net/{wifi_device_name}/carrier"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        if output.decode("utf-8").split()[0] == "0":
            wifi_media_state = "Media disconnected"
        else:
            wifi_media_state = "Media connected"
    else:
        wifi_device_name = "NONE"
        wifi_mac_address = "NONE"
        wifi_media_state = "NONE"

    if eth_media_state == "Media connected":
        # Find IPv6 address of ethernet device
        cmd = f"ip -6 addr show {eth_device_name}"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        eth_ipv6_address = re.findall("(?<=inet6\s)[\da-f:]+", output.decode("utf-8"))[0]
        
        # Find IPv4 address of ethernet device
        cmd = f"ip -4 addr show {eth_device_name}"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        tokens = output.decode("utf-8").split()
        index = tokens.index("inet")
        eth_ipv4_address = tokens[index + 1]
        eth_ipv4_address = eth_ipv4_address.split("/")[0]
        
        # Find Wi-Fi subnet mask
        cmd = f"ifconfig {eth_device_name}"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        tokens = output.decode("utf-8").split()
        index = tokens.index("netmask")
        eth_subnet_mask = tokens[index + 1]
    else:
        eth_ipv6_address = "NONE"
        eth_ipv4_address = "NONE"
        eth_subnet_mask  = "NONE"

    if wifi_media_state == "Media connected":
        # Find IPv6 address of Wi-Fi device
        cmd = f"ip -6 addr show {wifi_device_name}"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        wifi_ipv6_address = re.findall("(?<=inet6\s)[\da-f:]+", output.decode("utf-8"))[0]
        
        # Find IPv4 address of Wi-Fi device
        cmd = f"ip -4 addr show {wifi_device_name}"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        tokens = output.decode("utf-8").split()
        index = tokens.index("inet")
        wifi_ipv4_address = tokens[index + 1]
        wifi_ipv4_address = wifi_ipv4_address.split("/")[0]
        
        # Find Wi-Fi BSSID for currently established connection
        cmd = f"iw dev {wifi_device_name} link"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        tokens = output.decode("utf-8").split()
        wifi_bssid = tokens[2]
        
        # Find Wi-Fi subnet mask
        cmd = f"ifconfig {wifi_device_name}"
        process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()
        tokens = output.decode("utf-8").split()
        index = tokens.index("netmask")
        wifi_subnet_mask = tokens[index + 1]
    else:
        wifi_ipv6_address = "NONE"
        wifi_ipv4_address = "NONE"
        wifi_bssid        = "NONE"
        wifi_subnet_mask  = "NONE"
    
    # Find system device name
    sys_device_name = os.uname().nodename

    # Find system total physical memory
    with open("/proc/meminfo") as file:
        for line in file:
            if "MemTotal" in line:
                sys_memory = str(format(float(math.ceil(int(line.split()[1].split()[0])/(10**6))), ".2f")) + " GB" 
                break       
        file.close()

    # Find system processor model name
    cmd = "lscpu"
    process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
    output, error = process.communicate()
    tokens = output.decode("utf-8").split("\n")
    for token in tokens:
        if "Model name:" in token:
            sys_processor = " ".join(token.split()[2:])
            break

    # Find system primary disk total capacity
    sys_disk_capacity = str(math.ceil(shutil.disk_usage("/")[0]/(10**9))) + " GB"
    
    # Find system operating system name
    cmd = "lsb_release -a"
    process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
    output, error = process.communicate()
    tokens = output.decode("utf-8").split("\n")
    for token in tokens:
        if "Description:" in token:
            sys_os_name = " ".join(token.split()[1:])
            break

    # Find system operating system architecture
    sys_os_type = "64-bit" if os.uname().machine == "x86_64" else "32-bit" if os.uname().machine == "x86" else "NONE"

    print("")
    print("Linux IP Configuration v1.0-beta")
    print("Copyright (C) 2022 Yahya Mateen")
    print("Licensed under GNU-GPLv3")
    
    print("")
    print("System information:")
    print("")
    print(f"\tDevice Name .................... : {sys_device_name}")
    print(f"\tMemory ......................... : {sys_memory}")
    print(f"\tProcessor ...................... : {sys_processor}")
    print(f"\tDisk Capacity .................. : {sys_disk_capacity}")
    print(f"\tOS Name ........................ : {sys_os_name}")
    print(f"\tOS Type ........................ : {sys_os_type}")

    print("")
    print("Ethernet adapter Local Area Connection:")
    print("")
    print(f"\tDevice ......................... : {eth_device_name}")
    print(f"\tMAC Address .................... : {eth_mac_address}")
    print(f"\tMedia State .................... : {eth_media_state}")
    print(f"\tIPv4 Address ................... : {eth_ipv4_address}")
    print(f"\tSubnet Mask .................... : {eth_subnet_mask}")
    print(f"\tIPv6 Address ................... : {eth_ipv6_address}")

    print("")
    print("Wireless LAN adapter Wi-Fi:")
    print("")
    print(f"\tDevice ......................... : {wifi_device_name}")
    print(f"\tMAC Address .................... : {wifi_mac_address}")
    print(f"\tMedia State .................... : {wifi_media_state}")
    print(f"\tBSSID .......................... : {wifi_bssid}")
    print(f"\tIPv4 Address ................... : {wifi_ipv4_address}")
    print(f"\tSubnet Mask .................... : {wifi_subnet_mask}")
    print(f"\tIPv6 Address ................... : {wifi_ipv6_address}")