# Global args
ARG CENTOR_USER=centor
ARG CENTOR_HOME=/home/$CENTOR_USER

# This stage contains the basic Ubuntu image with some prerequisites 
# required by the current project (GCC11 and ODBC driver)
FROM ubuntu:22.04 AS base
LABEL description="Base Ubuntu image with the minimum requirement"

COPY ./script/ubuntu_setup_base.sh /tmp
RUN chmod +x /tmp/ubuntu_setup_base.sh
RUN /tmp/ubuntu_setup_base.sh
RUN rm -f /tmp/ubuntu_setup_base.sh

FROM base AS devenv

LABEL description="Container for use with Visual Studio" 

# Avoid blocking on tzdata interactive dialog
ARG DEBIAN_FRONTEND=noninteractive

COPY ./script/ubuntu_setup_devenv.sh /tmp
RUN chmod +x /tmp/ubuntu_setup_devenv.sh
RUN /tmp/ubuntu_setup_devenv.sh

# Configure SSH for communication with Visual Studio 
RUN mkdir -p /var/run/sshd
RUN echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config && ssh-keygen -A

# Create user to connect with Visual Studio
ARG CENTOR_USER=centor
ARG CENTOR_HOME=/home/$CENTOR_USER
RUN useradd -m -d $CENTOR_HOME -s /bin/bash -G sudo $CENTOR_USER
RUN echo "$CENTOR_USER:centor"|chpasswd

USER $CENTOR_USER

# Install VCPKG
ARG CENTOR_VCPKG_ROOT=$CENTOR_HOME
RUN mkdir -p $CENTOR_VCPKG_ROOT
WORKDIR $CENTOR_VCPKG_ROOT
RUN git clone https://github.com/Microsoft/vcpkg.git \ 
    && cd vcpkg \
    && ./bootstrap-vcpkg.sh

ARG CENTOR_GITHUB_TOKEN

# Set up git credentials for private repo access
RUN git config --global credential.helper store
RUN echo "https://x-oauth-basic:$CENTOR_GITHUB_TOKEN@github.com" > $CENTOR_HOME/.git-credentials

USER root
ENTRYPOINT service ssh start && /bin/bash

FROM devenv AS build

ARG CENTOR_USER=centor
ARG CENTOR_HOME=/home/$CENTOR_USER

USER $CENTOR_USER
RUN mkdir -p $CENTOR_HOME/cpp_blockchain
COPY --chown=$CENTOR_USER . $CENTOR_HOME/cpp_blockchain

ENV ENABLE_TESTING="ON"

WORKDIR $CENTOR_HOME/cpp_blockchain
RUN cmake --preset linux-gcc-release
RUN cmake --build ./out/linux-gcc-release

FROM build AS test

ARG CENTOR_USER=centor
ARG CENTOR_HOME=/home/$CENTOR_USER

ENV CENTOR_HOME=$CENTOR_HOME
ENTRYPOINT $CENTOR_HOME/cpp_blockchain/out/linux-gcc-release/runtime/tests_my_blockchain

# This is the small final target 
# that have to go in production
FROM base as runtime

ARG CENTOR_USER=centor
ARG CENTOR_HOME=/home/$CENTOR_USER

# prepare the machine
RUN mkdir cpp_blockchain

# copy all requires binaries and files
COPY --from=build $CENTOR_HOME/cpp_blockchain/_out/RelWithDebInfo/install/bin cpp_blockchain/

WORKDIR /cpp_blockchain/

EXPOSE 3000

ENTRYPOINT ./blockchain_server