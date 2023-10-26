#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class CCompanyAddrBookModel;
class CCompanyAddrBookItem;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void onTreeClicked(const QModelIndex& index);

private:
    Ui::Widget *ui;
    CCompanyAddrBookModel *model;
    QMap<QString, CCompanyAddrBookItem*> map;
};
#endif // WIDGET_H
