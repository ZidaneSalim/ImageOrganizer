#ifndef IMAGEORGANIZERWINDOW_H
#define IMAGEORGANIZERWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageOrganizerWindow; } // <class>ImageOrganizerWindow</class> dans le .ui
QT_END_NAMESPACE

class ImageOrganizerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageOrganizerWindow(QWidget *parent = nullptr);
    ~ImageOrganizerWindow();

private slots:
    // Auto-connect via .ui (objectName + clicked)
    void on_pushButton_2_clicked(); // Importer
    void on_pushButton_clicked();   // Exporter

private:
    Ui::ImageOrganizerWindow *ui = nullptr;

    // État minimal
    QStringList m_paths;
    int m_outputSize = 2048;
    int m_gutter     = 8;
    QColor m_bgColor = Qt::white;
    int m_fitMode    = 0; // 0=Strict; 1=FitInside; 2=CenterCrop (pour V2)

    // Aides UI
    void updateUiState();  // active/désactive Export, met à jour "X images loaded"
    void resetProgress();  // remet progressBar

    // À implémenter par toi (guide)
    void refreshPreview();                 // génère une preview (downsized) et l’affiche (si tu ajoutes un QLabel dédié)
    bool exportFinal(const QString &path); // compose en pleine résolution et sauvegarde
};

#endif // IMAGEORGANIZERWINDOW_H
