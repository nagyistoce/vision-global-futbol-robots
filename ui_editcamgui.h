/********************************************************************************
** Form generated from reading UI file 'editcamgui.ui'
**
** Created: Mon Oct 17 23:27:22 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCAMGUI_H
#define UI_EDITCAMGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editCamGUI
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QSpinBox *spinBoxCamaraIndex;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBoxCamaraType;
    QComboBox *comboBoxCamaraResolution;
    QWidget *widget;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_4;
    QPlainTextEdit *plainTextEdit;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonIntrinsics;
    QPushButton *pushButtonDistortion;
    QPushButton *pushButtonExtrinsics;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonApply;
    QPushButton *pushButtonClear;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayoutFrame;
    QLabel *imageLabel;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonConfiguration;

    void setupUi(QWidget *editCamGUI)
    {
        if (editCamGUI->objectName().isEmpty())
            editCamGUI->setObjectName(QString::fromUtf8("editCamGUI"));
        editCamGUI->resize(1109, 560);
        verticalLayoutWidget = new QWidget(editCamGUI);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 30, 401, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 30, 351, 171));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        spinBoxCamaraIndex = new QSpinBox(tab);
        spinBoxCamaraIndex->setObjectName(QString::fromUtf8("spinBoxCamaraIndex"));
        spinBoxCamaraIndex->setGeometry(QRect(120, 10, 141, 27));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 98, 17));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 84, 17));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 100, 74, 17));
        comboBoxCamaraType = new QComboBox(tab);
        comboBoxCamaraType->setObjectName(QString::fromUtf8("comboBoxCamaraType"));
        comboBoxCamaraType->setGeometry(QRect(120, 50, 211, 31));
        comboBoxCamaraResolution = new QComboBox(tab);
        comboBoxCamaraResolution->setObjectName(QString::fromUtf8("comboBoxCamaraResolution"));
        comboBoxCamaraResolution->setGeometry(QRect(120, 90, 141, 31));
        tabWidget->addTab(tab, QString());
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setEnabled(true);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        widget->setFont(font);
        tabWidget->addTab(widget, QString());

        verticalLayout->addWidget(groupBox);

        verticalLayoutWidget_4 = new QWidget(editCamGUI);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(20, 420, 401, 121));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(verticalLayoutWidget_4);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setEnabled(false);
        plainTextEdit = new QPlainTextEdit(groupBox_4);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 20, 371, 91));

        verticalLayout_4->addWidget(groupBox_4);

        verticalLayoutWidget_2 = new QWidget(editCamGUI);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 280, 401, 131));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(verticalLayoutWidget_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        widget1 = new QWidget(groupBox_2);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(20, 40, 341, 29));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonIntrinsics = new QPushButton(widget1);
        pushButtonIntrinsics->setObjectName(QString::fromUtf8("pushButtonIntrinsics"));

        horizontalLayout->addWidget(pushButtonIntrinsics);

        pushButtonDistortion = new QPushButton(widget1);
        pushButtonDistortion->setObjectName(QString::fromUtf8("pushButtonDistortion"));

        horizontalLayout->addWidget(pushButtonDistortion);

        pushButtonExtrinsics = new QPushButton(widget1);
        pushButtonExtrinsics->setObjectName(QString::fromUtf8("pushButtonExtrinsics"));
        pushButtonExtrinsics->setEnabled(false);

        horizontalLayout->addWidget(pushButtonExtrinsics);

        widget2 = new QWidget(groupBox_2);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(70, 90, 221, 29));
        horizontalLayout_2 = new QHBoxLayout(widget2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButtonApply = new QPushButton(widget2);
        pushButtonApply->setObjectName(QString::fromUtf8("pushButtonApply"));

        horizontalLayout_2->addWidget(pushButtonApply);

        pushButtonClear = new QPushButton(widget2);
        pushButtonClear->setObjectName(QString::fromUtf8("pushButtonClear"));

        horizontalLayout_2->addWidget(pushButtonClear);


        verticalLayout_2->addWidget(groupBox_2);

        verticalLayoutWidget_5 = new QWidget(editCamGUI);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(440, 80, 651, 461));
        verticalLayoutFrame = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayoutFrame->setObjectName(QString::fromUtf8("verticalLayoutFrame"));
        verticalLayoutFrame->setContentsMargins(0, 0, 0, 0);
        imageLabel = new QLabel(verticalLayoutWidget_5);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));

        verticalLayoutFrame->addWidget(imageLabel);

        pushButtonStart = new QPushButton(editCamGUI);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        pushButtonStart->setGeometry(QRect(450, 40, 93, 27));
        pushButtonStop = new QPushButton(editCamGUI);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setGeometry(QRect(580, 40, 93, 27));
        pushButtonConfiguration = new QPushButton(editCamGUI);
        pushButtonConfiguration->setObjectName(QString::fromUtf8("pushButtonConfiguration"));
        pushButtonConfiguration->setGeometry(QRect(890, 40, 171, 27));

        retranslateUi(editCamGUI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(editCamGUI);
    } // setupUi

    void retranslateUi(QWidget *editCamGUI)
    {
        editCamGUI->setWindowTitle(QApplication::translate("editCamGUI", "Configuraci\303\263n de C\303\241mara 1", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("editCamGUI", "Seleccionar C\303\241mara", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("editCamGUI", "C\303\241mara \303\255ndice:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("editCamGUI", "C\303\241mara tipo:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("editCamGUI", "Resoluci\303\263n:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("editCamGUI", "C\303\241mara (OpenCV)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(widget), QApplication::translate("editCamGUI", "C\303\241mara (FFmpeg)", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("editCamGUI", "Log", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("editCamGUI", "Cargar Archivos", 0, QApplication::UnicodeUTF8));
        pushButtonIntrinsics->setText(QApplication::translate("editCamGUI", "P. Intr\303\255nsecos", 0, QApplication::UnicodeUTF8));
        pushButtonDistortion->setText(QApplication::translate("editCamGUI", "C. Distonrsi\303\263n", 0, QApplication::UnicodeUTF8));
        pushButtonExtrinsics->setText(QApplication::translate("editCamGUI", "P. Extr\303\255nsecos", 0, QApplication::UnicodeUTF8));
        pushButtonApply->setText(QApplication::translate("editCamGUI", "Aplicar", 0, QApplication::UnicodeUTF8));
        pushButtonClear->setText(QApplication::translate("editCamGUI", "Limpiar", 0, QApplication::UnicodeUTF8));
        imageLabel->setText(QString());
        pushButtonStart->setText(QApplication::translate("editCamGUI", "Start", 0, QApplication::UnicodeUTF8));
        pushButtonStop->setText(QApplication::translate("editCamGUI", "Stop", 0, QApplication::UnicodeUTF8));
        pushButtonConfiguration->setText(QApplication::translate("editCamGUI", "Guardar Configuraci\303\263n", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class editCamGUI: public Ui_editCamGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCAMGUI_H
