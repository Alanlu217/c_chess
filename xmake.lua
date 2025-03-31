package("rl", function()
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "vendor/raylib"))
    on_install(function(package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
    end)
end)

add_requires("rl")

target("toml-c", function()
    set_kind("static")
    add_files("vendor/toml-c/toml.c")
    add_includedirs("vendor/toml-c/", { public = true })
end)

target("chess", function()
    set_kind("binary")
    add_files("src/*.c", "src/screens/*.c")
    add_includedirs("include/")

    add_packages("rl")
    add_deps("toml-c")
end)
