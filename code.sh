#!/bin/bash

# Step 1: System Update
sudo apt update
sudo apt upgrade -y

# NOTE: If dpkg gets interrupted, kill this script and run:
# cd /var/lib/dpkg/updates && sudo rm * && sudo apt update && sudo apt upgrade -y && sudo apt --fix-broken install && sudo apt update && sudo apt upgrade -y

# Step 2: Set Locale
locale
sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
locale

# Step 3: Setup Sources
sudo apt install software-properties-common
sudo add-apt-repository universe
sudo apt update && sudo apt install curl -y
export ROS_APT_SOURCE_VERSION=$(curl -s https://api.github.com/repos/ros-infrastructure/ros-apt-source/releases/latest | grep -F "tag_name" | awk -F'"' '{print $4}')
curl -L -o /tmp/ros2-apt-source.deb "https://github.com/ros-infrastructure/ros-apt-source/releases/download/${ROS_APT_SOURCE_VERSION}/ros2-apt-source_${ROS_APT_SOURCE_VERSION}.$(. /etc/os-release && echo ${UBUNTU_CODENAME:-${VERSION_CODENAME}})_all.deb"
sudo dpkg -i /tmp/ros2-apt-source.deb

# Step 4: Install ROS2 Humble
sudo apt update && sudo apt upgrade -y
sudo apt install -y ros-humble-desktop
sudo apt install -y ros-dev-tools

# Step 5: Source Setup
source /opt/ros/humble/setup.bash
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

# Step 6: Install Gazebo & ROS2 Bridges
sudo apt install -y gazebo gazebo-plugin-base
sudo apt install -y libgazebo-dev
sudo apt install -y ros-humble-gazebo-ros-pkgs ros-humble-gazebo-plugins

# Step 7: Development Tools
sudo apt install -y build-essential cmake git python3-dev python3-pip
sudo apt install -y python3-colcon-common-extensions

# Step 8: Python Dependencies
pip install numpy scipy matplotlib pandas pytest pytest-asyncio pymavlink sympy plotly black pylint

# Step 9: Verify Installation
cd /opt/ros
ls -la
gazebo --version
python3 -c "import numpy, scipy; print('Python deps OK')"

# Test ROS2 environment
echo $ROS_DISTRO
Step 10: Clone & Setup Project Repository (Optional - if you have the repo URL)
cd ~
git clone <your-repo-url> Sentinel-AI
cd Sentinel-AI
Step 11: Create ROS2 Package Structure (After cloning)
cd ~/Sentinel-AI
mkdir -p swarm_core config tests launch
touch swarm_core/__init__.py