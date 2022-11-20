# Emulate x86 architecture
FROM --platform=linux/x86_64 ubuntu:latest

# Switch apt source to mirror
RUN sed -i "s/archive.ubuntu.com/mirrors.ustc.edu.cn/g" /etc/apt/sources.list
RUN sed -i "s/security.ubuntu.com/mirrors.ustc.edu.cn/g" /etc/apt/sources.list

# Install packages
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential sudo git locales zsh vim perl curl \ 
    && apt-get clean -y

# Generate locale
RUN locale-gen --no-purge en_US.UTF-8

# Create a user to show my student ID
ARG USERNAME="PB20061372"
RUN useradd $USERNAME -m \
    && echo "$USERNAME ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
USER $USERNAME

# Install oh-my-zsh and set theme to fino-time (my favorite)
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" ""
RUN sed -i "s/robbyrussell/fino-time/g" ~/.zshrc