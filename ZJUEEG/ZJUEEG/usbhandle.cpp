#include "usbhandle.h"


UsbHandle::UsbHandle()
{

}


bool UsbHandle::nativeEventFilter(const QByteArray &eventType, void *message, long *result){
    if(eventType == "windows_generic_MSG"){
        MSG* ev = static_cast<MSG *>(message);
        if(ev->message == WM_DEVICECHANGE){
            qDebug("here2");
        }
    }
    return false;
}
