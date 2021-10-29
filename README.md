# OS-Assignment-1
Producer Consumer Problem

## About The Project
The code for this project covers the producer consumer problem. In this problem the producer should put values in the array and the consumer should take values out. The producer should wait to execute if the array is full or the consumer is using the critical code they share. The consumer should wait if the array is empty or the producer is using the critical code. This project implements a solution to this problem using a single file, pthreads, semaphores, and shared memory.

## Built With
This project was originally built on MobaXTerm.

## Getting Started
### Prerequisites
The prerequisites for this code involve making sure g++ is installed and the pthread library is installed if not automatically installed.
To install g++ on MobaXTerm, use the following command.

`apt-get install gcc-g++`

### Installation
To install the code for this project, either copy and paste the code into a file on your computer, or type the following command.

`git clone https://github.com/JarekHeath/OS-Assignment-1/blob/a03a08d4e3480c7ef24c933e4c2202964165ea12/producer_consumer.cpp`

## Usage
To use and compile this program, run the following commands.

`g++ producer_consumer.cpp -pthread -lrt -o producer_consumer`

`./producer_consumer &`

If you would like to exit the program before it has finished, press the following keys.

ctrl and c

## Example of Output
The following is an example of an output when the amount of times the program should loop is equal to 10.

![image](https://user-images.githubusercontent.com/92826628/139353510-1e6bec1f-ba1d-4d4b-af21-9c4045739ad5.png)

## Contact
Email: jheath10@kent.edu

## Acknowledgments
Inspiration from code shown during Qiang Guan's Operating System's class.
