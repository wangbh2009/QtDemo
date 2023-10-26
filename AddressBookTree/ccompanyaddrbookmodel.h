#ifndef CCOMPANYADDRBOOKMODEL_H
#define CCOMPANYADDRBOOKMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QSharedPointer>

class CCompanyAddrBookModel;
class CCompanyAddrBookItem{
public:
    CCompanyAddrBookItem(QString data);
    typedef QSharedPointer<CCompanyAddrBookItem> CCompanyAddrBookItemPtr;

    int  childPosition(const CCompanyAddrBookItem *item) const;

    int  childCount() const;

    CCompanyAddrBookItem           *child(int number);
    const CCompanyAddrBookItem     *child(int number) const;

    virtual QVariant data(int pos, int role)const;

    void appendChild(CCompanyAddrBookItem* item);

    void setParent(CCompanyAddrBookItem* parent);

    void setModel(CCompanyAddrBookModel* model);

    QModelIndex index() const;

    QString getID()const{
        return mID;
    }
    void setID(QString id){
        mID = id;
    }

    CCompanyAddrBookItem           *parent();
    const CCompanyAddrBookItem     *parent() const;
private:
    QString mData;
    QString mID;
    QList<CCompanyAddrBookItemPtr> children;
    CCompanyAddrBookModel* mAddrBookModel;
    CCompanyAddrBookItem*  mParent;

};

class CDepartment : public CCompanyAddrBookItem{
public:
    CDepartment(QString data)
        :CCompanyAddrBookItem(data)
    {
    }
};

class CContact : public CCompanyAddrBookItem{
public:
    CContact(QString data)
        :CCompanyAddrBookItem(data)
    {
    }
};

class CCompanyAddrBookModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    CCompanyAddrBookModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex &child) const override;

    CCompanyAddrBookItem* getRootItem() const;

    CCompanyAddrBookItem* getItem(const QModelIndex &index) const;
private:
    QModelIndex indexFromItem(const CCompanyAddrBookItem *item) const;

    QSharedPointer<CCompanyAddrBookItem>   rootItem;

    friend class CCompanyAddrBookItem;
};

#endif // CCOMPANYADDRBOOKMODEL_H
