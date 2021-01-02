# envoy-lb-simulator

This is a command-line to simulate the load balancer for [envoy](https://github.com/envoyproxy/envoy) proxy.

## Installation

```sh
git clone --recursive https://github.com/ynqa/envoy-lb-simulator.git
cd envoy-lb-simulator/
bazel build //envoy-lb-simulator:envoy-lb-simulator
```

## Example

```sh
envoy-lb-simulator --config-path examples/cluster.yaml --cluster test_cluster
```

## References
- [Load balancing simulation and visualization](https://github.com/envoyproxy/envoy/issues/7974).
