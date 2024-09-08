# University Management System

## Overview
This project is a GUI-based University Management System implemented in C++ using the Qt framework. It provides functionality for managing students, teachers, and administrative tasks within a university setting.

## Features
- Student management (add, remove, update, view)
- Teacher management (add, remove, update, view)
- Admin authentication
- Record checking and information retrieval
- User-friendly graphical interface

## Project Structure
The project is organized into several components:
- `build/`: Contains build-related files
- Source files:
  - Student-related: `addstudent`, `removestudent`, `updatestudent`, `studentdes`, `studentexist`
  - Teacher-related: `addteacher`, `removeteacher`, `updateteacher`, `teacherdes`, `teacherexist`
  - Authentication: `adminauthenticate`, `studentauthenticate`, `teacherauthenticate`
  - Information checking: `checkinfo`, `checkrecords`, `checkteacher`, `checkteacherinfo`
  - Main application: `main`, `mainwindow`
  - Other utility files: `struct`, `CMakeLists.txt`

## Technical Details
- Language: C++
- GUI Framework: Qt
- Build System: CMake
- File Types:
  - `.cpp`: C++ source files
  - `.h`: C++ header files
  - `.ui`: Qt UI files

## Getting Started
1. Clone the repository
2. Ensure you have Qt and CMake installed on your system
3. Navigate to the project directory
4. Run the following commands:
   ```
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
5. Run the executable generated in the `build` directory

## Contributing
Contributions to improve the University Management System are welcome. Please feel free to fork the repository, make changes, and submit a pull request.

