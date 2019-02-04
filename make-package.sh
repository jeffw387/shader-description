# pass package version as argument 1
conan create . jeffw387/testing && conan alias json-shader/latest@jeffw387/testing json-shader/$1@jeffw387/testing