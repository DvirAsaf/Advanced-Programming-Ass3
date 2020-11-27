cmake_minimum_required(VERSION 3.16)
project(untitled3)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled3 main.cpp anomaly_detection_util.h anomaly_detection_util.cpp AnomalyDetector.h timeseries.h SimpleAnomalyDetector.cpp timeseries.cpp MainTrain.cpp mainTime.cpp SimpleAnomalyDetector.h)