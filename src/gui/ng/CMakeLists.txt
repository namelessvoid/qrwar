find_package(SFML 2.5 REQUIRED graphics)
add_library(namelessgui
    gui.cpp
	button.cpp
	buttongroup.cpp
    text.cpp
    label.cpp
    lineinput.cpp
    radiotogglebutton.cpp
	spritewidget.cpp
	widget.cpp
    widgeteventmixin.cpp
	window.cpp
    confirmationdialog.cpp
    messagedialog.cpp
    tabwidget.cpp
    spinbox.cpp
    listwidget.cpp
    listitem.cpp
    croppingviewfactory.cpp
    scrollbar.cpp
)
target_include_directories(namelessgui
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(namelessgui sfml-graphics)
