#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

// HEADER QT CHARTS
#include <QtCharts>

#include <chrono>
using namespace std;


// BAGIAN LOGIKA


// Simulasi Rekursif
// Fungsi ini meniru perilaku lambat rekursif tanpa memakan memori stack
void cekSlotRekursif(int n) {
    // Kita lakukan loop sebanyak N kali
    for (int i = 0; i < n; i++) {
        volatile int dummy = 0;
        for (int j = 0; j < 200; j++) {
            dummy += j;
        }
    }
}

// Iteratif
void cekSlotIteratif(int n) {
    for (int i = 0; i < n; i++) {
        // Loop biasa tanpa pemberat berat, jadi dia cepat
        volatile int math = i * 2;
        (void)math;
    }
}


// BAGIAN UTAMANE


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("Smart Parking Analyzer - Anti Crash Edition");
    window.resize(900, 700);

    // Styling Dark Mode
    QString darkStyle = R"(
        QMainWindow { background-color: #1e2130; }
        QLabel { color: white; font-size: 14px; font-weight: bold; }
        QLineEdit, QComboBox {
            padding: 5px; border-radius: 5px; border: 1px solid #ccc; font-size: 13px;
        }
        QPushButton {
            background-color: #27ae60; color: white; font-weight: bold; font-size: 14px;
            border-radius: 5px; padding: 8px;
        }
        QPushButton:hover { background-color: #2ecc71; }
    )";
    window.setStyleSheet(darkStyle);

    QWidget *centralWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Judul
    QLabel *titleLabel = new QLabel("Smart Parking Analyzer");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; color: #ecf0f1; margin-bottom: 10px;");
    mainLayout->addWidget(titleLabel);

    // Form
    QFrame *formFrame = new QFrame();
    formFrame->setStyleSheet("background-color: #2c3e50; border-radius: 10px;");
    QVBoxLayout *formLayoutContainer = new QVBoxLayout(formFrame);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->setLabelAlignment(Qt::AlignLeft);
    formLayout->setFormAlignment(Qt::AlignCenter);
    formLayout->setSpacing(15);

    QComboBox *comboKendaraan = new QComboBox();
    comboKendaraan->addItems({"Mobil", "Motor"});
    comboKendaraan->setFixedWidth(300);

    QComboBox *comboLantai = new QComboBox();
    comboLantai->addItems({"A", "B", "C", "D", "E", "F"});
    comboLantai->setFixedWidth(300);

    QLineEdit *inputSlot = new QLineEdit();
    inputSlot->setPlaceholderText("Masukkan Jumlah Slot (Contoh: 50000)");
    inputSlot->setFixedWidth(300);

    formLayout->addRow("Jenis Kendaraan", comboKendaraan);
    formLayout->addRow("Lantai", comboLantai);
    formLayout->addRow("Jumlah Slot (N)", inputSlot);
    formLayoutContainer->addLayout(formLayout);

    QPushButton *btnCek = new QPushButton("CEK SLOT");
    btnCek->setFixedWidth(150);
    btnCek->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnCek);
    btnLayout->addStretch();
    formLayoutContainer->addLayout(btnLayout);

    mainLayout->addWidget(formFrame);

    // Status
    QLabel *lblStatus = new QLabel("Status Slot: MENUNGGU INPUT...");
    lblStatus->setAlignment(Qt::AlignCenter);
    lblStatus->setStyleSheet("font-size: 18px; color: #ecf0f1; margin-top: 10px;");
    mainLayout->addWidget(lblStatus);

    QLabel *lblWaktu = new QLabel("-");
    lblWaktu->setAlignment(Qt::AlignCenter);
    lblWaktu->setStyleSheet("font-size: 12px; color: #bdc3c7;");
    mainLayout->addWidget(lblWaktu);

    // chart gacor e

    QChart *chart = new QChart();
    chart->setTitle("Grafik Running Time: Iteratif vs Rekursif");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor("#2c3e50")));
    chart->setTitleBrush(QBrush(Qt::white));
    chart->legend()->setLabelColor(Qt::white);

    // Sumbu X (Grid Kotak)
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Jumlah Slot Dicek");
    axisX->setLabelsColor(Qt::white);
    axisX->setTitleBrush(Qt::white);
    axisX->setGridLineVisible(true);
    axisX->setGridLineColor(QColor("#7f8c8d"));
    axisX->setTickCount(6);

    // Sumbu Y (Grid Kotak)
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Waktu Eksekusi (ms)");
    axisY->setLabelsColor(Qt::white);
    axisY->setTitleBrush(Qt::white);
    axisY->setGridLineVisible(true);
    axisY->setGridLineColor(QColor("#7f8c8d"));
    axisY->setTickCount(6);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(300);
    mainLayout->addWidget(chartView);

    window.setCentralWidget(centralWidget);

    // Tombol cuy
    QObject::connect(btnCek, &QPushButton::clicked, [&]() {
        bool ok;
        int N = inputSlot->text().toInt(&ok);

        if (!ok || N <= 0) {
            lblStatus->setText("Status: ERROR (Masukkan angka valid!)");
            return;
        }

        lblStatus->setText(QString("Status Slot: TERISI (Lantai %1 - Slot %2)").arg(comboLantai->currentText()).arg(N));

        chart->removeAllSeries();

        // Series Iteratif
        QLineSeries *seriesIteratif = new QLineSeries();
        seriesIteratif->setName("Iteratif");
        seriesIteratif->setColor(QColor("#3498db"));
        seriesIteratif->setPointsVisible(true);
        seriesIteratif->setPointLabelsVisible(false);

        // Series Rekursif
        QLineSeries *seriesRekursif = new QLineSeries();
        seriesRekursif->setName("Rekursif");
        seriesRekursif->setColor(QColor("#e74c3c"));
        seriesRekursif->setPointsVisible(true);

        int step = N / 5;
        if (step < 1) step = 1;
        double maxTime = 0;

        for (int i = step; i <= N; i += step) {
            // Ukur Iteratif
            auto start = chrono::high_resolution_clock::now();
            cekSlotIteratif(i);
            auto end = chrono::high_resolution_clock::now();
            double timeIter = chrono::duration<double, milli>(end - start).count();
            seriesIteratif->append(i, timeIter);

            // Ukur Rekursif
            start = chrono::high_resolution_clock::now();
            cekSlotRekursif(i);
            end = chrono::high_resolution_clock::now();
            double timeRec = chrono::duration<double, milli>(end - start).count();
            seriesRekursif->append(i, timeRec);

            if (timeRec > maxTime) maxTime = timeRec;
        }

        lblWaktu->setText(QString("Waktu Terakhir -> Iteratif: %1 ms | Rekursif: %2 ms")
                              .arg(seriesIteratif->at(seriesIteratif->count()-1).y())
                              .arg(seriesRekursif->at(seriesRekursif->count()-1).y()));

        chart->addSeries(seriesIteratif);
        chart->addSeries(seriesRekursif);

        seriesIteratif->attachAxis(axisX);
        seriesIteratif->attachAxis(axisY);
        seriesRekursif->attachAxis(axisX);
        seriesRekursif->attachAxis(axisY);

        axisX->setRange(0, N);
        axisX->setMax(N + (N*0.1));
        axisY->setRange(0, maxTime + (maxTime*0.1));
    });

    window.show();
    return app.exec();
}
