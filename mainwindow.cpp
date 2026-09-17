#include "mainwindow.h"
#include "mydatabase.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QCloseEvent>
#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include <cstring>
#include <limits>

namespace
{
const char *FaceDetectionModel = "D:/opencv4.5.5-MinGw7.3.0/face_detection_yunet_2022mar.onnx";
const char *FaceRecognitionModel = "D:/opencv4.5.5-MinGw7.3.0/face_recognition_sface_2021dec.onnx";

QImage matToQImage(const cv::Mat &image)
{
    if (image.empty())
        return QImage();

    if (image.type() == CV_8UC3)
        return QImage(image.data, image.cols, image.rows,
                      static_cast<int>(image.step), QImage::Format_BGR888).copy();
    if (image.type() == CV_8UC1)
        return QImage(image.data, image.cols, image.rows,
                      static_cast<int>(image.step), QImage::Format_Grayscale8).copy();

    cv::Mat converted;
    image.convertTo(converted, CV_8U);
    return matToQImage(converted);
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), accessTimer(new QTimer(this))
{
    ui->setupUi(this);
    setWindowTitle("医院门禁人脸识别系统");

    ui->departmentCombo->addItems({"内科", "外科", "急诊", "药房", "行政"});
    ui->positionCombo->addItems({"医生", "护士", "药师", "行政"});
    ui->phoneEdit->setValidator(new QRegularExpressionValidator(
        QRegularExpression("[0-9+\\- ]{0,20}"), ui->phoneEdit));

    ui->departmentFilterCombo->addItems({"全部科室", "内科", "外科", "急诊", "药房", "行政"});
    ui->positionFilterCombo->addItems({"全部岗位", "医生", "护士", "药师", "行政"});
    ui->statusFilterCombo->addItems({"全部状态", "在职", "休假", "离职"});
    ui->employeeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->employeeTable->verticalHeader()->setVisible(false);

    // 新增员工按钮：打开员工录入页面
    connect(ui->newEmployeeButton, &QPushButton::clicked, this, &MainWindow::showEmployeePage);
    connect(ui->employeeManagementButton, &QPushButton::clicked,
            this, &MainWindow::showEmployeeManagementPage);
    // 门禁核验按钮：打开人脸识别门禁页面
    connect(ui->accessButton, &QPushButton::clicked, this, &MainWindow::showAccessPage);
    // 员工页面返回按钮：回到主页
    connect(ui->employeeBackButton, &QPushButton::clicked, this, &MainWindow::showHomePage);
    connect(ui->managementBackButton, &QPushButton::clicked, this, &MainWindow::showHomePage);
    // 门禁页面返回按钮：回到主页
    connect(ui->accessBackButton, &QPushButton::clicked, this, &MainWindow::showHomePage);
    // 员工录入页-相机按钮：打开摄像头采集员工人脸
    connect(ui->employeeCameraButton, &QPushButton::clicked, this, &MainWindow::captureEmployeeFace);
    // 员工录入页-选择图片按钮：从本地选图片作为员工人脸
    connect(ui->employeeImageButton, &QPushButton::clicked, this, &MainWindow::selectEmployeeImage);
    // 员工录入页-保存按钮：保存员工信息+人脸特征到SQLite
    connect(ui->saveEmployeeButton, &QPushButton::clicked, this, &MainWindow::saveEmployee);
    // 30ms 定时取帧，在同一个循环中完成预览、人脸检测和实时比对。
    accessTimer->setInterval(30);
    connect(accessTimer, &QTimer::timeout, this, &MainWindow::updateAccessFrame);
    connect(ui->accessCameraButton, &QPushButton::clicked, this, &MainWindow::startAccessRecognition);
    connect(ui->accessImageButton, &QPushButton::clicked, this, &MainWindow::stopAccessRecognition);
    connect(ui->accessFileButton, &QPushButton::clicked, this, &MainWindow::recognizeAccessImage);
    connect(ui->queryEmployeeButton, &QPushButton::clicked, this, &MainWindow::refreshEmployeeTable);
    connect(ui->resetEmployeeButton, &QPushButton::clicked, this, &MainWindow::resetEmployeeFilters);
    connect(ui->editEmployeeButton, &QPushButton::clicked, this, &MainWindow::editSelectedEmployee);
    connect(ui->disableEmployeeButton, &QPushButton::clicked, this, &MainWindow::disableSelectedEmployee);
    connect(ui->deleteEmployeeButton, &QPushButton::clicked, this, &MainWindow::deleteSelectedEmployee);
    connect(ui->employeeTable, &QTableWidget::cellDoubleClicked,
            this, [this](int, int) { editSelectedEmployee(); });
    try
    {
        faceDetector = cv::FaceDetectorYN::create(FaceDetectionModel, "", cv::Size(320, 320));
        faceRecognizer = cv::FaceRecognizerSF::create(FaceRecognitionModel, "");
    }
    catch (const cv::Exception &e)
    {
        QMessageBox::critical(this, "模型加载失败",
                              QString("无法加载人脸识别模型：\n%1").arg(e.what()));
        ui->newEmployeeButton->setEnabled(false);
        ui->accessButton->setEnabled(false);
    }

    showHomePage();
}

MainWindow::~MainWindow()
{
    stopAccessRecognition();
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 关闭窗口前主动释放摄像头，避免设备被进程继续占用。
    stopAccessRecognition();
    QMainWindow::closeEvent(event);
}

void MainWindow::showHomePage()
{
    stopAccessRecognition();
    ui->stackedWidget->setCurrentWidget(ui->homePage);
}

void MainWindow::showEmployeePage()
{
    stopAccessRecognition();
    ui->stackedWidget->setCurrentWidget(ui->employeePage);
}

void MainWindow::showEmployeeManagementPage()
{
    stopAccessRecognition();
    ui->stackedWidget->setCurrentWidget(ui->employeeManagementPage);
    refreshEmployeeTable();
}

void MainWindow::showAccessPage()
{
    accessFaceFeature.release();
    ui->accessFaceLabel->setPixmap(QPixmap());
    ui->accessFaceLabel->setText("请点击“开始识别”打开摄像头");
    showAccessResult("等待识别", "#555555");
    ui->stackedWidget->setCurrentWidget(ui->accessPage);
}

bool MainWindow::captureFromCamera(cv::Mat &image, QString &errorMessage)
{
    cv::VideoCapture camera(0);
    if (!camera.isOpened())
    {
        errorMessage = "摄像头打开失败，请检查摄像头是否连接或被其他程序占用。";
        return false;
    }

    // 丢弃前几帧，给摄像头留出自动曝光时间。
    for (int i = 0; i < 8; ++i)
        camera.read(image);
    camera.release();

    if (image.empty())
    {
        errorMessage = "读取摄像头画面失败。";
        return false;
    }
    return true;
}

bool MainWindow::selectImage(cv::Mat &image, QString &errorMessage)
{
    const QString path = QFileDialog::getOpenFileName(
        this, "选择人脸图片", QString(), "图片 (*.jpg *.jpeg *.png *.bmp)");
    if (path.isEmpty())
        return false;

    // QFile + imdecode 可以正确读取包含中文的 Windows 路径。
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        errorMessage = "图片文件无法打开。";
        return false;
    }
    const QByteArray bytes = file.readAll();
    std::vector<uchar> buffer(bytes.begin(), bytes.end());
    image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    if (image.empty())
    {
        errorMessage = "图片格式不支持或图片已经损坏。";
        return false;
    }
    return true;
}

bool MainWindow::extractFaceFeature(const cv::Mat &image, cv::Mat &feature,
                                    QImage &preview, QString &errorMessage)
{
    if (!faceDetector || !faceRecognizer)
    {
        errorMessage = "人脸识别模型尚未加载。";
        return false;
    }

    try
    {
        faceDetector->setInputSize(image.size());
        cv::Mat faces;
        faceDetector->detect(image, faces);
        if (faces.rows == 0)
        {
            errorMessage = "未检测到人脸，请正对摄像头并保证光线充足。";
            return false;
        }
        // if (faces.rows > 1)
        // {
        //     errorMessage = "检测到多张人脸，请确保画面中只有一人。";
        //     return false;
        // }

        cv::Mat alignedFace;
        faceRecognizer->alignCrop(image, faces.row(0), alignedFace);
        faceRecognizer->feature(alignedFace, feature);
        feature = feature.reshape(1, 1).clone();
        if (feature.type() != CV_32F)
            feature.convertTo(feature, CV_32F);
        if (feature.total() != 128)
        {
            feature.release();
            errorMessage = "提取到的人脸特征不是 128 维，请检查识别模型。";
            return false;
        }

        cv::Mat marked = image.clone();
        const cv::Rect imageBounds(0, 0, marked.cols, marked.rows);
        cv::Rect faceRect(cvRound(faces.at<float>(0, 0)), cvRound(faces.at<float>(0, 1)),
                          cvRound(faces.at<float>(0, 2)), cvRound(faces.at<float>(0, 3)));
        faceRect &= imageBounds;
        cv::rectangle(marked, faceRect, cv::Scalar(0, 255, 0), 2);
        preview = matToQImage(marked);
        return true;
    }
    catch (const cv::Exception &e)
    {
        feature.release();
        errorMessage = QString("人脸特征提取失败：%1").arg(e.what());
        return false;
    }
}

void MainWindow::setEmployeeFace(const cv::Mat &image)
{
    QString errorMessage;
    QImage preview;
    if (!extractFaceFeature(image, employeeFaceFeature, preview, errorMessage))
    {
        QMessageBox::warning(this, "采集失败", errorMessage);
        return;
    }
    ui->employeeFaceLabel->setPixmap(QPixmap::fromImage(preview));
    ui->employeeFaceLabel->setText(QString());
    ui->employeeFeatureLabel->setText("已成功提取 128 维人脸特征");
}

void MainWindow::captureEmployeeFace()
{
    cv::Mat image;
    QString errorMessage;
    if (!captureFromCamera(image, errorMessage))
    {
        QMessageBox::warning(this, "摄像头错误", errorMessage);
        return;
    }
    setEmployeeFace(image);
}

void MainWindow::selectEmployeeImage()
{
    cv::Mat image;
    QString errorMessage;
    if (!selectImage(image, errorMessage))
    {
        if (!errorMessage.isEmpty())
            QMessageBox::warning(this, "图片错误", errorMessage);
        return;
    }
    setEmployeeFace(image);
}

void MainWindow::saveEmployee()
{
    EmployeeFaceRecord employee;
    employee.employeeNo = ui->employeeNoEdit->text().trimmed();
    employee.name = ui->employeeNameEdit->text().trimmed();
    employee.department = ui->departmentCombo->currentText();
    employee.position = ui->positionCombo->currentText();
    employee.phone = ui->phoneEdit->text().trimmed();
    employee.status = "在职";
    if (ui->pharmacyPermissionCheck->isChecked())
        employee.accessAreas.append("药房");
    if (ui->doctorOfficePermissionCheck->isChecked())
        employee.accessAreas.append("医生办公室");
    if (ui->warehousePermissionCheck->isChecked())
        employee.accessAreas.append("耗材库房");

    if (employee.employeeNo.isEmpty() || employee.name.isEmpty() || employee.phone.isEmpty())
    {
        QMessageBox::warning(this, "信息不完整", "请填写工号、姓名和联系电话。");
        return;
    }
    if (employeeFaceFeature.empty())
    {
        QMessageBox::warning(this, "缺少人脸", "请先通过摄像头或图片采集员工人脸。");
        return;
    }

    QString errorMessage;
    const QList<EmployeeFaceRecord> existingEmployees =
        MyDatabase::instance()->queryEmployees(QString(), QString(), QString(), &errorMessage);
    const double duplicateThreshold = MyDatabase::instance()->faceMatchThreshold(&errorMessage);
    if (!errorMessage.isEmpty())
    {
        QMessageBox::critical(this, "数据库错误", errorMessage);
        return;
    }

    // 新员工入库前与全部员工（包括休假、离职）比对，防止同一人重复建档。
    double bestScore = -std::numeric_limits<double>::infinity();
    const EmployeeFaceRecord *duplicateEmployee = nullptr;
    const int expectedBytes = static_cast<int>(128 * sizeof(float));
    for (const EmployeeFaceRecord &existing : existingEmployees)
    {
        if (existing.faceFeature.size() != expectedBytes)
            continue;
        cv::Mat storedFeature(1, 128, CV_32F);
        std::memcpy(storedFeature.data, existing.faceFeature.constData(),
                    static_cast<size_t>(expectedBytes));
        const double score = faceRecognizer->match(
            employeeFaceFeature, storedFeature, cv::FaceRecognizerSF::FR_COSINE);
        if (score > bestScore)
        {
            bestScore = score;
            duplicateEmployee = &existing;
        }
    }
    if (duplicateEmployee && bestScore >= duplicateThreshold)
    {
        QMessageBox::warning(
            this, "人脸已存在",
            QString("该人脸已录入，不能重复添加。\n已有员工：%1（工号：%2）\n匹配度：%3")
                .arg(duplicateEmployee->name, duplicateEmployee->employeeNo)
                .arg(bestScore, 0, 'f', 3));
        return;
    }

    const cv::Mat continuousFeature = employeeFaceFeature.isContinuous()
                                          ? employeeFaceFeature
                                          : employeeFaceFeature.clone();
    employee.faceFeature = QByteArray(
        reinterpret_cast<const char *>(continuousFeature.ptr<float>()),
        static_cast<int>(continuousFeature.total() * continuousFeature.elemSize()));

    if (!MyDatabase::instance()->addEmployee(employee, &errorMessage))
    {
        QMessageBox::critical(this, "保存失败", errorMessage);
        return;
    }

    QMessageBox::information(this, "保存成功",
                             QString("员工 %1（%2）已录入，人脸特征已保存到数据库。")
                                 .arg(employee.name, employee.employeeNo));
    clearEmployeeForm();
}

void MainWindow::clearEmployeeForm()
{
    ui->employeeNoEdit->clear();
    ui->employeeNameEdit->clear();
    ui->phoneEdit->clear();
    ui->departmentCombo->setCurrentIndex(0);
    ui->positionCombo->setCurrentIndex(0);
    ui->pharmacyPermissionCheck->setChecked(false);
    ui->doctorOfficePermissionCheck->setChecked(false);
    ui->warehousePermissionCheck->setChecked(false);
    ui->employeeFaceLabel->setPixmap(QPixmap());
    ui->employeeFaceLabel->setText("尚未采集人脸");
    ui->employeeFeatureLabel->setText("未提取人脸特征");
    employeeFaceFeature.release();
}

void MainWindow::startAccessRecognition()
{
    if (accessTimer->isActive())
        return;

    QString databaseError;
    // 开始识别时缓存当前全部在职员工，离职和休假人员已由 SQL 排除。
    activeEmployees = MyDatabase::instance()->queryEmployeeFaces(&databaseError);
    if (!databaseError.isEmpty())
    {
        QMessageBox::critical(this, "数据库错误", databaseError);
        return;
    }
    accessMatchThreshold = MyDatabase::instance()->faceMatchThreshold(&databaseError);
    if (!databaseError.isEmpty())
    {
        QMessageBox::critical(this, "数据库错误", databaseError);
        return;
    }

    if (!accessCamera.open(0))
    {
        QMessageBox::warning(this, "摄像头错误", "摄像头打开失败，请检查设备是否被占用。");
        return;
    }

    lastLogKey.clear();
    logDebounceTimer.invalidate();
    ui->accessAreaCombo->setEnabled(false);
    ui->accessCameraButton->setEnabled(false);
    ui->accessImageButton->setEnabled(true);
    showAccessResult("正在识别，请正对摄像头", "#555555");
    accessTimer->start();
}

void MainWindow::stopAccessRecognition()
{
    if (accessTimer)
        accessTimer->stop();
    if (accessCamera.isOpened())
        accessCamera.release();

    if (ui)
    {
        ui->accessAreaCombo->setEnabled(true);
        ui->accessCameraButton->setEnabled(true);
        ui->accessImageButton->setEnabled(false);
        ui->accessFileButton->setEnabled(true);
    }
}

void MainWindow::recognizeAccessImage()
{
    stopAccessRecognition();

    cv::Mat image;
    QString errorMessage;
    if (!selectImage(image, errorMessage))
    {
        if (!errorMessage.isEmpty())
            QMessageBox::warning(this, "图片错误", errorMessage);
        return;
    }

    activeEmployees = MyDatabase::instance()->queryEmployeeFaces(&errorMessage);
    accessMatchThreshold = MyDatabase::instance()->faceMatchThreshold(&errorMessage);
    if (!errorMessage.isEmpty())
    {
        QMessageBox::critical(this, "数据库错误", errorMessage);
        return;
    }

    QImage preview;
    if (!extractFaceFeature(image, accessFaceFeature, preview, errorMessage))
    {
        showAccessResult(errorMessage, "#d32f2f");
        return;
    }
    ui->accessFaceLabel->setPixmap(QPixmap::fromImage(preview));
    ui->accessFaceLabel->setText(QString());
    recognizeAccessFace();
}

void MainWindow::updateAccessFrame()
{
    cv::Mat frame;
    if (!accessCamera.isOpened() || !accessCamera.read(frame) || frame.empty())
    {
        stopAccessRecognition();
        showAccessResult("摄像头画面读取失败", "#d32f2f");
        return;
    }

    QString featureError;
    QImage preview;
    // 复用已有特征提取函数；没有检测到人脸时只显示实时画面，不进入数据库比对。
    if (!extractFaceFeature(frame, accessFaceFeature, preview, featureError))
    {
        accessFaceFeature.release();
        ui->accessFaceLabel->setPixmap(QPixmap::fromImage(matToQImage(frame)));
        ui->accessFaceLabel->setText(QString());
        if (featureError.startsWith("未检测到人脸"))
            showAccessResult("未检测到人脸", "#555555");
        else
            showAccessResult(featureError, "#d32f2f");
        return;
    }

    ui->accessFaceLabel->setPixmap(QPixmap::fromImage(preview));
    ui->accessFaceLabel->setText(QString());
    recognizeAccessFace();
}

void MainWindow::recognizeAccessFace()
{
    if (accessFaceFeature.empty())
        return;

    double bestScore = -std::numeric_limits<double>::infinity();
    const EmployeeFaceRecord *bestEmployee = nullptr;
    const int expectedBytes = static_cast<int>(128 * sizeof(float));

    // 与所有在职员工逐一做余弦相似度比对，并保留最高匹配分。
    for (const EmployeeFaceRecord &employee : activeEmployees)
    {
        if (employee.faceFeature.size() != expectedBytes)
            continue;

        cv::Mat storedFeature(1, 128, CV_32F);
        std::memcpy(storedFeature.data, employee.faceFeature.constData(),
                    static_cast<size_t>(expectedBytes));
        const double score = faceRecognizer->match(
            accessFaceFeature, storedFeature, cv::FaceRecognizerSF::FR_COSINE);
        if (score > bestScore)
        {
            bestScore = score;
            bestEmployee = &employee;
        }
    }

    if (bestEmployee && bestScore >= accessMatchThreshold)
    {
        const QString area = ui->accessAreaCombo->currentText();
        const QString employeeInfo = QString("\n工号：%1  姓名：%2  科室：%3  匹配度：%4")
                                         .arg(bestEmployee->employeeNo,
                                              bestEmployee->name,
                                              bestEmployee->department)
                                         .arg(bestScore, 0, 'f', 3);

        if (bestEmployee->accessAreas.contains(area))
        {
            showAccessResult("身份核验通过，允许进入" + employeeInfo, "#2e7d32");
            writeAccessLogWithDebounce(bestEmployee, "放行");
        }
        else
        {
            showAccessResult("身份确认成功，无本区域权限" + employeeInfo, "#ef6c00");
            writeAccessLogWithDebounce(bestEmployee, "无权限拒绝");
        }
    }
    else
    {
        showAccessResult("身份识别失败，禁止通行", "#d32f2f");
        writeAccessLogWithDebounce(nullptr, "识别失败");
    }
}

void MainWindow::showAccessResult(const QString &text, const QString &color)
{
    ui->accessResultLabel->setText(text);
    ui->accessResultLabel->setStyleSheet(
        QString("QLabel { color: %1; font-weight: bold; padding: 6px; }").arg(color));
}

void MainWindow::writeAccessLogWithDebounce(const EmployeeFaceRecord *employee,
                                            const QString &result)
{
    const QString employeeNo = employee ? employee->employeeNo : QString();
    const QString logKey = employeeNo + '|' + ui->accessAreaCombo->currentText() + '|' + result;

    // 同一人脸、同一区域、同一结果在 1 秒内只写一次，防止实时帧造成日志重复。
    if (logDebounceTimer.isValid() && lastLogKey == logKey
        && logDebounceTimer.elapsed() < 1000)
        return;

    AccessLogRecord record;
    if (employee)
    {
        record.employeeNo = employee->employeeNo;
        record.name = employee->name;
        record.department = employee->department;
    }
    record.accessArea = ui->accessAreaCombo->currentText();
    record.result = result;

    QString errorMessage;
    if (!MyDatabase::instance()->addAccessLog(record, &errorMessage))
        qWarning() << errorMessage;

    lastLogKey = logKey;
    logDebounceTimer.restart();
}

void MainWindow::refreshEmployeeTable()
{
    const QString department = ui->departmentFilterCombo->currentIndex() == 0
                                   ? QString() : ui->departmentFilterCombo->currentText();
    const QString position = ui->positionFilterCombo->currentIndex() == 0
                                 ? QString() : ui->positionFilterCombo->currentText();
    const QString status = ui->statusFilterCombo->currentIndex() == 0
                               ? QString() : ui->statusFilterCombo->currentText();

    QString errorMessage;
    managementEmployees = MyDatabase::instance()->queryEmployees(
        department, position, status, &errorMessage);
    if (!errorMessage.isEmpty())
    {
        QMessageBox::critical(this, "查询失败", errorMessage);
        return;
    }

    ui->employeeTable->setRowCount(managementEmployees.size());
    for (int row = 0; row < managementEmployees.size(); ++row)
    {
        const EmployeeFaceRecord &employee = managementEmployees.at(row);
        const QStringList values = {employee.employeeNo, employee.name, employee.department,
                                    employee.position, employee.phone,
                                    employee.accessAreas.join("、"), employee.status};
        for (int column = 0; column < values.size(); ++column)
        {
            auto *item = new QTableWidgetItem(values.at(column));
            item->setTextAlignment(Qt::AlignCenter);
            ui->employeeTable->setItem(row, column, item);
        }

        // 人员状态用固定颜色区分，便于快速判断是否仍参与门禁识别。
        QColor statusColor("#757575");
        if (employee.status == "在职")
            statusColor = QColor("#2e7d32");
        else if (employee.status == "休假")
            statusColor = QColor("#ef6c00");
        ui->employeeTable->item(row, 6)->setForeground(statusColor);
        QFont statusFont = ui->employeeTable->item(row, 6)->font();
        statusFont.setBold(true);
        ui->employeeTable->item(row, 6)->setFont(statusFont);
    }
}

void MainWindow::resetEmployeeFilters()
{
    ui->departmentFilterCombo->setCurrentIndex(0);
    ui->positionFilterCombo->setCurrentIndex(0);
    ui->statusFilterCombo->setCurrentIndex(0);
    refreshEmployeeTable();
}

int MainWindow::selectedEmployeeIndex() const
{
    const int row = ui->employeeTable->currentRow();
    if (row < 0 || row >= managementEmployees.size())
        return -1;
    return row;
}

void MainWindow::editSelectedEmployee()
{
    const int index = selectedEmployeeIndex();
    if (index < 0)
    {
        QMessageBox::information(this, "提示", "请先选择一名员工。");
        return;
    }

    EmployeeFaceRecord employee = managementEmployees.at(index);
    QDialog dialog(this);
    dialog.setWindowTitle("编辑员工档案");
    dialog.resize(460, 520);
    auto *layout = new QVBoxLayout(&dialog);
    auto *form = new QFormLayout;
    auto *staffIdEdit = new QLineEdit(employee.employeeNo);
    auto *nameEdit = new QLineEdit(employee.name);
    auto *departmentCombo = new QComboBox;
    auto *positionCombo = new QComboBox;
    auto *phoneEdit = new QLineEdit(employee.phone);
    auto *statusCombo = new QComboBox;
    auto *pharmacyCheck = new QCheckBox("药房");
    auto *doctorOfficeCheck = new QCheckBox("医生办公室");
    auto *warehouseCheck = new QCheckBox("耗材库房");
    auto *faceStatusLabel = new QLabel("保留原人脸特征");
    auto *cameraButton = new QPushButton("摄像头重新采集");
    auto *imageButton = new QPushButton("选择图片重新采集");

    // 工号是员工档案主键，编辑时只读，数据库更新也只把它用于 where 条件。
    staffIdEdit->setReadOnly(true);
    departmentCombo->addItems({"内科", "外科", "急诊", "药房", "行政"});
    positionCombo->addItems({"医生", "护士", "药师", "行政"});
    statusCombo->addItems({"在职", "休假", "离职"});
    departmentCombo->setCurrentText(employee.department);
    positionCombo->setCurrentText(employee.position);
    statusCombo->setCurrentText(employee.status);
    pharmacyCheck->setChecked(employee.accessAreas.contains("药房"));
    doctorOfficeCheck->setChecked(employee.accessAreas.contains("医生办公室"));
    warehouseCheck->setChecked(employee.accessAreas.contains("耗材库房"));

    auto *permissionWidget = new QWidget;
    auto *permissionLayout = new QVBoxLayout(permissionWidget);
    permissionLayout->setContentsMargins(0, 0, 0, 0);
    permissionLayout->addWidget(pharmacyCheck);
    permissionLayout->addWidget(doctorOfficeCheck);
    permissionLayout->addWidget(warehouseCheck);
    auto *faceButtonsWidget = new QWidget;
    auto *faceButtonsLayout = new QHBoxLayout(faceButtonsWidget);
    faceButtonsLayout->setContentsMargins(0, 0, 0, 0);
    faceButtonsLayout->addWidget(cameraButton);
    faceButtonsLayout->addWidget(imageButton);

    form->addRow("工号：", staffIdEdit);
    form->addRow("姓名：", nameEdit);
    form->addRow("科室：", departmentCombo);
    form->addRow("岗位：", positionCombo);
    form->addRow("联系电话：", phoneEdit);
    form->addRow("门禁权限：", permissionWidget);
    form->addRow("人员状态：", statusCombo);
    form->addRow("人脸特征：", faceStatusLabel);
    form->addRow(QString(), faceButtonsWidget);
    layout->addLayout(form);

    cv::Mat editedFeature;
    auto collectNewFeature = [this, &editedFeature, faceStatusLabel](const cv::Mat &image) {
        QString errorMessage;
        QImage preview;
        if (!extractFaceFeature(image, editedFeature, preview, errorMessage))
        {
            QMessageBox::warning(this, "采集失败", errorMessage);
            return;
        }
        faceStatusLabel->setText("已采集新的 128 维人脸特征");
        faceStatusLabel->setStyleSheet("color:#2e7d32;font-weight:bold;");
    };
    connect(cameraButton, &QPushButton::clicked, &dialog, [this, collectNewFeature]() {
        cv::Mat image;
        QString errorMessage;
        if (!captureFromCamera(image, errorMessage))
        {
            QMessageBox::warning(this, "摄像头错误", errorMessage);
            return;
        }
        collectNewFeature(image);
    });
    connect(imageButton, &QPushButton::clicked, &dialog, [this, collectNewFeature]() {
        cv::Mat image;
        QString errorMessage;
        if (!selectImage(image, errorMessage))
        {
            if (!errorMessage.isEmpty())
                QMessageBox::warning(this, "图片错误", errorMessage);
            return;
        }
        collectNewFeature(image);
    });

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, [&]() {
        if (nameEdit->text().trimmed().isEmpty() || phoneEdit->text().trimmed().isEmpty())
        {
            QMessageBox::warning(&dialog, "信息不完整", "姓名和联系电话不能为空。");
            return;
        }
        dialog.accept();
    });

    if (dialog.exec() != QDialog::Accepted)
        return;

    employee.name = nameEdit->text().trimmed();
    employee.department = departmentCombo->currentText();
    employee.position = positionCombo->currentText();
    employee.phone = phoneEdit->text().trimmed();
    employee.status = statusCombo->currentText();
    employee.accessAreas.clear();
    if (pharmacyCheck->isChecked()) employee.accessAreas.append("药房");
    if (doctorOfficeCheck->isChecked()) employee.accessAreas.append("医生办公室");
    if (warehouseCheck->isChecked()) employee.accessAreas.append("耗材库房");

    const bool updateFace = !editedFeature.empty();
    if (updateFace)
    {
        const cv::Mat feature = editedFeature.isContinuous() ? editedFeature : editedFeature.clone();
        employee.faceFeature = QByteArray(reinterpret_cast<const char *>(feature.ptr<float>()),
                                          static_cast<int>(feature.total() * feature.elemSize()));
    }

    QString errorMessage;
    if (!MyDatabase::instance()->updateEmployee(employee, updateFace, &errorMessage))
    {
        QMessageBox::critical(this, "保存失败", errorMessage);
        return;
    }
    refreshEmployeeTable();
    QMessageBox::information(this, "保存成功", "员工档案已更新。");
}

void MainWindow::disableSelectedEmployee()
{
    const int index = selectedEmployeeIndex();
    if (index < 0)
    {
        QMessageBox::information(this, "提示", "请先选择一名员工。");
        return;
    }

    const EmployeeFaceRecord &employee = managementEmployees.at(index);
    if (QMessageBox::question(this, "确认禁用",
                              QString("确定将员工 %1（%2）状态改为离职吗？")
                                  .arg(employee.name, employee.employeeNo))
        != QMessageBox::Yes)
        return;

    QString errorMessage;
    if (!MyDatabase::instance()->disableEmployee(employee.employeeNo, &errorMessage))
    {
        QMessageBox::critical(this, "禁用失败", errorMessage);
        return;
    }
    refreshEmployeeTable();
}

void MainWindow::deleteSelectedEmployee()
{
    const int index = selectedEmployeeIndex();
    if (index < 0)
    {
        QMessageBox::information(this, "提示", "请先选择一名员工。");
        return;
    }

    const EmployeeFaceRecord &employee = managementEmployees.at(index);
    if (QMessageBox::warning(
            this, "确认删除",
            QString("确定永久删除员工 %1（%2）吗？\n此操作会删除员工资料和人脸特征，且无法恢复。")
                .arg(employee.name, employee.employeeNo),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No)
        != QMessageBox::Yes)
        return;

    QString errorMessage;
    if (!MyDatabase::instance()->deleteEmployee(employee.employeeNo, &errorMessage))
    {
        QMessageBox::critical(this, "删除失败", errorMessage);
        return;
    }
    refreshEmployeeTable();
}
