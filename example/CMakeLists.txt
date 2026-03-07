find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(QAutoStartExample main.cpp)
target_link_libraries(QAutoStartExample PRIVATE QAutoStart Qt6::Widgets)
