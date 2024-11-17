#include "dumpcontroller.h"
#include <QVariant>
#include <QDateTime>
#include <QThread>
#include <QSql>
#include <QSqlDatabase>

DumpController::DumpController()
{}

void DumpController::service(HttpRequest& request, HttpResponse& response)
{    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.db");
    if (!db.open()){
        response.write("Database don't open",true);
    }
    else{
        QByteArray page("<html lang=\"en\"><head>");
        page.append("<meta charset=\"UTF-8\">");
        page.append("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
        page.append("<link rel=\"stylesheet\" href=\"./style.css\">");
        page.append("<title>Registration</title>");
        page.append("</head><body>");
        page.append("<div class=\"container\">");
        page.append("<form action=\"\" class=\"form\">");
        page.append("<svg width=\"24\" height=\"24\" viewBox=\"0 0 24 24\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\" class=\"form__icon\">");
        page.append("<path d=\"M15 14C12.33 14 7 15.33 7 18V20H23V18C23 15.33 17.67 14 15 14ZM6 10V7H4V10H1V12H4V15H6V12H9V10M15 12C16.0609 12 17.0783 11.5786 17.8284 10.8284C18.5786 10.0783 19 9.06087 19 8C19 6.93913 18.5786 5.92172 17.8284 5.17157C17.0783 4.42143 16.0609 4 15 4C13.9391 4 12.9217 4.42143 12.1716 5.17157C11.4214 5.92172 11 6.93913 11 8C11 9.06087 11.4214 10.0783 12.1716 10.8284C12.9217 11.5786 13.9391 12 15 12Z\" fill=\"black\"/>");
        page.append("</svg>");
        page.append("<div class=\"form__titles\">");
        page.append("<h1 class=\"form__title\">Registration</h1>");
        page.append("<p class=\"form__subtitle\">Be one of thousands of teams using SprintHealth. Start your free trial now.</p>");
        page.append("</div>");

        page.append("<div class=\"form__inputs\">");

        page.append("<label for=\"name-input\" class=\"form__text\">Имя</label>");
        page.append("<input type=\"text\" class=\"form__input\" id=\"name-input\">");
        page.append("<span id=\"name-error\" class=\"form__error\"></span>");

        page.append("<label for=\"surname-input\" class=\"form__text\">Фамилия</label>");
        page.append("<input type=\"text\" class=\"form__input\" id=\"surname-input\">");
        page.append("<span id=\"surname-error\" class=\"form__error\"></span>");

        page.append("<label for=\"patronymic-input\" class=\"form__text\">Отчество</label>");
        page.append("<input type=\"text\" class=\"form__input\" id=\"patronymic-input\">");
        page.append("<span id=\"patronymic-error\" class=\"form__error\"></span>");

        page.append("<label for=\"email-input\" class=\"form__text\">Email</label>");
        page.append("<input type=\"email\" class=\"form__input\" id=\"email-input\">");
        page.append("<span id=\"email-error\" class=\"form__error\"></span>");

        page.append("<label for=\"login-input\" class=\"form__text\">Login</label>");
        page.append("<input type=\"login\" class=\"form__input\" id=\"login-input\">");
        page.append("<span id=\"login-error\" class=\"form__error\"></span>");

        page.append("<label for=\"password-input\" class=\"form__text\">Password</label>");
        page.append("<div class=\"password__input\">");
        page.append("<input type=\"password\" id=\"password-input\" class=\"form__input\">");
        page.append("<svg width=\"18\" height=\"10\" viewBox=\"0 0 18 10\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\" id=\"icon-eye\" class=\"form__icon-eye\">");
        page.append("<path d=\"M0.0500398 1.31001C0.00753229 1.18307 -0.00905319 1.04888 0.00126676 0.915406C0.0115867 0.781931 0.0486021 0.651887 0.110118 0.532984C0.171634 0.414082 0.256398 0.308741 0.359384 0.223209C0.462371 0.137676 0.581483 0.0736927 0.709658 0.0350526C0.837834 -0.00358758 0.972463 -0.0160978 1.10556 -0.00173683C1.23866 0.0126241 1.36753 0.0535638 1.48451 0.118655C1.60149 0.183747 1.70422 0.271666 1.78659 0.377198C1.86896 0.482729 1.9293 0.603726 1.96404 0.733013C4.05004 7.71901 13.946 7.72001 16.034 0.737014C16.0715 0.611076 16.1333 0.493743 16.2161 0.391714C16.2989 0.289686 16.4009 0.204959 16.5165 0.142372C16.632 0.0797857 16.7587 0.0405647 16.8894 0.0269483C17.02 0.0133318 17.1521 0.0255866 17.278 0.0630134C17.404 0.10044 17.5213 0.162306 17.6233 0.245078C17.7254 0.32785 17.8101 0.429908 17.8727 0.545424C17.9353 0.66094 17.9745 0.787652 17.9881 0.918326C18.0017 1.049 17.9895 1.18108 17.952 1.30701C17.5884 2.5583 16.9713 3.7214 16.139 4.72401L17.414 6.00001C17.5962 6.18862 17.697 6.44122 17.6947 6.70342C17.6924 6.96561 17.5873 7.21642 17.4019 7.40183C17.2165 7.58724 16.9656 7.69241 16.7034 7.69469C16.4412 7.69697 16.1886 7.59617 16 7.41401L14.689 6.10301C13.9816 6.63672 13.2 7.06423 12.369 7.37201L12.726 8.70701C12.7641 8.83506 12.7762 8.96945 12.7615 9.10223C12.7467 9.23501 12.7056 9.3635 12.6404 9.4801C12.5752 9.59671 12.4873 9.69907 12.3819 9.78114C12.2764 9.86321 12.1557 9.92333 12.0266 9.95794C11.8976 9.99255 11.7629 10.001 11.6306 9.98267C11.4983 9.96437 11.3709 9.91975 11.2561 9.85143C11.1413 9.78311 11.0414 9.69248 10.9622 9.58489C10.883 9.4773 10.8262 9.35493 10.795 9.22501L10.431 7.86801C9.48404 8.00801 8.51604 8.00801 7.56904 7.86801L7.20504 9.22501C7.17392 9.35493 7.11709 9.4773 7.03789 9.58489C6.9587 9.69248 6.85875 9.78311 6.74395 9.85143C6.62914 9.91975 6.50181 9.96437 6.36948 9.98267C6.23714 10.001 6.10248 9.99255 5.97345 9.95794C5.84442 9.92333 5.72363 9.86321 5.61822 9.78114C5.51281 9.69907 5.42491 9.59671 5.35971 9.4801C5.29451 9.3635 5.25334 9.23501 5.23863 9.10223C5.22392 8.96945 5.23596 8.83506 5.27404 8.70701L5.63104 7.37201C4.79998 7.06392 4.0184 6.63607 3.31104 6.10201L2.00104 7.41401C1.81353 7.60179 1.55911 7.70738 1.29375 7.70757C1.02838 7.70776 0.773813 7.60252 0.58604 7.41501C0.398267 7.22751 0.292671 6.97309 0.292484 6.70772C0.292296 6.44236 0.397532 6.18779 0.58504 6.00001L1.86004 4.72501C1.07604 3.78901 0.45004 2.65101 0.04804 1.31101L0.0500398 1.31001Z\" fill=\"#430909\"/>");
        page.append("</svg>");
        page.append("</div>");
        page.append("<span id=\"password-error\" class=\"form__error\"></span>");

        page.append("<label for=\"password-input\" class=\"form__text\">Repeat password</label>");
        page.append("<div class=\"password__input\">");
        page.append("<input type=\"password\" id=\"repPassword-input\" class=\"form__input\">");
        page.append("<svg width=\"18\" height=\"10\" viewBox=\"0 0 18 10\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\" id=\"re-icon-eye\" class=\"form__icon-eye\">");
        page.append("<path d=\"M0.0500398 1.31001C0.00753229 1.18307 -0.00905319 1.04888 0.00126676 0.915406C0.0115867 0.781931 0.0486021 0.651887 0.110118 0.532984C0.171634 0.414082 0.256398 0.308741 0.359384 0.223209C0.462371 0.137676 0.581483 0.0736927 0.709658 0.0350526C0.837834 -0.00358758 0.972463 -0.0160978 1.10556 -0.00173683C1.23866 0.0126241 1.36753 0.0535638 1.48451 0.118655C1.60149 0.183747 1.70422 0.271666 1.78659 0.377198C1.86896 0.482729 1.9293 0.603726 1.96404 0.733013C4.05004 7.71901 13.946 7.72001 16.034 0.737014C16.0715 0.611076 16.1333 0.493743 16.2161 0.391714C16.2989 0.289686 16.4009 0.204959 16.5165 0.142372C16.632 0.0797857 16.7587 0.0405647 16.8894 0.0269483C17.02 0.0133318 17.1521 0.0255866 17.278 0.0630134C17.404 0.10044 17.5213 0.162306 17.6233 0.245078C17.7254 0.32785 17.8101 0.429908 17.8727 0.545424C17.9353 0.66094 17.9745 0.787652 17.9881 0.918326C18.0017 1.049 17.9895 1.18108 17.952 1.30701C17.5884 2.5583 16.9713 3.7214 16.139 4.72401L17.414 6.00001C17.5962 6.18862 17.697 6.44122 17.6947 6.70342C17.6924 6.96561 17.5873 7.21642 17.4019 7.40183C17.2165 7.58724 16.9656 7.69241 16.7034 7.69469C16.4412 7.69697 16.1886 7.59617 16 7.41401L14.689 6.10301C13.9816 6.63672 13.2 7.06423 12.369 7.37201L12.726 8.70701C12.7641 8.83506 12.7762 8.96945 12.7615 9.10223C12.7467 9.23501 12.7056 9.3635 12.6404 9.4801C12.5752 9.59671 12.4873 9.69907 12.3819 9.78114C12.2764 9.86321 12.1557 9.92333 12.0266 9.95794C11.8976 9.99255 11.7629 10.001 11.6306 9.98267C11.4983 9.96437 11.3709 9.91975 11.2561 9.85143C11.1413 9.78311 11.0414 9.69248 10.9622 9.58489C10.883 9.4773 10.8262 9.35493 10.795 9.22501L10.431 7.86801C9.48404 8.00801 8.51604 8.00801 7.56904 7.86801L7.20504 9.22501C7.17392 9.35493 7.11709 9.4773 7.03789 9.58489C6.9587 9.69248 6.85875 9.78311 6.74395 9.85143C6.62914 9.91975 6.50181 9.96437 6.36948 9.98267C6.23714 10.001 6.10248 9.99255 5.97345 9.95794C5.84442 9.92333 5.72363 9.86321 5.61822 9.78114C5.51281 9.69907 5.42491 9.59671 5.35971 9.4801C5.29451 9.3635 5.25334 9.23501 5.23863 9.10223C5.22392 8.96945 5.23596 8.83506 5.27404 8.70701L5.63104 7.37201C4.79998 7.06392 4.0184 6.63607 3.31104 6.10201L2.00104 7.41401C1.81353 7.60179 1.55911 7.70738 1.29375 7.70757C1.02838 7.70776 0.773813 7.60252 0.58604 7.41501C0.398267 7.22751 0.292671 6.97309 0.292484 6.70772C0.292296 6.44236 0.397532 6.18779 0.58504 6.00001L1.86004 4.72501C1.07604 3.78901 0.45004 2.65101 0.04804 1.31101L0.0500398 1.31001Z\" fill=\"#430909\"/>");
        page.append("</svg>");
        page.append("</div>");
        page.append("<span id=\"password-error\" class=\"form__error\"></span>");

        page.append("<label for=\"date-input\" class=\"form__text\">Дата рождения</label>");
        page.append("<input type=\"date\" class=\"form__input\" id=\"date-input\">");
        page.append("<span id=\"date-error\" class=\"form__error\"></span>");

        page.append("</div>");
        page.append("<button class=\"form__btn\" id=\"submit-btn\">Get started</button>");
        page.append("<p>Have an account? <a href=\"./login\" class=\"form__link link-register\">Sig in</a></p>");
        page.append("</form>");
        page.append("</div>");

        page.append("<script>");
        page.append("const eyeIcon = document.querySelector('#icon-eye');");
        page.append("const reEyeIcon = document.querySelector('#re-icon-eye');");
        page.append("const passwordInput = document.querySelector('#password-input');");
        page.append("const rePasswordInput = document.querySelector('#repPassword-input');");
        page.append("const openEye = '<path d=\"M11 5C11.7956 5 12.5587 5.31607 13.1213 5.87868C13.6839 6.44129 14 7.20435 14 8C14 8.79565 13.6839 9.55871 13.1213 10.1213C12.5587 10.6839 11.7956 11 11 11C10.2044 11 9.44129 10.6839 8.87868 10.1213C8.31607 9.55871 8 8.79565 8 8C8 7.20435 8.31607 6.44129 8.87868 5.87868C9.44129 5.31607 10.2044 5 11 5ZM11 0.5C16 0.5 20.27 3.61 22 8C20.27 12.39 16 15.5 11 15.5C6 15.5 1.73 12.39 0 8C1.73 3.61 6 0.5 11 0.5ZM2.18 8C2.98825 9.65031 4.24331 11.0407 5.80248 12.0133C7.36165 12.9858 9.1624 13.5013 11 13.5013C12.8376 13.5013 14.6383 12.9858 16.1975 12.0133C17.7567 11.0407 19.0117 9.65031 19.82 8C19.0117 6.34969 17.7567 4.95925 16.1975 3.98675C14.6383 3.01424 12.8376 2.49868 11 2.49868C9.1624 2.49868 7.36165 3.01424 5.80248 3.98675C4.24331 4.95925 2.98825 6.34969 2.18 8Z\" fill=\"#430909\"/>';");
        page.append("const closeEye = '<path d=\"M0.0500398 1.31001C0.00753229 1.18307 -0.00905319 1.04888 0.00126676 0.915406C0.0115867 0.781931 0.0486021 0.651887 0.110118 0.532984C0.171634 0.414082 0.256398 0.308741 0.359384 0.223209C0.462371 0.137676 0.581483 0.0736927 0.709658 0.0350526C0.837834 -0.00358758 0.972463 -0.0160978 1.10556 -0.00173683C1.23866 0.0126241 1.36753 0.0535638 1.48451 0.118655C1.60149 0.183747 1.70422 0.271666 1.78659 0.377198C1.86896 0.482729 1.9293 0.603726 1.96404 0.733013C4.05004 7.71901 13.946 7.72001 16.034 0.737014C16.0715 0.611076 16.1333 0.493743 16.2161 0.391714C16.2989 0.289686 16.4009 0.204959 16.5165 0.142372C16.632 0.0797857 16.7587 0.0405647 16.8894 0.0269483C17.02 0.0133318 17.1521 0.0255866 17.278 0.0630134C17.404 0.10044 17.5213 0.162306 17.6233 0.245078C17.7254 0.32785 17.8101 0.429908 17.8727 0.545424C17.9353 0.66094 17.9745 0.787652 17.9881 0.918326C18.0017 1.049 17.9895 1.18108 17.952 1.30701C17.5884 2.5583 16.9713 3.7214 16.139 4.72401L17.414 6.00001C17.5962 6.18862 17.697 6.44122 17.6947 6.70342C17.6924 6.96561 17.5873 7.21642 17.4019 7.40183C17.2165 7.58724 16.9656 7.69241 16.7034 7.69469C16.4412 7.69697 16.1886 7.59617 16 7.41401L14.689 6.10301C13.9816 6.63672 13.2 7.06423 12.369 7.37201L12.726 8.70701C12.7641 8.83506 12.7762 8.96945 12.7615 9.10223C12.7467 9.23501 12.7056 9.3635 12.6404 9.4801C12.5752 9.59671 12.4873 9.69907 12.3819 9.78114C12.2764 9.86321 12.1557 9.92333 12.0266 9.95794C11.8976 9.99255 11.7629 10.001 11.6306 9.98267C11.4983 9.96437 11.3709 9.91975 11.2561 9.85143C11.1413 9.78311 11.0414 9.69248 10.9622 9.58489C10.883 9.4773 10.8262 9.35493 10.795 9.22501L10.431 7.86801C9.48404 8.00801 8.51604 8.00801 7.56904 7.86801L7.20504 9.22501C7.17392 9.35493 7.11709 9.4773 7.03789 9.58489C6.9587 9.69248 6.85875 9.78311 6.74395 9.85143C6.62914 9.91975 6.50181 9.96437 6.36948 9.98267C6.23714 10.001 6.10248 9.99255 5.97345 9.95794C5.84442 9.92333 5.72363 9.86321 5.61822 9.78114C5.51281 9.69907 5.42491 9.59671 5.35971 9.4801C5.29451 9.3635 5.25334 9.23501 5.23863 9.10223C5.22392 8.96945 5.23596 8.83506 5.27404 8.70701L5.63104 7.37201C4.79998 7.06392 4.0184 6.63607 3.31104 6.10201L2.00104 7.41401C1.81353 7.60179 1.55911 7.70738 1.29375 7.70757C1.02838 7.70776 0.773813 7.60252 0.58604 7.41501C0.398267 7.22751 0.292671 6.97309 0.292484 6.70772C0.292296 6.44236 0.397532 6.18779 0.58504 6.00001L1.86004 4.72501C1.07604 3.78901 0.45004 2.65101 0.04804 1.31101L0.0500398 1.31001Z\" fill=\"#430909\"/>';");
        page.append("eyeIcon.addEventListener('click', () = > {");
        page.append("if (passwordInput.type == = 'password') {");
        page.append("passwordInput.type = 'text';");
        page.append("eyeIcon.innerHTML = openEye;");
        page.append("} else {");
        page.append("passwordInput.type = 'password';");
        page.append("eyeIcon.innerHTML = closeEye;}");
        page.append("})");
        page.append("reEyeIcon.addEventListener('click', () = > {");
        page.append("if (rePasswordInput.type == = 'password') {");
        page.append("rePasswordInput.type = 'text';");
        page.append("reEyeIcon.innerHTML = openEye;");
        page.append("} else {");
        page.append("rePasswordInput.type = 'password';");
        page.append("reEyeIcon.innerHTML = closeEye;}");
        page.append("})");
        page.append("const validateEmail = (email) = > {");
        page.append("const re = / ^ [a - zA - Z0 - 9] + (? : [a - zA - Z0 - 9\\ - .] + ) * @[a - zA - Z0 - 9] + (? : -[a - zA - Z0 - 9] + ) * \\.[a - zA - Z] {2, }$ / ;");
        page.append("return re.test(String(email).toLowerCase());");
        page.append("}");
        page.append("const validatePassword = (password) = > {");
        page.append("const re = / ^ (? = .*[a - z])(? = .*[A - Z])(? = .*\\d)(? = .*[$_\\ - &])[a - zA - Z\\d$_\\ - &]{8, 64}$ / ;");
        page.append("return password.length >= 8 && re.test(password);");
        page.append("}");
        page.append("const emailInput = document.querySelector('#email-input');");
        page.append("const submitBtn = document.querySelector('#submit-btn');");
       
        page.append("const error_form = document.querySelectorAll('.form__error');");
        page.append("const form__input = document.querySelectorAll('.form__input');");
        
        page.append("submitBtn.addEventListener('click', (event) = > {");
        page.append("event.preventDefault()");
        page.append("let isValid = true;");
        page.append("for (let i = 0; i < error_form.length; i++) {");
        page.append("error_form[i].textContent = '';");
        page.append("}");
        page.append("const email = emailInput.value;");
        page.append("const password = passwordInput.value;");
        page.append("for (let i = 0; i < form__input.length; i++) {");
        page.append("if (form__input[i].textContent == = '') {");    
        page.append("error_form[i].textContent = 'Пустое поле'");        
        page.append("isValid = false;");            
        page.append("}");
        page.append("}");
        page.append("if (!validateEmail(email)) {");
        page.append("emailError.textContent = 'Неверный формат почты';");
        page.append("isValid = false;");
        page.append("}");
        page.append("if (!validatePassword(password)) {");
        page.append("passwordError.textContent = 'Пароль должен содержать минимум 8 символов, хотя бы одну заглавную и строчную букву, цифру и специальный символ ($ _ - &)';");
        page.append("isValid = false;");
        page.append("}");
        page.append("if (isValid) {");
        page.append("console.log('Данные валидны');");
        page.append("}");
        page.append("})");
        page.append("</script>");
        page.append("</body>");
        page.append("</html>");

        response.write(page,true);
    }
}
