from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class CMakeConan(ConanFile):

    name = "terminus_warpcore"
    version = "0.0.1"

    license = "Terminus Proprietary"
    author = "Marvin Smith <marvin_smith1@me.com>"
    url = "https://bitbucket.org/msmith81886/terminus-cmake/src/main/"
    description = "High-Performance Image-Processing API"
    topics = ("terminus", "cmake", "build")

    options = { "ENABLE_TESTS": [True, False] }

    default_options = { "ENABLE_TESTS": True }

    settings = "os", "compiler", "build_type", "arch"

    def build_requirements(self):
        self.test_requires("gtest/1.13.0")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["VERSION_FROM_CONANFILE"] = self.version
        tc.variables["NAME_FROM_CONANFILE"] = self.name
        tc.variables["DESC_FROM_CONANFILE"] = self.description
        tc.variables["URL_FROM_CONANFILE"] = self.url

        for option in self.default_options:
            tc.variables[option] = self.default_options[option]
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()


    def package_info(self):
        self.cpp_info.builddirs = ["cmake"]

