#include "dirlistwidget.h"

DirListWidget::DirListWidget(QWidget *parent):QWidget(parent)
{
    setWindowFlags(Qt::SplashScreen);
    setMaximumSize(200,287);
    setMinimumSize(200,287);
//    this->setStyleSheet(
//                 "background:#f0f0f0"
//                );

    mainLayout=new QVBoxLayout();
    mainLayout->setMargin(0);
    title=new QLabel(QString::fromLocal8Bit("资料库"));
    title->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    title->setStyleSheet(QLABEL_LITTLE_TITLE_STYLE);
    title->setPalette(Constant::getCommanFontColor());
    title->setFont(Constant::get12FontSize());
    title->resize(200,26);
    title->setMaximumSize(200,26);
    title->setMinimumSize(200,26);
    title->setMargin(0);
    listWidget=new MyListWidget();
    listWidget->setMaximumWidth(200);
    listWidget->setMinimumWidth(200);
    listWidget->loadData(dirList);
    QHBoxLayout *buttonLayout=new QHBoxLayout();
    buttonLayout->setMargin(0);
    loadButton=new QPushButton(QString::fromLocal8Bit("载入"));
    loadButton->setFont(Constant::get12FontSize());
    loadButton->setPalette(Constant::getCommanFontColor());
    loadButton->setStyleSheet(QPUSHBUTTON_COMMON_BUTTON_STYLE);
    loadButton->resize(QPUSHBUTTON_LONG_SIZE);
    loadButton->setMinimumSize(QPUSHBUTTON_LONG_SIZE);
    loadButton->setMaximumSize(QPUSHBUTTON_LONG_SIZE);
    iconButton=new QPushButton(0);
    iconButton->setIcon(QIcon(":/resources/folder-open.png"));
    iconButton->setStyleSheet(QPUSHBUTTON_COMMON_BUTTON_STYLE);
    iconButton->resize(QPUSHBUTTON_SHORT_SIZE);
    iconButton->setMinimumSize(QPUSHBUTTON_SHORT_SIZE);
    iconButton->setMaximumSize(QPUSHBUTTON_SHORT_SIZE);
    buttonLayout->addWidget(iconButton);
    buttonLayout->addWidget(loadButton);
    mainLayout->addWidget(title);
    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(buttonLayout);
    this->setLayout(mainLayout);

    connect(iconButton,SIGNAL(clicked()),this,SLOT(iconButtonClicked()));
    connect(loadButton,SIGNAL(clicked()),this,SLOT(loadButtonClicked()));
    connect(listWidget,SIGNAL(mySonItemBePressed(int)),this,SLOT(listItemPressed(int)));
    connect(listWidget,SIGNAL(mySonItemBeDoubleClick(int)),this,SLOT(listItemDoubleClicked(int)));
}

DirListWidget::~DirListWidget(){

}

//将用户编辑和新加载的路径保存到json格式
void DirListWidget::saveDirBean(QString name,QString realPath,QString studyDate,QString studyTime){
    qDebug()<<"DirListWidget::saveDirBean";
    int index=-1;
    //查看是否此路径已经存在于历史列表中
    for(int i=0;i<dirList.size();i++){
        if(realPath==dirList[i].getRealPath()){
            index=i;
        }
    }
    if(index!=-1){
        if(dirList[index].getName()!=name){
            //用户编辑了行内标识符
            //将此用户编辑行改变标识符
            dirList[index].setName(name);
            renewal();
        }else{
            //用户按“载入”按钮，加载了以往的文件路径
            //TODO 将这个路径置顶
        }
    }else{
        //逻辑循环进入这一步，说明这是用户新打开的路径
        //保存新路径
        DirBean bean(name,realPath,studyDate,studyTime);
        dirList.insert(0,bean);
        renewal();
    //    listView->selectOn(0);
    }
   saveDirList2JSON();
}

//加载本地路径下的json格式
void DirListWidget::loadPath(){
    rapidjson::Document document;
    JsonUtils::ResultCode info=JsonUtils::ParseFile(DIRPATH_RESOURCE.toStdString(),document);
    //加载成功、解析成功
    if(info==JsonUtils::kSuccess){
        if(document.HasMember("history")){
            rapidjson::Value& a=document["history"];
            if(a.IsArray()){
                for (int i = 0; i < a.Size(); i++){
                    DirBean dirbean;
                    const rapidjson::Value &object=a[i];
                    dirbean.setName(object["name"].GetString());
                    dirbean.setRealPath(object["realPath"].GetString());
                    dirbean.setStudyDate(object["studyDate"].GetString());
                    dirbean.setStudyTime(object["studyTime"].GetString());
                    //json字符串中，最后的数组打开时间最远
                    dirList.append(dirbean);
                    renewal();
                }
            }else{
                qDebug()<<"JsonParseException";
            }
        }else{
            qDebug()<<"JsonParseException";
        }
    }else if(info==JsonUtils::kFailToOpenFile){
        //文件打开有误
        qDebug()<<"FileIOException";
    }else if(info==JsonUtils::kParseError){
        //json解析有误
        qDebug()<<"JsonParseException";
    }
}

//将用户编辑的new name保存到json中
void DirListWidget::saveItemChange(QString newName){
    qDebug()<<"DirListWidget::saveItemChange";
    QString name=dirList[index].getName();
    if(newName==name){
        //do nothing
        qDebug()<<"no change";
    }else{
        //TODO 用户将无法再编辑，而是通过对话框回调
      //  saveDirBean(newName,dirList[index].getRealPath(),dirList[index].getStudyDate(),dirList[index].getStudyTime());
    }
}

//加载新的体绘制数据时，加入listWidget中
void DirListWidget::popDirPath(QString path){
    if(DicomLoader::HasData()){
        QString name(QString::fromStdString(DicomLoader::GetDataInfo()->patient_name));
        QString studyDate(QString::fromStdString(DicomLoader::GetDataInfo()->study_date));
        QString studyTime(QString::fromStdString(DicomLoader::GetDataInfo()->study_time));
        DirBean dirBean(name,path,studyDate,studyTime);
        //最后加入的总在最前
        dirList.insert(0,dirBean);
    }else{
        qDebug()<<"DirListWidget::appendDirPath";
        qDebug()<<"It's not logically possible";
    }
}

//listWidget菜单中选项被点击时，会记录当前位置
void DirListWidget::listItemPressed(int index){
    this->index=index;
}

//listWidget菜单双击
void DirListWidget::listItemDoubleClicked(int index){
    emit showEditDialog(dirList[index]);
}

//第一个文件图标按钮的点击
void DirListWidget::iconButtonClicked(){
    emit showLoadDialog();
}

//第二个载入按钮的点击
void DirListWidget::loadButtonClicked(){
    if(index>0&&index<dirList.size()){
        emit loadThisPathData(dirList[index].getName(),dirList[index].getRealPath());
    }
}

//更新listWidget中数据
void DirListWidget::renewal(){
    listWidget->removeAllItems();
    listWidget->loadData(dirList);
    this->update();
}

//保存文件列表为json格式
void DirListWidget::saveDirList2JSON(){
    //接下来将dirList写成json格式，覆写到文件中
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator=document.GetAllocator();
    rapidjson::Value historyArray(rapidjson::kArrayType);
    //dirList中的数组，最前面的是最近打开的，所以存在最顶上
    for(int i=0;i<dirList.size();i++){
        rapidjson::Value bean(rapidjson::kObjectType);
        bean.AddMember("name",JsonUtils::CreateStringValue(dirList[i].getName().toStdString(),allocator),allocator);
        bean.AddMember("realPath",JsonUtils::CreateStringValue(dirList[i].getRealPath().toStdString(),allocator),allocator);
        bean.AddMember("studyDate",JsonUtils::CreateStringValue(dirList[i].getStudyDate().toStdString(),allocator),allocator);
        bean.AddMember("studyTime",JsonUtils::CreateStringValue(dirList[i].getStudyTime().toStdString(),allocator),allocator);
        historyArray.PushBack(bean,allocator);
    }
    document.AddMember("history",historyArray,allocator);
    JsonUtils::WriteStringToFile(DIRPATH_RESOURCE.toStdString(),JsonUtils::StringfyDocument(document));
}

void DirListWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
//    QPainter   painter(this);

 //   painter.drawRect(this->rect());
}
