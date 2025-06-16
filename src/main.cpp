// Copyright (c) Tyler Veness

#include <chrono>
#include <thread>

#include <networktables/DoubleTopic.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

int main() {
  using namespace std::chrono_literals;

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto table = inst.GetTable("datatable");
  auto x_sub = table->GetDoubleTopic("x").Subscribe(0.0);
  auto y_sub = table->GetDoubleTopic("y").Subscribe(0.0);

  inst.StartClient4("Example client");
  inst.SetServerTeam(1234);

  // Recommended if running on DS computer; this gets the robot IP from the DS
  inst.StartDSClient();

  while (true) {
    std::this_thread::sleep_for(1s);

    [[maybe_unused]]
    double x = x_sub.Get();
    [[maybe_unused]]
    double y = y_sub.Get();
  }
}
