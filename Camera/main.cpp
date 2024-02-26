#include "Precompiled.hpp"
#include "Camera.hpp"
#include <iostream>


char GetKey()
{
    char key;
    std::cout << "Enter a option: ";
    std::cin >> key;
    return key;
}

int main()
{
    std::cout << "Boost.Statechart Camera example\n\n";

    std::cout << "h<CR>: Press shutter half-way\n";
    std::cout << "f<CR>: Press shutter fully\n";
    std::cout << "r<CR>: Release shutter\n";
    std::cout << "c<CR>: Enter/exit configuration\n";
    std::cout << "s<CR>: Enter shutting again\n";
    std::cout << "e<CR>: Exits the program\n\n";
    std::cout << "You may chain commands, e.g. hfr<CR> first presses the shutter half-way,\n";
    std::cout << "fully and then releases it.\n\n";


    Camera myCamera;
    myCamera.initiate();

    char key = GetKey();
    while ( key != 'e' )
    {
        switch( key )
        {
            case 'h':
            {
                myCamera.process_event( EvShutterHalf() );
            }
                break;

            case 'f':
            {
                myCamera.process_event( EvShutterFull() );
            }
                break;

            case 'r':
            {
                myCamera.process_event( EvShutterRelease() );
            }
                break;

            case 'c':
            {
                myCamera.process_event( EvConfig() );
            }
                break;

            case 's':
            {
                myCamera.process_event( EvShutterHalfAgain() );
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