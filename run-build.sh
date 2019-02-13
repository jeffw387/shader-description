mkdir -p build
cd build
conan install .. --build=missing --profile=$CONANPROFILE > build/install.log
conan build .. > build/build.log