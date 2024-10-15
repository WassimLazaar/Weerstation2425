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
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GraphView
{
public:
    QFrame *horizontalFrame;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;

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
        horizontalFrame->setGeometry(QRect(10, 10, 781, 551));
        horizontalLayout = new QHBoxLayout(horizontalFrame);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(GraphView);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 570, 91, 29));

        retranslateUi(GraphView);

        QMetaObject::connectSlotsByName(GraphView);
    } // setupUi

    void retranslateUi(QDialog *GraphView)
    {
        GraphView->setWindowTitle(QCoreApplication::translate("GraphView", "Grafiek View", nullptr));
        pushButton->setText(QCoreApplication::translate("GraphView", "reset zoom", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphView: public Ui_GraphView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHVIEW_H
