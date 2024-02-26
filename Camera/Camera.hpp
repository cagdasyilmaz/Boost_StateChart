#ifndef CAMERA_CAMERA_HPP
#define CAMERA_CAMERA_HPP

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>

#include <boost/config.hpp>

#ifdef BOOST_INTEL
#pragma warning( disable: 304 ) // access control not specified
#endif

namespace sc = boost::statechart;

struct EvShutterHalf : sc::event<EvShutterHalf> {};
struct EvShutterHalfAgain : sc::event<EvShutterHalfAgain> {};
struct EvShutterFull : sc::event<EvShutterFull> {};
struct EvShutterRelease : sc::event<EvShutterRelease> {};
struct EvConfig : sc::event<EvConfig> {};

struct NotShooting;
struct Camera : sc::state_machine<Camera, NotShooting>
{
    bool isMemoryAvailable() const {return true;}
    bool isBatteryLow() const {return false;}
};

struct Idle;
struct NotShooting : sc::simple_state<NotShooting, Camera, Idle>
{
    typedef sc::custom_reaction<EvShutterHalf> reactions;

    NotShooting();
    ~NotShooting(); //override;

    sc::result react(const EvShutterHalf&);
};

struct Idle: sc::simple_state<Idle, NotShooting>
{
    typedef sc::custom_reaction<EvConfig> reactions;

    Idle();
    ~Idle();

    sc::result react(const EvConfig&);
};

#endif //CAMERA_CAMERA_HPP
