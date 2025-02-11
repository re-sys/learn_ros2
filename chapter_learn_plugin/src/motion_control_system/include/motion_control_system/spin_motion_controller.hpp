#ifndef SPIN_MOTION_CONTROLER_HPP
#define SPIN_MOTION_CONTROLER_HPP
#include "motion_control_interface.hpp"

namespace motion_control_system{

    class SpinMotionController:public MotionController
    {
    private:
        /* data */
    public:
        virtual void start() override;
        virtual void stop() override;
    };
    
    
}

#endif
