#include "imageorganizerwindow.h"
#include "ui_imageorganizerwindow.h" // généré depuis imageorganizerwindow.ui

#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>

static QString imagesFilter()
{
    return QStringLiteral("Images (*.png *.jpg *.jpeg *.bmp *.webp *.tif *.tiff)");
}

ImageOrganizerWindow::ImageOrganizerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageOrganizerWindow)
{
    ui->setupUi(this);

    setWindowTitle(QStringLiteral("Image Organizer — V1 (carrés)"));

    // État initial UI
    // pushButton = bouton Export (désactivé au début)
    ui->pushButton->setEnabled(false);

    // label_2 = compteur
    ui->label_2->setText(QStringLiteral("0 image(s) chargée(s)"));

    // progressBar = remise à zéro
    resetProgress();

    // NOTE: Autoconnect fonctionnera si:
    // - le .ui contient bien les objectName "pushButton_2" et "pushButton"
    // - les slots s'appellent on_pushButton_2_clicked() et on_pushButton_clicked()
}

ImageOrganizerWindow::~ImageOrganizerWindow()
{
    delete ui;
}

void ImageOrganizerWindow::updateUiState()
{
    const bool hasImages = !m_paths.isEmpty();
    ui->pushButton->setEnabled(hasImages); // Export activé si on a des images

    ui->label_2->setText(QStringLiteral("%1 image(s) chargée(s)").arg(m_paths.size()));
}

void ImageOrganizerWindow::resetProgress()
{
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
}

void ImageOrganizerWindow::refreshPreview()
{
    // TODO (à implémenter par toi) :
    // 1) Charger QImage depuis m_paths (utilise QImageReader pour gérer EXIF).
    // 2) V1 Strict : rejeter width != height (accumuler la liste des rejetées et prévenir via QMessageBox).
    // 3) Calculer la grille (nCols=ceil(sqrt(N)), nRows=ceil(N/nCols), tileSize, positions).
    // 4) Composer une image de PREVIEW (taille ~min(1024, m_outputSize)) via QPainter + fond m_bgColor.
    // 5) Afficher dans un QLabel de preview (si tu en ajoutes un dans le .ui, ex: "previewLabel").
}

bool ImageOrganizerWindow::exportFinal(const QString &path)
{
    // TODO (à implémenter par toi) :
    // - Charger/valider images (strict carrés en V1).
    // - Composer m_outputSize x m_outputSize (QImage + QPainter, fond m_bgColor).
    // - Déterminer le format depuis l’extension (PNG/JPEG) et sauvegarder (QImage::save).
    // - Mettre à jour ui->progressBar si tu veux montrer l’avancement.
    return false;
}

// --- Importer (pushButton_2) ---
void ImageOrganizerWindow::on_pushButton_2_clicked()
{
    const QString startDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    const QStringList files = QFileDialog::getOpenFileNames(
        this,
        QStringLiteral("Choisir des images"),
        startDir.isEmpty() ? QDir::homePath() : startDir,
        imagesFilter()
        );
    if (files.isEmpty())
        return;

    m_paths = files;

    resetProgress();
    updateUiState();

    statusBar()->showMessage(QStringLiteral("%1 image(s) importée(s)").arg(m_paths.size()), 3000);

    // Tu pourras appeler refreshPreview() quand tu auras un QLabel de preview.
    // refreshPreview();
}

// --- Exporter (pushButton) ---
void ImageOrganizerWindow::on_pushButton_clicked()
{
    if (m_paths.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("Exporter"),
                                 QStringLiteral("Aucune image chargée."));
        return;
    }

    const QString startDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    const QString defaultName =
        QDir(startDir.isEmpty() ? QDir::homePath() : startDir)
            .filePath(QStringLiteral("mosaic.png"));

    const QString savePath = QFileDialog::getSaveFileName(
        this,
        QStringLiteral("Enregistrer l'image composée"),
        defaultName,
        QStringLiteral("PNG (*.png);;JPEG (*.jpg *.jpeg)")
        );
    if (savePath.isEmpty())
        return;

    ui->progressBar->setValue(10);
    const bool ok = exportFinal(savePath);
    ui->progressBar->setValue(ok ? 100 : 0);

    if (ok) {
        statusBar()->showMessage(QStringLiteral("Fichier enregistré : %1").arg(savePath), 4000);
    } else {
        QMessageBox::warning(this, QStringLiteral("Exporter"),
                             QStringLiteral("L'export n'a pas abouti (implémente exportFinal)."));
    }
}
