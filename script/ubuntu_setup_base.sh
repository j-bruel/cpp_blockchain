#! /bin/bash

# Install  GCC11 on 20.04
apt update -y
apt install -y  apt-transport-https ca-certificates software-properties-common curl
add-apt-repository 'deb http://mirrors.kernel.org/ubuntu jammy main universe'
apt install -y libstdc++6

# Install MSSql ODBC 18 driver
su -c '
curl https://packages.microsoft.com/keys/microsoft.asc | apt-key add -
curl https://packages.microsoft.com/config/ubuntu/$(lsb_release -rs)/prod.list > /etc/apt/sources.list.d/mssql-release.list
'

apt update -y
ACCEPT_EULA=Y apt install -y msodbcsql18