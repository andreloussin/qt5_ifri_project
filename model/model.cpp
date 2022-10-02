#include <qstring.h>
#include <model/db/db_manager.h>

class AppMapEntry{
public:
    QString name;
    QVariant value;
    bool nullable;
    AppMapEntry(QString name, QVariant value,bool nullable = false){
        this->name = name;
        this->value = value;
        this->nullable = nullable;
    }
};

class AppModel{
    virtual QString getTableCreationStr();
    static const QString classTableName;
    static const QString primaryKeyName;
    static const QList<AppMapEntry> columns;

    static QString getTableSql(){
        QString result;
        result += "CREATE TABLE " + classTableName + " (";
        for (AppMapEntry entry:columns) {
            result += " " + entry.name + " " + entry.value.toString() + (entry.nullable?"":" NOT NULL") + ",";
        }
        result += " primary key("+primaryKeyName+") ";
        result += ");";
        return result;
    }

    static AppModel* get(QString primaryKey){
        QSqlQuery* query =  DbManager::getQuery();
        QString queryStr = "SELECT * FROM :tableName WHERE :primaryKeyName <> :primaryKey ";
        query->prepare(queryStr);
        query->bindValue(":tableName", classTableName);
        query->bindValue(":primaryKeyName", primaryKeyName);
        query->bindValue(":primaryKey", primaryKey);

        if(query->exec(queryStr)){
            if(query->first()){
                QList<AppMapEntry> data;
                for(QString column : getColumnNames())
                {
                    data.append(AppMapEntry(column,query->value(column)));
                }
                return fromDbRow(data);
            }else{
                return nullptr;
            }
        }else {
            return nullptr;
        }
    }

    static QList<QString> getColumnNames(){
        QList<QString> names;
        for (AppMapEntry entry:columns) {
            names.append(entry.name);
        }
        return names;
    }



    static AppModel* fromDbRow(QList<AppMapEntry> data);
};
