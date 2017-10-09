#ifndef MAINWINDOW_H
#define MAINWINDOW_H


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    bool m_embedded;
    QPixmap m_device;

protected:
    void update_background();

    virtual void paintEvent(QPaintEvent* event);

};

#endif // MAINWINDOW_H
