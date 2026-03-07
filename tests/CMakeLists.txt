find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(tst_qautostart tst_qautostart.cpp)
target_link_libraries(tst_qautostart PRIVATE QAutoStart Qt6::Test)
add_test(NAME tst_qautostart COMMAND tst_qautostart)
