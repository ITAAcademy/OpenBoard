#ifndef SHADERTEST_H
#define SHADERTEST_H

#include <QDialog>
#include "editWidget/codeeditor.h"
namespace Ui {
class ShaderTest;
}

class ShaderTest : public QDialog
{
    Q_OBJECT

    bool status;
    CodeEditor fragmentTextEdit;
    CodeEditor vertexTextEdit;
public:

    explicit ShaderTest(QWidget *parent = 0);
    ~ShaderTest();
    QString getVertextValue();
    QString getFragmentValue();
    QString getLog();
    void setLog(QString str);

    bool getStatus() const;
    void setStatus(bool value);

signals:
    test();


private:
    Ui::ShaderTest *ui;
private slots:
    click();
};

#endif // SHADERTEST_H
