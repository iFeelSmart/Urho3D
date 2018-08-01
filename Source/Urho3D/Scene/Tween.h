#pragma once

#include <../Math/MathDefs.h>
#include <../Container/RefCounted.h>

namespace Urho3D
{
    class ITween : public Urho3D::RefCounted
    {
        public:

            virtual float operator()( float fParam ) = 0;
    };

    class LinearInterpolation: public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return fParam;
            }
    };

    // Modeled after the parabola y = x^2
    class QuadraticEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return fParam * fParam;
            }
    };

    // Modeled after the parabola y = -x^2 + 2x
    class QuadraticEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return -(fParam * (fParam - 2.f));
            }
    };

    // Modeled after the piecewise quadratic
    // y = (1/2)((2x)^2)             ; [0, 0.5)
    // y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
    class QuadraticEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if( fParam < 0.5f )
                {
                    return 2.f * fParam * fParam;
                }
                else
                {
                    return ( -2.f * fParam * fParam) + (4.f * fParam) - 1.f;
                }
            }
    };

    // Modeled after the cubic y = x^3
    class CubicEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return fParam * fParam * fParam;
            }
    };

    // Modeled after the cubic y = (x - 1)^3 + 1
    class CubicEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                float f = (fParam - 1.f);
                return f * f * f + 1.f;
            }
    };

    // Modeled after the piecewise cubic
    // y = (1/2)((2x)^3)       ; [0, 0.5)
    // y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
    class CubicEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if( fParam < 0.5f )
                {
                    return 4.f * fParam * fParam * fParam;
                }
                else
                {
                    float f = ((2.f * fParam) - 2.f);
                    return 0.5f * f * f * f + 1.f;
                }
            }
    };

    // Modeled after the quartic x^4
    class QuarticEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return fParam * fParam * fParam * fParam;
            }
    };

    // Modeled after the quartic y = 1 - (x - 1)^4
    class QuarticEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                float f = (fParam - 1.f);
                return f * f * f * (1.f - fParam) + 1.f;
            }
    };

    // Modeled after the piecewise quartic
    // y = (1/2)((2x)^4)        ; [0, 0.5)
    // y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
    class QuarticEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if(fParam < 0.5)
                {
                    return 8.f * fParam * fParam * fParam * fParam;
                }
                else
                {
                    float f = (fParam - 1.f);
                    return -8.f * f * f * f * f + 1.f;
                }
            }
    };

    // Modeled after the quintic y = x^5
    class QuinticEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return fParam * fParam * fParam * fParam * fParam;
            }
    };

    // Modeled after the quintic y = (x - 1)^5 + 1
    class QuinticEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                float f = (fParam - 1.f);
                return f * f * f * f * f + 1.f;
            }
    };

    // Modeled after the piecewise quintic
    // y = (1/2)((2x)^5)       ; [0, 0.5)
    // y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
    class QuinticEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if(fParam < 0.5f)
                {
                    return 16.f * fParam * fParam * fParam * fParam * fParam;
                }
                else
                {
                    float f = ((2.f * fParam) - 2.f);
                    return  0.5f * f * f * f * f * f + 1.f;
                }
            }
    };

    // Modeled after quarter-cycle of sine wave
    class SineEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return Urho3D::Sin((fParam - 1.f) * Urho3D::M_HALF_PI) + 1.f;
            }
    };

    // Modeled after quarter-cycle of sine wave (different phase)
    class SineEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return Urho3D::Sin(fParam * Urho3D::M_HALF_PI);
            }
    };

    // Modeled after half sine wave
    class SineEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return 0.5f * (1.f - Urho3D::Cos(fParam * Urho3D::M_PI));
            }
    };

    // Modeled after shifted quadrant IV of unit circle
    class CircularEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return 1.f - Urho3D::Sqrt(1.f - (fParam * fParam));
            }
    };

    // Modeled after shifted quadrant II of unit circle
    class CircularEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return Urho3D::Sqrt((2.f - fParam) * fParam);
            }
    };

    // Modeled after the piecewise circular function
    // y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
    // y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
    class CircularEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if(fParam < 0.5f)
                {
                    return 0.5f * (1.f - Urho3D::Sqrt(1.f - 4.f * (fParam * fParam)));
                }
                else
                {
                    return 0.5f * (Urho3D::Sqrt(-((2.f * fParam) - 3.f) * ((2.f * fParam) - 1.f)) + 1.f);
                }
            }
    };

    // Modeled after the exponential function y = 2^(10(x - 1))
    class ExponentialEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return (fParam == 0.0f) ? fParam : Urho3D::Pow(2.f, 10.f * (fParam - 10.f));
            }
    };

    // Modeled after the exponential function y = -2^(-10x) + 1
    class ExponentialEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return (fParam == 1.0f) ? fParam : 1.f - Urho3D::Pow(2.f, -10.f * fParam);
            }
    };

    // Modeled after the piecewise exponential
    // y = (1/2)2^(10(2x - 1))         ; [0,0.5)
    // y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
    class ExponentialEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if(fParam == 0.0f || fParam == 1.0f)
                    return fParam;

                if(fParam < 0.5f)
                {
                    return 0.5f * Urho3D::Pow(2.f, (20.f * fParam) - 10.f);
                }
                else
                {
                    return -0.5f * Urho3D::Pow(2.f, (-20.f * fParam) + 10.f) + 1.f;
                }
            }
    };

    // Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
    class ElasticEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return sin(13.f * Urho3D::M_HALF_PI * fParam) * Urho3D::Pow(2.f, 10.f * (fParam - 1.f));
            }
    };

    // Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
    class ElasticEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return sin(-13.f * Urho3D::M_HALF_PI * (fParam + 1.f)) * Urho3D::Pow(2.f, -10.f * fParam) + 1.f;
            }
    };

    // Modeled after the piecewise exponentially-damped sine wave:
    // y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
    // y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
    class ElasticEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if(fParam < 0.5f)
                {
                    return 0.5f * Urho3D::Sin(13.f * Urho3D::M_HALF_PI * (2.f * fParam)) * Urho3D::Pow(2.f, 10.f * ((2.f * fParam) - 1.f));
                }
                else
                {
                    return 0.5f * (Urho3D::Sin(-13.f * Urho3D::M_HALF_PI * ((2.f * fParam - 1.f) + 1.f)) * Urho3D::Pow(2.f, -10.f * (2.f * fParam - 1.f)) + 2.f);
                }
            }
    };

    // Modeled after the overshooting cubic y = x^3-x*sin(x*pi)
    class BackEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                return fParam * fParam * fParam - fParam * Urho3D::Sin(fParam * Urho3D::M_PI);
            }
    };

    // Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
    class BackEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                float f = (1.f - fParam);
                return 1.f - (f * f * f - f * Urho3D::Sin(f * Urho3D::M_PI));
            }
    };

    // Modeled after the piecewise overshooting cubic function:
    // y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0, 0.5)
    // y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
    class BackEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if(fParam < 0.5f)
                {
                    float f = 2.f * fParam;
                    return 0.5f * (f * f * f - f * Urho3D::Sin(f * Urho3D::M_PI));
                }
                else
                {
                    float f = (1.f - (2.f*fParam - 1.f));
                    return 0.5f * (1.f - (f * f * f - f * Urho3D::Sin(f * Urho3D::M_PI))) + 0.5f;
                }
            }
    };

    class BounceEaseOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if(fParam < 4.f/11.0f)
                {
                    return (121.f * fParam * fParam)/16.0f;
                }
                else if(fParam < 8.f/11.0f)
                {
                    return (363.f/40.0f * fParam * fParam) - (99.f/10.0f * fParam) + 17.f/5.0f;
                }
                else if(fParam < 9.f/10.0f)
                {
                    return (4356.f/361.0f * fParam * fParam) - (35442.f/1805.0f * fParam) + 16061.f/1805.0f;
                }
                else
                {
                    return (54.f/5.0f * fParam * fParam) - (513.f/25.0f * fParam) + 268.f/25.0f;
                }
            }
    };

    class BounceEaseIn : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                BounceEaseOut b;
                return 1.f - b(1.f - fParam);
            }
    };

    class BounceEaseInOut : public ITween
    {
        public:

            virtual float operator()( float fParam )
            {
                if(fParam < 0.5f)
                {
                    BounceEaseIn b;
                    return 0.5f * b(fParam*2.f);
                }
                else
                {
                    BounceEaseOut b;
                    return 0.5f * b(fParam * 2.f - 1.f) + 0.5f;
                }
            }
    };

}
