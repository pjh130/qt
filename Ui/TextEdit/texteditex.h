#ifndef TEXTEDITEX_H
#define TEXTEDITEX_H

#include <QTextEdit>
#include <QFileInfo>
#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QDir>
#include <QTextEdit>
#include <QFileInfo>
#include <QUrl>
#include <QHash>
#include <QMovie>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QUuid>
#include <QTextDocument>
#include <QTextBlock>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>

typedef QHash<QUrl, QImage*>  ImgResourcesMgr;   //picture driver.
typedef QHash<QUrl, QMovie*>  MovieResourcesMgr;   //Movie driver.
typedef QHash<QUrl, QString>  FileNameResourcesMgr;   //resource file name driver.

class TextEditEx : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEditEx(QWidget *parent = 0);
    ~TextEditEx();

signals:
    void fileDrag(QString strFilePath);
    void enterKeyPressed(QKeyEvent*);

public slots:
    void animateMovie(int);
    //void clipBoxChanged();
    void autoScrollSend(const QTextCursor &cursor);
public:
    //add a custom resource,if the resname is not exist in the map,so insert resource into map
    void insertCustomResource(QString resName,QString resFile,bool forceUpdate=false);
    //add a rich text into the textedit.
    void insertRichText(QString resFile);
    //remove the named resource,delete the resource Object if bRemoveObject is true.
    void removeCustomResource(QString resName);
    //remove all custom resource,delete the resource Object if bRemoveObject is true.
    void removeAllCustomResource( bool bRemoveObject = true);
    //render all resources.
    void reRenderCustomResource();
    //render the named resource
    void reRenderCustomResource(QString resName);
    const ImgResourcesMgr &getImgResources();
    const MovieResourcesMgr &getMovieResources();
    const FileNameResourcesMgr &getResourcePath();
    void copyResourcefrom(const ImgResourcesMgr &srcResource);
    void copyResourcefrom(const MovieResourcesMgr &srcResource);
    QString getImgsrcName(QString resFile);
    QStringList serializeResource();
protected:
    virtual bool canInsertFromMimeData ( const QMimeData * source ) const;
    virtual void insertFromMimeData ( const QMimeData * source );
    //virtual void dragEnterEvent(QDragEnterEvent *e);
    //virtual void dropEvent(QDropEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
private:
    ImgResourcesMgr urlImgResources;      //picture driver.
    MovieResourcesMgr urlMovieResources;  //Movie driver.
    FileNameResourcesMgr urlResourcePath; //resource path;
};

#endif // TEXTEDITEX_H
