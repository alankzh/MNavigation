#include "dicominfowidget.h"

DicomInfoWidget::DicomInfoWidget(QWidget *parent):QWidget(parent)
{


    setMaximumWidth(200);
    setMinimumWidth(200);
    QSizePolicy sizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    setSizePolicy(sizePolicy);
    //������
    QVBoxLayout *mainLayout=new QVBoxLayout();
    title=new QLabel(QString::fromLocal8Bit("DCOM  ����"));
    title->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    title->setStyleSheet(QLABEL_LITTLE_TITLE_STYLE);
    title->setPalette(Constant::getCommanFontColor());
    title->setFont(Constant::get12FontSize());
    title->resize(200,26);
    title->setMaximumSize(200,26);
    title->setMinimumSize(200,26);
    title->setMargin(0);
    mainLayout->addWidget(title);

    //����������ǰ��ͼƬ
    QHBoxLayout *iconLayout=new QHBoxLayout();
    //�˰�ťֻ������ʾͼƬ��ר����һ���ؼ���ʾͼƬ���Ի����������ӦЧ��
    BackgroundButton *iconButton=new BackgroundButton();
    iconButton->setBackground(":/resources/pageSmall.png","png");
    iconButton->needClickEffect(false);
    patientName=new QLabel(QString::fromLocal8Bit(""));
    patientName->setFont(Constant::get18FontSize());
    patientName->setPalette(Constant::getCommanFontColor());
    patientName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    patientName->setStyleSheet(QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    iconLayout->addWidget(iconButton);
    iconLayout->addWidget(patientName);
    iconLayout->setContentsMargins(5,13,5,13);
    mainLayout->addLayout(iconLayout);

    //�����ձ�ͳ������ڵĲ���
    QHBoxLayout *sexAndAgeLayout=new QHBoxLayout();
    patientSex=new QLabel(QString::fromLocal8Bit("      "));
    patientSex->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    patientSex->setFont(Constant::get12FontSize());
    patientSex->setPalette(Constant::getLittleFontColor());
    patientSex->setStyleSheet( QLABEL_JUST_PADDING_LEFT_5PX);

    patientBirthday=new QLabel(QString::fromLocal8Bit(""));
    patientBirthday->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    patientBirthday->setFont(Constant::get12FontSize());
    patientBirthday->setPalette(Constant::getLittleFontColor());
//    patientBirthday->setStyleSheet( QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    sexAndAgeLayout->addWidget(getPreDescription(QString::fromLocal8Bit("�Ա�:")));
    sexAndAgeLayout->addWidget(patientSex);
    QLabel *agelabelInfo=new QLabel(QString::fromLocal8Bit("��������:"));
    agelabelInfo->setFont(Constant::get12FontSize());
    agelabelInfo->setPalette(Constant::getCommanFontColor());
    agelabelInfo->setStyleSheet(QLABEL_JUST_PADDING_LEFT_5PX);
    sexAndAgeLayout->addWidget(agelabelInfo);
    sexAndAgeLayout->addWidget(patientBirthday,1);
    sexAndAgeLayout->setContentsMargins(5,0,5,13);
    mainLayout->addLayout(sexAndAgeLayout);
    mainLayout->addWidget(getPartingLine());

    //�ļ���·��
    QHBoxLayout *dirPathLayout=new QHBoxLayout();
    dirPath=new QLabel(QString::fromLocal8Bit(""));
    dirPath->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    dirPath->setFont(Constant::get12FontSize());
    dirPath->setPalette(Constant::getLittleFontColor());
    dirPath->setStyleSheet(QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    dirPathLayout->addWidget(getPreDescription(QString::fromLocal8Bit("�ļ���·��:")));
    dirPathLayout->addWidget(dirPath,1);
    dirPathLayout->setContentsMargins(5,10,5,10);
    mainLayout->addLayout(dirPathLayout);
    mainLayout->addWidget(getPartingLine());

    //�������
    QHBoxLayout *studyDescriptionLayout=new QHBoxLayout();
    studyDescription=new QLabel(QString::fromLocal8Bit(""));
    studyDescription->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    studyDescription->setFont(Constant::get12FontSize());
    studyDescription->setPalette(Constant::getLittleFontColor());
    studyDescription->setStyleSheet(QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    studyDescriptionLayout->addWidget(getPreDescription(QString::fromLocal8Bit("�������:")));
    studyDescriptionLayout->addWidget(studyDescription,1);
    studyDescriptionLayout->setContentsMargins(5,10,5,10);
    mainLayout->addLayout(studyDescriptionLayout);
    mainLayout->addWidget(getPartingLine());

    //��������
    QHBoxLayout *seriesDescriptionLayout=new QHBoxLayout();
    seriesDescription=new QLabel(QString::fromLocal8Bit(""));
    seriesDescription->setFont(Constant::get12FontSize());
    seriesDescription->setPalette(Constant::getLittleFontColor());
    seriesDescription->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    seriesDescription->setStyleSheet(QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    seriesDescriptionLayout->addWidget(getPreDescription(QString::fromLocal8Bit("��������:")));
    seriesDescriptionLayout->addWidget(seriesDescription,1);
    seriesDescriptionLayout->setContentsMargins(5,10,5,10);
    mainLayout->addLayout(seriesDescriptionLayout);
    mainLayout->addWidget(getPartingLine());

    //����ID
    QHBoxLayout *studyIDLayout=new QHBoxLayout();
    studyID=new QLabel(QString::fromLocal8Bit(""));
    studyID->setFont(Constant::get12FontSize());
    studyID->setPalette(Constant::getLittleFontColor());
    studyID->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    studyID->setStyleSheet(QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    studyIDLayout->addWidget(getPreDescription(QString::fromLocal8Bit("����ID:")));
    studyIDLayout->addWidget(studyID,1);
    studyIDLayout->setContentsMargins(5,10,5,10);
    mainLayout->addLayout(studyIDLayout);
    mainLayout->addWidget(getPartingLine());

    //�������
    QHBoxLayout *studyDateLayout=new QHBoxLayout();
    studyDate=new QLabel(QString::fromLocal8Bit(""));
    studyDate->setFont(Constant::get12FontSize());
    studyDate->setPalette(Constant::getLittleFontColor());
    studyDate->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    studyDate->setStyleSheet(QLABEL_PADDING_LEFT_AND_RIGHT_5PX);
    studyDateLayout->addWidget(getPreDescription(QString::fromLocal8Bit("�������:")));
    studyDateLayout->addWidget(studyDate,1);
    studyDateLayout->setContentsMargins(5,10,5,10);
    mainLayout->addLayout(studyDateLayout);

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,15,0,15);
    this->setLayout(mainLayout);


}

//�������dicom��Ϣ��ʾ����
void DicomInfoWidget::setInfo(QString dPath){
    if(DicomLoader::HasData()){
       const DicomLoader::ResourceInfo *info=DicomLoader::GetDataInfo();
       if(!info->patient_name.empty()){
           patientName->setText(QString::fromStdString(info->patient_name));
       }
       if(!info->patient_sex.empty()){
             qDebug()<<QString::fromStdString(info->patient_sex);
            patientSex->setText(QString::fromStdString(info->patient_sex));
       }
       if(!info->patient_DOB.empty()){
           patientBirthday->setText(QString::fromStdString(info->patient_DOB));
       }
       if(!info->study_description.empty()){
           studyDescription->setText(QString::fromStdString(info->study_description));
       }
       if(!info->series_description.empty()){
           seriesDescription->setText(QString::fromStdString(info->series_description));
       }
       if(!info->study_ID.empty()){
          studyID->setText(QString::fromStdString(info->study_ID));
       }
       if(!info->study_date.empty()){
          studyDate->setText(QString::fromStdString(info->study_date));
       }
       dirPath->setText(dPath);

       setElidedText(patientName);
       setElidedText(patientSex);
       setElidedText(patientBirthday);
       setElidedText(dirPath);
       setElidedText(studyID);
       setElidedText(studyDate);
       setElidedText(studyDescription);
       setElidedText(seriesDescription);
    }else{

    }
}

//����һ���ָ���QLabel
QLabel* DicomInfoWidget::getPartingLine(){
    //�ָ���
    QLabel *partingLine=new QLabel();
    partingLine->setStyleSheet(
                "QLabel"
                "{"
                "background-color:#d9d9d9;"
                "margin-left:0px;"
                "margin-top:0px;"
                "margin-right:0px;"
                "margin-bottom:0px"
                "}"
                );
    partingLine->setMaximumHeight(1);
    return partingLine;
}

//����һ��label�������������Ϣ����������
QLabel* DicomInfoWidget::getPreDescription(QString info){
    QLabel *description=new QLabel(info);
    description->setFont(Constant::get12FontSize());
    description->setPalette(Constant::getCommanFontColor());
    return description;
}

//��ʡ�ԺŴ���̫�����ַ�
void DicomInfoWidget::setElidedText(QLabel *label)
{
    QFontMetrics fontWidth(label->font());
    QString hint=label->text();
    label->setToolTip(hint);
    int width = fontWidth.width(hint);  //�����ַ������
    if(width>=label->width()-10)  //���ַ�����ȴ��ڱ�ǩ���ʱ(���Ҽ���5px)
    {
        hint = fontWidth.elidedText(hint,Qt::ElideRight,label->width()-10);  //�Ҳ���ʾʡ�Ժ�
    }
    //����ֵ��QLabel
    label->setText(hint);
}

