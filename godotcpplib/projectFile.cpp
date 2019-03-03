%{Cpp:LicenseTemplate}\
@if "%{CreateClass}" == "true"
#include "CameraControl.h"
@endif

/** GDNative Initialize **/
extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *options) {
    godot::Godot::gdnative_init(options);
    //Godot::print("GDNATIVE_INIT");
}

/** GDNative Terminate **/
extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *options) {
    godot::Godot::gdnative_terminate(options);
    //Godot::print("GDNATIVE_TERMINATE");
}

/** NativeScript Initialize **/
extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);
    //Godot::print("NATIVESCRIPT_INIT");
@if "%{CreateClass}" == "true"
    godot::register_class<CameraControl>();
@endif
}
