# QAutoStart

[![Unit Tests](https://github.com/MrEricSir/QAutoStart/workflows/CI/badge.svg)](https://github.com/MrEricSir/QAutoStart/actions)

Enables or disables a Qt application to start at login on Windows, Mac, and Linux. A simple [example app](https://github.com/MrEricSir/QAutoStart/tree/main/example) is included.

For full details see [the documentation.](https://mrericsir.github.io/QAutoStart/qautostart.html)

## Quick Start

When creating your `QApplication`, make sure to set a name and organization; this will be used to 
differentiate your app from other apps that autostart on the system.

```cpp
QApplication app(argc, argv);
app.setApplicationName("QAutoStartExample");
app.setOrganizationDomain("com.EricGregory.QAutoStartExample");
```

Enable autostart for your application with:
```cpp
QAutoStart::Get().setEnabled(true);
```

Disable it with:
```cpp
QAutoStart::Get().setEnabled(false);
```

Check if it's enabled with:
```cpp
bool isAutoStartEnabled = QAutoStart::Get().isEnabled();
```

## How To Include

The most straightforward way to include QAutoStart is with `git submodule`.

In the root directory of your existing project's git repository:

```bash
git submodule add git@github.com:MrEricSir/QAutoStart.git external/QAutoStart
git add .gitmodules
git commit -m "Add QAutoStart submodule"
```

This will place QAutoStart into `external/QAutoStart`.

Add the submodule to your `CMakeLists.txt`:

add_subdirectory(external/QAutoStart)
target_link_libraries(YourApp PRIVATE QAutoStart::QAutoStart)
