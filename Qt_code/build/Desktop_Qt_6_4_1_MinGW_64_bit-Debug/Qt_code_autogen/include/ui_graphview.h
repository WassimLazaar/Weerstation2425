/********************************************************************************
** Form generated from reading UI file 'graphview.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHVIEW_H
#define UI_GRAPHVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GraphView
{
public:
    QFrame *horizontalFrame;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *GraphView)
    {
        if (GraphView->objectName().isEmpty())
            GraphView->setObjectName("GraphView");
        GraphView->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GraphView->sizePolicy().hasHeightForWidth());
        GraphView->setSizePolicy(sizePolicy);
        GraphView->setMinimumSize(QSize(800, 600));
        GraphView->setMaximumSize(QSize(800, 600));
        horizontalFrame = new QFrame(GraphView);
        horizontalFrame->setObjectName("horizontalFrame");
        horizontalFrame->setGeometry(QRect(10, 10, 781, 511));
        horizontalLayout = new QHBoxLayout(horizontalFrame);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(GraphView);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 550, 91, 29));
        label = new QLabel(GraphView);
        label->setObjectName("label");
        label->setGeometry(QRect(630, 540, 161, 20));
        label_2 = new QLabel(GraphView);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(630, 560, 151, 20));

        retranslateUi(GraphView);

        QMetaObject::connectSlotsByName(GraphView);
    } // setupUi

    void retranslateUi(QDialog *GraphView)
    {
        GraphView->setWindowTitle(QCoreApplication::translate("GraphView", "Grafiek View", nullptr));
        pushButton->setText(QCoreApplication::translate("GraphView", "reset zoom", nullptr));
        label->setText(QCoreApplication::translate("GraphView", "WASD om te bewegen", nullptr));
        label_2->setText(QCoreApplication::translate("GraphView", "+ en - om te zoomen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphView: public Ui_GraphView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHVIEW_H
