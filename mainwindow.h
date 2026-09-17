#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QElapsedTimer>
#include <QMainWindow>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include "mydatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void showHomePage();
    void showEmployeePage();
    void showEmployeeManagementPage();
    void showAccessPage();
    void captureEmployeeFace();
    void selectEmployeeImage();
    void saveEmployee();
    void startAccessRecognition();
    void stopAccessRecognition();
    void updateAccessFrame();
    void recognizeAccessImage();
    void recognizeAccessFace();
    void refreshEmployeeTable();
    void resetEmployeeFilters();
    void editSelectedEmployee();
    void disableSelectedEmployee();
    void deleteSelectedEmployee();

private:
    bool captureFromCamera(cv::Mat &image, QString &errorMessage);
    bool selectImage(cv::Mat &image, QString &errorMessage);
    bool extractFaceFeature(const cv::Mat &image, cv::Mat &feature,
                            QImage &preview, QString &errorMessage);
    void setEmployeeFace(const cv::Mat &image);
    void clearEmployeeForm();
    void showAccessResult(const QString &text, const QString &color);
    void writeAccessLogWithDebounce(const EmployeeFaceRecord *employee,
                                    const QString &result);
    int selectedEmployeeIndex() const;

    Ui::MainWindow *ui;
    cv::Ptr<cv::FaceDetectorYN> faceDetector;
    cv::Ptr<cv::FaceRecognizerSF> faceRecognizer;
    cv::Mat employeeFaceFeature;
    cv::Mat accessFaceFeature;
    cv::VideoCapture accessCamera;
    QTimer *accessTimer;
    QElapsedTimer logDebounceTimer;
    QString lastLogKey;
    static constexpr double DefaultFaceMatchThreshold = 0.363;
    QList<EmployeeFaceRecord> activeEmployees;
    QList<EmployeeFaceRecord> managementEmployees;
    double accessMatchThreshold = DefaultFaceMatchThreshold;
};

#endif // MAINWINDOW_H
