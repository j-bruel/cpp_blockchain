#! /bin/bash
# upgrade apt
apt update -y
apt upgrade -y
apt remove -y gpg

# install current script tools
apt install -y gnupg1 apt-transport-https ca-certificates software-properties-common wget curl git

# add microsoft SQL server driver v18 entry in local apt repo (specific for unbuntu 22.04)
su -c '
curl https://packages.microsoft.com/keys/microsoft.asc | apt-key add -
curl https://packages.microsoft.com/config/ubuntu/$(lsb_release -rs)/prod.list > /etc/apt/sources.list.d/mssql-release.list
'

# add kitware cmake repo
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
apt-add-repository 'deb https://apt.kitware.com/ubuntu/ jammy main'
apt update -y
apt install -y kitware-archive-keyring
rm /etc/apt/trusted.gpg.d/kitware.gpg

# install compiling tools
apt install -y zip unzip tar gdb pkg-config cmake
apt install -y build-essential software-properties-common
apt install -y ninja-build 
add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt update -y

# install gcc v12
apt install -y g++-12
# setting compiler alternatives
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 120 --slave /usr/bin/g++ g++ /usr/bin/g++-12 --slave /usr/bin/gcov gcov /usr/bin/gcov-12

# install sql server odbc driver
ACCEPT_EULA=Y apt install -y msodbcsql17
ACCEPT_EULA=Y apt install -y mssql-tools
# install odbc development resources
apt install -y unixodbc-dev
apt install -y libtool

# install powershell for CI scripts
apt install -y powershell

# visual tool to remote debug in 
apt install -y rsync autoconf openssh-server
# install mono to be able launch nuget commands
apt install -y mono-devel
# storage of git cred as text
# on first time asked then never
git config --global credential.helper store
# install language pack for support of std::locale utf8
apt install -y language-pack-en