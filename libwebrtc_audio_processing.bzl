def _libwebrtc_audio_processing(repo_ctx):
    prefix = repo_ctx.os.environ.get("BAZEL_LIBWEBRTC_AUDIO_PROCESSING_PREFIX", "/usr/")
    prefix = repo_ctx.path(prefix)

    include_dir = prefix.get_child("include").get_child("webrtc_audio_processing")
    repo_ctx.symlink(include_dir, include_dir.basename)

    library_directive = ""
    dynamic = prefix.get_child("lib").get_child("libwebrtc_audio_processing.so")
    static = prefix.get_child("lib").get_child("libwebrtc_audio_processing.a")

    if dynamic.exists:
        repo_ctx.symlink(dynamic, dynamic.basename)
        library_directive += """
        shared_library = "libwebrtc_audio_processing.so","""

    if static.exists:
        repo_ctx.symlink(static, static.basename)
        library_directive += """
        static_library = "libwebrtc_audio_processing.a","""

    repo_ctx.file("BUILD", """
cc_import(
        name = "libwebrtc_audio_processing",
        hdrs = glob(["webrtc_audio_processing/*.h"]),""" + library_directive + """
        visibility = ["//visibility:public"]
        )
                  """)

libwebrtc_audio_processing = repository_rule(
        implementation = _libwebrtc_audio_processing,
        local = True,
        environ = ["BAZEL_LIBWEBRTC_AUDIO_PROCESSING_PREFIX"],
        )
