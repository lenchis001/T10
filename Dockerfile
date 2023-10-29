FROM ubuntu

RUN apt update && apt install g++ cmake make p7zip-full wget libxxf86vm-dev -y

# Preparing libs
RUN mkdir /Libs

WORKDIR /Libs
RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.7z && 7z x ./boost_1_82_0.7z && rm ./boost_1_82_0.7z
WORKDIR /Libs/boost_1_82_0
RUN ./bootstrap.sh && ./b2 link=static variant=release cxxflags=-fPIC cflags=-fPIC
ENV BOOST_ROOT=/Libs/boost_1_82_0

# Preparing libs finished

RUN mkdir /Project
WORKDIR /Project
COPY . .
RUN mkdir /Project/build
WORKDIR /Project/build
RUN cmake .. && make -j4