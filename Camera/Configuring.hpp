#ifndef CAMERA_CONFIGURING_HPP
#define CAMERA_CONFIGURING_HPP

#include "Camera.hpp"

#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>

#ifdef BOOST_INTEL
#pragma warning( disable: 304 ) // access control not specified
#endif

namespace sc = boost::statechart;

struct Configuring : sc::simple_state<Configuring, NotShooting>
{
    typedef sc::transition<EvConfig, Idle> reactions;

    Configuring();
    ~Configuring();
};

#endif //CAMERA_CONFIGURING_HPP
