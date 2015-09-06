#include "shadertest.h"
#include "ui_shadertest.h"


bool ShaderTest::getStatus() const
{
    return status;
}

void ShaderTest::setStatus(bool value)
{
    status = value;
    if(!status)
    {
        ui->progressBar->setStyleSheet(QString("QProgressBar::chunk {\
        background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,\
        stop: 0 #%1,\
        stop: 0.4999 #%2,\
        stop: 0.5 #%3,\
        stop: 1 #%4 );\
        border-bottom-right-radius: 7px;\
        border-bottom-left-radius: 7px;\
        border: 1px solid black;\
        }").arg("d00", "b00", "800", "700"));
            ui->log->setMaximumWidth(999);
            ui->log->setMinimumWidth(150);
    }
    else
    {
        ui->progressBar->setStyleSheet(QString("QProgressBar::chunk {\
        background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,\
        stop: 0 #%1,\
        stop: 0.4999 #%2,\
        stop: 0.5 #%3,\
        stop: 1 #%4 );\
        border-bottom-right-radius: 7px;\
        border-bottom-left-radius: 7px;\
        border: 1px solid black;\
        }").arg("0d0", "0b0", "080", "070"));
        ui->log->setMaximumWidth(20);
        ui->log->setMinimumWidth(20);
    }
    ui->progressBar->setValue(2);

}

ShaderTest::click()
{
       ui->progressBar->setValue(1);
       emit test();
}

ShaderTest::ShaderTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShaderTest)
{
    ui->setupUi(this);

    //connect(ui->commandLinkButton, SIGNAL(pressed()), this, SIGNAL(test()));
    ui->gridLayout_5->addWidget(&vertexTextEdit);
    ui->gridLayout_4->addWidget(&fragmentTextEdit);


    fragmentTextEdit.setPlainText("\
                                  uniform sampler2D textureSampler;\n\
                                  uniform float animationKey;\n\
                                  uniform bool reverse;\n\
                                  void main(void)\n\
                                  {\n\
                                      vec4 col = texture2D(textureSampler, vec2(gl_TexCoord[0]));\n\
                                      float alpha = animationKey;\n\
                                      if (reverse)alpha=1.0-alpha;\n\
                                      if (alpha>col.a)alpha=col.a;\n\
                                      gl_FragColor = vec4(col.rgb,alpha);\n\
                                  }\n\
");

      vertexTextEdit.setPlainText("\
                                  attribute vec4 qt_Vertex;\n\
                                  attribute vec4 qt_MultiTexCoord0;\n\
                                  \n\
                                  void main(void)\n\
                                  {\n\
                                      gl_Position = gl_ModelViewProjectionMatrix * qt_Vertex;\n\
                                      gl_TexCoord[0]=gl_MultiTexCoord0;\n\
                                  }\n\
");
    connect(ui->commandLinkButton, SIGNAL(pressed()), this, SLOT(click()));
    setStatus(true);
    ui->progressBar->setValue(0);
    setMinimumWidth(400);
}

ShaderTest::~ShaderTest()
{
    delete ui;
}

QString ShaderTest::getVertextValue()
{
    return vertexTextEdit.toPlainText();
}

QString ShaderTest::getFragmentValue()
{
    return fragmentTextEdit.toPlainText();
}

QString ShaderTest::getLog()
{
    return ui->log->toPlainText();
}

void ShaderTest::setLog(QString str)
{
    ui->log->setPlainText(str);
}
