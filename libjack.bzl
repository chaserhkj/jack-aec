def _libjack(repo_ctx):
    prefix = repo_ctx.os.environ.get("BAZEL_LIBJACK_PREFIX", "/usr/")
    prefix = repo_ctx.path(prefix)

    include_dir = prefix.get_child("include").get_child("jack")
    repo_ctx.symlink(include_dir, include_dir.basename)

    library_directive = ""
    dynamic = prefix.get_child("lib").get_child("libjack.so")
    static = prefix.get_child("lib").get_child("libjack.a")

    if dynamic.exists:
        repo_ctx.symlink(dynamic, dynamic.basename)
        library_directive += """
        shared_library = "libjack.so","""

    if static.exists:
        repo_ctx.symlink(static, static.basename)
        library_directive += """
        static_library = "libjack.a","""

    repo_ctx.file("BUILD", """
cc_import(
        name = "libjack",
        hdrs = glob(["jack/**"]),""" + library_directive + """
        visibility = ["//visibility:public"]
        )
                  """)

libjack = repository_rule(
        implementation = _libjack,
        local = True,
        environ = ["BAZEL_LIBJACK_PREFIX"],
        )
