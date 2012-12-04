#include "video_writer_bmp.hpp"
#include "basic_types.hpp"
#include "exception.hpp"
#include <iostream>
#include <QFileInfo>
#include <stdexcept>
#include <opencv2/highgui/highgui.hpp>

namespace bias
{
    const QString IMAGE_FILE_BASE = QString("image_");
    const QString IMAGE_FILE_EXT = QString(".bmp");

    VideoWriter_bmp::VideoWriter_bmp() : VideoWriter() 
    {
        isFirst_ = true;
    }

    VideoWriter_bmp::VideoWriter_bmp(QString fileName) : VideoWriter(fileName) 
    {
        isFirst_ = true;
    }

    VideoWriter_bmp::~VideoWriter_bmp() {}

    void VideoWriter_bmp::addFrame(StampedImage stampedImg)
    {
        if (isFirst_)
        {
            initialize();
            isFirst_= false;
        }

        QString imageFileName = IMAGE_FILE_BASE;  
        imageFileName += QString::number(frameCount_);
        imageFileName += IMAGE_FILE_EXT;
        QFileInfo imageFileInfo(logDir_,imageFileName);
        QString fullPathName = imageFileInfo.absoluteFilePath();
        if (frameCount_%2==0) 
        {
            try
            {
                cv::imwrite(fullPathName.toStdString(), stampedImg.image);
            }
            catch (std::runtime_error &err)
            {
                unsigned int errorId = ERROR_VIDEO_WRITER_ADD_FRAME;
                std::string errorMsg("adding frame failed - "); 
                errorMsg += err.what();
                throw RuntimeError(errorId, errorMsg);
            }
        }
        frameCount_++;
    }

    void VideoWriter_bmp::initialize()
    {
        QFileInfo fileInfo(fileName_);
        baseName_ = fileInfo.baseName();
        baseDir_ = fileInfo.dir();

        if (!baseDir_.exists())
        {
            unsigned int errorId = ERROR_VIDEO_WRITER_INITIALIZE;
            std::string errorMsg("base log directory, "); 
            errorMsg += baseDir_.absolutePath().toStdString();
            errorMsg += std::string("does not exist");
            throw RuntimeError(errorId, errorMsg);
        }

        logDir_ = QDir(baseDir_.absolutePath() + "/" + baseName_);
        if (logDir_.exists()) 
        {
            // Log directory exists - increment baseName until we find
            // one which doesn't a bit kludgey, but easy.
            QString baseNameTemp;

            unsigned int cnt = 1;
            while (logDir_.exists())
            {
                baseNameTemp =  baseName_ + "_" + QString::number(cnt);
                logDir_ = QDir(baseDir_.absolutePath() + "/" + baseNameTemp);
                cnt++;
            }

            baseName_ = baseNameTemp;
        }

        if (!baseDir_.mkdir(baseName_))
        {
            unsigned int errorId = ERROR_VIDEO_WRITER_INITIALIZE;
            std::string errorMsg("unable to create log directory, "); 
            errorMsg += baseDir_.absolutePath().toStdString();
            throw RuntimeError(errorId, errorMsg);
        }

    }

} // namespace bias
