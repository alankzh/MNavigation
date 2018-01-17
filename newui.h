#ifndef NEWUI_H
#define NEWUI_H
#include "qts.h"
#include "customWidgets/dirlistwidget.h"
#include "customWidgets/dicominfowidget.h"
#include "tools/constant.h"
#include "DicomLoader.h"
#include "customWidgets/drawwidget.h"
#include "tools/screentools.h"
#include "customWidgets/operationplanwidget.h"
#include "customWidgets/textureselectwidget.h"
#include "customThread/loadthreadhelper.h"
#include "customThread/progressbarwidget.h"
#include "customThread/progressobserver.h"
#include <QSizePolicy>


/**
 * @brief The NewUi class
 * ������,�·��UI����
 */
class NewUi : public QWidget
{
    Q_OBJECT
public:
    NewUi(QWidget *parent = 0);
    ~NewUi();
public slots:
    void loadVolumeData(QString name,QString dirPath);
    void showLoadDialog();

    void onDataLoadingDone();
private:
    void init();
    void connection();

    /*������� start-------------------------------------------------------------------------------------------*/
    DirListWidget *dirListWidget=NULL;
    DicomInfoWidget *dicomInfoWidget=NULL;

    DrawWidget *drawWidget=NULL;

    OperationPlanWidget *operationPlanWidget=NULL;
    TextureSelectWidget *textureSelectWidget=NULL;
    /*������� end  -------------------------------------------------------------------------------------------*/

    /*�߳���� start--------------------------------------------------------------------------------------------*/
    LoadThreadHelper *threadHelper=NULL;
    ProgressBarWidget *progressBar;
    ProgressObserver::Pointer observer;
    ProgressReceive *receive;
    /*�߳���� end----------------------------------------------------------------------------------------------*/

    /*������� start--------------------------------------------------------------------------------------------*/
    QString dirPath;
    /*������� end---------------------------------------------------------------------------------------------*/
};

#endif // NEWUI_H
