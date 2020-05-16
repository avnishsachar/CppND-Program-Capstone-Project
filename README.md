# CPPND: Capstone Project

## Object Detection in C++ with OpenCV

<img src="output/out.jpg"/>

## Overview
This is the capstone project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). I implemented an object detection model using OpenCV. The program read an image file and then performs object detection on it. Finally, it gives an output image which is the original image with bounding boxes over the detected objects in the image. The bounding boxes also have an overlay of the detected class and the confidence value. This program is modular in the sense that it can be used for various Deep Neural Network Models (but it has only been tested with [yolov3](https://pjreddie.com/darknet/yolo/) and [yolov3-tiny](https://pjreddie.com/darknet/yolo/)). By default, the scripts will load the yolov3-tiny model (it needs less computation compared to other yolo models at the expense of performance). The program is run through the command line and takes in various options and input parameters.


## File Structure

This repository contains:
- `data/` : Contains sample input image data that may be used for the program.

- `include/` : Constains the header files `buffer.h`, `input.h`, `output.h`, `object_detector.h` files.

- `model/` : Constains a script `getModel.sh` to download and generate the model weight, configuration and class names files for the yolov3-tiny DNN model. 

- `output/` : The output image file of the program will be generated and saved here.

- `src/` : Source. Constains the `main.cpp`, `input.cpp`, `output.cpp`, `object_detector.cpp` files.

- `CMakeLists.txt` : cmake configuration file

- `README.md` : This file


## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1.x
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/master)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

  **! This repository has been successfully built and tested on Ubuntu 18.08 with OpenCV 4.1 running C++14.**

## Build Instructions

1. Clone this repo using `git clone https://github.com/avnishsachar/CppND-Program-Capstone-Project.git`
2. Enter the root directory of the repository using `cd CppND-Program-Capstone-Project`
3. `cd model`
4. `sudo chmod a+x getModel.sh`
5. `./getModel.sh`
5. `cd ..`
3. `mkdir build && cd build`
4. `cmake ..`
5. `make`

The executable(`objectdetector`) is created in the current directory(`build`).

## Run

In `build` directory, run the executable like below:

`./objectdetector [options] --input=<image-file>`

- `<image-file>` is the **absolute file path with no preceding space** to the image you want to input.
- Options:
 - `-c` : specifies the *confidence threshold* between 0 and 1.0. If omitted, default value is 0.5.
 - `-n` : specifies the threshold used for *Non-max Suppression* between 0 and 1.0. If omitted, default value is 0.4.
 - `-h` `-?` `--help` `--usage`: Shows usage.

 #### Example

`./objectdetector --input=/home/avnish/CppND-Capstone-Project/data/coffee.jpg`

## Rubric

__README (All Rubric Points REQUIRED)__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | A README with instructions is included with the project |The README is included with the project and has instructions for building/running the project. If any additional libraries are needed to run the project, these are indicated with cross-platform installation instructions. You can submit your writeup as markdown or pdf.| |
| :heavy_check_mark: | The README indicates which project is chosen. | The README describes the project you have built. The README also indicates the file and class structure, along with the expected behavior or output of the program. | |
| :heavy_check_mark: | The README includes information about each rubric point addressed. | The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed. | |

__Compiling and Testing (All Rubric Points REQUIRED)__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | The submission must compile and run. | The project code must compile and run without errors. We strongly recommend using cmake and make, as provided in the starter repos. If you choose another build system, the code must compile on any reviewer platform. |

__Loops, Functions, I/O__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | The project demonstrates an understanding of C++ functions and control structures.| A variety of control structures are used in the project. The project code is clearly organized into functions.| Every *.cpp file |
| :heavy_check_mark: | The project reads data from a file and process the data, or the program writes data to a file. | The project reads data from an external file or writes data to a file as part of the necessary operation of the program.| reads image frame in main.cpp  |
| :heavy_check_mark: | The project accepts user input and processes the input.|The project accepts input from a user as part of the necessary operation of the program.|  main.cpp parses command line arguments |

__Object Oriented Programming__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | The project uses Object Oriented Programming techniques. | The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks. | All *.cpp and *.h files |
| :heavy_check_mark: | Classes use appropriate access specifiers for class members. | All class data members are explicitly specified as public, protected, or private.| All *.cpp and *.h files |
| :heavy_check_mark: | Class constructors utilize member initialization lists. | All class members that are set to argument values are initialized through member initialization lists.| All *.cpp and *.h files |
| :heavy_check_mark: | Classes abstract implementation details from their interfaces. | All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.| All *.cpp and *.h files |
| :heavy_check_mark: | Classes encapsulate behavior. | Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.| All *.cpp and *.h files |
| | Classes follow an appropriate inheritance hierarchy. | Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.|  |
|  | Overloaded functions allow the same function to operate on different parameters. |  |
|  | Derived class functions override virtual base class functions. |One member function in an inherited class overrides a virtual base class member function.| |
| :heavy_check_mark: | Templates generalize functions in the project. | One function is declared with a template that allows it to accept a generic parameter.| Done so with in buffer.h|

__Memory Management__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| :heavy_check_mark: | The project makes use of references in function declarations. | At least two variables are defined as references, or two functions use pass-by-reference in the project code.|Extensively done so in multiple functions in object_detector.h |
| :heavy_check_mark: | The project uses destructors appropriately. | At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor. | input.h for class Input|
|  | The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. | The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.| |
| :heavy_check_mark: | The project follows the Rule of 5. | For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.| Done in object_detector.h for class ObjectDetector |
| :heavy_check_mark: | The project uses move semantics to move data, instead of copying it, where possible. | For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object. | Done in object_detector.cpp for class ObjectDetector  |
| :heavy_check_mark: | The project uses smart pointers instead of raw pointers. | The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.| used in main.cpp |

__Concurrency__

|DONE | CRITERIA | MEETS SPECIFICATIONS| WHERE |
|-- | -- | --| -- |
| | The project uses multithreading. | The project uses multiple threads in the execution.| |
|  | A promise and future is used in the project. | A promise and future is used to pass data from a worker thread to a parent thread in the project code.| |
| :heavy_check_mark: | A mutex or lock is used in the project. | A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.| used in Buffer extensively |
|  | A condition variable is used in the project. | A std::condition_variable is used in the project code to synchronize thread execution.| |

## Reference

[1] https://github.com/opencv/opencv/blob/master/samples/dnn/object_detection.cpp
