#ifndef USBHANDLE_H
#define USBHANDLE_H

#include <QAbstractNativeEventFilter>
#include <windows.h>
#include <QMessageBox>

class UsbHandle: public QAbstractNativeEventFilter
{
public:
    UsbHandle();
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
};

#endif // USBHANDLE_H
