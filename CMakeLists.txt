cmake_minimum_required(VERSION 3.13)
project(lotterySystem C)

set(CMAKE_C_STANDARD 99)

add_executable(lotterySystem lotteryServer.c lotteryServer.h lotteryClient.c lotteryClient.h)