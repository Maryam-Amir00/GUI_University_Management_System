# University Management System

## Overview
This project is a GUI-based University Management System implemented in C++ using the Qt framework. It provides functionality for managing students, teachers, and administrative tasks within a university setting.

## Features
The system is divided into three main sections:

### 1. Admin Section
- Student management:
  - Add student
  - Remove student
  - Update student information
  - Check student records
- Teacher management:
  - Add teacher
  - Remove teacher
  - Update teacher information
  - Check teacher records
- Log out functionality

### 2. Student Section
- Check information: Allows students to view their information using their roll number
- Check existence: Verifies if a student exists in the records

### 3. Teacher Section
- Check information: Allows teachers to view their information using their ID
- Check existence: Verifies if a teacher exists in the records

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
   make
   ```
5. Run the executable generated in the `build` directory

## Contributing
Contributions to improve the University Management System are welcome. Please feel free to fork the repository, make changes, and submit a pull request.


