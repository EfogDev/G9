#include "settingswindow.h"

SettingsWindow::SettingsWindow(Settings settings, QWidget *parent): QWidget(parent) {
    this->settings = settings;

    connect(this, SIGNAL(destroyed()), qApp, SLOT(quit()));

    setFixedSize(350, 500);
    setWindowTitle("Настройки");

    QString groupBoxStyle = "QGroupBox {\
                                 border: 1px solid #777;\
                                 margin: 10px;\
                                 padding: 4px;\
                                 border-radius: 3px;\
                             }\
                             \
                             QGroupBox::title {\
                                 subcontrol-origin: margin;\
                                 subcontrol-position: top left;\
                                 padding: 4px;\
                                 left: 20px;\
                                 font-weight: bold;\
                             }";

    /* Main */

    mainGroup = new QGroupBox("Основные", this);
    mainGroup->setGeometry(20, 20, width() - 40, 290);
    mainGroup->setStyleSheet(groupBoxStyle);

    autoSaveLabel = new Label("Сохранять скриншот", mainGroup);
    autoSaveLabel->adjustSize();
    autoSaveLabel->move(62, 42);
    connect(autoSaveLabel, SIGNAL(clicked()), this, SLOT(autoSaveLabelClicked()));

    autoSaveCheckBox = new QCheckBox("", mainGroup);
    autoSaveCheckBox->adjustSize();
    autoSaveCheckBox->move(40, 40);
    connect(autoSaveCheckBox, SIGNAL(toggled(bool)), this, SLOT(autoSaveChanged()));

    saveDirLabel = new Label("Папка: ", mainGroup);
    saveDirLabel->adjustSize();
    saveDirLabel->move(40, 74);
    saveDirLabel->setEnabled(false);

    saveDirEdit = new QLineEdit(mainGroup);
    saveDirEdit->setReadOnly(true);
    saveDirEdit->setGeometry(90, 70, 100, 25);
    saveDirEdit->setEnabled(false);

    saveDirButton = new QPushButton("Обзор", mainGroup);
    saveDirButton->setGeometry(195, 70, 70, 25);
    saveDirButton->setEnabled(false);
    connect(saveDirButton, SIGNAL(clicked()), this, SLOT(saveDirButtonClicked()));

    saveFormatLabel = new Label("Формат сохранения: ", mainGroup);
    saveFormatLabel->adjustSize();
    saveFormatLabel->move(40, 110);
    saveFormatLabel->setEnabled(false);

    saveFormatComboBox = new QComboBox(mainGroup);
    saveFormatComboBox->setGeometry(175, 105, 90, 25);
    saveFormatComboBox->setEditable(false);
    saveFormatComboBox->setEnabled(false);
    saveFormatComboBox->addItem("png");
    saveFormatComboBox->addItem("jpg");
    saveFormatComboBox->addItem("gif");
    connect(saveFormatComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(saveFormatComboBoxSelected(int)));

    saveQualityLabel = new Label("Качество (0-99):", mainGroup);
    saveQualityLabel->adjustSize();
    saveQualityLabel->move(40, 145);
    saveQualityLabel->setEnabled(false);

    saveQualityEdit = new QLineEdit("99", mainGroup);
    saveQualityEdit->setGeometry(145, 140, 120, 25);
    saveQualityEdit->setMaxLength(3);
    QIntValidator *validator = new QIntValidator(1, 99);
    saveQualityEdit->setValidator(validator);
    saveQualityEdit->setEnabled(false);

    autoCopyLabel = new Label("Копировать в буффер", mainGroup);
    autoCopyLabel->adjustSize();
    autoCopyLabel->move(62, 177);
    connect(autoCopyLabel, SIGNAL(clicked()), this, SLOT(autoCopyLabelClicked()));

    autoCopyCheckBox = new QCheckBox("", mainGroup);
    autoCopyCheckBox->adjustSize();
    autoCopyCheckBox->move(40, 175);

    autoSendLabel = new Label("Отправлять на сервер (недоступно)", mainGroup);
    autoSendLabel->adjustSize();
    autoSendLabel->move(62, 204);
    autoSendLabel->setEnabled(false);

    autoSendCheckbox = new QCheckBox("", mainGroup);
    autoSendCheckbox->adjustSize();
    autoSendCheckbox->move(40, 202);
    autoSendCheckbox->setEnabled(false);

    soundLabel = new Label("Воспроизводить звук", mainGroup);
    soundLabel->adjustSize();
    soundLabel->move(62, 232);
    connect(soundLabel, SIGNAL(clicked()), this, SLOT(soundLabelClicked()));

    soundCheckBox = new QCheckBox("", mainGroup);
    soundCheckBox->adjustSize();
    soundCheckBox->move(40, 230);

    /* Additional */

    additionalGroup = new QGroupBox("Дополнительные", this);
    additionalGroup->setGeometry(20, 330, width() - 40, 130);
    additionalGroup->setStyleSheet(groupBoxStyle);

    opacityLabel = new Label("Затемнение (0-99%):", additionalGroup);
    opacityLabel->adjustSize();
    opacityLabel->move(40, 40);

    opacityEdit = new QLineEdit("82", additionalGroup);
    opacityEdit->setGeometry(175, 35, 88, 25);
    opacityEdit->setMaxLength(3);
    opacityEdit->setValidator(validator);

    frameColorLabel = new Label("Цвет линий:", additionalGroup);
    frameColorLabel->adjustSize();
    frameColorLabel->move(40, 75);

    QPixmap pixmap(17, 17);
    pixmap.fill(QColor(120, 120, 120));

    frameColorImage = new Label(additionalGroup);
    frameColorImage->setPixmap(pixmap);
    frameColorImage->setGeometry(120, 75, 17, 17);

    frameColorButton = new QPushButton("Выбрать", additionalGroup);
    frameColorButton->adjustSize();
    frameColorButton->setGeometry(145, 70, 120, frameColorButton->height());
    connect(frameColorButton, SIGNAL(clicked()), this, SLOT(frameColorButtonClicked()));

    /* Buttons */

    saveButton = new QPushButton("Сохранить", this);
    saveButton->setGeometry(width() - 118, height() - 38, 90, 25);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveClicked()));

    cancelButton = new QPushButton("Отмена", this);
    cancelButton->setGeometry(width() - 118 - 90 - 10, height() - 38, 90, 25);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));

    load();
    show();
}

void SettingsWindow::load() {
    if (settings.autoSave) {
        autoSaveCheckBox->setChecked(true);
        saveDirLabel->setEnabled(true);
        saveDirEdit->setEnabled(true);
        saveDirButton->setEnabled(true);
        saveFormatLabel->setEnabled(true);
        saveFormatComboBox->setEnabled(true);
    }

    if (settings.autoCopy)
        autoCopyCheckBox->setChecked(true);

    if (settings.sound)
        soundCheckBox->setChecked(true);

    saveDirEdit->setText(settings.saveDir);

    if (settings.saveFormat == "png")
        saveFormatComboBox->setCurrentIndex(0);

    if (settings.saveFormat == "jpg") {
        saveFormatComboBox->setCurrentIndex(1);
        saveQualityEdit->setEnabled(true);
        saveQualityLabel->setEnabled(true);
    }

    if (settings.saveFormat == "gif") {
        saveFormatComboBox->setCurrentIndex(2);
        saveQualityEdit->setEnabled(true);
        saveQualityLabel->setEnabled(true);
    }

    saveQualityEdit->setText(QString::number(settings.saveQuality));

    opacityEdit->setText(QString::number(settings.opacity * 100));

    QPixmap pixmap(17, 17);
    pixmap.fill(settings.frameColor);

    frameColorImage->setPixmap(pixmap);
}

void SettingsWindow::autoSaveLabelClicked() {
    autoSaveCheckBox->toggle();
}

void SettingsWindow::autoSaveChanged() {
    if (autoSaveCheckBox->isChecked()) {
        autoSaveCheckBox->setChecked(true);
        saveDirLabel->setEnabled(true);
        saveDirEdit->setEnabled(true);
        saveDirButton->setEnabled(true);
        saveFormatLabel->setEnabled(true);
        saveFormatComboBox->setEnabled(true);
    } else {
        autoSaveCheckBox->setChecked(false);
        saveDirLabel->setEnabled(false);
        saveDirEdit->setEnabled(false);
        saveDirButton->setEnabled(false);
        saveFormatLabel->setEnabled(false);
        saveFormatComboBox->setEnabled(false);
        saveQualityEdit->setEnabled(false);
        saveQualityLabel->setEnabled(false);
    }
}

void SettingsWindow::autoCopyLabelClicked() {
    autoCopyCheckBox->toggle();
}

void SettingsWindow::soundLabelClicked() {
    soundCheckBox->toggle();
}

void SettingsWindow::saveFormatComboBoxSelected(int index) {
    if (saveFormatComboBox->itemText(index) == "png") {
        saveQualityEdit->setEnabled(false);
        saveQualityLabel->setEnabled(false);
    } else {
        saveQualityEdit->setEnabled(true);
        saveQualityLabel->setEnabled(true);
    }
}

void SettingsWindow::saveDirButtonClicked() {
    QFileDialog* dialog = new QFileDialog(this, "Выберите папку");
    dialog->setOption(QFileDialog::ShowDirsOnly);
    dialog->setFileMode(QFileDialog::Directory);

    if (dialog->exec()) {
        QString dir = dialog->selectedFiles().at(0);
        saveDirEdit->setText(dir);
    }
}

void SettingsWindow::frameColorButtonClicked() {
    QColorDialog* dialog = new QColorDialog(this);
    dialog->exec();

    if (dialog->selectedColor() != QColor::Invalid) {
        QPixmap pixmap(17, 17);
        pixmap.fill(dialog->currentColor());
        frameColorImage->setPixmap(pixmap);
    }
}

void SettingsWindow::saveClicked() {
    if (autoSaveCheckBox->isChecked()) {
        settings.autoSave = true;
        settings.saveQuality = saveQualityEdit->text().toInt();
        settings.saveDir = saveDirEdit->text();

        switch (saveFormatComboBox->currentIndex()) {
            case 0:
                settings.saveFormat = "png";
                break;
            case 1:
                settings.saveFormat = "jpg";
                break;
            case 2:
                settings.saveFormat = "gif";
                break;
        }
    } else {
        settings.autoSave = false;
    }

    if (autoCopyCheckBox->isChecked())
        settings.autoCopy = true;
    else settings.autoCopy = false;

    if (soundCheckBox->isChecked())
        settings.sound = true;
    else settings.sound = false;

    settings.opacity = opacityEdit->text().toDouble() / 100;
    settings.frameColor = frameColorImage->pixmap()->toImage().pixel(1, 1);

    emit saved(settings);
    qApp->exit();
    close();
}

void SettingsWindow::cancelClicked() {
    qApp->exit();
    close();
}

SettingsWindow::~SettingsWindow() {
    qApp->exit();
}
