#include "fileuploadcontroller.h"

FileUploadController::FileUploadController()
{}

void FileUploadController::service(HttpRequest& request, HttpResponse& response)
{
    QFile res;
    QTextStream in(&res);
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
    page.append("<h1 class=\"navigation__user\"><a href=\"./\"> exit</a></h1>");
    page.append("<h1 class=\"navigation__user\">user</h1>");
    page.append("</div>");
    page.append("<div class=\"container\">");
    page.append("<div class=\"dataUnloading\">");
    page.append("<form class=\"menu\" method=\"post\">");
    page.append("<div class=\"menu__sprint\">");
    page.append("<h2 class=\"menu__sprint-title\">Select sprint</h2>");
    page.append("<input type=\"hidden\" name=\"action\" value=\"show1\">");

    //Сбор спринтов
    for (int i=2; i<sprint.length();i++)
    {
        spr = sprint.at(i);
        page.append("<div>");
        page.append("<input type=\"checkbox\" id='sprint"+QByteArray::number(i-1)+"' name=\"Sprint"+QByteArray::number(i-1)+"\">");
        page.append("<label for=\"sprint"+QByteArray::number(i-1)+"\">"+spr.at(0)+"</label>");
        page.append("</div>");
    }

    page.append("</div>");
    /*page.append("<div class=\"menu__command\">");
    page.append("<h2 class=\"menu__command-title\">Select command</h2>");

    //Сбор команд


    page.append("</div>");*/
    page.append("</form>");
    page.append("<div class=\"slider\">");
    page.append("<div class=\"slider__date\">");
    page.append("<span class=\"date\"></span>");
    page.append("</div>");

    //Сбор графиков
    if (request.getParameter("action")=="show1")
    {
        QString str = request.getHeader("sprint1");
        page.append(str);
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
    page.append("const totalSlides = slides.length;");

    page.append("function updateDate() {");
    page.append("const dateSpan = document.querySelector('.slider__date .date');");
    page.append("dateSpan.textContent = currentSlide + 1;");
    page.append("}");

    page.append("leftArrow.addEventListener('click', () => {");
    page.append("currentSlide = (currentSlide - 1 + totalSlides) % totalSlides;");
    page.append(" updateSlide();");
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

