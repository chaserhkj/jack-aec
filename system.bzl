def _libjack(repo_ctx):
    prefix = repo_ctx.os.environ.get("BAZEL_SYSTEM_PREFIX", "/usr/")
    prefix = repo_ctx.path(prefix)
    repo_ctx.symlink(prefix.get_child("include").get_child("jack"), "jack")
    repo_ctx.symlink(prefix.get_child("lib").get_child("libjack.so"), "libjack.so")
    repo_ctx.file("BUILD", """
cc_import(
        name = "libjack",
        hdrs = glob(["jack/*.h"]),
        shared_library = "libjack.so",
        visibility = ["//visibility:public"]
        )
                  """)

libjack = repository_rule(
        implementation = _libjack,
        local = True,
        environ = ["BAZEL_SYSTEM_PREFIX"],
        )
