
#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QMimeData>
#include <QVariant>
#include <QUuid>
#include <QMap>

class TrackItem;

class TrackTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum GroupColumn
    {
        GroupColumn_Name = 0,
        GroupColumn_UUID,
        GroupColumn_Size
    };
    enum SampleColumn
    {
        SampleColumn_Name = 0,
        SampleColumn_DefaultFile,
        SampleColumn_StartTime,
        SampleColumn_Frequency,
        SampleColumn_Probability,
        SampleColumn_VolumeMultiplier,
        SampleColumn_GroupUUID,
        SampleColumn_Size
    };

public:
    TrackTreeModel(QObject *parent = nullptr);
    ~TrackTreeModel();

    void addSample(const QVector<QVariant> &data, const QUuid &uuid);
    void addGroup(const QVector<QVariant> &data, const QUuid &uuid);

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    Qt::DropActions supportedDropActions () const override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool dropMimeData( const QMimeData * data, Qt::DropAction action,
                                            int row, int column, const QModelIndex & parent) override;
    QVariant headerData(int section, Qt::Orientation orientation,
                           int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                         const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;

    void setIsGroup(const QModelIndex &index);
    QUuid getUuid(const QModelIndex &index) const;
    void setUuid(const QModelIndex &index, const QUuid &uuid) const;
    bool isGroup(const QModelIndex &index) const;
    void setFilePath(const QString &filePath);
    QString getFilePath() const;
    const TrackItem *getRoot() const;

private:
    TrackItem *getItemSafe(const QModelIndex &index) const;
    TrackItem *getItemUnsafe(const QModelIndex &index);
    TrackItem *getGroup(const QUuid &uuid) const;
    void removeGroup(const QUuid &uuid);

private:
    QMap<QUuid, TrackItem*> m_groups;
    QString m_filePath;
    TrackItem *m_rootItem;

};
