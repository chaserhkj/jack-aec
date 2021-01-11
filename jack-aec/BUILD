cc_binary(
        name = "jack-aec",
        deps = [
                "@libjack//:libjack",
                "@libwebrtc_audio_processing//:libwebrtc_audio_processing",
                "@absl//absl/flags:flag",
                "@absl//absl/flags:parse",
                "@absl//absl/flags:usage",
                ],
        srcs = ["main.cc"],
        visibility = ["//visibility:public"]
        )
