cc_binary(
        name = "jack-aec",
        deps = [
                "@libjack//:libjack",
                #"@libwebrtc_audio_processing//:libwebrtc_audio_processing",
                "@libspeexdsp//:libspeexdsp",
                "@absl//absl/flags:flag",
                "@absl//absl/flags:parse",
                "@absl//absl/flags:usage",
                "@absl//absl/strings:str_format"
                ],
        srcs = [
                "main.cc",
                "flags.cc",
                "flags.h",
                "ec_ctx.h",
                "ec_ctx.cc",
                "jack_mgr.h",
                "jack_mgr.cc"
                ],
        visibility = ["//visibility:public"]
        )
