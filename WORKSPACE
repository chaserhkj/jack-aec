load("//:libjack.bzl", "libjack")

libjack(
        name = "libjack",
        )

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
        name = "absl",
        remote = "https://github.com/abseil/abseil-cpp",
        branch = "master"
        )

load("//:libwebrtc_audio_processing.bzl", "libwebrtc_audio_processing")

libwebrtc_audio_processing(
        name = "libwebrtc_audio_processing"
        )

load("//:libspeexdsp.bzl", "libspeexdsp")
libspeexdsp(
        name = "libspeexdsp"
        )