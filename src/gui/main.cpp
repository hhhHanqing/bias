#include <list>
#include <QApplication>
#include <QSharedPointer>
#include <QMessageBox>
#include "camera_window.hpp"
#include "camera_facade.hpp"

// ------------------------------------------------------------------------
// TO DO ... temporary main function. Currently just opens a camera
// window for each camera found attached to the system.
// ------------------------------------------------------------------------
int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    bias::GuidList guidList;
    bias::CameraFinder cameraFinder;
    std::list<QSharedPointer<bias::CameraWindow>> windowPtrList;

    // Get list guids for all cameras found
    try
    { 
        guidList = cameraFinder.getGuidList();
    }
    catch (bias::RuntimeError &runtimeError)
    {
        QString msgTitle("Camera Enumeration Error");
        QString msgText("Camera enumeration failed:\n\nError ID: ");
        msgText += QString::number(runtimeError.id());
        msgText += QString("\n\n");
        msgText += QString::fromStdString(runtimeError.what());
        QMessageBox::critical(0, msgTitle,msgText);
        return 0;
    }

    // If no cameras found - error
    if (guidList.empty()) 
    {
        QString msgTitle("Camera Enumeration Error");
        QString msgText("No cameras found");
        QMessageBox::critical(0, msgTitle,msgText);
        return 0;
    }

    // Open camera window for each camera 
    bias::GuidList::iterator guidIt;
    for (guidIt=guidList.begin(); guidIt!=guidList.end(); guidIt++)
    {
        bias::Guid guid = *guidIt;
        QSharedPointer<bias::CameraWindow> windowPtr(new bias::CameraWindow(guid));
        windowPtr -> show();
        windowPtrList.push_back(windowPtr);
    }
    return app.exec();
}
