/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *centralLayout;
    QStackedWidget *stackedWidget;
    QWidget *homePage;
    QVBoxLayout *homeLayout;
    QLabel *homeTitleLabel;
    QSpacerItem *homeTopSpacer;
    QPushButton *newEmployeeButton;
    QSpacerItem *homeMidSpacer;
    QPushButton *employeeManagementButton;
    QSpacerItem *homeManagementSpacer;
    QPushButton *accessLogButton;
    QSpacerItem *homeLogSpacer;
    QPushButton *accessButton;
    QSpacerItem *homeBottomSpacer;
    QWidget *employeePage;
    QVBoxLayout *employeePageLayout;
    QHBoxLayout *employeeHeaderLayout;
    QPushButton *employeeBackButton;
    QLabel *employeeTitleLabel;
    QSpacerItem *employeeHeaderSpacer;
    QHBoxLayout *employeeContentLayout;
    QGroupBox *employeeInfoGroup;
    QFormLayout *employeeFormLayout;
    QLabel *employeeNoLabel;
    QLineEdit *employeeNoEdit;
    QLabel *employeeNameLabel;
    QLineEdit *employeeNameEdit;
    QLabel *departmentLabel;
    QComboBox *departmentCombo;
    QLabel *positionLabel;
    QComboBox *positionCombo;
    QLabel *phoneLabel;
    QLineEdit *phoneEdit;
    QLabel *employeeAccessLabel;
    QWidget *employeeAccessWidget;
    QVBoxLayout *employeeAccessLayout;
    QCheckBox *pharmacyPermissionCheck;
    QCheckBox *doctorOfficePermissionCheck;
    QCheckBox *warehousePermissionCheck;
    QGroupBox *employeeFaceGroup;
    QVBoxLayout *employeeFaceLayout;
    QLabel *employeeFaceLabel;
    QLabel *employeeFeatureLabel;
    QHBoxLayout *employeeFaceButtonsLayout;
    QPushButton *employeeCameraButton;
    QPushButton *employeeImageButton;
    QPushButton *saveEmployeeButton;
    QWidget *employeeManagementPage;
    QVBoxLayout *employeeManagementLayout;
    QHBoxLayout *managementHeaderLayout;
    QPushButton *managementBackButton;
    QLabel *managementTitleLabel;
    QSpacerItem *managementHeaderSpacer;
    QHBoxLayout *managementFilterLayout;
    QLabel *departmentFilterLabel;
    QComboBox *departmentFilterCombo;
    QLabel *positionFilterLabel;
    QComboBox *positionFilterCombo;
    QLabel *statusFilterLabel;
    QComboBox *statusFilterCombo;
    QPushButton *queryEmployeeButton;
    QPushButton *resetEmployeeButton;
    QTableWidget *employeeTable;
    QHBoxLayout *managementButtonsLayout;
    QSpacerItem *managementButtonsSpacer;
    QPushButton *editEmployeeButton;
    QPushButton *disableEmployeeButton;
    QPushButton *deleteEmployeeButton;
    QWidget *accessLogPage;
    QVBoxLayout *accessLogPageLayout;
    QHBoxLayout *accessLogHeaderLayout;
    QPushButton *accessLogBackButton;
    QLabel *accessLogTitleLabel;
    QSpacerItem *accessLogHeaderSpacer;
    QHBoxLayout *accessLogFilterLayout;
    QLabel *logAreaLabel;
    QComboBox *logAreaCombo;
    QLabel *logResultLabel;
    QComboBox *logResultCombo;
    QPushButton *queryLogButton;
    QPushButton *resetLogButton;
    QSpacerItem *accessLogFilterSpacer;
    QTableWidget *accessLogTable;
    QWidget *accessPage;
    QVBoxLayout *accessPageLayout;
    QHBoxLayout *accessHeaderLayout;
    QPushButton *accessBackButton;
    QLabel *accessTitleLabel;
    QSpacerItem *accessHeaderSpacer;
    QHBoxLayout *accessAreaLayout;
    QSpacerItem *accessAreaLeftSpacer;
    QLabel *accessAreaLabel;
    QComboBox *accessAreaCombo;
    QSpacerItem *accessAreaRightSpacer;
    QLabel *accessHintLabel;
    QLabel *accessFaceLabel;
    QLabel *accessResultLabel;
    QHBoxLayout *accessButtonsLayout;
    QPushButton *accessCameraButton;
    QPushButton *accessImageButton;
    QPushButton *accessFileButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 669);
        MainWindow->setMinimumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralLayout = new QVBoxLayout(centralwidget);
        centralLayout->setObjectName("centralLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        homePage = new QWidget();
        homePage->setObjectName("homePage");
        homeLayout = new QVBoxLayout(homePage);
        homeLayout->setObjectName("homeLayout");
        homeLayout->setContentsMargins(110, 80, 110, 100);
        homeTitleLabel = new QLabel(homePage);
        homeTitleLabel->setObjectName("homeTitleLabel");
        QFont font;
        font.setPointSize(24);
        font.setBold(true);
        homeTitleLabel->setFont(font);
        homeTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        homeLayout->addWidget(homeTitleLabel);

        homeTopSpacer = new QSpacerItem(20, 60, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        homeLayout->addItem(homeTopSpacer);

        newEmployeeButton = new QPushButton(homePage);
        newEmployeeButton->setObjectName("newEmployeeButton");
        newEmployeeButton->setMinimumSize(QSize(0, 90));
        QFont font1;
        font1.setPointSize(18);
        newEmployeeButton->setFont(font1);

        homeLayout->addWidget(newEmployeeButton);

        homeMidSpacer = new QSpacerItem(20, 35, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        homeLayout->addItem(homeMidSpacer);

        employeeManagementButton = new QPushButton(homePage);
        employeeManagementButton->setObjectName("employeeManagementButton");
        employeeManagementButton->setMinimumSize(QSize(0, 90));
        employeeManagementButton->setFont(font1);

        homeLayout->addWidget(employeeManagementButton);

        homeManagementSpacer = new QSpacerItem(20, 35, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        homeLayout->addItem(homeManagementSpacer);

        accessLogButton = new QPushButton(homePage);
        accessLogButton->setObjectName("accessLogButton");
        accessLogButton->setMinimumSize(QSize(0, 90));
        accessLogButton->setFont(font1);

        homeLayout->addWidget(accessLogButton);

        homeLogSpacer = new QSpacerItem(20, 35, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        homeLayout->addItem(homeLogSpacer);

        accessButton = new QPushButton(homePage);
        accessButton->setObjectName("accessButton");
        accessButton->setMinimumSize(QSize(0, 90));
        accessButton->setFont(font1);

        homeLayout->addWidget(accessButton);

        homeBottomSpacer = new QSpacerItem(20, 60, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        homeLayout->addItem(homeBottomSpacer);

        stackedWidget->addWidget(homePage);
        employeePage = new QWidget();
        employeePage->setObjectName("employeePage");
        employeePageLayout = new QVBoxLayout(employeePage);
        employeePageLayout->setObjectName("employeePageLayout");
        employeeHeaderLayout = new QHBoxLayout();
        employeeHeaderLayout->setObjectName("employeeHeaderLayout");
        employeeBackButton = new QPushButton(employeePage);
        employeeBackButton->setObjectName("employeeBackButton");

        employeeHeaderLayout->addWidget(employeeBackButton);

        employeeTitleLabel = new QLabel(employeePage);
        employeeTitleLabel->setObjectName("employeeTitleLabel");
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        employeeTitleLabel->setFont(font2);
        employeeTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        employeeHeaderLayout->addWidget(employeeTitleLabel);

        employeeHeaderSpacer = new QSpacerItem(80, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        employeeHeaderLayout->addItem(employeeHeaderSpacer);


        employeePageLayout->addLayout(employeeHeaderLayout);

        employeeContentLayout = new QHBoxLayout();
        employeeContentLayout->setObjectName("employeeContentLayout");
        employeeInfoGroup = new QGroupBox(employeePage);
        employeeInfoGroup->setObjectName("employeeInfoGroup");
        employeeFormLayout = new QFormLayout(employeeInfoGroup);
        employeeFormLayout->setObjectName("employeeFormLayout");
        employeeFormLayout->setHorizontalSpacing(20);
        employeeFormLayout->setVerticalSpacing(20);
        employeeNoLabel = new QLabel(employeeInfoGroup);
        employeeNoLabel->setObjectName("employeeNoLabel");

        employeeFormLayout->setWidget(0, QFormLayout::LabelRole, employeeNoLabel);

        employeeNoEdit = new QLineEdit(employeeInfoGroup);
        employeeNoEdit->setObjectName("employeeNoEdit");

        employeeFormLayout->setWidget(0, QFormLayout::FieldRole, employeeNoEdit);

        employeeNameLabel = new QLabel(employeeInfoGroup);
        employeeNameLabel->setObjectName("employeeNameLabel");

        employeeFormLayout->setWidget(1, QFormLayout::LabelRole, employeeNameLabel);

        employeeNameEdit = new QLineEdit(employeeInfoGroup);
        employeeNameEdit->setObjectName("employeeNameEdit");

        employeeFormLayout->setWidget(1, QFormLayout::FieldRole, employeeNameEdit);

        departmentLabel = new QLabel(employeeInfoGroup);
        departmentLabel->setObjectName("departmentLabel");

        employeeFormLayout->setWidget(2, QFormLayout::LabelRole, departmentLabel);

        departmentCombo = new QComboBox(employeeInfoGroup);
        departmentCombo->setObjectName("departmentCombo");

        employeeFormLayout->setWidget(2, QFormLayout::FieldRole, departmentCombo);

        positionLabel = new QLabel(employeeInfoGroup);
        positionLabel->setObjectName("positionLabel");

        employeeFormLayout->setWidget(3, QFormLayout::LabelRole, positionLabel);

        positionCombo = new QComboBox(employeeInfoGroup);
        positionCombo->setObjectName("positionCombo");

        employeeFormLayout->setWidget(3, QFormLayout::FieldRole, positionCombo);

        phoneLabel = new QLabel(employeeInfoGroup);
        phoneLabel->setObjectName("phoneLabel");

        employeeFormLayout->setWidget(4, QFormLayout::LabelRole, phoneLabel);

        phoneEdit = new QLineEdit(employeeInfoGroup);
        phoneEdit->setObjectName("phoneEdit");

        employeeFormLayout->setWidget(4, QFormLayout::FieldRole, phoneEdit);

        employeeAccessLabel = new QLabel(employeeInfoGroup);
        employeeAccessLabel->setObjectName("employeeAccessLabel");

        employeeFormLayout->setWidget(5, QFormLayout::LabelRole, employeeAccessLabel);

        employeeAccessWidget = new QWidget(employeeInfoGroup);
        employeeAccessWidget->setObjectName("employeeAccessWidget");
        employeeAccessLayout = new QVBoxLayout(employeeAccessWidget);
        employeeAccessLayout->setObjectName("employeeAccessLayout");
        employeeAccessLayout->setContentsMargins(0, 0, 0, 0);
        pharmacyPermissionCheck = new QCheckBox(employeeAccessWidget);
        pharmacyPermissionCheck->setObjectName("pharmacyPermissionCheck");

        employeeAccessLayout->addWidget(pharmacyPermissionCheck);

        doctorOfficePermissionCheck = new QCheckBox(employeeAccessWidget);
        doctorOfficePermissionCheck->setObjectName("doctorOfficePermissionCheck");

        employeeAccessLayout->addWidget(doctorOfficePermissionCheck);

        warehousePermissionCheck = new QCheckBox(employeeAccessWidget);
        warehousePermissionCheck->setObjectName("warehousePermissionCheck");

        employeeAccessLayout->addWidget(warehousePermissionCheck);


        employeeFormLayout->setWidget(5, QFormLayout::FieldRole, employeeAccessWidget);


        employeeContentLayout->addWidget(employeeInfoGroup);

        employeeFaceGroup = new QGroupBox(employeePage);
        employeeFaceGroup->setObjectName("employeeFaceGroup");
        employeeFaceLayout = new QVBoxLayout(employeeFaceGroup);
        employeeFaceLayout->setObjectName("employeeFaceLayout");
        employeeFaceLabel = new QLabel(employeeFaceGroup);
        employeeFaceLabel->setObjectName("employeeFaceLabel");
        employeeFaceLabel->setMinimumSize(QSize(360, 320));
        employeeFaceLabel->setFrameShape(QFrame::Shape::Box);
        employeeFaceLabel->setScaledContents(true);
        employeeFaceLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        employeeFaceLayout->addWidget(employeeFaceLabel);

        employeeFeatureLabel = new QLabel(employeeFaceGroup);
        employeeFeatureLabel->setObjectName("employeeFeatureLabel");
        employeeFeatureLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        employeeFaceLayout->addWidget(employeeFeatureLabel);

        employeeFaceButtonsLayout = new QHBoxLayout();
        employeeFaceButtonsLayout->setObjectName("employeeFaceButtonsLayout");
        employeeCameraButton = new QPushButton(employeeFaceGroup);
        employeeCameraButton->setObjectName("employeeCameraButton");

        employeeFaceButtonsLayout->addWidget(employeeCameraButton);

        employeeImageButton = new QPushButton(employeeFaceGroup);
        employeeImageButton->setObjectName("employeeImageButton");

        employeeFaceButtonsLayout->addWidget(employeeImageButton);


        employeeFaceLayout->addLayout(employeeFaceButtonsLayout);


        employeeContentLayout->addWidget(employeeFaceGroup);


        employeePageLayout->addLayout(employeeContentLayout);

        saveEmployeeButton = new QPushButton(employeePage);
        saveEmployeeButton->setObjectName("saveEmployeeButton");
        saveEmployeeButton->setMinimumSize(QSize(0, 46));
        QFont font3;
        font3.setPointSize(13);
        font3.setBold(true);
        saveEmployeeButton->setFont(font3);

        employeePageLayout->addWidget(saveEmployeeButton);

        stackedWidget->addWidget(employeePage);
        employeeManagementPage = new QWidget();
        employeeManagementPage->setObjectName("employeeManagementPage");
        employeeManagementLayout = new QVBoxLayout(employeeManagementPage);
        employeeManagementLayout->setObjectName("employeeManagementLayout");
        managementHeaderLayout = new QHBoxLayout();
        managementHeaderLayout->setObjectName("managementHeaderLayout");
        managementBackButton = new QPushButton(employeeManagementPage);
        managementBackButton->setObjectName("managementBackButton");

        managementHeaderLayout->addWidget(managementBackButton);

        managementTitleLabel = new QLabel(employeeManagementPage);
        managementTitleLabel->setObjectName("managementTitleLabel");
        managementTitleLabel->setFont(font2);
        managementTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        managementHeaderLayout->addWidget(managementTitleLabel);

        managementHeaderSpacer = new QSpacerItem(80, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        managementHeaderLayout->addItem(managementHeaderSpacer);


        employeeManagementLayout->addLayout(managementHeaderLayout);

        managementFilterLayout = new QHBoxLayout();
        managementFilterLayout->setObjectName("managementFilterLayout");
        departmentFilterLabel = new QLabel(employeeManagementPage);
        departmentFilterLabel->setObjectName("departmentFilterLabel");

        managementFilterLayout->addWidget(departmentFilterLabel);

        departmentFilterCombo = new QComboBox(employeeManagementPage);
        departmentFilterCombo->setObjectName("departmentFilterCombo");

        managementFilterLayout->addWidget(departmentFilterCombo);

        positionFilterLabel = new QLabel(employeeManagementPage);
        positionFilterLabel->setObjectName("positionFilterLabel");

        managementFilterLayout->addWidget(positionFilterLabel);

        positionFilterCombo = new QComboBox(employeeManagementPage);
        positionFilterCombo->setObjectName("positionFilterCombo");

        managementFilterLayout->addWidget(positionFilterCombo);

        statusFilterLabel = new QLabel(employeeManagementPage);
        statusFilterLabel->setObjectName("statusFilterLabel");

        managementFilterLayout->addWidget(statusFilterLabel);

        statusFilterCombo = new QComboBox(employeeManagementPage);
        statusFilterCombo->setObjectName("statusFilterCombo");

        managementFilterLayout->addWidget(statusFilterCombo);

        queryEmployeeButton = new QPushButton(employeeManagementPage);
        queryEmployeeButton->setObjectName("queryEmployeeButton");

        managementFilterLayout->addWidget(queryEmployeeButton);

        resetEmployeeButton = new QPushButton(employeeManagementPage);
        resetEmployeeButton->setObjectName("resetEmployeeButton");

        managementFilterLayout->addWidget(resetEmployeeButton);


        employeeManagementLayout->addLayout(managementFilterLayout);

        employeeTable = new QTableWidget(employeeManagementPage);
        if (employeeTable->columnCount() < 7)
            employeeTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        employeeTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        employeeTable->setObjectName("employeeTable");
        employeeTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        employeeTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        employeeTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        employeeTable->setAlternatingRowColors(true);
        employeeTable->setColumnCount(7);

        employeeManagementLayout->addWidget(employeeTable);

        managementButtonsLayout = new QHBoxLayout();
        managementButtonsLayout->setObjectName("managementButtonsLayout");
        managementButtonsSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        managementButtonsLayout->addItem(managementButtonsSpacer);

        editEmployeeButton = new QPushButton(employeeManagementPage);
        editEmployeeButton->setObjectName("editEmployeeButton");
        editEmployeeButton->setMinimumSize(QSize(120, 38));

        managementButtonsLayout->addWidget(editEmployeeButton);

        disableEmployeeButton = new QPushButton(employeeManagementPage);
        disableEmployeeButton->setObjectName("disableEmployeeButton");
        disableEmployeeButton->setMinimumSize(QSize(120, 38));

        managementButtonsLayout->addWidget(disableEmployeeButton);

        deleteEmployeeButton = new QPushButton(employeeManagementPage);
        deleteEmployeeButton->setObjectName("deleteEmployeeButton");
        deleteEmployeeButton->setMinimumSize(QSize(120, 38));

        managementButtonsLayout->addWidget(deleteEmployeeButton);


        employeeManagementLayout->addLayout(managementButtonsLayout);

        stackedWidget->addWidget(employeeManagementPage);
        accessLogPage = new QWidget();
        accessLogPage->setObjectName("accessLogPage");
        accessLogPageLayout = new QVBoxLayout(accessLogPage);
        accessLogPageLayout->setObjectName("accessLogPageLayout");
        accessLogHeaderLayout = new QHBoxLayout();
        accessLogHeaderLayout->setObjectName("accessLogHeaderLayout");
        accessLogBackButton = new QPushButton(accessLogPage);
        accessLogBackButton->setObjectName("accessLogBackButton");

        accessLogHeaderLayout->addWidget(accessLogBackButton);

        accessLogTitleLabel = new QLabel(accessLogPage);
        accessLogTitleLabel->setObjectName("accessLogTitleLabel");
        accessLogTitleLabel->setFont(font2);
        accessLogTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        accessLogHeaderLayout->addWidget(accessLogTitleLabel);

        accessLogHeaderSpacer = new QSpacerItem(80, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        accessLogHeaderLayout->addItem(accessLogHeaderSpacer);


        accessLogPageLayout->addLayout(accessLogHeaderLayout);

        accessLogFilterLayout = new QHBoxLayout();
        accessLogFilterLayout->setObjectName("accessLogFilterLayout");
        logAreaLabel = new QLabel(accessLogPage);
        logAreaLabel->setObjectName("logAreaLabel");

        accessLogFilterLayout->addWidget(logAreaLabel);

        logAreaCombo = new QComboBox(accessLogPage);
        logAreaCombo->addItem(QString());
        logAreaCombo->addItem(QString());
        logAreaCombo->addItem(QString());
        logAreaCombo->addItem(QString());
        logAreaCombo->setObjectName("logAreaCombo");

        accessLogFilterLayout->addWidget(logAreaCombo);

        logResultLabel = new QLabel(accessLogPage);
        logResultLabel->setObjectName("logResultLabel");

        accessLogFilterLayout->addWidget(logResultLabel);

        logResultCombo = new QComboBox(accessLogPage);
        logResultCombo->addItem(QString());
        logResultCombo->addItem(QString());
        logResultCombo->addItem(QString());
        logResultCombo->addItem(QString());
        logResultCombo->setObjectName("logResultCombo");

        accessLogFilterLayout->addWidget(logResultCombo);

        queryLogButton = new QPushButton(accessLogPage);
        queryLogButton->setObjectName("queryLogButton");

        accessLogFilterLayout->addWidget(queryLogButton);

        resetLogButton = new QPushButton(accessLogPage);
        resetLogButton->setObjectName("resetLogButton");

        accessLogFilterLayout->addWidget(resetLogButton);

        accessLogFilterSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        accessLogFilterLayout->addItem(accessLogFilterSpacer);


        accessLogPageLayout->addLayout(accessLogFilterLayout);

        accessLogTable = new QTableWidget(accessLogPage);
        if (accessLogTable->columnCount() < 6)
            accessLogTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        accessLogTable->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        accessLogTable->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        accessLogTable->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        accessLogTable->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        accessLogTable->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        accessLogTable->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        accessLogTable->setObjectName("accessLogTable");
        accessLogTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        accessLogTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        accessLogTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        accessLogTable->setAlternatingRowColors(true);
        accessLogTable->setColumnCount(6);

        accessLogPageLayout->addWidget(accessLogTable);

        stackedWidget->addWidget(accessLogPage);
        accessPage = new QWidget();
        accessPage->setObjectName("accessPage");
        accessPageLayout = new QVBoxLayout(accessPage);
        accessPageLayout->setObjectName("accessPageLayout");
        accessHeaderLayout = new QHBoxLayout();
        accessHeaderLayout->setObjectName("accessHeaderLayout");
        accessBackButton = new QPushButton(accessPage);
        accessBackButton->setObjectName("accessBackButton");

        accessHeaderLayout->addWidget(accessBackButton);

        accessTitleLabel = new QLabel(accessPage);
        accessTitleLabel->setObjectName("accessTitleLabel");
        accessTitleLabel->setFont(font2);
        accessTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        accessHeaderLayout->addWidget(accessTitleLabel);

        accessHeaderSpacer = new QSpacerItem(80, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        accessHeaderLayout->addItem(accessHeaderSpacer);


        accessPageLayout->addLayout(accessHeaderLayout);

        accessAreaLayout = new QHBoxLayout();
        accessAreaLayout->setObjectName("accessAreaLayout");
        accessAreaLeftSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        accessAreaLayout->addItem(accessAreaLeftSpacer);

        accessAreaLabel = new QLabel(accessPage);
        accessAreaLabel->setObjectName("accessAreaLabel");

        accessAreaLayout->addWidget(accessAreaLabel);

        accessAreaCombo = new QComboBox(accessPage);
        accessAreaCombo->addItem(QString());
        accessAreaCombo->addItem(QString());
        accessAreaCombo->addItem(QString());
        accessAreaCombo->setObjectName("accessAreaCombo");

        accessAreaLayout->addWidget(accessAreaCombo);

        accessAreaRightSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        accessAreaLayout->addItem(accessAreaRightSpacer);


        accessPageLayout->addLayout(accessAreaLayout);

        accessHintLabel = new QLabel(accessPage);
        accessHintLabel->setObjectName("accessHintLabel");
        accessHintLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        accessPageLayout->addWidget(accessHintLabel);

        accessFaceLabel = new QLabel(accessPage);
        accessFaceLabel->setObjectName("accessFaceLabel");
        accessFaceLabel->setMinimumSize(QSize(520, 390));
        accessFaceLabel->setMaximumSize(QSize(650, 16777215));
        accessFaceLabel->setFrameShape(QFrame::Shape::Box);
        accessFaceLabel->setScaledContents(true);
        accessFaceLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        accessPageLayout->addWidget(accessFaceLabel);

        accessResultLabel = new QLabel(accessPage);
        accessResultLabel->setObjectName("accessResultLabel");
        accessResultLabel->setMinimumSize(QSize(0, 76));
        accessResultLabel->setWordWrap(true);
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        accessResultLabel->setFont(font4);
        accessResultLabel->setFrameShape(QFrame::Shape::StyledPanel);
        accessResultLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        accessPageLayout->addWidget(accessResultLabel);

        accessButtonsLayout = new QHBoxLayout();
        accessButtonsLayout->setObjectName("accessButtonsLayout");
        accessCameraButton = new QPushButton(accessPage);
        accessCameraButton->setObjectName("accessCameraButton");
        accessCameraButton->setMinimumSize(QSize(0, 42));

        accessButtonsLayout->addWidget(accessCameraButton);

        accessImageButton = new QPushButton(accessPage);
        accessImageButton->setObjectName("accessImageButton");
        accessImageButton->setMinimumSize(QSize(0, 42));

        accessButtonsLayout->addWidget(accessImageButton);

        accessFileButton = new QPushButton(accessPage);
        accessFileButton->setObjectName("accessFileButton");
        accessFileButton->setMinimumSize(QSize(0, 42));

        accessButtonsLayout->addWidget(accessFileButton);


        accessPageLayout->addLayout(accessButtonsLayout);

        stackedWidget->addWidget(accessPage);

        centralLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\214\273\351\231\242\351\227\250\347\246\201\344\272\272\350\204\270\350\257\206\345\210\253\347\263\273\347\273\237", nullptr));
        homeTitleLabel->setText(QCoreApplication::translate("MainWindow", "\345\214\273\351\231\242\345\221\230\345\267\245\351\227\250\347\246\201\347\256\241\347\220\206", nullptr));
        newEmployeeButton->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\221\230\345\267\245", nullptr));
        employeeManagementButton->setText(QCoreApplication::translate("MainWindow", "\345\221\230\345\267\245\346\241\243\346\241\210\347\256\241\347\220\206", nullptr));
        accessLogButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\351\227\250\347\246\201\350\256\277\351\227\256\346\227\245\345\277\227", nullptr));
        accessButton->setText(QCoreApplication::translate("MainWindow", "\351\227\250\347\246\201\344\272\272\350\204\270\350\257\206\345\210\253", nullptr));
        employeeBackButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\351\241\265", nullptr));
        employeeTitleLabel->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\345\221\230\345\267\245", nullptr));
        employeeInfoGroup->setTitle(QCoreApplication::translate("MainWindow", "\345\221\230\345\267\245\345\237\272\347\241\200\344\277\241\346\201\257", nullptr));
        employeeNoLabel->setText(QCoreApplication::translate("MainWindow", "\345\267\245\345\217\267 *", nullptr));
        employeeNoEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\224\257\344\270\200\345\267\245\345\217\267", nullptr));
        employeeNameLabel->setText(QCoreApplication::translate("MainWindow", "\345\247\223\345\220\215 *", nullptr));
        employeeNameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\247\223\345\220\215", nullptr));
        departmentLabel->setText(QCoreApplication::translate("MainWindow", "\347\247\221\345\256\244", nullptr));
        positionLabel->setText(QCoreApplication::translate("MainWindow", "\345\262\227\344\275\215", nullptr));
        phoneLabel->setText(QCoreApplication::translate("MainWindow", "\350\201\224\347\263\273\347\224\265\350\257\235 *", nullptr));
        phoneEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\350\201\224\347\263\273\347\224\265\350\257\235", nullptr));
        employeeAccessLabel->setText(QCoreApplication::translate("MainWindow", "\345\214\272\345\237\237\346\235\203\351\231\220", nullptr));
        pharmacyPermissionCheck->setText(QCoreApplication::translate("MainWindow", "\350\215\257\346\210\277", nullptr));
        doctorOfficePermissionCheck->setText(QCoreApplication::translate("MainWindow", "\345\214\273\347\224\237\345\212\236\345\205\254\345\256\244", nullptr));
        warehousePermissionCheck->setText(QCoreApplication::translate("MainWindow", "\350\200\227\346\235\220\345\272\223\346\210\277", nullptr));
        employeeFaceGroup->setTitle(QCoreApplication::translate("MainWindow", "\344\272\272\350\204\270\351\207\207\351\233\206", nullptr));
        employeeFaceLabel->setText(QCoreApplication::translate("MainWindow", "\345\260\232\346\234\252\351\207\207\351\233\206\344\272\272\350\204\270", nullptr));
        employeeFeatureLabel->setText(QCoreApplication::translate("MainWindow", "\346\234\252\346\217\220\345\217\226\344\272\272\350\204\270\347\211\271\345\276\201", nullptr));
        employeeCameraButton->setText(QCoreApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264\351\207\207\351\233\206", nullptr));
        employeeImageButton->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        saveEmployeeButton->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\221\230\345\267\245\344\277\241\346\201\257\345\222\214\344\272\272\350\204\270\347\211\271\345\276\201", nullptr));
        managementBackButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\351\241\265", nullptr));
        managementTitleLabel->setText(QCoreApplication::translate("MainWindow", "\345\221\230\345\267\245\346\241\243\346\241\210\347\256\241\347\220\206", nullptr));
        departmentFilterLabel->setText(QCoreApplication::translate("MainWindow", "\347\247\221\345\256\244\357\274\232", nullptr));
        positionFilterLabel->setText(QCoreApplication::translate("MainWindow", "\345\262\227\344\275\215\357\274\232", nullptr));
        statusFilterLabel->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232", nullptr));
        queryEmployeeButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        resetEmployeeButton->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260/\351\207\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem = employeeTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\345\267\245\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = employeeTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = employeeTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\347\247\221\345\256\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = employeeTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\345\262\227\344\275\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = employeeTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\350\201\224\347\263\273\347\224\265\350\257\235", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = employeeTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\351\227\250\347\246\201\346\235\203\351\231\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = employeeTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\344\272\272\345\221\230\347\212\266\346\200\201", nullptr));
        editEmployeeButton->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\345\221\230\345\267\245", nullptr));
        disableEmployeeButton->setText(QCoreApplication::translate("MainWindow", "\347\246\201\347\224\250\345\221\230\345\267\245", nullptr));
        deleteEmployeeButton->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\221\230\345\267\245", nullptr));
        accessLogBackButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\351\241\265", nullptr));
        accessLogTitleLabel->setText(QCoreApplication::translate("MainWindow", "\351\227\250\347\246\201\350\256\277\351\227\256\346\227\245\345\277\227", nullptr));
        logAreaLabel->setText(QCoreApplication::translate("MainWindow", "\350\256\277\351\227\256\345\214\272\345\237\237\357\274\232", nullptr));
        logAreaCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\345\205\250\351\203\250\345\214\272\345\237\237", nullptr));
        logAreaCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\350\215\257\346\210\277", nullptr));
        logAreaCombo->setItemText(2, QCoreApplication::translate("MainWindow", "\345\214\273\347\224\237\345\212\236\345\205\254\345\256\244", nullptr));
        logAreaCombo->setItemText(3, QCoreApplication::translate("MainWindow", "\350\200\227\346\235\220\345\272\223\346\210\277", nullptr));

        logResultLabel->setText(QCoreApplication::translate("MainWindow", "\351\200\232\350\241\214\347\273\223\346\236\234\357\274\232", nullptr));
        logResultCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\345\205\250\351\203\250\347\273\223\346\236\234", nullptr));
        logResultCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\346\224\276\350\241\214", nullptr));
        logResultCombo->setItemText(2, QCoreApplication::translate("MainWindow", "\346\227\240\346\235\203\351\231\220\346\213\222\347\273\235", nullptr));
        logResultCombo->setItemText(3, QCoreApplication::translate("MainWindow", "\350\257\206\345\210\253\345\244\261\350\264\245", nullptr));

        queryLogButton->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        resetLogButton->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260/\351\207\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = accessLogTable->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\351\200\232\350\241\214\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = accessLogTable->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\345\221\230\345\267\245\345\267\245\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = accessLogTable->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = accessLogTable->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\347\247\221\345\256\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = accessLogTable->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "\350\256\277\351\227\256\345\214\272\345\237\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = accessLogTable->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "\351\200\232\350\241\214\347\273\223\346\236\234", nullptr));
        accessBackButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236\344\270\273\351\241\265", nullptr));
        accessTitleLabel->setText(QCoreApplication::translate("MainWindow", "\351\227\250\347\246\201\344\272\272\350\204\270\350\257\206\345\210\253", nullptr));
        accessAreaLabel->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\351\227\250\347\246\201\345\214\272\345\237\237\357\274\232", nullptr));
        accessAreaCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\350\215\257\346\210\277", nullptr));
        accessAreaCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\345\214\273\347\224\237\345\212\236\345\205\254\345\256\244", nullptr));
        accessAreaCombo->setItemText(2, QCoreApplication::translate("MainWindow", "\350\200\227\346\235\220\345\272\223\346\210\277", nullptr));

        accessHintLabel->setText(QCoreApplication::translate("MainWindow", "\351\207\207\351\233\206\347\216\260\345\234\272\344\272\272\350\204\270\345\220\216\357\274\214\345\260\206\344\270\216\346\225\260\346\215\256\345\272\223\345\206\205\345\205\250\351\203\250\345\221\230\345\267\245\347\232\204 128 \347\273\264\347\211\271\345\276\201\350\277\233\350\241\214\346\257\224\345\257\271", nullptr));
        accessFaceLabel->setText(QCoreApplication::translate("MainWindow", "\350\257\267\351\207\207\351\233\206\351\227\250\347\246\201\344\272\272\350\204\270", nullptr));
        accessResultLabel->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205\350\257\206\345\210\253", nullptr));
        accessCameraButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\350\257\206\345\210\253", nullptr));
        accessImageButton->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\350\257\206\345\210\253", nullptr));
        accessFileButton->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207\350\257\206\345\210\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
