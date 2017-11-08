#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qts.h"
#include "vtks.h"
#include "customWidgets/greenbutton.h"
#include "myvolumewidget.h"
#include "customWidgets/backgroundbutton.h"
#include "myslicerwidget.h"
#include "vtkcustomtransformanimationcue.h"
#include "stlmanager.h"
#include "actormanager.h"
#include "customWidgets/mygridlayout.h"
#include "customWidgets/mydialog.h"
#include "customWidgets/threebackgroundbutton.h"
#include "customWidgets/markbutton.h"
#include "tools/constant.h"
#include "tools/screentools.h"
#include "customWidgets/selectpropertywidget.h"
#include <string>
#include "customThread/progressbarwidget.h"
#include "customThread/volumewidgetthreadhelper.h"
#include <math.h>
#include "customAnimator/animator.h"
#include "customAnimator/motion.h"

/**
 * @brief The MainWindow class
 * 这是主窗口
 */
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    bool m_embedded;
    QPixmap m_background;

    void init();

    void setLayout();

    void setLayout2();

    void setConnection();

    void setDrawConnection();

    void onOpenVolumeDir();

    void obtainFocus();

    StlManager *stlManager;
    actorManager *actorM;

    QPushButton *proSelectButton;
    SelectPropertyWidget *selectProWidget;
    BackgroundButton *titleButton;
    ThreeBackgroundButton *minimizeButton;//最小化主窗口
    ThreeBackgroundButton *maxmizeButton;//最大化
    ThreeBackgroundButton *exitButton;
/*start-edit   with lvyunxiao         -----------------------------------------------------*/
    MarkButton *pEndMarkButton;
    MarkButton *pStartMarkButton;
/*end-edit with lvyunxiao------------------------------------------------------------*/
    BackgroundButton *volumeLoadButton;
    BackgroundButton *stlLoadButton;
    BackgroundButton *stlSelectButton;
    BackgroundButton *stlDeleteButton;//按下弹出删除哪个.stl模型的对话框
    BackgroundButton *volumeMagnifyButton;
    BackgroundButton *magnifyButton;
    BackgroundButton *shrinkButton;
    myVolumeWidget *volumeWidget;
    mySlicerWidget *sagitalWidget;
    mySlicerWidget *coronalWidget;
    mySlicerWidget *axialWidget;
    QSlider *volumeSlider;
    QSlider *coronalSlider;
    QSlider *axialSlider;
    QSlider *sagitalSlider;
    QLabel *sagitalLabel;
    QLabel *axialLabel;
    QLabel *coronalLabel;
    MyDialog *stlLoadDialog;//选择加载哪个.stl模型
    MyDialog *stlSelectDialog;//选择操作哪个.stl模型
    MyDialog *stlDeleteDialog;//选择删除哪个.stl模型
    bool isOpenDir=false;
    int lastposition;
    //能否做标记
    bool canTarger=false;
    //vtk qt 事件链接
    vtkSmartPointer<vtkEventQtSlotConnect> vtkQtConnect;
    //体绘制数据
    vtkSmartPointer<vtkVolume> volume;
    //当前操作的stl名
    QString operationStlName;

    bool max=false;

    QPoint mouseClickPoint;
    bool isMouseHover=false;
    ProgressBarWidget *progressBar;
signals:
    void Mark(vtkVector3d ModelPosition);

public slots:
    void volumeLoadClicked();
    void exitClicked();
    void volumeMagnifyClicked();
    void magnifyClicked();
    void shrinkCliked();
    void focusButtonClicked();
    void maxmizeClicked();
    void minimizeClicked();

    void vSlicerValueChange(int v);
    void sSlicerValueChange(int v);
    void aSlicerValueChange(int v);
    void cSlicerValueChange(int v);

    void stlLoadButtonClicked();
    void stlSelectButtonClicked();
    void stlDeleteButtonClicked();
    void deleteStl(QString name, int index);
    void loadStl(QString name, int index);
    void selectStl(QString name, int index);

/*start-edit with lvyunxiao--------------------------------------------*/
    void volumeSlicerRetunZero();
    void onDataLoadingDone();
    void receiveFocus();
    void markedAnimator(bool marked);
    void startSurgeryAnimator(double startPosition[3],double endPosition[3]);
/*end-edit with lvyunxiao-----------------------------------------------*/
protected:

    void update_background();

    virtual void paintEvent(QPaintEvent* event);

    virtual void keyPressEvent(QKeyEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    QList<QString> stlList={};
};

#endif // MAINWINDOW_H
