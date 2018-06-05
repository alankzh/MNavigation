#ifndef PROJECTPOP_H
#define PROJECTPOP_H
#include <QtWidgets>

//手术方案创建窗口
class ProjectPop:QWidget
{
public:
    Q_OBJECT
    ProjectPop(QWidget *parent=nullptr);

    void Show();

    void Hide();

    void AffirmCreateProject();
};

#endif // PROJECTPOP_H
