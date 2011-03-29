#include "createusercontrol.h"

CreateUserControl::CreateUserControl()
{
    form = new CreateUserForm();
    connect(form, SIGNAL(submitClicked()), SLOT(_submitClicked()));
}

CreateUserControl::~CreateUserControl()
{
    delete form;
}

void CreateUserControl::showForm()
{
    form->clearContents();
    form->show();
}

void CreateUserControl::_submitClicked()
{
    emit submitClicked(form->getUserName(), form->getPassword(),
		       form->getFirstName(), form->getLastName(), form->getPriveledge());
    form->close();
}
