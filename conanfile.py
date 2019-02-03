from conans import ConanFile, tools, CMake

class JsonshaderConan(ConanFile):
    name = "json-shader"
    version = "0.0.6"
    settings = "os", "compiler", "build_type", "arch", "cppstd"
    description = "<Description of Jsonshader here>"
    license = "MIT"
    author = "Jeff Wright <jeffw387@gmail.com>"
    exports = "CMakeLists.txt"
    exports_sources = "src/*"
    requires = (
      "fmt/5.3.0@bincrafters/stable",
      "Catch2/2.5.0@catchorg/stable",
      "jsonformoderncpp/3.5.0@vthiery/stable",
      "cxxopts/2.1.2@jeffw387/testing",
      "glm/0.9.9.1@g-truc/stable",
      "vulkan-sdk/1.X.X@jeffw387/testing"
    )
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.hpp", "./", "src")
        self.copy("json-shader.*", "bin", "bin", keep_path=False)

    def package_info(self):
        self.cpp_info.includedirs = ["src"]
        self.cpp_info.bindirs = ["bin"]

    def deploy(self):
        self.copy("json-shader*", dst="bin", src="bin")
