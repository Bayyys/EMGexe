#ifndef WORDENGINE_H
#define WORDENGINE_H

#include <QObject>
#include <QAxWidget>
#include <QAxObject>

class WordEngine :public QObject
{
    Q_OBJECT
public:
    explicit WordEngine(QObject *parent = 0);

public slots:
    bool open(const QString &file);//打开文档
    void save(const QString &savePath);//保存并关闭文档

    void replaceText(const QString &label,const QString &text);//替换文档中标签出的文字
    void alterTableRowCount(const QString &tabel, const int rowCount);//在表个中添加新行
    void fillTableCell(const QString &tabel,const QList<QStringList> &data);//填充表格内容

private:
    QAxWidget *_word;//word主程序
    QAxObject *_workDocument;//工作簿
    bool _isOpen;//文档打开状态

    QMap<QString,int> _tabelIndex;//文档中的表格索引，注意word中表格的索引值是从1开始的，这里根据不同的情况单独实现
};

#endif // WORDENGINE_H
