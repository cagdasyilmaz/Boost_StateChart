#ifndef CAMERA_SHOOTING_HPP
#define CAMERA_SHOOTING_HPP

#include "Camera.hpp"
#include "Precompiled.hpp"


#include <boost/statechart/event.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/deferral.hpp>

#include <boost/mpl/list.hpp>
#include <boost/config.hpp>

#include <thread>
#include <chrono>

#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#endif

namespace sc = boost::statechart;
namespace mpl = boost::mpl;
using namespace std::chrono_literals;

//////////////////////////////////////////////////////////////////////////////
struct EvInFocus : sc::event<EvInFocus> {};

struct Focusing;
struct Shooting : sc::simple_state<Shooting, Camera, Focusing> {
    typedef sc::transition<EvShutterRelease, NotShooting> reactions;

    Shooting();
    ~Shooting();

    void DisplayFocused(const EvInFocus&) {
        std::cout << "\t\t\tFocused in the Shooting state block!\n";
    }
};

struct Focusing : sc::state<Focusing, Shooting>
{
    typedef mpl::list<
            sc::custom_reaction<EvInFocus>,
            sc::deferral<EvShutterFull>
    > reactions;

    Focusing(my_context ctx);
    ~Focusing();

    sc::result react(const EvInFocus&);
};

#endif //CAMERA_SHOOTING_HPP
