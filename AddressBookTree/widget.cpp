#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QStandardItemModel>
#include "CCompanyAddrBookModel.h"
#include <QMap>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    model = new CCompanyAddrBookModel();

    CCompanyAddrBookItem* child1 = new CDepartment("江苏");
    child1->setID("11");
    model->getRootItem()->appendChild(child1);
    map.insert("11", child1);

    CCompanyAddrBookItem* child2 = new CDepartment("浙江");
    child2->setID("12");
    model->getRootItem()->appendChild(child2);
    ui->treeView->setModel(model);

    ui->treeView->setHeaderHidden(true);

    connect(ui->treeView, &QTreeView::doubleClicked,this, &Widget::onTreeClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onTreeClicked(const QModelIndex& index){
    if (!index.isValid()){
        return;
    }

    CCompanyAddrBookItem* item = model->getItem(index);
    if (!item){
        return;
    }

    if (item->childCount() > 0){
        return;
    }

    QString id = item->getID();
    if (id == "11"){
        CCompanyAddrBookItem* child11 = new CDepartment("南京");
        child11->setID("111");
        item->appendChild(child11);
        CCompanyAddrBookItem* child12 = new CDepartment("苏州");
        child12->setID("112");
        item->appendChild(child12);
    }
    else if (id == "111"){
        CCompanyAddrBookItem* child111 = new CContact("张三");
        child111->setID("1111");
        item->appendChild(child111);
        CCompanyAddrBookItem* child112 = new CContact("李四");
        child112->setID("1112");
        item->appendChild(child112);
    }
}


