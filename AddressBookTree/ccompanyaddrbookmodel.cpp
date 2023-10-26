#include "ccompanyaddrbookmodel.h"
#include <QDebug>

CCompanyAddrBookItem::CCompanyAddrBookItem(QString data)
    :mData(data),mParent(nullptr)
{
}

int CCompanyAddrBookItem::childPosition(const CCompanyAddrBookItem *item) const
{
    int result = -1;
    for(int i = 0; i < children.size(); ++i)
    {
        if(children[i].data() == item)
        {
            result = i;
            break;
        }
    }
    return result;
}

void CCompanyAddrBookItem::appendChild(CCompanyAddrBookItem* item)
{
    int pos = children.size();
    QModelIndex i = index();
    mAddrBookModel->beginInsertRows(i,pos,pos);
    item->setParent(this);
    item->setModel(mAddrBookModel);
    children.append((CCompanyAddrBookItemPtr)item);
    mAddrBookModel->endInsertRows();
}

void CCompanyAddrBookItem::setParent(CCompanyAddrBookItem* parent)
{
    mParent = parent;
}

void CCompanyAddrBookItem::setModel(CCompanyAddrBookModel* model)
{
    mAddrBookModel = model;
}

CCompanyAddrBookItem* CCompanyAddrBookItem::parent()
{
    return mParent;
}
const CCompanyAddrBookItem* CCompanyAddrBookItem::parent() const
{
    return mParent;
}

int CCompanyAddrBookItem::childCount() const
{
    return children.size();
}

CCompanyAddrBookItem* CCompanyAddrBookItem::child(int number)
{
    return const_cast<CCompanyAddrBookItem *>(static_cast<const CCompanyAddrBookItem &>(*this).child(number));
}
const CCompanyAddrBookItem* CCompanyAddrBookItem::child(int number) const
{
    return children.value(number).data();
}

QVariant CCompanyAddrBookItem::data(int pos, int role)const
{
    if (role == Qt::DisplayRole){
        return mData;
    }else{
        return QVariant();
    }
}


QModelIndex CCompanyAddrBookItem::index() const
{
    if(!mAddrBookModel){
        return QModelIndex();
    }

    return mAddrBookModel->indexFromItem(this);
}

CCompanyAddrBookModel::CCompanyAddrBookModel()
    :rootItem(new CCompanyAddrBookItem(""))
{
    rootItem->setModel(this);
}

CCompanyAddrBookItem *CCompanyAddrBookModel::getItem(const QModelIndex &index) const
{
    return index.isValid() ?
               static_cast<CCompanyAddrBookItem*>(index.internalPointer()) :
               rootItem.data();
}

int CCompanyAddrBookModel::rowCount(const QModelIndex &parent) const{
    CCompanyAddrBookItem *item = getItem(parent);
    if (!item){
        return 0;
    }
    return item->childCount();
}

int CCompanyAddrBookModel::columnCount(const QModelIndex &parent) const{
    return 1;
}

QVariant CCompanyAddrBookModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid()){
        return QVariant();
    }

    CCompanyAddrBookItem *item = getItem(index);
    if (!item){
        return QVariant();
    }

    return item->data(index.column(), role);
}

QModelIndex CCompanyAddrBookModel::index(int row, int column, const QModelIndex &parent) const{
    if(!hasIndex(row, column, parent)){
        return QModelIndex();
    }

    CCompanyAddrBookItem *parentItem = getItem(parent);
    if (!parentItem){
        return QModelIndex();
    }

    CCompanyAddrBookItem *childItem = parentItem->child(row);
    if (!childItem){
        return QModelIndex();
    }
    return createIndex(row, column, childItem);
}

QModelIndex CCompanyAddrBookModel::parent(const QModelIndex &child) const{
    if (!child.isValid()){
        return QModelIndex();
    }

    CCompanyAddrBookItem *childItem = getItem(child);
    if(!childItem){
        return QModelIndex();
    }

    CCompanyAddrBookItem *parentItem = childItem->parent();
    if (!parentItem || parentItem == rootItem){
        return QModelIndex();
    }

    CCompanyAddrBookItem *grandParent = parentItem->parent();
    if(!grandParent){
        return QModelIndex();
    }

    return createIndex(grandParent->childPosition(parentItem), 0, parentItem);
}

QModelIndex CCompanyAddrBookModel::indexFromItem(const CCompanyAddrBookItem *item) const
{
    if(!item){
        return QModelIndex();
    }

    if(item == rootItem.data()){
        return QModelIndex();
    }

    return createIndex(item->parent()->childPosition(item), 0, const_cast<CCompanyAddrBookItem *>(item));
}

CCompanyAddrBookItem* CCompanyAddrBookModel::getRootItem() const
{
    return rootItem.data();
}

