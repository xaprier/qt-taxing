# qt-taxing

A tax editor and querying GUI application using JSON and Qt

## Building Project

First of all you need to install Qt packages from it's own <a href="https://www.qt.io/download">website</a>.
And for building the project you need CMake. You can easily learn how to install the CMake and Qt with googling.

Clone the repository

```
git clone https://github.com/xaprier/qt-taxing.git
```

Enter the repository folder

```
cd qt-taxing
```

Execute the CMake build command

```
cmake CMakeLists.txt -B build/
```

Enter and run the project binary file

```
./build/VergiSistemi
```

# Documentation

## <a href="https://github.com/xaprier/qt-taxing/tree/main/data">data</a> Directory

An example data json files in that directory.

logins.json is the data file which includes the tax manager user login infos. You can add or change them manually.s

users.json is the data file which includes the users which will give tax for the author. You can add users to them manually(not recommended) or with management GUI

## <a href="https://github.com/xaprier/qt-taxing/tree/main/cpp-files">cpp-files</a> Directory

All the .cpp files of project in this directory, header and cpp files seperated.

- <a href="https://github.com/xaprier/qt-taxing/blob/main/cpp-files/logindialog.cpp">cpp-files/logindialog.cpp</a> is the Qt Dialog class which check the username and password and according to that logins the managementdialog.cpp

- <a href="https://github.com/xaprier/qt-taxing/blob/main/cpp-files/managementdialog.cpp">cpp-files/managementdialog.cpp</a> is the Qt Dialog class which adds users to the <a href="https://github.com/xaprier/qt-taxing/blob/main/data/users.json">data/users.json</a> file and change the values of that users in GUI

- <a href="https://github.com/xaprier/qt-taxing/blob/main/cpp-files/questioning.cpp">cpp-files/questioning.cpp</a> is the Qt Dialog class which inquirying the tax info with user tax number.

- <a href="https://github.com/xaprier/qt-taxing/blob/main/cpp-files/taxsystem.cpp">cpp-files/taxsystem.cpp</a> is the Qt MainWindow class which creating dialog(login/questioning) with which button clicked system.

- <a href="https://github.com/xaprier/qt-taxing/blob/main/cpp-files/main.cpp">cpp-files/main.cpp</a> is the file of main() function. It creates a taxsystem object and shows it.

## <a href="https://github.com/xaprier/qt-taxing/tree/main/design-files">design-files</a> Directory

- <a href="https://github.com/xaprier/qt-taxing/tree/main/design-files/logindialog.ui">design-files/logindialog.ui</a>
- <a href="https://github.com/xaprier/qt-taxing/tree/main/design-files/managementdialog.ui">design-files/managementdialog.ui</a>
- <a href="https://github.com/xaprier/qt-taxing/tree/main/design-files/questioning.ui">design-files/questioning.ui</a>
- <a href="https://github.com/xaprier/qt-taxing/tree/main/design-files/taxsystem.ui">design-files/taxsystem.ui</a>

## <a href="https://github.com/xaprier/qt-taxing/tree/main/header-files">header-files</a> Directory

- <a href="https://github.com/xaprier/qt-taxing/tree/main/header-files/logindialog.h">header-files/logindialog.h</a>
- <a href="https://github.com/xaprier/qt-taxing/tree/main/header-files/managementdialog.h">header-files/managementdialog.h</a>
- <a href="https://github.com/xaprier/qt-taxing/tree/main/header-files/questioning.h">header-files/questioning.h</a>
- <a href="https://github.com/xaprier/qt-taxing/tree/main/header-files/taxsystem.h">header-files/taxsystem.h</a>
