#include "object.h"

class Animator : public Object {
public:
    virtual void animate() = 0;
    // Add other common animator methods here
};

// Example implementation of an animator
class FadeAnimator : public Animator {
public:
    void animate() override {
        // Implement the animation logic here
    }
};