#include <iostream>

#include "common/common/random_generator.h"
#include "exe/main_common.h"
#include "exe/platform_impl.h"
#include "tclap/CmdLine.h"

class LoadBalancerSimulatorImpl {
 public:
  LoadBalancerSimulatorImpl(Envoy::OptionsImpl options)
      : base_(options, real_time_system_, default_listener_hooks_,
              prod_component_factory_,
              std::make_unique<Envoy::Random::RandomGeneratorImpl>(),
              platform_impl_.threadFactory(), platform_impl_.fileSystem(),
              nullptr) {}

  std::unordered_map<std::string, uint32_t> simulate(
      const std::string& cluster_name, const int n) {
    auto endpoints = std::unordered_map<std::string, uint32_t>();
    auto cluster = base_.server()->clusterManager().get(cluster_name);
    for (int i = 0; i < n; i++) {
      auto host = cluster->loadBalancer().chooseHost(nullptr);
      auto address = host->address()->asString();
      auto it = endpoints.find(address);
      if (it != endpoints.end()) {
        it->second++;
      } else {
        endpoints.insert(std::make_pair(address, 1));
      }
    }
    return endpoints;
  }

 private:
  Envoy::PlatformImpl platform_impl_;
  Envoy::Event::RealTimeSystem real_time_system_;
  Envoy::DefaultListenerHooks default_listener_hooks_;
  Envoy::ProdComponentFactory prod_component_factory_;
  Envoy::MainCommonBase base_;
};

std::vector<std::string> toArgsVector(int argc, const char* const* argv) {
  std::vector<std::string> args;
  args.reserve(argc);

  for (int i = 0; i < argc; ++i) {
    args.emplace_back(argv[i]);
  }
  return args;
}

int main(int argc, char* argv[]) {
  TCLAP::CmdLine cmd("envoy-lb-simulator", ' ', Envoy::VersionInfo::version());
  TCLAP::ValueArg<std::string> config_path("c", "config-path",
                                           "Path to configuration file", false,
                                           "", "string", cmd);
  TCLAP::ValueArg<std::string> cluster(
      "", "cluster",
      "Target of cluster to simulate load balancing for endpoints", false, "",
      "string", cmd);
  TCLAP::ValueArg<uint32_t> iter(
      "i", "iter", "Number of iterations to assign which endpoints", false, 100,
      "uint32_t", cmd);

  try {
    auto args = toArgsVector(argc, argv);
    cmd.parse(args);
  } catch (const TCLAP::ArgException& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  try {
    Envoy::OptionsImpl options_("cluster_name", "node_name", "zone_name",
                                spdlog::level::err);
    options_.setConfigPath(config_path.getValue());
    auto simulator = std::make_unique<LoadBalancerSimulatorImpl>(options_);
    auto endpoints = simulator->simulate(cluster.getValue(), iter.getValue());
    for (auto& e : endpoints) {
      std::cout << e.first << ": " << e.second << std::endl;
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
