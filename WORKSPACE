workspace(name="envoy_lb_simulator")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

local_repository(
    name = "envoy",
    path = "envoy",
)

load("@envoy//bazel:api_binding.bzl", "envoy_api_binding")
envoy_api_binding()

load("@envoy//bazel:api_repositories.bzl", "envoy_api_dependencies")
envoy_api_dependencies()

load("@envoy//bazel:repositories.bzl", "envoy_dependencies")
envoy_dependencies()

load("@envoy//bazel:repositories_extra.bzl", "envoy_dependencies_extra")
envoy_dependencies_extra()

load("@envoy//bazel:dependency_imports.bzl", "envoy_dependency_imports")
envoy_dependency_imports()
