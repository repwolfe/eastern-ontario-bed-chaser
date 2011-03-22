#include "storageHandler.h"
#include <QtXml/qdom.h>
#include "../Common/logger.h"

/**
  * This constructor takes the name of a file to load the model
  * @param filename: The name of the file.
  *
  * @todo implement a default constructor
StorageHandler::StorageHandler(QString fileName)
{
    StorageHandler handler = StorageHandler();
    if(handler.loadModel(fileName)){
        Logger::errorMessage("StorageHandler", "StorageHandler(filename)", "Failed to load file");
    }
    return handler
}
*/

/**
 * This loads the model from a file
 *
 * @param filename is the name of the file
 *
 * @return True if it worked, False otherwise
 */
int StorageHandler::loadModel(QString fileName){
    QDomDocument doc;
    QFile file(fileName += ".xml");

    //open the file
    QString* errorMsg;
    int* intPtr;
    bool NamespaceParsing = false;
    if( !file.open(QIODevice::ReadOnly) )
      return -1;
    if( !doc.setContent( file.readAll(), NamespaceParsing, errorMsg, intPtr, intPtr) ) //load the file into doc
    {
        Logger::errorMessage("storageHandler", "loadModel","Failed on getcontent()");
      file.close();
      return -2;
    }
    file.close();
    //load the file into the QDomElement
    QDomElement root = doc.documentElement();
    if( root.tagName() != "Area" )
      return -3;

    //parse the xml into objsects
    QDomNode n = root.firstChild();

            /** /// @todo change the parsing of this into a complex series of
                --if-- statements, or a switch
    while( !n.isNull() )
    {
      QDomElement e = n.toElement();
      if( !e.isNull() )
      {
        if( e.tagName() == "WaitingList" )
        {
          Contact c;

          c.name = e.attribute( "name", "" );
          c.phone = e.attribute( "phone", "" );
          c.eMail = e.attribute( "email", "" );

          QMessageBox::information( 0, "Contact", c.name + "\n" + c.phone + "\n" + c.eMail );
        }
      }

      n = n.nextSibling();
    }
    */
};

int StorageHandler::saveModel(QString filename, Area* anArea, int facilityID){
return 0;
};
