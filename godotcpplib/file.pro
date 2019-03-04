TEMPLATE = lib
CONFIG  -= qt
DEFINES += UNICODE
TARGET   = %{ProjectName}

#Define paths here
GODOT_NATIVE_LIBRARY = "%{GDNativePath}"

INCLUDEPATH += "$${GODOT_NATIVE_LIBRARY}/godot_headers"
INCLUDEPATH += "$${GODOT_NATIVE_LIBRARY}/include"
INCLUDEPATH += "$${GODOT_NATIVE_LIBRARY}/include/gen"
INCLUDEPATH += "$${GODOT_NATIVE_LIBRARY}/include/core"

win32 {
    debug {
        QMAKE_CXXFLAGS_DEBUG += /std:c++latest /EHsc /D_DEBUG /MDd
        LIBS += -L$${GODOT_NATIVE_LIBRARY}/bin -llibgodot-cpp.windows.debug.64
    }
    release {
        QMAKE_CXXFLAGS_RELEASE += /std:c++latest /Os /EHsc /DNDEBUG /MD
        LIBS += -L$${GODOT_NATIVE_LIBRARY}/bin -llibgodot-cpp.windows.release.64
    }
}

linux-g++ | linux-g++-64 {
    debug {
        QMAKE_CXXFLAGS_DEBUG += -fPIC -std=c++17 -g -O2
        LIBS += -L$${GODOT_NATIVE_LIBRARY}/bin -lgodot-cpp.linux.debug.64
    }
    release {
        QMAKE_CXXFLAGS_RELEASE += -fPIC -std=c++17 -Os
        LIBS += -L$${GODOT_NATIVE_LIBRARY}/bin -lgodot-cpp.linux.release.64
    }
}
SOURCES += \\
        %{CppFileName} \\
@if "%{CreateClass}" == "true"
        %{CppSource}
@endif

HEADERS += \\
@if "%{CreateClass}" == "true"
        %{CppHeader}
@endif
