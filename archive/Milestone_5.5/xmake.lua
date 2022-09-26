add_rules("mode.debug", "mode.release")  -- See https://xmake.io/#/manual/custom_rule?id=built-in-rules

add_cxflags()
add_ldflags()

set_languages("c++17")

-- set_optimize()
-- add_defines()

add_requires("conan::glfw/3.3.8", { alias = 'glfw'})  -- OS-independent window, input etc library
add_requires("conan::glad/0.1.36", { alias = 'glad'})  -- modern alternative to GLEW
-- add_requires("conan::glew/2.2.0", { alias = 'glew'})  -- hook into system OpenGL
add_requires("conan::glm/cci.20220420", { alias = 'glm'})  -- maths
add_requires("conan::stb/cci.20210910", { alias = 'stb'})  -- stb_image.h for image loading
add_requires("conan::imgui/cci.20220621+1.88.docking", { alias = 'imgui', configs = { glfw_opengl3 = true } })  -- UI

target("myexe")
  set_kind("binary")
  add_headerfiles("./**.h")
  add_files("./**.cpp")
  add_packages("glfw", "glad", "glm", "stb", "imgui")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

