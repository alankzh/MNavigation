#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qts.h"
#include "vtks.h"
#include "greenbutton.h"
#include "myvolumewidget.h"
#include "backgroundbutton.h"
#include "rendersetting.h"
#include "myslicerwidget.h"
#include "vtkcustomtransformanimationcue.h"
#include "stlmanager.h"
#include "actormanager.h"
#include "mygridlayout.h"
#include "mydialog.h"
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
    // GreenButton greenButton1;
    // GreenButton greenButton2;

    void init();

    void setLayout();

    void reset();

    void setConnection();

    void setDrawConnection();

    void onOpenVolumeDir();

    StlManager *stlManager;
    actorManager *actorM;

    BackgroundButton *greenButton1;
    BackgroundButton *greenButton2;
    BackgroundButton *navigationButton;
    BackgroundButton *exitButton;
    BackgroundButton *translateButton;
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
    BackgroundButton *stlDeleteButton;//按下弹出删除哪个.stl模型的对话框
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

    //比例
    double proportionZ;
    double proportionY;
    double proportionX;

signals:
	void Mark(vtkVector3d ModelPosition);

public slots:

	void navigationClicked();
	void exitClicked();
	void translateClicked();
	void magnifyClicked();
	void shrinkCliked();
    void focusButtonClicked();

	void vSlicerValueChange(int v);
	void sSlicerValueChange(int v);
	void aSlicerValueChange(int v);
	void cSlicerValueChange(int v);

	void greenButton1Clicked();
	void greenButton2Clicked();
	void deleteButtonClicked();
	void deleteStl(QString name, int index);
	void loadStl(QString name, int index);
	void selectStl(QString name, int index);
protected:

    void update_background();

    virtual void paintEvent(QPaintEvent* event);

    virtual void keyPressEvent(QKeyEvent *event);

    QList<QString> stlList={};
};

#endif // MAINWINDOW_H
