#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <core/Godot.hpp>
#include <gen/Camera.hpp>
#include <gen/InputEvent.hpp>

using namespace godot;

class CameraControl : public Camera{
    GODOT_CLASS(CameraControl, Camera);
public:
    Vector3 m_translateVector = {0,0,0};
    Vector2 m_originalMousePosition = {0,0};
    Vector2 m_mousePosition = {0,0};
    float m_moveSpeed   = 1.0f;
    float m_mouseSensitivity = 0.3f;
    float m_moveScale = 0;
    real_t m_yaw = 0;
    real_t m_pitch = 0;
    bool m_rightButtonPressed = false;

    CameraControl(){}
    //Called when the node is created.
    void _init();
    //Called when the node is ready.
    void _ready();
    //Called when there is an input event. The input event propagates up through the node tree until a node consumes it.
    void _unhandled_input(Ref<InputEvent> event);
    //Called during the processing step of the main loop.
    void _process(float delta);
    static void _register_methods();

    ~CameraControl() = default;
};

#endif // CAMERACONTROL_H
