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
    title=new QLabel(QString::fromLocal8Bit("���Ͽ�"));
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
    loadButton=new QPushButton(QString::fromLocal8Bit("����"));
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

//���û��༭���¼��ص�·�����浽json��ʽ
void DirListWidget::saveDirBean(QString name,QString realPath,QString studyDate,QString studyTime){
    qDebug()<<"DirListWidget::saveDirBean";
    int index=-1;
    //�鿴�Ƿ��·���Ѿ���������ʷ�б���
    for(int i=0;i<dirList.size();i++){
        if(realPath==dirList[i].getRealPath()){
            index=i;
        }
    }
    if(index!=-1){
        if(dirList[index].getName()!=name){
            //�û��༭�����ڱ�ʶ��
            //�����û��༭�иı��ʶ��
            dirList[index].setName(name);
            renewal();
        }else{
            //�û��������롱��ť���������������ļ�·��
            //TODO �����·���ö�
        }
    }else{
        //�߼�ѭ��������һ����˵�������û��´򿪵�·��
        //������·��
        DirBean bean(name,realPath,studyDate,studyTime);
        dirList.insert(0,bean);
        renewal();
    //    listView->selectOn(0);
    }
   saveDirList2JSON();
}

//���ر���·���µ�json��ʽ
void DirListWidget::loadPath(){
    rapidjson::Document document;
    JsonUtils::ResultCode info=JsonUtils::ParseFile(DIRPATH_RESOURCE.toStdString(),document);
    //���سɹ��������ɹ�
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
                    //json�ַ����У����������ʱ����Զ
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
        //�ļ�������
        qDebug()<<"FileIOException";
    }else if(info==JsonUtils::kParseError){
        //json��������
        qDebug()<<"JsonParseException";
    }
}

//���û��༭��new name���浽json��
void DirListWidget::saveItemChange(QString newName){
    qDebug()<<"DirListWidget::saveItemChange";
    QString name=dirList[index].getName();
    if(newName==name){
        //do nothing
        qDebug()<<"no change";
    }else{
        //TODO �û����޷��ٱ༭������ͨ���Ի���ص�
      //  saveDirBean(newName,dirList[index].getRealPath(),dirList[index].getStudyDate(),dirList[index].getStudyTime());
    }
}

//�����µ����������ʱ������listWidget��
void DirListWidget::popDirPath(QString path){
    if(DicomLoader::HasData()){
        QString name(QString::fromStdString(DicomLoader::GetDataInfo()->patient_name));
        QString studyDate(QString::fromStdString(DicomLoader::GetDataInfo()->study_date));
        QString studyTime(QString::fromStdString(DicomLoader::GetDataInfo()->study_time));
        DirBean dirBean(name,path,studyDate,studyTime);
        //�������������ǰ
        dirList.insert(0,dirBean);
    }else{
        qDebug()<<"DirListWidget::appendDirPath";
        qDebug()<<"It's not logically possible";
    }
}

//listWidget�˵���ѡ����ʱ�����¼��ǰλ��
void DirListWidget::listItemPressed(int index){
    this->index=index;
}

//listWidget�˵�˫��
void DirListWidget::listItemDoubleClicked(int index){
    emit showEditDialog(dirList[index]);
}

//��һ���ļ�ͼ�갴ť�ĵ��
void DirListWidget::iconButtonClicked(){
    emit showLoadDialog();
}

//�ڶ������밴ť�ĵ��
void DirListWidget::loadButtonClicked(){
    if(index>0&&index<dirList.size()){
        emit loadThisPathData(dirList[index].getName(),dirList[index].getRealPath());
    }
}

//����listWidget������
void DirListWidget::renewal(){
    listWidget->removeAllItems();
    listWidget->loadData(dirList);
    this->update();
}

//�����ļ��б�Ϊjson��ʽ
void DirListWidget::saveDirList2JSON(){
    //��������dirListд��json��ʽ����д���ļ���
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator=document.GetAllocator();
    rapidjson::Value historyArray(rapidjson::kArrayType);
    //dirList�е����飬��ǰ���������򿪵ģ����Դ������
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
