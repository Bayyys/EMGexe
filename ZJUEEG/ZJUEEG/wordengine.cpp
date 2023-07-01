#include "wordengine.h"
#include "qt_windows.h"
#include <QMessageBox>
#include "mainwindow.h"
WordEngine::WordEngine(QObject *parent) : QObject(parent)
{
    HRESULT result = OleInitialize(0);

        if (result != S_OK && result != S_FALSE)
        {
            qDebug()<<QString("Could not initialize OLE (error %x)").arg((unsigned int)result);
        }
        //moveToThread方法产生线程
        //this->moveToThread(&m_thread);
        //m_thread.start();

}

/// Summary:根据传入的模板文件地址创建新的word文档并打开
/// parameters:
///     file：.dot模板文件的绝对地址，这里只能使用绝对地址，否则找不到文件，并且建议使用QDir::toNativeSeparators()将地址中的'/'转换成'\'
/// return:
///     文档是否打开
bool WordEngine::open(const QString& file)
{
    _word = new QAxWidget("word.Application");
    QAxObject *document = _word->querySubObject("Documents");//获取所有打开的文档
    if (!document)
        return false;

    document->dynamicCall("Add(QString)",file);//使用模板文件创建新的文档
    _workDocument = _word->querySubObject("ActiveDocument");//激活文档

    if (_workDocument)
        _isOpen = true;
    else
        _isOpen = false;

    if (!_isOpen)
    {
        QMessageBox box(QMessageBox::Information,QString("提示"),QString("未找到模板文件：%0").arg(file));
        box.addButton(QString("确定"),QMessageBox::AcceptRole);
        box.exec();
    }

    return _isOpen;
}

/// Summary:将文档保存到指定地址，并关闭word程序
/// parameters:
///     savePath：word的保存地址
void WordEngine::save(const QString &savePath)
{
    //保存
    if (_isOpen && _workDocument)
    {
        _workDocument->dynamicCall("SaveAs (const QString&)",savePath);
    }

    if (_word)
    {
        _word->setProperty("DisplayAlerts",true);
    }

    //关闭文档
    if (_workDocument)
    {
        _workDocument->dynamicCall("Close(bool)",true);
        delete _workDocument;
        _workDocument = NULL;
    }

    //推出word程序
    if (_word)
    {
        _word->dynamicCall("Quit()");
        delete _word;
        _word = NULL;
    }

    _isOpen = false;
}

/// Summary:替换指定书签处的内容
/// parameters:
///     label:书签名称，这里的书签对应的是在word中的插入->书签
///     text:内容
void WordEngine::replaceText(const QString &label, const QString &text)
{
    if (!_workDocument)
        return ;

    //查找书签
    QAxObject *bookmark = _workDocument->querySubObject("Bookmarks(QString)",label);
    if (bookmark)
    {
        //选定书签，并替换内容
        bookmark->dynamicCall("Select(void)");
        bookmark->querySubObject("Range")->setProperty("Text",text);
        delete bookmark;
    }
}

/// Summary:调整表格行数，目前只能插入不能删除，在word模板中，在表格中至少需要有一行内容空行，否则在插入新行的时候，数据内容会跟随表头行的格式，有时候导出结果会非常难看
/// parameters:
///     tabel:表格名称
///     rowCount:行数
void WordEngine::alterTableRowCount(const QString &tabel, const int rowCount)
{
    if (NULL == _workDocument) return;
    QAxObject *table = _workDocument->querySubObject("Tables(int)",_tabelIndex.value(tabel));//获取表格
    if (NULL == table) return;

    //获取表格目前的行数
    QAxObject *rows = table->querySubObject("Rows");
    qint32 count = rows->dynamicCall("Count").toInt();

    //插入行
    for (int i = count - 1; i < rowCount; ++i)
    {
        rows->querySubObject("Add()");
    }
}

/// Summary:填充表格内容
/// parameters:
///     tabel:表格名称
///     data:内容
void WordEngine::fillTableCell(const QString &tabel, const QList<QStringList> &data)
{
    if (NULL == _workDocument) return;
    QAxObject *table = _workDocument->querySubObject("Tables(int)",_tabelIndex.value(tabel));//获取表格
    if (NULL == table) return;

    //获取表格目前的行数
    QAxObject *rows = table->querySubObject("Rows");
    qint32 rowCount = rows->dynamicCall("Count").toInt();

    //获取表格目前的列数
    QAxObject *columns = table->querySubObject("Columns");
    qint32 columnCount = columns->dynamicCall("Count").toInt();

    //当前表格行数小于数据的行数，调整到数据的行数
    if (data.size()>rowCount)
    {
        alterTableRowCount(tabel,data.size());
    }

    //填充表格内容
    for (int row = 0; row < data.size(); ++row)
    {
        for (int column = 0; column < data.at(row).size() && column < columnCount; ++column)
        {
            QAxObject *cell=table->querySubObject("Cell(int,int)",row+2,column+1);//获取单元格，注意word中的索引是从1开始的，再加上表头row应该+2
            if(!cell) return;
            cell->dynamicCall("Select(void)");
            cell->querySubObject("Range")->setProperty("Text",data.at(row).at(column));
            delete cell;
        }
    }
}
