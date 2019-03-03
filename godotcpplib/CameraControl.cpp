#include "CameraControl.h"
#include <gen/Input.hpp>
#include <gen/InputEventMouseMotion.hpp>
#include <gen/InputEventMouseButton.hpp>
#include <gen/GlobalConstants.hpp>

static inline real_t deg2rad(real_t &deg)
{ return deg * Math_PI / 180.0; }

static inline real_t clamp(real_t value, real_t min, real_t max)
{ return value < min ? min : (value > max ? max : value);}

void CameraControl::_init()
{

}

void CameraControl::_ready()
{
    Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
}

void CameraControl::_unhandled_input(Ref<InputEvent> event)
{
    m_translateVector = {0,0,0};
    //Mouse
    Ref<InputEventMouseButton> mouseButton = event;
    if (event->is_class( mouseButton->___get_class_name() )) {
        //Right mouse button is pressed
        if(mouseButton->is_pressed() && mouseButton->get_button_mask() == GlobalConstants::BUTTON_RIGHT){
            m_rightButtonPressed = true;
            m_originalMousePosition = mouseButton->get_global_position();
            Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
        } else if (m_rightButtonPressed){ //Right mouse button is released
            m_rightButtonPressed = false;
            Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
            Input::get_singleton()->warp_mouse_position(m_originalMousePosition);
        }
    }

    Ref<InputEventMouseMotion> mouseMotion = event;
    if (event->is_class( mouseMotion->___get_class_name() ))
    {
        if(m_rightButtonPressed){
            m_yaw += mouseMotion->get_relative().x * -m_mouseSensitivity;
            m_pitch = clamp( m_pitch += (mouseMotion->get_relative().y * -m_mouseSensitivity ), -90.0f, 90.0f );

            set_rotation( Vector3(0, deg2rad(m_yaw), 0) );
            rotate_object_local( Vector3(1,0,0), deg2rad(m_pitch) );
        }
    }
}

void CameraControl::_process(float delta)
{
    //Speed is not dependent on framerate
    m_moveScale = m_moveSpeed * delta;
    m_translateVector = {0,0,0};

    //Keyboard
    if(Input::get_singleton()->is_key_pressed(godot::GlobalConstants::KEY_A)){
        m_translateVector.x = -m_moveScale;
    }
    if(Input::get_singleton()->is_key_pressed(godot::GlobalConstants::KEY_D)){
        m_translateVector.x = m_moveScale;
    }
    if(Input::get_singleton()->is_key_pressed(godot::GlobalConstants::KEY_W)){
        m_translateVector.z = -m_moveScale;
    }
    if(Input::get_singleton()->is_key_pressed(godot::GlobalConstants::KEY_S)){
        m_translateVector.z = m_moveScale;
    }
    if(Input::get_singleton()->is_key_pressed(godot::GlobalConstants::KEY_SPACE)){
        m_translateVector.y = m_moveScale;
    }
    if(Input::get_singleton()->is_key_pressed(godot::GlobalConstants::KEY_CONTROL)){
        m_translateVector.y = -m_moveScale;
    }

    translate(m_translateVector);
}

void CameraControl::_register_methods()
{
    register_method("_init", &CameraControl::_init);
    register_method("_ready", &CameraControl::_ready);
    register_method("_unhandled_input", &CameraControl::_unhandled_input);
    register_method("_process", &CameraControl::_process);
}
