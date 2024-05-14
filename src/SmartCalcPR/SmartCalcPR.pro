QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    lib/s21_credit.c \
    lib/s21_credit_list.c \
    lib/s21_deposit.c \
    main.cpp \
    mainwindow.cpp \
    plot_window.cpp \
    qcustomplot.cpp \
    lib/s21_calc.c \
    lib/s21_list.c

HEADERS += \
    lib/s21_credit.h \
    lib/s21_deposit.h \
    mainwindow.h \
    lib/s21_calc.h \
    plot_window.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui \
    plot_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
