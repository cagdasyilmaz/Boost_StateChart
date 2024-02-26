#include "Precompiled.hpp"
#include "Shooting.hpp"
#include <iostream>

#include <boost/config.hpp>

#ifdef BOOST_INTEL
#  pragma warning( disable: 383 ) // reference to temporary used
#endif

//////////////////////////////////////////////////////////////////////////////
Shooting::Shooting()
{
    std::cout << "\tEntering Shooting state block\n";
}

Shooting::~Shooting()
{
    std::cout << "\tExiting Shooting state block\n";
}

//////////////////////////////////////////////////////////////////////////////
struct Storing : sc::simple_state< Storing, Shooting >
{
    typedef sc::custom_reaction<EvShutterHalfAgain> reactions;

    Storing()
    {
        std::cout << "\t\tEntering Storing state!\n";
        std::cout << "\t\t\tPicture taken!\n"
                  << "\t\t\tand stored!\n";
    }

    ~Storing()
    {
        std::cout << "\t\tExisting Storing state!\n";
    }

    sc::result react(const EvShutterHalfAgain&);
};

sc::result Storing::react(const EvShutterHalfAgain&)
{
    std::cout << "\t\t\tReturning back to the Shooting state block!\n";
    return transit<Focusing>();
}


//////////////////////////////////////////////////////////////////////////////
struct Focused : sc::simple_state< Focused, Shooting >
{
    typedef sc::custom_reaction< EvShutterFull > reactions;

    Focused() { std::cout << "\t\tEntering Focused state!\n"; }
    ~Focused() { std::cout << "\t\tExisting Focused state!\n"; }

    sc::result react( const EvShutterFull & );
};

sc::result Focused::react( const EvShutterFull & )
{
    if ( context< Camera >().isMemoryAvailable() )
    {
        return transit<Storing>();
    }
    else
    {
        std::cout << "Cache memory full. Please wait...\n";
        //std::cout << "\t\tMemory full. Returning back to NotShooting State ...\n";
        //return transit<NotShooting>();
        return discard_event();
    }
}

//////////////////////////////////////////////////////////////////////////////
Focusing::Focusing(my_context ctx) : my_base(ctx)
{
    std::cout << "\t\tEntering Focusing state!\n";
    post_event(boost::intrusive_ptr<EvInFocus>(new EvInFocus()));
    std::this_thread::sleep_for(1s);
}

Focusing::~Focusing()
{
    std::cout << "\t\tExisting Focusing state!\n";
}

sc::result Focusing::react(const EvInFocus & evt)
{
    return transit<Focused>(&Shooting::DisplayFocused, evt);
}