// The following includes are only made here but not in
// Camera.hpp
// The Shooting and Configuring states can themselves apply the
// same pattern to hide their inner implementation, which
// ensures that the two teams working on the Camera state
// machine will never need to disturb each other.

#include "Precompiled.hpp"
#include "Camera.hpp"
#include "Configuring.hpp"
#include "Shooting.hpp"

NotShooting::NotShooting()
{
    std::cout << "\tEntering NotShooting state block!\n";
}

NotShooting::~NotShooting()
{
    std::cout << "\tExiting NotShooting state block!\n";
}

sc::result NotShooting::react(const EvShutterHalf&)
{
    if( context<Camera>().isBatteryLow() ) {
        std::cout << "\t\t\tBattery is low! Camera do not enter shutter mode!\n";
        return forward_event();
    } else {
        return transit<Shooting>();
    }
}

Idle::Idle()
{
    std::cout << "\t\tEntering Idle state!\n";
}

Idle::~Idle()
{
    std::cout << "\t\tExiting Idle state!\n";
}

sc::result Idle::react(const EvConfig &)
{
    return transit<Configuring>();
}

