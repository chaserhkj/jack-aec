def _libspeexdsp(repo_ctx):
    prefix = repo_ctx.os.environ.get("BAZEL_LIBSEEXDSP_PREFIX", "/usr/")
    prefix = repo_ctx.path(prefix)

    include_dir = prefix.get_child("include").get_child("speex")
    repo_ctx.symlink(include_dir, include_dir.basename)

    library_directive = ""
    dynamic = prefix.get_child("lib").get_child("libspeexdsp.so")
    static = prefix.get_child("lib").get_child("libspeexdsp.a")

    if dynamic.exists:
        repo_ctx.symlink(dynamic, dynamic.basename)
        library_directive += """
        shared_library = "libspeexdsp.so","""

    if static.exists:
        repo_ctx.symlink(static, static.basename)
        library_directive += """
        static_library = "libspeexdsp.a","""

    repo_ctx.file("BUILD", """
cc_import(
        name = "libspeexdsp",
        hdrs = glob(["speex/**"]),""" + library_directive + """
        visibility = ["//visibility:public"]
        )
                  """)

libspeexdsp = repository_rule(
        implementation = _libspeexdsp,
        local = True,
        environ = ["BAZEL_LIBSPEEXDSP_PREFIX"],
        )
