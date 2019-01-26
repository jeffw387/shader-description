from conans import ConanFile, tools, CMake

class JsonshaderConan(ConanFile):
    name = "json-shader"
    version = "0.0.1"
    settings = "os", "compiler", "build_type", "arch", "cppstd"
    description = "<Description of Jsonshader here>"
    license = "MIT"
    author = "Jeff Wright jeffw387@gmail.com"
    requires = (
      "fmt/5.3.0@bincrafters/stable",
      "Catch2/2.5.0@catchorg/stable",
      "jsonformoderncpp/3.5.0@vthiery/stable",
      "cxxopts/2.1.2@jeffw387/testing"
    )
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()