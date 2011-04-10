#include "createusercontrol.h"

CreateUserControl::CreateUserControl()
{
    _form = new CreateUserForm();
    connect(_form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

CreateUserControl::~CreateUserControl()
{
    delete _form;
}

void CreateUserControl::showForm()
{
    _form->clearContents();
    _form->show();
}

void CreateUserControl::_submitClicked()
{
    const QString& username	= _form->getUserName().trimmed();
    const QString& password	= _form->getPassword().trimmed();
    const QString& priveledge	= _form->getPriveledge().trimmed();

    if (!username.isEmpty() && !password.isEmpty() && !priveledge.isEmpty())
    {
	emit submitClicked(username, password, priveledge);
	_form->close();
    }
    else
    {
	_form->displayError();
    }
}
