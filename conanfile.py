from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class CMakeConan(ConanFile):

    name = "terminus_image"
    version = "0.0.1"

    license = "Terminus Proprietary"
    author = "Marvin Smith <marvin_smith1@me.com>"
    url = "https://bitbucket.org/msmith81886/terminus-cmake/src/main/"
    description = "High-Performance Image-Processing API"
    topics = ("terminus", "cmake", "build")

    options = { "shared": [True, False],
                "with_tests": [True, False],
                "with_docs": [True, False],
                "with_coverage": [True, False]
    }

    default_options = { "shared": True,
                        "with_tests": True,
                        "with_docs": True,
                        "with_coverage": False,
                        "boost/*:shared": True }

    settings = "os", "compiler", "build_type", "arch"

    def build_requirements(self):
        self.build_requires("gtest/1.13.0")
        self.build_requires("terminus_cmake/1.0.0")

    def requirements(self):
        self.requires("boost/1.82.0")
        #self.requires("gdal/3.4.3")
        self.requires("terminus_log/0.0.1")
        self.requires("terminus_math/0.0.1")
        self.requires("terminus_outcome/0.0.1")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CONAN_PKG_VERSION"]     = self.version
        tc.variables["CONAN_PKG_NAME"]        = self.name
        tc.variables["CONAN_PKG_DESCRIPTION"] = self.description
        tc.variables["CONAN_PKG_URL"]         = self.url

        tc.variables["TERMINUS_IMAGE_ENABLE_TESTS"]    = self.options.with_tests
        tc.variables["TERMINUS_IMAGE_ENABLE_DOCS"]     = self.options.with_docs
        tc.variables["TERMINUS_IMAGE_ENABLE_COVERAGE"] = self.options.with_coverage
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

