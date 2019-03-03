TEMPLATE = lib
CONFIG  -= qt
DEFINES += UNICODE
TARGET   = %{ProjectName}

#Define paths here
GODOT_NATIVE_LIBRARY = "%{GDNativePath}"
GODOT_HOME = "%{GodotHomePath}"

INCLUDEPATH += "$${GODOT_NATIVE_LIBRARY}\\godot_headers"
INCLUDEPATH += "$${GODOT_NATIVE_LIBRARY}\\include"
INCLUDEPATH += "$${GODOT_NATIVE_LIBRARY}\\include\\gen"
INCLUDEPATH += "$${GODOT_NATIVE_LIBRARY}\\include\\core"

debug {
    QMAKE_CXXFLAGS_DEBUG += /std:c++latest /EHsc /D_DEBUG /MDd
    LIBS += -L$${GODOT_NATIVE_LIBRARY}\\bin -llibgodot-cpp.windows.debug.64
    LIBS += -L$${GODOT_HOME}\\bin -lgodot.windows.opt.debug.64
}

release {
    QMAKE_CXXFLAGS_RELEASE += /std:c++latest /O2 /EHsc /DNDEBUG /MD
    LIBS += -L$${GODOT_NATIVE_LIBRARY}\\bin -llibgodot-cpp.windows.release.64
    LIBS += -L$${GODOT_HOME}\\bin -lgodot.windows.opt.64
}

SOURCES += \\
        %{CppFileName} \\
@if "%{CreateClass}" == "true"
        %{CppHeader}
@endif

HEADERS += \\
@if "%{CreateClass}" == "true"
        %{CppSource}
@endif
