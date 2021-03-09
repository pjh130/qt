#include "texteditex.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QTextDocument>

TextEditEx::TextEditEx(QWidget *parent) :
    QTextEdit(parent)
{
//	connect(this, SIGNAL(textChanged()), this, SLOT(autoScrollSend()));
    connect(document(), SIGNAL(cursorPositionChanged( const QTextCursor &)), this, SLOT(autoScrollSend(const QTextCursor &)));
}
void TextEditEx::autoScrollSend(const QTextCursor &cursor)
{
    setTextCursor(cursor);
}//End

TextEditEx::~TextEditEx()
{
    removeAllCustomResource(true);
}
//add a custom resource,if the resname is not exist in the map,so insert resource into map
void TextEditEx::insertCustomResource(QString resName,QString resFile,bool forceUpdate)
{
    if(resName.count()>0)
    {
        QFileInfo resourceInfo(resFile);
        QString sufFix = resourceInfo.suffix();

        if(0==sufFix.compare(QString("gif"),Qt::CaseInsensitive))
        {
            if(!urlMovieResources.contains(resName) || forceUpdate)
            {
                if(forceUpdate)
                {
                    removeCustomResource(resName);
                }
                QMovie *movie = new QMovie(this);
                movie->setFileName(resFile);
                movie->setCacheMode(QMovie::CacheNone);
                urlMovieResources.insert(QUrl(resName),movie);
                urlResourcePath.insert(QUrl(resName),resFile);
                qDebug("TextEditEx::insertCustomResource--map insert %1 \n",resName.toStdString().c_str());
                connect(movie,SIGNAL(frameChanged(int)),this,SLOT(animateMovie(int)));
                movie->start();
            }
        }
        else if(QImageReader::supportedImageFormats().contains(resourceInfo.suffix().toLower().toLatin1()))
        {
            if(!urlImgResources.contains(QUrl(resName))|| forceUpdate)
            {
                if(forceUpdate)
                {
                    removeCustomResource(resName);
                }
                QImage *resImage = new QImage(resFile);
                urlImgResources.insert(QUrl(resName),resImage);
                urlResourcePath.insert(QUrl(resName),resFile);
            }
        }
    }
}

//remove the named resource,delete the resource Object if bRemoveObject is true.
void TextEditEx::removeCustomResource(QString resName)
{
    if(resName.count()>0)
    {
        //for png resource
        if(true)
        {
            ImgResourcesMgr::Iterator currentIterator;
            currentIterator = urlImgResources.find(QUrl(resName));
            if(currentIterator != urlImgResources.end())
            {
                QImage *tempImage = currentIterator.value();
                delete tempImage;
                urlImgResources.remove(QUrl(resName));
                urlResourcePath.remove(QUrl(resName));
            }
        }
        //for gif resource
        if(true)
        {
            MovieResourcesMgr::Iterator currentIterator;
            currentIterator = urlMovieResources.find(QUrl(resName));
            if(currentIterator != urlMovieResources.end())
            {
                QMovie *tempMovie = currentIterator.value();
                delete tempMovie;
                urlMovieResources.remove(QUrl(resName));
                urlResourcePath.remove(QUrl(resName));
            }
        }
    }
}

//remove all custom resource,delete the resource Object if bRemoveObject is true.
void TextEditEx::removeAllCustomResource( bool bRemoveObject)
{
    //for png resource
    if(true)
    {
        ImgResourcesMgr::Iterator currentIterator;
        for( currentIterator = urlImgResources.begin(); currentIterator!=urlImgResources.end();)
        {
            if(bRemoveObject)//delete the object
            {
                QImage *tempImage = currentIterator.value();
                delete tempImage;
            }
            urlResourcePath.remove(QUrl(currentIterator.key()));
            currentIterator = urlImgResources.erase(currentIterator);
        }
    }

    //for gif resource
    if(true)
    {
        MovieResourcesMgr::Iterator currentIterator;

        for( currentIterator = urlMovieResources.begin(); currentIterator!=urlMovieResources.end();)
        {
            if(bRemoveObject)//delete the object
            {
                QMovie *tempMovie = currentIterator.value();
                delete tempMovie;
            }
            urlResourcePath.remove(QUrl(currentIterator.key()));
            currentIterator = urlMovieResources.erase(currentIterator);
        }
    }
    //qApp->clipboard()->clear();
}

//render all resources.
void TextEditEx::reRenderCustomResource()
{
    ImgResourcesMgr::Iterator currentIterator;
    for( currentIterator = urlImgResources.begin(); currentIterator!=urlImgResources.end();currentIterator++)
    {
        QImage *tempImage = currentIterator.value();
        QTextDocument *doc = document();
        doc->addResource(QTextDocument::ImageResource,
                         currentIterator.key(),*tempImage);
        setLineWrapColumnOrWidth(lineWrapColumnOrWidth()); // ..刷新显示
    }
}

//render the named resource
void TextEditEx::reRenderCustomResource(QString resName)
{
    if(resName.count()>0)
    {
        ImgResourcesMgr::Iterator currentIterator;
        currentIterator = urlImgResources.find(QUrl(resName));
        if(currentIterator != urlImgResources.end())
        {
            QTextDocument *doc = document();
            QImage *tempImage = currentIterator.value();
            doc->addResource(QTextDocument::ImageResource,
                             currentIterator.key(),*tempImage);
            setLineWrapColumnOrWidth(lineWrapColumnOrWidth()); // ..刷新显示
        }
    }
}

const ImgResourcesMgr &TextEditEx::getImgResources()
{
    return urlImgResources;
}

const MovieResourcesMgr &TextEditEx::getMovieResources()
{
    return urlMovieResources;
}

const FileNameResourcesMgr &TextEditEx::getResourcePath()
{
    return urlResourcePath;
}

void TextEditEx::animateMovie(int)
{
    if (QMovie* movie = qobject_cast<QMovie*>(sender()))
    {
/*        QFileInfo resourceInfo(movie->fileName());
//        QString sufFix = resourceInfo.suffix();
//        QString resName = resourceInfo.fileName();
//        resName = resName.left(resName.length()-sufFix.length()-1);
//        resName.append("_gif");

        QString relName = resourceInfo.absoluteFilePath();
        if(relName.count()>0 && relName.at(0)==QChar(':'))
        {
            relName = relName.mid(1);
        }
        QString resName = relName.toUtf8().toBase64().data();
*/
        QString resName =getImgsrcName(movie->fileName());
        //driver the send text input box's gif movie.
        QTextDocument *doc = document();
        doc->addResource(QTextDocument::ImageResource,
                         QUrl(resName),movie->currentPixmap());
        setLineWrapColumnOrWidth(lineWrapColumnOrWidth()); // ..刷新显示
    }
}

QString TextEditEx::getImgsrcName(QString resFile)
{
    QFileInfo fileInfo(resFile);
    QString relName = fileInfo.absoluteFilePath();
    //if(relName.count()>0 && relName.at(0)==QChar(':'))
    //{
    //    relName = relName.mid(1);
    //}
    //QString tt = resFile.toUtf8().toPercentEncoding();
    //qDebug()<<"TextEditEx::getImgsrcName:"<<tt;
    QString faceName = relName.toUtf8().toPercentEncoding().toBase64().data();
    return /*"____" + */faceName;
}

void TextEditEx::insertRichText(QString resFile)
{
    if(!QFile::exists(resFile))
    {
        return;
    }

    QFileInfo fileInfo(resFile);
    QString sufFix = fileInfo.suffix();
    //insert gif into QMovie.
    if(0==sufFix.compare(QString("gif"),Qt::CaseInsensitive))
    {
            QString faceName = getImgsrcName(resFile);
            QString textRich = QString("<img src='%1'>").arg(faceName);
            qDebug()<<textRich;
//            qDebug()<<QByteArray::fromBase64(QByteArray(faceName.toStdString().c_str())).data();
            textCursor().insertHtml(textRich);
            insertCustomResource(faceName,resFile);
    }
    //insert the image supportted by QImage
    else if(QImageReader::supportedImageFormats().contains(fileInfo.suffix().toLower().toLatin1()))
    {
            QString faceName = getImgsrcName(resFile);
            QString textRich = QString("<img src='%1'>").arg(faceName);
            qDebug()<<textRich;
//            qDebug()<<QByteArray::fromBase64(QByteArray(faceName.toStdString().c_str())).data();
//            textCursor().insertImage(faceName);
            insertHtml(textRich);
            insertCustomResource(faceName,resFile);
            reRenderCustomResource(faceName);
    }
}

void TextEditEx::copyResourcefrom(const ImgResourcesMgr &srcResource)
{
    ImgResourcesMgr::const_iterator currentIterator;
    for(currentIterator = srcResource.begin();
        currentIterator!= srcResource.end();
        currentIterator++)
    {
        if(!urlImgResources.contains(currentIterator.key()))
        {
            QUrl srcUrl = currentIterator.key();
            QImage *srcImage = currentIterator.value();
            QImage *dstImage = new QImage(*srcImage);
            urlImgResources.insert(srcUrl,dstImage);
        }
    }
}

void TextEditEx::copyResourcefrom(const MovieResourcesMgr &srcResource)
{
    MovieResourcesMgr::const_iterator currentIterator;
    for(currentIterator = srcResource.begin();
        currentIterator!= srcResource.end();
        currentIterator++)
    {
        if(!urlMovieResources.contains(currentIterator.key()))
        {
            QUrl srcUrl = currentIterator.key();
            QMovie *srcMovie = currentIterator.value();
            QMovie *dstMovie = new QMovie(this);
            dstMovie->setFileName(srcMovie->fileName());
            dstMovie->setCacheMode(QMovie::CacheNone);
            urlMovieResources.insert(srcUrl,dstMovie);
            connect(dstMovie,SIGNAL(frameChanged(int)),this,SLOT(animateMovie(int)));
            dstMovie->start();
        }
    }
}

bool TextEditEx::canInsertFromMimeData ( const QMimeData * source ) const
{
//    qDebug()<<"myEditText::canInsertFromMimeData";

    if(source->hasImage())
    {
        return true;
    }
    else if(source->hasUrls())
    {
        return true;
    }
    else
    {
        return QTextEdit::canInsertFromMimeData(source);
    }
}

void TextEditEx::insertFromMimeData ( const QMimeData * source )
{
    qDebug()<<"myEditText::insertFromMimeData"<<source->formats();

    //for copy and paste
    if(source->hasImage())
    {
        qDebug()<<"myEditText::insertFromMimeData hasImage";
        QImage img = qvariant_cast<QImage>(source->imageData());
        if(!img.isNull())
        {
            QString sourceCachName = QString(QUuid::createUuid().toString());
            sourceCachName.append(".png");
            QString urlImagePath = QDir::tempPath() + QDir::separator() + "image/";
            QDir dir(urlImagePath);
            if(!dir.exists())
            {
                dir.mkpath(urlImagePath);
            }
            urlImagePath += sourceCachName;
            if(!QFile::exists(urlImagePath))
            {
                QImageWriter writer(urlImagePath);
                writer.write(img);
            }
            insertRichText(urlImagePath);
        }
//        textCursor().insertImage(urlImagePath);
    }
    //for drag and drop
    else if(source->hasUrls())
    {
        qDebug()<<"myEditText::insertFromMimeData hasUrls";
        QList<QUrl> urls = source->urls();
        foreach(QUrl url,urls)
        {
            QFileInfo info(url.toLocalFile());
            qDebug()<<"info.absoluteFilePath: "<<info.absoluteFilePath();

            if(info.exists())
            {
                emit fileDrag(info.absoluteFilePath());
                insertRichText(info.absoluteFilePath());
            }
        }
    }
    else if(source->hasHtml())
    {
        qDebug()<<"myEditText::insertFromMimeData hasHtml";
        QTextDocument *doc = new QTextDocument();
        if(doc!=NULL)
        {
            doc->setHtml(source->html());
            QTextFrame *frm = doc->rootFrame();
            for(QTextFrame::Iterator it = frm->begin(); it !=frm->end();it++)
            {
                QTextFrame *pFrm = it.currentFrame();
                if(NULL != pFrm)
                {
                    pFrm->dumpObjectInfo();
                }
                else if(it.currentBlock().isValid())
                {
                    QTextBlock tt = it.currentBlock();
                    for(QTextBlock::Iterator itb = tt.begin();itb!=tt.end();itb++)
                    {
                        QTextFragment tfmt = itb.fragment();
                        qDebug()<<tfmt.charFormat().type()<<tfmt.charFormat().objectType();
                        if(tfmt.charFormat().type() == QTextFormat::CharFormat)
                        {
                            if(tfmt.charFormat().objectType()==QTextFormat::NoObject)
                            {
                                QTextCharFormat tif = tfmt.charFormat().toCharFormat();
                                if(tif.isValid())
                                {
                                    QString partContent = tfmt.text();
                                    partContent.replace(0x2028,QLatin1Char('\n'));
                                    partContent = Qt::convertFromPlainText(partContent);
                                    textCursor().insertHtml(partContent);
//                                    qDebug()<<partContent;
                                }
                            }
                            else if(tfmt.charFormat().objectType()==QTextFormat::ImageObject)
                            {
                                QTextImageFormat tif = tfmt.charFormat().toImageFormat();
                                if(tif.isValid())
                                {
                                    QString fileName = tif.name();
                                    //处理一下文件
                                    QString strStart = "file:///";
                                    if(fileName.startsWith(strStart))
                                    {
                                        fileName = fileName.mid(strStart.length());
                                    }
                                    qDebug()<<"fileName------>"<<fileName;
                                    QFileInfo fileInfo;

                                    fileInfo.setFile(fileName);
                                    if(fileInfo.exists())
                                    {
                                        insertRichText(fileName);
                                    }
                                    else if(fileName.mid(0,3).compare(QString("qrc:"),Qt::CaseInsensitive))
                                    {
                                        QString decFileName = fileName.mid(3);
                                        fileInfo.setFile(decFileName);
                                        if(fileInfo.exists())
                                        {
                                            insertRichText(decFileName);
                                        }
                                    }
                                    else
                                    {
                                        QString decFileName = QByteArray::fromBase64(fileName.toUtf8());
                                        fileInfo.setFile(decFileName);
                                        if(fileInfo.exists())
                                        {
                                            insertRichText(decFileName);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            delete doc;
        }
    }
    else
    {
        QTextEdit::insertFromMimeData(source);
        qDebug()<<source->text();
    }
    ensureCursorVisible();
}

QStringList TextEditEx::serializeResource()
{
    QStringList resList;
    for(FileNameResourcesMgr::Iterator it= urlResourcePath.begin();it!=urlResourcePath.end();it++)
    {
        QString resItem = QString("%1").arg(it.value());
        resList.append(resItem);
    }
    return resList;
}
//
//void TextEditEx::dragEnterEvent(QDragEnterEvent *e)
//{
//    qDebug()<<"TextEditEx::dragEnterEvent";
//	e->acceptProposedAction();
//	QTextEdit::dragEnterEvent(e);
//}
//
//void TextEditEx::dropEvent(QDropEvent *e)
//{
//    qDebug()<<"TextEditEx::dropEvent";
//    QList<QUrl> lstUrl = e->mimeData()->urls();
//    for(int i=0; i<lstUrl.length(); i++)
//    {
//        qDebug()<<"file:"<<lstUrl.at(i).toLocalFile();
//        emit fileDrag(lstUrl.at(i).toLocalFile());
//    }
//}

void TextEditEx::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
    {
        emit enterKeyPressed(e);

        if (!e->isAccepted())
        {
            return;
        }
    }
    QTextEdit::keyPressEvent(e);
}
