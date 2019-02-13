mkdir -p build
cd build
conan install .. --build=missing --profile=$CONANPROFILE > install.log
conan build .. > build.log