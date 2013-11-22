TEMPLATE = app
TARGET = vision_framework
INCLUDEPATH += . \
    /usr/local/include/opencv \
    /usr/local/lib \
    /usr/local/include 
LIBS += -L/usr/lib \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_calib3d \
    -lopencv_video \
    -lopencv_features2d \
    -lopencv_ml \
    -lopencv_highgui \
    -lopencv_objdetect \
    -lopencv_contrib \
    -lopencv_legacy \
    -lopencv_flann \
    -lcvblob \
    -lQtGui \
    -lQtCore \
    -lpthread
HEADERS += dimensionsfielddialog.h \
    FrameLabel.h \
    Structures.h \
    captureconnectdialog.h \
    capturefromfile.h \
    framedata.h \
    ringbuffer.h \
    cvimageqt.h \
    plugin_detect_balls.h \
    ball.h \
    homography.h \
    plugin_networking.h \
    practicalsocket.h \
    editcolorgui.h \
    subqlabel.h \
    colorspace.h \
    segmentation.h \
    pattern_matching.h \
    team.h \
    pattern.h \
    marker.h \
    plugin_find_secondaries_blobs.h \
    plugin_morphology.h \
    plugin_find_blobs.h \
    plugin_colorsegmentation.h \
    plugin_colorconversions.h \
    globaltracking.h \
    trackingstrategy.h \
    timer.h \
    datastruct.h \
    visionplugin.h \
    visionstack.h \
    capturefromcamera.h \
    captureinterface.h \
    capture_thread.h \
    mainwindow.h
FORMS += DimensionsFieldDialog.ui \
    CaptureConnectDialog.ui \
    editcolorgui.ui \
    mainwindow.ui
SOURCES += dimensionsfielddialog.cpp \
    FrameLabel.cpp \
    captureconnectdialog.cpp \
    capturefromfile.cpp \
    framedata.cpp \
    ringbuffer.cpp \
    cvimageqt.cpp \
    plugin_detect_balls.cpp \
    ball.cpp \
    homography.cpp \
    plugin_networking.cpp \
    practicalsocket.cpp \
    editcolorgui.cpp \
    subqlabel.cpp \
    colorspace.cpp \
    segmentation.cpp \
    pattern_matching.cpp \
    team.cpp \
    pattern.cpp \
    marker.cpp \
    plugin_find_secondaries_blobs.cpp \
    plugin_morphology.cpp \
    plugin_find_blobs.cpp \
    plugin_colorsegmentation.cpp \
    plugin_colorconversions.cpp \
    globaltracking.cpp \
    trackingstrategy.cpp \
    visionplugin.cpp \
    visionstack.cpp \
    capturefromcamera.cpp \
    captureinterface.cpp \
    capture_thread.cpp \
    main.cpp \
    mainwindow.cpp
