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

public slots:

    void navigationClicked();

    void exitClicked();

    void translateClicked();

    void magnifyClicked();

    void shrinkCliked();

    void vSlicerValueChange(int v);
    void sSlicerValueChange(int v);
    void aSlicerValueChange(int v);
    void cSlicerValueChange(int v);

    void greenButton1Clicked();
    void greenButton2Clicked();

private:
    bool m_embedded;
    QPixmap m_background;
    // GreenButton greenButton1;
    // GreenButton greenButton2;

    void init();

    void setLayout();

    void setConnection();

    void setDrawConnection();

    void onOpenVolumeDir();

    GreenButton *greenButton1;
    GreenButton *greenButton2;
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


    bool isOpenDir;
    int lastposition;
    bool hasVolumeData=false;

protected:
    void update_background();

    virtual void paintEvent(QPaintEvent* event);

    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
