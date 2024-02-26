#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/termination.hpp>

#include <boost/mpl/list.hpp>

#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>

#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#  pragma warning( disable: 444 ) // destructor for base is not virtual
#  pragma warning( disable: 981 ) // operands are evaluated in unspecified order
#endif

namespace sc = boost::statechart;
namespace mpl = boost::mpl;
using namespace std::chrono_literals;

struct EvPrevious : sc::event<EvPrevious> {};
struct EvNext : sc::event<EvNext> {};
struct EvReset : sc::event<EvReset> {};
struct EvGetElapsedTime : sc::event<EvGetElapsedTime>
{
public:
    EvGetElapsedTime(double& time) : time_{time} {}

    void Assign(double time) const
    {
        time_ = time;
    }

private:
    double& time_;
};

struct StateBlock;
struct StateMachine : sc::state_machine<StateMachine, StateBlock> {};

struct PreviousState;
struct StateBlock : sc::simple_state<StateBlock, StateMachine, PreviousState>
{
public:
    typedef sc::transition<EvReset, StateBlock> reactions;

    StateBlock() : elapsedTime_( 0.0 ) { std::cout << "Entering StateBlock!\n"; }

    ~StateBlock() override { std::cout << "Leaving StateBlock!\n"; }

    double & ElapsedTime()
    {
        return elapsedTime_;
    }

    double ElapsedTime() const
    {
        return elapsedTime_;
    }

private:
    double elapsedTime_;
};

struct NextState : sc::simple_state< NextState, StateBlock>
{
public:
    typedef mpl::list<
            sc::custom_reaction< EvGetElapsedTime >,
            sc::transition< EvPrevious, PreviousState >,
            sc::termination< EvNext >
    > reactions;

    NextState()
        : begin{std::chrono::steady_clock::now()}
    {

        std::cout << "\tEntering NextState!\n";
    }

    ~NextState()
    {
        context<StateBlock>().ElapsedTime() = ElapsedTime();
        std::cout << "\tLeaving NextState!\n";
    }

    sc::result react( const EvGetElapsedTime & evt )
    {
        evt.Assign(ElapsedTime());
        return discard_event();
    }

private:
    double ElapsedTime() const
    {
        /*return context< StateBlock >().ElapsedTime() +
               std::difftime(std::time( 0 ), startTime_);*/

        std::chrono::duration<double> last = std::chrono::steady_clock::now() - begin;

        return context< StateBlock >().ElapsedTime() + last.count();
    }

    std::chrono::time_point<std::chrono::steady_clock> begin;
};

struct PreviousState : sc::simple_state<PreviousState, StateBlock>
{
    typedef mpl::list<
            sc::custom_reaction< EvGetElapsedTime >,
            sc::transition< EvNext, NextState >
    > reactions;

    sc::result react(const EvGetElapsedTime& evt)
    {
        evt.Assign(context<StateBlock>().ElapsedTime());
        return discard_event();
    }

    PreviousState() { std::cout << "\tEntering PreviousState!\n"; }

    virtual ~PreviousState() { std::cout << "\tLeaving PreviousState!\n"; }
};

namespace
{
    char GetKey()
    {
        char key;
        std::cin >> key;
        return key;
    }
}

int main() {

    std::cout << "Boost.Statechart StateMachine example\n\n";
    std::cout << "n<CR>: Jump the next state\n";
    std::cout << "p<CR>: Jump to previous state\n";
    std::cout << "d<CR>: Displays the elapsed time in the current state (seconds)\n";
    std::cout << "e<CR>: Exits the program\n\n";
    std::cout << "We may chain commands, e.g. rs<CR> resets and then jump the initial state in StateBlock\n\n";

    StateMachine stateMachine;
    stateMachine.initiate();

    char key = GetKey();

    while ( key != 'e' )
    {
        switch( key )
        {
            case 'r':
            {
                stateMachine.process_event( EvReset() );
            }
                break;

            case 'n':
            {
                stateMachine.process_event( EvNext() );
            }
                break;

            case 'p':
            {
                stateMachine.process_event( EvPrevious() );
            }
                break;

            case 'd':
            {
                double elapsedTime = 0.0;
                stateMachine.process_event( EvGetElapsedTime( elapsedTime ) );
                std::cout << "Elapsed time: " << elapsedTime << "\n";
            }
                break;

            default:
            {
                std::cout << "Invalid key!\n";
            }
                break;
        }

        key = GetKey();
    }


    return 0;
}