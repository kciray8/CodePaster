/****************************************************************************
**
** CodePaster is program to simple and quick copy/paste snippets of code and organize it
** Copyright (C) 2013 Yaroslaw Baranow(aka KciRay).
** Contact: Yaroslaw Baranow (kciray8@gmail.com)
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
*****************************************************************************/

#ifndef CODE_H
#define CODE_H
#include <QDomElement>
#include <QDomDocument>

class Code {
    QString m_html;
    QString m_keywords;
    QString m_text;
    int m_lenght;
    int m_id;
    qint64 m_createTime;//In ms
    int m_copyCounter;
public:
    Code(QString m_html, QString m_keywords);
    Code();
    inline QString *getText() {return &m_text;}
    inline QString *getHtml() {return &m_html;}
    inline QString *getKeywords() {return &m_keywords;}
    inline int getLenght() {return m_lenght;}
    inline void setId(int id) {this->m_id = id;}
    inline int getId() {return m_id;}
    inline void incCopyCounter() {m_copyCounter++;}
    
    QDomElement getXML(QDomDocument *domDoc);
    void buildFromXML(QDomElement xml);
    void setTextFromHTML(QString html);
    void setCreateTime(qint64 createTime);
    QString getProperties();
    void copyMembers(Code* code);
};

#endif // CODE_H
