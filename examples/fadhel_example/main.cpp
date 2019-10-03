#include <nodes/FlowScene>
#include <nodes/FlowView>

#include <QtWidgets/QApplication>

#include "InModel.h"
#include "OutModel.h"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;

//Registers the DataModels to be used in the program.
static std::shared_ptr<DataModelRegistry> registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();
  ret->registerModel<InModel>();
  ret->registerModel<OutModel>();
  return ret;
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  FlowScene scene(registerDataModels());
  FlowView view(&scene);

  view.setWindowTitle("fadhel Node example");
  view.resize(800, 600);
  view. show();

  return app.exec();
}


