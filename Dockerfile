FROM debian:testing

RUN sh -c "echo 'deb http://llvm.org/apt/wheezy/ llvm-toolchain-wheezy main' >> /etc/apt/sources.list"
RUN apt-get update -qq
RUN apt-get install -qq wget apt-utils
RUN wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | apt-key add -
RUN apt-get update -qq
RUN apt-get install -qq gnulib autoconf-archive libllvm3.4 llvm-3.4 llvm-3.4-dev llvm-3.4-runtime libboost-dev zlib1g-dev
RUN apt-get install -qq g++-4.8 git

RUN git clone https://github.com/kmc-jp/Klang.git
WORKDIR Klang
RUN git checkout -b llvm origin/llvm
RUN ACLOCAL_ARGS="-I/usr/share/gnulib/m4" ./autogen.sh;
RUN ln -s /usr/bin/llvm-config-3.4 /usr/bin/llvm-config
RUN apt-get install -qq libc++-dev libncurses5-dev libncursesw5-dev
