#include "emitbutton.h"

EmitButton::EmitButton(QString text,QWidget *parent):QRadioButton(parent)
{
    this->setText(text);
    connect(this,SIGNAL(toggled(bool)),this,SLOT(onSelfClicked(bool)));
}

void EmitButton::onSelfClicked(bool c){
    if(c&&isChecked()){
     emit sendText(this->text());
    }
}


