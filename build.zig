const std = @import("std");
const rl_build = @import("vendor/raylib/src/build.zig");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const raylib = rl_build.addRaylib(b, target, optimize, .{});

    const toml_c = b.addStaticLibrary(.{
        .name = "tomlc",
        .target = target,
        .optimize = optimize,
    });
    toml_c.linkLibC();
    toml_c.addCSourceFiles(.{
        .files = &.{"vendor/toml-c/toml.c"},
    });
    toml_c.addIncludePath(b.path("vendor/toml-c/"));

    const exe = b.addExecutable(.{
        .name = "c_chess",
        .target = target,
        .optimize = optimize,
    });
    exe.linkLibC();
    exe.linkLibrary(raylib);
    exe.linkLibrary(toml_c);
    exe.addCSourceFiles(.{
        .files = &.{
            "src/main.c",
            "src/conf.c",
            "src/win.c",
            "src/screens/game_screen.c",
            "src/screens/start_screen.c",
            "src/screens/button.c",
        },
    });
    exe.addIncludePath(b.path("include/"));
    exe.addIncludePath(b.path("vendor/raylib/src"));
    exe.addIncludePath(b.path("vendor/toml-c/"));

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
