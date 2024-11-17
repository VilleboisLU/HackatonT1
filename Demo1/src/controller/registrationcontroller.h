#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

using namespace stefanfrings;

class RegistrationController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(RegistrationController)
public:

    RegistrationController();

    void service(HttpRequest& request, HttpResponse& response);
};

#endif // LOGINCONTROLLER_H
