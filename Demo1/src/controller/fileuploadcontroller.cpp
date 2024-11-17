#include "fileuploadcontroller.h"

FileUploadController::FileUploadController()
{}

void FileUploadController::service(HttpRequest& request, HttpResponse& response)
{
    QFile res;
    QTextStream in(&res);
    mngr = new QNetworkAccessManager();
    if (request.getParameter("action")=="show")
    {
        QTemporaryFile* file=request.getUploadedFile("file_sprint");
        res.setFileName("C:/data/sprint.csv");
        res.open(QFile::WriteOnly);
        if (file)
        {
            while (!file->atEnd() && !file->error())
            {
                QByteArray buffer=file->read(65536);
                in << QString::fromUtf8(buffer);
            }
        }
        else
        {
            response.write("upload failed");
        }
        res.close();
        file=request.getUploadedFile("file_history");
        res.setFileName("C:/data/history.csv");
        res.open(QFile::WriteOnly);
        if (file)
        {
            while (!file->atEnd() && !file->error())
            {
                QByteArray buffer=file->read(65536);
                in << QString::fromUtf8(buffer);
            }
        }
        else
        {
            response.write("upload failed");
        }
        res.close();
        file=request.getUploadedFile("file_data");
        res.setFileName("C:/data/data.csv");
        res.open(QFile::WriteOnly);
        if (file)
        {
            while (!file->atEnd() && !file->error())
            {
                QByteArray buffer=file->read(65536);
                in << QString::fromUtf8(buffer);
            }
        }
        else
        {
            response.write("upload failed");
        }
        res.close();

    }

    QString line;
    QVector<QString> spr;
    QVector<QString> hist;
    QVector<QString> dat;
    QVector<QVector<QString>> team_data;
    QString str;
    QStringList ids;
    QStringList area;
    QStringList inf;
    QByteArray dates;
    QDate dts, dtf;
    QVector<QDate> dats;
    int count = 0;
    res.setFileName("C:/data/sprint.csv");
    if (res.open(QFile::ReadOnly | QFile::Text))
    {
        while (!in.atEnd())
        {
            line = in.readLine();
            spr.clear();
            for (QString item : line.split(";"))
            {
                spr.append(item);
            }
            sprint.append(spr);
        }
        res.close();
    }
    res.setFileName("C:/data/history.csv");
    if (res.open(QFile::ReadOnly | QFile::Text))
    {
        while (!in.atEnd())
        {
            line = in.readLine();
            spr.clear();
            for (QString item : line.split(";"))
            {
                spr.append(item);
            }
            history.append(spr);
        }
        res.close();
    }
    res.setFileName("C:/data/data.csv");
    if (res.open(QFile::ReadOnly | QFile::Text))
    {
        while (!in.atEnd())
        {
            line = in.readLine();
            spr.clear();
            for (QString item : line.split(";"))
            {
                spr.append(item);
            }
            data.append(spr);
        }
        res.close();
    }

    QByteArray page("<!DOCTYPE html>");
    page.append("<html lang=\"en\">");
    page.append("<head>");
    page.append("<meta charset=\"UTF-8\">");
    page.append("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    page.append("<link rel=\"stylesheet\" href=\"style2.css\">");
    page.append("<title>Main page</title>");
    page.append("</head>");
    page.append("<body>");

    page.append("<div class=\"navigation\">");
    page.append("<a class=\"navigation__user\" href=\"/\">");
    page.append("<svg class=\"navigation__icon\" width=\"24\" height=\"24\" viewBox=\"0 0 24 24\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\">");
    page.append("<path d=\"M10 16L6 12M6 12L10 8M6 12H18\" stroke=\"black\" stroke-width=\"1.5\" stroke-miterlimit=\"10\" stroke-linecap=\"round\" stroke-linejoin=\"round\"/>");
    page.append("</svg>");
    page.append("</a>");
    page.append("</div>");
    page.append("<div>");
    page.append("<div class=\"dataUnloading\">");
    page.append("<form class=\"menu\" method=\"post\">");
    page.append("<div class=\"menu__sprint\">");
    page.append("<h2 class=\"menu__sprint-title\">Select sprint</h2>");
    page.append("<input type=\"hidden\" name=\"action\" value=\"show1\">");

    //Сбор спринтов
    for (int i=2; i<sprint.length();i++)
    {
        spr = sprint.at(i);
        if (request.getParameter("action")=="show1")
        {
            if (request.getParameter("Sprint"+QByteArray::number(i-1))=="on")
            {
                if (count != 0){
                    dates.append(",");
                }
                page.append("<div>");
                page.append("<input type=\"checkbox\" id='sprint"+QByteArray::number(i-1)+"' name=\"Sprint"+QByteArray::number(i-1)+"\" checked/>");
                page.append("<label for=\"sprint"+QByteArray::number(i-1)+"\">"+spr.at(0)+"</label>");
                page.append("</div>");
                QString d;
                QStringList d1;
                d = spr.at(2);
                d1 = d.split(" ");
                d1 = d1.at(0).split("-");
                dts = QDate(d1.at(0).toInt(),d1.at(1).toInt(),d1.at(2).toInt());
                d = spr.at(3);
                d1 = d.split(" ");
                d1 = d1.at(0).split("-");
                dtf = QDate(d1.at(0).toInt(),d1.at(1).toInt(),d1.at(2).toInt());
                while (dts<=dtf) {
                    dats.append(dts);
                    dates.append("\"");
                    dates.append(dts.toString());
                    dts = dts.addDays(1);
                    dates.append("\"");
                    if (dts <= dtf)
                    {
                        dates.append(",");
                    }
                    count++;
                }
                d = spr.at(4);
                d = d.replace("{","");
                d = d.replace("}","");
                d1 = d.split(",");
                ids.append(d1);
            }
            else
            {
                page.append("<div>");
                page.append("<input type=\"checkbox\" id='sprint"+QByteArray::number(i-1)+"' name=\"Sprint"+QByteArray::number(i-1)+"\">");
                page.append("<label for=\"sprint"+QByteArray::number(i-1)+"\">"+spr.at(0)+"</label>");
                page.append("</div>");
            }
        }
        else
        {
            page.append("<div>");
            page.append("<input type=\"checkbox\" id='sprint"+QByteArray::number(i-1)+"' name=\"Sprint"+QByteArray::number(i-1)+"\">");
            page.append("<label for=\"sprint"+QByteArray::number(i-1)+"\">"+spr.at(0)+"</label>");
            page.append("</div>");
        }
    }

    page.append("</div>");
    page.append("<div class=\"menu__command\">");
    page.append("<h2 class=\"menu__command-title\">Select command</h2>");

    //Сбор команд
    for (int i=2; i<data.length();i++)
    {
        dat = data.at(i);
        if (request.getParameter("Command"+QByteArray::number(i-1))=="on")
        {
            team_data.append(dat);
        }
        if (area.indexOf(dat.at(1))==-1)
        {
            area.append(dat.at(1));
            if (request.getParameter("action")=="show1")
            {
                if (request.getParameter("Command"+QByteArray::number(i-1))=="on")
                {
                    page.append("<div>");
                    page.append("<input type=\"checkbox\" id='command"+QByteArray::number(i-1)+"' name=\"Command"+QByteArray::number(i-1)+"\" checked/>");
                    page.append("<label for=\"command"+QByteArray::number(i-1)+"\">"+dat.at(1)+"</label>");
                    page.append("</div>");
                }
                else
                {
                    page.append("<div>");
                    page.append("<input type=\"checkbox\" id='command"+QByteArray::number(i-1)+"' name=\"Command"+QByteArray::number(i-1)+"\">");
                    page.append("<label for=\"command"+QByteArray::number(i-1)+"\">"+dat.at(1)+"</label>");
                    page.append("</div>");
                }
            }
            else
            {
                page.append("<div>");
                page.append("<input type=\"checkbox\" id='command"+QByteArray::number(i-1)+"' name=\"Command"+QByteArray::number(i-1)+"\">");
                page.append("<label for=\"command"+QByteArray::number(i-1)+"\">"+dat.at(1)+"</label>");
                page.append("</div>");
            }
        }
    }

    page.append("</div>");
    page.append("<button class=\"form__btn\" id=\"files__btn\">View</button>");
    page.append("</form>");
    page.append("<div class=\"slider\">");
    page.append("<div class=\"slider__date\">");
    page.append("<span class=\"date\"></span>");
    page.append("</div>");

    QVector<QVector<QString>> chang;
    for (int i=0; i<history.length(); i++)
    {
        hist = history.at(i);
        int c=0;
        for (int j=0; j<chang.length(); j++)
        {
            if(hist.at(0) == chang.at(j).at(0)){
                c++;
            }
        }
        if (c == 0){
            QVector<QString> l;
            l.append(hist.at(0));
            l.append("1");
        }
        else
        {
            for (int j=0; j<chang.length(); j++)
            {
                if (hist.at(0) == chang.at(j).at(0))
                {
                    QString s = chang.at(j).at(1);
                    int l = s.toInt();
                    l++;
                    QVector<QString> li;
                    li.append(chang.at(j).at(0));
                    li.append(QString(l));
                    chang.insert(j, li);
                }
            }
        }

    }

    //Сбор графиков
    area.clear();
    if (request.getParameter("action")=="show1")
    {
        for (int i=0; i<count; i++)
        {
            if (i==0)
            {
                page.append("<div class=\"slider__img active\">");
                for (int j=0; j < team_data.length(); j++)
                {
                    QVector<QString> team = team_data.at(j);
                    QString d;
                    QStringList d1;
                    d = team.at(10);
                    d1 = d.split(" ");
                    d1 = d1.at(0).split("-");
                    dts = QDate(d1.at(0).toInt(),d1.at(1).toInt(),d1.at(2).toInt());
                    if (dats.at(i) == dts and area.indexOf(team.at(1))==-1)
                    {
                        area.append(team.at(1));
                        page.append("<label for="" class=\"slider__img-command\">"+team.at(1)+"</label>");
                        for (int k=0; k<ids.length(); k++)
                        {
                            if (ids.at(k) == team.at(0))
                            {
                                QString parant = team.at(12);
                                for (int t=0; t<history.length(); t++)
                                {
                                    hist = history.at(t);
                                    if(parant == hist.at(0))
                                    {
                                        page.append("<p class=\"slider__img-text\">"+hist.at(0)+"</p>");
                                    }
                                }
                            }
                        }
                        page.append("<div class=\"slider__img-health\">");
                        page.append("<p class=\"slider__img-text\"></p>");
                        page.append("<img src=\"./istockphoto-450233085-612x612.jpg\" class=\"slider__img-img\">");
                        page.append("</div>");
                    }
                }
                page.append("</div>");
            }
            else
            {
                page.append("<div class=\"slider__img\">");
                for (int j=0; j < team_data.length(); j++)
                {
                    QVector<QString> team = team_data.at(j);
                    QString d;
                    QStringList d1;
                    d = team.at(10);
                    d1 = d.split(" ");
                    d1 = d1.at(0).split("-");
                    dts = QDate(d1.at(0).toInt(),d1.at(1).toInt(),d1.at(2).toInt());
                    if (dats.at(i) == dts and area.indexOf(team.at(1))==-1)
                    {
                        area.append(team.at(1));
                        page.append("<label for="" class=\"slider__img-command\">"+team.at(1)+"</label>");
                        for (int k=0; k<ids.length(); k++)
                        {
                            if (ids.at(k) == team.at(0))
                            {
                                QString parant = team.at(12);
                                for (int t=0; t<history.length(); t++)
                                {
                                    hist = history.at(t);
                                    if(parant == hist.at(0))
                                    {
                                        page.append("<p class=\"slider__img-text\">"+hist.at(1)+"</p>");
                                    }
                                }
                            }
                        }
                        page.append("<div class=\"slider__img-health\">");
                        page.append("<p class=\"slider__img-text\"></p>");
                        page.append("<img src=\"./istockphoto-450233085-612x612.jpg\" class=\"slider__img-img\">");
                        page.append("</div>");
                    }
                }
                page.append("</div>");
            }
        }
    }

    page.append("<span class=\"arrow arrow-left\">");
    page.append("<svg class=\"slider__icon icon-left\" width=\"11\" height=\"14\" viewBox=\"0 0 11 14\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\">");
    page.append("<path d=\"M0 0V14L11 7L0 0Z\" fill=\"black\"/>");
    page.append("</svg>");
    page.append("</span>");
    page.append("<span class=\"arrow arrow-right\">");
    page.append("<svg class=\"slider__icon icon-right\" width=\"11\" height=\"14\" viewBox=\"0 0 11 14\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\">");
    page.append("<path d=\"M0 0V14L11 7L0 0Z\" fill=\"black\"/>");
    page.append("</svg>");
    page.append("</span>");
    page.append("</div>");
    page.append("</div>");
    page.append("</div>");
    page.append("</div>");

    page.append("<script>");
    page.append("const slides = document.querySelectorAll('.slider__img');");
    page.append("const dates = document.querySelectorAll('.date');");
    page.append("const leftArrow = document.querySelector('.arrow-left');");
    page.append("const rightArrow = document.querySelector('.arrow-right');");

    page.append("let currentSlide = 0;");
    page.append("const totalSlides = "+QByteArray::number(count)+";");
    page.append("let arr = ["+dates+"];");

    page.append("function updateDate() {");
    page.append("const dateSpan = document.querySelector('.slider__date .date');");
    page.append("dateSpan.textContent = arr[currentSlide];");
    page.append("}");

    page.append("leftArrow.addEventListener('click', () => {");
    page.append("currentSlide = (currentSlide - 1 + totalSlides) % totalSlides;");
    page.append("updateSlide();");
    page.append("});");

    page.append("rightArrow.addEventListener('click', () => {");
    page.append("currentSlide = (currentSlide + 1) % totalSlides;");
    page.append("updateSlide();");
    page.append("});");

    page.append("dates.forEach((date, index) => {");
    page.append("date.addEventListener('click', () => {");
    page.append("currentSlide = index;");
    page.append("updateSlide();");
    page.append("});");
    page.append("});");

    page.append("function updateSlide() {");
    page.append("slides.forEach((slide, index) => {");
    page.append("slide.classList.remove('active');");
    page.append("if (index === currentSlide) {");
    page.append("slide.classList.add('active');");
    page.append("}");
    page.append("});");
    page.append("dates.forEach((date, index) => {");
    page.append("date.classList.remove('active');");
    page.append("if (index === currentSlide) {");
    page.append("date.classList.add('active');");
    page.append("}");
    page.append("});");
    page.append("updateDate();");
    page.append("}");

    page.append("updateSlide();");
    page.append("</script>");

    page.append("</body>");
    page.append("</html>");

    response.write(page,true);
}

